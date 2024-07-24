#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;
#define BUF_SIZE 1024
void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int serv_sock, client_sock;
    socklen_t client_addr_len;
    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr, client_addr;

    if (argc != 2)
        printf("Usage: %s <Port> \n", argv[0]);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error!");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error!");

    client_addr_len = sizeof(client_addr);

    // 调用五次 accept 函数, 为五个客户端提供服务.
    int str_len;
    for (int i = 0; i < 5; ++i)
    {
        client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == -1)
            error_handling("accept() error!");
        else
            printf("Connect client : %d \n", i + 1);
        while ((str_len = read(client_sock, msg, BUF_SIZE)) != -1)
        {
            fputs(msg, stdout);
            write(client_sock, msg, str_len);
        }
        close(client_sock);
    }
    close(serv_sock);
    return 0;
}