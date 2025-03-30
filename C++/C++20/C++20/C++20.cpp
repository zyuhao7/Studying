#include <iostream>
#include <compare>
#include <vector>
#include <algorithm>
#include <map>
#include <concepts>
#include <string>

using namespace std;
//三路比较运算符 <=> and operator==() = default

/*
   当定义 <=> 时，编译器会自动生成以下运算符（除非显式定义）：
            ==, !=
           <, <=, >, >=
*/

//struct Point
//{
//    int x, y;
//
//    // 自动生成 ==, <, >, <=, >=, !=
//    auto operator<=>(const Point&) const = default;
//};
//
//int main()
//{
//    Point p1{ 1, 2 }, p2{ 1, 3 };
//
//    if (p1 < p2)
//        std::cout << "p1 小于 p2\n";
//    if (p1 == p2)
//        std::cout << "p1 等于 p2\n";
//
//    return 0;
//}


//struct Employee {
//    int id;
//    std::string name;
//    double salary;
//
//    auto operator<=>(const Employee&) const = default;
//
//    // 也可以单独定义比较方式
//    std::strong_ordering operator<=>(int other_id) const {
//        return id <=> other_id;
//    }
//};
//
//int main() {
//    std::vector<Employee> staff{
//        {103, "Alice", 75000.0},
//        {101, "Bob", 65000.0},
//        {102, "Charlie", 82000.0}
//    };
//
//    // 使用自动生成的 < 运算符排序
//    std::sort(staff.begin(), staff.end());
//
//    // 使用自定义的比较
//    Employee e{ 101, "Bob", 65000.0 };
//    if (e == 101) {
//        std::cout << "Found employee with ID 101\n";
//    }
//
//    return 0;
//}

// 范围 for 中的初始化语句和初始化器
//std::vector<int> get_data() {
//    return { 1, 2, 3, 4, 5 };
//}
//
//int main()
//{
//	std::vector<int> v{ 1, 2, 3, 4, 5 };
//    for (int i = 0; auto & e : v)
//    {
//        e += i++;
//    }
//	for (auto& e : v)
//	{
//		cout << e << " ";
//	}
//    cout << endl;
//    for (auto vec = get_data(); auto & e : vec)
//    {
//        cout << e << " ";
//    }
//    cout << endl;
//
//    for (int i = 0; auto & x : {"a", "b", "c"})
//    {
//        cout << i++ << ": " << x << endl;
//    }
//
//	map<int, string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
//    for (auto &[k, v] : m)
//    {
//		cout << k << ": " << v << endl;
//    }
//
//	for (auto vec = std::vector<int>{ 1,2 ,3 }; auto & e : vec)
//	{
//		cout << e << " ";
//	}
//    return 0;
//}

// 约束与概念
/*
     1. 概念(Concepts)
    定义：概念是对模板参数的一组要求/约束

    作用：指定模板参数必须满足的属性

    常用标准概念
    std::integral<T>      // T是整型
    std::floating_point<T> // T是浮点型
    std::derived_from<T, U> // T派生自U
    std::convertible_to<T, U> // T可转换为U
    std::invocable<F, Args...> // F可使用Args调用

    语法：template<typename T> concept Name = constraint;

    2. 约束(Constraints)
    定义：对模板参数的具体限制条件

    形式：可以是逻辑组合的多个要求
*/


// 定义自定义概念
//template<typename T>
//concept Addable = requires(T a, T b) {
//    { a + b } -> std::same_as<T>; // 要求a+b返回T类型
//};
//
//template<typename T>
//concept Printable = requires(std::ostream & os, T t) {
//    { os << t } -> std::same_as<std::ostream&>; // 要求支持<<操作
//};
//
////// a) 简写函数模板
////void print(const Printable auto& value) {
////    std::cout << value << '\n';
////}
////// b) 传统模板语法
////template<Printable T>
////void print(const T& value) {
////    std::cout << value << '\n';
////}
//
//template<typename T>
//    requires Addable<T>&& Printable<T>
//auto add_and_print(T a, T b) {
//    auto sum = a + b;
//    std::cout << sum << '\n';
//    return sum;
//}
//
//// 组合概念
//template<typename T>
//concept Numeric = std::integral<T> || std::floating_point<T>;
//
//template<typename T>
//concept AddableAndPrintable = Addable<T> && Printable<T>;
//
//
//// requires 表达式用于定义更复杂的要求
//template<typename T>
//concept Container = requires(T c) {
//    c.begin();      // 必须有begin()方法
//    c.end();        // 必须有end()方法
//    c.clear();
//    typename T::iterator;
//	{ c.size() } -> std::same_as<size_t>; // size()返回size_t类型
//	{ c.push_back(std::declval<typename T::value_type>()) }; // push_back()方法
//    typename T::value_type; // 必须有value_type成员类型
//};


//int main()
//{
//	//print(42);
//	//print(3.14);
//	//print("Hello, World!");
//	add_and_print(1, 2);
//	add_and_print(3.14, 2.71);
//
//
//	return 0;
//}
// 
// 排序算法约束
//template<typename Iter>
//concept RadomAccessIterator = requires(Iter it)
//{
//	requires std::random_access_iterator<Iter>;
//{ it[0] }-> std::same_as<typename std::iterator_traits<Iter>::reference>;
//};
//
//template<RadomAccessIterator Iter>
//void my_sort(Iter begin, Iter end)
//{
//    std::sort(begin, end);
//}
//
//int main()
//{
//	std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6 };
//	my_sort(v.begin(), v.end());
//	for (auto i : v)
//	{
//		cout << i << " ";
//	}
//	cout << endl;
//	return 0;
//}