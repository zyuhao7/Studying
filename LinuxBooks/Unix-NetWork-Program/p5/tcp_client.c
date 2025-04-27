// tcp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 9877
#define MAXLINE 4096

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, fp) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        if (read(sockfd, recvline, MAXLINE) == 0)
        {
            printf("server terminated prematurely\n");
            exit(1);
        }
        fputs(recvline, stdout);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        printf("usage: tcp_client <IPaddress>\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    close(sockfd);
}
