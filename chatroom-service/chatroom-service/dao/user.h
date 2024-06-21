#ifndef USER_H__
#define USER_H__
#include"api.h"

class User {
public:
	//加好友 传入id与json，json 包含传入要加的好友ID，返回成功与否
	status addFriend(TransPara transPara);
	//删好友 同上
	status delFriend(TransPara transPara);
	//获取好友列表 用json返回好友列表 传入id
	json getFriendsList(TransPara transPara);

	//更改用户资料 传入id与json，json 包含传入要更改的用户资料，返回成功与否 
	status updateProfile(TransPara transPara);
	//获取用户资料	用json返回用户资料 获取到用户资料以后，把全局变量中的name改成json返回值中的名字 传入id
	json getProfile(TransPara transPara);
};


#endif // USER_H__