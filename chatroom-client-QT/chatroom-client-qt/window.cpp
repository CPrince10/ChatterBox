#include "window.h"
#include"api.h"
#include"netcommunication.h"

Window::Window()
{
	netCommunication->setNetReCeiver(this);
}

void Window::recv(json content)
{

}

//提取json content里面内容
//void Window::recv(json content)
//{
//   
//
//}
//弹出窗口与服务器断开连接 回到登陆界面
//void Window::disconnect(status status)
//{
//	
//	
//
//}
//
