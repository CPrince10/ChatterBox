#include "message.h"
#include"../service/recvService.h"
#include "serverCommunication.h"
#include <fstream>
#include <chrono>
status Message::writeIntoChatRecord(json content)
{
	auto now = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
	int name = content["ID"];
	std::string content1 = content["content"];
	std::ofstream of;
	of.open(std::to_string(name) + ".txt", std::ios::out | std::ios::app);

	of << name << "  " << timestamp << std::endl;
	of << content1 << std::endl;
	of << std::endl;
	of.close();
	if (of.good()) {
		return 1;
	}
	else {
		return 0;
	}
}

json Message::readFromChatRecord(json content)
{
	int name = content["ID"];
	std::ifstream ifs;
	ifs.open(std::to_string(name) + ".txt", std::ios::in);
	json output;
	json records;

	std::string line;
	int count = 0;
	json a;
	records.push_back(a);
	while (std::getline(ifs, line)) {

		json record;
		json ti;

		// 从文件中读取人名和时间戳，存储到 JSON 对象中，使用 string 类型
		record["ID"] = line.substr(0, line.find("  "));
		ti["timestamp"] = line.substr(line.find("  ") + 2);

		// 从文件中读取聊天内容，存储到 JSON 对象中，使用 string 类型
		std::getline(ifs, line);
		record["content"] = line;

		// 将单条聊天记录添加到 JSON 数组中
		records.push_back(record);

		// 跳过空行
		std::getline(ifs, line);

		count++;
	}
	records[0]["ID"] = count;
	
	ifs.close();
	return records;
}

status Message::sendMessage(json content)
{
	std::string con;
	int id;

	content.at("ID").get_to(id);
	content.at("content").get_to(con);
	json myjson = {
		{"control",21 },
		{"ID",id },
		  {"content",con}
	};
	
	int a = serverCommunication->QSendToServer(myjson);
	if (a == -1) {
		return -1;
	}
	else {
		
		json b = serverCommunication->QRecvFromServer();
		a = b["status"];
		if (a == -1) {
			return -1;
		}
		else if (a == 0) {
			return 0;
		}
		else {
			writeIntoChatRecord(content);
			return 1;
		};

	}
	return 0;
}

void Message::recvMessage(json content)
{

	Message a;
	a.writeIntoChatRecord(content);
	RecvMessage::recvMessage(content);
}
