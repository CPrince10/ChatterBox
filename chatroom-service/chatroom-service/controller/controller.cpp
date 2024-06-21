#include "controller.h"
#include "../service/service.h"



//构造对象
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

//调用对应接口的方法

json RecvContext::getResult(TransPara transPara) {

	return rs->communicate(transPara);
}

//构造对象

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

//调用对应接口的方法

status SendContext::getResult(TransPara transPara) {
	return as->communicate(transPara);
}
