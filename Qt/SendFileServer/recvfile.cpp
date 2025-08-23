#include "recvfile.h"
#include <QFile>

RecvFile::RecvFile(QTcpSocket* sock, QObject *parent)
    : QThread{parent}
{
    m_sock = sock;
}

void RecvFile::run()
{
    QFile *file = new QFile("recv.txt");
    file->open(QFile::WriteOnly);

    connect(m_sock, &QTcpSocket::readyRead, this,[=](){
        static int count = 0;
        static int total = 0;
        if(count == 0)
        {
            m_sock->read((char*)&total, 4);
        }
        QByteArray all =  m_sock->readAll();
        count += all.size();
        file->write(all);

        if(count == total)
        {
            m_sock->close();
            m_sock->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }

    });
    // 进入底层事件循环
    exec();
}
