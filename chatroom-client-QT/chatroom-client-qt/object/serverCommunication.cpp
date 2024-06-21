#include "serverCommunication.h"
#include "../netcommunication.h"
#include "message.h"


ServerCommunication::ServerCommunication()
{

}

ServerCommunication* ServerCommunication::serverCommunication = nullptr;

ServerCommunication* ServerCommunication::getInstance()
{
	if (serverCommunication == nullptr) {
		serverCommunication = new ServerCommunication;
	}
	return serverCommunication;
}

status ServerCommunication::QSendToServer(json content)
{
	return netCommunication->sendToServer(content);
}

json ServerCommunication::QRecvFromServer()
{
	return netCommunication->ReceiveInformation();
}

void ServerCommunication::asynRecvFromServer(json content)
{
	Message::recvMessage(content);
}

void ServerCommunication::disconnect(status sta)
{	netCommunication->getNetReceiver()->disconnect(sta);
}

void ServerCommunication::connect(status sta)
{

}
