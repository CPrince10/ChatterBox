#include "api.h"
#include <cstdlib>
#include "hv/hloop.h"
#include "hv/hsocket.h"
#include "hv/hthread.h"
#include <map>

// 定义一个全局数组用于存储 hio_t* 对象
 std::map<int, hio_t*>  idToSocket;
 std::map<hio_t*, int>  socketToId;

//#define MAX_CONNECTIONS 50
//hio_t* connections[MAX_CONNECTIONS];
//int ID[MAX_CONNECTIONS];
//int connection_count = 0;

//数据库相关的连接对象
sql::mysql::MySQL_Driver* driver;
sql::Connection* con = nullptr;


TransPara::TransPara(json tranJson, int id)
{
	this->tranJson = tranJson;
	this->id = id;
}
