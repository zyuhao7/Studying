#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <functional>
using namespace std;

// day-2025-3-29

// 1. auto 与 decltype
// auto add = [](int a, int b)
// { return a + b; };

// decltype(auto) sub = [](int a, int b)
// {
//     return a - b;
// };

// int main()
// {
//     vector<int> v{1, 2, 3, 4, 5};
//     vector<int>::iterator it = v.begin();
//     auto it1 = v.begin();

//     int x = 10;
//     const auto y = 20;
//     auto &z = x;
//     // y = 30; err assignment of read-only variable 'y'
//     int sum = add(x, y);
//     cout << sum << endl;

//     // decltype(expr) 获取表达式 expr 的 精确类型，但 不对其求值
//     decltype(x) t = 20;
//     decltype(it) it2 = v.begin();
//     decltype(add(1, 2)) a = 100;

//     int &ref = x;
//     // 避免 auto 丢失 const 或 &，更精准推导类型
//     decltype(auto) ref1 = ref;
//     ref1 = 20;
//     cout << ref << endl;

//     decltype(ref) d = x; // y 也是 int&
//     return 0;
// }

// 预置与弃置的函数
/*
1.1 =default 作用
显式指定 默认构造、析构、拷贝/移动构造等函数由编译器自动生成（默认行为）。

用于 恢复 被用户声明但未定义的函数。
*/
// class MyClass
// {
// public:
//     MyClass() = default;  // 让编译器生成默认构造函数 = MyClass() {}
//     ~MyClass() = default; // 让编译器生成默认析构函数 = ~MyClass() {}
//     MyClass(const MyClass &) = default;
//     MyClass(MyClass &&) = default;
//     MyClass &operator=(const MyClass &) = default;
//     MyClass &operator=(MyClass &&) = default;
// };

/*
2. 弃置函数（= delete）
2.1 =delete 作用
禁止编译器自动生成特定的 构造/拷贝/赋值运算。

让某些 函数无法被调用，以 防止不合理的使用。
*/
// class NoCopyable
// {
// public:
//     NoCopyable() = default;                             // 默认构造函数
//     NoCopyable(const NoCopyable &) = delete;            // 禁止拷贝构造函数
//     NoCopyable &operator=(const NoCopyable &) = delete; // 禁止拷贝赋值运算符
// };

// final 与 override
/*
1. final 关键字
作用
用于 禁止类被继承 或 禁止虚函数被重写。

防止错误的继承和重写，提高代码的稳定性。
*/

// 1.1 final 用于类，防止被继承
// class Base final
// {
// public:
//     void show()
//     {
//         cout << "Base class" << endl;
//     }
// };
// error: cannot derive from 'final' base 'Base' in derived type 'Derived'
// class Derived : public Base
// {
// };

// 1.2 final 用于虚函数，防止被重写，避免误修改基类逻辑
// class Parent
// {
// public:
//     virtual void func() final // ❌ 这个函数不能被重写
//     {
//         std::cout << "Parent func()" << std::endl;
//     }
// };

// class Child : public Parent
// {
// public:
//     // void func() override // ❌ 编译错误！不能重写 final 函数
//     // {
//     //     std::cout << "Child func()" << std::endl;
//     // }
// };
/*
2. override 关键字
作用
强制 指定某个函数是 重写基类的虚函数，防止拼写错误或意外行为。

让代码更加安全、可读性更强。
*/

// class Base
// {
// public:
//     virtual void show()
//     { // 父类的虚函数
//         std::cout << "Base show()" << std::endl;
//     }
// };

// class Derived : public Base
// {
// public:
//     void show() override
//     { // 明确表示重写
//         std::cout << "Derived show()" << std::endl;
//     }
// };

// 尾随返回类型
// auto 函数名(参数列表) -> 返回类型;

//  ✅ 先解析参数类型，再决定返回类型
// template <typename T1, typename T2>
// auto add(T1 a, T2 b) -> decltype(a + b)
// {
//     return a + b;
// }

