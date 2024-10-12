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
    int sock;
    struct sockaddr_in addr;
    char message[1024];
    int str_len;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handle("socket() error!");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = ntohs(atoi(argv[2]));

    // 调用 connect 函数向服务器发送请求连接.
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        error_handle("connect() error!");
    }

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1)
        error_handle("read() error!");

    cout << "Message from server: " << message << endl;
    close(sock);
    return 0;
}

void error_handle(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}