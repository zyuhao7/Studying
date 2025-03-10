#pragma once
#include "message.h"
//  消息派发类

namespace messaging
{
    // 1. 示意关闭队列的消息
    class close_queue
    {
    };

    class dispatcher
    {
    private:
        queue *q;
        bool chained;
        // 2. dispatcher实例不可复制
        dispatcher(dispatcher const &) = delete;
        dispatcher &operator=(dispatcher const &) = delete;

        // 3. 准许 TemplateDispatcher的实例访问内部数据
        template <
            typename Dispatcher,
            typename Msg,
            typename Func>
        friend class TemplateDispatcher;

        void wait_and_dispatcher()
        {
            // 4. 无限循环, 等待消息并发送消息
            for (;;)
            {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }
        // 5. dispatch() 判断消息是否属于 close_queue 类型, 若是则抛异常
        bool dispatch(std::shared_ptr<message_base> const &msg)
        {
            if (dynamic_cast<wrapped_message<close_queue> *>(msg.get()))
            {
                throw close_queue();
            }
            return false;
        }

    public:
        // 6. dispatcher是可移动的实例
        dispatcher(dispatcher &&other)
            : q(other.q),
              chained(other.chained)
        {
            // 7. 上游的消息分发者不会等待消息
            other.chained = true;
        }
        explicit dispatcher(queue *q_)
            : q(q_),
              chained(chained)
        {
        }
        // 8 根据 TemplateDispatcher 处理某种具体类型的消息
        template <typename Message, typename Func, typename dispatcher>
        TemplateDispatcher<dispatcher, Message, Func>
        handle(Func &&f, std::string info_msg)
        {
            std::cout << "Dispatcher handle msg is " << info_msg << std::endl;
            return TemplateDispatcher<dispatcher, Message, Func>(
                q, this, std::forward<Func>(f), info_msg);
        }

        // 9. 析构函数可能抛异常
        ~dispatcher() noexcept(false)
        {
            if (!chained)
            {
                wait_and_dispatcher();
            }
        }
    };

    class sender
    {
        // 1. sender 类中包装了消息队列的指针
        queue *q;

    public:
        // 2. 以默认方式构造的 sender类内部不含队列
        sender()
            : q(nullptr)
        {
        }
        // 3. 根据队列指针构造 sender 实例
        sender(queue *q_)
            : q(q_)
        {
        }
        template <typename Message>
        void send(Message const &msg)
        {
            if (q)
            {
                // 4. 发送消息会向队列添加消息
                q->push(msg);
            }
        }
    };

    class receiver
    {
        // 1 receiver 实例完全拥有消息队列
        queue q;

    public:
        // 2. receiver 对象准许隐式类型转换为 sender 对象, 前者拥有的队列被后者引用
        opeator sender()
        {
            return sender(&q);
        }
        // 3. 队列上的等待行为会创建一个 dispatcher 对象
        dispatcher wait()
        {
            return dispatcher(&q);
        }
    };

    template <typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher
    {
        std::string _msg;
        queue *q;
        PreviousDispatcher *prev;
        Func f;
        bool chained;
        TemplateDispatcher(TemplateDispatcher const &) = delete;
        TemplateDispatcher &operator=(TemplateDispatcher const &) = delete;

        template <typename Dispatcher, typename OtherMsg, typename OtherFunc>
        // 1. 根据类模板 TemplateDispatcher<> 具现化而成的各种类型互为友元
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for (;;)
            {
                auto msg = q->wait_and_pop();
                // 2. 如果消息已妥善处理, 则跳出无限循环
                if (dispatch(msg))
                    break;
            }
        }
        bool dispatch(std::shared_ptr<message_base> const &msg)
        {
            // 3. 查验消息类型并调用相应的处理函数
            if (wrapped_message<Msg> *wrapper = dynamic_cast<wrapped_message<Msg> *>(msg.get()))
            {
                f(wrapper->contents);
                return true;
            }
            else
            {
                // 4. 衔接前一个 dispatcher 对象, 形成连锁调用
                return prev->dispatch(msg);
            }
        }

    public:
        TemplateDispatcher(TemplateDispatcher &&other)
            : q(other.q),
              prev(other.prev),
              f(std::move(other.f)),
              chained(other.chained),
              _msg(other._msg)
        {
            std::cout << "TemplateDispatcher copy construct msg is " << _msg << std::endl;
            other.chained = true;
        }

        TemplateDispatcher(queue *q_, PreviousDispatcher *prev_, Func &&f_, std::string msg)
            : q(q_),
              prev(prev_),
              f(std::forward<Func>(f)),
              chained(false),
              _msg(msg)
        {
            std::cout << "TemplateDispatcher copy construct msg is " << _msg << std::endl;
            prev_->chained = true;
        }

        // 5. 按衔接成链的方式引入更多处理函数
        template <typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
        handle(OtherFunc &&of, std::string info_msg)
        {
            return TemplateDispatcher<
                TemplateDispatcher, OtherMsg, OtherFunc>(
                q, this, std::forward<OtherFunc>(of), info_msg);
        }

        // 6. 该类的析构函数的异常行为描述也是 noexcept（false)
        ~TemplateDispatcher() noexcept(false)
        {
            if (!chained)
            {
                wait_and_dispatch();
            }
            std::cout << "~TemplateDispatcher  msg is " << _msg << std::endl;
        }
    };
}