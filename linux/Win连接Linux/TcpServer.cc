#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>

const static int default_backlog = 6;

enum
{
    Usage_Err = 1,
    Socket_Err,
    Bind_Err,
    Listen_Err
};

#define CONV(addr_ptr) ((struct sockaddr *)addr_ptr)

class TcpServer
{
public:
    TcpServer(uint16_t port) : _port(port), _isrunning(false)
    {
    }
    // 都是固定套路
    void Init()
    {
        // 1. 创建socket, file fd, 本质是文件
        _listensock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensock < 0)
        {
            exit(0);
        }
        int opt = 1;
        setsockopt(_listensock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

        // 2. 填充本地网络信息并bind
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        // 2.1 bind
        if (bind(_listensock, CONV(&local), sizeof(local)) != 0)
        {
            exit(Bind_Err);
        }

        // 3. 设置socket为监听状态，tcp特有的
        if (listen(_listensock, default_backlog) != 0)
        {
            exit(Listen_Err);
        }
    }
    void ProcessConnection(int sockfd, struct sockaddr_in &peer)
    {
        uint16_t clientport = ntohs(peer.sin_port);
        std::string clientip = inet_ntoa(peer.sin_addr);
        std::string prefix = clientip + ":" + std::to_string(clientport);
        std::cout << "get a new connection, info is : " << prefix << std::endl;
        while (true)
        {
            char inbuffer[1024];
            ssize_t s = ::read(sockfd, inbuffer, sizeof(inbuffer)-1);
            if(s > 0)
            {
                inbuffer[s] = 0;
                std::cout << prefix << "# " << inbuffer << std::endl;
                std::string echo = inbuffer;
                echo += "[tcp server echo message]";
                write(sockfd, echo.c_str(), echo.size());
            }
            else
            {
                std::cout << prefix << " client quit" << std::endl;
                break;
            }
        }
    }
    void Start()
    {
        _isrunning = true;
        while (_isrunning)
        {
            // 4. 获取连接
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int sockfd = accept(_listensock, CONV(&peer), &len);
            if (sockfd < 0)
            {
                continue;
            }
            ProcessConnection(sockfd, peer);
        }
    }
    ~TcpServer()
    {
    }

private:
    uint16_t _port;
    int _listensock; // TODO
    bool _isrunning;
};

using namespace std;

void Usage(std::string proc)
{
    std::cout << "Usage : \n\t" << proc << " local_port\n"
              << std::endl;
}
// ./tcp_server 8888
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        return Usage_Err;
    }
    uint16_t port = stoi(argv[1]);
    std::unique_ptr<TcpServer> tsvr = make_unique<TcpServer>(port);
    tsvr->Init();
    tsvr->Start();

    return 0;
}

