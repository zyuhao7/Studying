#ifndef __unp_h
#define __unp_h

#include <sys/types.h>  /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/time.h>   /* timeval{} for select() */
#include <time.h>       /* timespec{} for pselect() */

#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>  /* inet(3) functions */
#include <errno.h>
#include <fcntl.h> /* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> /* for S_xxx file mode constants */
#include <sys/uio.h>  /* for iovec{} and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h> /* for Unix domain sockets */

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h> /* for convenience */
#endif

#ifdef HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif

/* OSF/1 actually disables recv() and send() in <sys/socket.h> */
#ifdef __osf__
#undef recv
#undef send
#define recv(a, b, c, d) recvfrom(a, b, c, d, 0, 0)
#define send(a, b, c, d) sendto(a, b, c, d, 0, 0)
#endif

/* Define some portably used constants */
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif

#ifndef SHUT_RD
#define SHUT_RD 0   /* shutdown for reading */
#define SHUT_WR 1   /* shutdown for writing */
#define SHUT_RDWR 2 /* shutdown for reading and writing */
#endif

#define MAXLINE 4096  /* max text line length */
#define BUFFSIZE 8192 /* buffer size for reads and writes */

#define SA struct sockaddr



void Close(int);
void Connect(int, const struct sockaddr *, socklen_t);
void Bind(int, const struct sockaddr *, socklen_t);
void Listen(int, int);
int Accept(int, struct sockaddr *, socklen_t *);
void Write(int, void *, size_t);
void Read(int, void *, size_t);
void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
void Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);

const char *Inet_ntop(int, const void *, char *, socklen_t);
void Inet_pton(int, const char *, void *);

int Socket(int, int, int);
void Setsockopt(int, int, int, const void *, socklen_t);

#endif /* __unp_h */
