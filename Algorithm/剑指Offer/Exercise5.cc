#include <iostream>
#include <vector>
#include <string>
using namespace std;

// day-9-8
//  面试题 41: 和为 s 的两个数字 VS 和为 s 的连续正数序列
//  题目1 输入一个递增排序的数组和一个数字 s, 在数组中查找两个数, 使得他们的和正好是 s. 如果有多对, 输出任意一对就可.

// void FindNumWithSum(vector<int> &v, int sum)
// {
//     if (v.size() <= 2)
//         return;
//     int cur = 0;
//     int i = 0, j = v.size() - 1;
//     while (i < j)
//     {
//         cur = v[i] + v[j];
//         if (cur > sum)
//         {
//             j--;
//         }
//         else if (cur < sum)
//         {
//             i++;
//         }
//         else
//         {
//             cout << v[i] << " " << v[j] << endl;
//             return;
//         }
//     }
//     return;
// }
// int main()
// {
//     vector<int> v = {1, 2, 4, 7, 11, 15};
//     FindNumWithSum(v, 15);
//     return 0;
// }

// 题目2 输入一个正数 s, 打印出所有和为 s 的连续正数序列 (至少含有两个数)

// void PrintContinuousSequence(int l, int r)
// {
//     for (int i = l; i <= r; ++i)
//     {
//         cout << i << " ";
//     }
//     cout << endl;
// }

// void FindContinuousSequence(int sum)
// {
//     if (sum < 3)
//         return;
//     int l = 1, r = 2;
//     int m = (sum + 1) / 2;
//     int curSum = l + r;
//     while (l < m)
//     {
//         if (curSum == sum)
//             PrintContinuousSequence(l, r);

//         while (curSum > sum && l < m)
//         {
//             curSum -= l;
//             l++;
//             if (curSum == sum)
//                 PrintContinuousSequence(l, r);
//         }
//         r++;
//         curSum += r;
//     }
// }

// int main()
// {
//     FindContinuousSequence(15);
// }

// 面试题 42 翻转单词顺序 VS 左旋转字符串
// 1. 输入一个英文句子, 翻转句子中单词的顺序, 但单词字符的顺序不变, 表单符号和普通字母一样处理, 例如输入
// I am a student. 则输出 student. a am I
// string reverseWord(string s)
// {
//     int len = s.size() - 1;
//     int j = len;
//     string res;
//     for (int i = len; i >= 0; --i)
//     {
//         if (s[i] == ' ')
//         {
//             for (int k = i; k <= j; ++k)
//                 res += s[k];
//             j = i;
//         }
//         if (i == 0)
//             for (int k = i; k <= j; ++k)
//                 res += s[k];
//     }
//     return res;
// }

// string reverseMessage(string s)
// {
//     int len = s.size() - 1;
//     int j = len;
//     string res;
//     for (int i = len; i >= 0; --i)
//     {
//         if (s[i] != ' ')
//         {
//             j = i;
//             while (s[i] != ' ' && i >= 0)
//             {
//                 --i;
//                 if (i == -1)
//                     break;
//             }
//             res += s.substr(i + 1, j - i) + " ";
//         }
//     }
//     return res.substr(0, res.size() - 1);
// }
// int main()
// {
//     cout << "I am a student." << endl;
//     cout << reverseWord("I am a student.");
// }

// 题目 2 左旋转字符串.

// void LeftRotationStringhelper(string &s, int i, int j)
// {
//     while (i < j)
//     {
//         char t = s[i];
//         s[i] = s[j];
//         s[j] = t;
//         i++;
//         --j;
//     }
//     return;
// }
// void LeftRotationString(string &s, int k)
// {
//     LeftRotationStringhelper(s, 0, k - 1);        // bacdefg
//     LeftRotationStringhelper(s, k, s.size() - 1); // bagfedc
//     LeftRotationStringhelper(s, 0, s.size() - 1); // cdefgab
//     cout << s << endl;
//     return;
// }

// int main()
// {
//     string s = "abcdefg";
//     LeftRotationString(s, 2);
// }

// day-2024-9-9`
// 面试题 43 n个 骰子的点数
// 把 n 个骰子扔在地上, 所有朝上一面的和为 s,输入 n 求 s 的所有可能出现的值的概率.
// class Solution
// {
// public:
//     vector<double> statisticsProbability(int num)
//     {
//         vector<double> dp(6, 1.0 / 6.0);
//         for (int i = 2; i <= num; ++i)
//         {
//             vector<double> tmp(5 * i + 1);
//             for (int j = 0; j < dp.size(); ++j)
//             {
//                 for (int k = 0; k < 6; ++k)
//                 {
//                     tmp[j + k] += dp[j] / 6.0;
//                 }
//             }
//             dp = tmp;
//         }
//         return dp;
//     }
// };

// 面试题 44 扑克牌的顺子
// 从扑克牌中随机抽五张牌, 判断是不是一个顺子, 即 这五张牌是不是连续的. 2 ~ 10 为数字本身, A 为 1, J = 11, Q = 12, K = 13
// 大小王为任意的数.
// class Solution
// {
// public:
//     bool checkDynasty(vector<int> &places)
//     {
//         sort(places.begin(), places.end());
//         int zeroCnt = 0;
//         for (int i = 0; i < places.size(); ++i)
//         {
//             if (places[i] == 0)
//                 zeroCnt++;
//             else if (i > 0 && places[i] == places[i - 1])
//                 return false;
//         }
//         int gapCnt = 0;
//         for (int i = zeroCnt; i < places.size() - 1; ++i)
//         {
//             int diff = places[i + 1] - places[i];
//             if (diff == 0)
//                 return false;
//             gapCnt += diff - 1;
//         }
//         return gapCnt <= zeroCnt;
//     }
// };

