#include <iostream>
#include <string>
#include <vector>
using namespace std;

// day-2025-2-18
// 递归示例：打印所有参数
// void printAll()
// {
//     cout << endl;
// }
// template <typename T, typename... Args>
// void printAll(const T &first, const Args &...args)
// {
//     cout << first << " ";
//     printAll(args...);
// }

// 折叠表达式版本 C++ 17
// template <typename... Args>
// void printAll(const Args &...args)
// {
//     // 使用左折叠展开参数包，并在每个参数之后输出一个空格
//     ((std::cout << args << " "), ...);
//     std::cout << std::endl;
// }

// 折叠表达式示例：计算总和
// template <typename... Args>
// auto sum(Args... args) -> decltype((args + ...))
// {
//     return (args + ...);
// }

// 示例：日志记录器

// 基础情况：无参数
// void log(const std::string &msg)
// {
//     std::cout << msg << std::endl;
// }

//  递归情况：至少一个参数
// template <typename T, typename... Args>
// void log(const std::string &msg, const T &first, const Args &...args)
// {
//     std::cout << msg << ": " << first << " ";
//     log("", args...); // 递归调用，省略消息前缀
// }

int main()
{
    // printAll("hello", 1, 2.3, "world");

    // cout << sum(1, 2, 3, 4, 5) << endl;

    log("Error", 404, "Not Found");
    log("Sum", 10, 20, 30);
    return 0;
}