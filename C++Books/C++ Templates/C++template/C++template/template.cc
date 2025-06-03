#include <iostream>
#include <string>
#include <stddef.h>
#include <cstring>
#include <vector>
#include <list>
#include <stack>
#include <typeinfo>
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

//template <typename Derived>
//struct Base {  // 依赖性基类
//	void foo() {
//		static_cast<Derived*>(this)->impl();  // 调用派生类的实现
//	}
//};
//
//struct MyDerived : Base<MyDerived> {  // CRTP
//	void impl() {
//		std::cout << "MyDerived::impl()\n";
//	}
//};
//
//int main() {
//	MyDerived d;
//	d.foo();  // 输出 "MyDerived::impl()"
//}

// 2025-5-25
// 第十章-实例化
//class MyInt
//{
//public:
//	MyInt(int i);
//};
//
//MyInt operator-(MyInt const&);
//bool operator>(MyInt const&, MyInt const&);
//
//typedef MyInt Int;
//template<typename T>
//void f(T i)
//{
//	if (i > 0)
//	{
//		g(-i);
//	}
//}
//
//void g(Int)
//{
//	f<Int>(42);
//}

//template<typename T>
//void f(T x)
//{
//	g1(x);
//}
//
//void g1(int)
//{
//
//}
//
//
//int main()
//{
//	f(7);
//	return 0;
//}

// 第十一章-模板实参推演
//template<int N>
//class X {
//public:
//	typedef int I;
//	void f(int) 
//	{
//		cout << "X::f(int) " << endl;
//	}
//};
//
//template<int N>
//void fppm(void (X<N>::* p)(typename X<N>::I)) {
//	// 这里的 p 是一个指向成员函数的指针
//	// 你可以在这里使用 p 来调用 X<N>::f
//	X<N> x;
//	(x.*p)(42); // 调用成员函数
//};
//
//
//int main()
//{
//	fppm(&X<33>::f);
//}

//class S{};
//
//template<typename T>
//class Wrapper
//{
//private:
//	T object;
//
//public:
//	Wrapper(T obj) :object(obj){}
//
//	friend void f(Wrapper<T> const& a)
//	{
//		cout << "f(Wrapper<T> const& a)" << endl;
//	}
//};
//
//int main()
//{
//	S s;	
//	Wrapper<S> w(s); 
//	f(w);		// f(Wrapper<T> const& a)
//	//f(s);		// 错误：没有匹配的函数
//}

// day-2025-5-26
// 第十二章-特化与重载

//template<typename T>
//int f(T)
//{
//	return 1;
//}
//
//template<typename T>
//int f(T*)
//{
//	return 2;
//}
//
//template<typename T>
//std::string f1(T)
//{
//	return "Template";
//}
//
//std::string f1(int&)
//{
//	return "Nontemplate";
//}
//
//int main()
//{
//	std::cout << f<int*>((int*)0) << endl; // 1
//	std::cout << f<int>((int*)0) << endl;  // 2
//	std::cout << f(0) << endl;			   // 1	
//	std::cout << f((int*)0) << endl;	   // 2
//
//	int x = 7;
//	std::cout << f1(x) << endl;			// Nontemplate
//}

//template<typename T>
//class Invalid{};
//
//Invalid<double> x; // 显式专用化；已实例化“Invalid<double>”
//
//template<>
//class Invalid<double>;

//template<typename T>
//int f(T)
//{
//	return 1;
//}
//
//template<typename T>
//int f(T*)
//{
//	return 2;
//}
//template<>
//int f(int)
//{
//	return 3;
//}
//
//template<>
//int f(int*)
//{
//	return 4;
//}
//
//template<typename T>
//int f(T, T x = 42)
//{
//	return x;
//}

//template<>
//int f(int, int = 35) // err f: 函数模板的显式专用化或实例化不能有任何默认参数
//{
//	return 0;
//}

//template<typename T>
//int g(T, T x = 42)
//{
//	return x;
//}
//
//template<>
//int g(int, int y)
//{
//	return y / 2;
//}
//
//int main()
//{
//	cout << g(0) << endl; // 21
//}

// day-2025-5-27
// 第十三章-未来的方向
//typedef vector<list<int>> ListOfIntLists; // 以前是错误,尖括号不能连写.
//
//template<typename T>
//class Table
//{
//public:
//	typedef vector<list<T>> Type;
//};
//
//int main()
//{
//	Table<int>::Type table; // 正确，使用 typedef 定义的类型
//
//	
//	return 0;
//}

