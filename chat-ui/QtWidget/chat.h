#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent,QString name);
    ~chat();

    //重写关闭事件
    void closeEvent(QCloseEvent*);

signals:

    //关闭的信号
    void closeWidget();

private:
    Ui::chat *ui;
    QString myname;
};

#endif // CHAT_H
