#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <tuple>
#include <array>
#include <map>
#include <set>
#include <type_traits>
#include <filesystem>
using namespace std;
using fs = std::filesystem;

// day-2025-5-25
// 折叠表达式
//template<typename... Args>
//constexpr int Sum(Args... args)
//{
//	return (args + ...);
//}
//
//// 想指定一个初始值.
//template<typename... Args>
//auto Func(Args... args)
//{
//	return (args + ... + 100);
//}
//
//// 在 C++17 之前，要实现类似的函数，您必须显式指定递归规则：
//// C++ 14
//auto sum()
//{
//	return 0;
//}
//template<typename Arg, typename... Args>
//auto sum(Arg first, Args... rest)
//{
//	return first + sum(rest...);
//}
//
//template<typename T, typename... Args>
//void PushToVector (std::vector<T>& v, Args&&... args)
//{
//	(v.push_back(std::forward<Args>(args)), ...);
//}
//
//int main()
//{
//	cout << Sum(1, 2, 3, 4, 5) << endl;
//	cout << sum(1, 2, 3, 4, 5) << endl;
//	cout << Func(1, 2, 3, 4, 5) << endl;
//
//	vector<int> lst = { 1, 3, 5, 7 };
//	PushToVector(lst, 2, 4, 6, 8);
//	int res = std::accumulate(lst.begin(), lst.end(), 0, [](int a, int b) {return a + b;});
//	cout << res;
//
//	return 0;
//}

//	模板<auto>

//template<auto n>
//void Func(){
//	cout << "n is : " << n << endl;
//}
//
//// C++ 14
//template<typename Type, Type n>
//void Func2()
//{
//	cout << "n is :" << n << endl;
//}
//
//int main()
//{
//	Func<42>();
//	Func<'c'>();
//
//	Func2<int, 42>();
//	Func2<char, 'c'>();
//}

// 类模板参数推导
// C++ 14
//template<typename T, typename U>
//struct S
//{
//	T first;
//	U second;
//	S(T f, U s)
//	:first(f),
//	second(s)
//	{}
//};
//
//// C++17
//template<typename T, typename U>
//struct S1
//{
//	T first;
//	U second;
//};
//
//template<typename T, typename U>
//S1(const T& f, const U& s) -> S1<T, U>;
//
//int main()
//{
//	// 在 C++17 之前，模板参数推导仅适用于函数，因此，在构造模板类时，始终需要显式指定模板参数: C++14
//	auto p = std::pair<int, char>(10, 'c');
//	auto pr = std::make_pair(10, 'c');
//	pair<char, int> p1 = { 'c', 14 };
//	tuple<char, int, double> t1 = { 'c', 42, 3.14 };
//	S<int, char> s1 = { 10, 'c' };
//
//	//C++ 17
//	pair p2 = { 'c', 42 };
//	tuple t2 = { 'c', 42, 3.14 };
//	S s2 = { 10,'c' };
//
//	S1 s3 = { 42, "hello" };
//	cout << s3.first << " " << s3.second << endl;
//
//	return 0;
//}

// constexpr 表达式
// C++17 使我们能够执行编译时条件分支。这是一个非常强大的工具，在元编程中特别有用。
//template<typename T>
//auto GetValue(T t)
//{
//	if constexpr (std::is_pointer<T>::value)
//		return *t;
//	else
//		return t;
//}

// 在 C++17 之前，我们必须使用 SFINAE 和 enable_if
//template<typename T>
//typename std::enable_if<std::is_pointer<T>::value,
//	std::remove_pointer_t<T>>::type
//	GetValue(T t)
//{
//	return *t;
//}
//
//template<typename T>
//typename std::enable_if<!std::is_pointer<T>::value, T>::type
//GetValue(T t)
//{
//	return t;
//}
//
//int main()
//{
//	int v = 10;
//	cout << GetValue(v) << endl;
//	cout << GetValue(&v) << endl;
//
//}

// constexpr lambda
//constexpr int Func(int x)
//{
//	auto f = [x]() {return x * x;};
//	return x + f();
//}
//
//int main()
//{
//	constexpr int v = Func(10);
//	static_assert(v == 110);
//
//	constexpr auto squared = [](int x) {return x * x;};
//	constexpr int s = squared(5);
//	static_assert(s == 25);
//	return 0;
//}

// *Lambda 表达式中的此捕获
//class SomeClass
//{
//public:
//	int m_x = 0;
//	void f() const
//	{
//		cout << m_x << endl;
//	}
//	void g()
//	{
//		m_x++;
//	}
//	// c++14
//	void Func()
//	{
//		auto lambda1 = [self = *this]() {self.f();};
//		auto lambda2 = [self = *this]() mutable {self.g();};
//		lambda1();
//		lambda2();
//	}
//
//	// C++17
//	void FuncNew()
//	{
//		auto lambda1 = [*this]() {f();};
//		auto lambda2 = [*this]()mutable {g();};
//		lambda1();
//		lambda2();
//	}
//};
//
//int main()
//{
//	SomeClass sc;
//	sc.Func();
//	sc.FuncNew();
//}

// 内联变量
// header.h
//#ifndef _HEADER_H
//#define _HEADER_H
//inline int MyVar = 42;
//#endif 

// source1.h
// #include "header.h"
//MyVar += 10;

// source2.h
// #include "header.h"
//Func(MyVar);

//在 C++17 之前, 程序员必须将 MyVar变量声明为 extern, 并在其中一个 .cpp 为其赋值。

// 结构化绑定

//struct S
//{
//	char x{ 'C' };
//	int y{ 42 };
//	double z{ 3.14 };
//};
//
//int main()
//{
	// C++17
	//set<int> mySet;
	//auto [iter, ok] = mySet.insert(42);

	//S s;
	//auto [a, b, c] = s;
	//cout << a << " " << b << " " << c << endl;	

	//int arr[] = { 1,2,3,4 };
	//auto [a, b, c, d] = arr;
	//cout << a << b << c << d << endl;

	//map<int, int> map;
	//map[1] = 1;
	//map[2] = 2;
	//map[3] = 3;
	//for (const auto& [key, val] : map)
	//{
	//	cout << "key: " << key << ' ';
	//	cout << "val: " << val << endl;
	//}

	// 带有初始化器的 if 和 switch 运算符
	//if(init; condition)
	//switch(init, condition)

	//std::map<int, string> map;
	//if (auto [it, ok] = map.insert({ 2, "hello" }); ok)
	//{

	//}

	// C++14
	//set<int> mySet;
	//set<int>::iterator iter;
	//bool ok;
	//std::tie(iter, ok) = mySet.insert(42);

}