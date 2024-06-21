#include "regist.h"
#include "ui_regist.h"
#include "QtWidget.h"
#include "controller\controller.h"
#include <QString>
#include <QtWidgets\qmessagebox.h>
#include"netcommunication.h"

Regist::Regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/dialogBox1.png"));
    //设置名称
    this->setWindowTitle("欢迎使用本聊天系统!");
    connect(ui->pushBut_logIn, &QPushButton::clicked, this, [=]() {

          //连接服务器
     netCommunication->connectToServer();
       
        //接收用户输入
        QString userName = ui->lineEdit_accounts->text();
        QString userPassword = ui->lineEdit_passw->text();

        std::string userName1 = userName.toStdString();
        std::string userPassword1 = userPassword.toStdString();


        json myjson = {
        {"name", userName1},
        {"password", userPassword1},
        };

        SendContext sendcontext(5);
        status sta = sendcontext.getResult(myjson);

        if (sta != -1&&sta!=0)
        {
            QtWidget* page = new QtWidget;
            page->show();

            //Window * homepage=new HomepageWindow;
            //netCommunication->setNetReCeiver(homepage);
            std::string notes = "注册成功! ID是" + std::to_string(sta);
            QString note = QString::fromStdString(notes);
            QMessageBox::information(this, "提示",note,QMessageBox::Ok);
            //以及打开后关闭注册界面
            this->close();
           
        }
        else
        {
            QMessageBox::warning(nullptr, "警告", "注册失败!");
        }
        });




}

Regist::~Regist()
{
    delete ui;
}
