#ifndef API_H__
#define API_H__
#include<iostream>
#include<string>
#include "mysql/mysql/jdbc.h"
#include <nlohmann/json.hpp>
#include "hv/hloop.h"
#include<map>
//json 库的命名空间定义，使用json代替nlohmann::json，减少代码量
using json = nlohmann::json;

//定义网络传输时的状态码，-1表示无法连接服务器，0表示已连接但被拒绝服务或者输入不合法，1表示操作成功
typedef int status;

//处理状态的宏定义
#define STATUS_HANDELLING(stu)\
	if (stu == -1) {\
		return -1;\
	}\
	else if(stu==0){\
		return 0;\
	}\
	else {\
		return 1;\
	}

//// 定义一个全局数组用于存储 hio_t* 对象
//#define MAX_CONNECTIONS 10
//extern hio_t* connections[MAX_CONNECTIONS];
//extern int connection_count;
// 定义一个全局数组用于存储 hio_t* 对象
extern std::map<int, hio_t*>  idToSocket;
extern std::map<hio_t*, int>  socketToId;

//传输参数类
class TransPara{
public:
	json tranJson;
	//id为发起请求者的ID
	int id;
	//构造对象
	TransPara(json tranJson, int id);
};

//全局通用变量声明
extern sql::mysql::MySQL_Driver* driver;
extern sql::Connection* con;

//数据库操作宏，传入string类型的sql语句即可完成操作
#define MYSQL_EXCUTABLE(sqlState)\
sql::Statement *stmt;\
stmt= con->createStatement();\
bool returnValue = stmt->execute(sqlState);\
delete stmt;
//数据库查询宏，传入string类型的sql语句即可查询，返回一个名为res的ResultSet类型，可以从中提取出查询到的结果
//使用完res以后记得delete res;
#define MYSQL_QUERY(sqlState)\
sql::Statement *stmt;\
sql::ResultSet *res;\
stmt=con->createStatement();\
res=stmt->executeQuery(sqlState);

#endif // API_H__


