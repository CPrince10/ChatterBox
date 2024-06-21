#include "sendService.h"
#include "../object/user.h"
#include "../object/client.h"
#include "../object/message.h"

status SendMessage::communicate(json content) {
	Message mess;
	return mess.sendMessage(content);
}

status SendSuper::communicate(json content)
{
	return 0;
}

status AddFriend::communicate(json content)
{
	User user;
	return user.addFriend(content);
}

status DelFriend::communicate(json content)
{
	User user;
	return user.delFriend(content);
}

status UpdateProfile::communicate(json content)
{
	User user;
	return user.updateProfile(content);
}

status LoginIn::communicate(json content)
{
	Client client;
	return client.loginIn(content);
}

status SignUp::communicate(json content)
{
	Client client;
	return client.signUp(content);
}
