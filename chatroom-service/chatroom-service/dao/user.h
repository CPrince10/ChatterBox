#ifndef USER_H__
#define USER_H__
#include"api.h"

class User {
public:
	//�Ӻ��� ����id��json��json ��������Ҫ�ӵĺ���ID�����سɹ����
	status addFriend(TransPara transPara);
	//ɾ���� ͬ��
	status delFriend(TransPara transPara);
	//��ȡ�����б� ��json���غ����б� ����id
	json getFriendsList(TransPara transPara);

	//�����û����� ����id��json��json ��������Ҫ���ĵ��û����ϣ����سɹ���� 
	status updateProfile(TransPara transPara);
	//��ȡ�û�����	��json�����û����� ��ȡ���û������Ժ󣬰�ȫ�ֱ����е�name�ĳ�json����ֵ�е����� ����id
	json getProfile(TransPara transPara);
};


#endif // USER_H__