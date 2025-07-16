#include <iostream>
using namespace std;
// facade 模式
// day-2025-7-16
/*
    Facade 模式（外观模式） 是结构型设计模式之一，提供一个统一的接口，用来访问子系统中的一群接口，使得子系统更易使用。
        ┌────────────┐
        │        Client          │
        └────┬───────┘
                  │
                  ▼
        ┌────────────┐
        │         Facade         │  ←←←←  外观类，对外提供简化接口
        └────┬───────┘
        ┌────┴──────────────┐
        ▼                                      ▼
    ┌────────────┐      ┌────────────┐
    │ SubsystemA             │      │ SubsystemB             │  ←←←←  子系统（可多个）
    └────────────┘      └────────────┘

     优点
    简化接口：对外隐藏子系统复杂逻辑
    解耦合：客户端不依赖子系统具体实现
    更好的维护性：统一管理子系统行为

    缺点
    不易扩展子系统功能（增加子模块时需修改 Facade）
    可能成为"上帝类"或过度封装
*/
// 子系统类
class CPU
{
public:
    void start()
    {
        std::cout << "CPU 启动" << std::endl;
    }
};

class Memory
{
public:
    void load()
    {
        std::cout << "内存加载程序" << std::endl;
    }
};

class HardDrive
{
public:
    void read()
    {
        std::cout << "硬盘读取系统文件" << std::endl;
    }
};
//  外观类（Facade）
class ComputeFacade
{
public:
    ComputeFacade()
        : cpu(), mem(), hd() {}
    void Start()
    {
        cout << "启动电脑" << endl;
        cpu.start();
        mem.load();
        hd.read();
        cout << "启动成功" << endl;
    }

private:
    CPU cpu;
    Memory mem;
    HardDrive hd;
};

int main()
{
    ComputeFacade facade;
    facade.Start();
    return 0;
}