#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
// 程序员面试金典
// day-2025-8-1
// 01.01 判定字符是否唯一	数组	简单
// 法1 统计字符出现次数
// class Solution
// {
// public:
//     bool isUnique(string s)
//     {
//         char dict[26] = {0};
//         for (int i = 0; i < s.size(); ++i)
//             dict[s[i] - 'a']++;
//         for (int i = 0; i < s.size(); ++i)
//             if (dict[s[i] - 'a'] > 1)
//                 return false;
//         return true;
//     }
// };
// 法2: 位运算.
// class Solution
// {
// public:
//     bool isUnique(string s)
//     {
//         // 用一个 32 位整数来记录每个字符是否出现过.
//         int a = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             int x = s[i] - 'a';
//             if (a & (1 << x))
//                 return false;
//             a |= (1 << x);
//         }
//         return true;
//     }
// };

// 01.02 判定是否互为字符重排	数组,字符串	简单
// class Solution
// {
// public:
//     bool CheckPermutation(string s1, string s2)
//     {
//         if (s1.size() != s2.size())
//             return false;
//         char cnt[26] = {0};
//         for(auto& c : s1)
//             cnt[c - 'a']++;
//         for(auto&c : s2)
//             cnt[c - 'a']--;
//         for(int i = 0; i < 26; ++i)
//             if(cnt[i] != 0)
//                 return false;
//         return true;
//     }
// };

// 01.03	URL 化	字符串	简单
// class Solution
// {
// public:
//     string replaceSpaces(string s, int length)
//     {
//         string t = "";
//         for (int i = 0; i < length; ++i)
//         {
//             if (s[i] == ' ')
//                 t += "%20";
//             else
//                 t += s[i];
//         }
//         return t;
//     }
// };

// class Solution
// {
// public:
//     string replaceSpaces(string s, int length)
//     {
//         int j = s.size();
//         for (int i = length - 1; i >= 0; --i)
//         {
//             if (s[i] == ' ')
//             {
//                 s[--j] = '0';
//                 s[--j] = '2';
//                 s[--j] = '%';
//             }
//             else
//                 s[--j] = s[i];
//         }
//         return s.substr(j, s.size() - j);
//     }
// };

// 01.04	回文排列	哈希表,字符串	简单
// class Solution
// {
// public:
//     bool canPermutePalindrome(string s)
//     {
//         unordered_map<char, int> cnt;
//         for (auto &c : s)
//             cnt[c]++;
//         int odd = 0;
//         for (auto &[c, v] : cnt)
//             if (v % 2)
//                 odd++;
//         return odd <= 1;
//     }
// };

// 01.05	一次编辑	字符串,动态规划	中等
// class Solution
// {
// public:
//     bool oneEditAway(string s, string t)
//     {
//         if (t.size() > s.size())
//             swap(s, t);
//         if (s.size() - t.size() > 1)
//             return false;
//         for (int i = 0; i < t.size(); ++i)
//         {
//             if (s[i] == t[i])
//                 continue;
//             // 替换
//             if (s.size() == t.size())
//                 return s.substr(i + 1) == t.substr(i + 1);
//             // 删除/插入
//             if (s.size() > t.size())
//                 return s.substr(i + 1) == t.substr(i);
//         }
//         return true;
//     }
// };

// 01.06 字符串压缩 字符串 简单
// class Solution
// {
// public:
//     string compressString(string S)
//     {
//         string t = "";
//         for (int i = 0; i < S.size();)
//         {
//             int j = i;
//             while (j < S.size() && S[j] == S[i])
//                 j++;
//             t += S[i];
//             t += to_string(j - i);
//             i = j;
//         }
//         return t.size() < S.size() ? t : S;
//     }
// };

// 01.07	旋转矩阵	数组	中等
// class Solution
// {
// public:
//     void rotate(vector<vector<int>> &mat)
//     {
//         // 先上下翻转, 然后按次对角线对折.
//         int n = mat.size();
//         for (int i = 0; i < n / 2; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 swap(mat[i][j], mat[n - i - 1][j]); // 列不变, 行交换.
//             }
//         }
//         // 主对角线对折
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < n - i - 1; ++j)
//             {
//                 swap(mat[i][j], mat[n - j - 1][n - i - 1]);
//             }
//         }
//         // 次对角线对折.
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < i; ++j)
//             {
//                 swap(mat[i][j], mat[j][i]);
//             }
//         }
//     }
// };
