#include <iostream>
using namespace std;

// 第十二章 - 线程控制
// day-2025-8-17
/*
    线程属性
        #include <pthread.h>
        int pthread_attr_init(pthread_attr_t *attr);
        int pthread_attr_destroy(pthread_attr_t *attr);
            两个函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr,
        int *detachstate);
        int pthread_attr_setdetachstate(pthread_attr_t *attr, int *detachstate);
            两个函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_attr_getstack(const pthread_attr_t *restrict attr,
        void **restrict stackaddr,
        size_t *restrict stacksize);
        int pthread_attr_setstack(pthread_attr_t *attr,
        void *stackaddr, size_t stacksize);
            两个函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,
        size_t *restrict stacksize);
        int pthread_attr_setstacksize (pthread_attr_t *attr, size_t stacksize);
            两个函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_attr_getguardsize(const pthread_attr_t *restrict attr,
        size_t *restrict guardsize);
        int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
            两个函数的返回值：若成功，返回0；否则，返回错误编号

    同步属性
        互斥量属性
            互斥量属性是用pthread_mutexattr_t结构表示的。
            #include <pthread.h>
            int pthread_mutexattr_init(pthread_mutexattr_t *attr);
            int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
                两个函数的返回值：若成功，返回0；否则，返回错误编号
            值得注意的3个属性是：进程共享属性、健壮属性以及类型属性。

            #include <pthread.h>
            int pthread_mutexattr_getpshared(const pthread_mutexattr_t
            *restrict attr,
            int *restrict pshared);
            int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,
            int pshared);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

            可以使用 pthread_mutexattr_getrobust 函数获取健壮的互斥量属性的值。
            #include <pthread.h>
            int pthread_mutexattr_getrobust(const pthread_mutexattr_t
            *restrict attr,
            int *restrict robust);
            int pthread_mutexattr_setrobust(pthread_mutexattr_t *attr,
            int robust);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

            线程可以调用pthread_mutex_consistent 函数，指明与该互斥量相关的状态在互斥量解锁之前是一致的。
            #include <pthread.h>
            int pthread_mutex_consistent(pthread_mutex_t *mutex);
                返回值：若成功，返回0；否则，返回错误编号

            可以用pthread_mutexattr_gettype函数得到互斥量类型属性
            #include <pthread.h>
            int pthread_mutexattr_gettype(const pthread_mutexattr_t*restrict
            attr,int*restrict type);
            int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
                两个函数的返回值: 若成功，返回0；否则，返回错误编号

            读写锁属性
            读 写 锁 与 互 斥 量 类 似 ， 也 是 有 属 性 的
            #include <pthread.h>
            int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
            int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

            读写锁支持的唯一属性是进程共享属性
            #include <pthread.h>
            int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *
            restrict attr,
            int *restrict pshared);
            int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr,
            int pshared);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

            条件变量属性
                Single UNIX Specification目前定义了条件变量的两个属性：进程共享属性和时钟属性。
                #include <pthread.h>
                int pthread_condattr_init(pthread_condattr_t *attr);
                int pthread_condattr_destroy(pthread_condattr_t *attr);
                    两个函数的返回值：若成功，返回0；否则，返回错误编号

                #include <pthread.h>
                int pthread_condattr_getpshared(const pthread_condattr_t *
                restrict attr,
                int *restrict pshared);
                int pthread_condattr_setpshared(pthread_condattr_t *attr,
                int pshared);
                    两个函数的返回值：若成功，返回0；否则，返回错误编号

                #include <pthread.h>
                int pthread_condattr_getclock(const pthread_condattr_t *
                restrict attr,
                clockid_t *restrict clock_id);
                int pthread_condattr_setclock(pthread_condattr_t *attr,
                clockid_t clock_id);
                    两个函数的返回值:若成功，返回0；否则，返回错误编号

                屏障属性
                #include <pthread.h>
                int pthread_barrierattr_init(pthread_barrierattr_t *attr);
                int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
                    两个函数的返回值：若成功，返回0；否则，返回错误编号

                #include <pthread.h>
                int pthread_barrierattr_getpshared(const pthread_barrierattr_t *
                restrict attr,int *restrict pshared);
                int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr,
                int pshared);
                    两个函数的返回值：若成功，返回0；否则，返回错误编号

        重入
            如果一个函数在相同的时间点可以被多个线程安全地调用，就称该函数是线程安全的
            如果一个函数对多个线程来说是可重入的，就说这个函数就是线程安全的

            #include <stdio.h>
            int ftrylockfile(FILE *fp);
                返回值：若成功，返回0；若不能获取锁，返回非0数值
            void flockfile(FILE *fp);
            void funlockfile(FILE *fp);

            #include <stdio.h>
            int getchar_unlocked(void);
            int getc_unlocked(FILE *fp);
                两个函数的返回值: 若成功，返回下一个字符；若遇到文件尾或者出错，返回EOF

            int putchar_unlocked(int c);
            int putc_unlocked(int c, FILE *fp);
                两个函数的返回值：若成功，返回c；若出错，返回EOF

        线程和信号
            #include <signal.h>
            int pthread_sigmask(int how, const sigset_t *restrict set,
            sigset_t *restrict oset);
                返回值：若成功，返回0；否则，返回错误编号

            #include <signal.h>
            int sigwait(const sigset_t *restrict set, int *restrict signop);
                返回值：若成功，返回0；否则，返回错误编号

            #include <signal.h>
            int pthread_kill(pthread_t thread, int signo);
                返回值：若成功，返回0；否则，返回错误编号

        线程和 fork
            当线程调用fork时，就为子进程创建了整个进程地址空间的副本。

            #include <pthread.h>
            int pthread_atfork(void (*prepare)(void), void (*parent)(void),
            void (*child)(void));
                    返回值：若成功，返回0；否则，返回错误编号

*/