#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include"Window.h"
#include <QWidget>

extern std::map<int, std::string> idToName;
extern std::map<std::string, int> nameToId;
extern int Id_talk;
namespace Ui {
class homePage;
}

class homePage : public QWidget , public Window 
{
    Q_OBJECT

public:
    explicit homePage(QWidget *parent = nullptr);
    
    void disconnect(status status);
    ~homePage();

    ////弹出警告
    //void BounceOut();

    ////关闭页面
    void closePage();
    //获取id
    int  getID();

private:
    Ui::homePage *ui;
    QVector<bool> IsShowChat;

    QVector<bool> IsShowPeople;


};

#endif // HOMEPAGE_H
