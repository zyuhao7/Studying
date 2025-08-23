#include "mainwindow.h"
#include "qtcpserver.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TCP客户端");

    ui->disconnect->setDisabled(true);

    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");

    m_sock = new QTcpSocket;

    connect(m_sock, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = m_sock->readAll();
        ui->record->append("服务器说: " + data);
    });

    connect(m_sock, &QTcpSocket::disconnected, this, [=](){
        m_sock->close();
        m_sock->deleteLater();
        m_status->setPixmap(QPixmap(":/no-wifi.png").scaled(20, 20));
        ui->record->append("与服务器断开连接成功 ..");
        ui->connect->setEnabled(true);
        ui->disconnect->setDisabled(true);
    });

    connect(m_sock, &QTcpSocket::connected, this, [=](){
        m_status->setPixmap(QPixmap(":/internet.png").scaled(20, 20));
        ui->record->append("已经成功连接到服务器..");
        ui->connect->setDisabled(true);
        ui->disconnect->setEnabled(true);
    });

    // 状态栏
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/no-wifi.png").scaled(20, 20));

    ui->statusbar->addWidget(new QLabel("连接状态: "));
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendMsg_clicked()
{
    QString msg = ui->msg->toPlainText();
    m_sock->write(msg.toUtf8());
    ui->record->append("客户端说:" + msg);
}


void MainWindow::on_connect_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_sock->connectToHost(QHostAddress(ip), port);
}


void MainWindow::on_disconnect_clicked()
{
    m_sock->close();
    ui->connect->setEnabled(true);
    ui->disconnect->setDisabled(true);
}

