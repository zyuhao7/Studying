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

// day-2024-9-21
// 剑指 Offer II 003. 前 n 个数字二进制中 1 的个数
// class Solution
// {
// public:
//     vector<int> countBits(int n)
//     {
//         vector<int> res(n + 1);
//         for (int i = 1; i <= n; ++i)
//         {
//             res[i] = res[i >> 1] + i % 2;
//             res[i] = res[i & (i - 1)] + 1;
//         }
//         return res;
//     }
// };

// 剑指 Offer II 004. 只出现一次的数字
// 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

// 位运算
// 统计所有数字每位出现 1 的个数, 如果 1 出现的个数无法被三整除, 说明 只出现一次的数字在该位为 1, 否则是 0.
// 时间复杂度 为 O(N * logM) n 是 数组 nums 长度, M 是数组中元素的最大值.

// class Solution
// {
// public:
//     int singleNumber(vector<int> &nums)
//     {
//         int ans = 0;
//         for (int i = 0; i < 32; ++i)
//         {
//             int cnt = 0;
//             for (int n : nums)
//             {
//                 if (n >> i & 1)
//                     cnt++;
//             }
//             cnt %= 3;
//             ans |= cnt << i;
//         }
//         return ans;
//     }
// };

// day-2024-9-22
// 剑指 Offer II 005. 单词长度的最大乘积
// 给你一个字符串数组 words ，找出并返回 length(words[i]) * length(words[j]) 的最大值，并且这两个单词不含有公共字母。
// 如果不存在这样的两个单词，返回 0 。

// 思路: 统计每一个字符串各位字符是否存在, 放在一个数组, 按长度排序.(不用排序, 直接遍历就可)
// class Solution
// {
// public:
//     int maxProduct(vector<string> &words)
//     {
//         int n = words.size();
//         int mask[n];
//         memset(mask, 0, sizeof(mask));
//         for (int i = 0; i < words.size(); ++i)
//         {
//             for (auto c : words[i])
//             {
//                 mask[i] |= 1 << (c - 'a');
//             }
//         }
//         int ans = 0;
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 if ((mask[i] & mask[j]) == 0)
//                 {
//                     ans = max(ans, int(words[i].size() * words[j].size()));
//                 }
//             }
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 006. 排序数组中两个数字之和
// 法 1
// class Solution
// {
// public:
//     vector<int> twoSum(vector<int> &numbers, int target)
//     {
//         vector<int> res(2, 0);
//         int n = numbers.size();
//         int i = 0, j = n - 1;
//         while (i < j)
//         {
//             if (numbers[i] + numbers[j] == target)
//             {
//                 res[0] = i + 1;
//                 res[1] = j + 1;
//                 break;
//             }
//             else if (numbers[i] + numbers[j] < target)
//             {
//                 i++;
//             }
//             else
//                 j--;
//         }
//         return res;
//     }
// };
// 法 2
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& numbers, int target) {
//         for (int i = 0, n = numbers.size();; ++i) {
//             int x = target - numbers[i];
//             int j = lower_bound(numbers.begin() + i + 1, numbers.end(), x) - numbers.begin();
//             if (j < n && numbers[j] == x) {
//                 return {i + 1, j + 1};
//             }
//         }
//     }
// };