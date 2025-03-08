#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <iostream>
#include <queue>
#include <mutex>
#include <future>
#include <vector>
#include <atomic>
#include <condition_variable>

// day-2025-3-8 线程池
// 线程池是一种多线程处理形式，它处理过程中将任务添加到队列，然后再创建线程后自动启动这些任务。
class ThreadPool
{
public:
    using Task = std::packaged_task<void()>;

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete; // 线程池不允许拷贝构造和拷贝赋值.

    // 静态实例
    static ThreadPool &instance()
    {
        static ThreadPool ins;
        return ins;
    }

    ~ThreadPool()
    {
        stop();
    }

    template <typename F, typename... Args>
    auto commit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        using RetType = decltype(f(args...));
        if (stop_.load())
        {
            return std::future<RetType>{};

            // auto promise = std::make_shared<std::promise<RetType>>();
            // promise->set_value();
            // return promise->get_future();
        }

        auto task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<RetType> ret = task->get_future();
        {
            std::lock_guard<std::mutex> cv_mt(cv_mt_);
            tasks_.emplace([task]()
                           { (*task)(); });
        }
        cv_lock_.notify_one();
        return ret;
    }

    int idleThreadCount()
    {
        return thread_num_;
    }

private:
    ThreadPool(unsigned int num = 5)
        : stop_(false)
    {
        if (num < 1)
            thread_num_ = 1;
        else
            thread_num_ = num;
        start();
    }
    // do work
    void start()
    {
        for (int i = 0; i < thread_num_; ++i)
        {
            pool_.emplace_back([this]()
                               { 
                                while (!this->stop_.load())
                                {
                                    Task task;
                                    {
                                        std::unique_lock<std::mutex> cv_mt(cv_mt_);
                                        this->cv_lock_.wait(cv_mt, [this]()
                                                            { 
                                                                return this->stop_.load() || !this->tasks_.empty(); 
                                                            });
                                        if(this->tasks_.empty())
                                            return;
                                        task = std::move(this->tasks_.front());
                                        this->tasks_.pop();
                                    }
                                    this->thread_num_--;
                                    task();
                                    this->thread_num_++;
                                } });
        }
    }

    void stop()
    {
        stop_.store(true);     // 先将线程结束标志位置为 true.
        cv_lock_.notify_all(); // 唤醒阻塞的条件变量处理 task 或者返回.
        for (auto &td : pool_)
        {
            if (td.joinable())
            {
                std::cout << "join thread " << td.get_id() << std::endl;
                td.join();
            }
        }
    }
    std::mutex cv_mt_;
    std::condition_variable cv_lock_;
    std::atomic_bool stop_;
    std::atomic_int thread_num_;
    std::queue<Task> tasks_;
    std::vector<std::thread> pool_;
};

#endif