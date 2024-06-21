#include "serverCommunication.h"

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
	return 1;
}

json ServerCommunication::QRecvFromServer()
{
	return {};
}

void ServerCommunication::asynRecvFromServer(json content)
{

}

void ServerCommunication::disconnect(status sta)
{

}

void ServerCommunication::connect(status sta)
{

}
