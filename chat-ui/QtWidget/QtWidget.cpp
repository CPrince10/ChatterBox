#include "QtWidget.h"
#include"homepage.h"
QtWidget::QtWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/dialogBox1.png"));
    //设置名称
    this->setWindowTitle("欢迎使用本聊天系统!");
    connect(ui.pushBut_logOn,&QPushButton::clicked,this,[=](){

        //**判断是否在数据库中是的话创建主页面，不是的话显示输入错误请注册或者重新输入
        homePage *page=new homePage;
        page->show();

        //以及打开后关闭登陆界面
        this->close();


    });




}
