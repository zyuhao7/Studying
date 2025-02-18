#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include <string>
using namespace std;

// day-2025-2-18
// 第十六章-模板与泛型编程
// 定义模板
int compare(const string &s1, const string &s2)
{
    if (s1 < s2)
        return -1;
    if (s1 > s2)
        return 1;
    return 0;
}

// 函数模板
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

// 非类型模板参数
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

// template <typename T>
// int compare(const T &v1, const T &v2)
// {
//     if (less<T>()(v1, v2))
//         return -1;
//     if (less<T>()(v2, v1))
//         return 1;
//     return 0;
// }

// 类模板
template <typename T>
class Blob
{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(std::initializer_list<T> il);
    Blob(T *p, size_t n);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    T &back();
    T &operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
T &Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "index out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()){};

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)){};

// 模板参数
template <typename Foo>
Foo calc(const Foo &a, const Foo &b)
{
    Foo tmp = a;
    a = b;
    b = tmp;
    return tmp;
}
// 成员模板
class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}

    template <typename T>
    void operator()(T *p) const
    {
        os << " deleting unique_ptr " << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};
int main()
{
    // cout << compare(1, 0) << endl;

    // vector<int> v1{1, 2, 3}, v2{4, 5, 6};
    // cout << compare(v1, v2) << endl;
    // cout << compare("hi", "mom") << endl;

    // Blob<int> ia;
    // Blob<int> ia2 = {0, 1, 2, 3, 4};

    // double *p = new double;
    // DebugDelete d;
    // d(p); // 调用DebugDelete::operator()(double*)

    // unique_ptr<int, DebugDelete> p1(new int, DebugDelete());
    // unique_ptr<string, DebugDelete> p2(new string, DebugDelete());

    

    return 0;
}