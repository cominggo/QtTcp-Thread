#include "sendFile.h"
#include"qhostaddress.h"
#include"qfile.h"
#include"qfileinfo.h"
void sendFile::connectServer(QString ip, unsigned short port)
{
	m_tcp = new QTcpSocket(this);
	m_tcp->connectToHost(QHostAddress(ip), port);//���ӷ�����
	connect(m_tcp, &QTcpSocket::connected, this, &sendFile::connectOk);//���ӳɹ��������ź�
	connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
		{
			m_tcp->close();
			m_tcp->deleteLater();
			emit gameOver();
		});//�Ͽ����ӣ������ź�

}
void sendFile::sendFiler(QString path)
{
	QFile file(path);
	QFileInfo info(path);//�ļ������������ļ���С
	int fileSize = info.size();//��ȡ�ļ���С���ֽ�
	qDebug() << "�ļ���С��" << fileSize;
	file.open(QFile::ReadOnly);//�����ļ�ֻ��
	while (!file.atEnd())
	{
		static int num = 0;
		if (num == 0)
		{
			m_tcp->write((char*)&fileSize, 4);//���ȷ����ļ���С��������
		}
		QByteArray line = file.readLine();
		num += line.size();
		int percent = (num * 100) / fileSize;//�������
		emit curPercent(percent);//�����߳��źţ����½�����
		m_tcp->write(line);
	}
}


