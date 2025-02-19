#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
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

// int main()
// {
//     // printAll("hello", 1, 2.3, "world");

//     // cout << sum(1, 2, 3, 4, 5) << endl;

//     // log("Error", 404, "Not Found");
//     // log("Sum", 10, 20, 30);
//     return 0;
// }

// day-2025-2-19
// 模板折叠

// 嵌套折叠表达式  左折叠 * 右折叠 左 * 左 右 * 右一样
// template <typename... Args>
// auto complexFold(Args... args)
// {
//     return (args + ...) * (... + args);
// }

// // 左移操作符 (流插入)
// template <typename... Args>
// void printAll(Args... args)
// {
//     (cout << ... << args) << endl;
// }

// // 字符串拼接
// template <typename... Args>
// std::string concatenate(const Args &...args)
// {
//     return (std::string{} + ... + args);
// }

// template <typename... Args>
// auto sumWithInit(int init, Args... args)
// {
//     return (init + ... + args); // 左折叠
// }
// // 参数包为空的情况
// template <typename... Args>
// auto sum(Args... args)
// {
//     return (0 + ... + args);
// }

// int main()
// {
//     cout << complexFold(1, 2, 3) << endl;
//     printAll(1, 2, 3, "hello", 4.5);
//     cout << concatenate("hello", "world", "C++", "17") << endl;
//     cout << sumWithInit(10, 1, 2, 3, 4, 5) << endl;
//     cout << sum(1, 2, 3, 4, 5) << endl;
//     cout << sum() << endl;
//     return 0;
// }

#include <type_traits>
// SFINAE
// 整数类型
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_type(T value)
{
    cout << "Integer type : " << value << endl;
}
// 浮点类型
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
print_type(T value)
{
    cout << "Floating point type:" << value << endl;
}

// 检测类型是否具有特定成员
// 辅助函数, 检测是否存在成员函数 foo
template <typename T>
class has_foo
{
private:
    typedef char yes[1];
    typedef char no[2];

    template <typename U, void (U::*)()>
    struct SFINAE
    {
    };

    template <typename U>
    static yes &test(SFINAE<U, &U::foo> *);

    template <typename U>
    static no &test(...);

public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

// 函数仅在 T 类型具有成员函数 foo 时才会被实例化
template <typename T>
typename std::enable_if<has_foo<T>::value, void>::type
call_foo(T &obj)
{
    obj.foo();
    cout << "foo() called!" << endl;
}

class WithFoo
{
public:
    void foo()
    {
        cout << "WithFoo::foo() called!" << endl;
    }
};

class WithoutFoo
{
};

int main()
{
    print_type(10);
    print_type(10.5);
    WithFoo wf;
    call_foo(wf);
    WithoutFoo wo;
    // call_foo(wo); // 编译错误
    return 0;
}