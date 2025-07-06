#include <iostream>
#include <vector>

using namespace std;

//Factory Method 工厂方法模式
/*
定义：
工厂方法模式通过定义一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法让类的实例化推迟到子类中。

主要角色：

	Product（产品接口/抽象类）
	ConcreteProduct（具体产品类）
	Creator（抽象工厂类）
	ConcreteCreator（具体工厂类）

		+--------------+         +---------------------+
		|   Factory    |<--------| ConcreteFactoryA/B  |
		+--------------+         +---------------------+
		| +createProduct()       | +createProduct()    |
		+--------------+         +---------------------+
				|
				v
		 +-------------+
		 |   Product   |<--------+ ConcreteProductA/B
		 +-------------+         +--------------------+
		 | +use()      |         | +use()             |
		 +-------------+         +--------------------+

 |            模式                 |			说明		     	|				  区别                   |
| ---------------------------------|------------------------------- | -------------------------------------- |
|   Simple Factory  （简单工厂）   | 工厂类中用条件判断返回不同产品 | 不属于 GoF 23 种设计模式；违反开闭原则 |
|   Factory Method  （工厂方法）   | 每种产品对应一个工厂子类       | 满足开闭原则，结构更清晰               |
|   Abstract Factory  （抽象工厂） | 创建  一组相关产品 的接口      | 适合多种产品族（如 GUI 套件）          |
|   Builder      				   | 逐步构造复杂对象               | 更关注构建过程，而非产品种类           |
|   Prototype    				   | 通过复制已有对象创建新对象     | 适合对象构造代价大的场景               |
|   Singleton                      | 确保一个类只有一个实例         | 关注实例唯一性，不创建多个产品         |

*/

//产品类接口和具体实现
class Product
{
public:
	virtual void use() = 0; // 抽象方法
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

// 工厂类接口和具体实现
class Factory
{
public:
	virtual Product* createProduct() = 0;
	virtual ~Factory() = default;
};

class ConreteFactoryA : public Factory
{
public:
	Product* createProduct() override
	{
		return new ConcreteProductA();
	}
};

class ConreteFactoryB : public Factory
{
public:

	Product* createProduct() override
	{
		return new ConcreteProductB();
	}
};

int main()
{
	Factory* facA = new ConreteFactoryA();

	Product* prodA = facA->createProduct();
	prodA->use();

	Factory* facB = new ConreteFactoryB();

	Product* prodB = facB->createProduct();
	prodB->use();

	delete prodA;
	delete facA;
	delete prodB;
	delete facB;
	return 0;
}