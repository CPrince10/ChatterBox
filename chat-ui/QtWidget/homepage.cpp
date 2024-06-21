#include "homepage.h"
#include "ui_homepage.h"
#include<QIcon>
#include"chat.h"
#include"QMessageBox"
#include"chat.h"
#include"people.h"
homePage::homePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::homePage)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/person1.png"));
    //设置名称
    this->setWindowTitle("主界面");

    //**获取一下数据库的人数,和联系人名称
    //获取的人数n
    int n=5;
    //获取的联系人名称数组
    QStringList listName;
    //**把联系人名称放进去
    listName<<"张三"<<"李四"<<"王五"<<"赵六"<<"七七";

    QVector<QToolButton *> vector;
    //此处n代表人数
    for(int i=0;i<n;i++)
    {
        QToolButton *btn =new QToolButton(this);

        //加载图片
        //btn->setIcon(QPixmap(":/image/dialogBox2.png"));
        //设置图片大小
        //btn->setIconSize(QPixmap(":/image/dialogBox2.png").size());
        //设置网名
        btn->setText(QString("%1").arg(listName[i]));
        //btn->setText(QString(listName[i]));
        //设置窗口大小
        btn->setFixedSize(270, 60);
        //和图片一起显示
        //btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        //设置放在窗口中
        ui->Layout_friend->addWidget(btn);
        vector.push_back(btn);

        //对IsShowChat进行初始化，代表聊天页面未打开
        IsShowChat.push_back(false);


    }

    //点击图标显示聊天框
    for(int i=0;i<n;i++)
    {
        connect(vector[i],&QToolButton::clicked,[=]()
        {
            //判断页面是否打开
            if(IsShowChat[i])
            {
                //如果打开,弹出警告
                QMessageBox::warning(this,"警告!","该聊天框已被打开!");
                return;

            }
            //创建出来n个chat页面
            chat *chatWithSb=new chat(0,vector[i]->text());
            //根据聊天的人不同修改名称
            chatWithSb->setWindowTitle(vector[i]->text());
            chatWithSb->show();
            IsShowChat[i]=true;

            //关闭时将对应的IsShowChat变为false
            connect(chatWithSb,&chat::closeWidget,this,[=]()
                   {
                        IsShowChat[i]=false;
                    });

        });
    }

    //对IsShowPeople进行初始化，代表我的页面未打开
    //IsShowPeople.push_back(false);
    connect(ui->toolBut_mine,&QToolButton::clicked,this,[=]() {

        //判断页面是否打开
        //if(IsShowPeople)
        //{
            //如果打开,弹出警告
            //QMessageBox::warning(this,"警告!","该页面已被打开!");
            //return;

        //}
        people *mypeople=new people;
        //显示我的页面
        mypeople->show();
        //关闭时将对应的IsShow变为false
        //connect(ui->toolBut_mine,&QToolButton::close,this,[=]()
                //{
                    //IsShowPeople.push_back(false);
               //});

        });





    }



homePage::~homePage()
{
    delete ui;
}
