#include "people.h"
#include "ui_people.h"
#include"QtWidget.h"
#include <QApplication>
#include <QMessageBox>
#include "controller\controller.h"
#include<qjsonobject.h>

#include"netcommunication.h"
#include "homepage.h"
people::people(QWidget* parent) :
	QWidget(parent), Window(),
	ui(new Ui::people)
{
	ui->setupUi(this);

	//设置图标
	this->setWindowIcon(QIcon(":/image/person2.png"));
	//设置名称
	this->setWindowTitle("我的");

	////显示基本信息
	RecvContext rec(2);
	json json1 = rec.getResult();

	std::string name = json1["Username"];
	std::string birthday = json1["Birthday"];
	std::string sex = json1["Gender"];
	std::string cons = json1["Constellation"];
	std::string intr = json1["Introduction"];
	//2002-09-10

	QString qname = QString::fromStdString(name);
	QString qmessage = QString::fromStdString(birthday);
	QString qsex = QString::fromStdString(sex);
	QString qcons = QString::fromStdString(cons);
	QString qintr = QString::fromStdString(intr);

	ui->lineEdit_name->setText(qname);
	ui->lineEdit_birthday->setText(qmessage);
	ui->lineEdit_sex->setText(qsex);
	ui->lineEdit_cons->setText(qcons);
	ui->textEdit_intr->setText(qintr);

	////编辑基本信息
	connect(ui->pushBut_edit, &QPushButton::clicked, [=]()
		{
			// 获取用户输入，如果为空则设置默认值
			QString userInput_name = ui->lineEdit_name->text().isEmpty() ? "" : ui->lineEdit_name->text();
			if (userInput_name.isEmpty()) {
					QMessageBox::warning(this, "警告", "修改失败！姓名不能为空");
			}
			else {
				QString userInput_birthday = ui->lineEdit_birthday->text().isEmpty() ? "" : ui->lineEdit_birthday->text();
				QString userInput_sex = ui->lineEdit_sex->text().isEmpty() ? "" : ui->lineEdit_sex->text();
				QString userInput_cons = ui->lineEdit_cons->text().isEmpty() ? "" : ui->lineEdit_cons->text();
				QString userInput_intr = ui->textEdit_intr->toPlainText().isEmpty() ? QString() : ui->textEdit_intr->toPlainText().toUtf8();

				std::string name = userInput_name.toStdString();
				std::string birthday = userInput_birthday.toStdString();
				std::string sex = userInput_sex.toStdString();
				std::string cons = userInput_cons.toStdString();
				std::string intr = userInput_intr.toUtf8().constData();

				json jsonObject;
				jsonObject["name"] = name;
				jsonObject["birthday"] = birthday;
				jsonObject["gender"] = sex;
				jsonObject["constellation"] = cons;
				jsonObject["introduction"] = intr;

				SendContext sendcontext(6);

				status sta = sendcontext.getResult(jsonObject);
				if (sta != 1)
				{
					QMessageBox::warning(this, "警告", "修改失败！请检查填写格式");
				}
				else {
					QMessageBox::warning(this, "提示", "修改成功！");
				}
			}

		});
	if (this->close())
	{
		homePage* homepage = new homePage;
		homepage->show();

	}

}

////
void people::disconnect(status status)
{

	QMessageBox::warning(nullptr, "警告", "连接断开！", QMessageBox::Ok);

	closePage();

	QtWidget b;
	b.show();

}

////
void people::closePage()
{
	this->close();
}

people::~people()
{
	delete ui;
}
