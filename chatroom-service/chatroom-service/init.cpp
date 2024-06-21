#include "init.h"
#include<cstdlib>
#include<mutex>
#include"api.h"
#include "hv/hloop.h"
#include "hv/hsocket.h"
#include "hv/hthread.h"
#include "controller/controller.h"
void initMySQL();
void initNet();

// ������������ַ�Ͷ˿�
static const char* host = "0.0.0.0";
static const int port = 1234;
// �����߳�����
static int thread_num = 5;
// ��������ѭ��
static hloop_t* accept_loop = nullptr;
// �����̵߳��¼�ѭ������
static hloop_t** worker_loops = nullptr;

//��ʼ����Ŀ
void initProj() {
	initMySQL();
	initNet();
}

// ��ȡ��һ�������̵߳��¼�ѭ��
static hloop_t* get_next_loop() {
	static int s_cur_index = 0;
	if (s_cur_index == thread_num) {
		s_cur_index = 0;
	}
	return worker_loops[s_cur_index++];
}

// ���ӹرջص�����
static void on_close(hio_t* io) {
	int id = socketToId[io];
	idToSocket.erase(id);
	socketToId.erase(io);
	printf("on_close fd=%d error=%d\n", hio_fd(io), hio_error(io));
}

// ���ݽ��ջص�����
static void on_recv(hio_t* io, void* buf, int readbytes) {
	const char* charContent = static_cast<const char*>(buf);
	std::string stringContent = std::string(charContent, readbytes);
	json content = json::parse(stringContent);
	int control = content["control"];
	if (control < 20) {
		RecvContext rc(control % 10);
		//��json
		json nullJson = {};
		//���촫�����
		TransPara transPara(nullJson, socketToId[io]);
		//�����²�ӿ�
		json returnJson = rc.getResult(transPara);
		std::string returnString = returnJson.dump();
		std::cout << returnString << std::endl;
		const void* buffer = static_cast<const void*>(returnString.data());
		size_t length = returnString.length();
		hio_write(io, buffer, length);
	}
	else {
		SendContext sc(control % 10);
		//���촫�����
		TransPara transPara(content, (control == 25) ? (0) : (socketToId[io]));
		int returnStatus = sc.getResult(transPara);
		//��¼ʱ���洢��ID���׽��ֽ�map����
		if (control == 24 && returnStatus == 1) {
			int id = content["ID"];
			idToSocket[id] = io;
			socketToId[io] = id;
		}

		json returnJson = {
			{"status",returnStatus},
		};
		std::string returnString = returnJson.dump();
		std::cout << returnString << std::endl;
		const void* buffer = static_cast<const void*>(returnString.data());
		size_t length = returnString.length();
		hio_write(io, buffer, length);
	}
}

// �������¼�������
static void new_conn_event(hevent_t* ev) {
	hloop_t* loop = ev->loop;
	hio_t* io = (hio_t*)hevent_userdata(ev);


	// �������ӵ��¼�ѭ���󶨵������̵߳��¼�ѭ����
	hio_attach(loop, io);

	char localaddrstr[SOCKADDR_STRLEN] = { 0 };
	char peeraddrstr[SOCKADDR_STRLEN] = { 0 };
	printf("tid=%ld connfd=%d [%s] <= [%s]\n",
		(long)hv_gettid(),
		(int)hio_fd(io),
		SOCKADDR_STR(hio_localaddr(io), localaddrstr),
		SOCKADDR_STR(hio_peeraddr(io), peeraddrstr));

	// �������ӵĹرպ����ݽ��ջص�����������ʼ��������
	hio_setcb_close(io, on_close);
	hio_setcb_read(io, on_recv);
	hio_read(io);
}

// ���ӽ��ܻص�����
static void on_accept(hio_t* io) {
	// �����Ӵ���ѭ���Ϸ��룬�Ա�����ɹ����̴߳���
	hio_detach(io);

	// ��ȡ��һ�������̵߳��¼�ѭ�������������ӵ��¼����뵽�����̵߳��¼�������
	hloop_t* worker_loop = get_next_loop();
	hevent_t ev;
	memset(&ev, 0, sizeof(ev));
	ev.loop = worker_loop;
	ev.cb = new_conn_event;
	ev.userdata = io;
	hloop_post_event(worker_loop, &ev);
}

// �����̺߳���
static HTHREAD_RETTYPE worker_thread(void* userdata) {
	hloop_t* loop = (hloop_t*)userdata;
	// ���й����̵߳��¼�ѭ��
	hloop_run(loop);
	return 0;
}

// �������ӵ��̺߳���
static HTHREAD_RETTYPE accept_thread(void* userdata) {
	hloop_t* loop = (hloop_t*)userdata;
	// ����һ��TCP����������ʼ��������
	hio_t* listenio = hloop_create_tcp_server(loop, host, port, on_accept);
	if (listenio == NULL) {
		exit(EXIT_FAILURE);
	}
	// ���н������ӵ��¼�ѭ��
	hloop_run(loop);
	return 0;
}

void initMySQL()
{
	try
	{
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "123456");
		con->setSchema("chatroom_sys");
	}
	catch (std::exception e) {
		std::cerr << "Connect to mysql failed, the reason is:" << std::endl;
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Connect to mysql success" << std::endl<<std::endl<<std::endl;
}

void initNet()
{
	// ��ʼ�������̵߳��¼�ѭ�����飬�����������߳�
	worker_loops = (hloop_t**)malloc(sizeof(hloop_t*) * thread_num);
	for (int i = 0; i < thread_num; ++i) {
		worker_loops[i] = hloop_new(HLOOP_FLAG_AUTO_FREE);
		hthread_create(worker_thread, worker_loops[i]);
	}

	// ������������ѭ���������н������ӵ��¼�ѭ��
	accept_loop = hloop_new(HLOOP_FLAG_AUTO_FREE);
	accept_thread(accept_loop);
}

