#include "controller.h"
#include "../service/service.h"



//�������
RecvContext::RecvContext(status sta) {
	switch (sta)
	{
		case 1: {
		rs = new GetFriendsList;
		break;
	}
	case 2: {
		rs =new GetProfile;
		break;
	}
	default:
		break;
	}
}

//���ö�Ӧ�ӿڵķ���

json RecvContext::getResult(TransPara transPara) {

	return rs->communicate(transPara);
}

//�������

SendContext::SendContext(status sta) {
	switch (sta)
	{
	case 1: {
			as =new  SendMess;
		break;
	}
	case 2: {
		as =new AddFriend;
		break;
	}
	case 3: {
		as =new DelFriend;
		break;
	}
	case 4: {
		as =new LoginIn;
		break;
	}
	case 5: {
		as =new SignUp;
		break;
	}
	case 6: {
		as =new UpdateProfile;
		break;
	}
	default:
		break;
	}
}

//���ö�Ӧ�ӿڵķ���

status SendContext::getResult(TransPara transPara) {
	return as->communicate(transPara);
}
