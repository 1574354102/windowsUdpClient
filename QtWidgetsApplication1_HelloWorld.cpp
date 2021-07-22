#include "QtWidgetsApplication1_HelloWorld.h"
#include "QKeyEvent"
#include <cstring>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;
//解决中文乱码问题
#ifdef WIN32

#pragma  execution_character_set("utf-8")

#endif

constexpr auto PublicServerIP = "39.105.86.70";
constexpr auto ServerPort = 3080;
constexpr auto UserNameLen = 20;

QtWidgetsApplication1_HelloWorld::~QtWidgetsApplication1_HelloWorld()
{
    udpNodePtr->Stop();
}

QtWidgetsApplication1_HelloWorld::QtWidgetsApplication1_HelloWorld(QWidget *parent)
    : QMainWindow(parent), udpNodePtr(&listener), timer(new QTimer(this))
{
    ui.setupUi(this);

    udpNodePtr->Start();
    timer->start(1000);

    ui.editInput->installEventFilter(this);

    connect(ui.buttonSend, SIGNAL(clicked()), this, SLOT(sendText()));
    connect(&listener.message, &Message::SigReceive, this, &QtWidgetsApplication1_HelloWorld::showText);
    connect(&listener.message, &Message::SigReceiveOnlineInfo, this, &QtWidgetsApplication1_HelloWorld::showOnlineInfo);
    connect(timer, &QTimer::timeout, this, &QtWidgetsApplication1_HelloWorld::sendHeartBeatPacket);
}

void QtWidgetsApplication1_HelloWorld::sendText()
{
    if (ui.editInput->toPlainText().isEmpty())
    {
        return;
    }
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);

    writer.StartObject();

    writer.Key("msgType");
    writer.Int(0);

    writer.Key("msgInfo");
    writer.String(ui.editInput->toPlainText().toStdString().c_str());

    writer.EndObject();
    
    udpNodePtr->Send(LPCTSTR(PublicServerIP), ServerPort, (BYTE*)buf.GetString(), buf.GetSize());
    
    ui.editInput->clear();
}

void QtWidgetsApplication1_HelloWorld::sendHeartBeatPacket()
{
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);

    writer.StartObject();

    writer.Key("msgType");
    writer.Int(1);
    
    writer.Key("userName");
    writer.String(ui.editUserName->text().toStdString().c_str());

    writer.EndObject();
    
    udpNodePtr->Send(LPCTSTR(PublicServerIP), ServerPort, (BYTE*)buf.GetString(), buf.GetSize());
}

void QtWidgetsApplication1_HelloWorld::showOnlineInfo(int onlineNum, QString usersName)
{
    ui.textOnlineNumber->setText("在线人数:" + QString::number(onlineNum));
    ui.textUserOnline->setText(usersName);
}

void QtWidgetsApplication1_HelloWorld::showText(bool isNotSelfMsg, QString msg)
{
    QString outInfo;
    outInfo.append(msg);
    outInfo.append("\n\n");

    QTextCursor outputCursor(ui.textOutput->textCursor());
    QTextBlockFormat blockFormat;
    QTextCharFormat charFormat;
    
    if (!isNotSelfMsg)
    {
        blockFormat.setAlignment(Qt::AlignRight);
        charFormat.setBackground(Qt::green);
    }
    else
    {
        blockFormat.setAlignment(Qt::AlignLeft);
        charFormat.setBackground(Qt::white);
    }
    outputCursor.setBlockFormat(blockFormat);
    outputCursor.mergeCharFormat(charFormat);
    ui.textOutput->setTextCursor(outputCursor);
    ui.textOutput->append(outInfo);
}

bool QtWidgetsApplication1_HelloWorld::eventFilter(QObject* obj, QEvent* e)
{
    if (obj == ui.editInput)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent* event = dynamic_cast<QKeyEvent*>(e);
            if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
            {
                if (ui.editInput->toPlainText().isEmpty())
                {
                    ui.editInput->append("\n");
                }
                else
                {
                    ui.editInput->append("");
                }
                return true;
            }
            else if (event->key() == Qt::Key_Return)
            {
                sendText();
                return true;
            }
        }
    }
    return false;
}