#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM)
    {
        puts("Time Out!");
    }
    alarm(2);
}

int main(int argc, char *argv[])
{
    int i;
    struct sigaction act; // 代替 signal.
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask); // 将 sa_mask 函数的所有位初始化为 0.
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    alarm(2);

    for (i = 0; i < 3; ++i)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}