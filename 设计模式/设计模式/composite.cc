#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;
// day-2025-7-14
// composite ģʽ
/*
	��������ϳ����νṹ�Ա�ʾ"����-����"�Ĳ�νṹ��Composite ģʽʹ���û��Ե�������Ҷ�ӣ�����϶�������������һ�µ�ʹ�÷�ʽ��
               ����������������������������������������
               ��   Equipment�������ࣩ              ��
               ����������������������������������������
                        ��       ��
            ��������������       ��������������
    ������������������������������     ��������������������������������������������
    ��  Leaf�豸��              ��     �� Composite�豸�ࣨ��ϣ�                ��
    �� e.g. Disk                ��     �� e.g. Chassis                           ��
    ������������������������������     ��������������������������������������������

    | ����        | ����                                                                       |
| --------- | ---------------------------------------------                                    |
| Component | ����ӿڣ�����Ҷ�Ӻ���϶����еĲ���                                           |
| Leaf      | ��ʾҶ�Ӷ������Ӷ���                                                           |
| Composite | ��ʾ�������󣬳����Ӷ����б�                                                     |
| �ŵ�      | ͳһҶ������϶����ʹ�÷�ʽ���ṹ��������չ                                 |
| ȱ��      | ����׷��͸���Ի��������Ͱ�ȫ�����ܻ���Ҷ�����б�¶�����õĲ������� Add/Remove��  |

    ����еĵݹ����������ģ������� Display��Power��Price �����Եݹ�ر�����������
    std::shared_ptr ���ִ� C++ ���Ƽ�������ָ�����ʽ�����ڱ����ڴ�й©���ֶ���������������ڡ�

*/
// 1. ������� Equipment
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
        // Ĭ�ϲ�֧��
    }

    virtual void Remove(std::shared_ptr<Equipment> eq) {
        // Ĭ�ϲ�֧��
    }
    
    virtual void Display(int depth) const = 0;

protected:
    string name_;
};

// 2. Ҷ�ӽڵ㣺���� Disk, CPU
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

// 3. Composite �ڵ㣺���� Chassis, Cabinet
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