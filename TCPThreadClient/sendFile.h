#pragma once
#pragma execution_character_set("utf-8")
#include<QObject>
#include"qtcpsocket.h"
class sendFile :
	public QObject
{
	Q_OBJECT
public :
	void connectServer(QString ip, unsigned short port);//���ӷ�����
	void sendFiler(QString path);//�����ļ���������
signals:
	void connectOk();//���ӳɹ��ź�
	void gameOver();//�Ͽ�����
	void curPercent(int);//��ǰ������
private:
	QTcpSocket *m_tcp;
};

