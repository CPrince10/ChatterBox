#include <iostream>
#include <string>
#include "user.h"
#include"serverCommunication.h"

using namespace std;

status User::addFriend(json content)
{
	int friend_id = content["ID"];
	//	std::cout << "要添加的好友的ID是" << content_id << std::endl;
	json request;
	request["control"] = 22;//请求标识:添加好友      
	request["ID"] = friend_id;
	int returnValue= serverCommunication->QSendToServer(request) ;
	if (returnValue == -1) {
		return -1;
	}
	else {
			json rejson = serverCommunication->QRecvFromServer();
		rejson.at("status").get_to(returnValue);
		return returnValue;
	}
}

status User::delFriend(json content)
{
	int friend_id = content["ID"];
//	std::cout << "要删除的好友的ID是" << content_id << std::endl;
	json request;
	request["control"] = 23;//请求标识:删除好友
	request["ID"] = friend_id;
	int returnValue = serverCommunication->QSendToServer(request);
	if (returnValue == -1) {
		return -1;
	}
	else {
		json rejson = serverCommunication->QRecvFromServer();
		rejson.at("status").get_to(returnValue);
		return returnValue;
	}
}

json User::getFriendsList()
{
	json request;
	status returnValue;
	json error = {
		{"ID",-1},
		{"Name",NULL},
	};//如果返回好友数量为-1，则出错
	request["control"] = 11;
	returnValue = serverCommunication->QSendToServer(request);
	if (returnValue <= 0) return error;
	json list = serverCommunication->QRecvFromServer();
	return list;
}

status User::updateProfile(json content)
{
	json request = content;
	request["control"] = 26;
	int returnValue = serverCommunication->QSendToServer(request);
	if (returnValue == -1) {
		return -1;
	}
	else {
		json rejson = serverCommunication->QRecvFromServer();
		rejson.at("status").get_to(returnValue);
		return returnValue;
	}
}

json User::getProfile()
{
	json request;
		json error = {
		{"Username",NULL},
		{"Birthday",NULL},
		{"Gender",NULL},
		{"Constellation",NULL},
		{"Introduction",NULL}
	};//如果失败的话，id为-1
	request["control"] = 12;
	status returnValue = serverCommunication->QSendToServer(request);
	if (returnValue <= 0) return error;
	json list = serverCommunication->QRecvFromServer();
	name = list["Username"];
	return list;
}
