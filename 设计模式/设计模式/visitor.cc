#include <iostream>
#include <vector>
#include <string>

// day-2025-7-30
/*
    访问者模式（Visitor Pattern） ：
    访问者模式是一种行为型设计模式，它允许你在不修改现有对象结构的情况下定义新的操作。
    通过将操作封装在访问者对象中，你可以在不同元素上执行这些操作，实现元素类与操作逻辑的解耦。

    核心角色
    - 抽象访问者（Visitor） ：定义对所有具体元素的访问操作接口
    - 具体访问者（Concrete Visitor） ：实现抽象访问者接口，提供具体操作
    - 抽象元素（Element） ：声明接受访问者的accept()方法
    - 具体元素（Concrete Element） ：实现accept()方法，调用访问者的对应方法
    - 对象结构（Object Structure） ：管理元素集合，提供遍历接口

    模式优点
    - 开闭原则 ：新增操作只需添加新的访问者，无需修改元素类
    - 单一职责 ：每个访问者专注于一组相关操作
    - 灵活性 ：可以在不修改对象结构的情况下定义新操作

*/
// 前向声明
class ConcreteElementA;
class ConcreteElementB;

// 抽象访问者
class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(ConcreteElementA *element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB *element) = 0;
};

// 抽象元素
class Element
{
public:
    virtual ~Element() = default;
    virtual void accept(Visitor *visitor) = 0;
};

// 具体元素A
class ConcreteElementA : public Element
{
private:
    std::string data_ = "ElementA Data";

public:
    void accept(Visitor *visitor) override
    {
        visitor->visitConcreteElementA(this);
    }
    std::string getData() const { return data_; }
};

// 具体元素B
class ConcreteElementB : public Element
{
private:
    int value_ = 100;

public:
    void accept(Visitor *visitor) override
    {
        visitor->visitConcreteElementB(this);
    }
    int getValue() const { return value_; }
};

// 具体访问者1：数据显示访问者
class DisplayVisitor : public Visitor
{
public:
    void visitConcreteElementA(ConcreteElementA *element) override
    {
        std::cout << "DisplayVisitor: Showing ElementA data - " << element->getData() << std::endl;
    }
    void visitConcreteElementB(ConcreteElementB *element) override
    {
        std::cout << "DisplayVisitor: Showing ElementB value - " << element->getValue() << std::endl;
    }
};

// 具体访问者2：数据处理访问者
class ProcessVisitor : public Visitor
{
public:
    void visitConcreteElementA(ConcreteElementA *element) override
    {
        std::cout << "ProcessVisitor: Processing ElementA data - " << element->getData() << " (processed)" << std::endl;
    }
    void visitConcreteElementB(ConcreteElementB *element) override
    {
        int newValue = element->getValue() * 2;
        std::cout << "ProcessVisitor: Processing ElementB value - " << element->getValue() << " -> " << newValue << std::endl;
    }
};

// 对象结构
class ObjectStructure
{
private:
    std::vector<Element *> elements_;

public:
    void addElement(Element *element)
    {
        elements_.push_back(element);
    }
    void accept(Visitor *visitor)
    {
        for (Element *element : elements_)
        {
            element->accept(visitor);
        }
    }
    ~ObjectStructure()
    {
        for (Element *element : elements_)
        {
            delete element;
        }
    }
};

// 客户端代码
int main()
{
    ObjectStructure *objectStructure = new ObjectStructure();
    objectStructure->addElement(new ConcreteElementA());
    objectStructure->addElement(new ConcreteElementB());

    Visitor *displayVisitor = new DisplayVisitor();
    Visitor *processVisitor = new ProcessVisitor();

    std::cout << "=== Applying DisplayVisitor ===" << std::endl;
    objectStructure->accept(displayVisitor);

    std::cout << "\n=== Applying ProcessVisitor ===" << std::endl;
    objectStructure->accept(processVisitor);

    delete displayVisitor;
    delete processVisitor;
    delete objectStructure;
    return 0;
}