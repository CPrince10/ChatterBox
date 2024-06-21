#include "service.h"
#include "../dao/user.h"
#include "../dao/client.h"
#include "../dao/message.h"


json GetFriendsList::communicate(TransPara transPara)
{
	User user;
	return user.getFriendsList(transPara);
}

json GetProfile::communicate(TransPara transPara)
{
	User user;
	return user.getProfile(transPara);
}


status SendMess::communicate(TransPara transPara) {
	Message mess;
	return mess.sendMessage(transPara);
}

status AddFriend::communicate(TransPara transPara)
{
	User user;
	return user.addFriend(transPara);
}

status DelFriend::communicate(TransPara transPara)
{
	User user;
	return user.delFriend(transPara);
}

status UpdateProfile::communicate(TransPara transPara)
{
	User user;
	return user.updateProfile(transPara);
}

status LoginIn::communicate(TransPara transPara)
{
	Client client;
	return client.loginIn(transPara);
}

int SignUp::communicate(TransPara transPara)
{
	Client client;
	return client.signUp(transPara);
}
