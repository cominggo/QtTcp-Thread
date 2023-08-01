#include "TcpThreadClient.h"
#include"qthread.h"
#include"sendFile.h"
#include"qmessagebox.h"
#include"qfiledialog.h"
TcpThreadClient::TcpThreadClient(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.ip->setText("127.0.0.1");
	ui.port->setText("8989");
	ui.progressBar->setRange(0, 100);//���ý�����
	ui.progressBar->setValue(0);
	
	//�����߳�,�������
	QThread *t = new QThread(this);
	sendFile *worker = new sendFile;
	worker->moveToThread(t);
	t->start();
	//���ӷ������������߳�ִ�����Ӳ���
	connect(this, &TcpThreadClient::startConnect, worker, &sendFile::connectServer);
	//�������̷߳��͵��ź�
	connect(worker, &sendFile::connectOk, this, [=]()
		{
			QMessageBox::information(this, "���ӷ�����", "�Ѿ��ɹ����ӷ�������");
		});
	//�Ͽ����ӣ��ͷ���Դ
	connect(worker, &sendFile::gameOver, this, [=]()
		{
			QMessageBox::information(this, "���ӷ�����", "��������Ͽ����ӣ�");
			t->quit();
			t->wait();
			worker->deleteLater();
			t->deleteLater();
		});
	//�����źŸ����̣߳����ļ�
	connect(this, &TcpThreadClient::sendData, worker, &sendFile::sendFiler);

	//���½�����
	connect(worker, &sendFile::curPercent, ui.progressBar, &QProgressBar::setValue);
}

TcpThreadClient::~TcpThreadClient()
{}
//���ӷ�����
void  TcpThreadClient::connectServer()
{
	QString ip = ui.ip->text();
	unsigned short port = ui.port->text().toUShort();
	emit startConnect(ip, port);

}
//ѡ���ļ�
void TcpThreadClient::chooseFile()
{
	QString path = QFileDialog::getOpenFileName();//��һ�������ļ�
	if (path.isEmpty())
	{
		QMessageBox::information(this, "���ļ�", "ѡ����ļ�����Ϊ�գ�");
		return;

	}
	ui.filePath->setText(path);
	qDebug() << "�ļ���ַ" << path;
}
//�����ļ������߳�
void TcpThreadClient::sendFiler()
{
	emit sendData(ui.filePath->text());//�����źŸ����߳̽����ļ�

}
