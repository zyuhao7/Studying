#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include "sendfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"服务器主线程: "<<QThread::currentThread();

    ui->ip->setText("127.0.0.1");
    ui->port->setText("8899");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    QThread* t = new QThread;
    SendFile* worker = new SendFile;

    worker->moveToThread(t);
    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);
    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);

    connect(worker, &SendFile::connectOK, this, [=](){
        QMessageBox::information(this, "连接服务器", "已经成功连接到服务器..");
    });

    connect(worker, &SendFile::gameOver, this, [=](){
        t->quit();
        t->wait();
        worker->deleteLater();
        t->deleteLater();
    });

    connect(worker, &SendFile::currentPercent, ui->progressBar, &QProgressBar::setValue);

    t->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectSrv_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    emit startConnect(port, ip);
}


void MainWindow::on_chooseFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty())
    {
        QMessageBox::warning(this, "打开文件", "选择的文件路径不能为空!");
        return;
    }
    ui->filePath->setText(path);
}


void MainWindow::on_sendFile_clicked()
{
    emit sendFile(ui->filePath->text());
}

