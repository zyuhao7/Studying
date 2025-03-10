#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging
{
    // 1. 消息基类, 队列中存储的项目
    struct message_base
    {
        virtual ~message_base() {}
    };

    // 2. 每种消息都具有特化类型
    template <typename Msg>
    struct wrapped_message : message_base
    {
        Msg contents;
        explicit wrapped_message(Msg const &contents_)
            : contents(contents_) {}
    };

    // 3. 消息队列
    class queue
    {
        std::mutex mtx_;
        std::condition_variable cv_;
        // 4. 以内部队列存储 message_base型 共享指针
        std::queue<std::shared_ptr<message_base>> que_;

    public:
        template <typename T>
        void push(T const &msg)
        {
            std::lock_guard<std::mutex> lock(mtx_);
            // 5. 包装发送的消息, 并存储相关的指针
            que_.push(std::make_shared<wrapped_message<T>>(msg));
            cv_.notify_all();
        }

        std::shared_ptr<message_base> wait_and_pop()
        {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock, [&]()
                     { return !que_.empty(); });
            auto t = que_.front();
            que_.pop();
            return t;
        }
    };

}