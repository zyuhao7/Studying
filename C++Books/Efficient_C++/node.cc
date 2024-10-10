#include <iostream>
#include <string>
#include <mutex>
using namespace std;
// day-2024-10-10
// 第一章 跟踪实例
// 第二章 构造函数和析构函数

// 线程同步的方式:
// 1. 信号量(semaphore)、 2. 互斥(mutex) 3. 临界区 (critical section)

// 临界区是指某一时间只能由一个线程执行的一个代码段.
/*
    get_the_lock(CSLock);
    {   // 临界区开始
        // 被保护的计算
    }   // 临界区结束
    release_the_lock(CSLock);

class Lock
{
public:
    Lock(pthread_mutex_t &key)
        : theKey(key)
    {
        pthread_mutex_lock(&theKey);
    }
    ~Lock()
    {
        pthread_mutex_unlock(&theKey);
    }

private:
    pthread_mutex_t &theKey;
};



#include <unistd.h>
#include <pthread.h>

class BaseLock
{
public:
    // LogSource 对象在下文解释
    BaseLock(pthread_mutex_t &key, LogSource &lsrc) {}
    virtual ~BaseLock() {}
};

class MutexLock : public BaseLock
{
public:
    MutexLock(pthread_mutex_t &key, LogSource &lsrc);
    ~MutexLock();

private:
    pthread_mutex_t &theKey;
    LogSource &src;
};

MutexLock::MutexLock(pthread_mutex_t &akey, LogSource &source)
    : BaseLock(aKey, source),
      theKey(aKey),
      src(source)
{
    pthread_mutex_lock(&theKey);
#if defined(DEBUG)
    cout << "MutexLock " << &aKey << "created at " << src.file() << "line" << src.line() << endl;
#endif
}

MutexLock::~MutexLock()
{
    pthread_mutex_unlock(&theKey);
#if defined(DEBUG)
    cout << "MutexLock " << &aKey << "destroyed at " << src.file() << "line" << src.line() << endl;
#endif
}

// LogSource
class BaseLogSource
{
public:
    BaseLogSource() {}
    virtual ~BaseLogSource() {}
};

class LogSource : public BaseLogSource
{
public:
    LogSource(const char *name, int num)
        : filename(name),
          lineNum(num)
    {
    }
    ~LogSource() {}

private:
    char *filename;
    int lineNum;
};

    // 假设 sharedCounter 是一个可以由多个线程访问且需要序列化的整数变量.
    {
        MutexLock myLock(theKey, LogSource(__FILE__, __LINE__));
        sharedCounter++;
        // 这个版本涉及到四个构造和析构, BaseLock、MutexLock、BaseLogSource、LogSource.

        pthread_mutex_lock(&theKey);
        sharedCounter++;
        pthread_mutex_unlock(&theKey);

    }
*/

int main()
{

    return 0;
}
