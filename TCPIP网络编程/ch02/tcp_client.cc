#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;
void error_handle(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    struct sockaddr_in serv_addr;
    char msg[64];
    int sock;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handle("socket() error");

    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof serv_addr) == -1)
        error_handle("connect() error!");

    if (read(sock, msg, sizeof msg) == -1)
        error_handle("read data error!");

    cout << msg << endl;
    close(sock);

    return 0;
}