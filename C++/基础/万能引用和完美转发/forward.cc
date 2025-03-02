#include <iostream>
#include <string>
#include <utility>
#include <type_traits>
using namespace std;

// day-2025-3-2
// 右值
// 纯右值:  表示临时对象或者字面量
// 将亡值: 表示即将被移动的对象

// int main()
// {
//     int a = 10;
//     int &b = a;
//     int &&c = 20;
//     int d = a + 5; // a + 5 是一个纯右值

//     cout << std::boolalpha;
//     // `(a)` 是一个左值表达式，所以 decltype((a)) 是 `int&`
//     cout << "a是左值: " << is_lvalue_reference<decltype((a))>::value << endl;
//     cout << "c 是右值引用: " << is_rvalue_reference<decltype(c)>::value << endl;

//     return 0;
// }

// void func(int &x)
// {
//     std::cout << "func(int&)" << std::endl;
// }

// void func(int &&x)
// {
//     std::cout << "func(int&&)" << std::endl;
// }

// int main()
// {
//     int a = 5;
//     const int &ref = a;
//     cout << boolalpha;

//     cout << "ref 是左值引用: " << is_lvalue_reference<decltype(ref)>::value << endl;
//     func(a);
//     func(100);

//     return 0;
// }

// 模板万能引用
// template <typename T>
// void check_reference(T &&x)
// {
//     cout << boolalpha;
//     cout << "T 是左值引用: " << is_lvalue_reference<T>::value << endl;
//     cout << "T 是右值引用: " << is_rvalue_reference<T>::value << endl;
//     cout << "T 是右值: " << is_rvalue_reference<T &&>::value << endl;
//     cout << "x 是左值引用: " << is_lvalue_reference<decltype(x)>::value << endl;
//     cout << "x 是右值引用: " << is_rvalue_reference<decltype(x)>::value << endl;
// }

// int main()
// {
//     int a = 10;
//     check_reference(a);
//     check_reference(20);
//     int &&c = 100;
//     cout << "==========================" << endl;
//     check_reference(c); // 然而，实际中 T 被推导为 int&，这是因为 命名的右值引用变量在表达式中被视为左值。
//     cout << "==========================" << endl;
//     check_reference(std::move(c));
//     return 0;
// }

// void process(int &x)
// {
//     std::cout << "process(int&)" << std::endl;
// }

// void process(int &&x)
// {
//     std::cout << "process(int&&)" << std::endl;
// }

// template <typename T>
// void wrapper(T &&arg)
// {
//     process(std::forward<T>(arg));
// }

// int main()
// {
//     int a = 10;
//     wrapper(a);
//     wrapper(20);
//     return 0;
// }

//  类型推导（Type Deduction）

// template <typename T>
// void deduce_type(T &&)
// {
//     cout << boolalpha;
//     cout << "T 是左值引用: " << is_lvalue_reference<T>::value << endl;
//     cout << "T 是右值引用: " << is_rvalue_reference<T &&>::value << endl;
// }

// int main()
// {
//     int a = 0;
//     const int &ref = a;
//     deduce_type(a);
//     deduce_type(10);
//     deduce_type(ref);
//     deduce_type(std::move(a));
// }

// template <typename T>
// void display_type(T &&param)
// {
//     cout << "Type of T: "
//          << (std::is_lvalue_reference<T>::value ? "左值引用" : "右值引用")
//          << ","
//          << (is_integral<typename remove_reference<T>::type>::value ? "Integral" : "Non-Integral")
//          << endl;
// }

// int main()
// {
//     int x = 10;
//     const int &y = x;
//     display_type(x); // T被推导为 int&

//     display_type(20); // T被推导为 int&&

//     display_type(y); // T被推导为 const int&

//     display_type(std::move(x)); // T被推导为 int&&
// }

// 原样转发（Perfect Forwarding）
// class Person
// {
// public:
//     string name;
//     int age;
//     Person(string &n, int a)
//         : name(n),
//           age(a)
//     {
//         std::cout << "Constructed Person(const std::string&, int)" << std::endl;
//     }
//     Person(string &&n, int a)
//         : name(n),
//           age(a)
//     {
//         std::cout << "Constructed Person(std::string&&, int)" << std::endl;
//     }
// };

// template <typename T, typename... Args>
// T create(Args &&...args)
// {
//     return T(std::forward<Args>(args)...);
// }

// int main()
// {
//     string name = "Alice";
//     Person p1 = create<Person>(name, 30);
//     Person p2 = create<Person>(string("Bob"), 25);
// }

// 类的定义
// class BigObject
// {
// public:
//     std::string data;

//     BigObject(const std::string &d) : data(d)
//     {
//         std::cout << "BigObject constructed with lvalue" << std::endl;
//     }

//     BigObject(std::string &&d) : data(std::move(d))
//     {
//         std::cout << "BigObject constructed with rvalue" << std::endl;
//     }
// };

// // 处理函数，左值和右值的重载
// void process(const BigObject &obj)
// {
//     std::cout << "Processing lvalue BigObject" << std::endl;
// }

// void process(BigObject &&obj)
// {
//     std::cout << "Processing rvalue BigObject" << std::endl;
// }

// // 包装函数，不使用原样转发
// template <typename T>
// void bad_wrapper(T &&obj)
// {
//     process(obj); // 始终以左值形式传递
// }

// // 包装函数，使用原样转发
// template <typename T>
// void good_wrapper(T &&obj)
// {
//     process(std::forward<T>(obj)); // 原样转发
// }

// int main()
// {
//     std::string s = "Sample data";

//     // 使用bad_wrapper
//     // BigObject bo1 = BigObject(s); // 使用lvalue构造
//     // BigObject bo2 = BigObject(std::move(s)); // 使用rvalue构造

//     // bad_wrapper(bo1); // 始终作为左值处理
//     // bad_wrapper(BigObject("Temp")); // 作为左值处理，浪费移动语义

//     // 使用good_wrapper
//     // good_wrapper(bo1); // 作为左值处理
//     // good_wrapper(BigObject("Temp")); // 作为右值处理，利用移动语义

//     return 0;
// }