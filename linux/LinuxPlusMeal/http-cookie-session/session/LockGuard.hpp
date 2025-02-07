#pragma once

#include <pthread.h>

// 不定义锁，默认认为外部会给我们传入锁对象
class Mutex
{
public:
    Mutex(pthread_mutex_t *lock):_lock(lock)
    {}
    void Lock()
    {
        pthread_mutex_lock(_lock);
    }
    void Unlock()
    {
        pthread_mutex_unlock(_lock);
    }
    ~Mutex()
    {}

private:
    pthread_mutex_t *_lock;
};

class LockGuard
{
public:
    LockGuard(pthread_mutex_t *lock): _mutex(lock)
    {
        _mutex.Lock();
    }
    ~LockGuard()
    {
        _mutex.Unlock();
    }
private:
    Mutex _mutex;
};