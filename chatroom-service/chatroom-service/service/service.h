#ifndef SERVICE_H__
#define SERVICE_H__
#include"api.h"

//service 层文件，完成所有与逻辑处理相关的操作

//客户端获取消息的操作抽象类
class RecvSuper {
public:
	virtual json communicate(TransPara transPara)=0;
};

//客户端需要发送消息的操作抽象类
class SendSuper {
public:
	virtual status communicate(TransPara transPara)=0;
};

//============================================================
//获取好友列表
class GetFriendsList : public RecvSuper {
public:
	json communicate(TransPara transPara);
};

//获取个人资料
class GetProfile : public RecvSuper {
public:
	json communicate(TransPara transPara);
};


//=============================================================
//发送消息
class SendMess : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//加好友
class AddFriend : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//删除好友
class DelFriend : public SendSuper {

public:
	status communicate(TransPara transPara);
};

//更改用户资料
class UpdateProfile : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//登录
class LoginIn : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//注册
class SignUp : public SendSuper {
public:
	status communicate(TransPara transPara);
};

#endif // SERVICE_H__