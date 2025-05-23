#include <iostream>
#include <string>
#include <stddef.h>
#include <cstring>
using namespace std;

// 第一部分 - 基础
// day-2025-5-20
//template<typename T>
//inline T const& Max(T const& a, T const& b)
//{
//	return a > b ? a : b;
//}
//
//template<typename T>
//inline T* const& Max(T* const& a, T* const& b)
//{
//	return *a > *b ? a : b;
//}
//
//inline char const* const& Max(char const* const& a, char const* const& b)
//{
//	return std::strcmp(a, b) < 0 ? b : a;
//}


//int main()
//{
	//int a = 7;
	//int b = 42;
	//cout << "Max(a,b): " << Max(a, b) << endl;

	//std::string s1 = "hello";
	//std::string s2 = "world";
	//cout << "Max(s1,s2): " << Max(s1, s2) << endl;

	//int* p1 = &b;
	//int* p2 = &a;
	//cout << "Max(p1,p2): " << *Max(p1, p2) << endl;

	//char const* str1 = "David";
	//char const* str2 = "Alice";
	//cout << "Max(str1,str2): " << Max(str1, str2) << endl;


	// inline T const& Max(T const& a, T const& b)
	/*
	int i = 42;
	cout << "Max(7,i): " << Max(7, i) << endl;

	double f1 = 3.4;
	double f2 = 6.7;
	cout << "Max(f1,f2): " << Max(f1, f2) << endl;

	string s1 = "hello";
	string s2 = "world";
	cout << "Max(s1,s2): " << Max(s1, s2) << endl;
	*/
//}

//#include "stack1.h"
// 类模板

// 局部特化
//template<typename T1, typename T2>
//class MyClass{};
//
//template<typename T>
//class MyClass<T, T> {};
//
//template<typename T>
//class MyClass<T, int>{};
//
//template<typename T1, typename T2>
//class MyClass<T1*, T2*>{};
//
//template<typename T>
//class MyClass<T*, T*>{};
//
//
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<std::string> stringSt;
//
//		intSt.push(7);
//		cout << "intSt.top(): " << intSt.top() << endl;
//
//		stringSt.push("hello");
//		cout << "stringSt.top(): " << stringSt.top() << endl;
//		stringSt.pop();
//		stringSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//}

//#include <deque>
//#include "stack3.h"
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<double, std::deque<double>> doubleSt;
//		intSt.push(7);
//		cout << "intSt.top(): " << intSt.top() << endl;
//
//		doubleSt.push(3.14);
//		cout << "doubleSt.top(): " << doubleSt.top() << endl;
//		doubleSt.pop();
//		doubleSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception : " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//}


//2025-5-21
// 第四章-非类型模板参数
//#include "stack4.h"

//int main()
//{
//	try
//	{
//		Stack<int, 20> int20St;
//		Stack<int, 40> int40St;
//		Stack<string, 20> stringSt;
//
//		int20St.push(7);
//		cout << "int20St.top(): " << int20St.top() << endl;
//
//		int40St.push(42);
//		cout << "int40St.top(): " << int40St.top() << endl;
//
//		stringSt.push("helo");
//		cout << "stringSt.top(): " << stringSt.top() << endl;
//		stringSt.pop();
//		stringSt.pop();
//
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//		return EXIT_FAILURE;
//	}
//
//
//	return 0;
//}

// 非类型的函数模板参数
//template<typename T, int N>
//T addN(T const& x)
//{
//	return x + N;
//}
//
//int main()
//{
//	int i = 7;
//	double d = 3.14;
//	cout << "addN<int, 10>(i): " << addN<int, 10>(i) << endl;
//	cout << "addN<double, 5>(d): " << addN<double, 5>(d) << endl;
//	return 0;
//}

// 第五章-技巧性基础知识
//template<typename T>
//class MyClass
//{
//	typename T::SubType* ptr; // 不使用 typename ,会 被误以为 T::SubType 和 ptr 的乘积
//};
//
//template<typename T>
//class Base
//{
//public:
//	void Exit()
//	{
//		cout << "Base::Exit()"<<endl;
//	}
//};
//
//template<typename T>
//class Derived : Base<T> {
//public:
//	void foo()
//	{
//		Base<T>::Exit();
//	}
//};
//
//int main()
//{
//	Derived<int> d;
//	d.foo();
//}

//#include "stack5.h"

//int main()
//{
//	Stack<int> intSt;
//	Stack<double> doubleSt;
//	doubleSt = intSt;
//
//	return 0;
//}
// 
//#include "stack6.h"
//// 模板的模板参数
//int main()
//{
//	Stack<int, std::deque> intSt;
//	Stack<double, std::deque> doubleSt;
//	intSt.push(7);
//	cout << "intSt.top(): " << intSt.top() << endl;
//	doubleSt.push(3.14);
//	cout << "doubleSt.top(): " << doubleSt.top() << endl;
//	doubleSt.pop();
//	doubleSt.pop();
//
//	return 0;
//}
// 
// 
//#include <deque>
//#include "stack7.h"
//int main()
//{
//	try
//	{
//		Stack<int> intSt;
//		Stack<double> doubleSt;
//		intSt.push(7);
//		intSt.push(42);
//
//		doubleSt.push(7.7);
//
//		doubleSt = intSt;
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//		std::cout << doubleSt.top() << endl;
//		doubleSt.pop();
//	}
//	catch (const std::exception& e)
//	{
//		std::cerr << "Exception: " << e.what() << std::endl;
//	}
//
//}

