#include <iostream>
#include <string>
using namespace std;
/*
    装饰器模式属于结构型设计模式，它允许向现有对象动态添加新功能，同时不改变其结构。
    这种模式通过创建一个包装对象（装饰器）来包裹真实对象，从而在保持类方法签名完整性的前提下，提供额外功能。

    装饰器模式的主要角色包括：
    1. 组件接口（Component）：定义对象的接口，装饰器和真实对象都需要实现这个接口。
    2. 具体组件（Concrete Component）：实现组件接口的基本对象，装饰器可以包裹它。
    3. 装饰器（Decorator）：包含一个组件指针，并定义与组件接口一致的接口。
    4. 具体装饰器（Concrete Decorator）：添加额外功能的装饰器，实现装饰器接口。

    装饰器模式的主要优点包括：
    1. 动态添加功能：可以在运行时动态添加新功能，而不需要修改原始对象。
    2. 避免类爆炸：通过使用装饰器模式，我们可以避免创建大量的具体装饰器类，从而减少类的数量。
    3. 符合开闭原则：可以添加新的装饰器而不改变原始对象的代码，符合开闭原则。

    装饰器模式的主要缺点包括：
    1. 调试复杂：由于装饰器模式使用了多个包装层，调试可能会变得复杂，特别是在嵌套装饰器的情况下。
    2. 性能问题：装饰器模式可能会引入额外的间接层，导致性能下降。
    3. 代码复杂性：装饰器模式引入了额外的类和接口，可能会增加代码的复杂性。

*/
// day-2025-7-15
// 抽象组件 - 定义对象接口
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getDescription() const = 0;
};

// 具体组件 - 实现基本功能
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double radius)
        : radius(radius) {}
    void draw() const override
    {
        std::cout << "绘制圆形，半径: " << radius << std::endl;
    }
    std::string getDescription() const override
    {
        return "圆形(半径: " + std::to_string(radius) + ")";
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double width, double height)
        : width(width), height(height) {}
    void draw() const override
    {
        std::cout << "绘制矩形，宽: " << width << ", 高: " << height << std::endl;
    }
    std::string getDescription() const override
    {
        return "矩形(宽: " + std::to_string(width) + ", 高: " + std::to_string(height) + ")";
    }
};

// 抽象装饰器 - 继承自组件并包含组件指针
class ShapeDecorator : public Shape
{
protected:
    Shape *decoratedShape;

public:
    ShapeDecorator(Shape *shape)
        : decoratedShape(shape) {}
    ~ShapeDecorator() override
    {
        delete decoratedShape;
    }
    void draw() const override
    {
        decoratedShape->draw();
    }
    std::string getDescription() const override
    {
        return decoratedShape->getDescription();
    }
};

// 具体装饰器 - 添加额外功能
class RedShapeDecorator : public ShapeDecorator
{
public:
    RedShapeDecorator(Shape *shape)
        : ShapeDecorator(shape) {}
    void draw() const override
    {
        decoratedShape->draw();
        setRedBorder();
    }
    std::string getDescription() const override
    {
        return decoratedShape->getDescription() + "，红色边框";
    }

private:
    void setRedBorder() const
    {
        std::cout << "设置边框颜色为红色" << std::endl;
    }
};

class DashedShapeDecorator : public ShapeDecorator
{
public:
    DashedShapeDecorator(Shape *shape)
        : ShapeDecorator(shape) {}
    void draw() const override
    {
        decoratedShape->draw();
        setDashedBorder();
    }
    std::string getDescription() const override
    {
        return decoratedShape->getDescription() + "，虚线边框";
    }

private:
    void setDashedBorder() const
    {
        std::cout << "设置边框样式为虚线" << std::endl;
    }
};

// 客户端代码
int main()
{
    // 创建基本形状
    Shape *circle = new Circle(5.0);
    Shape *rectangle = new Rectangle(4.0, 6.0);

    std::cout << "=== 基本形状 ===" << std::endl;
    circle->draw();
    std::cout << "描述: " << circle->getDescription() << std::endl;
    rectangle->draw();
    std::cout << "描述: " << rectangle->getDescription() << std::endl;

    // 使用装饰器添加功能
    Shape *redCircle = new RedShapeDecorator(new Circle(5.0));
    Shape *dashedRectangle = new DashedShapeDecorator(new Rectangle(4.0, 6.0));
    Shape *redDashedCircle = new RedShapeDecorator(new DashedShapeDecorator(new Circle(7.0)));

    std::cout << "\n=== 装饰后的形状 ===" << std::endl;
    redCircle->draw();
    std::cout << "描述: " << redCircle->getDescription() << std::endl;
    dashedRectangle->draw();
    std::cout << "描述: " << dashedRectangle->getDescription() << std::endl;
    redDashedCircle->draw();
    std::cout << "描述: " << redDashedCircle->getDescription() << std::endl;

    // 清理内存
    delete circle;
    delete rectangle;
    delete redCircle;
    delete dashedRectangle;
    delete redDashedCircle;

    return 0;
}