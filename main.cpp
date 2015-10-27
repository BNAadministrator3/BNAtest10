#include "mainwindow.h"
#include <QApplication>



//注意主函数没有改变！
OperatingSystem operating_system;

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN32
    operating_system = os_win32;
#endif
#ifdef Q_OS_LINUX
    operating_system = linux;
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
