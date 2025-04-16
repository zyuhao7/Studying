// day-2025-4-16

// 3 无重复字符的最长子串
// class Solution {
//     public:
//         int lengthOfLongestSubstring(string s) {
//             unordered_map<char, int> mp;
//             int MaxLen = 0;
//             int l = 0, r = 0;
//             while(r < s.size())
//             {
//                 mp[s[r]]++;
//                 while(mp[s[r]] > 1)
//                 {
//                     mp[s[l]]--;
//                     l++;
//                 }

//                 MaxLen = max(MaxLen, r - l + 1);
//                 r++;
//             }
//             return MaxLen;
//         }
//     };

// 567 字符串的排列
// class Solution
// {
// public:
//     bool checkInclusion(string s1, string s2)
//     {
//         int hash1[26] = {0};
//         for (int i = 0; i < s1.size(); ++i)
//             hash1[s1[i] - 'a']++;
//         int hash2[26] = {0};
//         for (int i = 0; i < s1.size() && i < s2.size(); ++i)
//         {
//             hash2[s2[i] - 'a']++;
//         }

//         if (memcmp(hash1, hash2, sizeof(hash1)) == 0)
//             return true;
//         for (int i = s1.size(); i < s2.size(); ++i)
//         {
//             hash2[s2[i] - 'a']++;
//             hash2[s2[i - s1.size()] - 'a']--;
//             if (memcmp(hash1, hash2, sizeof(hash1)) == 0)
//                 return true;
//         }

//         return false;
//     }
// };

// 76 最小覆盖子串
// class Solution
// {
// public:
//     string minWindow(string s, string t)
//     {
//         unordered_map<char, int> cnt;
//         int len1 = s.size();
//         int len2 = t.size();
//         int minLen = len1 + 1, idx = -1, n = len2, l = 0, r = 0;
//         for (auto &c : t)
//             cnt[c]++;
//         while (r < len1)
//         {
//             cnt[s[r]]--;
//             if (cnt[s[r]] >= 0)
//                 n--;
//             while (n == 0)
//             {
//                 if (r - l + 1 < minLen)
//                 {
//                     minLen = r - l + 1;
//                     idx = l;
//                 }
//                 cnt[s[l]]++;
//                 if (cnt[s[l]] > 0)
//                     n++;
//                 l++;
//             }
//             r++;
//         }
//         if (idx == -1)
//             return "";
//         return s.substr(idx, minLen);
//     }
// };