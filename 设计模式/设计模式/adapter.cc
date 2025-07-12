#include <iostream>
#include <vector>

using namespace std;


// day-2025-7-12
/*
	������ģʽ��һ�ֽṹ�����ģʽ��������һ����Ľӿ�ת���ɿͻ�������������һ���ӿڡ�
	������ģʽʹ��ԭ�����ڽӿڲ����ݶ�����һ�����������һ������

	 ��ɫ	˵��
	Target	�ͻ��������Ľӿڣ��������ӿڣ�
	Adaptee	��Ҫ���������
	Adapter	ͨ���̳л���ϵķ�ʽ���� Adaptee ת��Ϊ Target
	Client	ʹ�� Target �ӿڵ���

		 +-----------+         +----------------+
		 |  Client   |-------> |    Target      |
		 +-----------+         +----------------+
									^  ��
									|  ||
						+-----------+  +-------------+
						|                            |
				 +--------------+         +-----------------+
				 |  Adapter     |-------> |    Adaptee      |
				 +--------------+         +-----------------+


	�ŵ�						˵��
	����			�ͻ��˺ͱ���������ֻ�����ӿ�
	�ɸ���			���Ը���������
	���Ͽ���ԭ��	���޸������࣬��չ����������

*/

// 1. Target �ӿ�:Shape
class Shape {
public:
	virtual void draw() const = 0;
	virtual ~Shape() = default;
};

//2. Adaptee ��:TextView
class TextView {
public:
	void displayText() const {
		std::cout << "Drawing a TextView!" << std::endl;
	}
};

//3. Adapter ��: TextShapeAdapter
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
		textView->displayText(); // ���ñ�����ķ���
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
//	// �����ͨͼ��
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