// 面试题 45 圆圈中最后剩下的数字
// 0, 1 ... n - 1个数字排成一个圆圈, 从 0 开始每次从这个圆圈中删除第 m 个数字, 求最后剩下的数字.
// 链表 - 超出时间限制.
// class Solution
// {
// public:
//     int iceBreakingGame(int n, int m)
//     {
//         if (n < 1 || m < 1)
//             return -1;
//         list<int> lt;
//         for (int i = 0; i < n; ++i)
//             lt.push_back(i);

//         list<int>::iterator it = lt.begin();
//         while (lt.size() > 1)
//         {
//             for (int i = 1; i < m; ++i)
//             {
//                 it++;
//                 if (it == lt.end())
//                     it = lt.begin();
//             }
//             list<int>::iterator next = ++it;
//             if (next == lt.end())
//                 next = lt.begin();
//             --it;
//             lt.erase(it);
//             it = next;
//         }
//         return *it;
//     }
// };

// class Solution
// {
// public:
//     int iceBreakingGame(int n, int m)
//     {
//         if (n < 1 || m < 1)
//             return -1;
//         int x = 0;
//         // f [i] = (f[i - 1] + m ) % i.
//         for (int i = 2; i <= n; ++i)
//         {
//             x = (x + m) % i;
//         }
//         return x;
//     }
// };

// 面试题 46 求 1 + 2 + + n
// 构造函数求解
// class Temp
// {
// public:
//     Temp()
//     {
//         ++N;
//         Sum += N;
//     }
//     static void Reset()
//     {
//         N = 0;
//         Sum = 0;
//     }
//     static unsigned int GetSum()
//     {
//         return Sum;
//     }

// private:
//     static unsigned int N;
//     static unsigned int Sum;
// };
// unsigned int Temp::N = 0;
// unsigned int Temp::Sum = 0;

// unsigned int Sum_solution1(int n)
// {
//     Temp::Reset();
//     Temp *t = new Temp[n];
//     delete[] t;
//     t = nullptr;
//     return Temp::GetSum();
// }

// // 虚函数求解
// class A;
// A *Array[2];
// class A
// {
// public:
//     virtual unsigned int Sum(unsigned int n)
//     {
//         return 0;
//     }
// };

// class B : public A
// {
// public:
//     unsigned int Sum(unsigned int n)
//     {
//         return Array[!!n]->Sum(n - 1) + n;
//     }
// };

// int Sum_solution2(int n)
// {
//     A a;
//     B b;
//     Array[0] = &a;
//     Array[1] = &b;
//     int val = Array[1]->Sum(n);
//     return val;
// }

// // 模板类型求解
// template <unsigned int n>
// struct Sum_solution4
// {
//     enum Val
//     {
//         N = Sum_solution4<n - 1>::N + n
//     };
// };
// template <>
// struct Sum_solution4<1>
// {
//     enum Val
//     {
//         N = 1
//     };
// };

// int main()
// {

//     cout << Sum_solution1(5) << endl;
//     cout << Sum_solution2(5) << endl;
//     cout << Sum_solution4<5>().N << endl;
// }

// 面试题 47 不用加减乘除做加法
// 写一个函数, 求两个整数之和, 要求不得使用 + - * / 四则运算符号.

// int Add(int a, int b)
// {
//     //  3 + 5 11  101
//     int sum, carry;
//     do
//     {
//         sum = a ^ b;
//         carry = (a & b) << 1;
//         a = sum;
//         b = carry;
//     } while (b != 0);
//     return a;
// }

// int main()
// {
//     cout << Add(3, 5) << endl;
//     cout << Add(-1, 3) << endl;
//     cout << Add(-1, -3) << endl;

//     return 0;
// }

// 面试题 48 不能被继承的类
// 用 C++ 设计一个不能被继承的类
// 构造函数私有化？
// class A
// {
// public:
//     static A *GetInstance()
//     {
//         return new A();
//     }
//     static void DeleteInstance(A *pIns)
//     {
//         delete pIns;
//     }

// private:
//     A() {}
//     ~A() {}
// };

// class B : public A
// {
// };

// // 利用虚拟继承.
// template <typename T>
// class C
// {
//     friend T;

// private:
//     C() {}
//     ~C() {}
// };

// class D : virtual public C<D>
// {
// public:
//     D() {}
//     ~D() {}
// };

// class Try : public D
// {
// public:
//     Try() {}
//     ~Try() {}
// };
// int main()
// {
//     // B b;
//     D d;
//     Try t;
//     return 0;
// }

// class A
// {
// private:
//     int n1;
//     int n2;

// public:
//     A()
//         : n2(0),
//           n1(n2 + 2)
//     {
//     }
//     void Print()
//     {
//         cout << "n1: " << n1 << ", n2: " << n2 << endl;
//     }
// };

// int main(int argc, char *argv[])
// {
//     A a;
//     a.Print();
//     return 0;
// }

// day-2024-9-11
//  面试题 49 把字符串转成整数
// class Solution
// {
// public:
//     int myAtoi(string s)
//     {
//         int n = 0;
//         bool flag = true;
//         int i = 0;
//         while (s[i] == ' ')
//             i++;
//         if (s[i] == '+')
//             i++;
//         else if (s[i] == '-')
//         {
//             flag = false;
//             i++;
//         }
//         while (i < s.size() && isdigit(s[i]))
//         {
//             if (n > INT_MAX / 10 || (n == INT_MAX / 10 && (s[i] - '0' > 7)))
//                 return flag ? INT_MAX : INT_MIN;
//             n = n * 10 + (s[i] - '0');
//             i++;
//         }
//         return flag ? n : -n;
//     }
// };


// 面试题 50 树中两个节点的最低公共祖先