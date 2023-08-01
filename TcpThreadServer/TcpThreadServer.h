#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_TcpThreadServer.h"
#include"qtcpserver.h"
#include"MyTcpServer.h"
class TcpThreadServer : public QMainWindow
{
    Q_OBJECT

public:
    TcpThreadServer(QWidget *parent = nullptr);
    ~TcpThreadServer();
signals:

public slots:
	void setListen();
	

private:
    Ui::TcpThreadServerClass ui;
	MyTcpServer *m_s;
};
