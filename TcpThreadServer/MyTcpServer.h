#pragma once
#include <qtcpserver.h>
class MyTcpServer :
	public QTcpServer
{
	Q_OBJECT
protected:
	virtual void incomingConnection(qintptr socketDescriptor);
signals:
	void newDescriptor(qintptr sock);
};

