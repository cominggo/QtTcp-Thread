#include "TcpServer.h"
#include"qhostaddress.h"
TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowTitle("TCP-�ͻ���");
	ui.port->setText("8899");//����Ĭ�ϵĶ˿�
	ui.IP->setText("127.0.0.1");
	//���ӺͶϿ���ť״̬��ʾ�ǻ����
	ui.disconnect->setDisabled(true);
	//���������ķ���������
	m_tcp = new QTcpSocket(this);

	//��ȡ����
	connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
		{
			QByteArray data = m_tcp->readAll();//��ȡ����
			ui.record->append("������˵��" + data);
		});
	//ͨ������
	connect(m_tcp, &QTcpSocket::connected, this, [=]()
		{
			m_status->setPixmap(QPixmap(":/TcpServer/����.png").scaled(20, 20));
			ui.record->append("�Ѿ��ɹ����ӷ�����...");
			ui.connect->setDisabled(true);
			ui.disconnect->setDisabled(false);

		});
	//ͨ�ŶϿ�
	connect(m_tcp, &QTcpSocket::disconnected, this, [=]()//�׽��ֶϿ�����
		{

			m_status->setPixmap(QPixmap(":/TcpServer/���߷���.png").scaled(20, 20));
			ui.record->append("�������Ϳͻ����Ѿ��Ͽ�����...");
			ui.connect->setDisabled(false);
			ui.disconnect->setDisabled(true);

		});

	//���״̬��ͼ��
	m_status = new QLabel;
	m_status->setPixmap(QPixmap(":/TcpServer/���߷���.png").scaled(20, 20));
	ui.statusBar->addWidget(new QLabel("����״̬��"));
	ui.statusBar->addWidget(m_status);
}

TcpServer::~TcpServer()
{}

//����������
void TcpServer::setListen()
{
	unsigned short port = ui.port->text().toUShort();
	QString ip = ui.IP->text().toUtf8();
	//���ӷ�����
	m_tcp->connectToHost(QHostAddress(ip), port);
	qDebug() << "qidong";


}

//���ͻ��˷�������
void TcpServer::sendmsg()
{
	QString msg = ui.msg->toPlainText();
	m_tcp->write(msg.toUtf8());
	ui.record->append("�ͻ���˵��" + msg);

}

void TcpServer::disconnect()
{
	m_tcp->close();
	ui.connect->setDisabled(false);
	ui.disconnect->setDisabled(true);
}

