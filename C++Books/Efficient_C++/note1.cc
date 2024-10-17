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

// day-2024-10-17
//  第九章 内联

// inline bool is_hex(char c, int &val)
// {
//     switch (c)
//     {
//     case '0':
//         val = 0;
//         break;
//     case '1':
//         val = 1;
//         break;
//     case '2':
//         val = 2;
//         break;
//     case '3':
//         val = 3;
//         break;
//     case '4':
//         val = 4;
//         break;
//     case '5':
//         val = 5;
//         break;
//     case '6':
//         val = 6;
//         break;
//     case '7':
//         val = 7;
//         break;
//     case '8':
//         val = 8;
//         break;
//     case '9':
//         val = 9;
//         break;
//     case 'a':
//         val = 10;
//         break;
//     case 'A':
//         val = 10;
//         break;
//     case 'b':
//         val = 11;
//         break;
//     case 'B':
//         val = 11;
//         break;
//     case 'c':
//         val = 12;
//         break;
//     case 'C':
//         val = 12;
//         break;
//     case 'd':
//         val = 13;
//         break;
//     case 'D':
//         val = 13;
//         break;
//     case 'e':
//         val = 14;
//         break;
//     case 'E':
//         val = 14;
//         break;
//     case 'f':
//         val = 15;
//         break;
//     case 'F':
//         val = 15;
//         break;
//     default:
//         return false;
//     }
//     return true;
// }

// inline int parse_hex(char *cp)
// {
//     int ret = 0;
//     int tmp;
//     while (is_hex(*cp, tmp))
//     {
//         ret = (ret << 4) + tmp;
//         ++cp;
//     }
//     for (int i = 31; i >= 0; --i)
//     {
//         if ((ret >> i) & 1)
//             cout << 1;
//         else
//             cout << 0;
//     }
//     return ret;
// }

// int main()
// {
//     char *alpha_number = "78";
//     int bin_number = parse_hex(alpha_number);
//     cout << endl;
//     cout << bin_number << endl; // 十进制 305419896
// }

// 要点:
// 1. 直接量参数与内联结合使用, 为编译器性能的大幅提升开辟了更为广阔的空间.
// 2. 使用内联有时会适得其反, 尤其是滥用的情况下. 内联可能使得代码量变大, 而代码量增多后会较原先出现更多的缓存失败
// 和 换页问题.
// 3. 非精简方法的内联决策应根据样本执行的配置文件来制定, 不能主观臆断.
// 4. 对于那些调用频率高的方法, 如果其静态尺寸较大, 而动态尺寸较小, 可以考虑将其重写, 从而抽取其核心的动态特性,
// 并将动态组件内联.
// 5. 精简化与唯一化总是可以被内联.