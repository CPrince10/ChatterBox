#ifndef PEOPLE_H
#define PEOPLE_H

#include <QWidget>

namespace Ui {
class people;
}

class people : public QWidget
{
    Q_OBJECT

public:
    explicit people(QWidget *parent = nullptr);
    ~people();

    //重写关闭事件
    void closeEvent(QCloseEvent*);

signals:

    //关闭的信号
    void closeWidget();

private:
    Ui::people *ui;
};

#endif // PEOPLE_H
