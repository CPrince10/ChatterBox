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

// 服务器监听地址和端口
static const char* host = "0.0.0.0";
static const int port = 1234;
// 工作线程数量
static int thread_num = 5;
// 服务器主循环
static hloop_t* accept_loop = nullptr;
// 工作线程的事件循环数组
static hloop_t** worker_loops = nullptr;

//初始化项目
void initProj() {
	initMySQL();
	initNet();
}

// 获取下一个工作线程的事件循环
static hloop_t* get_next_loop() {
	static int s_cur_index = 0;
	if (s_cur_index == thread_num) {
		s_cur_index = 0;
	}
	return worker_loops[s_cur_index++];
}

// 连接关闭回调函数
static void on_close(hio_t* io) {
	int id = socketToId[io];
	idToSocket.erase(id);
	socketToId.erase(io);
	printf("on_close fd=%d error=%d\n", hio_fd(io), hio_error(io));
}

// 数据接收回调函数
static void on_recv(hio_t* io, void* buf, int readbytes) {
	const char* charContent = static_cast<const char*>(buf);
	std::string stringContent = std::string(charContent, readbytes);
	json content = json::parse(stringContent);
	int control = content["control"];
	if (control < 20) {
		RecvContext rc(control % 10);
		//空json
		json nullJson = {};
		//构造传输参数
		TransPara transPara(nullJson, socketToId[io]);
		//调用下层接口
		json returnJson = rc.getResult(transPara);
		std::string returnString = returnJson.dump();
		std::cout << returnString << std::endl;
		const void* buffer = static_cast<const void*>(returnString.data());
		size_t length = returnString.length();
		hio_write(io, buffer, length);
	}
	else {
		SendContext sc(control % 10);
		//构造传输参数
		TransPara transPara(content, (control == 25) ? (0) : (socketToId[io]));
		int returnStatus = sc.getResult(transPara);
		//登录时，存储该ID与套接字进map当中
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

// 新连接事件处理函数
static void new_conn_event(hevent_t* ev) {
	hloop_t* loop = ev->loop;
	hio_t* io = (hio_t*)hevent_userdata(ev);


	// 将新连接的事件循环绑定到工作线程的事件循环上
	hio_attach(loop, io);

	char localaddrstr[SOCKADDR_STRLEN] = { 0 };
	char peeraddrstr[SOCKADDR_STRLEN] = { 0 };
	printf("tid=%ld connfd=%d [%s] <= [%s]\n",
		(long)hv_gettid(),
		(int)hio_fd(io),
		SOCKADDR_STR(hio_localaddr(io), localaddrstr),
		SOCKADDR_STR(hio_peeraddr(io), peeraddrstr));

	// 设置连接的关闭和数据接收回调函数，并开始监听数据
	hio_setcb_close(io, on_close);
	hio_setcb_read(io, on_recv);
	hio_read(io);
}

// 连接接受回调函数
static void on_accept(hio_t* io) {
	// 将连接从主循环上分离，以便后续由工作线程处理
	hio_detach(io);

	// 获取下一个工作线程的事件循环，并将新连接的事件加入到工作线程的事件队列中
	hloop_t* worker_loop = get_next_loop();
	hevent_t ev;
	memset(&ev, 0, sizeof(ev));
	ev.loop = worker_loop;
	ev.cb = new_conn_event;
	ev.userdata = io;
	hloop_post_event(worker_loop, &ev);
}

// 工作线程函数
static HTHREAD_RETTYPE worker_thread(void* userdata) {
	hloop_t* loop = (hloop_t*)userdata;
	// 运行工作线程的事件循环
	hloop_run(loop);
	return 0;
}

// 接受连接的线程函数
static HTHREAD_RETTYPE accept_thread(void* userdata) {
	hloop_t* loop = (hloop_t*)userdata;
	// 创建一个TCP服务器并开始监听连接
	hio_t* listenio = hloop_create_tcp_server(loop, host, port, on_accept);
	if (listenio == NULL) {
		exit(EXIT_FAILURE);
	}
	// 运行接受连接的事件循环
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
	// 初始化工作线程的事件循环数组，并创建工作线程
	worker_loops = (hloop_t**)malloc(sizeof(hloop_t*) * thread_num);
	for (int i = 0; i < thread_num; ++i) {
		worker_loops[i] = hloop_new(HLOOP_FLAG_AUTO_FREE);
		hthread_create(worker_thread, worker_loops[i]);
	}

	// 创建服务器主循环，并运行接受连接的事件循环
	accept_loop = hloop_new(HLOOP_FLAG_AUTO_FREE);
	accept_thread(accept_loop);
}

