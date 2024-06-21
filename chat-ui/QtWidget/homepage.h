#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class homePage;
}

class homePage : public QWidget
{
    Q_OBJECT

public:
    explicit homePage(QWidget *parent = nullptr);
    ~homePage();



private:
    Ui::homePage *ui;
    QVector<bool> IsShowChat;

    QVector<bool> IsShowPeople;


};

#endif // HOMEPAGE_H
