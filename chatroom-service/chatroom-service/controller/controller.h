#ifndef CONTROLLER_H__
#define CONTROLLER_H__
#include"api.h"
#include "../service/service.h"

//控制器，传入对应的数字完成构造，后调用对象的getresult(json content);方法完成操作


//客户端需要获取数据的操作的上下文接口，用于线程主操作调用，返回对应的json数据
class RecvContext
{
	RecvSuper *rs=nullptr;
public:
	//构造对象
	RecvContext(status sta);

	//调用对应接口的方法
	json getResult(TransPara transPara);
};


//客户端不需要获取数据的操作的上下文接口，用于线程主操作调用，返回对应的json数据
class SendContext
{
	SendSuper *as=nullptr;
public:
	//构造对象
	SendContext(status sta);

	//调用对应接口的方法
	status getResult(TransPara transPara);
};

#endif // CONTROLLER_H__