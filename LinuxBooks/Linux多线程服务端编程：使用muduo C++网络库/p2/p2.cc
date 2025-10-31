#include <iostream>
#include <muduo/base/Mutex.h>
#include <boost/noncopyable.hpp>
#include <unistd.h>
#include <muduo/base/Thread.h>
#include <set>
using namespace std;
using namespace muduo;
using namespace boost;
// day-2025-10-31
// 第二章 线程同步精要
// 互斥量 mutex
// class Request;

// class Inventory
// {
// public:
//     void add(Request *req)
//     {
//         MutexLockGuard lock(mutex_);
//         requests_.insert(req);
//     }

//     void remove(Request *req)
//     {
//         MutexLockGuard lock(mutex_);
//         requests_.erase(req);
//     }

//     void printAll() const;

// private:
//     mutable MutexLock mutex_;
//     std::set<Request *> requests_;
// };

// Inventory g_inventory;

// class Request
// {
// public:
//     void process()
//     {
//         MutexLockGuard lock(mutex_);
//         g_inventory.add(this);
//         // print();  // optional
//     }

//     void print() const
//     {
//         MutexLockGuard lock(mutex_);
//         printf("Request::print() on %p\n", this);
//     }

//     ~Request()
//     {
//         MutexLockGuard lock(mutex_);
//         sleep(1); // 模拟耗时
//         g_inventory.remove(this);
//         printf("Request %p destroyed\n", this);
//     }

// private:
//     mutable MutexLock mutex_;
// };

// // ========== printAll 修复死锁版本 ==========

// void Inventory::printAll() const
// {
//     std::set<Request *> copy;

//     {
//         MutexLockGuard lock(mutex_);
//         copy = requests_;
//     } // 释放 inventory 锁

//     for (auto req : copy)
//     {
//         req->print();
//     }

//     printf("Inventory::printAll() done.\n");
// }

// // ========== threadFunc ==========

// void threadFunc()
// {
//     Request *req = new Request();
//     req->process();
//     delete req;
// }

// int main()
// {
//     muduo::Thread t(threadFunc);
//     t.start();

//     usleep(500 * 1000); // 等线程进入析构 sleep

//     g_inventory.printAll(); // 不会死锁

//     t.join();
//     return 0;
// }
#include <muduo/base/Condition.h>
#include <deque>
#include <cassert>
// 条件变量 condition variable

// MutexLock mutex;
// Condition cond(mutex);
// std::deque<int> queue;

// int dequeue()
// {
//     MutexLockGuard lock(mutex);
//     while (queue.empty())
//     {
//         cond.wait(); // 这一步会原子地 unlock mutex 并进入等待, 不会与 enqueue死锁
//         // wait() 执行完毕会自动重新加锁
//     }
//     assert(!queue.empty());
//     int x = queue.front();
//     queue.pop_front();
//     return x;
// }

// void enqueue(int x)
// {
//     MutexLockGuard lock(mutex);
//     queue.push_back(x);
//     cond.notify(); // 通知等待的线程
// }

// class CountDownLatch : public boost::noncopyable
// {
// public:
//     explicit CountDownLatch(int count);
//     void wait()
//     {
//         MutexLockGuard lock(mutex_);
//         while (count_ > 0)
//         {
//             condition_.wait();
//         }
//     } // 等待计数值变为0

//     void countDown()
//     {
//         MutexLockGuard lock(mutex_);
//         --count_;
//         if (count_ == 0)
//             condition_.notifyAll();
//     } // 计数减一

// private:
//     mutable MutexLock mutex_;
//     Condition condition_;
//     int count_;
// };

// class Mutexlock : boost::noncopyable
// {
// public:
//     Mutexlock()
//         : holder_(0)
//     {
//         pthread_mutex_init(&mutex_, NULL);
//     }
//     ~Mutexlock()
//     {
//         assert(holder_ == 0);
//         pthread_mutex_destroy(&mutex_);
//     }

//     bool isLockedByThisThread()
//     {
//         return holder_ == CurrentThread::tid();
//     }

//     void assertLocked()
//     {
//         assert(isLockedByThisThread());
//     }

//     void lock()
//     {
//         pthread_mutex_lock(&mutex_);
//         holder_ = CurrentThread::tid();
//     }

//     void unlock()
//     {
//         holder_ = 0;
//         pthread_mutex_unlock(&mutex_);
//     }

//     pthread_mutex_t *getPthreadMutex()
//     {
//         return &mutex_;
//     }

// private:
//     pthread_mutex_t mutex_;
//     pid_t holder_;
// };

// class MutexlockGuard : public boost::noncopyable
// {
// public:
//     explicit MutexlockGuard(Mutexlock &mutex)
//         : mutex_(mutex)
//     {
//         mutex_.lock();
//     }
//     ~MutexLockGuard()
//     {
//         mutex_.unlock();
//     }

//     Mutexlock &mutex_;
// };

class condition : boost::noncopyable
{
public:
    explicit condition(MutexLock &mutex)
        : mutex_(mutex)
    {
        pthread_cond_init(&pcond_, NULL);
    }
    ~condition() { pthread_cond_destroy(&pcond_); }
    void wait()
    {
        pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
    }
    void notify()
    {
        pthread_cond_signal(&pcond_);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&pcond_);
    }

private:
    MutexLock &mutex_;
    pthread_cond_t pcond_;
};

template <typename T>
class Singleton : boost::noncopyable
{
public:
    static T &instance()
    {
        pthread_once(&ponce_, &Singleton::init);
        return *value_;
    }

private:
    Singleton();
    ~Singleton();
    static void init()
    {
        value_ = new T();
    }

private:
    static pthread_once_t ponce_;
    static T *value_;
};

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T *Singleton<T>::value_ = NULL;



int main()
{
}