#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
/*
    解释器设计模式:
    解释器模式是一种行为型设计模式，用于定义语言的文法规则，并构建一个解释器来解释该语言中的句子。
    它适用于简单的语法规则场景，如表达式解析、配置文件解析等。

    核心角色
     1.抽象表达式（Abstract Expression） ：声明解释操作的接口
     2.终结符表达式（Terminal Expression） ：实现文法中终结符的解释操作
     3.非终结符表达式（Non-terminal Expression） ：实现文法中非终结符的解释操作，包含子表达式
     4.上下文（Context） ：存储解释器的全局信息
     5.客户端（Client） ：构建抽象语法树，调用解释操作

*/

// 抽象表达式
class Expression
{
public:
    virtual int interpret(const std::unordered_map<std::string, int> &context) = 0;
    virtual ~Expression() = default;
};

// 终结符表达式：变量
class VariableExpression : public Expression
{
private:
    std::string name;

public:
    VariableExpression(const std::string &name)
        : name(name) {}
    int interpret(const std::unordered_map<std::string, int> &context) override
    {
        return context.at(name); // 从上下文中获取变量值
    }
};

// 终结符表达式：常量
class ConstantExpression : public Expression
{
private:
    int value;

public:
    ConstantExpression(int value)
        : value(value) {}
    int interpret(const std::unordered_map<std::string, int> &context) override
    {
        return value; // 直接返回常量值
    }
};

// 非终结符表达式：加法
class AddExpression : public Expression
{
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret(const std::unordered_map<std::string, int> &context) override
    {
        return left->interpret(context) + right->interpret(context); // 解释并相加
    }
};

// 非终结符表达式：减法
class SubtractExpression : public Expression
{
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    SubtractExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret(const std::unordered_map<std::string, int> &context) override
    {
        return left->interpret(context) - right->interpret(context); // 解释并相减
    }
};

// 客户端：构建表达式树并解释
int main()
{
    // 构建表达式: a + b - c
    auto a = std::make_unique<VariableExpression>("a");
    auto b = std::make_unique<VariableExpression>("b");
    auto c = std::make_unique<VariableExpression>("c");

    auto add = std::make_unique<AddExpression>(std::move(a), std::move(b));
    auto subtract = std::make_unique<SubtractExpression>(std::move(add), std::move(c));

    // 上下文环境
    std::unordered_map<std::string, int> context = {
        {"a", 10},
        {"b", 5},
        {"c", 3}};

    // 解释表达式
    std::cout << "Result: " << subtract->interpret(context) << std::endl; // 输出: 12
    return 0;
}