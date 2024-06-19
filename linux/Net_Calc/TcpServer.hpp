#include "Protolcol.hpp"
#include "Socket.hpp"
#include <iostream>
#include <pthread.h>
#include <functional>

using func_t = std::function<void(Net_work::Socket *sockp)>;

class TcpServer;

class ThreadData
{
public:
    ThreadData(TcpServer *tcp_this, Net_work::Socket *sockp)
        : this_(tcp_this), sockp_(sockp)
    {
    }

public:
    TcpServer *this_;
    Net_work::Socket *sockp_;
};

class TcpServer
{
public:
    TcpServer(uint16_t port, func_t handle_request)
        : port_(port), listensocket_(new Net_work::TcpSocket()), handle_request_(handle_request)
    {
        listensocket_->BuildListenSocketMethod(port_, Net_work::backlog);
    }

    static void *ThreadRun(void *args)
    {
        pthread_detach(pthread_self());
        ThreadData *td = static_cast<ThreadData *>(args);
        td->this_->handle_request_(td->sockp_);
        td->sockp_->CloseSocket();
        delete td->sockp_;
        delete td;
    }

    void loop()
    {
        while (true)
        {
            std::string peerip;
            uint16_t peerport;
            Net_work::Socket *newsock = listensocket_->AcceptConnection(&peerip, &peerport);
            if (newsock == nullptr)
                continue;
            std::cout << "获取一个新连接, sockfd : " << newsock->GetSockFd() << "client info : " << peerip << ": " << peerport << std::endl;
            // newsock->CloseSocket();
            pthread_t tid;
            ThreadData *td = new ThreadData(this, newsock);
            pthread_create(&tid, nullptr, ThreadRun, td);
        }
    }

    ~TcpServer()
    {
        delete listensocket_;
    }

private:
    int port_;
    Net_work::Socket *listensocket_;

public:
    func_t handle_request_;
};