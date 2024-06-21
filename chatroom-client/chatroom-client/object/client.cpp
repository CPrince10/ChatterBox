#include "client.h"
#include"serverCommunication.h"

status Client::loginIn(json content)
{

	std::string pw;
	int id;
	content.at("ID").get_to(id);
	content.at("password").get_to(pw);
	json myjson = {
		{"control",24 },
	{"ID", id},
		{"password",pw }
	};
	//检查ID是否五位数,password是否5～10位
	if ((id < 10000 || id>99999) || (pw.length() > 10 || pw.length() < 5))
		return 0;
	//检查每个字符的合法性
	for (int i = 0; i < pw.length(); i++)
		if (pw[i] < 48 ||
			(pw[i] > 57 && pw[i] < 65) ||
			(pw[i] > 90 && pw[i] < 97) ||
			pw[i]>122)
			return 0;
	int b = serverCommunication->QSendToServer(myjson);
	if (b == -1) {
		return -1;
	}
	else {
		json rejson = serverCommunication->QRecvFromServer();
		rejson.at("status").get_to(b);
		if (b == 0) {
			return 0;
		}
		else {

			return 1;
		}

	}
	return 0;
}

status Client::signUp(json content)
{

	std::string pw, name;
	content.at("password").get_to(pw);
	content.at("name").get_to(name);
	json myjson = {
		{"control",24 },
		{"password",pw },
		  {"name",name}
	};
	//检查ID是否五位数,password是否5～10位,name是否2～10位
	if ((id < 10000 || id>99999) || (pw.length() > 10 || pw.length() < 5) || (name.length() > 10 || name.length() < 2))
		return 0;
	//检查每个字符的合法性
	for (int i = 0; i < pw.length(); i++)
		if (pw[i] < 48 ||
			(pw[i] > 57 && pw[i] < 65) ||
			(pw[i] > 90 && pw[i] < 97) ||
			pw[i]>122)
			return 0;
	for (int i = 0; i < name.length(); i++)
		if (name[i] < 48 ||
			(name[i] > 57 && name[i] < 65) ||
			(name[i] > 90 && name[i] < 97) ||
			name[i]>122)
			return 0;
	int b = serverCommunication->QSendToServer(myjson);
	if (b == -1) {
		return -1;
	}
	else {
		json rejson = serverCommunication->QRecvFromServer();
		rejson.at("status").get_to(b);
		if (b == 0) {
			return 0;
		}
		else {

			return 1;
		}
		return 0;
	}
}