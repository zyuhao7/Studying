#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>
using namespace std;
// day-2024-10-3
// 剑指 Offer II 016. 不含重复字符的最长子字符串
// class Solution
// {
// public:
//     int lengthOfLongestSubstring(string s)
//     {
//         unordered_map<char, int> mp;

//         int l = 0, r = 0, maxLen = 0;
//         while (r < s.size())
//         {
//             if (!mp[s[r]])
//             {
//                 mp[s[r++]]++;
//                 maxLen = max(maxLen, r - l);
//             }
//             else
//             {
//                 mp[s[l++]]--;
//             }
//         }
//         return maxLen;
//     }
// };

// 剑指 Offer II 017. 含有所有字符的最短字符串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

// class Solution
// {
// public:
//     string minWindow(string s, string t)
//     {
//         int l = 0;
//         int len1 = s.size();
//         int len2 = t.size();
//         int pos = -1;
//         int n = len2;
//         int minLen = len1 + 1;
//         unordered_map<char, int> cnt;
//         for (auto c : t)
//             cnt[c]++;
//         for (int r = 0; r < len1; ++r)
//         {
//             cnt[s[r]]--;
//             if (cnt[s[r]] >= 0)
//                 n--;

//             while (n == 0)
//             {
//                 if (r - l + 1 < minLen)
//                 {
//                     pos = l;
//                     minLen = r - l + 1;
//                 }
//                 cnt[s[l]]++;
//                 if (cnt[s[l]] > 0)
//                 {
//                     n++;
//                 }
//                 l++;
//             }
//         }
//         if (pos == -1)
//             return "";
//         return s.substr(pos, minLen);
//     }
// };

// 剑指 Offer II 018. 有效的回文
// 给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false
// class Solution
// {
// public:
//     bool isPalindrome(string s)
//     {
//         int i = 0, j = s.size() - 1;
//         while (i < j)
//         {
//             while (i < j && !isalnum(s[i]))
//             {
//                 i++;
//             }
//             while (i < j && !isalnum(s[j]))
//             {
//                 j--;
//             }
//             if (tolower(s[i]) != tolower(s[j]))
//             {
//                 return false;
//             }
//             i++;
//             j--;
//         }
//         return true;
//     }
// };

int main()
{

    return 0;
}