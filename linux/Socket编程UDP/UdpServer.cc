#pragma once
#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "nocopy.hpp"
#include "Log.hpp"
#include "Comm.hpp"
#include "InetAddr.hpp"

const static uint16_t defaultport = 8888;
const static int defaultfd = -1;
const static int defaultsize = 1024;
class UdpServer : public nocopy
{
public:
    UdpServer(uint16_t port = defaultport)
        : _port(port), _sockfd(defaultfd)
    {
    }
    void Init()
    {
        // 1. 创建 socket，就是创建了文件细节

        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            LOG(FATAL, "socket errr, %d : %s\n", errno,
                strerror(errno));
            exit(Socket_Err);
        }
        LOG(INFO, "socket success, sockfd: %d\n",
            _sockfd);

        // 2. 绑定，指定网络信息
        struct sockaddr_in local;
        bzero(&local, sizeof(local)); // memset
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = INADDR_ANY; // 0
        // local.sin_addr.s_addr = inet_addr(_ip.c_str()); // 1. 4  字节 IP  2. 变成网络序列
        // 结构体填完，设置到内核中了吗？？没有

        int n = ::bind(_sockfd, (struct sockaddr *)&local,
                       sizeof(local));
        if (n != 0)
        {
            LOG(FATAL, "bind errr, %d : %s\n", errno,
                strerror(errno));
            exit(Bind_Err);
        }
    }
    void Start()
    {
        // 服务器永远不退出

        char buffer[defaultsize];
        for (;;)
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer); // 不能乱写

            ssize_t n = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&peer, &len);
            if (n > 0)
            {
                InetAddr addr(peer);
                buffer[n] = 0;
                std::cout << "[" << addr.PrintDebug() << "]# " << buffer << std::endl;
                sendto(_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&peer, len);
            }
        }
    }
    ~UdpServer()
    {
    }

private:
    // std::string _ip; // 后面要调整

    uint16_t _port;
    int _sockfd;
};

int main()
{
    UdpServer server;
    server.Init();
    server.Start();
}