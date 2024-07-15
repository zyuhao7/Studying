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

// 未完待续···