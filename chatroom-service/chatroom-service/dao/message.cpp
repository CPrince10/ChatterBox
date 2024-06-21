#include "message.h"
#include "api.h"

using namespace std;
//核心接口，发消息接口，传入的参数有json和ID，通过收信人的ID，
//在全局map中查找到其对应的socket并发送给对方
status Message::sendMessage(TransPara transPara)
{
	//我的id
	int id = transPara.id;
	//对方的id
	int iid= transPara.tranJson["ID"];
	//查看对方是否在线
		auto it = idToSocket.find(iid);
	// 在线
	if (it != idToSocket.end()) {

		//查找数据库,两人是否为好友
		string sql;
		sql = "select * from friend where (UserID= " + to_string(id)
			+ " and FriendID= " + to_string(iid) + ") or (FriendID= " + to_string(id)
			+ " and UserID= " + to_string(iid) + ");";
		MYSQL_QUERY(sql);
		if (res->next())
		{

			//发送数据
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
	// 不在线
	else {
		return 0;
	}
	




}
