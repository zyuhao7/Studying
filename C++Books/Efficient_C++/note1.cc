#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
using namespace std;

// day-2024-10-15
// 第八章 内联基础

// 内联类似于宏,在调用方法内部展开被调用方法, 以此来代替方法的调用.

// class GateInt
// {
//     int x;

// public:
//     // 类内成员函数默认 内联. 或者类外定义加 inline.
//     int get()
//     {
//         return x;
//     }
//     void set(int arg)
//     {
//         x = arg;
//     }
// };

// int calc(int num1, int num2)
// {
//     return num1 + num2;
// }
// int main()
// {
//     int x[2000];
//     int y[2000];
//     int z[2000];
//     auto start = chrono::high_resolution_clock::now();
//     for (int i = 0; i < 2000; ++i)
//     {
//         for (int j = 0; j < 2000; ++j)
//         {
//             for (int k = 0; k < 2000; ++k)
//             {
//                 z[i] = calc(y[j], x[k]);
//             }
//         }
//     }
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
//     std::cout << "spends: " << duration.count() << " seconds" << std::endl;
//     // 没内联 :  14 s
// 内联 : 14 s 估计优化了.

// GateInt gi;
// gi.set(12);
// cout << gi.get() << endl;
//     return 0;
// }

// 内联就是用方法的代码来替换对方法的调用.
// 内联通过消除调用开销来提升性能, 并且允许进行调用间优化.
// 内联的主要作用是对运行时间进行优化, 荡然它也可以使可执行映像变得更小.