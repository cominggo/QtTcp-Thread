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
	//ͨ�����ӱ�־
	connect(m_s, &MyTcpServer::newDescriptor, this, [=](qintptr sock)
		{
			//QTcpSocket *tcp = m_s->nextPendingConnection();
			//�������̣߳����ô��εķ�ʽ
			recvFile *subThread = new recvFile(sock);//�׽��ִ������߳�
			subThread->start();

			connect(subThread, &recvFile::over, this, [=]()
				{
					subThread->quit();
					subThread->wait();//�˳��߳�
					subThread->deleteLater();//�ͷ��ڴ�
					QMessageBox::information(this, "�ļ�����", "�ļ�������ϣ�");
				});
		});
}

TcpThreadServer::~TcpThreadServer()
{}
//��������
void TcpThreadServer::setListen()
{
	unsigned short port = ui.port->text().toUShort();
	m_s->listen(QHostAddress::Any, port);

}