## 工厂模式
```c++
// 在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。工厂模式作为一种创建模式，一般在创建复杂对象时，考虑使用；在创建简单对象时，建议直接new完成一个实例对象的创建。

// 简单工厂模式
// 主要特点是需要在工厂类中做判断，从而创造相应的产品，当增加新产品时，需要修改工厂类。使用简单工厂模式，我们只需要知道具体的产品型号就可以创建一个产品。
// 缺点：工厂类集中了所有产品类的创建逻辑，如果产品量较大，会使得工厂类变的非常臃肿。

// code
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
```

```c++
// 工厂方法模式
// 定义一个创建对象的接口，其子类去具体现实这个接口以完成具体的创建工作。如果需要增加新的产品类，只需要扩展一个相应的工厂类即可.
// 缺点：产品类数据较多时，需要实现大量的工厂类，这无疑增加了代码量.
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
```

```c++
// 抽象工厂模式
// 抽象工厂模式提供创建一系列相关或相互依赖对象的接口,而无需指定它们具体的类。当存在多个产品系列，而客户端只使用一个系列的产品时，可以考虑使用抽象工厂模式.
// 缺点：当增加一个新系列的产品时,不仅需要现实具体的产品类,还需要增加一个新的创建接口，扩展相对困难.

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
```