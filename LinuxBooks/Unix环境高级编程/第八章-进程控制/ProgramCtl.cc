#include <iostream>
using namespace std;
// day-2025-8-29
// 第八章 进程控制
/*
        进程标识
            #include <unistd.h>
            pid_t getpid(void);
                返回值：调用进程的进程ID

            pid_t getppid(void);
                返回值：调用进程的父进程ID

            uid_t getuid(void);
                返回值：调用进程的实际用户ID

            uid_t geteuid(void);
                返回值：调用进程的有效用户ID

            gid_t getgid(void);
                返回值：调用进程的实际组ID

            gid_t getegid(void);
                返回值：调用进程的有效组ID

        函数 fork
        一个现有的进程可以调用fork函数创建一个新进程。
            #include <unistd.h>
            pid_t fork(void);
                返回值：子进程返回0，父进程返回子进程ID；若出错，返回−1

        函数 wait 和 waitpid
        当一个进程正常或异常终止时，内核就向其父进程发送 SIGCHLD信号。
            #include <sys/wait.h>
            pid_t wait(int *statloc);
            pid_t waitpid(pid_t pid, int *statloc, int options);
                两个函数返回值：若成功，返回进程ID；若出错，返回0
                pid == -1 等待任一子进程。此种情况下，waitpid与wait等效。
                pid > 0 等待进程ID与pid相等的子进程。
                pid == 0 等待组ID等于调用进程组ID的任一子进程。（9.4节将说明进程组。）
                pid <−1 等待组ID等于pid绝对值的任一子进程。

        竞争条件
        函数 exec


 */