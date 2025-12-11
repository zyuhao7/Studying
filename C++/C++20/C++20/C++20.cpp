#include <iostream>
#include <vector>
#include <queue>
#include <cctype>
#include <cmath>
#include <string>
#include <cstdint>
#include <chrono>
#include <map>
#include <list>
#include <unordered_map>
#include <string.h>
#include <algorithm>
#include <stack>
#include <type_traits>
#include <initializer_list>
using namespace std;

// day-2025-12-11
// 强类型枚举
//template<typename T>
//std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
//{
//    return stream << static_cast<typename std::underlying_type<T>::type>(e);
//}
//
//enum Left
//{
//    val1 = 1,
//    val2 = 2
//};
//
//enum Right
//{
//    val3 = 1,
//    val4 = 2
//};
//
//enum class new_enum : unsigned int
//{
//    value1,
//    value2,
//    value3 = 100,
//    value4 = 100
//};

//int main()
//{
//    if (Left::val1 == Right::val3)
//        cout << "Left::val1 == Right::val3" << endl;

    // compile err
    //if (new_enum::value3 == 100)
    //{
    //    cout << "true" << endl;
    //}

//    if (new_enum::value3 == new_enum::value4)
//        std::cout << "new_enum::value3 == new_enum::value4" << endl;
//    cout << new_enum::value2 << endl;
//}

// 委托构造
//class Base
//{
//public:
//    std::string str;
//    int val;;
//    Base() = delete;
//    Base(std::string s)
//    {
//        str = s;
//    }
//    Base(std::string s, int v)
//        :Base(s)
//    {
//        val = v;
//    }
//    virtual void foo() final
//    {
//        return;
//    }
//
//    virtual void foo(int v)
//    {
//        val = v;
//    }
//};
//
//class Subclass final : public Base
//{
//public:
//    double floating;
//    Subclass() = delete;
//
//    Subclass(double f, int v, std::string s) : Base(s, v)
//    {
//        floating = f;
//    }
//
//    virtual void foo(int v) override
//    {
//        std::cout << v << endl;
//        val = v;
//    }
//};
//
//int main()
//{
//    Subclass s(1.2, 3, "abc");
//    s.foo(1);
//}

// 非类型模板
//template <auto value> void foo() {
//    std::cout << value << std::endl;
//    return;
//}
//
//int main() {
//    foo<10>(); // value is deduced as type int
//}

// 可变模板参数
// szieof...
//template<typename... Ts>
//void magic(Ts... args)
//{
//    cout << sizeof...(args) << endl;
//}
//
//template<typename T0>
//void printf1(T0 value)
//{
//    cout << value << endl;
//}
//
//template<typename T, typename... Ts>
//void printf1(T value, Ts... args)
//{
//    std::cout << value << std::endl;
//    printf1(args...);
//}
//
//template<typename T0, typename... T>
//void printf2(T0 t0, T... t)
//{
//    cout << t0 << endl;
//    if constexpr (sizeof...(t) > 0) printf2(t...);
//}
//
//template<typename T, typename... Ts>
//auto printf3(T value, Ts... args)
//{
//    cout << value << endl;
//    (void)std::initializer_list<T>{([&args] {
//        std::cout << args << endl;
//        }(), value)...};
//}
//
//int main()
//{
//    magic();
//    magic(1);
//    magic(1, "");
//
//    printf1(1, 2, "123", 1.1);
//    printf2(1, 2.3, "abc");
//    printf3(111, 123, "alpha", 1.2);
//}

//template<typename T = int, typename U = int>
//auto add(T x, U y) -> decltype(x + y) {
//    return x + y;
//}
//
//int main() {
//    std::cout << add(1, 2) << std::endl;
//}


// alias template
//template<typename T, typename U>
//class MagicType
//{
//public:
//    T dark;
//    U magic;
//};

// 不合法, typedef 不支持模板别名.
//template<typename T>
//typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;

//typedef int(*process)(void*);
//using NewProcess = int(*)(void*);
//template<typename T>
//using TrueDarkMagic = MagicType<vector<T>, std::string>;
//
//int main()
//{
//    TrueDarkMagic<bool> you;
//}


