#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;
void error_handle(char *msg);
int main()
{
    int fd;
    char buf[] = "Let's go Learning!\n";

    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        error_handle("open() error!");
    }

    cout << "file desc: " << fd << endl;

    if (write(fd, buf, sizeof(buf)) == -1)
    {
        error_handle("write() error!");
    }

    close(fd);
    return 0;
}

void error_handle(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}