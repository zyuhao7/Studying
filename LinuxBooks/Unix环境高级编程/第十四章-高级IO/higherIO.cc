
// 第十四章 高级 IO
// day-2025-8-23

/*
    本章涵盖: 非阻塞I/O、记录锁、I/O 多路转接（select 和 poll 函数）、异步I/O、readv 和 writev 函数以及存储映射 I/O （mmap）.

    非阻塞IO
    记录锁
        记录锁（record locking）的功能是：当第一个进程正在读或修改文件的某个部分时，使用记录锁可以阻止其他进程修改同一文件区。
        fcntl记录锁
        #include <fcnt1.h>
        int fcnt1(int fd, int cmd, ... struct flock *flockptr );
            返回值：若成功，依赖于cmd（见下），否则，返回−1

        对于记录锁，cmd是F_GETLK、F_SETLK或F_SETLKW。
        struct flock {
        short l_type;　　　 // F_RDLCK(共享读锁), F_WRLCK(独占性写锁), or F_UNLCK(解锁一个区域)
        short l_whence;　　 // SEEK_SET, SEEK_CUR, or SEEK_END
        off_t l_start;　　　 // offset in bytes, relative to l_whence  要加锁或解锁区域的起始字节偏移量（l_start和l_whence）
        off_t l_len;　　　　 // length, in bytes; 0 means lock to EOF  区域的字节长度（l_len）。
        pid_t l_pid;　　　　 // returned with F_GETLK  进程的ID（l_pid）持有的锁能阻塞当前进程
        };

    IO 多路复用
        select 和 pselect
        #include <sys/select.h>
        int select(int maxfdp1, fd_set *restrict readfds,
        fd_set *restrict writefds, fd_set *restrict exceptfds,
        struct timeval *restrict tvptr);
            返回值：准备就绪的描述符数目；若超时，返回0；若出错，返回−1

        #include <sys/select.h>
        int FD_ISSET(int fd, fd_set *fdset);

        返回值：若fd在描述符集中，返回非0值；否则，返回0
        void FD_CLR(int fd, fd_set *fdset);
        void FD_SET(int fd, fd_set *fdset);
        void FD_ZERO(fd_set *fdset);

        POSIX.1也定义了一个select的变体，称为pselect
        #include <sys/select.h>
        int pselect(int maxfdp1, fd_set *restrict readfds,
        fd_set *restrict writefds, fd_set *restrict exceptfds,
        const struct timespec *restrict tsptr,
        const sigset_t *restrict sigmask);
            返回值：准备就绪的描述符数目；若超时，返回0；若出错，返回−1

        函数 poll
        #include <poll.h>
        int poll(struct pollfd fdarray[], nfds_t nfds, int timeout);
            返回值：准备就绪的描述符数目；若超时，返回0；若出错，返回-1

        struct pollfd {
            int　 fd;　　　 // file descriptor to check, or < 0 to ignore
            short events;  // events of interest on fd
            short revents; // events that occurred on fd
        };

    day-2025-8-24
    异步IO
        System V 异步I/O
        System V的异步I/O信号是 SIGPOLL

        BSD 异步I/O
        异步I/O是信号SIGIO和SIGURG的组合
            SIGIO是通用异步I/O信号，SIGURG则只用来通知进程网络连接上的带外数据已经到达

        POSIX 异步 I/O
        在进行异步I/O之前需要先初始化AIO控制块，调用aio_read函数来进行异步读操作，或调用aio_write函数来进行异步写操作。
        #include <aio.h>
        int aio_read(struct aiocb *aiocb);
        int aio_write(struct aiocb *aiocb);
            两个函数的返回值：若成功，返回0；若出错，返回−1

        要想强制所有等待中的异步操作不等待而写入持久化的存储中，可以设立一个 AIO 控制块并调用aio_fsync函数。
        #include <aio.h>
        int aio_fsync(int op, struct aiocb *aiocb);
            返回值：若成功，返回0；若出错，返回−1

        如果在完成了所有事务时，还有异步操作未完成时，可以调用aio_suspend函数来阻塞进程，直到操作完成
        #include <aio.h>
        int aio_suspend(const struct aiocb *const list[], int nent,
        const struct timespec *timeout);
            返回值：若成功，返回0；若出错，返回−1

        当还有我们不想再完成的等待中的异步I/O操作时，可以尝试使用aio_cancel函数来取消它们。
        #include <aio.h>
        int aio_cancel(int fd, struct aiocb *aiocb);

        该函数提交一系列由一个AIO控制块列表描述的I/O请求
        #include <aio.h>
        int lio_listio(int mode, struct aiocb *restrict const list[restrict],
        int nent, struct sigevent *restrict sigev);
            返回值：若成功，返回0；若出错，返回−1

        函数 readv 和 writev
        #include <sys/uio.h>
        ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
        ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
            两个函数的返回值：已读或已写的字节数；若出错，返回−1

        这两个函数的第二个参数是指向iovec结构数组的一个指针：
        struct iovec {
            void *iov_base; // starting address of buffer
            size_t iov_len; // size of buffer
        };
        writev 函数从缓冲区中聚集输出数据的顺序是：iov[0]、iov[1]直至 iov[iovcnt-1]。
        writev返回输出的字节总数，通常应等于所有缓冲区长度之和。

        总之，应当用尽量少的系统调用次数来完成任务。如果我们只写少量的数据，将会发现自己复制数据然后使用一次write会比用writev更
        合算。但也可能发现，我们管理自己的分段缓冲区会增加程序额外的复杂性成本，所以从性能成本的角度来看不合算。


        函数 readn 和 writen
        一次read操作所返回的数据可能少于所要求的数据，即使还没达到文件尾端也可能是这样.这不是一个错误，应当继续读该设备。
        一次write操作的返回值也可能少于指定输出的字节数。
        #include "apue.h"
        ssize_t readn(int fd, void *buf, size_t nbytes);
        ssize_t writen(int fd, void *buf, size_t nbytes);
            个函数的返回值：读、写的字节数；若出错，返回−1

        ssize_t readn(int fd, void *ptr, size_t n)
        {
            size_t nleft; // 剩余需要读的数据
            size_t nread; // 已经读取的
            nleft = n;
            while (nleft > 0)
            {
                if (nread = read(fd, ptr, nleft) < 0)
                {
                    if (nleft == n)
                        return -1; // 读失败
                    else
                        break; // 读失败，但已经读了一些数据
                }
                else if (nread == 0)
                    break; // EOF
                nleft -= nread;
                ptr += nread;
            }
            return n - nleft; // 返回已经读到的数据
        }

        内存映射 I/O
        存储映射I/O（memory-mapped I/O）能将一个磁盘文件映射到存储空间中的一个缓冲区上，于是，当从缓冲区中取数据时，就相当于读
        文件中的相应字节。 与此类似，将数据存入缓冲区时，相应字节就自动写入文件.

        应首先告诉内核将一个给定的文件映射到一个存储区域中。这是由mmap函数实现的:
        #include <sys/mman.h>
        void *mmap(void *addr, size_t len, int prot, int flag, int fd, off_t off);
            返回值：若成功，返回映射区的起始地址；若出错，返回MAP_FAILED

            addr参数用于指定映射存储区的起始地址.通常将其设置为0，这表示由系统选择该映射区的起始地址.
            fd参数是指定要被映射文件的描述符.
            len参数是映射的字节数，off是要映射字节在文件中的起始偏移量.
            prot参数指定了映射存储区的保护要求.

        映射存储区位于堆和栈之间：这属于实现细节，各种实现之间可能不同。

        调用mprotect可以更改一个现有映射的权限。
        #include <sys/mman.h>
        int mprotect(void *addr, size_t len, int prot);
            返回值：若成功，返回0；若出错，返回-1

        msync函数类似于fsync（见3.13节），但作用于存储映射区。
        #include <sys/mman.h>
        int msync(void *addr, size_t len, int flags);
            返回值：若成功，返回0；若出错，返回-1

        当进程终止时，会自动解除存储映射区的映射，或者直接调用munmap函数也可以解除映射区。关闭映射存储区时使用的文件描述符并不解除映射区。
        #include <sys/mman.h>
        int munmap(void *addr, size_t len);
            返回值：若成功，返回0；若出错，返回−1
*/
