#include "MyTcpServer.h"

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
	emit newDescriptor(socketDescriptor);//重写这个函数，让子线程可以调用tcp套接字
}
