#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];
    char str[] = "how are you ?";
    char buf[BUF_SIZE];

    pid_t pid;
    // 调用 pipe 函数创建管道. fds 数组保存用于 I/O 的文件描述符.

    pipe(fds);
    // 子进程将同时拥有创建管道获取的两个文件描述符, 复制的并非管道, 而是文件描述符.
    pid = fork();

    if (pid == 0)
    {
        write(fds[1], str, sizeof(str));
    }
    else
    {
        read(fds[0], buf, BUF_SIZE);
        puts(buf);
    }
    return 0;
}