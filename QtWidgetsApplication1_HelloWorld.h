#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1_HelloWorld.h"
#include "HPSocket.h"
#include "CListenerImp.h"
#include "QTimer"

class QtWidgetsApplication1_HelloWorld : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1_HelloWorld(QWidget *parent = Q_NULLPTR);
    ~QtWidgetsApplication1_HelloWorld();

private:
    Ui::QtWidgetsApplication1_HelloWorldClass ui;
    CListenerImp listener;
    CUdpNodePtr udpNodePtr;
    QTimer* timer;

private slots:
    void sendText();
    void showText(bool isNotSelfMsg, QString msg);
    void sendHeartBeatPacket();
    void showOnlineInfo(int onlineNum, QString usersName);

protected:
    bool eventFilter(QObject* obj, QEvent* e);
};