//  decltype(auto) 直接推导返回类型，可以替代 C++11 的尾随返回类型。
// template <typename T1, typename T2>
// decltype(auto) add1(T1 a, T2 b)
// {
//     return a + b;
// }

// std::function<int(int, int)> add2 = [](int a, int b) -> int
// {
//     return a + b;
// };

// 右值引用
/*
    2.1 移动语义（Move Semantics）
    移动语义避免了 不必要的拷贝，提升性能。例如：
*/
// class MyString
// {
// private:
//     char *data;

// public:
//     // 构造函数
//     MyString(const char *str)
//     {
//         data = new char[strlen(str) + 1];
//         strcpy(data, str);
//         std::cout << "构造" << std::endl;
//     }

//     // 拷贝构造函数（左值引用，深拷贝）
//     MyString(const MyString &other)
//     {
//         std::cout << "拷贝构造" << std::endl;
//         data = new char[strlen(other.data) + 1]; // 分配内存
//         strcpy(data, other.data);                // 深拷贝
//     }

//     // 移动构造函数（右值引用，浅拷贝）
//     MyString(MyString &&other) noexcept
//     {
//         data = other.data;    // 直接移动指针
//         other.data = nullptr; // 清空原对象，防止释放
//         std::cout << "移动构造" << std::endl;
//     }

//     ~MyString()
//     {
//         delete[] data;
//     }
// };

// int main()
// {
//     MyString a("Hello");
//     MyString b = std::move(a); // 触发移动构造
// }

/*
    2.2 右值引用用于函数参数
    右值引用可以用于 高效传递临时对象：
*/

// 右值引用，避免拷贝
// void process(std::string &&str)
// {
//     /// 类似于:
//     // std::string temp("Hello");  // 隐式构造一个临时 `std::string`
//     // process(std::move(temp));   // 右值引用绑定，无拷贝

//     std::cout << "Before: " << str << ", Capacity: " << str.capacity() << std::endl;

//     str += " Processed"; // 追加数据，可能扩容

//     std::cout << "After: " << str << ", Capacity: " << str.capacity() << std::endl;
//     std::cout << "Processing: " << str << std::endl;
// }

// int main()
// {
//     process("Temporary String"); // ✅ 右值传递，避免不必要的拷贝
// }

// std::move 的底层原理
// template <typename T>
// typename remove_reference<T>::type &&move(T &&arg) noexcept
// {
//     return static_cast<typename remove_reference<T>::type &&>(arg);
// }
/*
    std::move(x) 本质上 将 x 转换为右值。
    不会真正移动数据，只是 让编译器认为 x 是右值，从而调用移动构造函数.
*/

// // std::forward 的底层原理
// template <typename T>
// template<typename _Tp>
// constexpr _Tp&&  forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
// {
//   return static_cast<_Tp&&>(__t);
// }

// template <typename T>
// void wrapper(T &&arg)
// {
//     process(std::forward<T>(arg));
// }

// 有作用域枚举
/*
    作用域枚举（Scoped Enumeration）是 C++11 引入的一种枚举类型，使用 enum class 或 enum struct 声明。
*/
#include <cstdint>

// enum class Color
// {
//     Red,
//     Green,
//     Blue
// };
// Color color = Color::Red; // 使用作用域枚举时，必须指定作用域

// enum class Direction : uint8_t
// {
//     North = 1,
//     South = 2,
//     East = 3,
//     West = 4
// }
/*
   可以前向声明
*/

// enum class Month : uint8_t
// {
//     Jan = 1,
//     Feb,
//     Mar,
//     Apr,
//     May,
//     Jun,
//     Jul,
//     Aug,
//     Sep,
//     Oct,
//     Nov,
//     Dec
// };

// void printMonth(Month m)
// {
//     switch (m)
//     {
//     case Month::Jan:
//         std::cout << "January";
//         break;
//     case Month::Feb:
//         std::cout << "February";
//         break;
//     // ... 其他月份
//     default:
//         std::cout << "Invalid month";
//     }
//     std::cout << " (" << static_cast<int>(m) << ")\n";
// }

