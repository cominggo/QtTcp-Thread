#pragma once
#pragma execution_character_set("utf-8")
#include<QObject>
#include"qtcpsocket.h"
class sendFile :
	public QObject
{
	Q_OBJECT
public :
	void connectServer(QString ip, unsigned short port);//连接服务器
	void sendFiler(QString path);//发送文件给服务器
signals:
	void connectOk();//连接成功信号
	void gameOver();//断开连接
	void curPercent(int);//当前进度条
private:
	QTcpSocket *m_tcp;
};

