#ifndef CONTROLLER_H__
#define CONTROLLER_H__
#include"api.h"
#include "../service/service.h"

//�������������Ӧ��������ɹ��죬����ö����getresult(json content);������ɲ���


//�ͻ�����Ҫ��ȡ���ݵĲ����������Ľӿڣ������߳����������ã����ض�Ӧ��json����
class RecvContext
{
	RecvSuper *rs=nullptr;
public:
	//�������
	RecvContext(status sta);

	//���ö�Ӧ�ӿڵķ���
	json getResult(TransPara transPara);
};


//�ͻ��˲���Ҫ��ȡ���ݵĲ����������Ľӿڣ������߳����������ã����ض�Ӧ��json����
class SendContext
{
	SendSuper *as=nullptr;
public:
	//�������
	SendContext(status sta);

	//���ö�Ӧ�ӿڵķ���
	status getResult(TransPara transPara);
};

#endif // CONTROLLER_H__