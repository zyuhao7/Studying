#include <iostream>
#include <string>
#include <vector>
// day-2025-7-24
/*
   中介者设计模式（Mediator Pattern）详解
    中介者模式是一种行为型设计模式，它通过引入一个中介者对象来封装一系列对象之间的交互，
    从而减少对象之间的直接耦合，使系统更易于维护和扩展。

    - 抽象中介者（Mediator） ：定义同事对象之间交互的接口
    - 具体中介者（ConcreteMediator） ：实现中介者接口，协调各个同事对象
    - 抽象同事类（Colleague） ：定义同事对象的接口，包含中介者引用
    - 具体同事类（ConcreteColleague） ：实现同事接口，通过中介者与其他同事交互
  适用场景
    - 多个对象之间存在复杂交互关系
    - 系统结构混乱，对象耦合度高
    - 需要通过一个中心控制点协调多个对象行为
  优点
    - 减少对象间直接耦合，遵循迪米特法则
    - 集中控制交互逻辑，便于维护
    - 可独立扩展中介者和同事类
*/

// 前向声明
class Colleague;

// 抽象中介者
class Mediator
{
public:
    virtual void registerColleague(Colleague *colleague) = 0;
    virtual void sendMessage(const std::string &message, Colleague *sender) = 0;
    virtual ~Mediator() = default;
};

// 抽象同事类
class Colleague
{
protected:
    Mediator *mediator;
    std::string name;

public:
    Colleague(Mediator *med, const std::string &n)
        : mediator(med), name(n) {}
    virtual void send(const std::string &message) = 0;
    virtual void receive(const std::string &message) = 0;
    virtual std::string getName() const { return name; }
    virtual ~Colleague() = default;
};

// 具体中介者：聊天室
class ChatRoom : public Mediator
{
private:
    std::vector<Colleague *> colleagues;

public:
    void registerColleague(Colleague *colleague) override
    {
        colleagues.push_back(colleague);
    }

    void sendMessage(const std::string &message, Colleague *sender) override
    {
        // 转发消息给除发送者外的所有同事
        for (auto colleague : colleagues)
        {
            if (colleague != sender)
            {
                colleague->receive(sender->getName() + ": " + message);
            }
        }
    }
};

// 具体同事类：用户
class User : public Colleague
{
public:
    User(Mediator *med, const std::string &name)
        : Colleague(med, name) {}

    void send(const std::string &message) override
    {
        std::cout << name << " 发送消息: " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    void receive(const std::string &message) override
    {
        std::cout << name << " 收到消息: " << message << std::endl;
    }
};

// 客户端代码
int main()
{
    // 创建中介者
    Mediator *chatRoom = new ChatRoom();

    // 创建同事对象
    Colleague *alice = new User(chatRoom, "Alice");
    Colleague *bob = new User(chatRoom, "Bob");
    Colleague *charlie = new User(chatRoom, "Charlie");

    // 注册同事到中介者
    chatRoom->registerColleague(alice);
    chatRoom->registerColleague(bob);
    chatRoom->registerColleague(charlie);

    // 发送消息
    alice->send("大家好！");
    bob->send("欢迎加入聊天室！");
    charlie->send("中介者模式真有趣！");

    // 释放资源
    delete alice;
    delete bob;
    delete charlie;
    delete chatRoom;

    return 0;
}
