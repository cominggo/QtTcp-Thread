#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_TcpServer.h"
#include<qtcpsocket.h>
#include"qlabel.h"
class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();
public slots:
	void setListen();
	void sendmsg();
	void disconnect();

private:
    Ui::TcpServerClass ui;
	QTcpSocket *m_tcp;
	QLabel *m_status;
};
