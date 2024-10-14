#pragma once

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <functional>
#include <memory>
#include "ThreadPool.hpp"
#include "Log.hpp"
#include "Comm.hpp"
#include "Socket.hpp"
#include "InetAddr.hpp"

using namespace Net_Work;
const static int default_backlog = 6;
using task_t = std::function<void()>;
using handler_t = std::function<std::string(std::string)>;

class TcpServer
{
public:
    TcpServer(uint16_t port, handler_t handler)
        : _port(port), _isrunning(false), _listensock(new TcpSocket()), _handler(handler)
    {
    }
    // 都是固定套路
    void Init()
    {
        _listensock->BuildListenSocketMethod(_port, default_backlog);
    }
    // 仅仅处理IO问题，具体协议处理，交给上层处理
    void ProcessConnection(std::shared_ptr<Socket> sock, InetAddr addr)
    {
        std::string request_str;
        if (sock->Recv(&request_str, 4096)) // 仅仅用来测试，不作为实际参考，实际读取要处理字节流问题
        {
            std::string response = _handler(request_str);
            sock->Send(response);
            sock->CloseSocket();
        }
    }
    void Start()
    {
        _isrunning = true;
        while (_isrunning)
        {
            std::string clientip;
            uint16_t clientport;
            std::shared_ptr<Socket> sock = _listensock->AcceptConnection(&clientip, &clientport);
            if (sock == nullptr)
            {
                continue;
            }
            InetAddr addr(clientip, clientport);
            task_t task = std::bind(&TcpServer::ProcessConnection, this, sock, addr);
            ThreadPool<task_t>::GetInstance()->Push(task);
        }
        _isrunning = false;
    }
    ~TcpServer()
    {
    }

private:
    uint16_t _port;
    std::unique_ptr<Socket> _listensock;
    bool _isrunning;
    handler_t _handler;
};