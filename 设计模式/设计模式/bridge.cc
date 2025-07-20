#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
 * Bridge设计模式实现 - 将抽象部分与实现部分分离，使它们可以独立变化
 * 日期: 2025-7-13
 *
 * 结构说明:
 * 1. 抽象层(Abstraction): Window类层次结构
 *    - Window: 抽象窗口基类
 *    - DialogWindow: 对话框窗口(具体抽象)
 *    - IconWindow: 图标窗口(具体抽象)
 *
 * 2. 实现层(Implementation): WindowImpl类层次结构
 *    - WindowImpl: 窗口实现基类
 *    - WindowsImpl: Windows系统实现
 *    - LinuxImpl: Linux系统实现
 *
 * 3. 关联关系: Window通过组合方式持有WindowImpl对象
 */

/*
 * 窗口实现接口(Implementor)
 * 定义实现类的接口，该接口不一定要与抽象类的接口完全一致
 * 实际上这两个接口可以完全不同，一般来说，实现接口只提供基本操作
 */
class WindowImpl
{
public:
    /* 绘制文本 */
    virtual void DrawText(const std::string &text) = 0;

    /* 绘制矩形 */
    virtual void DrawRect(int x, int y, int w, int h) = 0;

    /* 虚析构函数，确保派生类析构函数被正确调用 */
    virtual ~WindowImpl() {}
};

/*
 * Windows系统窗口实现(Concrete Implementor)
 * 实现WindowImpl接口，针对Windows系统提供具体实现
 */
class WindowsImpl : public WindowImpl
{
public:
    /* 在Windows系统上绘制文本 */
    void DrawText(const std::string &text) override
    {
        std::cout << "Windows: Drawing text - " << text << std::endl;
    }

    /* 在Windows系统上绘制矩形 */
    void DrawRect(int x, int y, int w, int h) override
    {
        std::cout << "Windows: Drawing rectangle at(" << x << "," << y << ") size " << w << " * " << h << std::endl;
    }
};

/*
 * Linux系统窗口实现(Concrete Implementor)
 * 实现WindowImpl接口，针对Linux系统提供具体实现
 */
class LinuxImpl : public WindowImpl
{
public:
    /* 在Linux系统上绘制文本 */
    void DrawText(const std::string &text) override
    {
        std::cout << "Linux: Drawing text - " << text << std::endl;
    }

    /* 在Linux系统上绘制矩形 */
    void DrawRect(int x, int y, int w, int h) override
    {
        std::cout << "Linux: Drawing rectangle at(" << x << "," << y << ") size " << w << " * " << h << std::endl;
    }
};

/*
 * 窗口抽象类(Abstraction)
 * 定义抽象接口，维护一个指向实现类对象的指针
 */
class Window
{
protected:
    WindowImpl *impl_; // 指向实现类的指针

public:
    /* 构造函数，传入具体实现 */
    Window(WindowImpl *impl)
        : impl_(impl)
    {
    }

    /* 虚析构函数 */
    virtual ~Window() {}

    /* 绘制窗口的抽象方法 */
    virtual void Draw() = 0;
};

/*
 * 对话框窗口(Refined Abstraction)
 * 扩展Window接口，实现对话框窗口的具体功能
 */
class DialogWindow : public Window
{
public:
    /* 构造函数，传入具体实现 */
    DialogWindow(WindowImpl *impl)
        : Window(impl) {}

    /* 绘制对话框窗口 */
    void Draw() override
    {
        std::cout << "[DialogWindow Drawing Start]" << std::endl;
        impl_->DrawText("this is a dialog"); // 绘制文本
        impl_->DrawRect(10, 10, 200, 100);   // 绘制矩形
        std::cout << "[DialogWindow Drawing End]" << std::endl;
    }
};

/*
 * 图标窗口(Refined Abstraction)
 * 扩展Window接口，实现图标窗口的具体功能
 */
class IconWindow : public Window
{
public:
    /* 构造函数，传入具体实现 */
    IconWindow(WindowImpl *impl)
        : Window(impl)
    {
    }

    /* 绘制图标窗口 */
    void Draw() override
    {
        std::cout << "[IconWindow Drawing Start]" << std::endl;
        impl_->DrawRect(0, 0, 50, 50); // 绘制矩形
        impl_->DrawText("Icon");       // 绘制文本
        std::cout << "[IconWindow Drawing End]" << std::endl;
    }
};

/*
 * 主函数示例
 * 演示如何使用Bridge模式：
 * 1. 创建具体实现对象(WindowsImpl/LinuxImpl)
 * 2. 创建抽象对象(DialogWindow/IconWindow)并传入实现对象
 * 3. 调用抽象对象的Draw方法
 */
// int main()
// {
//    // 创建Windows实现
//    WindowImpl* winImpl = new WindowsImpl();
//    // 创建对话框窗口并关联Windows实现
//    Window* dialogWin = new DialogWindow(winImpl);
//    dialogWin->Draw();
//
//    // 创建Linux实现
//    WindowImpl* linuxImpl = new LinuxImpl();
//    // 创建图标窗口并关联Linux实现
//    Window* iconWin = new IconWindow(linuxImpl);  // 修复原代码中的bug，应传入linuxImpl而非winImpl
//    iconWin->Draw();
//
//    // 释放资源
//    delete dialogWin;
//    delete winImpl;
//    delete iconWin;
//    delete linuxImpl;
//
//    return 0;
// }