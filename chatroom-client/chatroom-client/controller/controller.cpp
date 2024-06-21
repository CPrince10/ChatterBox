#include "controller.h"

//构造对象
RecvContext::RecvContext(status sta) {
	switch (sta)
	{
		/*	case 1: {
		RecvMessage recvMessage;
		rs = recvMessage;
		break;
		}*/
	case 1: {
		GetFriendsList getFriendsList;
		rs = getFriendsList;
		break;
	}
	case 2: {
		GetProfile getProfile;
		rs = getProfile;
		break;
	}
	default:
		break;
	}
}

//调用对应接口的方法
json RecvContext::getResult() {

	return rs.communicate();
}

//构造对象

SendContext::SendContext(status sta) {
	switch (sta)
	{
	case 1: {
		SendMessage sendMessage;
		as = sendMessage;
		break;
	}
	case 2: {
		AddFriend addFriend;
		as = addFriend;
		break;
	}
	case 3: {
		DelFriend delFriend;
		as = delFriend;
		break;
	}
	case 4: {
		LoginIn loginIn;
		as = loginIn;
		break;
	}
	case 5: {
		SignUp signUp;
		as = signUp;
		break;
	}
	case 6: {
		UpdateProfile updateProfile;
		as = updateProfile;
		break;
	}
	default:
		break;
	}
}

//调用对应接口的方法

status SendContext::getResult(json content) {
	return as.communicate(content);
}
