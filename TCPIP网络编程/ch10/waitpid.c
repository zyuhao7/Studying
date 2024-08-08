#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid = fork();

    if (pid == 0)
    {
        sleep(15); // 用 sleep 推迟子进程的执行.
        return 24;
    }
    else
    {
        // 调用 waitpid 传递参数 WNOHANG, 这样之前没有终止的子进程返回0.
        while (!waitpid(-1, &status, WNOHANG))
        {
            sleep(3);
            puts("Sleep 3 second. ");
        }
        if (WIFEXITED(status))
            printf("Child send : %d \n", WEXITSTATUS(status));
    }
    return 0;
}