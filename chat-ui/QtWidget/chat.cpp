#include "chat.h"
#include "ui_chat.h"

chat::chat(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    myname=name;

}

//重写关闭事件
void chat::closeEvent(QCloseEvent*)
{
    //emit是触发信号
    emit this->closeWidget();
}

chat::~chat()
{
    delete ui;
}