// int main()
// {
//     Month m = Month::Apr;
//     printMonth(m);

//     // 比较
//     if (m == Month::Apr)
//     {
//         std::cout << "It's April!\n";
//     }

//     // 转换为整数需要显式转换
//     int monthNum = static_cast<int>(m);
//     std::cout << "Month number: " << monthNum << "\n";

//     return 0;
// }

// constexpr 与字面类型
/*
    1. constexpr 关键字
    用于声明常量表达式，编译时求值，提升性能。

    1.1 constexpr 函数
    constexpr 函数在编译时求值，可以用于常量表达式。

    与 const 的区别：
        const 只保证运行时不修改
        constexpr 保证值在编译时已知
*/

// 字面类
// class Point
// {
// public:
//     constexpr Point(double xVal, double yVal) : x(xVal), y(yVal) {}
//     constexpr double getX() const { return x; }
//     constexpr double getY() const { return y; }

// private:
//     double x, y;
// };

// constexpr Point origin(0.0, 0.0);
// constexpr Point translated(const Point &p, double dx, double dy)
// {
//     return Point(p.getX() + dx, p.getY() + dy);
// }

// constexpr Point p2 = translated(origin, 1.0, 2.0);

// 列表初始化
// class Timer
// {
// public:
//     Timer();
// };

// class TimeKeeper
// {
// public:
//     TimeKeeper(const Timer &t);
// };

// TimeKeeper tk(Timer()); // 可能被解析为函数声明
// TimeKeeper tk{Timer()}; // 明确表示初始化

// struct Aggregate
// {
//     int x;
//     double y;
//     char z;
// };

// Aggregate a1{1, 2.5, 'c'}; // 直接初始化成员
// Aggregate a2{};            // 值初始化，所有成员为0/null

// int main()
// {
//     int x{5};
//     double y{3.14};
//     int arr[]{1, 2, 3, 4, 5};
//     std::vector<int> v{1, 2, 3, 4, 5};
//     int *p = new int[5]{1, 2, 3, 4, 5}; // 动态数组初始化

//     return 0;
// }

// 委托与继承的构造函数
/*
    委托构造函数和继承构造函数，它们分别解决了类内构造函数代码重复和基类构造函数继承的问题。
*/

// class MyClass
// {
// public:
//     MyClass() : MyClass(0, 0)
//     {
//         // 委托给下面的构造函数
//         std::cout << "Default constructor called" << std::endl;
//     }
//     MyClass(int a) : MyClass(a, 0)
//     {
//         // 委托给下面的构造函数
//         std::cout << "Single argument constructor called" << std::endl;
//     }
//     MyClass(int a, int b) : x(a), y(b)
//     {
//         // 直接初始化成员变量
//         std::cout << "Two arguments constructor called" << std::endl;
//     }

// private:
//     int x;
//     int y;
// };

// int main()
// {
//     // MyClass obj1;        // 委托构造函数
//     // MyClass obj2(5);     // 委托构造函数
//     // MyClass obj3(5, 10); // 直接调用

//     return 0;
// }

// 继承构造函数 (Inheriting Constructors)
// class Base
// {
// public:
//     Base(int);
//     Base(int, double);
// };

// class Derived : public Base
// {
// public:
//     using Base::Base; // 继承Base的所有构造函数
// };

// 相当于隐式生成：
// Derived(int x) : Base(x) {}
// Derived(int x, double y) : Base(x, y) {}

// class Base
// {
// public:
//     Base(int x) : x(x) {}
//     Base(int x, double y) : x(x), y(y) {}

// protected:
//     int x;
//     double y;
// };

// class Derived : public Base
// {
// public:
//     using Base::Base; // 继承Base的构造函数

//     // 委托构造函数
//     Derived() : Derived(0, 0.0) {}

//     // 可以添加新构造函数
//     Derived(const std::string &s) : Base(s.length()), str(s) {}

// private:
//     std::string str;
// };