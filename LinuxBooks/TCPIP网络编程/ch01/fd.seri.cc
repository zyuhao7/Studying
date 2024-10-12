#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

int main()
{
    int fd1, fd2, fd3;
    // 创建一个文件和两个套接字
    fd1 = socket(PF_INET, SOCK_STREAM, 0);
    fd2 = open("test.dat", O_CREAT | O_TRUNC | O_WRONLY);
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    // 输出之前创建的文件描述符的整数值.
    cout << "file1 desc 1: " << fd1 << endl; // 3 4 5
    cout << "file2 desc 2: " << fd2 << endl;
    cout << "file3 desc 3: " << fd3 << endl;
}