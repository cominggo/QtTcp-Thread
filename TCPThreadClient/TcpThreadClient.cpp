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
	ui.progressBar->setRange(0, 100);//设置进度条
	ui.progressBar->setValue(0);
	
	//创建线程,任务对象
	QThread *t = new QThread(this);
	sendFile *worker = new sendFile;
	worker->moveToThread(t);
	t->start();
	//连接服务器，让子线程执行连接操作
	connect(this, &TcpThreadClient::startConnect, worker, &sendFile::connectServer);
	//处理子线程发送的信号
	connect(worker, &sendFile::connectOk, this, [=]()
		{
			QMessageBox::information(this, "连接服务器", "已经成功连接服务器！");
		});
	//断开连接，释放资源
	connect(worker, &sendFile::gameOver, this, [=]()
		{
			QMessageBox::information(this, "连接服务器", "与服务器断开连接！");
			t->quit();
			t->wait();
			worker->deleteLater();
			t->deleteLater();
		});
	//发送信号给子线程，打开文件
	connect(this, &TcpThreadClient::sendData, worker, &sendFile::sendFiler);

	//更新进度条
	connect(worker, &sendFile::curPercent, ui.progressBar, &QProgressBar::setValue);
}

TcpThreadClient::~TcpThreadClient()
{}
//连接服务器
void  TcpThreadClient::connectServer()
{
	QString ip = ui.ip->text();
	unsigned short port = ui.port->text().toUShort();
	emit startConnect(ip, port);

}
//选择文件
void TcpThreadClient::chooseFile()
{
	QString path = QFileDialog::getOpenFileName();//打开一个磁盘文件
	if (path.isEmpty())
	{
		QMessageBox::information(this, "打开文件", "选择的文件不能为空！");
		return;

	}
	ui.filePath->setText(path);
	qDebug() << "文件地址" << path;
}
//发送文件给子线程
void TcpThreadClient::sendFiler()
{
	emit sendData(ui.filePath->text());//发送信号给子线程接受文件

}
