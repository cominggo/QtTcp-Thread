#include "MyTcpServer.h"

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
	emit newDescriptor(socketDescriptor);//��д��������������߳̿��Ե���tcp�׽���
}
