#include <iostream>
#include <vector>

using namespace std;
// day-2025-8-11
// Factory Method 工厂方法

/*
	工厂方法模式是一种创建型设计模式，它定义了一个创建对象的接口，但让子类决定要实例化哪一个类。工厂方法让类的实例化推迟到子类。
	主要角色
	Product（抽象产品）：定义工厂方法所创建的对象的接口
	ConcreteProduct（具体产品）：实现Product接口的具体类
	Creator（抽象创建者）：声明工厂方法，该方法返回一个Product类型的对象
	ConcreteCreator（具体创建者）：重写工厂方法以返回一个ConcreteProduct实例

	优点
	将对象的创建与使用分离
	支持开闭原则，易于扩展新产品
	消除代码对具体类的依赖
	代码更易于维护和扩展

	缺点
	每增加一个产品就需要增加一个具体工厂类，增加了系统的复杂度
	引入了额外的抽象层，可能增加理解难度

┌───────────────────┐       ┌───────────────────┐
│          Creator               	   │       │               Product   		      │
├───────────────────┤       ├───────────────────┤
│ 		 +factoryMethod()  			   │───>│              +operation()            │
└───────────────────┘       └───────────────────┘
				▲                          							▲
				│                            						│
┌───────────────────┐       ┌───────────────────┐
│         ConcreteCreator              │       │             ConcreteProduct   		  │
├───────────────────┤       ├───────────────────┤
│         +factoryMethod()  	       │       │ 			 +operation()      		  │
└───────────────────┘       └───────────────────┘



*/

class Product
{
public:
	virtual void use() = 0;
	virtual ~Product() = default;
};

class ConcreteProductA : public Product
{
	void use() override
	{
		std::cout << "Using Product A \n";
	}
};

class ConcreteProductB : public Product
{
	void use() override
	{
		std::cout << "Using Product B \n";
	}
};

class Factory
{
public:
	virtual Product *createProduct() = 0;
	virtual ~Factory() = default;
};

class ConreteFactoryA : public Factory
{
public:
	Product *createProduct() override
	{
		return new ConcreteProductA();
	}
};

class ConreteFactoryB : public Factory
{
public:
	Product *createProduct() override
	{
		return new ConcreteProductB();
	}
};

// int main()
//{
//	Factory* facA = new ConreteFactoryA();
//
//	Product* prodA = facA->createProduct();
//	prodA->use();
//
//	Factory* facB = new ConreteFactoryB();
//
//	Product* prodB = facB->createProduct();
//	prodB->use();
//
//	delete prodA;
//	delete facA;
//	delete prodB;
//	delete facB;
//	return 0;
// }