//class Base {
//public:
//	virtual Base* clone() const {
//		return new Base(*this);
//	}
//	virtual ~Base() {}
//};
//
//class Derived : public Base {
//public:
//	// 协变返回类型 - 返回 Derived* 而非Base*
//	virtual Derived* clone() const override {
//		return new Derived(*this);
//	}
//};

//day-2025-5-28
// 第十四章-模板的多态力量
// 第十五章-trait 和 policy
// s1.h
//namespace A
//{
//	int f(double);
//}
//
//// s2.h
//namespace B
//{
//	using A::f;
//	void g();
//}
//// s3.h
//namespace A
//{
//	int f(int);
//}
//// s4.h
//void B::g()
//{
//	f(1);
//}



// day-2025-5-29
// 第十五章-trait 和 policy类

//#include <iterator>
//template<typename Iter>
//inline typename std::iterator_traits<Iter>::value_type
//accum(Iter st, Iter ed)
//{
//	typedef typename std::iterator_traits<Iter>::value_type VT;
//	VT total = VT();
//	while (st != ed)
//	{
//		total += *st;
//		++st;
//	}
//	return total;
//}

// 普通指针
//namespace std
//{
//	template<typename T>
//	struct iterator_traits<T*> {
//		typedef T									value_type;
//		typedef ptrdiff_t							difference_type;
//		typedef random_access_iterator_tag			iterator_category;
//		typedef T*									pointer;
//		typedef T&									reference;
//	};
//}

//template<typename T>
//class TypeSize
//{
//public:
//	static size_t const value = sizeof(T);
//};
//int main()
//{
//	cout << "TypeSize<int>::value = " << TypeSize<int>::value << endl;
//
//}


//template<typename T>
//class ElementT;	// 基本模板
//
//template<typename T>
//class ElementT<std::vector<T>> {	//局部特化
//public:
//	typedef T Type;
//};
//
//template<typename T>
//class ElementT<std::list<T>> {     // //局部特化
//public:
//	typedef T Type;
//};
//
//template<typename T>
//class ElementT<std::stack<T>> {     // //局部特化
//public:
//	typedef T Type;
//};
//
//template<typename T>
//void print_element_type(T const& c)
//{
//	cout << "Container of " << typeid(typename ElementT<T>::Type).name() << " elements." << endl;
//}
//
//int main()
//{
//	stack<bool> st;
//	print_element_type(st);
//}

//template<typename C>
//class EelementT
//{
//public:
//	typedef typename C::value_type Type;
//};

//template<typename T>
//class IsClassT {
//private:
//	typedef char One;
//	typedef struct{ char a[2]; } Two;
//
//	template<typename C>
//	static One test(int C::*){}
//	template<typename C>
//	static Two test(...){} // ... 匹配非类类型
//
//public:
//	enum { Yes = sizeof(test<T>(0)) == sizeof(One) };
//	enum { No = !Yes };
//};
//
//
//class MyClass{};
//struct MyStruct{};
//union MyUnion{};
//void myfunc() {};
//enum E{e1}  e;
//
//template<typename T>
//void check()
//{
//	if (IsClassT<T>::Yes)
//	{
//		cout << "IsClassT" << endl;
//	}
//	else
//	{
//		cout << "!IsClassT" << endl;
//	}
//}
//
//template<typename T>
//void checkT(T)
//{
//	check<T>();
//}
//
//int main()
//{
//	cout << "int: ";
//	check<int>();
//
//	cout << "MyClass: ";
//	check<MyClass>();
//	
//	cout << "MyStruct: ";
//	MyStruct s;
//	checkT(s);
//
//	cout << "MyUnion: ";
//	check<MyUnion>();
//
//	cout << "enum: ";
//	checkT(e);
//
//	cout << "myfunc():";
//	checkT(myfunc);
//}

// 基本模板, 根据第一个实参来决定, 是选择第二个实参, 还是选择第三个实参
//template<bool C, typename Ta, typename Tb>
//class IfThenElse;
//
//// 局部特化, true的话选择第二个实参
//template<typename Ta, typename Tb>
//class IfThenElse<true, Ta, Tb>
//{
//public:
//	typedef Ta ResultT;
//};

