#include "homepage.h"
#include "ui_homepage.h"
#include<QIcon>
#include"chat.h"
#include"QMessageBox"
#include"chat.h"
#include"people.h"
#include "QtWidget.h"
#include "controller\controller.h"
#include<qjsonarray.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QDebug>
#include"netcommunication.h"
#include<map>
#include"api.h"
#include<vector>

std::map<int, std::string> idToName;
std::map<std::string, int> nameToId;

int Id_talk = 0;
homePage::homePage(QWidget *parent) :
    QWidget(parent),Window(),
    ui(new Ui::homePage)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/image/person1.png"));
    //设置名称
    this->setWindowTitle("主界面");

    ////获取一下数据库的人数,和联系人名称
    json myjson;
    RecvContext recv(1);

    myjson=recv.getResult();

    if (myjson[0]["ID"] == -1)
    {
        QMessageBox::warning(nullptr, "警告", "获取失败!");
    }
   
    //查询，添加联系人
    connect(ui->toolButton_search2, &QPushButton::clicked, this, [=]() {

        QString quserInput = ui->lineEdit_search->text();

        std::string quser = quserInput.toStdString();
        int ID = stoi(quser);
        json jsonObject =
        {
            {"ID" ,ID }
        };

        SendContext send(2);
        status quserinput = send.getResult(jsonObject);

        if (quserinput == 1)
        {
            //如果成功,弹出警告

            QMessageBox::information(this, "提示", "添加成功!");
            //刷新页面
            homePage* page = new homePage;
            page->show();
            //关闭当前页面
            this->close();
            return;
        }
        
        else
        {
            //如果失败,弹出警告
            QMessageBox::warning(this, "警告", "找不到该用户或已添加该用户!");
            return;
        }

        });

   /* {
        {
            {"ID", 5},
            { "name","" },
        },
        {
            {"ID",10000},
            {"name","name1"},
        },
        {
            {"ID",10001},
            {"name","name2"},
        },
    };*/
    ////***接收id
    ////接收人数和好友名称
    //获取的人数n

    

    int n = myjson[0]["ID"];
  
    for (int i = 1;i <= n;i++) {
        int ID = myjson[i]["ID"];
        std::string name = myjson[i]["Name"];
        idToName[ID] = name;
        nameToId[name] = ID;
    }
    //json jsonData = json::parse(myjson);

    QStringList listName;

    // 从 JSON 数据中提取 name 字段的值并存储到 QStringList 中（跳过第一个元素）
    for (int i = 1; i <=n; i++) {
        std::string name = myjson[i]["Name"];
        listName.push_back(QString::fromStdString(name));
    }
   

  

    QVector<QToolButton *> vector;

    //此处n代表人数
    for(int i=0;i<n;i++)
    {
        QToolButton *btn =new QToolButton(this);

       
        //设置网名
        btn->setText(QString("%1").arg(listName[i]));
        //btn->setText(QString(listName[i]));
        //设置窗口大小
        btn->setFixedSize(270, 60);
       

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
            //创建出来第n个chat页面
            chat *chatWithSb=new chat(0,vector[i]->text());
            //根据聊天的人不同修改名称
            chatWithSb->setWindowTitle(vector[i]->text());
            chatWithSb->show();

            Id_talk = myjson[i+1]["ID"];
            IsShowChat[i]=true;

            this->close();

            

            //关闭时将对应的IsShowChat变为false
            connect(chatWithSb,&chat::closeWidget,this,[=]()
                   {
                        IsShowChat[i]=false;
                        homePage* homepage = new homePage;
                        homepage->show();
                    });

        });
    }

    //对IsShowPeople进行初始化，代表我的页面未打开
    connect(ui->toolBut_mine,&QToolButton::clicked,this,[=]() {

        
        people *mypeople=new people;
        //显示我的页面
        mypeople->show();

        this->close();

       
        });

   


    }

////
void homePage::disconnect(status status)
{

    QMessageBox::warning(nullptr, "警告", "连接断开！", QMessageBox::Ok);

    closePage();

    QtWidget b;
    b.show();

}

int  homePage::getID()
{
    return Id_talk;
}

////
void homePage::closePage()
{
    this->close();
}

homePage::~homePage()
{
    delete ui;
}
