#ifndef PEOPLE_H
#define PEOPLE_H

#include <QWidget>
#include"Window.h"
namespace Ui {
class people;
}

class people : public QWidget,public Window
{
    Q_OBJECT

public:
    explicit people(QWidget *parent = nullptr);
    ~people();

  
    ////弹出警告
    void disconnect(status status);
    ////关闭页面
    void closePage();

signals:

    //关闭的信号
    void closeWidget();

private:
    Ui::people *ui;
};

#endif // PEOPLE_H
