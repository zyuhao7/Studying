#include "coroutine_pool.h"
#include "../co_routine.h"
#include <iostream>

CoroutinePool::CoroutinePool(int coroutineNum, size_t highWaterMark)
    : coroutineNum_(coroutineNum),
      highWaterMark_(highWaterMark),
      running_(false) {}

void CoroutinePool::start()
{
    running_ = true;
    for (int i = 0; i < coroutineNum_; ++i)
    {
        stCoRoutine_t *co = nullptr;
        co_create(&co, nullptr, &CoroutinePool::coroutineFunc, this);
        coroutines_.push_back(co);
        co_resume(co);
    }
}

void *CoroutinePool::coroutineFunc(void *arg)
{
    CoroutinePool *pool = static_cast<CoroutinePool *>(arg);
    co_enable_hook_sys(); // 启用hook

    while (pool->running_)
    {
        Task task;
        {
            std::unique_lock<std::mutex> lock(pool->mutex_);
            while (pool->taskQueue_.empty())
            {
                pool->cond_.wait(lock);
            }
            task = std::move(pool->taskQueue_.front());
            pool->taskQueue_.pop();
        }
        if (task)
            task();
    }
    return nullptr;
}

void CoroutinePool::addTask(Task task)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        taskQueue_.push(std::move(task));

        if (taskQueue_.size() >= highWaterMark_ && highWaterMarkCallback_)
        {
            highWaterMarkCallback_(taskQueue_.size());
        }
    }
    cond_.notify_one(); // 唤醒协程
}

void CoroutinePool::setHighWatermarkCallback(HighWatermarkCallback cb)
{
    highWaterMarkCallback_ = std::move(cb);
}