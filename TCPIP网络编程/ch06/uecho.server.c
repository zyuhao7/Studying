#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *msg);

int main(int argc, char *argv[])
{
  int serv_sock;
  char msg[BUF_SIZE];
  int str_len;
  socklen_t client_addr_sz;

  struct sockaddr_in serv_addr, client_addr;
  if (argc != 2)
  {
    printf("Usage: %s <poort>\n", argv[0]);
    exit(1);
  }
  // 创建 UDP 套接字后, 向 socket 的第二个参数传递 SOCK_DGRAM
  serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (serv_sock == -1)
  {
    error_handling("UDP socket() creation error!");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // 分配地址接受数据, 不限制数据传输对象.
  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
  {
    error_handling("bind() error");
  }

  while (1)
  {
    client_addr_sz = sizeof(client_addr);
    str_len = recvfrom(serv_sock, msg, BUFSIZ, 0, (struct sockaddr *)&client_addr, &client_addr_sz);

    // 通过调用上面的函数同时获取数据传输端的地址, 正是利用该地址进行逆向重传.
    sendto(serv_sock, msg, str_len, 0, (struct sockaddr *)&client_addr, client_addr_sz);
  }

  close(serv_sock);
  return 0;
}

void error_handling(char *msg)
{
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
