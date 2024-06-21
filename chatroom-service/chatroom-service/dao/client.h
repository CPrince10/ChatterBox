#ifndef CLIENT_H__
#define CLIENT_H__
#include"api.h"


class Client {
public:
	//登录	用json传入ID和密码，返回成功与否
	status loginIn(TransPara transPara);
	//注册	用json传入密码和名字，返回生成的ID，如果不成功，则返回0
	int signUp(TransPara transPara);
};

#endif // CLIENT_H__