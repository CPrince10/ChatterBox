#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidget.h"

class QtWidget : public QWidget
{
    Q_OBJECT

public:
    QtWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetClass ui;
};
