#include "api.h"
#include "../netcommunication.h"
#include "../object/serverCommunication.h"

NetCommunication* netCommunication = nullptr;
ServerCommunication* serverCommunication = nullptr;
std::string ip = "8.130.128.143";
int port = 1234;
std::string name = "";

void init()
{
	name = "";
	ip = "8.130.128.143";
	port = 1234;
	serverCommunication = ServerCommunication::getInstance();
	netCommunication = NetCommunication::getInstance();
}

