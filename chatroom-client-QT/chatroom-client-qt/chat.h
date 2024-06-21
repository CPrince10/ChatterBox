#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include"Window.h"
namespace Ui {
class chat;
}

class chat : public QWidget ,public Window
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent,QString name);
    ~chat();

    //重写关闭事件
    void closeEvent(QCloseEvent*);

    ////弹出警告
    void disconnect(status status);

    ////关闭页面
    void closePage();
    
    ////接收消息
    void recv(json content);

signals:

    //关闭的信号
    void closeWidget();


private:
    Ui::chat *ui;
    QString myname;
};

#endif // CHAT_H
