#include "QtWidget.h"
#include <QtWidgets/QApplication>
#include"homepage.h"
#include "chat.h"
#include"people.h"
#include "api.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();
    QtWidget b;
    b.show();

    return a.exec();
}
