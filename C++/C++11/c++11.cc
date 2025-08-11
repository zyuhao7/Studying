#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <functional>
using namespace std;

// day-2025-3-29
// day-2025-8-11 review

// 1. auto 与 decltype
auto add = [](int a, int b)
{ return a + b; };

decltype(auto) sub = [](int a, int b)
{
    return a - b;
};

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

// 右值引用
/*
    2.1 移动语义（Move Semantics）
    移动语义允许我们将一个对象的资源（如内存）转移到另一个对象，而不是进行深拷贝，从而避免不必要的资源分配和释放。
    移动语义避免了 不必要的拷贝，提升性能。例如：
*/
class MyString
{
private:
    char *data;

public:
    // 构造函数
    MyString(const char *str)
    {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        std::cout << "构造" << std::endl;
    }

    // 拷贝构造函数（左值引用，深拷贝）
    MyString(const MyString &other)
    {
        std::cout << "拷贝构造" << std::endl;
        data = new char[strlen(other.data) + 1]; // 分配内存
        strcpy(data, other.data);                // 深拷贝
    }

    // 移动构造函数（右值引用，浅拷贝）
    MyString(MyString &&other) noexcept
    {
        data = other.data;    // 直接移动指针
        other.data = nullptr; // 清空原对象，防止释放
        std::cout << "移动构造" << std::endl;
    }

    ~MyString()
    {
        delete[] data;
    }
};

// int main()
// {
//     MyString a("Hello");
//     // std::move 用于将左值转换为右值引用，从而触发移动语义
//     MyString b = std::move(a); // 触发移动构造
// }

/*
    2.2 右值引用用于函数参数
    右值引用可以用于 高效传递临时对象：
*/

// 右值引用，避免拷贝
void process(std::string &&str)
{
    /// 类似于:
    // std::string temp("Hello");  // 隐式构造一个临时 `std::string`
    // process(std::move(temp));   // 右值引用绑定，无拷贝

    std::cout << "Before: " << str << ", Capacity: " << str.capacity() << std::endl;
    str += " Processed"; // 追加数据，可能扩容

    std::cout << "After: " << str << ", Capacity: " << str.capacity() << std::endl;
    std::cout << "Processing: " << str << std::endl;
}

// int main()
// {
//     process("Temporary String"); //  右值传递，避免不必要的拷贝
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

// constexpr 泛化的常量表达式 与字面类型
/*
    constexpr 关键字
    constexpr 是 "constant expression" 的缩写，用于声明编译时常量表达式 。
    它可以应用于变量、函数和构造函数，使得这些实体能够在编译时计算值，而不是在运行时。

    与 const 的区别：
        const 只保证运行时不修改, 但值可能在运行时确定
        constexpr 保证值在编译时即可确定，并且不可修改

    字面类型（Literal Type）
    字面类型是指在编译时就可以确定值的类型，例如整数、浮点数、字符、枚举类型等。

    字面类的条件
    - 有 constexpr 构造函数
    - 所有非静态数据成员和基类都是字面类型
    - 如有析构函数，必须是默认析构函数

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
// constexpr int size = 10;
// int arr[size]; // 合法，size 是编译时常量

// constexpr Point p2 = translated(origin, 1.0, 2.0);

// constexpr 函数
// template <typename T>
// constexpr T cube(T x)
// {
//     return x * x * x;
// }

// // 字面类
// class Rectangle
// {
// public:
//     constexpr Rectangle(int w, int h) : width(w), height(h) {}
//     constexpr int area() const { return width * height; }

// private:
//     int width, height;
// };

// int main()
// {
//     // 编译时计算
//     constexpr int a = cube(3);
//     std::cout << "3的立方: " << a << std::endl;

//     // 字面类使用
//     constexpr Rectangle rect(5, 4);
//     std::cout << "矩形面积: " << rect.area() << std::endl;

//     // 数组大小
//     constexpr int size = 5;
//     int arr[size] = {1, 2, 3, 4, 5};

//     return 0;
// }

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

// 花括号或等号初始化器
/*
    在 C++11 及以后，推荐优先使用花括号 {} 进行变量初始化，原因如下：

    防止窄化转换（Narrowing Conversion）：即不允许 double 隐式转换为 int，或 long long 转换为 int，避免精度丢失。
    统一初始化方式：支持内置类型、类类型、数组、容器等。
    支持 std::initializer_list<T>，可以更灵活地初始化容器。

*/

// int main()
// {
//     int *p1 = new int(42);
//     int *p2 = new int(); // 初始化 0
// }

