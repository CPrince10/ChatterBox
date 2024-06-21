#ifndef MESSAGE_H__
#define MESSAGE_H__
#include"api.h"

class Message {

public:
	//核心接口，发消息接口，传入的参数有json和ID，通过收信人的ID，在全局map中查找到其对应的socket并发送给对方
	status sendMessage(TransPara transPara);
};


#endif // MESSAGE_H__