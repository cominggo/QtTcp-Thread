#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_TcpThreadClient.h"

class TcpThreadClient : public QMainWindow
{
    Q_OBJECT

public:
    TcpThreadClient(QWidget *parent = nullptr);
    ~TcpThreadClient();
public slots:
	void connectServer();//连接服务器
	void chooseFile();//选择文件
	void sendFiler();//发送文件给子线程
signals:
	void startConnect(QString ip,unsigned short port);
	void sendData(QString path);

private:
    Ui::TcpThreadClientClass ui;
};
