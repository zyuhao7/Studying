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