#pragma once

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

const char *root = "/";
const char *dev_null = "/dev/null";

void Daemon(bool ischdir, bool isclose)
{
    // 1. 忽略可能引起程序异常退出的信号
    signal(SIGCHLD, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    // 2. 让自己不要成为组长
    if (fork() > 0)
        exit(0);

    // 3. 设置让自己成为一个新的会话， 后面的代码其实是子进程在走
    setsid();

    // 4. 每一个进程都有自己的CWD，是否将当前进程的CWD更改成为 / 根目录
    if (ischdir)
        chdir(root);

    // 5. 已经变成守护进程啦，不需要和用户的输入输出，错误进行关联了
    if (isclose)
    {
        close(0);
        close(1);
        close(2);
    }
    else
    {
        // 这里一般建议就用这种
        int fd = open(dev_null, O_RDWR);
        if (fd > 0)
        {
            dup2(fd, 0);
            dup2(fd, 1);
            dup2(fd, 2);
            close(fd);
        }
    }
}