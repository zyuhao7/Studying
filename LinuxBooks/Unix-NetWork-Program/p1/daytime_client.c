#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXLINE 4096
#define SA struct sockaddr

// 错误处理：打印系统错误信息并退出
void err_sys(const char *msg)
{
    perror(msg);
    exit(1);
}

// 错误处理：打印自定义错误信息并退出
void err_quit(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: ./client <IPaddress>");

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    // 填充服务器地址结构
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;           // IPv4
    servaddr.sin_port = htons(13);            // 端口号13 (Daytime服务)

    // 将IP地址从文本转换为二进制
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error");

    // 连接到服务器
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    // 读取并打印服务器返回的数据
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; // 添加字符串结束符
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    close(sockfd); // 关闭套接字
    return 0;
}
