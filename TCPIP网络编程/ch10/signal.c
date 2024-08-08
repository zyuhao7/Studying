#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM)
    {
        puts("Time Out!");
    }
    alarm(2); // 为了每隔两秒重复 SIGALRM信号.
}

void keycontrol(int sig)
{
    if (sig == SIGINT)
    {
        puts("CTRL + C Pressed");
    }
}

int main(int argc, char *argv[])
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);

    alarm(2);

    for (i = 0; i < 3; ++i)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}