// 零初始化
//template<typename T>
//void foo()
//{
//	T t = T();
//	cout << "t: " << t << endl;
//}
//
//int main()
//{
//	foo<int>();
//	foo<double>();
//	foo<std::string>();
//	foo<int*>();
//	foo<std::string*>();
//	foo<int(*)()>();
//	foo<std::string(*)()>();
//	return 0;
//}

//#include <iostream>
//#include <typeinfo>
//
//template<typename T>
//void ref(T const& x)
//{
//	std::cout << "x in ref(T const&): " << typeid(x).name() << endl;
//}
//
//template<typename T>
//void nonref(T x)
//{
//	std::cout << "x in nonref(T) : " << typeid(x).name() << endl;
//}
//
//template<typename T, int N, int M>
//T const* max(T const (&a)[N], T const (&b)[M]) // 引用
//{
//	return a[0] > b[0] ? a : b;
//}
//
//int main()
//{
//	int a[5] = { 2, 2, 3, 4, 5 };
//	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int const* p = max(a, b);
//	std::cout << "p: " << *p << std::endl;
//
//	ref("hello");		// x in ref(T const&): char const [6]
//	nonref("hello");    // x in nonref(T) : char const * __ptr64
//
//	string s = "world";
//	::ref(s);
//	nonref(s);
//}


// 第六章-模板实战
//day-2025-5-22
//#include <algorithm>
//#include "tracer.h"
//int main()
//{
//	SortTracer input[] = { 7, 3, 5, 6, 4, 2, 0, 1, 9 ,8 };
//	for (int i = 0; i < 10;++i)
//	{
//		cerr << input[i].val() << " ";
//	}
//	std::cerr << std::endl;
//
//	long created_at_start = SortTracer::creations();
//	long max_live_at_start = SortTracer::max_live();
//	long assigned_at_start = SortTracer::assignments();
//	long compared_at_start = SortTracer::comparisons();
//
//	//执行算法
//	std::cerr << "---[Start std::sort() ]-------------------------" << std::endl;
//	std::sort(&input[0], &input[9] + 1);
//	std::cerr << "---[End std::sort() ]-------------------------" << std::endl;
//
//	// 确认结果
//	for (int i = 0; i < 10; ++i)
//	{
//		cerr << input[i].val() << " ";
//	}
//	std::cerr << std::endl;
//
//	std::cerr << "std::sort() of 10 SortTracer's"
//		<< " was performed by: \n"
//		<< SortTracer::creations() - created_at_start
//		<< " temporary tracers \n"
//		<< "up to "
//		<< SortTracer::max_live()
//		<< " tracers at the same time ("
//		<< max_live_at_start << " before) \n"
//		<< SortTracer::assignments() - assigned_at_start
//		<< " assignments \n"
//		<< SortTracer::comparisons() - compared_at_start
//		<< " comparisons \n";
//}


// day-2025-5-23
// 第八章-深入模板基础

// day-2025-5-24
// 第九章- 模板中的名称
//template<typename T>
//class C
//{
//	friend void f();
//	friend void f(C<T> const&);
//};
//
//void g(C<int> const& c)
//{
//	f(c); // 错误
//	f(); // 错误
//}
//
//int main()
//{
//	C<int> c;
//	f(c); // 错误
//	f(); // 错误
//	g(c); // 错误
//	return 0;
//}


//int C;
//class C
//{
//private:
//	int i[2];
//public:
//	static int f()
//	{
//		return sizeof(C);
//	}
//};
//
//int f()
//{
//	return sizeof(C);
//}
//
//
//class BX
//{
//public:
//	void f(int);
//	void f(char const*);
//	void g();
//};
//
//class DX : private BX
//{
//public:
//	using BX::f; // 允许访问 BX::f()
//};
//
//int main()
//{
//	std::cout << "C::f() =  " << C::f() << std::endl;
//	std::cout << "::f() =  " << f() << std::endl;
//	return 0;
//}

// 非依赖性基类
// 基类的类型不依赖于模板参数，即基类在模板定义时就已经完全确定。
//struct Base {
//	void foo() {}
//};
//
//template <typename T>
//struct Derived : Base  // // Base 不依赖 T，是非依赖性基类
//{  
//	void bar() 
//	{
//		foo();  // 直接调用 Base::foo()
//	}
//};
//基类的成员（如 foo()）在模板定义阶段就可以被直接查找，编译器知道它的存在。
//如果基类成员不存在，会在模板定义阶段报错（而非实例化阶段）。

// 依赖性基类
//template <typename T>
//struct Base {
//	void foo() { cout << "Base::foo()" << endl; }
//};
//
//template <typename T>
//struct Derived : Base<T> {  // Base<T> 依赖 T，是依赖性基类
//	void bar() {
//		// foo();  // 直接调用会报错！因为 foo() 是依赖性名称
//		this->foo();  // 正确：通过 this 或 Base<T>::foo() 访问
//	}
//};
//
//int main()
//{
//	Derived<int> d;
//	d.bar();  // 正确调用 Derived::bar()，间接访问 Base::foo()
//	return 0;
//}

template <typename Derived>
struct Base {  // 依赖性基类
	void foo() {
		static_cast<Derived*>(this)->impl();  // 调用派生类的实现
	}
};

struct MyDerived : Base<MyDerived> {  // CRTP
	void impl() {
		std::cout << "MyDerived::impl()\n";
	}
};

int main() {
	MyDerived d;
	d.foo();  // 输出 "MyDerived::impl()"
}