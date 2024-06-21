#include "../include/api.h"
#ifndef MESSAGE_H__
#define MESSAGE_H__

//月亮打烊了
//收消息json格式规范 ID(int) content(string)
//发消息同上
class Message {
private:
	/*
	* 聊天记录存储文件中的格式：
	* 人名  时间戳
	* 聊天内容
	* （空一行）
	* 下一个人名 时间戳
	* 聊天内容
	* ......
	*/
	
	//自己的名字，为全局变量,在api里面，即std::string name
	//写入聊天记录，用json传入单条的聊天记录和收信人ID，返回成功与否
	status writeIntoChatRecord(json content);

public:
	//发送消息，用json传入发送的消息内容和收信人ID，返回成功与否
	status sendMessage(json content);
	//接收消息，接收到消息时自动调用该函数，json中为发信人ID与消息内容（content）
	static void recvMessage(json content);
	//读出聊天记录，用json传入对方名称，用json返回所有聊天记录
	json readFromChatRecord(json content);

};

#endif // MESSAGE_H__


