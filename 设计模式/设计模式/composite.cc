#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;
// day-2025-7-14
// composite 模式
/*
	将对象组合成树形结构以表示"部分-整体"的层次结构。Composite 模式使得用户对单个对象（叶子）和组合对象（容器）具有一致的使用方式。
               ┌──────────────────┐
               │   Equipment（抽象类）              │
               └──────────────────┘
                        ▲       ▲
            ┌─────┘       └─────┐
    ┌─────────────┐     ┌────────────────────┐
    │  Leaf设备类              │     │ Composite设备类（组合）                │
    │ e.g. Disk                │     │ e.g. Chassis                           │
    └─────────────┘     └────────────────────┘

    | 概念        | 含义                                                                       |
| --------- | ---------------------------------------------                                    |
| Component | 抽象接口，声明叶子和组合对象共有的操作                                           |
| Leaf      | 表示叶子对象，无子对象                                                           |
| Composite | 表示容器对象，持有子对象列表                                                     |
| 优点      | 统一叶子与组合对象的使用方式；结构灵活；易于拓展                                 |
| 缺点      | 过于追求透明性会牺牲类型安全；可能会在叶子类中暴露不适用的操作（如 Add/Remove）  |

    组合中的递归设计是其核心，操作如 Display、Power、Price 都可以递归地遍历整棵树。
    std::shared_ptr 是现代 C++ 中推荐的智能指针管理方式，用于避免内存泄漏和手动管理对象生命周期。

*/
// 1. 抽象基类 Equipment
class Equipment
{
public:
    Equipment(const std::string& name)
        :name_(name)
    {
    }
    virtual ~Equipment(){}

    virtual double Power() const = 0;
    virtual double NetPrice() const = 0;
    virtual double DiscountPrice() const = 0;

    virtual void Add(std::shared_ptr<Equipment> eq) {
        // 默认不支持
    }

    virtual void Remove(std::shared_ptr<Equipment> eq) {
        // 默认不支持
    }
    
    virtual void Display(int depth) const = 0;

protected:
    string name_;
};

// 2. 叶子节点：例如 Disk, CPU
class Disk : public Equipment
{
public:
    Disk(const std::string& name, double price, double power)
        :Equipment(name), price_(price), power_(power) {}
    double Power() const  override { return power_; }
    double NetPrice() const override { return price_; }
    double DiscountPrice() const override { return price_ * 0.95; }

    void Display(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "Disk: " << name_ << ", Price: " << price_ << ", Power: " << power_ << "\n";
    }

private:
    double price_;
    double power_;
};

class CPU : public Equipment {
public:
    CPU(const std::string& name, double price, double power)
        : Equipment(name), price_(price), power_(power) {
    }

    double Power() const override { return power_; }
    double NetPrice() const override { return price_; }
    double DiscountPrice() const override { return price_ * 0.9; }

    void Display(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "CPU: " << name_ << ", Price: " << price_ << ", Power: " << power_ << "\n";
    }

private:
    double price_;
    double power_;
};

// 3. Composite 节点：例如 Chassis, Cabinet
class Chassis : public Equipment {
public:
    Chassis(const std::string& name) : Equipment(name) {}

    void Add(std::shared_ptr<Equipment> eq) override {
        components_.push_back(eq);
    }

    void Remove(std::shared_ptr<Equipment> eq) override {
        components_.erase(std::remove(components_.begin(), components_.end(), eq), components_.end());
    }

    double Power() const override {
        double total = 0;
        for (const auto& c : components_) total += c->Power();
        return total;
    }

    double NetPrice() const override {
        double total = 0;
        for (const auto& c : components_) total += c->NetPrice();
        return total;
    }

    double DiscountPrice() const override {
        double total = 0;
        for (const auto& c : components_) total += c->DiscountPrice();
        return total;
    }

    void Display(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "Chassis: " << name_ << "\n";
        for (const auto& c : components_) c->Display(depth + 2);
    }

private:
    std::vector<std::shared_ptr<Equipment>> components_;
};


//int main() {
//    auto disk1 = std::make_shared<Disk>("Seagate 1TB", 500, 5);
//    auto cpu1 = std::make_shared<CPU>("Intel i9", 3000, 95);
//
//    auto chassis = std::make_shared<Chassis>("Main Chassis");
//    chassis->Add(disk1);
//    chassis->Add(cpu1);
//
//    chassis->Display();
//
//    std::cout << "Total Net Price: " << chassis->NetPrice() << "\n";
//    std::cout << "Total Discount Price: " << chassis->DiscountPrice() << "\n";
//    std::cout << "Total Power: " << chassis->Power() << "W\n";
//
//    return 0;
//}