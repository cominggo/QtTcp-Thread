#include "TcpThreadClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpThreadClient w;
    w.show();
    return a.exec();
}
