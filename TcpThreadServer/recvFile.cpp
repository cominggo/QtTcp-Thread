#include "recvFile.h"
#include"qfile.h"

recvFile::recvFile(qintptr sock,QObject *parent) :QThread(parent)
{
	m_tcp = new QTcpSocket(this);
	m_tcp->setSocketDescriptor(sock);
}


void recvFile::run()
{
	
	QFile* file = new QFile("recv.txt");
	file->open(QFile::WriteOnly);

	//接受数据
	connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
		{
			static int count = 0;//记录读取进度
			static int total = 0;//文件总的大小
			if (count == 0)
			{
				m_tcp->read((char*)&total, 4);//读取第一次接受的信号，即为文件总大小
				qDebug() << "文件大小；" << total;
			}
			//读取剩下的数据
			QByteArray all = m_tcp->readAll();
			count += all.size();
			file->write(all);

			//判断是否全部读取完毕,完毕后，关闭套接字和文件
			if (count == total)
			{
				m_tcp->close();
				m_tcp->deleteLater();
				file->close();
				file->deleteLater();
				emit over();//发送信号给主线程，读取完毕
			}
		});
	//进入事件循环,让子线程在后台执行，并不是退出
	//如果不加，进行完run之后就结束了子线程。
	exec();
}
