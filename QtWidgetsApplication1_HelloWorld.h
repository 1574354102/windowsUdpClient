#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1_HelloWorld.h"

class QtWidgetsApplication1_HelloWorld : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1_HelloWorld(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1_HelloWorldClass ui;

private slots:
    void showText();
};