// 局部特化, false的话选择第三个实参
//template<typename Ta, typename Tb>
//class IfThenElse<false, Ta, Tb>
//{
//public:
//	typedef Tb ResultT;
//};


// 针对类型提升的基本模板
//template<typename T1, typename T2>
//class Promotion {
//public:
//	typedef typename IfThenElse<(sizeof(T1)> sizeof(T2)),
//		T1, typename IfThenElse<(sizeof(T1)< sizeof(T2)),
//		T2,
//		void
//		>::ResultT
//		>::ResultT ResultT;
//};
//
//template<typename T>
//class Promotion<T, T>
//{
//public:
//	typedef T resultT;
//};
//
//#define MK_PROMOTION(T1, T2, Tr) \
//template<> class Promotion<T1, T2>{ \
//	public: \
//	typedef Tr ResultT; \
//};	\
//template<> class Promotion<T2, T1> {\
//public: \
//		typedef Tr ResultT; \
//}; 
//MK_PROMOTION(bool, char, int)
//MK_PROMOTION(bool, unsigned char, int)
//// ...
//class Array{};
//
//template<typename T1, typename T2>
//class Promotion<Array<T1>, Array<T2>>
//{
//public:
//	typedef Array<typename Promotion<T1, T2>::ResultT> ResultT;
//};
//
//template<typename T>
//class Promotion<Array<T>, Array<T>>
//{
//public:
//	typedef Array<typename Promotion<T, T>::ResultT> ResultT;
//};

//template<typename T>
//class RParam
//{
//public:
//	typedef typename IfThenElse<sizeof(T) <= 2 * sizeof(void*)>,
//		T,
//		T const& > ::ResultT Type;
//};

//template<typename T>
//class RParam {
//public:
//	typedef typename IfThenElse<IsClassT<T>::No,
//		T,
//		Tconst&>::ResultT Type;
//};

// day-2025-5-30
// 第十六章-模板与继承
//class EmptyClass{
//	typedef int Int;
//};
//
//class EmptyToo : public EmptyClass{};
//class EmptyThree : public EmptyToo {};
//class NonEmpty : public  EmptyClass, public EmptyToo{};
//
//
//int main()
//{
//	cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) << endl;
//	cout << "sizeof(EmptyToo): " << sizeof(EmptyToo) << endl;
//	cout << "sizeof(EmptyThree): " << sizeof(EmptyThree) << endl;
//	cout << "sizeof(NonEmpty): " << sizeof(NonEmpty) << endl;
//}

//template<typename T1, typename T2>
//class Myclass
//{
//private:
//	T1 a;
//	T2 b;
//};
//
//template<typename T1, typename T2>
//class Myclass : private T1, private T2
//{
//
//};

// CRTP 奇异递归模板模式
//template<typename Derived>
//class CuriousBase{};
//
//class Curious : public CuriousBase<Curious>{};
//template<typename T>
//class CuriousTemplate : public CuriousBase<CuriousTemplate<T>>{};
//
//
//template<template<typename> class Derived>
//class MoreCuriousBase{};
//
//template<typename T>
//class MoreCurious : public MoreCuriousBase<MoreCurious>{};

// 参数化虚拟性
//class NonVirtual{};
//class Virtual
//{
//public:
//	virtual void foo(){}
//};
//
//template<typename VBase>
//class Base : private VBase
//{
//public:
//	// foo的虚拟性依赖于他在基类VBase中的生命
//	void foo() {
//		cout << "Base::foo()" << endl;
//	}
//};
//
//template<typename V>
//class Derived : public Base<V>
//{
//public:
//	void foo()
//	{
//		cout << "Derived::foo()" << endl;
//	}
//};
//
//int main()
//{
//	Base<NonVirtual>* p1 = new Derived<NonVirtual>;
//	p1->foo();
//	Base<Virtual>* p2 = new Derived<Virtual>;
//	p2->foo();
//}


// day-2025-6-1
// 第十七章-元编程 -metaprogram
//template<int N>
//class Pow3 {
//public:
//
//	enum {result = 3 *  Pow3<N - 1>::result};
//};
//
//template<>
//class Pow3<0>
//{
//public:
//	enum { result = 1 };
//};

