#pragma once
#pragma execution_character_set("utf-8")
#include<QThread>
#include"qtcpsocket.h"
class recvFile :
	public QThread
{
	Q_OBJECT
public:
	explicit recvFile(qintptr sock,QObject *parent = nullptr);//ͨ�����ε���ʽ�����뵽���߳���
protected:
	void run()override;
signals:
	void over();
private:
	QTcpSocket* m_tcp;
};

