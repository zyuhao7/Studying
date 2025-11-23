#include <type_traits>
#include <iostream>
using namespace std;

// Day-2025-11-23
//  std::enable_if_t
//  std::enable_if 是 C++11 引入的元编程工具，用于按条件启用/禁用模板。
//  enable_if_t 是 C++14 对其的简化版本：
// template <bool B, class T = void>
// using enable_if_t = typename std::enable_if<B, T>::type;
// 如果条件 B 是 true，则 enable_if_t<true, T> 展开为 T；
// 如果条件 false，匹配失败（SFINAE），该模板就被排除。

// template <typename T>
// std::enable_if_t<std::is_integral_v<T>, void>
// foo(T)
// {
//     std::cout << "integral\n";
// }

// template <typename T>
// std::enable_if_t<std::is_integral_v<T>>
// foo(T)
// {
//     std::cout << "integral\n";
// }

// template <typename T>
// auto foo(T x) -> std::enable_if_t<std::is_floating_point_v<T>, int>
// {
//     std::cout << "floating point\n";
//     return 1;
// }

// template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
// void bar(T)
// {
//     std::cout << "bar integer\n";
// }

// int main()
// {
//     foo(42);    // 调用成功，输出 "integral"
//     foo(3.14f); // 调用成功，输出 "floating point"
//     bar(10);    // 调用成功，输出 "bar integer"
//     // bar(2.71);    // 调用失败，编译错误
//     // foo(3.14);   // 调用失败，编译错误
// }

[[noreturn]] void func()
{
    std::terminate();
}

int main()
{
    func();
}