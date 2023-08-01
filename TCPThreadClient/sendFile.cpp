#include "sendFile.h"
#include"qhostaddress.h"
#include"qfile.h"
#include"qfileinfo.h"
void sendFile::connectServer(QString ip, unsigned short port)
{
	m_tcp = new QTcpSocket(this);
	m_tcp->connectToHost(QHostAddress(ip), port);//连接服务器
	connect(m_tcp, &QTcpSocket::connected, this, &sendFile::connectOk);//连接成功，发送信号
	connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
		{
			m_tcp->close();
			m_tcp->deleteLater();
			emit gameOver();
		});//断开连接，发送信号

}
void sendFile::sendFiler(QString path)
{
	QFile file(path);
	QFileInfo info(path);//文件操作，计算文件大小
	int fileSize = info.size();//读取文件大小，字节
	qDebug() << "文件大小：" << fileSize;
	file.open(QFile::ReadOnly);//设置文件只读
	while (!file.atEnd())
	{
		static int num = 0;
		if (num == 0)
		{
			m_tcp->write((char*)&fileSize, 4);//首先发送文件大小个服务器
		}
		QByteArray line = file.readLine();
		num += line.size();
		int percent = (num * 100) / fileSize;//计算进度
		emit curPercent(percent);//给主线程信号，更新进度条
		m_tcp->write(line);
	}
}