// external template
//template class std::vector<bool>;
//extern template class std::vector<double>;
//
//template<bool T>
//class MagicType
//{
//    bool magic = T;
//};
//
//int main()
//{
//    std::vector<vector<int>> matrix;
//    std::vector<MagicType<(1 > 2)>> magic;
//}


//template<int i>
//struct Int{};
//
//constexpr auto iter(Int<0>) -> Int<0>;
//
//template<int i>
//constexpr auto iter(Int<i>) {
//    return iter(Int<i - 1>{});
//}
//
//int main()
//{
//    decltype(iter(Int<10>{})) a;
//}


//tail return type 
// before c++11
//template< typename R, typename T, typename U>
//R add(T x, U y)
//{
//    return x + y;
//}
//
//// after 11
//template<typename T, typename U>
//auto add2(T x, U y) -> decltype(x + y)
//{
//    return x + y;
//}
//
//// after C++14
//
//template<typename T, typename U>
//auto add3(T x, U y)
//{
//    return x + y;
//}
//
//int main()
//{
//    int z = add<int, int, int>(1, 2);
//    cout << z << endl;
//
//    auto w = add2<int, double>(1, 2.0);
//    if (is_same<decltype(w), double>::value)
//    {
//        cout << "w is double: " << w << endl;
//    }
//    else
//        cout << "w is int: " << w << endl;
//
//    auto q = add3<double, int>(1.0, 2);
//    cout << "q: " << q << endl;
//}

// initializer_list
//class Foo 
//{
//public:
//    int m_a;
//    int m_b;
//    Foo(int a, int b)
//        :m_a(a),
//        m_b(b)
//    {
//    }
//};
//
//class MagicFoo
//{
//public:
//    std::vector<int> vec;
//    MagicFoo(std::initializer_list<int> list)
//    {
//        for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
//        {
//            vec.push_back(*it);
//        }
//    }
//    void foo(std::initializer_list<int> list)
//    {
//        for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
//        {
//            vec.push_back(*it);
//        }
//    }
//};
//
//int main()
//{
//    int arr[3] = { 1,2,3 };
//    Foo foo(1, 2);
//    std::vector<int> vec = { 1,2,3,4,5 };
//
//    MagicFoo magicFoo = { 1,2,3,4,5 };
//    magicFoo.foo({ 6,7,8,9 });
//    Foo foo2{ 3,4 };
//
//    std::cout << "arr[0]: " << arr[0] << endl;
//    std::cout << "foo: " << foo.m_a << ", " << foo.m_b << endl;
//    std::cout << "vec: ";
//    for (auto it = vec.begin(); it != vec.end(); ++it) cout << *it << " ";
//    cout << endl;
//
//    std::cout << "magicFoo: ";
//    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); it++)
//        cout << *it << " ";
//    cout << endl;
//
//    cout << "foo2: " << foo2.m_a << ", " << foo2.m_b << endl;
//}

// nullptr
//void foo(char*);
//void foo(int);
//
//int main()
//{
//    if (std::is_same<decltype(NULL), decltype(0)>::value)
//    {
//        cout << "NULL == 0" << endl;
//    }
//    if (is_same<decltype(NULL), decltype((void*)0)>::value)
//    {
//        cout << "NULL == (void*)0" << endl;
//    }
//    if (is_same<decltype(NULL), std::nullptr_t>::value)
//    {
//        cout << "NULL ==  nullptr" << endl;
//    }
//    foo(0);
//    foo(NULL);
//    foo(nullptr);
//}
//
//void foo(char*)
//{
//    std::cout << "void foo(char*)" << endl;
//}
//void foo(int i)
//{
//    std::cout << "void foo(int i)" << endl;
//}



//template <typename T>
//int compare(const T& v1, const T& v2)
//{
//    cout << "use compare T&" << endl;
//    if (v1 < v2)
//        return -1;
//    if (v2 < v1)
//        return 1;
//    return 0;
//}
//
////带字面常量的比较函数
//template <size_t N, size_t M>
//int compare(const char(&a1)[N], const char(&a2)[M])
//{
//    cout << "use const char (&)[N]" << endl;
//    return strcmp(a1, a2);
//}
//
//
//void testcompare()
//{
//    const char* p1 = "h1";
//    const char* p2 = "mom";
//    //调用特例化版本
//    compare(p1, p2);
//    //调用第二个版本
//    compare("hi", "mom");
//}
//
//int main()
//{
//    testcompare();
//}


