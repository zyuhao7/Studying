#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
// day-2025-7-28
/*
    state设计模式：
    状态模式是一种行为型设计模式，它允许对象在内部状态改变时改变其行为，使对象看起来似乎修改了其类。
    这种模式将状态相关的行为封装到独立的状态类中，通过委托而非继承来实现状态转换，从而避免了复杂的条件判断语句。
    核心角色：
    - 1.环境类（Context） ：维护一个指向当前状态对象的引用，并将与状态相关的操作委托给当前状态对象处理
    - 2.抽象状态类（State） ：定义一个接口，用于封装与环境类的一个特定状态相关的行为
    - 3.具体状态类（Concrete State） ：实现抽象状态类所定义的接口，对应环境类的一个具体状态

    TCP连接状态模型
        这个实现模拟了TCP连接的三种核心状态：
            1. 关闭状态(ClosedState) ：初始状态，连接尚未建立
            2. 已连接状态(ConnectedState) ：正常数据传输状态
            3.错误状态(ErrorState) ：处理连接异常情况

        关闭状态 → 连接 → 已连接状态 → 发送/接收数据 → 断开连接 → 关闭状态
            ↑                                                         ↓
            └────────── 错误发生 → 错误状态 → ──────┘
*/

#include <iostream>
#include <string>

// 前向声明
class TcpConnection;

// 前向声明（打破循环依赖）
class ConnectedState;
class ClosedState;

// 抽象状态类
class TcpState
{
protected:
    TcpConnection *conn;   // 指向环境类的指针
    std::string stateName; // 状态名称
public:
    TcpState(TcpConnection *connection, std::string name)
        : conn(connection), stateName(std::move(name)) {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void send(const std::string &data) = 0;
    std::string getName() const { return stateName; }
    virtual ~TcpState() = default;
};

// 环境类（先声明）
class TcpConnection
{
private:
    TcpState *currentState; // 当前状态
    std::string ip;         // 远程IP
    int port;               // 端口
public:
    TcpConnection(); // 构造函数声明（实现移至具体状态类之后）
    ~TcpConnection()
    {
        if (currentState)
            delete currentState;
    }
    void setState(TcpState *newState);
    void connect() { currentState->connect(); }
    void disconnect() { currentState->disconnect(); }
    void send(const std::string &data) { currentState->send(data); }
    std::string getAddress() const { return ip + ":" + std::to_string(port); }
    void setAddress(const std::string &ip, int port)
    {
        this->ip = ip;
        this->port = port;
    }
};

// 具体状态：关闭状态（仅声明）
class ClosedState : public TcpState
{
public:
    explicit ClosedState(TcpConnection *conn);
    void connect() override;
    void disconnect() override;
    void send(const std::string &data) override;
};

// 具体状态：已连接状态（仅声明）
class ConnectedState : public TcpState
{
public:
    explicit ConnectedState(TcpConnection *conn);
    void connect() override;
    void disconnect() override;
    void send(const std::string &data) override;
};

// ==== 成员函数实现（放在所有类声明之后）====
// ClosedState实现
ClosedState::ClosedState(TcpConnection *conn)
    : TcpState(conn, "关闭") {}

void ClosedState::connect()
{
    std::cout << "尝试连接到 " << conn->getAddress() << std::endl;
    // 现在可以安全使用ConnectedState
    conn->setState(new ConnectedState(conn));
    delete this;
}

void ClosedState::disconnect()
{
    std::cout << "错误：未连接状态无法断开" << std::endl;
}

void ClosedState::send(const std::string &data)
{
    std::cout << "错误：未连接状态无法发送数据: " << data << std::endl;
}

// ConnectedState实现
ConnectedState::ConnectedState(TcpConnection *conn)
    : TcpState(conn, "已连接") {}

void ConnectedState::connect()
{
    std::cout << "错误：已处于连接状态" << std::endl;
}

void ConnectedState::disconnect()
{
    std::cout << "断开连接" << std::endl;
    // 现在可以安全使用ClosedState
    conn->setState(new ClosedState(conn));
    delete this;
}

void ConnectedState::send(const std::string &data)
{
    std::cout << "发送数据: " << data << std::endl;
}

// TcpConnection构造函数实现
TcpConnection::TcpConnection() : currentState(nullptr), port(0)
{
    setAddress("127.0.0.1", 8080);
    setState(new ClosedState(this));
}
void TcpConnection::setState(TcpState *newState)
{
    if (currentState)
        delete currentState;
    currentState = newState;
}

// int main()
// {
//     TcpConnection conn;
//     conn.setAddress("192.168.1.1", 8080);
//     conn.setState(new ConnectedState(&conn));
//     conn.send("Hello");
//     conn.disconnect();
//     return 0;
// }