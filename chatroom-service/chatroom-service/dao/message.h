#ifndef MESSAGE_H__
#define MESSAGE_H__
#include"api.h"

class Message {

public:
	//���Ľӿڣ�����Ϣ�ӿڣ�����Ĳ�����json��ID��ͨ�������˵�ID����ȫ��map�в��ҵ����Ӧ��socket�����͸��Է�
	status sendMessage(TransPara transPara);
};


#endif // MESSAGE_H__