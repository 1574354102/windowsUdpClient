#include "QtWidgetsApplication1_HelloWorld.h"

//���������������
#ifdef WIN32

#pragma  execution_character_set("utf-8")

#endif

QtWidgetsApplication1_HelloWorld::QtWidgetsApplication1_HelloWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //�ź����
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(showText()));
}

//�ۺ���
void QtWidgetsApplication1_HelloWorld::showText()
{
    QString s;
    s.append("�����������죬��������Ͼ�ա�\n");
    s.append("��ߵ��ģ�������֮���\n");
    s.append("�˾�������ʶӯ��֮������\n");
    s.append("�����������£�Ŀ������Ƽ䡣\n");
    s.append("���Ƽ�������������߶�����Զ��\n");
    s.append("��ɽ��Խ��˭��ʧ·֮�ˣ�\n");
    s.append("Ƽˮ��꣬��������֮�͡�\n");

    ui.textEdit->setText(s);
}