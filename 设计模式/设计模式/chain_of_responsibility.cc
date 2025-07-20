#include <iostream>
#include <memory>
#include <string>
/*
 * 责任链设计模式(Chain of Responsibility)
 * 意图：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
 * 将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
 *
 * 应用场景：
 * 1. 多个对象可以处理同一请求，但具体由哪个对象处理在运行时动态决定
 * 2. 不明确指定接收者的情况下，向多个对象中的一个提交请求
 * 3. 可动态指定一组对象处理请求
 */

// 抽象处理者(Handler)
class Handler
{
protected:
    std::shared_ptr<Handler> next_handler_; // 下一个处理者

public:
    Handler()
        : next_handler_(nullptr) {}
    virtual ~Handler() = default;

    // 设置下一个处理者
    void set_next(std::shared_ptr<Handler> handler)
    {
        next_handler_ = handler;
    }

    // 处理请求的纯虚函数
    virtual void handle_request(int request) = 0;
};

// 具体处理者1：处理 1-10 的请求
class ConcreteHandler1 : public Handler
{
public:
    void handle_request(int request) override
    {
        if (request >= 1 && request <= 10)
        {
            std::cout << "ConcreteHandler1 处理请求: " << request << std::endl;
        }
        else if (next_handler_)
        {
            // 无法处理，传递给下一个处理者
            next_handler_->handle_request(request);
        }
        else
        {
            std::cout << "没有处理者能处理请求: " << request << std::endl;
        }
    }
};

// 具体处理者2：处理 11-20 的请求
class ConcreteHandler2 : public Handler
{
public:
    void handle_request(int request) override
    {
        if (request >= 11 && request <= 20)
        {
            std::cout << "ConcreteHandler2 处理请求: " << request << std::endl;
        }
        else if (next_handler_)
        {
            next_handler_->handle_request(request);
        }
        else
        {
            std::cout << "没有处理者能处理请求: " << request << std::endl;
        }
    }
};

// 具体处理者3：处理 21-30 的请求
class ConcreteHandler3 : public Handler
{
public:
    void handle_request(int request) override
    {
        if (request >= 21 && request <= 30)
        {
            std::cout << "ConcreteHandler3 处理请求: " << request << std::endl;
        }
        else if (next_handler_)
        {
            next_handler_->handle_request(request);
        }
        else
        {
            std::cout << "没有处理者能处理请求: " << request << std::endl;
        }
    }
};

// 客户端代码
// int main()
// {
//     // 创建具体处理者
//     auto handler1 = std::make_shared<ConcreteHandler1>();
//     auto handler2 = std::make_shared<ConcreteHandler2>();
//     auto handler3 = std::make_shared<ConcreteHandler3>();

//     // 构建责任链：handler1 -> handler2 -> handler3
//     handler1->set_next(handler2);
//     handler2->set_next(handler3);

//     // 测试不同的请求
//     handler1->handle_request(5);  // 应由handler1处理
//     handler1->handle_request(15); // 应由handler2处理
//     handler1->handle_request(25); // 应由handler3处理
//     handler1->handle_request(35); // 没有处理者能处理

//     return 0;
// }