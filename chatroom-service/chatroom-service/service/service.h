#ifndef SERVICE_H__
#define SERVICE_H__
#include"api.h"

//service ���ļ�������������߼�������صĲ���

//�ͻ��˻�ȡ��Ϣ�Ĳ���������
class RecvSuper {
public:
	virtual json communicate(TransPara transPara)=0;
};

//�ͻ�����Ҫ������Ϣ�Ĳ���������
class SendSuper {
public:
	virtual status communicate(TransPara transPara)=0;
};

//============================================================
//��ȡ�����б�
class GetFriendsList : public RecvSuper {
public:
	json communicate(TransPara transPara);
};

//��ȡ��������
class GetProfile : public RecvSuper {
public:
	json communicate(TransPara transPara);
};


//=============================================================
//������Ϣ
class SendMess : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//�Ӻ���
class AddFriend : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//ɾ������
class DelFriend : public SendSuper {

public:
	status communicate(TransPara transPara);
};

//�����û�����
class UpdateProfile : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//��¼
class LoginIn : public SendSuper {
public:
	status communicate(TransPara transPara);
};

//ע��
class SignUp : public SendSuper {
public:
	status communicate(TransPara transPara);
};

#endif // SERVICE_H__