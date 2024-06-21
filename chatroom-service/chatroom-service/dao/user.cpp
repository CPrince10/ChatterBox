#include "user.h"
#include "api.h"

using namespace std;

//加好友 传入id与json，json 包含传入要加的好友ID，返回成功与否
status User::addFriend(TransPara transpara)
{
	string stat;
	stat = "SELECT COUNT(*) AS FriendCount FROM friend WHERE (UserID = "
		+ to_string(transpara.id) + " AND FriendID = "
		+ to_string(transpara.tranJson["ID"]) + ") OR (UserID = "
		+ to_string(transpara.tranJson["ID"]) + " AND FriendID = "
		+ to_string(transpara.id) + " );";
	std::cout <<"addFriend:query exist:" << stat << std::endl;
	try {
		MYSQL_QUERY(stat);
		res->next();
		int fri_count = res->getInt("FriendCount");
		delete res;
		if (fri_count != 0) return 0;
		else {
			stat = "INSERT INTO friend (UserID,FriendID)"
				" VALUES ("
				+ to_string(transpara.id) + ","
				+ to_string(transpara.tranJson["ID"]) + ");";//数据库操
			std::cout <<"addFriend:insert friend  " <<stat << std::endl; //输出sql语句
			sql::Statement* stmt; stmt = con->createStatement(); bool returnValue = stmt->execute(stat); ;
			int rowAffect = stmt->getUpdateCount();
			delete stmt;
			if (rowAffect == 1) {
				return 1;
			}
			else {
				return 0;
			};
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::cerr << "SQL state: " << e.getSQLState() << std::endl;
		return -1;
	}
}

//删好友 同上
status User::delFriend(TransPara transPara)
{
	string stat;
	stat = "DELETE FROM friend WHERE (UserID = "
		+ to_string(transPara.id)
		+ " AND FriendID =  "
		+ to_string(transPara.tranJson["ID"]) + ") OR (UserID = "
		+ to_string(transPara.id)
		+ " AND FriendID =  " + to_string(transPara.tranJson["ID"]) + ");";  //操作选项
	std::cout << stat << std::endl; //输出sql语句
	sql::Statement* stmt; stmt = con->createStatement(); bool returnValue = stmt->execute(stat); 
	int rowAffect = stmt->getUpdateCount();
	delete stmt;
	if (rowAffect == 1) {
		return 1;
	}
	else {
		return 0;
	};
}

//获取好友列表 用json返回好友列表 传入id
json User::getFriendsList(TransPara transPara)
{
	string stat;
	stat = "SELECT COUNT(*) AS FriendCount From friend WHERE (UserID = "
		+ to_string(transPara.id) + ") OR (FriendID = "
		+ to_string(transPara.id) + ");";
	std::cout << stat << std::endl; //输出sql语句
	try {
		sql::Statement* stmt; sql::ResultSet* res;
		stmt = con->createStatement(); res = stmt->executeQuery(stat);;
		res->next();
		int fri_count = res->getInt("FriendCount");
		delete res;
		if (fri_count == 0) {
			json result_array = {
				{"ID",0},
				{"Name",NULL}
			};
			return result_array;
		}
		else {
			stat = "SELECT user.ID AS FriendID,user.Username AS FriendName FROM friend JOIN user ON friend.FriendID = user.ID WHERE friend.UserID = "
				+ to_string(transPara.id) + " UNION SELECT user.ID AS FriendID,user.Username AS FriendName FROM friend JOIN user ON friend.UserID = user.ID WHERE friend.FriendID = "
				+ to_string(transPara.id) + " ORDER BY FriendID;";
			//查找该id的好友列表
			std::cout << stat << std::endl; //输出sql语句
			//try catch 判断query
			try {
				sql::Statement* stmt; sql::ResultSet* res; stmt = con->createStatement(); res = stmt->executeQuery(stat);;
				json result_array = json::array();
				//处理结果集
				//第一组的ID表示好友数量
				json row;
				row["ID"] = fri_count;
				row["Name"] = "";
				result_array.push_back(row);
				//下面存储好友信息
				while (res->next())
				{
					json row;
					row["ID"] = res->getInt("FriendID");
					row["Name"] = res->getString("FriendName");
					result_array.push_back(row);
				}
				delete res;
				return result_array;
			}
			catch (sql::SQLException& e) {
				std::cerr << "MySQL error: " << e.what() << std::endl;
				std::cerr << "SQL state: " << e.getSQLState() << std::endl;
			}
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::cerr << "SQL state: " << e.getSQLState() << std::endl;
	}
}

//更改用户资料 传入id与json，json 包含传入要更改的用户资料，返回成功与否 
status User::updateProfile(TransPara transPara)
{
	string stat;
	std::string name = transPara.tranJson["name"];
	std::string birthday = transPara.tranJson["birthday"];
	std::string gender = transPara.tranJson["gender"];
	std::string constellation = transPara.tranJson["constellation"];
	std::string introduction = transPara.tranJson["introduction"];

	stat = "UPDATE user SET Username = '" + name;
	if (birthday != "") {
		stat += "', Birthday = '" + birthday;
	}
		stat+= "', Gender = '" + gender
		+ "', Constellation = '" + constellation
		+ "', Introduction = '" + introduction
		+ "' WHERE ID = " + std::to_string(transPara.id);

	std::cout << stat << std::endl; //输出sql语句
	sql::Statement* stmt; stmt = con->createStatement(); bool returnValue = stmt->execute(stat);
	int rowAffect = stmt->getUpdateCount();
	delete stmt;
	return rowAffect == 0 ? 0 : 1;
}

//获取用户资料	用json返回用户资料 获取到用户资料以后，把全局变量中的name改成json返回值中的名字 传入id
json User::getProfile(TransPara transPara)
{
	string stat;
	stat = "SELECT * FROM user WHERE ID = "
		+ to_string(transPara.id) + ";";
	std::cout << stat << std::endl; //输出sql语句
	try {
		MYSQL_QUERY(stat);
		json result;
		while(res->next())  //如果找不到该用户的资料，name为NULL
		{
		result["Username"] = res->getString("Username");
		result["Birthday"] = res->getString("Birthday");
		result["Gender"] = res->getString("Gender");
		result["Constellation"] = res->getString("Constellation");
		result["Introduction"] = res->getString("Introduction");
		}
			delete res;
		return result;
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::cerr << "SQL state: " << e.getSQLState() << std::endl;
	}
}