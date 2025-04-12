#ifndef PROCESSPOOL_H
#define PROCESSPOOL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
    动态创建进程(或线程)是比较耗费时间的，这将导致较慢的客户响应。
    动态创建的子进程(或子线程)通常只用来为一个客户服务(除非我们做特殊的处理)，这将导致系统上产生大量的细微进程(或线程)。
    进程(或线程)间的切换将消耗大量 CPU 时间。
    动态创建的子进程是当前进程的完整映像。
    当前进程必须谨慎地管理其分配的文件描述符和堆内存等系统资源，否则子进程可能复制这些资源，从而使系统的可用资源急剧下降，
    进而影响服务器的性能。
*/
// 半同步/ 半异步进程池 实现
class process
{

public:

public:
};

#endif