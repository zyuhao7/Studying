#include<iostream>
#include<string>
using namespace std;

#if 0
// 
// A是基类
class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;
};
// B是派生类，继承到派生类里面的成员访问限定要小于等于继承方式
class B : public A
{
public:
	int md;
protected:
	int me;
private:
	int mf;
};

// 基类的private私有成员，无论采用什么继承方式，在派生类里面都是可以继承下来，但是无法访问
// protected和private的区别。基类的private私有成员，在派生类和外部都不能直接访问；
//                           基类的protected的成员，在派生类中是可以访问的，在外部不能访问。

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	// 必须通过调用基类的构造函数来初始化从基类继承来的成员
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
private:
	int mb;
};
int main()
{
	Derive d(10);
	return 0;
}

//                                   重载、隐藏、覆盖

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }

	void show() { cout << "Base::show()" << endl; } // @1
	void show(int) { cout << "Base::show(int)" << endl; } // @2
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; } // @3

private:
	int mb;
};
int main()
{
	Derive d(10);
	d.show();        // 调用的是派生类自己的show方法
	d.Base::show();  // 指定了作用域，调用的是派生类从基类继承来的show方法
	//d.show(10);    // 编译错误，不能调用，派生类的show方法把基类继承来的show方法给隐藏了
	return 0; 
}

// 重载: 一组函数必须在统一作用域中,函数名相同, 参数列表不同,才能称做函数重载, @1 和 @2 是函数重载. @2 @3虽然函数名相同, 参数列表不同,
// 但它们不在同一个作用域, 不是重载关系.

// 隐藏: 指的是基类和派生类中的同名成员, 只要成员名字相同, 用派生类对象调用该成员名字时,就发生了隐藏(隐藏了基类的同名成员), 派生类默认
//调用的都是自己的成员, 如果要调用基类的同名函数, 需要添加基类的作用域, 上面代码中 @1 和 @3, @2 和 @3 都是隐藏关系.

// 覆盖: 指的是基类和派生类中的同名成员函数, 不仅函数名相同、 返回值相同、 参数列表也相同, 而且基类的该函数是 virtual 虚函数, 那么派生类
//的同名方法自动被处理成虚函数, 它们之间的关系是覆盖关系. 上面代码中没有覆盖关系的函数.




//										虚函数、vfptr和vftable



class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
	// 下面这个show()函数是虚函数
	virtual void show() { cout << "Base::show()" << endl; } // @1
	// 下面这个show(int)函数是虚函数
	virtual void show(int) { cout << "Base::show(int)" << endl; } // @2
	// 下面这个show(int, int)函数是普通函数
	void show(int, int) { cout << "Base::show(int, int)" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; } // @3 // 与1 构成覆盖.
private:
	int mb;
};

// 基类 Base里面有虚函数, 编译器会怎么处理?
// 处理过程一般是: 如果一个类有虚函数, 那么编译器在编译阶段, 会给当前类型生成一张虚函数表,虚函数表里面放的是虚函数的地址, 还有 RTTI指针
//信息; 这张虚函数表在代码运行阶段, 被加载到.rodata段, 也就是说只读不写, 这张虚函数表就是 vftable.



//											静态绑定和动态绑定

//静态绑定: 编译时期函数的调用就是确定的.
//动态绑定: 函数的调用要到运行时期才能确定.

class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
	// 下面这个show()函数是虚函数，为了演示动态绑定
	virtual void show() { cout << "Base::show()" << endl; }
	// 下面这个show(int, int)函数是普通函数，为了演示静态绑定
	void show(int, int) { cout << "Base::show(int, int)" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data) :Base(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};
int main()
{
	Derive d(10);
	Base* p = &d;
	/*
	  这里p的类型是Base，Base下的show(int,int)是普通函数，这里是静态绑定，
	  就是编译阶段就确定了，调用的是Base::show(int, int)函数，可以通过其
	  汇编指令查看是call Base::show...
	*/
	p->show(0, 0);
	/*
	  这里p的类型是Base，Base下的show()是虚函数，这里是动态绑定，其指令首先
	  访问p指向的对象的前4个字节vfptr，再访问对应的vftable，然后从vftable
	  中取虚函数的地址进行函数调用，只有在运行的时候，才能取到虚函数表中存放的
	  函数地址，因此是运行时的绑定，称作动态函数绑定
	*/
	p->show();

	cout << sizeof(Base) << endl; // 8
	cout << sizeof(Derive) << endl; //  12
	/*
	  这里p的类型是Base，因为Base里面有虚函数，这里*p识别的就是RTTI类型（识别RTTI
	  类型也是通过指针访问对象内存的vfptr，再访问vftable，通过RTTI指针取RTTI类型信息）；
	  如果p的类型Base里面没有虚函数，那么*p识别的就是编译时期的类型。
	*/
	cout << typeid(*p).name() << endl; // class Derive

	return 0;
}


//													多态
/* 多态指的是, 用基类指针或引用指向从它继承的一组派生类对象, 调用派生类的同名覆盖方法, 基类指针指向哪个派生类对象, 就会调用
* 相应派生类对象的同名覆盖方法. 怎么做到的呢? 因为通过基类指针调用派生类的同名覆盖方法时, 发生了动态绑定, 访问了基类指针指向
* 对象的虚函数表 vftable, 从这张 vftable 中取出来的就是这个派生类重写的虚函数的地址, 然后进行调用, 就可以做到了基类指针指向
* 谁, 就能调用谁的方法.
*/


//														抽象类
class Animal
{
public:
	Animal(string name)
		:_name(name){}

	virtual void bark() = 0; // 纯虚函数.
protected:
	string _name;
};

// Animal是一个抽象类, 抽象类不能定义对象, 但是可以定义指针或者引用, 一般把基类往往设计成抽象类, 因为定义基类的初衷,并不是
// 为了让抽象化某个实体的类型. 原因如下:
// 1. 基类给所有派生类提供公共的属性和方法, 通过继承达到代码复用的目的.
// 2. 基类可以给所有派生类提供统一的纯虚函数接口, 派生类通过函数重写, 达到多态调用的目的.


//													虚析构函数

class Base // 基类定义
{
public:
	Base(int data=10):_ptrb(new int(data))
	{ cout << "Base()" << endl; }
	// 改为virtual 析构函数. 
	virtual ~Base() { delete _ptrb; cout << "~Base()" << endl; }
protected:
	int *_ptrb;
};
class Derive : public Base // 派生类定义
{
public:
	Derive(int data=20):Base(data), _ptrd(new int(20))
	{ cout << "Derive()" << endl; }
	~Derive() { delete _ptrd; cout << "~Derive()" << endl; }
private:
	int *_ptrd;
};
int main()
{
	Base *p = new Derive();
	delete p; // 只调用了Base的析构函数，没有调用Derive派生类的析构函数
	return 0;
}
#endif