//template<int N>
//class Pow3
//{
//public:
//	static int const result = 3 * Pow3<N - 1>::result;
//};
//
//template<>
//class Pow3<0>
//{
//public:
//	static int const result = 1;
//};

// 计算平方根 sqrt(N)
//template<int N, int LO = 0, int HI = N>
//class Sqrt
//{
//public:
//	enum {mid = (LO + HI + 1) / 2 };
//
//	enum { result = (mid * mid > N) ? Sqrt<N, LO, mid - 1>::result : Sqrt<N, mid, HI>::result};
//};
//
//template<int N, int M>
//class Sqrt<N, M, M>
//{
//public:
//	enum {result = M};
//};


//template<bool C, typename Ta, typename Tb>
//class IfThenElse;
////
////// 局部特化, true的话选择第二个实参
//template<typename Ta, typename Tb>
//class IfThenElse<true, Ta, Tb>
//{
//public:
//	typedef Ta ResultT;
//};
//
//// 局部特化, false的话选择第三个实参
//template<typename Ta, typename Tb>
//class IfThenElse<false, Ta, Tb>
//{
//public:
//	typedef Tb ResultT;
//};
//template<int N, int LO = 0, int HI = N>
//class Sqrt
//{
//public:
//	enum {mid = (LO + HI + 1) / 2 };
//
//	typedef typename IfThenElse< (mid* mid > N),
//		Sqrt<N, LO, mid - 1>,
//		Sqrt<N, mid, HI >>::ResultT
//		subT;
//	enum {result = subT::result };
//};
//
//template<int N, int S>
//class Sqrt<N, S, S> {
//public:
//	enum {result = S};
//};

//int main()
//{
	//cout << Pow3<7>::result << endl;
	//cout << Pow3<6>::result << endl;
	//cout << Sqrt<16>::result << endl;

	//std::cout << Sqrt<16>::result << std::endl;  // 输出 4
	//std::cout << Sqrt<25>::result << std::endl;  // 输出 5
	//std::cout << Sqrt<10>::result << std::endl;  // 输出 3（因为 3²=9 ≤ 10 < 16=4²）

//	return 0;
//}

//template<typename T>
//inline T dot_product(int dim, T* a, T* b)
//{
//	T result = T();
//	for (int i = 0; i < dim; ++i)
//	{
//		result += a[i] * b[i];
//	}
//	return result;
//}
//
//int main()
//{
//	int a[3] = { 1, 2, 3 };
//	int b[3] = { 5,6,7 };
//	cout << dot_product(3, a, b) << endl;
//	cout << dot_product(3, a, a) << endl;
//
//}

//day-2025-6-2 
// 第十八章-模板表达式
// 
// // 一个简单的向量类
//template<typename T>
//class Vector {
//	T* data;
//	size_t size;
//public:
//	Vector(size_t n) : size(n), data(new T[n]) {}
//	~Vector() { delete[] data; }
//
//	T operator[](size_t i) const { return data[i]; }
//	T& operator[](size_t i) { return data[i]; }
//	size_t getSize() const { return size; }
//};
//
//// 表达式模板基类
//template<typename E>
//class VecExpression {
//public:
//	double operator[](size_t i) const {
//		return static_cast<const E&>(*this)[i];
//	}
//	size_t size() const {
//		return static_cast<const E&>(*this).size();
//	}
//};
//
//// 向量加法表达式
//template<typename E1, typename E2>
//class VecSum : public VecExpression<VecSum<E1, E2>> {
//	const E1& u;
//	const E2& v;
//public:
//	VecSum(const E1& u, const E2& v) : u(u), v(v) {}
//	double operator[](size_t i) const { return u[i] + v[i]; }
//	size_t size() const { return u.size(); }
//};
//
//// 重载 + 运算符来生成表达式
//template<typename E1, typename E2>
//VecSum<E1, E2> operator+(const VecExpression<E1>& u,
//	const VecExpression<E2>& v) {
//	return VecSum<E1, E2>(static_cast<const E1&>(u),
//		static_cast<const E2&>(v));
//}
//
//// 赋值运算符，触发实际计算
//template<typename T, typename E>
//Vector<T>& operator<<(Vector<T>& vec, const VecExpression<E>& expr) {
//	for (size_t i = 0; i < vec.getSize(); ++i) {
//		vec[i] = expr[i];
//	}
//	return vec;
//}

