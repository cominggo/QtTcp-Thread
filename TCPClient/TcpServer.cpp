#include "TcpServer.h"
#include"qhostaddress.h"
TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowTitle("TCP-客户端");
	ui.port->setText("8899");//设置默认的端口
	ui.IP->setText("127.0.0.1");
	//连接和断开按钮状态显示是互斥的
	ui.disconnect->setDisabled(true);
	//创建监听的服务器对象
	m_tcp = new QTcpSocket(this);

	//读取数据
	connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
		{
			QByteArray data = m_tcp->readAll();//读取数据
			ui.record->append("服务器说：" + data);
		});
	//通信连接
	connect(m_tcp, &QTcpSocket::connected, this, [=]()
		{
			m_status->setPixmap(QPixmap(":/TcpServer/连接.png").scaled(20, 20));
			ui.record->append("已经成功连接服务器...");
			ui.connect->setDisabled(true);
			ui.disconnect->setDisabled(false);

		});
	//通信断开
	connect(m_tcp, &QTcpSocket::disconnected, this, [=]()//套接字断开连接
		{

			m_status->setPixmap(QPixmap(":/TcpServer/离线服务.png").scaled(20, 20));
			ui.record->append("服务器和客户端已经断开连接...");
			ui.connect->setDisabled(false);
			ui.disconnect->setDisabled(true);

		});

	//添加状态栏图标
	m_status = new QLabel;
	m_status->setPixmap(QPixmap(":/TcpServer/离线服务.png").scaled(20, 20));
	ui.statusBar->addWidget(new QLabel("连接状态："));
	ui.statusBar->addWidget(m_status);
}

TcpServer::~TcpServer()
{}

//启动服务器
void TcpServer::setListen()
{
	unsigned short port = ui.port->text().toUShort();
	QString ip = ui.IP->text().toUtf8();
	//连接服务器
	m_tcp->connectToHost(QHostAddress(ip), port);
	qDebug() << "qidong";


}

//给客户端发送数据
void TcpServer::sendmsg()
{
	QString msg = ui.msg->toPlainText();
	m_tcp->write(msg.toUtf8());
	ui.record->append("客户端说：" + msg);

}

void TcpServer::disconnect()
{
	m_tcp->close();
	ui.connect->setDisabled(false);
	ui.disconnect->setDisabled(true);
}

