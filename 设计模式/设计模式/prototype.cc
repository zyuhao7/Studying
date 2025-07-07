#include <iostream>
#include <vector>
#include <string>
using namespace std;

// day-2025-7-7
// 原型模型

/*
	1. 概念介绍：
	Prototype 模式(原型模式)是一种 创建型设计模式，用于通过“复制”一个已有对象来创建新对象，而不是通过传统的 new 关键字实例化。

	2. 使用场景：
	创建对象成本高（如初始化开销大、耗时、占用大量资源）
	希望在运行时动态决定创建哪个类的实例
	避免创建过程依赖于子类

	3. 实现要点：
	定义一个原型接口（如 clone() 方法）
	每个需要复制的类实现该接口，返回自己的克隆对象

			+----------------+
			|   Prototype    | <------- 抽象原型接口
			+----------------+
			| +clone()       |
			+----------------+
				   ▲
				   ||
		 +------------------------+
		 |   ConcretePrototype    | <--- 具体原型类，包含实际的数据和实现 clone()
		 +------------------------+
		 | +clone()               |
		 +------------------------+

				  ▲
				  ||
			 +-------------+
			 |   Client    | <--- 客户端，通过 clone() 创建对象
			 +-------------+

	角色							说明
	Prototype（原型接口）			定义一个 clone() 接口用于复制自身。
	ConcretePrototype（具体原型类）	实现 clone() 方法，返回一个自身的拷贝。
	Client（客户端）				调用 clone() 方法创建新对象，而无需知道具体类名。


	✅ 优点：
	性能提升：通过复制减少 new 的开销。
	隐藏创建逻辑：客户端无需知道创建细节。
	简化复杂对象创建：尤其适用于带有大量配置的对象。

	❌ 缺点：
	每个类都要实现 clone()，维护成本略高。
	需要处理深拷贝 vs 浅拷贝的问题。
	如果对象包含指针或资源引用，clone() 的实现可能变复杂。


	模式				关键点						与 Prototype 区别
	Factory Method		延迟到子类创建对象			由子类决定创建哪个类
	Abstract Factory	创建一组相关对象			抽象工厂创建多个产品
	Builder				一步步构建复杂对象			构建过程与表示分离
	Singleton			只创建一个实例				控制实例数量
	Prototype			通过复制现有对象创建新对象	基于现有对象复制

*/

// 原型基类
//class Prototype
//{
//public:
//	virtual Prototype* clone() const = 0;
//	virtual void show() const = 0;
//	virtual ~Prototype(){}
//};
//
//// 具体类
//class ConcretePrototype : public Prototype
//{
//private:
//	string data;
//public:
//	ConcretePrototype(string d)
//		:data(d)
//	{}
//
//	// 实现 clone()
//	Prototype* clone() const override
//	{
//		return new ConcretePrototype(*this);
//	}
//
//	void show() const override
//	{
//		cout << "ConcretePrototype: " << data << endl;
//	}
//};
// 
//可以使用“原型注册表”来统一管理所有原型，然后按需 clone：
//class PrototypeManager {
//private:
//	unordered_map<string, Prototype*> prototypes;
//public:
//	void registerPrototype(string key, Prototype* proto) {
//		prototypes[key] = proto;
//	}
//
//	Prototype* create(string key) {
//		return prototypes[key]->clone();
//	}
//};

//// 客户端
//int main()
//{
//	Prototype* p1 = new ConcretePrototype("Original");
//	Prototype* p2 = p1->clone();
//	p1->show();
//	p2->show();
//
//	delete p1;
//	delete p2;
//}



// 原型接口
//class Shape {
//public:
//	virtual Shape* clone() const = 0;
//	virtual void draw() const = 0;
//	virtual ~Shape() {}
//};
//
//// 具体原型类：Circle
//class Circle : public Shape {
//private:
//	int radius;
//public:
//	Circle(int r) : radius(r) {}
//
//	// 实现克隆
//	Shape* clone() const override {
//		return new Circle(*this);  // 调用拷贝构造
//	}
//
//	void draw() const override {
//		cout << "Draw Circle with radius: " << radius << endl;
//	}
//};
//
//// 具体原型类：Rectangle
//class Rectangle : public Shape {
//private:
//	int width, height;
//public:
//	Rectangle(int w, int h) : width(w), height(h) {}
//
//	Shape* clone() const override {
//		return new Rectangle(*this);
//	}
//
//	void draw() const override {
//		cout << "Draw Rectangle of size: " << width << " * " << height << endl;
//	}
//};
//
//// 客户端
//int main() {
//	Shape* circle = new Circle(10);
//	Shape* rect = new Rectangle(4, 5);
//
//	Shape* copy1 = circle->clone();  // 克隆 Circle
//	Shape* copy2 = rect->clone();    // 克隆 Rectangle
//
//	copy1->draw(); // Draw Circle with radius: 10
//	copy2->draw(); // Draw Rectangle of size: 4 * 5
//
//	delete circle;
//	delete rect;
//	delete copy1;
//	delete copy2;
//
//	return 0;
//}
