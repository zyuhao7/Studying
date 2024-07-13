#include <iostream>
#include <string>
using namespace std;

// 工厂模式
/*
关键代码：创建过程在工厂类中完成。
*/

#if 0
// 定义产品类型信息
typedef enum
{
    Tank_Type_56,
    Tank_Type_96,
    Tank_Type_Num
} Tank_Type;

// 抽象产品类

class Tank
{
public:
    virtual const string &type() = 0;
};

// 具体的产品类
class Tank56 : public Tank
{
public:
    Tank56()
        : Tank(), m_strType("Tank56")
    {
    }
    const string &type() override
    {
        cout << m_strType.data() << endl;
        return m_strType;
    }

private:
    std::string m_strType;
};

// 具体的产品类
class Tank96 : public Tank
{
public:
    Tank96() : Tank(), m_strType("Tank96")
    {
    }
    const string &type() override
    {
        cout << m_strType.data() << endl;
        return m_strType;
    }

private:
    string m_strType;
};

// 工厂类
class TankFactory
{
public:
    // 根据产品信息创建具体的产品类实例，返回一个抽象产品类
    Tank *createTank(Tank_Type type)
    {
        switch (type)
        {
        case Tank_Type_56:
            return new Tank56();
        case Tank_Type_96:
            return new Tank96();
        default:
            return nullptr;
        }
    }
};

int main()
{
    TankFactory *factory = new TankFactory();
    Tank *tank56 = factory->createTank(Tank_Type_56);
    tank56->type();
    Tank *tank96 = factory->createTank(Tank_Type_96);
    tank96->type();
    delete tank96;
    tank96 = nullptr;

    delete tank56;
    tank56 = nullptr;

    delete factory;
    factory = nullptr;
    return 0;
}
#endif

#if 0
/*
关键代码：创建过程在其子类执行。
*/
// 产品抽象类
class Tank
{
public:
    virtual const string &type() = 0;
};

// 具体的产品类
class Tank56 : public Tank
{
public:
    Tank56() : Tank(), m_strType("Tank56")
    {
    }
    const string &type() override
    {
        cout << m_strType.data() << endl;
        return m_strType;
    }

private:
    string m_strType;
};
// 具体的产品类
class Tank96 : public Tank
{
public:
    Tank96() : Tank(), m_strType("Tank96")
    {
    }
    const string &type() override
    {
        cout << m_strType.data() << endl;
        return m_strType;
    }

private:
    string m_strType;
};

//抽象工厂类,提供一个创建接口
class TankFactory
{
public:
    // 提供创建产品实例的接口，返回抽象产品类
    virtual Tank *createTank() = 0;
};

// 具体的创建工厂类，使用抽象工厂类提供的接口，去创建具体的产品实例
class Tank56Factory : public TankFactory
{
public:
    Tank *createTank() override
    {
        return new Tank56();
    }
};

// 具体的创建工厂类，使用抽象工厂类提供的接口，去创建具体的产品实例
class Tank96Factory : public TankFactory
{
public:
    Tank *createTank() override
    {
        return new Tank96();
    }
};

int main()
{
    TankFactory *factory56 = new Tank56Factory();
    Tank *tank56 = factory56->createTank();
    tank56->type();

    TankFactory *factory96 = new Tank96Factory();
    Tank *tank96 = factory96->createTank();
    tank96->type();

    delete tank96;
    tank96 = nullptr;
    delete factory96;

    factory96 = nullptr;
    delete tank56;
    tank56 = nullptr;

    delete factory56;
    factory56 = nullptr;
    return 0;
}
#endif

#if 0

/*
 * 关键代码：在一个工厂里聚合多个同类产品。
 * 以下代码以白色衣服和黑色衣服为例,白色衣服为一个产品系列,黑色衣服为一个产品系列。白色上衣搭配白色裤子,黑色上衣搭配黑色裤字。每个系列的衣服由一个对应的工厂创建，这样一个工厂创建的衣服能保证衣服为同一个系列。
 */
// 抽象上衣类
class Coat
{
public:
    virtual const string &color() = 0;
};
// 黑色上衣类
class BlackCoat : public Coat
{
public:
    BlackCoat()
        : Coat(), m_strColor("Black Coat")
    {
    }
    const string &color() override
    {
        cout << m_strColor.data() << endl;
        return m_strColor;
    }

private:
    string m_strColor;
};

// 白色上衣类
class WhiteCoat : public Coat
{
public:
    WhiteCoat()
        : Coat(), m_strColor("White Coat")
    {
    }
    const string &color() override
    {
        cout << m_strColor.data() << endl;
        return m_strColor;
    }

private:
    string m_strColor;
};

// 抽象裤子类
class Pants
{
public:
    virtual const string &color() = 0;
};

// 黑色裤子类
class BlackPants : public Pants
{
public:
    BlackPants()
        : Pants(), m_strColor("Black Pants")
    {
    }
    const string &color() override
    {
        cout << m_strColor.data() << endl;
        return m_strColor;
    }

private:
    string m_strColor;
};

// 白色裤子类
class WhitePants : public Pants
{
public:
    WhitePants()
        : Pants(), m_strColor("White Pants")
    {
    }
    const string &color() override
    {
        cout << m_strColor.data() << endl;
        return m_strColor;
    }

private:
    string m_strColor;
};

// 抽象工厂类,提供衣服创建接口
class Factory
{
public:
    // 上衣创建接口，返回抽象上衣类
    virtual Coat *createCoat() = 0;
    // 裤子创建接口，返回抽象裤子类
    virtual Pants *createPants() = 0;
};

// 创建白色衣服的工厂类,具体实现创建白色上衣和白色裤子的接口.
class WhiteFactory : public Factory
{
public:
    Coat *createCoat() override
    {
        return new WhiteCoat();
    }
    Pants *createPants() override
    {
        return new WhitePants();
    }
};

// 创建黑色衣服的工厂类,具体实现创建黑色上衣和白色裤子的接口.
class BlackFactory : public Factory
{
    Coat *createCoat() override
    {
        return new BlackCoat();
    }
    Pants *createPants() override
    {
        return new BlackPants();
    }
};

#endif
