#include <iostream>
#include <thread>
#include <pthread.h>
using namespace std;
// day-2025-8-16
// 第十一章-线程
/*
    每个线程都包含有表示执行环境所必需的信息，其中包括进程中标识线程的线程ID、一组寄存器值、栈、调度优先级和策略、信号屏蔽字、errno变量
    以及线程私有数据。一个进程的所有信息对该进程的所有线程都是共享的，包括可执行程序的代码、程序的全局内存和堆内存、栈以及文件描述符。

    线程标识:
    #include <pthread.h>
    int pthread_equal(pthread_t tid1, pthread_t tid2);
                                    返回值：若相等，返回非0数值；否则，返回0

    线程可以通过调用pthread_self函数获得自身的线程ID。
    #include <pthread.h>
    pthread_t pthread_self(void);
                        返回值：调用线程的线程ID

    线程创建
    #include <pthread.h>
    int pthread_create(pthread_t *restrict tidp,
    const pthread_attr_t *restrict attr,
    void *(*start_rtn)(void *), void *restrict arg);
                     返回值：若成功，返回0；否则，返回错误编号
    当pthread_create成功返回时, 新创建线程的线程ID会被设置成tidp指向的内存单元。attr参数用于定制各种不同的线程属性。

    线程终止
    #include <pthread.h>
    void pthread_exit(void *rval_ptr);
    rval_ptr 参数是一个无类型指针，与传给启动例程的单个参数类似。进程中的其他线程也可以通过调用pthread_join函数访问到这个指针。

    #include <pthread.h>
    int pthread_join(pthread_t thread, void **rval_ptr);
                返回值：若成功，返回0；否则，返回错误编号
    调用线程将一直阻塞，直到指定的线程调用 pthread_exit、从启动例程中返回或者被取消。如果线程简单地从它的启动例程返回，rval_ptr就包含返回码。
    如果线程被取消，由rval_ptr指定的内存单元就设置为PTHREAD_CANCELED。

    线程取消
    #include <pthread.h>
    int pthread_cancel(pthread_t tid);
                返回值：若成功，返回0；否则，返回错误编号
    pthread_cancel并不等待线程终止，它仅仅提出请求。

    #include <pthread.h>
    int pthread_detach(pthread_t tid);
            返回值：若成功，返回0；否则，返回错误编号



    线程同步
      互斥量
        可以使用 pthread 的互斥接口来保护数据，确保同一时间只有一个线程访问数据。互斥量（mutex）从本质上说是一把锁，在访问共享资
        源前对互斥量进行设置（加锁），在访问完成后释放（解锁）互斥量。对互斥量进行加锁以后，任何其他试图再次对互斥量加锁的线程
        都会被阻塞直到当前线程释放该互斥锁。如果释放互斥量时有一个以上的线程阻塞，那么所有该锁上的阻塞线程都会变成可运行状态，第
        一个变为运行的线程就可以对互斥量加锁，其他线程就会看到互斥量依然是锁着的，只能回去再次等待它重新变为可用。

        #include <pthread.h>
        int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
        int pthread_mutex_destroy(pthread_mutex_t *mutex);
             两个函数的返回值：若成功，返回0；否则，返回错误编号要用默认的属性初始化互斥量，只需把attr设为NULL。

        #include <pthread.h>
        int pthread_mutex_lock(pthread_mutex_t *mutex);
        int pthread_mutex_trylock(pthread_mutex_t *mutex);
        int pthread_mutex_unlock(pthread_mutex_t *mutex);
            所有函数的返回值：若成功，返回0；否则，返回错误编号.如果线程不希望被阻塞，它可以使用 pthread_mutex_trylock 尝试对互斥量进行加锁。
            如果调用 pthread_mutex_trylock 时互斥量处于未锁住状态，那么 pthread_mutex_trylock将锁住互斥量，不会出现阻塞直接返回0，
            否则pthread_mutex_trylock 就会失败，不能锁住互斥量，返回EBUSY。

      避免死锁
        如果线程试图对同一个互斥量加锁两次，那么它自身就会陷入死锁状态，但是使用互斥量时，还有其他不太明显的方式也能产生死锁。
        例如，程序中使用一个以上的互斥量时，如果允许一个线程一直占有第一个互斥量，并且在试图锁住第二个互斥量时处于阻塞状态，
        但是拥有第二个互斥量的线程也在试图锁住第一个互斥量。因为两个线程都在相互请求另一个线程拥有的资源，所以这两个线程都无法向前运行，于是就产生死锁。

      函数 pthread_mutex_timedlock
      当线程试图获取一个已加锁的互斥量时，pthread_mutex_timedlock互斥量原语允许绑定线程阻塞时间。
      pthread_mutex_timedlock函数与pthread_mutex_lock 是基本等价的 ， 但是在达到超时时间值时，pthread_mutex_timedlock 不会对互斥量进行加锁，
      而是返回错误码 ETIMEDOUT。

        #include <pthread.h>
        #include <time.h>
        int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
        const struct timespec *restrict tsptr);
                返回值：若成功，返回0；否则，返回错误编号超时指定愿意等待的绝对时间

       读写锁
         读写锁（reader-writer lock）与互斥量类似，不过读写锁允许更高的并行性。互斥量要么是锁住状态，要么就是不加锁状态，
         而且一次只有一个线程可以对其加锁。读写锁可以有3种状态：读模式下加锁状态，写模式下加锁状态，不加锁状态。
         一次只有一个线程可以占有写模式的读写锁，但是多个线程可以同时占有读模式的读写锁。

        当读写锁是写加锁状态时，在这个锁被解锁之前，所有试图对这个锁加锁的线程都会被阻塞。当读写锁在读加锁状态时，所有试图以
        读模式对它进行加锁的线程都可以得到访问权，但是任何希望以写模式对此锁进行加锁的线程都会阻塞，直到所有的线程释放它们的读锁为止。

        读写锁也叫做共享互斥锁（shared-exclusive lock）。当读写锁是读模式锁住时，就可以说成是以共享模式锁住的。
        当它是写模式锁住的时候，就可以说成是以互斥模式锁住的。与互斥量相比，读写锁在使用之前必须初始化，在释放它们底层的内存之前必须销毁。

        #include <pthread.h>
        int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
        const pthread_rwlockattr_t *restrict attr);
        int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
                两个函数的返回值：若成功，返回0；否则，返回错误编号。读写锁通过调用 pthread_rwlock_init 进行初始化。

        #include <pthread.h>
        int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
        int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
        int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
                所有函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
        int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

    条件变量
    条件变量是线程可用的另一种同步机制。条件变量给多个线程提供了一个会合的场所。条件变量与互斥量一起使用时，允许线程以无竞争的方式等待特定的条件发生。
    条件本身是由互斥量保护的。线程在改变条件状态之前必须首先锁住互斥量。其他线程在获得互斥量之前不会察觉到这种改变，因为互斥量必须在锁定以后才能计算条件。

        #include <pthread.h>
        int pthread_cond_init(pthread_cond_t *restrict cond,
        const pthread_condattr_t *restrict attr);int pthread_cond_destroy(pthread_cond_t *cond);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

    我们使用pthread_cond_wait等待条件变量变为真。如果在给定的时间内条件不能满足，那么会生成一个返回错误码的变量。
        #include <pthread.h>
        int pthread_cond_wait(pthread_cond_t *restrict cond,
        pthread_mutex_t *restrict mutex);
        int pthread_cond_timedwait(pthread_cond_t *restrict cond,
        pthread_mutex_t *restrict mutex,
        const struct timespec *restrict tsptr);
                两个函数的返回值：若成功，返回0；否则，返回错误编号. 传递给pthread_cond_wait的互斥量对条件进行保护。

        #include <pthread.h>
        int pthread_cond_signal(pthread_cond_t *cond);
        int pthread_cond_broadcast(pthread_cond_t *cond);
                两个函数的返回值：若成功，返回0；否则，返回错误编号.
                在调用pthread_cond_signal或者pthread_cond_broadcast时，我们说这是在给线程或者条件发信号.

     自旋锁
        自旋锁与互斥量类似，但它不是通过休眠使进程阻塞，而是在获取锁之前一直处于忙等（自旋）阻塞状态。

        #include <pthread.h>
        int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
        int pthread_spin_destroy(pthread_spinlock_t *lock);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

        #include <pthread.h>
        int pthread_spin_lock(pthread_spinlock_t *lock);
        int pthread_spin_trylock(pthread_spinlock_t *lock);
        int pthread_spin_unlock(pthread_spinlock_t *lock);
                所有函数的返回值：若成功，返回0；否则，返回错误编号

      屏障
        屏障（barrier）是用户协调多个线程并行工作的同步机制。屏障允许每个线程等待，直到所有的合作线程都到达某一点，然后从该点继续执行。
        我们已经看到一种屏障，pthread_join函数就是一种屏障，允许一个线程等待，直到另一个线程退出。

        #include <pthread.h>
        int pthread_barrier_init(pthread_barrier_t *restrict barrier,
        const pthread_barrierattr_t *restrict attr,
        unsigned int count);
        int pthread_barrier_destroy(pthread_barrier_t *barrier);
                两个函数的返回值：若成功，返回0；否则，返回错误编号

        初始化屏障时，可以使用count参数指定，在允许所有线程继续运行之前，必须到达屏障的线程数目。

        #include <pthread.h>
        int pthread_barrier_wait(pthread_barrier_t *barrier);
                返回值：若成功，返回0或者
*/
