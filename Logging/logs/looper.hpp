#ifndef __M_LOOP_H__
#define __M_LOOP_H__
#include "util.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include "buffer.hpp"

// 异步任务处理器(AsyncLooper)
namespace log
{
    class AsyncLooper
    {
    public:
        using Functor = std::function<void(Buffer &buffer)>;
        using ptr = std::shared_ptr<AsyncLooper>;
        AsyncLooper(const Functor &cb) : _running(true),
                                         _looper_callback(cb),
                                         _thread(std::thread(&AsyncLooper::worker_loop, this))
        {
        }
        ~AsyncLooper() { stop(); }
        void stop()
        {
            _running = false;
            _pop_cond.notify_all();
            _thread.join();
        }
        void push(const std::string &msg)
        {
            if (_running == false)
                return;
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _push_cond.wait(lock, [&]
                                { return _tasks_push.writeAbleSize() >= msg.size(); });
                _tasks_push.push(msg.c_str(), msg.size());
            }
            _pop_cond.notify_all();
        }

    private:
        void worker_loop()
        {
            while (1)
            {
                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    if (_running == false && _tasks_push.empty())
                    {
                        return;
                    }
                    _pop_cond.wait(lock, [&]
                                   { return !_tasks_push.empty() || !_running; });
                    _tasks_push.swap(_tasks_pop);
                }
                _push_cond.notify_all();
                _looper_callback(_tasks_pop);
                _tasks_pop.reset();
            }
            return;
        }

    private:
        Functor _looper_callback;

    private:
        std::mutex _mutex;
        std::atomic<bool> _running;
        std::condition_variable _push_cond;
        std::condition_variable _pop_cond;
        Buffer _tasks_push;
        Buffer _tasks_pop;
        std::thread _thread;
    };
}
#endif