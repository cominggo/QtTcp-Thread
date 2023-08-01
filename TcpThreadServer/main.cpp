#include "TcpThreadServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpThreadServer w;
    w.show();
    return a.exec();
}
