#include "TcpThreadServer.h"
#include"qtcpsocket.h"
#include"recvFile.h"
#include"qmessagebox.h"

TcpThreadServer::TcpThreadServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	m_s = new MyTcpServer;
	ui.port->setText("8989");
	//通信连接标志
	connect(m_s, &MyTcpServer::newDescriptor, this, [=](qintptr sock)
		{
			//QTcpSocket *tcp = m_s->nextPendingConnection();
			//创建子线程，利用传参的方式
			recvFile *subThread = new recvFile(sock);//套接字传入子线程
			subThread->start();

			connect(subThread, &recvFile::over, this, [=]()
				{
					subThread->quit();
					subThread->wait();//退出线程
					subThread->deleteLater();//释放内存
					QMessageBox::information(this, "文件接受", "文件接受完毕！");
				});
		});
}

TcpThreadServer::~TcpThreadServer()
{}
//启动监听
void TcpThreadServer::setListen()
{
	unsigned short port = ui.port->text().toUShort();
	m_s->listen(QHostAddress::Any, port);

}