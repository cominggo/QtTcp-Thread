#include "TcpServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer w;
    w.show();
    return a.exec();
}
