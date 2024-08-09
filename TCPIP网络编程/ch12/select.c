#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/time.h>

#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads); // 将文件描述符0对应的位设置为 1.

    /*
    timeout.tv_sec = 5;
    timeout.tv_usec=5000;
    */

    while(1)
    {
      temps = reads; // 为了防止调用 select函数后, 位的内容改变, 提前保存.
      
      timeout.tv_sec = 5;
      timeout.tv_usec = 0;
      result = select(1, &temps,0, 0, &timeout);

      if(result == -1)
      {
        puts("select() err!");
        break;
      }
      else if(result == 0)
      {
        puts("Time-Out!");
      }
      else{
        if(FD_ISSET(0, &temps))
        {
           str_len = read(0, buf, BUF_SIZE);
           buf[str_len] = 0;
           printf("Message from console: %s", buf);
        }
      }
    }
  return 0;
}
