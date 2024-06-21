#ifndef NETCOMMUNICATION_H
#define NETCOMMUNICATION_H
#include <QWidget>
#include "api.h"
// 通信套接字
#include <QTcpSocket>
#include "controller/controller.h"
// qt 支持显示中文
#pragma execution_character_set("utf-8")
namespace Ui {
	class NetCommunication;
}

class NetCommunication : public QWidget
{
	Q_OBJECT
private:
	static NetCommunication *net;
	NetReceiver* netReceiver;
public:
	explicit NetCommunication(QWidget* parent);
	~NetCommunication();

	static NetCommunication* getInstance();
	
	void setNetReCeiver(NetReceiver* netReceiver);
	NetReceiver* getNetReceiver();

	void connectToServer();
	status sendToServer(json content);
	void disconnectServer();
	void SuccessfulConnection();
	json ReceiveInformation();
	void DisConnect();
	void asynReceiveInformation();

signals:

	//关闭的信号
	void closeWidget();

private:
	Ui::NetCommunication* ui;
	//QString myname;
	QTcpSocket* tcpSocket;
};


#endif // NETCOMMUNICATION_H

