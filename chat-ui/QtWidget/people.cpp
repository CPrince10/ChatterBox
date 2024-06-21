#include "people.h"
#include "ui_people.h"

people::people(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::people)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/person2.png"));
    //设置名称
    this->setWindowTitle("我的");

}

//重写关闭事件
void people::closeEvent(QCloseEvent*)
{
    //emit是触发信号
    emit this->closeWidget();
}


people::~people()
{
    delete ui;
}
