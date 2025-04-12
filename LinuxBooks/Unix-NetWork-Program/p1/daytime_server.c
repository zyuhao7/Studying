#include "unp.h"
#include <time.h>

#define LISTENQ 10 // 最大监听队列长度

void err_sys(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[1024];
    time_t ticks;

    // 创建监听socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    // 填充服务器地址
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;                // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 本机所有IP地址
    servaddr.sin_port = htons(13);                // 端口13（daytime服务）

    // 绑定地址
    if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error");

    // 开始监听
    if (listen(listenfd, LISTENQ) < 0)
        err_sys("listen error");

    printf("Daytime server running on port 13...\n");

    for (;;)
    { // 永久循环
        // 接受连接
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
            err_sys("accept error");

        // 获取当前时间
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        // 发送给客户端
        if (write(connfd, buff, strlen(buff)) < 0)
            err_sys("write error");

        // 关闭连接
        close(connfd);
    }
}
