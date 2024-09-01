#include <iostream>
#include <list>
#include <memory>
using namespace std;
// 2024-9-1
// 装饰器模式
// 允许向一个现有对象添加新的功能,  同时又不改变其结构    <结构型模式>.

// 抽象构件类
class Transform
{
public:
    virtual void move() = 0;
};

// 具体构件类 Car
class Car : public Transform
{
public:
    Car()
    {
        std::cout << "变形金刚是一辆车!!" << endl;
    }
    void move()
    {
        cout << "在陆地移动! " << endl;
    }
};

// 抽象装饰类
class Changer : public Transform
{
public:
    Changer(shared_ptr<Transform> tf)
    {
        this->transform = tf;
    }
    void move()
    {
        transform->move();
    }

private:
    shared_ptr<Transform> transform;
};

// 具体装饰类 Robot
class Robot : public Changer
{
public:
    Robot(shared_ptr<Transform> tf)
        : Changer(tf)
    {
        cout << "变成机器人了!" << endl;
    }
    void say()
    {
        cout << "说话!" << endl;
    }
};

// 具体装饰类 AirPlane
class Airplane : public Changer
{
public:
    Airplane(shared_ptr<Transform> tf)
        : Changer(tf)
    {
        cout << "变成飞机了! " << endl;
    }

    void say()
    {
        cout << "在天空飞翔!~" << endl;
    }
};

int main()
{
    shared_ptr<Transform> camaro = make_shared<Car>();
    camaro->move();

    cout << "-------------------------" << endl;

    shared_ptr<Robot> bumblebee = make_shared<Robot>(camaro);
    bumblebee->move();
    bumblebee->say();

    cout << "--------------------------" << endl;

    shared_ptr<Airplane> airplane = make_shared<Airplane>(camaro);
    airplane->move();
    airplane->say();
}