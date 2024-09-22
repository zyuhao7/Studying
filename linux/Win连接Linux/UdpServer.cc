#include <iostream>
#include <string>
#include <memory>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const static uint16_t defaultport = 8888;
const static int defaultfd = -1;
const static int defaultsize = 1024;

enum
{
    Usage_Err = 1,
    Socket_Err,
    Bind_Err
};

class UdpServer
{
public:
    UdpServer(uint16_t port = defaultport)
        : _port(port), _sockfd(defaultfd)
    {
    }
    void Init()
    {
        // 1. 创建socket，就是创建了文件细节
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            exit(Socket_Err);
        }

        // 2. 绑定，指定网络信息
        struct sockaddr_in local;
        bzero(&local, sizeof(local)); // memset
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = INADDR_ANY; // 1. 4字节IP 2. 变成网络序列

        // 结构体填完，设置到内核中了吗？？没有
        int n = ::bind(_sockfd, (struct sockaddr *)&local, sizeof(local));
        if (n != 0)
        {
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
                uint16_t clientport = ntohs(peer.sin_port);
                std::string clientip = inet_ntoa(peer.sin_addr);
                std::string prefix = clientip + ":" + std::to_string(clientport);
                buffer[n] = 0;
                std::cout << prefix << "# " << buffer << std::endl;


                std::string echo = buffer;
                echo += "[udp server echo message]";
                sendto(_sockfd, echo.c_str(), echo.size(), 0, (struct sockaddr *)&peer, len);
            }
        }
    }
    ~UdpServer()
    {
    }

private:
    uint16_t _port;
    int _sockfd;
};

void Usage(std::string proc)
{
    std::cout << "Usage : \n\t" << proc << " local_port\n"
              << std::endl;
}

// ./udp_server 8888
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        return Usage_Err;
    }

    uint16_t port = std::stoi(argv[1]);
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(port);
    usvr->Init();
    usvr->Start();

    return 0;
}

