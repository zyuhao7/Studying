#include <iostream>
#include <deque>
#include <list>
#include <iterator>
#include <numeric>
#include <vector>
#include <functional>

// day-2025-6-8
// Lambda 表达式
//[capture list](parameters)
//mutable			(optional)
//constexpr		    (optional)
//exception attr(optional)
//-> return type(optional)
//{
//    body
//}

//int main()
//{
//
//    auto just_one([]() { return 1; });
//    auto just_two([] { return 2; });
//    std::cout << just_one() << ", " << just_two() << '\n';
//
//
//
//    auto plus([](auto l, auto r) { return l + r; });
//
//    std::cout << plus(1, 2) << '\n';
//    std::cout << plus(std::string{ "a" }, "b") << '\n';
//    std::cout
//        << [](auto l, auto r) { return l + r; }(1, 2)
//        << '\n';
//
//
//    auto counter(
//        [count = 0]() mutable { return ++count; }
//    );
//
//    for (size_t i = 0; i < 5; ++i) {
//        std::cout << counter() << " ";
//    }
//    std::cout << '\n';
//
//    int a{ 0 };
//    auto incrementer([&a] { ++a; });
//
//    incrementer();
//    incrementer();
//    incrementer();
//
//    std::cout
//        << "Value of 'a' after 3 incrementer() calls: "
//        << a << '\n';
//
//    auto plus_ten([=](int x) { return plus(10, x); });
//    std::cout << plus_ten(5) << '\n';
//}
using namespace std;


// 使用Lambda为std::function添加多态性

//template<typename C>
//static auto consumer(C& container)
//{
//	return [&](auto value)
//		{
//			container.push_back(value);
//		};
//}
//
//template<typename C>
//static void print(const C& c)
//{
//	for (auto i : c)
//	{
//		cout << i << " ";
//	}
//	cout << endl;
//}
//
//
//int main()
//{
//	std::deque<int> deq;
//	std::list<int> lst;
//	std::vector<int> vec;
//
//	const vector<function<void(int)>> consumers{ consumer(deq), consumer(lst), consumer(vec) };
//	for (int i = 0; i < 10; ++i)
//	{
//		for (auto& consume : consumers)
//		{
//			consume(i);
//		}
//	}
//	print(deq);
//	print(lst);
//	print(vec);
//
//}

// 并置函数
//template<typename T, typename ...Ts>
//auto concat(T t, Ts ...ts)
//{
//	if constexpr (sizeof...(ts) > 0)
//	{
//		return [=](auto ... params)
//			{
//				return t(concat(ts...)(params...));
//			};
//	}
//	else
//		return t;
//}
//
//int main()
//{
//	auto twice([](int i) {return i * 2;});
//	auto thrice([](int i) {return i * 3;});
//
//	auto combined(
//		concat(twice, thrice, std::plus<int>{})
//	);
//
//	cout << combined(2, 3) << endl;
//
//}

// 使用同一输入调用多个函数
//template<typename ... Ts>
//static auto multicall(Ts ... functions)
//{
//	return [=](auto x) {
//		(void)std::initializer_list<int>{
//			((void)functions(x), 0)...
//		};
//	};
//}
//
//template<typename F, typename ...Ts>
//static auto for_each(F f, Ts ...xs)
//{
//	(void)std::initializer_list<int>{
//		((void)f(xs), 0)...
//	};
//}
//
//static auto brace_print(char a, char b)
//{
//	return [=](auto x)
//		{
//			cout << a << x << b<<" ";
//		};
//}
//
//int main()
//{
//	auto f(brace_print('(', ')'));
//	auto g(brace_print('[', ']'));
//	auto h(brace_print('{', '}'));
//	auto nl([](auto) {cout << endl;});
//
//	auto call_fgh(multicall(f, g, h, nl));
//	for_each(call_fgh, 1, 2, 3, 4, 5);
//}

// 使用std::accumulate和Lambda函数实现transform_if
//template<typename T>
//auto map(T fn)
//{
//	return [=](auto reduce_fn)
//		{
//			return [=](auto accum, auto input)
//				{
//					return reduce_fn(accum, fn(input));
//				};
//		};
//}
//
//template<typename T>
//auto filter(T predicate)
//{
//	return [=](auto reduce_fn)
//		{
//			return [=](auto accum, auto input)
//				{
//					if (predicate(input))
//					{
//						return reduce_fn(accum, input);
//					}
//					else
//						return accum;
//				};
//		};
//}
//
//int main()
//{
//	std::istream_iterator<int> it{ std::cin };
//	std::istream_iterator<int> end_it;
//
//	auto even([](int i) {return i % 2 == 0;});
//	auto twice([](int i) {return i * 2;});
//
//	auto copy_and_advance([](auto it, auto input)
//	{
//		*it = input;
//		return ++it;
//	});
//
//	std::accumulate(it, end_it,
//		std::ostream_iterator<int>{ std::cout," " },
//		filter(even)(
//			map(twice)(
//				copy_and_advance
//				)
//			));
//	cout << endl;
//
//}