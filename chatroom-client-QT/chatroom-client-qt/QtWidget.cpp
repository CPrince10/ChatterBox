#include "QtWidget.h"
#include"homepage.h"
#include "controller\controller.h"
#include <QString>
#include <QtWidgets\qmessagebox.h>
#include"netcommunication.h"
#include<ui_regist.h>
#include"regist.h"

QtWidget::QtWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/dialogBox1.png"));
    //设置名称
    this->setWindowTitle("欢迎使用本聊天系统!"); 
  
    connect(ui.pushBut_logOn,&QPushButton::clicked,this,[=](){
          //连接服务器
     netCommunication->connectToServer();

        ////判断是否在数据库中 是的话创建主页面，不是的话显示输入错误请注册或者重新输入
        //登陆界面
        //接收用户输入
        QString userNum=ui.lineEdit_accounts->text();
        QString userPassword = ui.lineEdit_passw->text();

        std::string userNum1 = userNum.toStdString();
        std::string userPassword1 = userPassword.toStdString();
        
       json myjson = {
       {"ID", stoi(userNum1)},
       {"password", userPassword1}
        };
             
        SendContext sendcontext(4);
        status sta=sendcontext.getResult(myjson);

        if (sta == 1)
        {
            homePage* page = new homePage;
            page->show();

            
           
            //以及打开后关闭登陆界面
            this->close();
            //获取一次用户信息
            RecvContext recvContext(2);
            recvContext.getResult();
        }
        else
        {
            QMessageBox::warning(nullptr, "警告", "账号或密码不匹配!");
        }

       
    });


    connect(ui.pushBut_logIn, &QPushButton::clicked, this, [=]() {

        Regist* regist = new Regist;
        regist->show();

        //以及打开后关闭登陆界面
        this->close();
        });


}
