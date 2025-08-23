#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->port->setText("8899");
    setWindowTitle("TCP服务器");

    m_server = new QTcpServer(this);

    connect(m_server, &QTcpServer::newConnection, this, [=](){
         m_sock = m_server->nextPendingConnection();

         m_status->setPixmap(QPixmap(":/internet.png").scaled(20, 20));

        // 检测是否可以接受数据
        connect(m_sock, &QTcpSocket::readyRead, this, [=](){
            QByteArray data = m_sock->readAll();
            ui->record->append("客户端说: " + data);
        });

        connect(m_sock, &QTcpSocket::disconnected, this, [=](){
            m_sock->close();
            m_sock->deleteLater();
            m_status->setPixmap(QPixmap(":/no-wifi.png").scaled(20, 20));
         });
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

void MainWindow::on_beginListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_server->listen(QHostAddress::Any, port);
    ui->beginListen->setDisabled(true);
}


void MainWindow::on_sendMsg_clicked()
{
    QString msg = ui->msg->toPlainText();
    m_sock->write(msg.toUtf8());
    ui->record->append("服务端说:" + msg);
}

