#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (pid == 0)
        puts("Hi , I am a Child Process! ");
    else
    {
        printf("Child Process Id: %d \n", pid);
        sleep(30);
    }
    if (pid == 0)
        puts("End Child Process!");
    else
        puts("End Parent Process!");
    return 0;
}
