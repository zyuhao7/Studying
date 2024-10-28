#include <iostream>
#include <exception>
#include "currency.h"
using namespace std;
// day-2024-10-28

// 本章复习的 C++ 特性如下:

// 参数传递的不同方式(如值传递、引用传递和常量引用传递)。
// 函数或方法返回的不同方式(如值返回、引用返回和常量引用返回)。
// 模板函数。
// 递归函数。
// 常量函数。
// 内存分配和释放函数:new和delete。
// 异常处理结构:try、catch 和 throw。
// 类与模板类。
// 类的公有成员、保护成员和私有成员。
// 友元。
// 操作符重载。

// ·标准模板库。
// 本章没有涉及的 C++特性将在后续章节需要的时候加以介绍。本章包含如下应用程序的代码:

// 动态分配与释放一维和二维数组。
// 求解二次方程。
// 生成 n 个元素的所有排列方式。
// 寻找 n 个元素的最大值。
// 此外，本章还给出测试和调试程序的一些技巧。

// int abc(int a, int b, int c)
// {
//     cout << "int abc(int a, int b, int c)" << endl;
//     return 0;
// }

// float abc(float a, float b, float c)
// {
//     cout << "float abc(float a, float b, float c)" << endl;
//     return 0.0;
// }
// int abc(int a, int b, int c)
// {
//     if (a <= 0 || b <= 0 || c <= 0)
//         throw illegalParameterValue("All parameter should be > 0");
//     return a + b * c;
// }
// int main()
// {
//     try
//     {
//         cout << abc(2, 0, 4) << endl;
//     }
//     catch (illegalParameterValue e)
//     {
//         cout << "the parameters to abc were 2, 0 and 4 " << endl;
//         cout << "illegalParameterValue exception thrown" << endl;
//         e.outputMessage();
//         return 1;
//     }

//     // abc(1, 2, 3);
//     // abc(1.0F, 2.0F, 3.0F);
//     //  abc(1, 2, 3.0F); // err
//     // abc(1.0, 2.0, 3.0); // ambiguous

//     return 0;
// }

// int main()
// {
//     currency g, h(positive, 3, 50), i, j;
//     g.setValue(negative, 2, 25);
//     i.setValue(-6.45);

//     j = h.add(g);

//     h.output();
//     cout << " + ";
//     g.output();
//     cout << " = ";
//     j.output();
//     cout << endl;

//     j = i.add(g).add(h);
//     j = i.increment(g).add(h);

//     return 0;
// }

// 递归函数
// #include <algorithm>
// #include <ostream>
// #include <iterator>
// void permutations(int list[], int k, int m)
// {
//     if (k == m)
//     {
//         copy(list, list + m + 1,
//              ostream_iterator<int>(cout, " "));

//         cout << endl;
//     }
//     else
//         for (int i = k; i <= m; ++i)
//         {
//             swap(list[i], list[k]);
//             permutations(list, k + 1, m);
//             swap(list[i], list[k]);
//         }
// }
// int main()
// {
//     int arr[] = {1, 2, 3};
//     permutations(arr, 0, 2);
//     return 0;
// }

// 练习:
// 19. 编写非递归程序计算 n!.

// 非递归.
// int Fibonacci(int x)
// {
//     int n = 1;
//     int n1 = 0, n2 = 1;
//     for (int i = 1; i < x; ++i)
//     {
//         n = n1 + n2;
//         n1 = n2;
//         n2 = n;
//     }
//     return n;
// }

// int f[1001] = {0};
// // 递归
// int Fibonacci2(int x)
// {
//     if (x <= 1)
//         return x;
//     if (f[x])
//         return f[x];

//     f[x] = Fibonacci2(x - 2) + Fibonacci2(x - 1);
//     return f[x];
// }

