
#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <pthread.h>
#include <functional>
#include "Log.hpp"
#include "Thread.hpp"
#include "LockGuard.hpp"

static const int defaultnum = 5;

class ThreadData
{
public:
    ThreadData(const std::string &name)
     : threadname(name)
    {
    }
    ~ThreadData()
    {
    }

public:
    std::string threadname;
};

template <class T>
class ThreadPool
{
private:
    ThreadPool(int thread_num = defaultnum) 
    : _thread_num(thread_num)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
        // 构建指定个数的线程
        for (int i = 0; i < _thread_num; i++)
        {
            // 待优化
            std::string threadname = "thread-";
            threadname += std::to_string(i + 1);

            ThreadData td(threadname);

            // Thread<ThreadData> t(threadname,
            //                      std::bind(&ThreadPool<T>::ThreadRun, this, std::placeholders::_1), td);
            // _threads.push_back(t);
            
            _threads.emplace_back(threadname,
                                  std::bind(&ThreadPool<T>::ThreadRun, this,
                                            std::placeholders::_1),
                                  td);
            lg.LogMessage(Info, "%s is created...\n", threadname.c_str());
        }
    }
    ThreadPool(const ThreadPool<T> &tp) = delete;
    const ThreadPool<T> &operator=(const ThreadPool<T>) = delete;

public:
    // 有线程安全问题的
    static ThreadPool<T> *GetInstance()
    {
        if (instance == nullptr)
        {
            LockGuard lockguard(&sig_lock);
            if (instance == nullptr)
            {
                lg.LogMessage(Info, "创建单例成功...\n");
                instance = new ThreadPool<T>();
                instance->Start();
            }
        }

        return instance;
    }
    bool Start()
    {
        // 启动
        for (auto &thread : _threads)
        {
            thread.Start();
            lg.LogMessage(Info, "%s is running ...\n", thread.ThreadName().c_str());
        }

        return true;
    }
    void ThreadWait(const ThreadData &td)
    {
        lg.LogMessage(Debug, "no task, %s is sleeping...\n", td.threadname.c_str());
        pthread_cond_wait(&_cond, &_mutex);
    }
    void ThreadWakeup()
    {
        pthread_cond_signal(&_cond);
    }
    void checkSelf()
    {
        // 1. _task_num > _task_num_high_water && _thread_num < _thread_num_high_water
        // 创建更多的线程，并且更新_thread_num

        // 2. _task_num == _task_num_low_water && _thread_num >= _thread_num_high_water
        // 把自己退出了，并且更新_thread_num
    }
    void ThreadRun(ThreadData &td)
    {
        while (true)
        {
            // checkSelf()
            // checkSelf();
            // 取任务
            T t;
            {
                LockGuard lockguard(&_mutex);
                while (_q.empty())
                {
                    ThreadWait(td);
                    lg.LogMessage(Debug, "thread %s is wakeup\n", td.threadname.c_str());
                }
                t = _q.front();
                _q.pop();
            }
            // 处理任务
            t();
            // lg.LogMessage(Debug, "%s handler task %s done, result is : %s\n",
            //               td.threadname, t.PrintTask().c_str(), t.PrintResult().c_str());
        }
    }
    void Push(T &in)
    {
        LockGuard lockguard(&_mutex);
        _q.push(in);
        ThreadWakeup();
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

    // for debug
    void Wait()
    {
        for (auto &thread : _threads)
        {
            thread.Join();
        }
    }

private:
    std::queue<T> _q;
    std::vector<Thread<ThreadData>> _threads;
    int _thread_num;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    static ThreadPool<T> *instance;
    static pthread_mutex_t sig_lock;
    // 扩展1：
    // int _thread_num;
    // int _task_num;

    // int _thread_num_low_water;  // 3
    // int _thread_num_high_water; // 10
    // int _task_num_low_water;    // 0
    // int _task_num_high_water;   // 30

    // 扩展2: 多进程+多线程

    // int number{1};
};

template <class T>
ThreadPool<T> *ThreadPool<T>::instance = nullptr;
template <class T>
pthread_mutex_t ThreadPool<T>::sig_lock = PTHREAD_MUTEX_INITIALIZER;