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
// �۵����ʽ
//template<typename... Args>
//constexpr int Sum(Args... args)
//{
//	return (args + ...);
//}
//
//// ��ָ��һ����ʼֵ.
//template<typename... Args>
//auto Func(Args... args)
//{
//	return (args + ... + 100);
//}
//
//// �� C++17 ֮ǰ��Ҫʵ�����Ƶĺ�������������ʽָ���ݹ����
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

//	ģ��<auto>

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

// ��ģ������Ƶ�
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
//	// �� C++17 ֮ǰ��ģ������Ƶ��������ں�������ˣ��ڹ���ģ����ʱ��ʼ����Ҫ��ʽָ��ģ�����: C++14
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

// constexpr ���ʽ
// C++17 ʹ�����ܹ�ִ�б���ʱ������֧������һ���ǳ�ǿ��Ĺ��ߣ���Ԫ������ر����á�
//template<typename T>
//auto GetValue(T t)
//{
//	if constexpr (std::is_pointer<T>::value)
//		return *t;
//	else
//		return t;
//}

// �� C++17 ֮ǰ�����Ǳ���ʹ�� SFINAE �� enable_if
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

// *Lambda ���ʽ�еĴ˲���
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

// ��������
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

//�� C++17 ֮ǰ, ����Ա���뽫 MyVar��������Ϊ extern, ��������һ�� .cpp Ϊ�丳ֵ��

// �ṹ����

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

	// ���г�ʼ������ if �� switch �����
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