#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

void error_handle(char *msg);

int main(int argc, char *argv[])
{
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    socklen_t client_addr_len;

    char message[] = "hello world";

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << "<port>" << endl;
        exit(1);
    }

    // 调用 socket 函数创建套接字.
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handle("socket() error!");
    }

    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 调用 bind 函数 分配 ip 地址和 端口号.
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handle("bind() error!");
    }

    // 调用 listen 函数将套接字转换为可接受连接状态
    if (listen(serv_sock, 5) == -1)
    {
        error_handle("listen() error!");
    }

    client_addr_len = sizeof(client_addr);

    // 调用 accept 函数受理连接请求.
    client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_sock == -1)
    {
        error_handle("accept() error!");
    }

    write(client_sock, message, sizeof(message));
    close(client_sock);
    close(serv_sock);

    return 0;
}

void error_handle(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}