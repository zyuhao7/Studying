#include <iostream>
#include <string>
#include <set>
using namespace std;
/*
     本章重点介绍 6 个典型的字符串问题分别为:
     1. 字符串的旋转.
     2. 字符串的包含.
     3. 字符串的全排列.
     4. 字符串转换成整数. (atoi)
     5. 回文串判断
     6. 最长回文串
*/
// 1.1  字符串的旋转
/*  题目描述:
 * 给定一个字符串, 要求将前面字符串的若干个字符移到字符串的尾部. 例如, 将字符串 "abcdf" 的前三个字符 'a', 'b', 'c' 移动到
 * 字符串的尾部, 那么原字符串将变成 "defabc".
 */
// 做过此类题, 根据记忆写的一个巧妙方法 .。. 不行了, 今天 2024-7-7-23:01, 休息休息,不对, 我还得去看八股，等会 沙特杯 T1 打 Tes
// 决赛, 明天开班!!  加油~ 今天算是正式开始暑假逆袭计划!!! 给我冲! 加油!!!一定行!! 本书题解明天补了~

// void Reverse(string& s, int begin, int end)
// {
//     for(int i=begin, j = end; i < j ;++i, --j)
//     {
//         char t = s[i];
//         s[i] = s[j];
//         s[j] = t;
//     }
// }

// string f(string& s, int n)
// {
//     int size = s.size();
//     Reverse(s, 0, size - n - 1);
//     Reverse(s,n, size - 1);
//     Reverse(s, 0, size - 1);

//     return s;
// }

// int main()
// {
//     int n;
//     string s;

//     cin>>s>>n;

//     f(s,n);

//     cout<<s<<endl;
//     return 0;
// }

// ===============================================================================================================================================================================
// 书解: 1. 蛮力移位
//  将字符一个一个移到字符串的尾部.
// void LeftShiftOne(char *s, int n)
// {
//     // 保存第一个字符.
//     char t = s[0];
//     for (int i = 1; i < n; ++i)
//     {
//         s[i - 1] = s[i];
//     }
//     s[n - 1] = t;
// }

// 然后调用 m 次 LeftShiftOne 函数, 使得字符串开头的 m 个字符移到字符串的尾部.
// void LeftRotateString(char *s, int n, int m)
// {
//     while (m--)
//     {
//         LeftShiftOne(s, n);
//     }
// }

// 时间复杂度 O(m * n) 空间复杂度 O(1)

// ===============================================================================================================================================================================

// 解法 2. 三步反转
// 可以将字符串分割为两个部分, 然后将这两个部分的字符串分别反转, 最后再对整体反转.
// 1. 将原字符串分为 X 和 Y 两个部分, 其中 X 为 "abc", Y 为 "def".
// 2. 将 X 的所有字符串反转, 即相当于 翻转 "abc" 得到 "cba", 再将 Y 的所有字符也反转, 即 "def" --> "fed".
// 3. 将整体反转.  cbafed  --> defabc.
// void ReverseString(char *s, int from, int to)
// {
//     while (from < to)
//     {
//         char t = s[from];
//         s[from++] = s[to];
//         s[to--] = t;
//     }
// }

// void LeftRotateString(char *s, int n, int m)
// {
//     m %= n;
//     ReverseString(s, 0, m - 1);
//     ReverseString(s, m, n - 1);
//     ReverseString(s, 0, n - 1);
// }

// ===============================================================================================================================================================================

// day-2024-7-21
// 字符串包含
// 给定一长字符串 a 和 一短字符串 b, 如何快速判断 b中的所有字符 是否在 a 中. bool StringContain(string& a, string& b);
// 自解:
// bool StringContain(string &a, string &b)
// {
//      set<char> S;
//      for (int i = 0; i < a.size(); ++i)
//           S.insert(a[i]);
//      for (int j = 0; j < b.size(); ++j)
//           if (!S.count(b[j]))
//                return false;
//      return true;
// }

// 书解:
// 解法一: 暴力轮询.
// 解法二: 排序后轮询.
// 解法三: 素数相乘(不可行).
// 解法四: 位运算法.
// bool StringContain(string &a, string &b)
// {
//      int hash = 0;
//      for (int i = 0; i < a.size(); ++i)
//      {
//           hash |= (1 << (a[i] - 'A'));
//      }
//      for (int j = 0; j < b.size(); ++j)
//      {
//           if ((hash & (1 << (b[j] - 'A'))) == 0)
//                return false;
//      }
//      return true;
// }

// int main()
// {
//      string a = "ABCD", b = "AA";
//      cout << StringContain(a, b);
// }

// 字符串的全排列
// 输入一个字符串, 打印出该字符串中字符的所有排列. 例如: 输入 "abc", 则打印 "abc", "acb", "bac", "bca", "cab", "cba".
// 自解:
// void FullPermutation(string a, int idx)
// {
//      int s = a.size() - 1;
//      if (idx == s - 1)
//      {
//           for (int i = 0; i <= s; ++i)
//           {
//                cout << a[i] << " ";
//           }
//           cout << endl;
//           return;
//      }

//      for (int i = idx; i < s; ++i)
//      {
//           swap(a[i], a[idx]);
//           FullPermutation(a, i + 1);
//           swap(a[i], a[idx]);
//      }
// }

// 书解:
// 解法: 递归
// void CalcAllPermutation(string s, int i, int j)
// {
//      if (j <= 1) // 有点问题, 如果 a = "ab", 输出err.
//           return;

//      if (i == j)
//      {
//           for (int k = 0; k <= j; ++k)
//           {
//                cout << s[k];
//           }
//           cout << endl;
//      }
//      else
//      {
//           for (int k = i; k <= j; ++k)
//           {
//                swap(s[k], s[i]);
//                CalcAllPermutation(s, i + 1, j);
//                swap(s[k], s[i]);
//           }
//      }
// }

// int main()
// {
//      string a = "abc";
//      CalcAllPermutation(a, 0, 2);
// }

// 字符的所有组合. 如果输出 "abc", 则 "a", "b", "c", "ab", "ac", "bc" "abc"

// void CharAllCombinationHelper(const std::string &s, std::string current, int idx)
// {
//      if (idx == s.length())
//      {
//           if (!current.empty())
//           {
//                std::cout << current << std::endl;
//           }
//           return;
//      }

//      // 不包含当前字符.
//      CharAllCombinationHelper(s, current, idx + 1);
//      // 包含当前字符.
//      CharAllCombinationHelper(s, current + s[idx], idx + 1);
// }

// void CharAllCombination(const std::string &s, int idx = 0)
// {
//      CharAllCombinationHelper(s, "", idx);
// }
// int main()
// {
//      CharAllCombination("abc");
// }
// ===============================================================================================================================================================================

// ===============================================================================================================================================================================

// ===============================================================================================================================================================================
