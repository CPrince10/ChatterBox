#include "sendService.h"
#include "../object/user.h"
#include "../object/client.h"
#include "../object/message.h"
#include <regex>
#include <string>

status SendMessage::communicate(json content) {
	Message mess;
	return mess.sendMessage(content);
}


status AddFriend::communicate(json content)
{
	int id = content["ID"];
	if (id<10000||id>99999) return 0;
	User user;
	return user.addFriend(content);
}

status DelFriend::communicate(json content)
{
	int id = content["ID"];
	if (id < 10000 || id>99999) return 0;
	User user;
	return user.delFriend(content);
}

status UpdateProfile::communicate(json content)
{
	//判断生日日期格式
	//格式为yyyy-mm-dd,且在1900至2100范围之间，且月份<=12,日<=31
	std::string dateStr = content["birthday"];
	if (dateStr != "") {
		std::regex pattern(R"(^(19\d{2}|20[01]\d|2100)-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
		if (std::regex_match(dateStr, pattern)) {
			int year = std::stoi(dateStr.substr(0, 4));
			if (year >= 1900 && year <= 2100) {

			}
			else return 0;
		}
		else return 0;
	}

	//判断性别check in{男，女}
	std::string gender = content["gender"];
	if (gender != "") {
		std::regex genderRegex("^(男|女)$", std::regex_constants::icase);
		if (!std::regex_match(gender, genderRegex)) return 0;
	}
	User user;
	return user.updateProfile(content);
}

status LoginIn::communicate(json content)
{
	Client client;

	return client.loginIn(content);
}

int SignUp::communicate(json content)
{
	Client client;
	return client.signUp(content);
}
