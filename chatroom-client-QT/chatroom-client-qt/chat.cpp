#include "chat.h"
#include "ui_chat.h"
#include <QApplication>
#include <QMessageBox>
#include"QtWidget.h"
#include <api.h>
#include <QString>
#include <string>
#include <iostream>
#include <QTextEdit>
#include "controller\controller.h"
#include"netcommunication.h"
#include"homepage.h"

chat::chat(QWidget* parent, QString name) :
	QWidget(parent), Window(),
	ui(new Ui::chat)
{
	ui->setupUi(this);
	myname = name;


	////用户点击发送按钮则获取输入框的内容
	connect(ui->pushButton, &QPushButton::clicked, [=]()
		{
			QString quserInput = ui->textEdit_input->toPlainText();
			std::string userInput = quserInput.toStdString();
			if (Id_talk == 0)
			{
				return;
			}
			json Input = {
					{"ID",Id_talk},
					{"content",userInput}
			};

			SendContext sendcontext(1);
			status sta = sendcontext.getResult(Input);

			if (sta != 1)
			{
				QMessageBox::warning(nullptr, "警告", "发送失败！");
			}
			else {
				QString mess = ui->textBro_receive->toPlainText();
				mess += "我:\n" + quserInput + "\n";
				ui->textBro_receive->setText(mess);
				QTextCursor cursor = ui->textBro_receive->textCursor();
				cursor.movePosition(QTextCursor::End);
				ui->textBro_receive->setTextCursor(cursor);
			}

		});

	connect(ui->pushButton_2, &QPushButton::clicked, [=]()
		{
			this->close();

		});



	connect(ui->pushButton_3, &QPushButton::clicked, [=]() {

		homePage homepage;
		int Id_Talk = homepage.getID();
		if (Id_Talk == 0)
		{
			return;
		}
		json jsonId = {
				{"ID",Id_Talk},
		};
		SendContext sendcontext(3);
		status sta = sendcontext.getResult(jsonId);
		if (sta != 1)
		{
			QMessageBox::warning(nullptr, "警告", "删除失败！");
		}
		else {
			this->close();
		}
		});

}

//重写关闭事件
void chat::closeEvent(QCloseEvent*)
{
	//emit是触发信号
	emit this->closeWidget();
}

////
void chat::disconnect(status status)
{

	QMessageBox::warning(nullptr, "警告", "连接断开！", QMessageBox::Ok);

	closePage();

	QtWidget b;
	b.show();

}

////
void chat::closePage()
{
	this->close();
}

void chat::recv(json content)
{
	int id = content["ID"];//传的是ID
	std::string name = idToName[id] + ":";
	std::string message = content["content"];

	QString qID = QString::fromStdString(name);
	QString qmessage = QString::fromStdString(message);
	QString mess = ui->textBro_receive->toPlainText();
	mess += qID + "\n" + qmessage + "\n";
	ui->textBro_receive->setText(mess);
	QTextCursor cursor = ui->textBro_receive->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui->textBro_receive->setTextCursor(cursor);
}

chat::~chat()
{
	delete ui;
}
