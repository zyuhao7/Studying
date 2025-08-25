#include <iostream>
using namespace std;

// day-2025-8-25
// 第十五章 进程间通信
/*
    进程间通信(InterProcess Communication) IPC
        管道
        管道只能在具有公共祖先的两个进程之间使用.
        通常，一个管道由一个进程创建，在进程调用fork之后，这个管道就能在父进程和子进程之间使用了.

        管道是通过调用pipe函数创建的:
        #include <unistd.h>
        int pipe(int fd[2]);
            返回值：若成功，返回0，若出错，返回-1
            经由参数 fd 返回两个文件描述符：fd[0]为读而打开，fd[1]为写而打开。fd[1]的输出是fd[0]的输入。

        函数popen和pclose
        这两个函数实现的操作是：创建一个管道， fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止。

        #include <stdio.h>
        FILE *popen(const char *cmdstring, const char *type);
            返回值：若成功，返回文件指针；若出错，返回NULL

        int pclose(FILE *fp);
            返回值：若成功，返回cmdstring的终止状态；若出错，返回-1

        协同进程
        UNIX系统过滤程序从标准输入读取数据，向标准输出写数据。几个过滤程序通常在shell管道中线性连接。
        当一个过滤程序既产生某个过滤程序的输入，又读取该过滤程序的输出时，它就变成了协同进程。

        FIFO
        FIFO有时被称为命名管道。

        创建FIFO类似于创建文件。确实，FIFO的路径名存在于文件系统中。
        #include <sys/stat.h>
        int mkfifo(const char *path, mode_t mode);
        int mkfifoat(int fd, const char *path, mode_t mode);
            两个函数的返回值：若成功，返回0；若出错，返回−1

        XSI  IPC
        标识符和键
        ftok提供的唯一服务就是由一个路径名和项目ID产生一个键。
        #include <sys/ipc.h>
        key_t ftok(const char *path, int id);
            返回值：若成功，返回键；若出错，返回(key_t)−1

        权限结构
        struct ipc_perm {
            uid_t uid; // owner's effective user id
            gid_t gid;   // owner's effective group id
            uid_t cuid;  // creator's effective user id
            gid_t cgid;  // creator's effective group id
            mode_t mode; // access modes
        };

*/