// nullptr
// #define NULL 0  // C++03 及以前
// #include <type_traits>
// int main()
// {
//     std::nullptr_t np = nullptr;
//     std::cout << std::boolalpha << std::is_same<decltype(nullptr), std::nullptr_t>::value << std::endl;

//     return 0;
// }

// long long
/*
    long long 至少 64 位（即 -2^63 到 2^63 - 1）。

    unsigned long long 至少 64 位（即 0 到 2^64 - 1）。
*/

// int main()
// {
//     std::cout << "sizeof(int): " << sizeof(int) << " bytes\n";             // 4
//     std::cout << "sizeof(long): " << sizeof(long) << " bytes\n";           // 4
//     std::cout << "sizeof(long long): " << sizeof(long long) << " bytes\n"; // 8
// }

// char16_t 与 char32_t
/*
    char16_t	表示 UTF-16 编码单元，即 16 位字符	2 字节（16 位）
    char32_t	表示 UTF-32 编码单元，即 32 位字符	4 字节（32 位）
*/

// 类型别名

// typedef unsigned int uint;
// using uit = unsigned int;

// typedef char *pStr1;
// using pStr2 = char *;

// pStr1 a, b; // a 和 b 都是 char*
// pStr2 c, d; // c 和 d 也是 char*

// using 在模板中的应用
// template <typename T>
// typedef std::vector<T> Vec; // ❌ 错误，typedef 不能用于模板

// template <typename T>
// using Vec = std::vector<T>; // ✅ 正确，Vec<T> 相当于 std::vector<T>

// Vec<int> numbers; // 等价于 std::vector<int>

// 函数指针别名
// typedef void (*FuncPtr)(int, double);
// using FuncPtr = void (*)(int, double);

//  复杂 STL 类型
// using StringList = std::vector<std::string>;
// using MapIntToStr = std::map<int, std::string>;

// 变参数模板
// template <typename... Args>
// void print(Args... args)
// {
//     cout << "Argument number : " << sizeof...(args) << endl;
// }

// 变参数模板展开
// void print()
// {
//     std::cout << "recursion end" << endl;
// }
// template <typename T, typename... Args>
// void print(const T &val, Args... args)
// {
//     cout << val << " ";
//     print(args...);
// }
// 通过 initializer_list 一次性展开
// template <typename... Args>
// void print(Args... args)
// {
//     (std::cout << ... << args) << endl; // C++ 17 折叠表达式
// }

// template <typename... Args>
// void print(Args... args)
// {
//     int dummy[] = {(std::cout << args << " ", 0)...};
//     (void)dummy;
//     std::cout << endl;
// }

// 变参数模板与 std::forward（完美转发）
// template <typename... Args>
// void forwardCall(Args &&...args)
// {
//     print(std::forward<Args>(args)...); // 保持参数的原始类型
// }

// std::make_shared 使用变参数模板来完美转发构造参数。
// #include <memory>

// int main()
// {
//     print();
//     print(1, 2, 3);
//     print(1.0, 2.0);

//     return 0;
// }

// lambda 表达式
/*
    [capture-list](parameters) mutable noexcept -> return-type {
        function-body
    }
    捕获列表：[] 用于指定 lambda 表达式可以访问的外部变量。
    参数列表：(参数) 用于指定 lambda 表达式的参数。
    异常说明符：noexcept 或 throw() 用于指定 lambda 表达式是否会抛出异常。
    返回类型：-> 返回类型 用于指定 lambda 表达式的返回类型。
    函数体：{} 用于定义 lambda 表达式的主体。
*/

// int main()
// {
//     int x = 10;
//     auto lambda = [x](int y) -> int
//     { return x + y; };

// 编译器生成的匿名类
// class LambdaClass
// {
// private:
//     int x; // 捕获的变量（按值）
// public:
//     // 构造函数，初始化捕获的变量
//     LambdaClass(int x_val) : x(x_val) {}

//     // 重载operator()
//     int operator()(int y) const  mutable的话去除 const
//     {
//         return x + y;
//     }
// };

// auto lambda = LambdaClass(x); // 创建函数对象

// cout << lambda(5) << endl;    // 输出 15
// }

// noexcept 说明符与 noexcept 运算符
/*
    noexcept 说明符用于声明一个函数 不会抛出异常
*/
#include <utility>

void foo() noexcept;
void bar() { throw 1; }

// struct A
// {
//     A() {}
//     A(A &&) noexcept { cout << "A moved" << endl; }
// };

// struct B
// {
//     B() {}
//     B(B &&) { cout << "B moved" << endl; } // 没有 noexcept 导致编译器可能会选择复制而不是移动
// };

