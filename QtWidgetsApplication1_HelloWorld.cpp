#include "QtWidgetsApplication1_HelloWorld.h"

//解决中文乱码问题
#ifdef WIN32

#pragma  execution_character_set("utf-8")

#endif

QtWidgetsApplication1_HelloWorld::QtWidgetsApplication1_HelloWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //信号与槽
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(showText()));
}

//槽函数
void QtWidgetsApplication1_HelloWorld::showText()
{
    QString s;
    s.append("穷睇眄于中天，极娱游于暇日。\n");
    s.append("天高地迥，觉宇宙之无穷；\n");
    s.append("兴尽悲来，识盈虚之有数。\n");
    s.append("望长安于日下，目吴会于云间。\n");
    s.append("地势极而南溟深，天柱高而北辰远。\n");
    s.append("关山难越，谁悲失路之人？\n");
    s.append("萍水相逢，尽是他乡之客。\n");

    ui.textEdit->setText(s);
}