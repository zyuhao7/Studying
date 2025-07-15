#include <iostream>
#include <vector>

using namespace std;


// day-2025-7-12
/*
	适配器模式是一种结构型设计模式，它允许将一个类的接口转换成客户端所期望的另一个接口。
	适配器模式使得原本由于接口不兼容而不能一起工作的类可以一起工作。

	 角色	说明
	Target	客户端期望的接口（抽象类或接口）
	Adaptee	需要被适配的类
	Adapter	通过继承或组合的方式，把 Adaptee 转换为 Target
	Client	使用 Target 接口的类

		 +-----------+         +----------------+
		 |  Client   |-------> |    Target      |
		 +-----------+         +----------------+
						^  ▲
						|  ||
			+-----------+  +-------------+
			|                            |
	 +--------------+         +-----------------+
	 |  Adapter     |-------> |    Adaptee      |
	 +--------------+         +-----------------+


	优点						说明
	解耦			客户端和被适配类解耦，只依赖接口
	可复用			可以复用已有类
	符合开闭原则	不修改已有类，扩展适配器即可

*/

// 1. Target 接口:Shape
class Shape {
public:
	virtual void draw() const = 0;
	virtual ~Shape() = default;
};

//2. Adaptee 类:TextView
class TextView {
public:
	void displayText() const {
		std::cout << "Drawing a TextView!" << std::endl;
	}
};

//3. Adapter 类: TextShapeAdapter
class TextShapeAdapter : public Shape
{
private:
	TextView* textView;

public:
	explicit TextShapeAdapter(TextView* tv)
		:textView(tv)
	{}

	void draw() const override
	{
		textView->displayText(); // 调用被适配的方法
	}
};

class Circle : public Shape {
public:
	void draw() const override {
		std::cout << "Drawing a Circle!" << std::endl;
	}
};

//int main()
//{
//	std::vector<std::shared_ptr<Shape>> shapes;
//
//	// 添加普通图形
//	shapes.push_back(std::make_shared<Circle>());
//
//	TextView* tv = new TextView();
//	shapes.push_back(std::make_shared<TextShapeAdapter>(tv));
//
//	for (const auto& sp : shapes)
//	{
//		sp->draw();
//	}
//	delete tv;
//	
//	return 0;
//}
