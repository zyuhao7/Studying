#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QMessageBox>
#include "recvfile.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"服务器主线程: "<<QThread::currentThread();

    m_server=  new QTcpServer(this);

    connect(m_server, &QTcpServer::newConnection, this,[=](){
        QTcpSocket *sock = m_server->nextPendingConnection();
        // 创建子线程
        RecvFile* subThread = new RecvFile(sock);
        subThread->start();

        connect(subThread, &RecvFile::over, this,[=](){
            subThread->quit();
            subThread->wait();
            subThread->deleteLater();
            QMessageBox::information(this, "文件接收", "文件接收完毕!");
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_server->listen(QHostAddress::Any, port);
}

