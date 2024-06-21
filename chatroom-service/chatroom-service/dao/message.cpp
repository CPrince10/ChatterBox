#include "message.h"
#include "api.h"

using namespace std;
//���Ľӿڣ�����Ϣ�ӿڣ�����Ĳ�����json��ID��ͨ�������˵�ID��
//��ȫ��map�в��ҵ����Ӧ��socket�����͸��Է�
status Message::sendMessage(TransPara transPara)
{
	//�ҵ�id
	int id = transPara.id;
	//�Է���id
	int iid= transPara.tranJson["ID"];
	//�鿴�Է��Ƿ�����
		auto it = idToSocket.find(iid);
	// ����
	if (it != idToSocket.end()) {

		//�������ݿ�,�����Ƿ�Ϊ����
		string sql;
		sql = "select * from friend where (UserID= " + to_string(id)
			+ " and FriendID= " + to_string(iid) + ") or (FriendID= " + to_string(id)
			+ " and UserID= " + to_string(iid) + ");";
		MYSQL_QUERY(sql);
		if (res->next())
		{

			//��������
			delete res;
			cout << "Find the friend." << endl;
			transPara.tranJson["ID"] = id;
			string returnString = transPara.tranJson.dump();
			const void* buffer = static_cast<const void*>(returnString.data());
			size_t length = returnString.length();
			int a = hio_write(idToSocket[iid], buffer, length);
			if (a == -1 || a == 0) {
				return 0;
			}
			else {
				cout << "Message sent successfully." << endl;
				return 1;
			}
		}


		else {
			delete res;

			return 0;
		}
	}
	// ������
	else {
		return 0;
	}
	




}
