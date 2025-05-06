#include <iostream>
#include <cstring>
#include <string>

using namespace std;
// 字符串
// 字符串比较.
// LeetCode  242. 有效的字母异位词
// 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词 若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词.
#if 1
bool isAnagram(string s, string t)
{
    if (s.size() != t.size())
        return false;
    int cnt[27] = {0};
    // 也可以合并.
    for (int i = 0; i < s.size(); ++i)
    {
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    // for (int i = 0; i < t.size(); ++i)
    //
    for (int i = 0; i < 26; ++i)
    {
        if (cnt[i] != 0)
            return false;
    }
    return true;
}

// LeetCode 205  同构字符串
// 判断两个字符串是否同构。每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序 ****(不改变顺序).*******
// 同构的定义是，可以通过把一个字符串的某些相同的字符转换成另一些相同的字符，使得两个字符串相同，且两种不同的字符不能够被转换成同一种字符。

bool isIsomorphic(string s, string t)
{
    unordered_map<char, char> s2t;
    unordered_map<char, char> t2s;

    for (int i = 0; i < s.size(); ++i)
    {
        // egg edg
        char x = s[i], y = t[i];
        if ((s2t.count(x) && s2t[x] != y) || (t2s.count(y) && t2s[y] != x))
            return false;
        s2t[x] = y;
        t2s[y] = x;
    }
    return true;
}

// 647. 回文子串
// 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
// 回文字符串 是正着读和倒过来读一样的字符串。
// 子字符串 是字符串中的由连续字符组成的一个序列。
int extendSubstrings(string s, int l, int r)
{
    int count = 0;
    while (l >= 0 && r < s.size() && s[l] == s[r])
    {
        --l;
        ++r;
        ++count;
    }
    return count;
}

int countSubstrings(string s)
{
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        cnt += extendSubstrings(s, i, i);     // odd
        cnt += extendSubstrings(s, i, i + 1); // even
    }
    return cnt;
}
#endif

// day-2025-4-22
// 5. 最长回文子串
// 中心扩展法
class Solution
{
public:
    pair<int, int> expandAroundCenter(string s, int l, int r)
    {
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }
        return {l + 1, r - 1};
    }
    string longestPalindrome(string s)
    {
        int st = 0, ed = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            auto [l1, r1] = expandAroundCenter(s, i, i);
            auto [l2, r2] = expandAroundCenter(s, i, i + 1);
            if (r1 - l1 > ed - st)
            {
                st = l1;
                ed = r1;
            }

            if (r2 - l2 > ed - st)
            {
                st = l2;
                ed = r2;
            }
        }
        return s.substr(st, ed - st + 1);
    }
};

// day-2025-5-2
//  20. 有效的括号
class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        if (s.size() % 2)
            return false;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                st.push(s[i]);
            else if (s[i] == ')')
            {
                if (!st.empty() && st.top() == '(')
                    st.pop();
                else
                    return false;
            }
            else if (s[i] == ']')
            {
                if (!st.empty() && st.top() == '[')
                    st.pop();
                else
                    return false;
            }
            else if (s[i] == '}')
            {
                if (!st.empty() && st.top() == '{')
                    st.pop();
                else
                    return false;
            }
        }
        return st.empty();
    }
};

// 151. 翻转字符串里的单词
class Solution
{
public:
    string reverseWords(string s)
    {
        stringstream ss(s);
        string word, ans = "";
        vector<string> words;
        while (ss >> word)
        {
            words.push_back(word);
        }
        reverse(words.begin(), words.end());
        for (const string &w : words)
        {
            ans += w + " ";
        }
        if (!ans.empty())
            ans.pop_back();
        return ans;
    }
};

// 125  验证回文串
class Solution
{
public:
    bool isPalindrome(string s)
    {
        int i = 0, j = s.size() - 1;
        while (i < j)
        {
            while (i < j && !isalnum(s[i]))
            {
                i++;
            }
            while (i < j && !isalnum(s[j]))
            {
                j--;
            }
            if (tolower(s[i]) != tolower(s[j]))
            {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};

// day-2025-5-6
// 678. 有效的括号字符串
// class Solution
// {
// public:
//     bool checkValidString(string s)
//     {
//         int l = 0, m = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             if (s[i] == '(')
//                 l++;
//             else if (s[i] == ')')
//                 l--;
//             else
//                 m++;
//             if (l < 0)
//             {
//                 l++;
//                 m--;
//             }
//             if (m < 0)
//                 return false;
//         }
//         int r = 0;
//         m = 0;
//         for (int i = s.size() - 1; i >= 0; --i)
//         {
//             if (s[i] == ')')
//                 r++;
//             else if (s[i] == '(')
//                 r--;
//             else
//                 m++;
//             if (r < 0)
//             {
//                 r++;
//                 m--;
//             }
//             if (m < 0)
//                 return false;
//         }
//         return true;
//     }
// };

// 67. 二进制求和
// class Solution
// {
// public:
//     string addBinary(string a, string b)
//     {

//         string res;
//         int len1 = a.size(), len2 = b.size(), carry = 0, sum = 0;
//         for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; --i, --j)
//         {
//             sum = 0;
//             if (i >= 0)
//                 sum += a[i] - '0';
//             if (j >= 0)
//                 sum += b[j] - '0';
//             if (carry)
//                 sum += carry;
//             res.push_back((sum % 2) + '0');
//             carry = sum / 2;
//         }
//         reverse(res.begin(), res.end());
//         return res;
//     }
// };

// 28.  找出字符串中第一个匹配项的下标
// class Solution
// {
// public:
//     int strStr(string haystack, string needle)
//     {
//         int m = haystack.size();
//         int n = needle.size();
//         for (int i = 0; i <= m - n; ++i)
//         {
//             for (int j = i; j < n + i; ++j)
//             {
//                 if (haystack[j] != needle[j - i])
//                     break;
//                 if (j == n + i - 1)
//                     return i;
//             }
//         }
//         return -1;
//     }
// };

// 392. 判断子序列
// class Solution
// {
// public:
//     bool isSubsequence(string s, string t)
//     {
//         if (s.empty())
//             return true;
//         int i = 0;
//         for (auto c : t)
//             if (c == s[i] && ++i == s.length())
//                 return true;
//         return false;
//     }
// };

// 647  回文子串
// class Solution
// {
// public:
//     int countSubstrings(string s)
//     {
//         int n = s.size();
//         int res = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             res += extendSubstring(s, i, i);
//             res += extendSubstring(s, i, i + 1);
//         }
//         return res;
//     }
//     int extendSubstring(string s, int l, int r)
//     {
//         int cnt = 0;
//         while (l >= 0 && r < s.size() && s[l] == s[r])
//         {
//             cnt++;
//             l--;
//             r++;
//         }
//         return cnt;
//     }
// };