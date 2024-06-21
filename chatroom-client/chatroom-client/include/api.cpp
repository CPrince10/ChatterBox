#include "api.h"
#include "../netcommunication.h"
#include "../object/serverCommunication.h"

NetCommunication* netCommunication = nullptr;
ServerCommunication* serverCommunication = nullptr;
std::string ip = "";
int port = 0;
std::string name = "";

void init()
{
	name = "";
	ip = "192.168.0.1";
	port = 8890;
	serverCommunication = ServerCommunication::getInstance();
	netCommunication = NetCommunication::getInstance();
}