// 第十九章-类型区分
//#include "type1.h"
//template<typename T>
//void test(T const& t)
//{
//	if (IsFundaT<T>::Yes)
//	{
//		cout << "T is fundamental type " << std::endl;
//	}
//	else
//	{
//		cout << "T is no fundamental type " << endl;
//	}
//}
//class MyType
//{
//public:
//	MyType();
//	~MyType();
//
//};
//
//MyType::MyType()
//{
//}
//
//MyType::~MyType()
//{
//}
//int main()
//{
//	test(7);
//	test(MyType());
//}

//#include "type3.h"
//template<typename T>
//class IsClassT {
//private:
//	typedef char One;
//	typedef struct{ char a[2]; } Two;
//
//	template<typename C>
//	static One test(int C::*){}
//	template<typename C>
//	static Two test(...){} // ... 匹配非类类型
//
//public:
//	enum { Yes = sizeof(test<T>(0)) == sizeof(One) };
//	enum { No = !Yes };
//};
////
//template<typename T>
//class TypeT
//{
//public:
//	enum {
//		IsFundaT = IsFundaT<T>::Yes,
//		IsPtrT = CompoundT<T>::IsPtrT,
//		IsRefT = CompoundT<T>::IsRefT,
//		IsArrayT = CompoundT<T>::IsArrayT,
//		IsPtrMemT = CompoundT<T>::IsPtrMemT,
//		IsEnumT = IsEnumT<T>::Yes,
//		IsClassT = IsClassT<T>::Yes,
//		IsFuncT = IsFunctionT<T>::Yes
//	};
//};
//
//class MyClass{};
//void myfunc(){}
//enum E{e1};
//template<typename T>
//void check()
//{
//	if (TypeT<T>::IsFundaT)
//	{
//		cout << "IsFundaT" << endl;
//	}
//	if (TypeT<T>::IsPtrT)
//	{
//		cout << "IsPtrT" << endl;
//	}
//	if (TypeT<T>::IsRefT)
//	{
//		cout << "IsRefT" << endl;
//	}
//	if (TypeT<T>::IsArrayT)
//	{
//		cout << "IsArrayT" << endl;
//	}
//	if (TypeT<T>::IsPtrMemT)
//	{
//		cout << "IsPtrMemT" << endl;
//	}
//	if (TypeT<T>::IsEnumT)
//	{
//		cout << "IsEnumT" << endl;
//	}
//	if (TypeT<T>::IsClassT)
//	{
//		cout << "IsClassT" << endl;
//	}
//	if (TypeT<T>::IsFuncT)
//	{
//		cout << "IsFuncT" << endl;
//	}
//}
////
//template<typename T>
//void checkT(T)
//{
//	check<T>();
//	// 对于指针类型, 要检查他们所指向的类型
//	if (TypeT<T>::IsPtrT || TypeT<T>::IsPtrMemT)
//	{
//		check<typename CompoundT<T>::BaseT>();
//	}
//}
//
//int main()
//{
//	cout << "int: ";
//	check<int>();
//
//	cout << "int&: ";
//	check<int&>();
//
//	cout << "char[42]: ";
//	check<char[42]>();
//
//	cout << "MyClass: ";
//	check<MyClass>();
//
//	cout << "ptr to enum: ";
//	E* ptr = 0;
//	checkT(ptr);
//
//	cout << "42: ";
//	checkT(42);
//
//	cout << "myfunc(): ";
//	checkT(myfunc);
//
//	cout << "memptr to array: ";
//	char(MyClass:: * memptr)[] = 0;
//	checkT(memptr);
//}


// day-2025-6-3
// 第二十章-智能指针
//#include "holder.h"
//#include "trule.h"
//
//int main()
//{
//	// 1. 创建一个 Holder，管理一个 int
//	Holder<int> h1(new int(42));
//
//	// 2. 使用 Trule 安全转移资源
//	Trule<int> t(h1); // h1 现在为空
//
//	// 3. 使用 yield() 获取资源并交给新的 Holder
//	Holder<int> h2(t.yield()); // t 现在为空
//
//	// 4. 检查资源是否转移成功
//	std::cout << "h1.get(): " << h1.get() << std::endl; // 输出: 0 (nullptr)
//	std::cout << "h2.get(): " << *h2.get() << std::endl; // 输出: 42
//
//	return 0;
//}

// 引用计数
