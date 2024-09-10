#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 简单⼯⼚模式：通过参数控制可以⽣产任何产品
// 优点：简单粗暴，直观易懂。使⽤⼀个⼯⼚⽣产同⼀等级结构下的任意产品

// 缺点：
// 1. 所有东西⽣产在⼀起，产品太多会导致代码量庞⼤
// 2. 开闭原则遵循(开放拓展，关闭修改)的不是太好，要新增产品就必须修改⼯⼚⽅法。

// class Fruit
// {
// public:
//     Fruit() {}
//     virtual void show() = 0;
// };

// class Apple : public Fruit
// {
// public:
//     Apple() {}
//     virtual void show()
//     {
//         std::cout << "Apple 苹果" << std::endl;
//     }
// };

// class Banana : public Fruit
// {
// public:
//     Banana() {}
//     virtual void show()
//     {
//         std::cout << "Banana ⾹蕉" << std::endl;
//     }
// };

// class FruitFactory
// {
// public:
//     static std::shared_ptr<Fruit> create(const std::string &name)
//     {
//         if (name == "苹果")
//         {
//             return std::make_shared<Apple>();
//         }
//         else if (name == "⾹蕉")
//         {
//             return std::make_shared<Banana>();
//         }
//         return std::shared_ptr<Fruit>();
//     }
// };

// int main()
// {
//     std::shared_ptr<Fruit> fruit = FruitFactory::create("苹果");
//     fruit->show();
//     fruit = FruitFactory::create("⾹蕉");
//     fruit->show();
//     return 0;
// }

// ⼯⼚⽅法：定义⼀个创建对象的接⼝，但是由⼦类来决定创建哪种对象，使⽤多个⼯⼚分别⽣产指定的固定产品
// 优点：
// 1. 减轻了⼯⼚类的负担，将某类产品的⽣产交给指定的⼯⼚来进⾏
// 2. 开闭原则遵循较好，添加新产品只需要新增产品的⼯⼚即可，不需要修改原先的⼯⼚类

// 缺点：对于某种可以形成⼀组产品族的情况处理较为复杂,需要创建⼤量的⼯⼚类.

// class Fruit
// {
// public:
//     Fruit() {}
//     virtual void show() = 0;
// };

// class Apple : public Fruit
// {
// public:
//     Apple() {}
//     virtual void show()
//     {
//         std::cout << "apple 苹果" << std::endl;
//     }
// };

// class Banana : public Fruit
// {
// public:
//     Banana() {}
//     virtual void show()
//     {
//         std::cout << "banana ⾹蕉" << std::endl;
//     }
// };

// class FruitFactory
// {
// public:
//     virtual std::shared_ptr<Fruit> create() = 0;
// };

// class AppleFactory : public FruitFactory
// {
// public:
//     virtual std::shared_ptr<Fruit> create()
//     {
//         return std::make_shared<Apple>();
//     }
// };

// class BananaFactory : public FruitFactory
// {
// public:
//     virtual std::shared_ptr<Fruit> create()
//     {
//         return std::make_shared<Banana>();
//     }
// };

// int main()
// {
//     std::shared_ptr<FruitFactory> factory(new AppleFactory());
//     std::shared_ptr<Fruit> fruit;

//     fruit = factory->create();
//     fruit->show();

//     factory.reset(new BananaFactory());
//     fruit = factory->create();
//     fruit->show();
//     return 0;
// }

// 抽象⼯⼚：围绕⼀个超级⼯⼚创建其他⼯⼚。每个⽣成的⼯⼚按照⼯⼚模式提供对象。
// 思想：将⼯⼚抽象成两层，抽象⼯⼚ & 具体⼯⼚⼦类， 在⼯⼚⼦类种⽣产不同类型的⼦产品

// class Fruit
// {
// public:
//     Fruit() {}
//     virtual void show() = 0;
// };

// class Apple : public Fruit
// {
// public:
//     Apple() {}
//     virtual void show()
//     {
//         std::cout << "apple 苹果" << std::endl;
//     }

// private:
//     std::string _color;
// };

// class Banana : public Fruit
// {
// public:
//     Banana() {}
//     virtual void show()
//     {
//         std::cout << "banana ⾹蕉" << std::endl;
//     }
// };

// class Animal
// {
// public:
//     virtual void voice() = 0;
// };

// class Lamp : public Animal
// {
// public:
//     void voice() { std::cout << "咩咩咩\n"; }
// };

// class Dog : public Animal
// {
// public:
//     void voice() { std::cout << "汪汪汪\n"; }
// };

// class Factory
// {
// public:
//     virtual std::shared_ptr<Fruit> getFruit(const std::string &name) = 0;
//     virtual std::shared_ptr<Animal> getAnimal(const std::string &name) = 0;
// };

// class FruitFactory : public Factory
// {
// public:
//     virtual std::shared_ptr<Animal> getAnimal(const std::string &name)
//     {
//         return std::shared_ptr<Animal>();
//     }
//     virtual std::shared_ptr<Fruit> getFruit(const std::string &name)
//     {
//         if (name == "苹果")
//         {
//             return std::make_shared<Apple>();
//         }
//         else if (name == "⾹蕉")
//         {
//             return std::make_shared<Banana>();
//         }
//         return std::shared_ptr<Fruit>();
//     }
// };

// class AnimalFactory : public Factory
// {

// public:
//     virtual std::shared_ptr<Fruit> getFruit(const std::string &name)
//     {
//         return std::shared_ptr<Fruit>();
//     }
//     virtual std::shared_ptr<Animal> getAnimal(const std::string &name)
//     {
//         if (name == "⼩⽺")
//         {
//             return std::make_shared<Lamp>();
//         }
//         else if (name == "⼩狗")
//         {
//             return std::make_shared<Dog>();
//         }
//         return std::shared_ptr<Animal>();
//     }
// };

// class FactoryProducer
// {
// public:
//     static std::shared_ptr<Factory> getFactory(const std::string &name)
//     {
//         if (name == "动物")
//         {
//             return std::make_shared<AnimalFactory>();
//         }
//         else
//         {
//             return std::make_shared<FruitFactory>();
//         }
//     }
// };

// int main()
// {
//     std::shared_ptr<Factory> fruit_factory = FactoryProducer::getFactory("⽔果");
//     std::shared_ptr<Fruit> fruit = fruit_factory->getFruit("苹果");
//     fruit->show();
//     fruit = fruit_factory->getFruit("⾹蕉");
//     fruit->show();

//     std::shared_ptr<Factory> animal_factory = FactoryProducer::getFactory("动物");
//     std::shared_ptr<Animal> animal = animal_factory->getAnimal("⼩⽺");
//     animal->voice();
//     animal = animal_factory->getAnimal("⼩狗");
//     animal->voice();
//     return 0;
// }
