#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include "../co_routine.h"
class CoroutinePool
{
public:
    using Task = std::function<void()>;
    using HighWatermarkCallback = std::function<void(size_t)>;
    CoroutinePool(int coroutineNum, size_t highWaterMark);

    void start();
    void addTask(Task task);

    void setHighWatermarkCallback(HighWatermarkCallback cb);
    static void *coroutineFunc(void *arg);

private:
    std::queue<Task> taskQueue_;
    std::mutex mutex_;
    std::condition_variable_any cond_;

    std::vector<stCoRoutine_t *> coroutines_;
    int coroutineNum_;

    HighWatermarkCallback highWaterMarkCallback_;
    size_t highWaterMark_;

    bool running_;
};
