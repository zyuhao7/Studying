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

