#include <iostream>
#include <vector>
#include <string>
using namespace std;
// day-2024-9-20
// 剑指 Offer II 001.整数除法
// 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。
// 模拟 + 快速幂

// class Solution
// {
// public:
//     int divide(int a, int b)
//     {
//         if (b == 1)
//             return a;
//         if (a == INT_MIN && b == -1)
//             return INT_MAX;
//         bool sign = (a > 0 && b > 0) || (a < 0 && b < 0);
//         a = a > 0 ? -a : a;
//         b = b > 0 ? -b : b;
//         int ans = 0;
//         while (a <= b)
//         {
//             int cnt = 1;
//             int x = b;
//             while (x >= (INT_MIN >> 1) && a <= (x << 1))
//             {
//                 x <<= 1;
//                 cnt <<= 1;
//             }
//             ans += cnt;
//             a -= x;
//         }
//         return sign ? ans : -ans;
//     }
// };

// 剑指 Offer II 002. 二进制加法
// 给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。
// 模拟

// class Solution
// {
// public:
//     string addBinary(string a, string b)
//     {
//         int len1 = a.size(), len2 = b.size();
//         string res;
//         int carry = 0;

//         for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; i--, j--)
//         {
//             int sum = carry;
//             if (i >= 0)
//                 sum += a[i] - '0';
//             if (j >= 0)
//                 sum += b[j] - '0';

//             res += (sum % 2) + '0';
//             carry = sum / 2;
//         }

//         reverse(res.begin(), res.end());

//         return res;
//     }
// };
