#pragma once
#ifndef USER_H__
#define USER_H__
#include "../include/api.h"

//Oreo
//json 规范：
//加好友：ID(int)
//删好友同上
//获取好友列表：返回的好友数量num(int),多个ID(int),usrName(string)
//更改用户资料和获取用户资料：name(string),birthday(string),gender(char),constellation(string),introduction(string)
class User {
public:
	//加好友 用json传入要加的好友ID，返回成功与否
	status addFriend(json content);
	//删好友 同上
	status delFriend(json content);
	//获取好友列表 用json返回好友列表
	json getFriendsList();

	//更改用户资料 用json传入要更改的用户资料，返回成功与否
	status updateProfile(json content);
	//获取用户资料	用json返回用户资料 获取到用户资料以后，把全局变量中的name改成json返回值中的名字
	json getProfile();
};

#endif // USER_H__
