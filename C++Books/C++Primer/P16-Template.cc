#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include <string>
using namespace std;

// day-2025-2-18
// 第十六章-模板与泛型编程
// 定义模板
// int compare(const string &s1, const string &s2)
// {
//     if (s1 < s2)
//         return -1;
//     if (s1 > s2)
//         return 1;
//     return 0;
// }

// // 函数模板
// template <typename T>
// int compare(const T &v1, const T &v2)
// {
//     if (v1 < v2)
//         return -1;
//     if (v1 > v2)
//         return 1;
//     return 0;
// }

// // 非类型模板参数
// template <unsigned N, unsigned M>
// int compare(const char (&p1)[N], const char (&p2)[M])
// {
//     return strcmp(p1, p2);
// }

// // template <typename T>
// // int compare(const T &v1, const T &v2)
// // {
// //     if (less<T>()(v1, v2))
// //         return -1;
// //     if (less<T>()(v2, v1))
// //         return 1;
// //     return 0;
// // }

// // 类模板
// template <typename T>
// class Blob
// {
// public:
//     typedef T value_type;
//     typedef typename std::vector<T>::size_type size_type;

//     Blob();
//     Blob(std::initializer_list<T> il);
//     Blob(T *p, size_t n);

//     size_type size() const { return data->size(); }
//     bool empty() const { return data->empty(); }
//     void push_back(T &&t) { data->push_back(std::move(t)); }
//     void pop_back();
//     T &back();
//     T &operator[](size_type i);

// private:
//     std::shared_ptr<std::vector<T>> data;
//     void check(size_type i, const std::string &msg) const;
// };

// template <typename T>
// void Blob<T>::check(size_type i, const std::string &msg) const
// {
//     if (i >= data->size())
//         throw std::out_of_range(msg);
// }

// template <typename T>
// T &Blob<T>::back()
// {
//     check(0, "back on empty Blob");
//     return data->back();
// }

// template <typename T>
// T &Blob<T>::operator[](size_type i)
// {
//     check(i, "index out of range");
//     return (*data)[i];
// }

// template <typename T>
// void Blob<T>::pop_back()
// {
//     check(0, "pop_back on empty Blob");
//     data->pop_back();
// }

// template <typename T>
// Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()){};

// template <typename T>
// Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)){};

// // 模板参数
// template <typename Foo>
// Foo calc(const Foo &a, const Foo &b)
// {
//     Foo tmp = a;
//     a = b;
//     b = tmp;
//     return tmp;
// }
// // 成员模板
// class DebugDelete
// {
// public:
//     DebugDelete(std::ostream &s = std::cerr) : os(s) {}

//     template <typename T>
//     void operator()(T *p) const
//     {
//         os << " deleting unique_ptr " << std::endl;
//         delete p;
//     }

// private:
//     std::ostream &os;
// };
// int main()
// {
//     // cout << compare(1, 0) << endl;

//     // vector<int> v1{1, 2, 3}, v2{4, 5, 6};
//     // cout << compare(v1, v2) << endl;
//     // cout << compare("hi", "mom") << endl;

//     // Blob<int> ia;
//     // Blob<int> ia2 = {0, 1, 2, 3, 4};

//     // double *p = new double;
//     // DebugDelete d;
//     // d(p); // 调用DebugDelete::operator()(double*)

//     // unique_ptr<int, DebugDelete> p1(new int, DebugDelete());
//     // unique_ptr<string, DebugDelete> p2(new string, DebugDelete());

//     return 0;
// }

// day-2025-2-19
// 模板实参推断
// #include <type_traits>
// template <typename T>
// void fobj(T, T)
// {
//     cout << "fobj(T, T)" << endl;
// }

// template <typename T>
// void fref(const T &, const T &)
// {
//     cout << "fref(const T &, const T &)" << endl;
// }

// // 尾置返回类型与类型转换
// template <typename It>
// auto fcn(It beg, It end) -> decltype(*beg)
// {
//     return *beg;
// }
// template <typename It>
// auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
// {
//     return *beg;
// }

// // 编写接受右值引用参数的模板函数
// template <typename T>
// void f3(T &&val)
// {
//     T t = val; // 拷贝还是绑定一个引用？ 依赖于T的类型 T是一个引用类型，val是一个左值，所以t是一个引用, 否则t是一个拷贝
//     t++;
//     cout << t << " " << val << endl;
// }

// // std::move 定义
// template <typename T>
// typename remove_reference<T>::type &&move(T &&t)
// {
//     return static_cast<typename remove_reference<T>::type &&>(t);
// }

// int main()
// {
//     string s1("a value");
//     const string s2("another value");
//     fobj(s1, s2); // fobj(T, T)
//     fref(s1, s2); // fref(const T &, const T &)
//     int a[10], b[42];
//     fobj(a, b); // fobj(T, T)
//     // fref(a, b); 类型不匹配

//     f3(0);
//     int x = 10;
//     f3(x);

//     string s3 = "hi";
//     string &&rr1 = std::move(s3);
//     string &&rr2 = std::move("hi");
//     rr1 = "hello";
//     cout << s3 << " " << rr1 << " " << rr2 << endl;
//     return 0;
// }

// day-2025-2-20
// 可变参数模板
template <typename... Args>
void g(const Args... args)
{
    cout << sizeof...(Args) << endl; // sizeof... 返回模板参数包中的参数数量
    cout << sizeof...(args) << endl; // sizeof... 返回函数的参数数量
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t)
{
    return os << t;
}
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args &...rest)
{
    os << t << ",";
    return print(os, rest...);
}

// 模板特例化
template <typename T>
int compare(const T &, const T &)
{
    cout << "compare(const T&, const T&)" << endl;
    return 0;
}
template <size_t N, size_t M>
int compare(const char (&)[N], const char (&)[M])
{
    cout << "compare(const char(&)[N], const char(&)[M])" << endl;
    return 0;
}

template <>
int compare(const char *const &p1, const char *const &p2)
{
    return strcmp(p1, p2);
}


int main()
{
    g(1, 2, 3, 4);
    g("hi", "mom");
    print(cout, 1, 2, 3, 4, "hi", "mom") << endl;

    const char *p1 = "hi", *p2 = "mom";
    compare(p1, p2);
    compare("hi", "mom");
    return 0;
}
