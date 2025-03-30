#include <iostream>
#include <compare>
#include <vector>
#include <algorithm>
#include <map>
#include <concepts>
#include <string>

using namespace std;
//��·�Ƚ������ <=> and operator==() = default

/*
   ������ <=> ʱ�����������Զ����������������������ʽ���壩��
            ==, !=
           <, <=, >, >=
*/

//struct Point
//{
//    int x, y;
//
//    // �Զ����� ==, <, >, <=, >=, !=
//    auto operator<=>(const Point&) const = default;
//};
//
//int main()
//{
//    Point p1{ 1, 2 }, p2{ 1, 3 };
//
//    if (p1 < p2)
//        std::cout << "p1 С�� p2\n";
//    if (p1 == p2)
//        std::cout << "p1 ���� p2\n";
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
//    // Ҳ���Ե�������ȽϷ�ʽ
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
//    // ʹ���Զ����ɵ� < ���������
//    std::sort(staff.begin(), staff.end());
//
//    // ʹ���Զ���ıȽ�
//    Employee e{ 101, "Bob", 65000.0 };
//    if (e == 101) {
//        std::cout << "Found employee with ID 101\n";
//    }
//
//    return 0;
//}

// ��Χ for �еĳ�ʼ�����ͳ�ʼ����
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

// Լ�������
/*
     1. ����(Concepts)
    ���壺�����Ƕ�ģ�������һ��Ҫ��/Լ��

    ���ã�ָ��ģ������������������

    ���ñ�׼����
    std::integral<T>      // T������
    std::floating_point<T> // T�Ǹ�����
    std::derived_from<T, U> // T������U
    std::convertible_to<T, U> // T��ת��ΪU
    std::invocable<F, Args...> // F��ʹ��Args����

    �﷨��template<typename T> concept Name = constraint;

    2. Լ��(Constraints)
    ���壺��ģ������ľ�����������

    ��ʽ���������߼���ϵĶ��Ҫ��
*/


// �����Զ������
//template<typename T>
//concept Addable = requires(T a, T b) {
//    { a + b } -> std::same_as<T>; // Ҫ��a+b����T����
//};
//
//template<typename T>
//concept Printable = requires(std::ostream & os, T t) {
//    { os << t } -> std::same_as<std::ostream&>; // Ҫ��֧��<<����
//};
//
////// a) ��д����ģ��
////void print(const Printable auto& value) {
////    std::cout << value << '\n';
////}
////// b) ��ͳģ���﷨
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
//// ��ϸ���
//template<typename T>
//concept Numeric = std::integral<T> || std::floating_point<T>;
//
//template<typename T>
//concept AddableAndPrintable = Addable<T> && Printable<T>;
//
//
//// requires ���ʽ���ڶ�������ӵ�Ҫ��
//template<typename T>
//concept Container = requires(T c) {
//    c.begin();      // ������begin()����
//    c.end();        // ������end()����
//    c.clear();
//    typename T::iterator;
//	{ c.size() } -> std::same_as<size_t>; // size()����size_t����
//	{ c.push_back(std::declval<typename T::value_type>()) }; // push_back()����
//    typename T::value_type; // ������value_type��Ա����
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
// �����㷨Լ��
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