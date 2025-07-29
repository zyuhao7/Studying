#include <iostream>
#include <string>
#include <memory>

/*                                      day-2025-7-29
    1. 模式定义
        策略模式是一种行为型设计模式，它定义了算法家族，分别封装起来，让它们之间可以互相替换，
        此模式让算法的变化不会影响使用算法的客户。

    2. 核心角色
        - 抽象策略（Strategy） ：定义所有支持算法的公共接口
        - 具体策略（Concrete Strategy） ：实现抽象策略接口，提供具体算法实现
        - 环境类（Context） ：持有策略对象的引用，负责将客户端请求委派给具体策略

    3. 策略模式优点
        - 开闭原则 ：新增策略无需修改现有代码
        - 消除条件语句 ：用多态代替复杂的 if-else/switch 逻辑
        - 算法复用 ：策略可以在不同场景中复用
        - 运行时切换 ：客户端可以动态选择不同策略

    4. 策略模式缺点
        - 增加了类的数量 ：每个策略都需要创建一个类
        - 客户端需要知道所有策略类 ：客户端必须了解所有策略类，才能选择合适的策略
*/
// 抽象策略：支付方式
class PaymentStrategy
{
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) const = 0;
};

// 具体策略：信用卡支付
class CreditCardPayment : public PaymentStrategy
{
private:
    std::string name;
    std::string cardNumber;

public:
    CreditCardPayment(std::string name, std::string cardNumber)
        : name(std::move(name)),
          cardNumber(std::move(cardNumber)) {}

    void pay(double amount) const override
    {
        std::cout << "使用信用卡支付: ¥" << amount << std::endl;
        std::cout << "持卡人: " << name << std::endl;
        std::cout << "卡号: ****-****-****-" << cardNumber.substr(12) << std::endl;
    }
};

// 具体策略：支付宝支付
class AlipayPayment : public PaymentStrategy
{
private:
    std::string account;

public:
    explicit AlipayPayment(std::string account)
        : account(std::move(account)) {}

    void pay(double amount) const override
    {
        std::cout << "使用支付宝支付: ¥" << amount << std::endl;
        std::cout << "支付宝账号: " << account << std::endl;
    }
};

// 环境类：购物车
class ShoppingCart
{
private:
    std::unique_ptr<PaymentStrategy> paymentStrategy;

public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy)
    {
        paymentStrategy = std::move(strategy);
    }

    void checkout(double amount) const
    {
        if (!paymentStrategy)
        {
            std::cerr << "请先选择支付方式!" << std::endl;
            return;
        }
        paymentStrategy->pay(amount);
    }
};

// 客户端代码
int main()
{
    ShoppingCart cart;
    double totalAmount = 399.99;

    // 选择信用卡支付
    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>(
        "张三", "6222021234567890"));
    cart.checkout(totalAmount);

    std::cout << "\n------------------------\n\n";

    // 切换为支付宝支付
    cart.setPaymentStrategy(std::make_unique<AlipayPayment>("zhangsan@example.com"));
    cart.checkout(totalAmount);

    return 0;
}