#include <iostream>
using namespace std;

// day-2024-9-16
// Item 1:理解模板类型推导

// 在模板类型推导时，有引用的实参会被视为无引用，他们的引用会被忽略
// 对于通用引用的推导，左值实参会被特殊对待
// 对于传值类型推导，const和/或volatile实参会被认为是non-const的和non-volatile的
// 在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用

// Item 2:理解auto类型推导

// auto类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list，而模板类型推导不这样做
// 在C++14中auto允许出现在函数返回值或者lambda函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是auto类型推导

// 2024-9-19
// Item 3:理解decltype

// decltype总是不加修改的产生变量或者表达式的类型。
// 对于 T 类型的不是单纯的变量名的左值表达式，decltype总是产出 T 的引用即 T&。
// C++14支持decltype(auto)，就像auto一样，推导出类型，但是它使用decltype的规则进行推导。

// Item 4:学会查看类型推导结果

// class Widget
// {
// };

// template <typename T>
// void f(const T &param)
// {
//     cout << "T =     " << typeid(T).name() << '\n'; // 显示 T PK6Widget

//     cout << "param = " << typeid(param).name() << '\n'; // 显示 param PK6Widget
// }

// int main()
// {
//     const Widget *w;
//     f(w);

//     return 0;
// }

// 类型推断可以从IDE看出，从编译器报错看出，从Boost TypeIndex库的使用看出
// 这些工具可能既不准确也无帮助，所以理解C++ 类型推导规则才是最重要的

// 第二章 auto
// Item 5:优先考虑auto而非显式类型声明

// auto变量必须初始化，通常它可以避免一些移植性和效率性的问题，也使得重构更方便，还能让你少打几个字
// 正如Item 2 和 6 讨论的，auto类型的变量可能会踩到一些陷阱

// Item 6:auto推导若非己愿，使用显式类型初始化惯用法

// 不可见的代理类可能会使auto从表达式中推导出“错误的”类型
// 显式类型初始器惯用法强制auto推导出你想要的结果

// 第三章 移步现代C++

// Item 7:区别使用()和{}创建对象

// 花括号初始化是最广泛使用的初始化语法，它防止变窄转换，并且对于C++最令人头疼的解析有天生的免疫性
// 在构造函数重载决议中，编译器会尽最大努力将括号初始化与std::initializer_list参数匹配，即便其他构造函数看起来是更好的选择
// 对于数值类型的std::vector来说使用花括号初始化和圆括号初始化会造成巨大的不同
// 在模板类选择使用圆括号初始化或使用花括号初始化创建对象是一个挑战

// Item 8:优先考虑nullptr而非0和NULL
// 优先考虑nullptr而非0和NULL
// 避免重载指针和整型
