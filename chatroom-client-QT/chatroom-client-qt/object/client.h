#pragma once
#ifndef CLIENT_H__
#define CLIENT_H__
#include "../include/api.h"

//粒石
// ID一定5位数00001
// 密码：5~10位，数字或大小写字母
// 用户名规范：2~10位 数字或大小写字母
//json 规范：登录：ID(int)，password(string),
//			注册：password(string),name(string)
class Client {
public:
	//登录	用json传入ID和密码，返回成功与否
	status loginIn(json content);
	//注册	用json传入ID，密码和名字，返回生成的ID，若失败则返回0
	int signUp(json content);
};

#endif // CLIENT_H__


