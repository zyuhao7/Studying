#include <iostream>
#include <string>
// day-2025-7-30
/*
    1. 模式定义
        模板方法模式是一种行为型设计模式，它定义了一个算法的骨架，将一些步骤延迟到子类中。
        模板方法模式使得子类可以在不改变算法结构的情况下，重新定义算法的某些步骤。
    2. 核心角色
        抽象类（Abstract Class） ：定义算法骨架（模板方法）和 primitive 操作（抽象方法）
        具体子类（Concrete Class） ：实现抽象类中的抽象方法，完成特定步骤
        模板方法（Template Method） ：在抽象类中定义，调用 primitive 操作和固定步骤
    3. 模板方法模式优点
        - 代码复用 ：将公共代码提取到父类，减少重复
        - 反向控制 ：父类控制流程，子类提供实现（好莱坞原则："不要调用我们，我们会调用你"）
        - 扩展性 ：子类可通过覆盖方法扩展功能
        - 封装不变部分 ：将算法骨架固定，变化部分延迟到子类
*/

// 抽象类：定义模板方法和抽象步骤
class AbstractClass
{
public:
    // 模板方法：定义算法骨架
    void templateMethod() const
    {
        step1();
        step2();
        step3();
        if (hook())
        { // 可选钩子
            specialStep();
        }
    }

    virtual ~AbstractClass() = default;

protected:
    // 抽象步骤：必须由子类实现
    virtual void step2() const = 0;
    virtual void step3() const = 0;

    // 具体步骤：父类已实现
    void step1() const
    {
        std::cout << "执行固定步骤 1\n";
    }

    // 钩子方法：子类可选择覆盖
    virtual bool hook() const
    {
        return true;
    }

    // 特殊步骤：仅在钩子条件满足时执行
    virtual void specialStep() const
    {
        std::cout << "执行特殊步骤\n";
    }
};

// 具体子类 A
class ConcreteClassA : public AbstractClass
{
protected:
    void step2() const override
    {
        std::cout << "执行子类 A 步骤 2\n";
    }

    void step3() const override
    {
        std::cout << "执行子类 A 步骤 3\n";
    }

    // 覆盖钩子方法
    bool hook() const override
    {
        return false; // 不执行特殊步骤
    }
};

// 具体子类 B
class ConcreteClassB : public AbstractClass
{
protected:
    void step2() const override
    {
        std::cout << "执行子类 B 步骤 2\n";
    }

    void step3() const override
    {
        std::cout << "执行子类 B 步骤 3\n";
    }

    // 使用默认钩子（true），执行特殊步骤
    void specialStep() const override
    {
        std::cout << "执行子类 B 特殊步骤\n";
    }
};

// 客户端代码
int main()
{
    AbstractClass *classA = new ConcreteClassA();
    std::cout << "=== 运行子类 A ===\n";
    classA->templateMethod();

    std::cout << "\n=== 运行子类 B ===\n";
    AbstractClass *classB = new ConcreteClassB();
    classB->templateMethod();

    delete classA;

    delete classB;
    return 0;
}