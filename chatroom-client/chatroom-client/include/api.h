//头文件
#ifndef API_H__
#define API_H__
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

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


#define JSON_TO_QSTRING(content)\
std::string jsonString = content.dump();\
QString qString = QString::fromStdString(jsonString);

#define QBYTEARRAY_TO_JSON(content)\
std::string string = content.toStdString();\
json returnJson = json::parse(string);

class ServerCommunication;
class NetCommunication;

//全局通用的数据
void init();
extern NetCommunication* netCommunication;
extern ServerCommunication* serverCommunication;
extern std::string ip;
extern int port;
extern std::string name;

#endif // API_H__
