#ifndef API_H__
#define API_H__
#include<iostream>
#include<string>
#include "mysql/mysql/jdbc.h"
#include <nlohmann/json.hpp>
#include "hv/hloop.h"
#include<map>
//json ��������ռ䶨�壬ʹ��json����nlohmann::json�����ٴ�����
using json = nlohmann::json;

//�������紫��ʱ��״̬�룬-1��ʾ�޷����ӷ�������0��ʾ�����ӵ����ܾ�����������벻�Ϸ���1��ʾ�����ɹ�
typedef int status;

//����״̬�ĺ궨��
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

//// ����һ��ȫ���������ڴ洢 hio_t* ����
//#define MAX_CONNECTIONS 10
//extern hio_t* connections[MAX_CONNECTIONS];
//extern int connection_count;
// ����һ��ȫ���������ڴ洢 hio_t* ����
extern std::map<int, hio_t*>  idToSocket;
extern std::map<hio_t*, int>  socketToId;

//���������
class TransPara{
public:
	json tranJson;
	//idΪ���������ߵ�ID
	int id;
	//�������
	TransPara(json tranJson, int id);
};

//ȫ��ͨ�ñ�������
extern sql::mysql::MySQL_Driver* driver;
extern sql::Connection* con;

//���ݿ�����꣬����string���͵�sql��伴����ɲ���
#define MYSQL_EXCUTABLE(sqlState)\
sql::Statement *stmt;\
stmt= con->createStatement();\
bool returnValue = stmt->execute(sqlState);\
delete stmt;
//���ݿ��ѯ�꣬����string���͵�sql��伴�ɲ�ѯ������һ����Ϊres��ResultSet���ͣ����Դ�����ȡ����ѯ���Ľ��
//ʹ����res�Ժ�ǵ�delete res;
#define MYSQL_QUERY(sqlState)\
sql::Statement *stmt;\
sql::ResultSet *res;\
stmt=con->createStatement();\
res=stmt->executeQuery(sqlState);

#endif // API_H__


