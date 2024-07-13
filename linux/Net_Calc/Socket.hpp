#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

#define Convert(addrptr) ((struct sockaddr *)addrptr)

namespace Net_work
{
    const static int defaultsockfd = -1;
    const static int backlog = 5;
    enum
    {
        SocketError = 1,
        BindError,
        ListenError,
    };

    // Socket 接口类.
    class Socket
    {
    public:
        virtual ~Socket() {}
        virtual void CreateSocketOrDie() = 0;
        virtual void BindSocketOrDie(uint16_t port) = 0;
        virtual void ListenSocketOrDie(int backlog) = 0;
        virtual Socket *AcceptConnection(std::string *peerip, uint16_t *peerport) = 0;
        virtual bool ConnectServer(std::string &serverip, uint16_t serverport) = 0;
        virtual int GetSockFd() = 0;
        virtual void SetSockFd(int sockfd) = 0;
        virtual void CloseSocket() = 0;

    public:
        void BuildListenSocketMethod(uint16_t port, int backlog)
        {
            CreateSocketOrDie();
            BindSocketOrDie(port);
            ListenSocketOrDie(backlog);
        }

        bool BuildConnecSocketMethod(std::string &serverip, uint16_t serverport)
        {
            CreateSocketOrDie();
            return ConnectServer(serverip, serverport);
        }

        void BuildNormalSocketMethod(int sockfd)
        {
            SetSockFd(sockfd);
        }
    };

    class TcpSocket : public Socket
    {
    public:
        TcpSocket(int sockfd = defaultsockfd)
            : sockfd_(sockfd)
        {
        }

        ~TcpSocket() {}

        void CreateSocketOrDie() override
        {
            sockfd_ = ::socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd_ < 0)
                exit(SocketError);
        }

        void BindSocketOrDie(uint16_t port) override
        {
            struct sockaddr_in local;
            memset(&local, 0, sizeof local);
            local.sin_family = AF_INET;
            local.sin_addr.s_addr = INADDR_ANY;
            local.sin_port = htons(port);

            int n = ::bind(sockfd_, Convert(&local), sizeof(local));
            if (n < 0)
                exit(BindError);
        }

        void ListenSocketOrDie(int backlog) override
        {
            int n = ::listen(sockfd_, backlog);
            if (n < 0)
                exit(ListenError);
        }

        Socket *AcceptConnection(std::string *peerip, uint16_t *peerport) override
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int newsockfd = ::accept(sockfd_, Convert(&peer), &len);
            if (newsockfd < 0)
                return nullptr;
            *peerport = ntohs(peer.sin_port);
            *peerip = inet_ntoa(peer.sin_addr);

            Socket *s = new TcpSocket(newsockfd);
            return s;
        }
        bool ConnectServer(std::string &serverip, uint16_t serverport) override
        {
            struct sockaddr_in server;
            memset(&server, 0, sizeof(server));
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr(serverip.c_str());
            server.sin_port = htons(serverport);

            int n = ::connect(sockfd_, Convert(&server), sizeof(server));
            if (n == 0)
                return true;
            else
                return false;
        }

        int GetSockFd() override
        {
            return sockfd_;
        }

        void SetSockFd(int sockfd) override
        {
            sockfd_ = sockfd;
        }

        void CloseSocket() override
        {
            if (sockfd_ > defaultsockfd)
                ::close(sockfd_);
        }

    private:
        int sockfd_;
    };
}
