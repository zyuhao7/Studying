#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <pthread.h>

// 设计方的视角
// typedef std::function<void()> func_t;
template <class T>
using func_t = std::function<void(T &)>;

template <class T>
class Thread
{
public:
    Thread(const std::string &threadname, func_t<T> func, T &data)
        : _tid(0), _threadname(threadname), _isrunning(false), _func(func), _data(data)
    {
    }

    static void *ThreadRoutine(void *args) // 类内方法，
    {
        // (void)args; // 仅仅是为了防止编译器有告警
        Thread *ts = static_cast<Thread *>(args);

        ts->_func(ts->_data);

        return nullptr;
    }

    bool Start()
    {
        int n = pthread_create(&_tid, nullptr, ThreadRoutine, this /*?*/);
        if (n == 0)
        {
            _isrunning = true;
            return true;
        }
        else
            return false;
    }
    bool Join()
    {
        if (!_isrunning)
            return true;
        int n = pthread_join(_tid, nullptr);
        if (n == 0)
        {
            _isrunning = false;
            return true;
        }
        return false;
    }
    std::string ThreadName()
    {
        return _threadname;
    }
    bool IsRunning()
    {
        return _isrunning;
    }
    ~Thread()
    {
    }

private:
    pthread_t _tid;
    std::string _threadname;
    bool _isrunning;
    func_t<T> _func;
    T _data;
};