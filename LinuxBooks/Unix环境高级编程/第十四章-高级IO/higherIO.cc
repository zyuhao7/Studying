
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

    异步IO

*/