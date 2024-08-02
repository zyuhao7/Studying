#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;
// 仿函数.

// 证同元素 Identity element
// 所谓 "运算 op 的证同元素", 意思是数值 A 若与该元素做 op 运算, 会得到 A 自己, 加法的证同元素为0, 因为任何元素加上0仍为自己.
// 乘法的证同元素为1.

template <class T>
inline T Identity_element(plus<T>)
{
    return T(0);
} // SGI STL 并未实际运用这个函数.

template <class T>
inline T Identity_element(multiplies<T>)
{
    return T(1);
} // 乘法的证同元素应用与 <stl_numerics.h> 的 power() 中.

template <class T>
struct identity : public unary_function<T, T>
{
    const T &operator()(const T &x) const
    {
        return x;
    }
};

// 选择函数 接受一个 pair 返回其第一元素.
// 由于 map 系以 pair 元素的第一元素为其键值 所以采用 select1st
template <class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type>
{
    const typename Pair::first_type &operator()(const Pair &x) const
    {
        return x.first;
    }
};

// 选择函数, 接受一个 pair 返回其第二元素
template <class Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type>
{
    const typename ::second2nd &operator()(const Pair &x) const
    {
        return x.second;
    }
};

// 投影函数 传回第一参数, 忽略第二参数
template <class Arg1, class Arg2>
struct project1st : public binary_function<Arg1, Arg2, Arg1>
{
    Arg1 operator()(const Arg1 &x, const Arg2 &) const
    {
        return x;
    }
};

// 传回第二参数, 忽略第一参数.
struct project1st : public binary_function<Arg1, Arg2, Arg2>
{
    Arg2 operator()(const Arg1 &, const Arg2 &y) const
    {
        return y;
    }
};

int main()
{
    greater<int> ig;
    cout << boolalpha << ig(4, 6) << endl; // false
    cout << greater<int>()(6, 4) << endl;  // true

    int a[] = {2, 3, 4, 5};
    vector<int> v(a, a + 4);
    cout << accumulate(v.begin(), v.end(), 1, multiplies<int>()) << endl; // 120.
    sort(v.begin(), v.end());                                             // 默认 less<int>().
    for (int e : v)
        cout << e << " "; // 2 3 4 5
    cout << endl;
    return 0;
}
