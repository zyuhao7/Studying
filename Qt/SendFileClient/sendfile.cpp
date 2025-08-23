#include "sendfile.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>

SendFile::SendFile(QObject *parent)
    : QObject{parent}
{}

void SendFile::connectServer(unsigned short port, QString ip)
{
    m_sock = new QTcpSocket;
    m_sock->connectToHost(QHostAddress(ip), port);

    connect(m_sock, &QTcpSocket::connected, this, &SendFile::connectOK);
    connect(m_sock, &QTcpSocket::disconnected, this, [=](){
        m_sock->close();
        m_sock->deleteLater();
        emit gameOver();
    });
}

void SendFile::sendFile(QString path)
{
    QFile file(path);
    QFileInfo info(path);
    int fileSiz = info.size();

    file.open(QFile::ReadOnly);
    while(!file.atEnd())
    {
        static int num = 0;
        if(num == 0)
        {
            m_sock->write((char*)&fileSiz, 4);
        }
        QByteArray line =  file.readLine();
        num += line.size();

        int percent = (num * 100) / fileSiz;
        emit currentPercent(percent);

        m_sock->write(line);

    }

}
