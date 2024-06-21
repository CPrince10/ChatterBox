#ifndef REGIST_H
#define REGIST_H

#include <QWidget>

namespace Ui {
class Regist;
}

class Regist : public QWidget
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = nullptr);
    ~Regist();

private:
    Ui::Regist *ui;
};

#endif // REGIST_H