//template<typename T>
//void print(T val) {
//    if constexpr (std::is_integral<T>::value)
//        std::cout << "int\n";
//    else
//        std::cout << "not int\n";
//}

//template<typename T>
//typename std::enable_if<std::is_integral<T>::value>::type
//print(T) {
//    std::cout << "Integral\n";
//}
//
//template<typename T>
//typename std::enable_if<std::is_floating_point<T>::value>::type
//print(T) {
//    std::cout << "Floating Point\n";
//}

//template<typename T>
//struct IsPointer {
//    static constexpr bool value = false;
//};
//
//template<typename T>
//struct IsPointer<T*> {
//    static constexpr bool value = true;
//};

//template<int N>
//struct Factorial {
//    static constexpr int value = N * Factorial<N - 1>::value;
//};
//
//template<>
//struct Factorial<0> {
//    static constexpr int value = 1;
//};


//uint64_t reverse_bits_simple(uint64_t x)
//{
//    uint64_t res = 0;
//    for (int i = 0; i < 64; ++i)
//    {
//        res <<= 1;
//        res |= (x & 1);
//        x >>= 1;
//    }
//    return res;
//}
//
//int main() {
//    const int N = 10'000'000;
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (uint64_t i = 0; i < N; ++i) {
//        reverse_bits_simple(i);
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    std::cout << "Time: " << elapsed << " ms\n";
//    return 0;
//}

//double strtod(const char* str)
//{
//    if (str == nullptr) return 0.0;
//    //跳过空格
//    while (isspace(*str)) str++;
//
//	//处理正负号
//    bool flag = true;
//    if(*str == '-')
//    {
//        flag = false;
//        str++;
//    }
//    else if (*str == '+')
//    {
//        str++;
//    }
//
//	//处理整数部分
//    double res = 0.0;
//    while (isdigit(*str))
//    {
//        res = res * 10 + (*str - '0');
//        str++;
//    }
//
//	//处理小数部分
//    if (*str == '.')
//    {
//        ++str;
//        double decimal = 1.0;
//        while (isdigit(*str))
//        {
//            decimal /= 10;
//            res += (*str - '0') * decimal;
//			++str;
//        }
//    }
//    //处理指数部分
//    if (*str == 'e' || *str == 'E')
//    {
//        ++str;
//        bool exp_flag = true;
//        if (*str == '-')
//        {
//            exp_flag = false;
//            ++str;
//        }
//        else if (*str == '+')
//        {
//            ++str;
//        }
//        int exp = 0;
//        while (isdigit(*str))
//        {
//            exp = exp * 10 + (*str - '0');
//            ++str;
//        }
//        if (exp_flag)
//            res *= pow(10, exp);
//        else
//			res /= pow(10, exp);
//    }
//	return flag ? res : -res;
//}
//int main() {
//    const char* inputs[] = {
//        "123.456",
//        "  -0.00123",
//        "1.23e3",
//        "-5.67E-2",
//        "invalid123",
//        "   +42"
//    };
//
//    for (const auto& s : inputs) {
//        std::cout << "Input: \"" << s << "\" -> " << strtod(s) << '\n';
//    }
//
//    return 0;
//}


//const int N = 200005;
//int a[N];
//
//int main() {
//    int n, k;
//    cin >> n >> k;
//
//    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
//        return a.first < b.first; // 大根堆，快乐值高优先
//        };
//    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
//
//    long long ans = 0;
//    int day = k + 1; // 第 k+1 天开始接待
//    vector<int> res(n + 1); // 保存每个人的接待天数（如果要输出）
//
//    for (int i = 1; i <= n; ++i) {
//        cin >> a[i];
//        pq.push({ a[i], i });
//
//        if (i >= k + 1) {
//            auto t = pq.top(); pq.pop();
//            ans += 1LL * t.first * (day - t.second);
//            res[t.second] = day;
//            day++;
//        }
//    }
//
//    while (!pq.empty()) {
//        auto t = pq.top(); pq.pop();
//        ans += 1LL * t.first * (day - t.second);
//        res[t.second] = day;
//        day++;
//    }
//
//    cout << ans << endl;
//    return 0;
//}



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