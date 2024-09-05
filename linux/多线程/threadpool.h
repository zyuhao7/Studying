#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
#define MAX_THREAD 5
typedef bool (*handler_t)(int);

class ThreadTask
{
private:
    int _data;
    handler_t _handler;

public:
    ThreadTask()
        : _data(-1),
          _handler(NULL)
    {
    }
    ThreadTask(int data, handler_t handler)
    {
        _data = data;
        _handler = handler;
    }

    void SetTask(int data, handler_t handler)
    {
        _data = data;
        _handler = handler;
    }

    void Run()
    {
        _handler(_data);
    }
};

class ThreadPool
{
private:
    int _thread_max;
    int _thread_cur;
    bool _tp_quit;
    std::queue<ThreadTask *> _task_queue;
    pthread_mutex_t _lock;
    pthread_cond_t _cond;

private:
    void LockQueue()
    {
        pthread_mutex_lock(&_lock);
    }

    void UnLockQueue()
    {
        pthread_mutex_unlock(&_lock);
    }

    void WakeUpOne()
    {
        pthread_cond_signal(&_cond);
    }

    void WakeUpAll()
    {
        pthread_cond_broadcast(&_cond);
    }

    void ThreadQuit()
    {
        _thread_cur--;
        UnLockQueue();
        pthread_exit(NULL);
    }

    void ThreadWait()
    {
        if (_tp_quit)
        {
            ThreadQuit();
        }
        pthread_cond_wait(&_cond, &_lock);
    }

    bool IsEmpty()
    {
        return _task_queue.empty();
    }

    static void *thr_start(void *arg)
    {
        ThreadPool *tp = (ThreadPool *)arg;
        while (1)
        {
            tp->LockQueue();
            while (tp->IsEmpty())
            {
                tp->ThreadWait();
            }
            ThreadTask *tt;
            tp->PopTask(&tt);
            tp->UnLockQueue();
            tt->Run();
            delete tt;
        }
        return NULL;
    }

public:
    ThreadPool(int max = MAX_THREAD)
        : _thread_max(max),
          _thread_cur(max),
          _tp_quit(false)
    {
        pthread_mutex_init(&_lock, NULL);
        pthread_cond_init(&_cond, NULL);
    }

    ~ThreadPool()
    {
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_cond);
    }

    bool PoolInit()
    {
        pthread_t tid;
        for (int i = 0; i < _thread_max; ++i)
        {
            int ret = pthread_create(&tid, NULL, thr_start, this);
            if (ret != 0)
            {
                cout << "create pool thread error!" << endl;
                return false;
            }
        }
        return true;
    }

    bool PushTask(ThreadTask *tt)
    {
        LockQueue();
        if (_tp_quit)
        {
            UnLockQueue();
            return false;
        }
        _task_queue.push(tt);
        WakeUpOne();
        UnLockQueue();
        return true;
    }

    bool PopTask(ThreadTask **tt)
    {
        *tt = _task_queue.front();
        _task_queue.pop();
        return true;
    }

    bool PoolQuit()
    {
        LockQueue();
        _tp_quit = true;
        UnLockQueue();

        while (_thread_cur > 0)
        {
            WakeUpAll();
            sleep(1);
        }
        return true;
    }
};