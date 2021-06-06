#include "QtWidgetsApplication1_HelloWorld.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1_HelloWorld w;
    w.show();
    return a.exec();
}
