#include <iostream>
#include <vector>

using namespace std;

//Factory Method ��������ģʽ
/*
���壺
��������ģʽͨ������һ�����ڴ�������Ľӿڣ����������ʵ������һ���ࡣ�������������ʵ�����Ƴٵ������С�

��Ҫ��ɫ��

	Product����Ʒ�ӿ�/�����ࣩ
	ConcreteProduct�������Ʒ�ࣩ
	Creator�����󹤳��ࣩ
	ConcreteCreator�����幤���ࣩ

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

 |            ģʽ                 |			˵��		     	|				  ����                   |
| ---------------------------------|------------------------------- | -------------------------------------- |
|   Simple Factory  ���򵥹�����   | ���������������жϷ��ز�ͬ��Ʒ | ������ GoF 23 �����ģʽ��Υ������ԭ�� |
|   Factory Method  ������������   | ÿ�ֲ�Ʒ��Ӧһ����������       | ���㿪��ԭ�򣬽ṹ������               |
|   Abstract Factory  �����󹤳��� | ����  һ����ز�Ʒ �Ľӿ�      | �ʺ϶��ֲ�Ʒ�壨�� GUI �׼���          |
|   Builder      				   | �𲽹��츴�Ӷ���               | ����ע�������̣����ǲ�Ʒ����           |
|   Prototype    				   | ͨ���������ж��󴴽��¶���     | �ʺ϶�������۴�ĳ���               |
|   Singleton                      | ȷ��һ����ֻ��һ��ʵ��         | ��עʵ��Ψһ�ԣ������������Ʒ         |

*/

//��Ʒ��ӿں;���ʵ��
class Product
{
public:
	virtual void use() = 0; // ���󷽷�
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

// ������ӿں;���ʵ��
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