// int main()
// {
//     // cout << Fibonacci(1) << endl;
//     // cout << Fibonacci(2) << endl;
//     // cout << Fibonacci(3) << endl;
//     // cout << Fibonacci(4) << endl;
//     // cout << Fibonacci(10) << endl;

//     cout << Fibonacci2(1) << endl;
//     cout << Fibonacci2(3) << endl;
//     cout << Fibonacci2(10) << endl;

//     return 0;
// }

// 23. 最大公约数(Greatest Common Divisor GCD) .
// int gcd(int a, int b)
// {
//     if (!b)
//         return a;
//     return gcd(b, a % b);
// }
// int main()
// {
//     cout << gcd(4, 8) << endl;
//     cout << gcd(20, 30) << endl;
//     cout << gcd(112, 42) << endl;
// }

// 25 [子集生成方法(Subset Generation)], 输出 n 个元素的所有子集. 例如 {a, b, c} -> {} {a} {b} {c} {a, b} ....
// #include <string>

// void SubsetGeneration(string str, int k, int m)
// {
//     if (k == m)
//     {
//         cout << str << endl;
//     }
//     for (int i = k; i <= m; ++i)
//     {
//         swap(str[i], str[k]);
//         SubsetGeneration(str, k + 1, m);
//         swap(str[i], str[k]);
//     }
// }
// int main()
// {
//     string s = "abc";
//     SubsetGeneration(s, 0, 2);

//     return 0;
// }

// #include <vector>

// void generateSubsets(int n, int index, vector<int> &subset)
// {
//     if (index == n)
//     {
//         for (int i = 0; i < n; i++)
//         {
//             cout << subset[i];
//         }
//         cout << endl;
//         return;
//     }

//     subset[index] = 0;
//     generateSubsets(n, index + 1, subset);

//     subset[index] = 1;
//     generateSubsets(n, index + 1, subset);
// }

// int main()
// {
//     int n;
//     cout << "输入元素个数 n: ";
//     cin >> n;

//     vector<int> subset(n);
//     generateSubsets(n, 0, subset);

//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <cmath>

// using namespace std;

// void generateSubsets(int n)
// {
//     int totalSubsets = pow(2, n); // 子集数量为 2^n

//     // 遍历每一个从 0 到 (2^n - 1) 的数字，这些数字的二进制表示即为子集
//     for (int i = 0; i < totalSubsets; ++i)
//     {
//         for (int j = n - 1; j >= 0; --j)
//         {
//             // 使用位运算判断每个位置的元素是否在子集中
//             cout << ((i >> j) & 1);
//         }
//         cout << endl;
//     }
// }

// int main()
// {
//     int n;
//     cout << "输入元素个数 n: ";
//     cin >> n;

//     generateSubsets(n);

//     return 0;
// }

// 标准模板库 STL
// C++ 标模板库是一个容器、适配器、迭代器、函数对象(仿函数)和算法的合集。
// #include <algorithm>
// #include <numeric>

// int product(int a[], int n)
// {
//     return accumulate(a, a + n, 1, multiplies<int>());
// }

// int main()
// {
//     int a[] = {1, 2, 5, 7};
//     cout << product(a, 4);
//     return 0;
// }

// 求解二次方程 a * x^2 + b * x + c 的根
// #include <cmath>
// void outputRoots(const double &a, const double &b, const double &c)
// {
//     int d = b * b - 4 * a * c;
//     if (d > 0)
//     {
//         // 有两个实根.
//         double sqrtd = sqrt(d);
//         cout << "two real roots: " << (-b + sqrtd) / 2 * a << "  and  " << (-b - sqrtd) / 2 * a << endl;
//     }
//     else if (d == 0)
//     {
//         cout << "two same root, is " << (-b) / 2 * a << endl;
//     }
//     else
//     {
//         cout << "the root are complex: " << -b / (2 * a) << " + " << sqrt(-d) / 2 * a << "i" << endl;
//     }
// }

// int main()
// {
//     outputRoots(1, 2, 5);
// }