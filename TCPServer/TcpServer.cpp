#include "TcpServer.h"
#include"qdebug.h"
TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowTitle("TCP-�����");
	ui.port->setText("8899");//����Ĭ�ϵĶ˿�
	//���������ķ���������
	m_s = new QTcpServer(this);//ָ������������ʱ�Զ��ͷ��ڴ�

	//�ȴ��ͻ��˵����ӣ������µ�����
	connect(m_s, &QTcpServer::newConnection, this, [=]()
		{
			//��������ͨ�ŵ��׽��ֶ���
			m_tcp = m_s->nextPendingConnection();
			ui.record->append("�ɹ��Ϳͻ��˽����µ�����...");
			m_status->setPixmap(QPixmap(":/TcpServer/����.png").scaled(20, 20));
			//����׽����Ƿ���Խ�������
			connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
				{
					QByteArray data = m_tcp->readAll();//��ȡ����
					ui.record->append("�ͻ���˵��" + data);
				});
			connect(m_tcp, &QTcpSocket::disconnected, this, [=]()//�׽��ֶϿ�����
				{
					m_tcp->close();
					m_tcp->deleteLater();
					m_status->setPixmap(QPixmap(":/TcpServer/���߷���.png").scaled(20, 20));
					ui.record->append("��ͻ��˶Ͽ�����...");

				});
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
	//���ü���
	m_s->listen(QHostAddress::Any, port);
	//ui.setListen->setDisabled(true);//���ð�ť���ɵ��
	qDebug() << "qidong";
}

//���ͻ��˷�������
void TcpServer::sendmsg()
{
	QString msg = ui.msg->toPlainText();
	m_tcp->write(msg.toUtf8());
	ui.record->append("������˵��" + msg);

}

