#include <iostream>
#include <cstdio>
#include <thread>
#include <string>
#include <cstdlib>
#include <WinSock2.h>
#include <Windows.h>

#pragma warning(disable : 4996)

#pragma comment(lib, "ws2_32.lib")

std::string serverip = "";  // 填写你的云服务器ip
uint16_t serverport = 8888; // 填写你的云服务开放的端口号

int main()
{
    WSADATA wsd;
    WSAStartup(MAKEWORD(2, 2), &wsd);

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport); //?
    server.sin_addr.s_addr = inet_addr(serverip.c_str());

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == SOCKET_ERROR)
    {
        std::cout << "socker error" << std::endl;
        return 1;
    }
    std::string message;
    char buffer[1024];
    while (true)
    {
        std::cout << "Please Enter@ ";
        std::getline(std::cin, message);
        if(message.empty()) continue;
        sendto(sockfd, message.c_str(), (int)message.size(), 0, (struct sockaddr *)&server, sizeof(server));
        struct sockaddr_in temp;
        int len = sizeof(temp);
        int s = recvfrom(sockfd, buffer, 1023, 0, (struct sockaddr *)&temp, &len);
        if (s > 0)
        {
            buffer[s] = 0;
            std::cout << buffer << std::endl;
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
