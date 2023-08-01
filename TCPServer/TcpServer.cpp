#include "TcpServer.h"
#include"qdebug.h"
TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowTitle("TCP-服务端");
	ui.port->setText("8899");//设置默认的端口
	//创建监听的服务器对象
	m_s = new QTcpServer(this);//指定父对象，析构时自动释放内存

	//等待客户端的连接，创建新的连接
	connect(m_s, &QTcpServer::newConnection, this, [=]()
		{
			//设置用于通信的套接字对象
			m_tcp = m_s->nextPendingConnection();
			ui.record->append("成功和客户端建立新的连接...");
			m_status->setPixmap(QPixmap(":/TcpServer/连接.png").scaled(20, 20));
			//检测套接字是否可以接受数据
			connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
				{
					QByteArray data = m_tcp->readAll();//读取数据
					ui.record->append("客户端说：" + data);
				});
			connect(m_tcp, &QTcpSocket::disconnected, this, [=]()//套接字断开连接
				{
					m_tcp->close();
					m_tcp->deleteLater();
					m_status->setPixmap(QPixmap(":/TcpServer/离线服务.png").scaled(20, 20));
					ui.record->append("与客户端断开连接...");

				});
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
	//设置监听
	m_s->listen(QHostAddress::Any, port);
	//ui.setListen->setDisabled(true);//设置按钮不可点击
	qDebug() << "qidong";
}

//给客户端发送数据
void TcpServer::sendmsg()
{
	QString msg = ui.msg->toPlainText();
	m_tcp->write(msg.toUtf8());
	ui.record->append("服务器说：" + msg);

}

