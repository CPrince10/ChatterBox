#ifndef CLIENT_H__
#define CLIENT_H__
#include"api.h"


class Client {
public:
	//��¼	��json����ID�����룬���سɹ����
	status loginIn(TransPara transPara);
	//ע��	��json������������֣��������ɵ�ID��������ɹ����򷵻�0
	int signUp(TransPara transPara);
};

#endif // CLIENT_H__