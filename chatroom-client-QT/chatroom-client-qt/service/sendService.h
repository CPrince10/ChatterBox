#pragma once
#ifndef SENDSERVICE_H__
#define SENDSERVICE_H__
#include "api.h"

/*
*	本文件：service层文件，完成发送有关的逻辑判断，接收controller请求，完成逻辑处理并且调用object的对应成员函数
*/

//发送操作的抽象类
class SendSuper {
public:
	virtual status communicate(json content)=0;
};

//发送消息
class SendMessage : public SendSuper {
public:
	status communicate(json content);
};

//加好友
class AddFriend : public SendSuper {
public:
	status communicate(json content);
};

//删除好友
class DelFriend : public SendSuper {

public:
	status communicate(json content);
};

//更改用户资料
class UpdateProfile : public SendSuper {
public:
	status communicate(json content);
};

//登录
class LoginIn : public SendSuper {
public:
	status communicate(json content);
};

//注册
class SignUp : public SendSuper {
public:
	int communicate(json content);
};


#endif // SENDSERVICE_H__
