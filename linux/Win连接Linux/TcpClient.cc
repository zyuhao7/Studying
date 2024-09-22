#include <winsock2.h>
#include <iostream>
#include <string>

#pragma warning(disable : 4996)

#pragma comment(lib, "ws2_32.lib")

std::string serverip = "";  // 填写你的云服务器ip
uint16_t serverport = 8888; // 填写你的云服务开放的端口号

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "socket failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverport);                  // 替换为服务器端口
    serverAddr.sin_addr.s_addr = inet_addr(serverip.c_str()); // 替换为服务器IP地址

    result = connect(clientSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR)
    {
        std::cerr << "connect failed" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    while (true)
    {
        std::string message;
        std::cout << "Please Enter@ ";
        std::getline(std::cin, message);
        if(message.empty()) continue;
        send(clientSocket, message.c_str(), message.size(), 0);

        char buffer[1024] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // 确保字符串以 null 结尾
            std::cout << "Received from server: " << buffer << std::endl;
        }
        else
        {
            std::cerr << "recv failed" << std::endl;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
