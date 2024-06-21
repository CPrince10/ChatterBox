#include "netcommunication.h"
#include <QTcpSocket>
#include <QWidget>
#include "QObject"
#include"object/serverCommunication.h"
#include"api.h"
#include "qlogging.h"
#include <QDebug>

NetCommunication* NetCommunication::net = nullptr;

NetCommunication::NetCommunication(QWidget* parent) :
	QWidget(parent)

{

	tcpSocket = Q_NULLPTR;

	// 分配控件指定父对象
	tcpSocket = new QTcpSocket(this);

	// 成功与服务器连接会触发connected信号
	connect(tcpSocket, &QTcpSocket::connected, this, &NetCommunication::SuccessfulConnection);

	// 当有消息发送过来，通信套接字会触发readyRead信号
	connect(tcpSocket, &QTcpSocket::readyRead, this, &NetCommunication::asynReceiveInformation);

	// 当服务器主动断开连接会触发disconnected信号
	connect(tcpSocket, &QTcpSocket::disconnected, this, &NetCommunication::DisConnect);

}

status NetCommunication::sendToServer(json content)
{
	std::string jsonString = content.dump();
	QString qString = QString::fromStdString(jsonString);
	// 发送信息
	qint64 Qsta;
	Qsta = tcpSocket->write(qString.toUtf8().data());
	long long sta = Qsta;
	return sta > 0 ? 1 : -1;
}

void NetCommunication::disconnectServer()
{
	// 主动与服务器断开连接
	tcpSocket->disconnectFromHost();
	tcpSocket->close();
}

void NetCommunication::SuccessfulConnection()
{
	serverCommunication->connect(1);
}

json NetCommunication::ReceiveInformation() {
	disconnect(tcpSocket, &QTcpSocket::readyRead, this, &NetCommunication::asynReceiveInformation);
	// 读取服务器发送过来的消息
	QByteArray content;
	if (tcpSocket->waitForReadyRead()) {
		// 读取数据
		content = tcpSocket->readAll();
		// 处理接收到的数据
	}
	std::string string = content.toStdString();
	json returnJson = json::parse(string);
	connect(tcpSocket, &QTcpSocket::readyRead, this, &NetCommunication::asynReceiveInformation);
	return returnJson;
}

void NetCommunication::DisConnect() {
	serverCommunication->disconnect(-1);
}

void NetCommunication::asynReceiveInformation()
{
	QByteArray content = tcpSocket->readAll();
	QBYTEARRAY_TO_JSON(content);
	serverCommunication->asynRecvFromServer(returnJson);
}

void NetCommunication::setNetReCeiver(NetReceiver* netReceiver)
{
	this->netReceiver = netReceiver;
}

NetReceiver* NetCommunication::getNetReceiver()
{
	return this->netReceiver;
}

void NetCommunication::connectToServer() {

	// 主动和服务器建立连接
	tcpSocket->connectToHost(QHostAddress(QString::fromStdString(ip)), port);
}

NetCommunication::~NetCommunication()
{
}

NetCommunication* NetCommunication::NetCommunication::getInstance()
{
	if (net == nullptr) {
		net = new NetCommunication(nullptr);
	}
	return net;
}

