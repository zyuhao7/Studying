#include <iostream>
using namespace std;

// 第七章 进程环境
// day-2025-8-28
/*
        main函数
        进程终止
        有8种方式使进程终止（termination），其中 5种为正常终止，它们是：
            （1）从main返回；
            （2）调用exit；
            （3）调用_exit或_Exit；
            （4）最后一个线程从其启动例程返回;
            （5）从最后一个线程调用pthread_exit;

        3种为异常终止，它们是：
            （1）调用abort;
            （2）接收到未被捕捉的信号；
            （3）最后一个线程调用pthread_cancel。

        3个函数用于正常终止一个程序：_exit和_Exit立即进入内核，exit则先执行一些清理处理，然后返回内核。
            #include <stdlib.h>
            void exit(int status);
            void _Exit(int status);

            #include <unistd.h>
            void _exit(int status);

        函数atexit
            #include <stdlib.h>
            int atexit(void (*func)(void));
                返回值：若成功，返回0；若出错，返回非0

        命令行参数
        环境表
        C程序的存储空间布局
            正文段
            初始化数据段
            未初始化数据段(bss段)
            栈
            堆

        共享库
        共享库使得可执行文件中不再需要包含公用的库函数，而只需在所有进程都可引用的存储区中保存这种库例程的一个副本
        程序第一次执行或者第一次调用某个库函数时，用动态链接方法将程序与共享库函数相链接。

        存储空间分配
            （1）malloc，分配指定字节数的存储区。此存储区中的初始值不确定。
            （2）calloc，为指定数量指定长度的对象分配存储空间。该空间中的每一位（bit）都初始化为0。
            （3）realloc，增加或减少以前分配区的长度。当增加长度时，可能需将以前分配区的内容移到另一个足够大的区域，以便在尾端提供增加的存储区，
            而新增区域内的初始值则不确定。

            #include <stdlib.h>
            void *malloc(size_t size);
            void *calloc(size_t nobj, size_t size);
            void *realloc(void *ptr, size_t newsize);
                3个函数返回值：若成功，返回非空指针；若出错，返回NULL
            void free(void *ptr);

        环境变量
        ISO C定义了一个函数getenv，可以用其取环境变量值.
            #include <stdlib.h>
            char *getenv(const char *name);
                返回值：指向与name关联的value的指针；若未找到，返回NULL

            #include <stdlib.h>
            int putenv(char *str);
                函数返回值：若成功，返回0；若出错，返回非0
                putenv取形式为name=value的字符串，将其放到环境表中。如果name已经存在，则先删除其原来的定义

            int setenv(const char *name, const char *value, int rewrite);
            int unsetenv(const char *name);
                两个函数返回值：若成功，返回0；若出错，返回−1

        函数 setjmp和 longjmp
            #include <setjmp.h>
            int setjmp(jmp_buf env);
                返回值：若直接调用，返回0；若从longjmp返回，则为非0
            void longjmp(jmp_buf env, int val);

*/