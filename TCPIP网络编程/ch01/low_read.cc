#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;
#define BUF_SIZE 100
void error_handle(char *msg);

int main()
{
    int fd;
    char buf[BUF_SIZE];
    fd = open("data.txt", O_RDONLY);

    if (fd == -1)
    {
        error_handle("open() error!");
    }

    cout << "file desc: " << fd << endl;

    if (read(fd, buf, sizeof(buf)) == -1)
    {
        error_handle("read() error!");
    }
    cout << "file data: " << buf << endl;
    close(fd);
    return 0;
}

void error_handle(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}