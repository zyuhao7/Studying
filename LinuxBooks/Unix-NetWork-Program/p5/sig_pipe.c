#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void sigpipe_handler(int signo)
{
    printf("SIGPIPE received\n");
}

int main()
{
    signal(SIGPIPE, sigpipe_handler);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // daytime 服务器
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    sleep(2);
    write(sockfd, "first\n", 6);
    sleep(2);
    write(sockfd, "second\n", 7); // 这里可能触发 SIGPIPE

    return 0;
}
