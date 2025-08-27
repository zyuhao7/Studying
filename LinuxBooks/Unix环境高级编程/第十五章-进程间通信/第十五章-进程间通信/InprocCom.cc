#include <iostream>
using namespace std;

// day-2025-8-25
// 第十五章 进程间通信
/*
    进程间通信(InterProcess Communication) IPC
        管道
        管道只能在具有公共祖先的两个进程之间使用.
        通常，一个管道由一个进程创建，在进程调用fork之后，这个管道就能在父进程和子进程之间使用了.

        管道是通过调用pipe函数创建的:
        #include <unistd.h>
        int pipe(int fd[2]);
            返回值：若成功，返回0，若出错，返回-1
            经由参数 fd 返回两个文件描述符：fd[0]为读而打开，fd[1]为写而打开。fd[1]的输出是fd[0]的输入。

        函数popen和pclose
        这两个函数实现的操作是：创建一个管道， fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止。

        #include <stdio.h>
        FILE *popen(const char *cmdstring, const char *type);
            返回值：若成功，返回文件指针；若出错，返回NULL

        int pclose(FILE *fp);
            返回值：若成功，返回cmdstring的终止状态；若出错，返回-1

        协同进程
        UNIX系统过滤程序从标准输入读取数据，向标准输出写数据。几个过滤程序通常在shell管道中线性连接。
        当一个过滤程序既产生某个过滤程序的输入，又读取该过滤程序的输出时，它就变成了协同进程。

        FIFO
        FIFO有时被称为命名管道。

        创建FIFO类似于创建文件。确实，FIFO的路径名存在于文件系统中。
        #include <sys/stat.h>
        int mkfifo(const char *path, mode_t mode);
        int mkfifoat(int fd, const char *path, mode_t mode);
            两个函数的返回值：若成功，返回0；若出错，返回−1

        XSI  IPC
        标识符和键
        ftok提供的唯一服务就是由一个路径名和项目ID产生一个键。
        #include <sys/ipc.h>
        key_t ftok(const char *path, int id);
            返回值：若成功，返回键；若出错，返回(key_t)−1

        权限结构
        struct ipc_perm {
            uid_t uid; // owner's effective user id
            gid_t gid;   // owner's effective group id
            uid_t cuid;  // creator's effective user id
            gid_t cgid;  // creator's effective group id
            mode_t mode; // access modes
        };

    2025-8-27
        消息队列
        调用的第一个函数通常是msgget，其功能是打开一个现有队列或创建一个新队列
        #include <sys/msg.h>
        int msgget(key_t key, int flag);
            返回值：若成功，返回消息队列ID；若出错，返回−1

        msgctl函数对队列执行多种操作
        #include <sys/msg.h>
        int msgctl(int msqid, int cmd, struct msqid_ds *buf);
            返回值：若成功，返回0；若出错，返回−1

        调用msgsnd将数据放到消息队列中。
        #include <sys/msg.h>
        int msgsnd(int msqid, const void *ptr, size_t nbytes, int flag);
            返回值：若成功，返回0；若出错，返回−1
            struct mymesg {
                long mtype;　　　 // positive message type
                char mtext[512]; // message data, of length nbytes
            };
            ptr就是一个指向mymesg结构的指针。

        msgrcv从队列中取用消息
        #include <sys/msg.h>
        ssize_t msgrcv(int msqid, void *ptr, size_t nbytes, long type, int flag);
            返回值：若成功，返回消息数据部分的长度；若出错，返回-1

        信号量
        信号量与已经介绍过的 IPC 机构（管道、FIFO 以及消息列队）不同。它是一个计数器，用于为多个进程提供对共享数据对象的访问。
            内核为每个信号量集合维护着一个semid_ds结构：
                struct semid_ds {
                    struct ipc_perm　sem_perm;　　// see Section 15.6.2
                    unsigned short sem_nsems; // # of semaphores in set
                    time_t　　　　　 sem_otime;// last-semop() time
                    time_t　　　　　 sem_ctime;//last-change time
                };
            每个信号量由一个无名结构表示，它至少包含下列成员：
                struct {
                    unsigned short　semval;　　　// semaphore value, always >= 0
                    pid_t　　　　　 sempid; // pid for last operation
                        unsigned short 　 semncnt; // # processes awaiting semval>curval
                        unsigned short　semzcnt; // # processes awaiting semval==0
                };

        当我们想使用XSI信号量时，首先需要通过调用函数semget来获得一个信号量ID。
        #include <sys/sem.h>
        int semget(key_t key, int nsems, int flag);
            返回值：若成功，返回信号量ID；若出错，返回−1

        semctl函数包含了多种信号量操作
        #include <sys/sem.h>
        int semctl(int semid, int semnum, int cmd, ...  # union semun arg );
            第4个参数是可选的，是否使用取决于所请求的命令，如果使用该参数，则其类型是semun，它是多个命令特定参数的联合（union）：
            union semun {
                int　　　　　　　val;　# for SETVAL
                struct semid_ds *buf;  # for IPC_STAT and IPC_SET
                unsigned short *array; # for GETALL and SETALL
            };

        函数semop自动执行信号量集合上的操作数组
        #include <sys/sem.h>
        int semop(int semid, struct sembuf semoparray[], size_t nops);
            返回值：若成功，返回0；若出错，返回−1
            struct sembuf {
                unsigned short　　　sem_num;　　 # member # in set (0, 1, ...,nsems-1
                short　　　　　　 　sem_op;　　  # operation(negative, 0,or pasitive
                short 　 　 　 　　 sem_flg;     # IPC_NOWAIT, SEM_UNDO
            };

        共享内存(存储)
        共享存储允许两个或多个进程共享一个给定的存储区。
        内核为每个共享存储段维护着一个结构，该结构至少要为每个共享存储段包含以下成员：
            struct shmid_ds {
                struct ipc_perm shm_perm;      #see Section 15.6.2
                    size_t　　　　　shm_segsz; # size of segment in bytes
                    pid_t　　　　　 shm_lpid; # pid of last shmop()
                    pid_t　　　　　 shm_cpid;  # pid of creator
                    shmatt_t　　　　shm_nattch; # number of current attaches
                    time_t　　　　　shm_atime; # last-attach time
                    time_t　　　　　shm_dtime;  # last-detach time
                    time_t　　　　　shm_ctime;  # last-change time
            };

        调用的第一个函数通常是shmget，它获得一个共享存储标识符。
        #include <sys/shm.h>
        int shmget(key_t key, size_t size, int flag);
            返回值：若成功，返回共享存储ID；若出错，返回−1

        shmctl函数对共享存储段执行多种操作
        #include <sys/shm.h>
        int shmctl(int shmid, int cmd, struct shmid_ds *buf);
            返回值：若成功，返回0；若出错，返回−1

        一旦创建了一个共享存储段，进程就可调用shmat将其连接到它的地址空间中
        #include <sys/shm.h>
        void *shmat(int shmid, const void *addr, int flag);
            返回值：若成功，返回指向共享存储段的指针；若出错，返回-1

        当对共享存储段的操作已经结束时，则调用 shmdt 与该段分离
        #include <sys/shm.h>
        int shmdt(const void *addr);
            返回值：若成功，返回0；若出错，返回-1

        POSIX 信号量
        我们可以调用sem_open函数来创建一个新的命名信号量或者使用一个现有信号量
        #include <semaphore.h>
        sem_t *sem_open(const char *name, int oflag, ... # mode_t mode, unsigned int value );
            返回值：若成功，返回指向sem_t的指针；若出错，返回SEM_FAILED

        当完成信号量操作时，可以调用sem_close函数来释放任何信号量相关的资源
        #include <semaphore.h>
        int sem_close(sem_t *sem);
            返回值：若成功，返回0；若出错，返回-1

        可以使用sem_unlink函数来销毁一个命名信号量
        include <semaphore.h>
        int sem_unlink(const char *name);
            返回值：若成功，返回0；若出错，返回-1

        可以使用sem_wait或者sem_trywait函数来实现信号量的减1操作
        include <semaphore.h>
        int sem_trywait(sem_t *sem);
        int sem_wait(sem_t *sem);
            两个函数的返回值：若成功，返回0；若出错则，返回−1

        第三个选择是阻塞一段确定的时间。为此，可以使用sem_timewait函数
        #include <semaphore.h>
        #include <time.h>
        int sem_timedwait(sem_t *restrict sem,
            const struct timespec *restrict tsptr);
            返回值：若成功，返回0；若出错，返回−1

        可以调用sem_post函数使信号量值增1
        #include <semaphore.h>
        int sem_post(sem_t *sem);
            返回值：若成功，返回0；若出错，返回−1

        可以调用sem_init函数来创建一个未命名的信号量。
        #include <semaphore.h>
        int sem_init(sem_t *sem, int pshared, unsigned int value);
            返回值：若成功，返回0；若出错，返回−1

        对未命名信号量的使用已经完成时，可以调用sem_destroy函数丢弃它
        #include <semaphore.h>
        int sem_destroy(sem_t *sem);
            返回值：若成功，返回0；若出错，返回−1

        sem_getvalue函数可以用来检索信号量值
        #include <semaphore.h>
        int sem_getvalue(sem_t *restrict sem, int *restrict valp);
            返回值：若成功，返回0；若出错，返回−1

        客户进程-服务器进程属性
        

*/