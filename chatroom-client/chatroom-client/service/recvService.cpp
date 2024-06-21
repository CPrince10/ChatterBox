#include "recvService.h"
#include "../object/user.h"
#include "../netcommunication.h"

json RecvSuper::communicate()
{
	return {};
}

void RecvMessage::recvMessage(json content)
{
	netCommunication->getNetReceiver()->recv(content);
}

json GetFriendsList::communicate()
{
	User user;
	return user.getFriendsList();
}

json GetProfile::communicate()
{
	User user;
	return user.getProfile();
}