// alignof 与 alignas
/*
    alignof 用于获取某个类型的对齐要求（alignment requirement），即该类型的变量在内存中的对齐字节数
    alignas 用于指定变量或类型的对齐方式，确保其满足特定的对齐要求。这在优化性能（如 SIMD 指令）或满足硬件需求时很有用。
*/

// struct A
// {
//     double d;
//     int i;
// }; // 8 字节对齐
// struct B
// {
//     char c;
//     int i;
// }; // 4 字节对齐

// struct alignas(16) A
// { // 结构体 A 强制对齐到 16 字节
//     double d;
//     int i;
// };

// alignas(32) int arr[4]; // 数组 `arr` 需 32 字节对齐

// int main()
// {
// cout << "Alignment of arr: " << alignof(arr) << endl;
// cout << "Address of arr: " << &arr << endl;
// cout << "Alignment of A: " << alignof(A) << endl;
// cout << "Size of A: " << sizeof(A) << endl;
// cout << "Alignment of int: " << alignof(int) << endl;
// cout << "Alignment of double: " << alignof(double) << endl;
// cout << "Alignment of A: " << alignof(A) << endl;
// cout << "Alignment of B: " << alignof(B) << endl;

// cout << boolalpha;
// cout << "A is noexcept movable: " << noexcept(A(declval<A>())) << endl;
// cout << "B is noexcept movable: " << noexcept(B(declval<B>())) << endl;

// cout << boolalpha;
// cout << "foo is noexcept : " << noexcept(foo()) << endl;
// cout << "bar is noexcept : " << noexcept(bar()) << endl;
// }

// 多线程内存模型

// int main()
// {
//     int arr[3]{};
//     for (int i = 0; i < 3; ++i)
//         cout << arr[i] << " ";

//     auto il = {10, 20, 30};
//     cout << typeid(il).name() << endl;
// }

// 外部模板
/*
    在标准C++中，只要在编译单元内遇到被完整定义的模板，编译器都必须将其实例化（instantiate）。
    这会大大增加编译时间，特别是模板在许多编译单元内使用相同的参数实例化。

    在 C++ 中，模板通常在头文件中定义，当多个源文件包含同一个模板并使用相同类型实例化时，每个源文件都会独立实例化该模板，导致：
    - 编译时间增加
    - 目标文件变大
    - 链接时需要合并重复的实例化代码

    C++11 引入 extern template 声明，允许我们：
    - 在头文件中声明模板的特定实例化为外部的（不进行实例化）
    - 在一个源文件中显式实例化该模板
    - 其他源文件使用该模板实例时会引用已实例化的版本
    - 可以避免重复实例化，减少编译时间和目标文件大小

*/
// 1. 外部模板声明
// 声明外部模板类
// extern template class Vector<int>;
// 声明外部模板函数
// extern template void sort<int*>(int*, int*);

// 2. 显式模板实例化
// 显式实例化模板类
// template class Vector<int>;

// 显式实例化模板函数
// template void sort<int *>(int *, int *);

// vector.h
// template <typename T>
// class Vector
// {
//     // 类定义...
// };

// 声明外部模板，告诉编译器不要在包含此头文件的源文件中实例化
// extern template class Vector<int>;
// extern template class Vector<double>;

// 一个源文件中显式实例化
// vector_inst.cpp
// #include "vector.h"

// 显式实例化，只在这个源文件中生成代码
// template class Vector<int>;
// template class Vector<double>;

// 3. 其他源文件中使用
// main.cpp
// #include "vector.h"

// int main() {
//     Vector<int> v1;  // 使用已在 vector_inst.cpp 中实例化的版本
//     Vector<double> v2;  // 同上
//     return 0;
// }

// 回返类别后置的函数声明
// template <typename LHS, typename RHS>
// Ret AddingFunc(const LHS &lhs, const RHS &rhs) { return lhs + rhs; } // Ret的型別必須是(lhs+rhs)的型別

// template <typename LHS, typename RHS>
// decltype(lhs + rhs) AddingFunc(const LHS &lhs, const RHS &rhs) { return lhs + rhs; } // 不合法的C++11

// template <typename LHS, typename RHS>
// auto AddingFunc(const LHS &lhs, const RHS &rhs) -> decltype(lhs + rhs) { return lhs + rhs; }

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

// 这种语法也能套用到一般的函数定义与声明：
// struct SomeStruct
// {
//     auto FuncName(int x, int y) -> int;
// };

// auto SomeStruct::FuncName(int x, int y) -> int
// {
//     return x + y;
// }