#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *msg);

int main(int argc, char *argv[])
{
    int sock;
    char msg[BUF_SIZE];
    int str_len;
    socklen_t addr_sz;
    struct sockaddr_in serv_addr, from_addr;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    // 创建 UDP 套接字.
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket() error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (1)
    {
        fputs("Insert message(q to quit):", stdout);
        fgets(msg, sizeof(msg), stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
            break;

        sendto(sock, msg, strlen(msg), 0,
               (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        addr_sz = sizeof(from_addr);
        str_len = recvfrom(sock, msg, BUF_SIZE, 0, (struct sockaddr *)&from_addr, &addr_sz);
        msg[str_len] = 0;

        // write(sock, msg, strlen(msg));

        // str_len = read(sock, msg, sizeof(msg) - 1);
        // msg[str_len] = 0;

        printf("Message from server: %s\n", msg);
    }
    close(sock);
    return 0;
}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
