#pragma once
#ifndef CONTROLLER_H__
#define CONTROLLER_H__
#include "../include/api.h"
#include "../service/recvService.h"
#include "../service/sendService.h"

class NetReceiver
{
public:
	virtual void recv(json content) = 0;
	virtual void disconnect(status) = 0;
};


//接收数据的上下文接口，用于前端调用，能够生成对应的接口对象
class RecvContext
{
	RecvSuper rs;
public:
	//构造对象
	RecvContext(status sta);

	//调用对应接口的方法
	json getResult();
};


//发送数据的上下文接口，用于前端调用，能够生成对应的接口对象
class SendContext
{
	SendSuper as;
public:
	//构造对象
	SendContext(status sta);

	//调用对应接口的方法
	status getResult(json content);
};



#endif // CONTROLLER_H__

