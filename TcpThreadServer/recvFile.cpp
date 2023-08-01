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

	//��������
	connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
		{
			static int count = 0;//��¼��ȡ����
			static int total = 0;//�ļ��ܵĴ�С
			if (count == 0)
			{
				m_tcp->read((char*)&total, 4);//��ȡ��һ�ν��ܵ��źţ���Ϊ�ļ��ܴ�С
				qDebug() << "�ļ���С��" << total;
			}
			//��ȡʣ�µ�����
			QByteArray all = m_tcp->readAll();
			count += all.size();
			file->write(all);

			//�ж��Ƿ�ȫ����ȡ���,��Ϻ󣬹ر��׽��ֺ��ļ�
			if (count == total)
			{
				m_tcp->close();
				m_tcp->deleteLater();
				file->close();
				file->deleteLater();
				emit over();//�����źŸ����̣߳���ȡ���
			}
		});
	//�����¼�ѭ��,�����߳��ں�ִ̨�У��������˳�
	//������ӣ�������run֮��ͽ��������̡߳�
	exec();
}
