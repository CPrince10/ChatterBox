#pragma once
#ifndef RECVSERVICE_H__
#define RECVSERVICE_H__
#include "api.h"


/*
*	本文件：service层文件，完成接收有关的逻辑判断，接收controller请求，完成逻辑处理并且调用object的对应成员函数
*/

//发送操作的抽象类
class RecvSuper {
public:
	virtual json communicate();
};

//接受信息
class RecvMessage
{
public:
	void recvMessage(json content);
};

//获取好友列表
class GetFriendsList : public RecvSuper {
public:
	json communicate();
};

//获取个人资料
class GetProfile : public RecvSuper {
public:
	json communicate();
};

#endif // RECVSERVICE_H__
