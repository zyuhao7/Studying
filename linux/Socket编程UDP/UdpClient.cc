#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void Usage(const std::string &process)
{
    std::cout << "Usage: " << process << " server_ip server_port"
              << std::endl;
}
// ./udp_client server_ip server_port

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }

    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    // 1. 创建 socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        std::cerr << "socket error: " << strerror(errno) << std::endl;
        return 2;
    }
    std::cout << "create socket success: " << sock << std::endl;
    // 2. client 要不要进行 bind? 一定要 bind 的！！
    // 但是，不需要显示 bind，client 会在首次发送数据的时候会自动进行bind
    // 为什么？server 端的端口号，一定是众所周知，不可改变的，client 需
    // 要 port，bind 随机端口.
    // 为什么？client 会非常多.
    // client 需要 bind，但是不需要显示 bind，让本地 OS 自动随机 bind，
    // 选择随机端口号

    // 2.1 填充一下 server 信息

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport);
    server.sin_addr.s_addr = inet_addr(serverip.c_str());
    while (true)
    {
        // 我们要发的数据

        std::string inbuffer;
        std::cout << "Please Enter# ";
        std::getline(std::cin, inbuffer);
        // 我们要发给谁呀？server
        ssize_t n = sendto(sock, inbuffer.c_str(),
                           inbuffer.size(), 0, (struct sockaddr *)&server, sizeof(server));
        if (n > 0)
        {
            char buffer[1024];
            // 收消息

            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            ssize_t m = recvfrom(sock, buffer, sizeof(buffer) - 1,
                                 0, (struct sockaddr *)&temp, &len); // 一般建议都是要填的.
            if (m > 0)
            {
                buffer[m] = 0;
                std::cout << "server echo# " << buffer << std::endl;
            }
            else
                break;
        }
        else
            break;
    }
    close(sock);
    return 0;
}
