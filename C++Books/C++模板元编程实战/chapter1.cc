#include <iostream>
#include <string>
#include <type_traits>
using namespace std;
// day-2025-6-10
// 第一章-基本技巧
//static int call_count = 3;
//constexpr int fun2(int a)
//{
//	return a + (call_count++);
//}
//int main()
//{
//	cout<< fun2(2);
//
//	return 0;
//}

//template<typename T>
//struct Fun_ { using type = T; };
//
//template<>
//struct Fun_<int> { using type = unsigned int; };
//
//template<>
//struct Fun_<long> { using type = unsigned long; };
//
//Fun_<int>::type h = 3;


//std::remove_reference<int&>::type h1 = 3;
//std::remove_reference_t<int&> h2 = 3;
//
//template<int a, int b>
//struct Add_
//{
//	constexpr static int val = a + b;
//};
//
//template<int a, int b>
//constexpr int Add = a + b;
//
//constexpr int x1 = Add_<2, 3>::val;
//constexpr int x2 = Add<2, 3>;

// 模板作为元函数的输入
//template<template<typename> class T1, typename T2>
//struct Fun_ {
//	using type = typename T1<T2>::type;
//};
//
//template<template<typename> class T1, typename T2>
//using Fun = typename Fun_<T1, T2>::type;
//
//Fun<std::remove_reference, int&> h = 3;

// 模板作为元函数的输出 todo.
//template<bool AddOrRemoveRef> struct Fun_;
//
//template<>
//struct Fun_<true> {
//	template<typename T>
//	using type = std::add_lvalue_reference<T>;
//};
//
//template<>
//struct Fun_<false> {
//	template<typename T>
//	using type = std::remove_reference<T>;
//};
//
//template<typename T>
//template<bool AddOrRemove>
//using Fun = typename Fun_<AddOrRemove>::template type<T>;
//
//template<typename T>
//using Res_ = Fun<false>;
//
//Res_<int&>::type h = 3;

//template<typename T>
//struct RemoveReferenceConst_ {
//private:
//	using inter_type = typename std::remove_reference<T>::type;
//
//public:
//	using type = typename std::remove_const<inter_type>::type;
//};
//
//template<typename T>
//using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;
//
//RemoveReferenceConst<const int&> h = 3;

//namespace std
//{
//	template<bool B, typename T, typename F>
//	struct conditional {
//		using type = T;
//	};
//
//	template<typename T, typename F>
//	struct conditional<false, T, F>
//	{
//		using type = F;
//	};
//
//	template<bool B, typename T, typename F>
//	using conditional_t = typename conditional<B, T, F>::type;
//}


//int main()
//{
//	std::conditional<true, int, float>::type x = 3;
//	std::conditional_t<true, int, float> y = 3.14f;
//	cout << x << " " << y << endl;
//}

//struct A; 
//struct B;
//
//template<typename T>
//struct Fun_ {
//	constexpr static size_t value = 0;
//};
//
//template<>
//struct Fun_<A> {
//	constexpr static size_t value = 1;
//};
//
//template<>
//struct Fun_<B> {
//	constexpr static size_t value = 2;
//};
//
//constexpr size_t h = Fun_<B>::value;

// err Wrapper是一个未完全特化的类模板,其内包含了一个模板的完全特化 Fun_<int>,但我运行成功了!
//template<typename TW>
//struct Wrapper {
//	template<typename T>
//	struct Fun_ {
//		constexpr static size_t value = 0;
//	};
//	template<>
//	struct Fun_<int> {
//		constexpr static size_t value = 1;
//	};
//};

//template<typename TW>
//struct Wrapper {
//	template<typename T, typename TDummy = void>
//	struct Fun_ {
//		constexpr static size_t value = 0;
//	};
//	template<typename TDummy> // 将完全特化修改为局部特化
//	struct Fun_<int, TDummy> {
//		constexpr static size_t value = 1;
//	};
//};


// 使用 std::enable_if 和 std::enable_if_t 实现分支
//namespace std
//{
//	template<bool B, typename T = void>
//	struct enable_if{};
//
//	template<typename T>
//	struct enable_if<true, T> { using type = T; };
//
//	template<bool B, typename T = void>
//	using enable_if_t = typename enable_if<B, T>::type;
//}

//template<bool IsFeedbackOut, typename T,
//		std::enable_if_t<IsFeedbackOut>* = nullptr>
//auto FeedbackOut_(T &&){/**/ }
//
//template<bool IsFeedbackOut, typename T,
//	std::enable_if_t<!IsFeedbackOut>* = nullptr>
//auto FeedbackOut_(T&&) {/**/ }


//template<bool Check, std::enable_if_t<Check>* = nullptr>
//auto func() {
//	return (int)0;
//}
//
//template<bool Check, std::enable_if_t<!Check>* = nullptr>
//auto func() {
//	return (double)1.1;
//}
//
//template<bool Check>
//auto wrap2()
//{
//	return func<Check>();
//}
//
//
//int main()
//{
//	cerr << wrap2<true>() << endl;
//}

// 使用 if constexpr 简化代码
//template<bool Check>
//auto fun()
//{
//	if constexpr (Check)
//	{
//		return (int)0;
//	}
//	else
//	{
//		return (double)3.14;
//	}
//}
//int main()
//{
//	cerr << fun<true>() << endl;
//}

//template<size_t Input>
//constexpr size_t OnesCount = (Input % 2) + OnesCount<(Input / 2)>;
//
//template<>
//constexpr size_t OnesCount<0> = 0;

//template<size_t ... Inputs>
//constexpr size_t Accumulate = 0;
//
//template<size_t CurInput, size_t... Inputs>
//constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;
//
//constexpr size_t res = Accumulate<1, 2, 3, 4, 5>;

// C++17
//template<size_t ...values>
//constexpr size_t fun()
//{
//	return (0 + ... + values);
//}
//
//constexpr size_t res = fun<1, 2, 3, 4, 5>();

// CRTP
//template<typename D>
//struct Base
//{
//	static void Fun()
//	{
//		D::imp();
//	}
//};
//
//struct Derive : public Base<Derive>
//{
//	static void imp()
//	{
//		cout << "Implementation from deriv class" << endl;
//	}
//};

//int main()
//{
	//Derive::Fun();
	//cout << res << endl;
	//cout << OnesCount<63>;
//}

