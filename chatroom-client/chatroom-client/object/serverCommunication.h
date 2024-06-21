#include "../include/api.h"
#pragma once
#ifndef SERVERCOMMUNICATION_H__
#define SERVERCOMMUNICATION_H__

class ServerCommunication {
private:
	ServerCommunication();
	static ServerCommunication* serverCommunication;
public:

	static ServerCommunication* getInstance();

	//向服务器传输信息	传入要传输的json，返回成功与否，-1=失败，除了-1都是成功
	status QSendToServer(json content);
	//接收服务器传来的信息	返回接收到的json
	//json 格式：状态码 status(int)
	json QRecvFromServer();

	//异步接受服务器消息 传入json,无返回值
	void asynRecvFromServer(json content);
	//是否断开服务器函数，若断开连接，传入-1
	void disconnect(status sta);
	//是否连接上服务器函数，若成功连接，传入1
	void connect(status sta);
};

#endif // SERVERCOMMUNICATION_H__

