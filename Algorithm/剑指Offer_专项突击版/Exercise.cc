#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>
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

// day-2024-9-23
// 剑指 Offer II 007. 数组中和为 0 的三个数
// 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
// 同时还满足 nums[i] + nums[j] + nums[k] == 0. 请你返回所有和为 0 且不重复的三元组。
// class Solution
// {
// public:
//     vector<vector<int>> threeSum(vector<int> &nums)
//     {
//         sort(nums.begin(), nums.end());
//         vector<vector<int>> res;
//         for (int i = 0; i < nums.size() - 2; i++)
//         {
//             if (i > 0 && nums[i] == nums[i - 1])
//                 continue;
//             int target = -nums[i];
//             int l = i + 1, r = nums.size() - 1;
//             while (l < r)
//             {
//                 if (nums[l] + nums[r] == target)
//                 {
//                     res.push_back({nums[i], nums[l], nums[r]});
//                     while (l < r && nums[l + 1] == nums[l])
//                         l++;
//                     while (l < r && nums[r] == nums[r - 1])
//                         r--;
//                     l++;
//                     r--;
//                 }
//                 else if (nums[l] + nums[r] < target)
//                     l++;
//                 else
//                     r--;
//             }
//         }
//         return res;
//     }
// };

// 剑指 Offer II 008. 和大于等于 target 的最短子数组
// 找出该数组中满足其总和大于等于 target 的长度最小的子数组[ numsl, numsl + 1, ..., numsr - 1, numsr ] ，并返回其长度。
// 如果不存在符合条件的子数组，返回 0.

// class Solution
// {
// public:
//     int minSubArrayLen(int target, vector<int> &nums)
//     {
//         int l = 0, r = 0, sum = 0, res = INT_MAX;
//         while (r < nums.size())
//         {
//             sum += nums[r];
//             while (sum >= target)
//             {
//                 res = min(res, r - l + 1);
//                 sum -= nums[l];
//                 l++;
//             }
//             r++;
//         }
//         return res == INT_MAX ? 0 : res;
//     }
// };

// 剑指 Offer II 009. 乘积小于 K 的子数组
// 给你一个整数数组 nums 和一个整数 k ，请你返回子数组内所有元素的乘积严格小于 k 的连续子数组的数目。

// class Solution
// {
// public:
//     int numSubarrayProductLessThanK(vector<int> &nums, int k)
//     {
//         long long s = 1;
//         int ans = 0;
//         int n = nums.size();
//         for (int i = 0, j = 0; j < n; ++j)
//         {
//             s *= nums[j];
//             while (i <= j && s >= k)
//             {
//                 s /= nums[i++];
//             }
//             ans += j - i + 1;
//         }
//         return ans;
//     }
// };

// day-2024-9-24
// 剑指 Offer II 010. 和为 k 的子数组

// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
// 子数组是数组中元素的连续非空序列。

// 哈希表 + 前缀和
// class Solution {
// public:
//     int subarraySum(vector<int>& nums, int k) {
//         unordered_map<int,int> prefixSum;
//         prefixSum[0] = 1;
//         int ans = 0, sum = 0;
//         for(auto num : nums)
//         {
//             sum += num;
//             ans += prefixSum[sum - k]; // 前缀和 - k 出现次数 3 4 7    K=7.
//             prefixSum[sum]++;
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 011. 0 和 1 个数相同的子数组
// 给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度
// class Solution
// {
// public:
//     int findMaxLength(vector<int> &nums)
//     {
//         unordered_map<int, int> d;
//         d[0] = -1;
//         int ans = 0, s = 0;
//         // 前缀和, 求 j 到 i 的最长和为 0 的连续数组长度. 为什么 d[0] = -1 ? 因为 i = j = 0,时候需要就算 s[0] - s[-1],
//         // 进而相当于 s[1] - s[0] ? 那么 s[1] 由数组可知, 那么 s[0] 只能等于 -1.
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             s += nums[i] ? 1 : -1;
//             if (d.count(s))
//             {
//                 ans = max(ans, i - d[s]);
//             }
//             else
//                 d[s] = i;
//         }
//         return ans;
//     }
// };

// day-2024-9-25
// 剑指 Offer II 012. 左右两边子数组的和相等
// 数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

// 前缀和

// class Solution
// {
// public:
//     int pivotIndex(vector<int> &nums)
//     {
//         int sum_left = 0;
//         int sum_right = accumulate(nums.begin(), nums.end(), 0);
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             sum_right -= nums[i];
//             if (sum_left == sum_right)
//                 return i;
//             sum_left += nums[i];
//         }
//         return -1;
//     }
// };

// 剑指 Offer II 013. 二维子矩阵的和

// 二维前缀和
// class NumMatrix
// {
// public:
//     NumMatrix(vector<vector<int>> &mtx)
//     {
//         int m = mtx.size();
//         int n = mtx[0].size();
//         s.resize(m + 1, vector<int>(n + 1, 0));
//         for (int i = 1; i <= m; ++i)
//         {
//             for (int j = 1; j <= n; ++j)
//             {
//                 s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + mtx[i - 1][j - 1];
//             }
//         }
//     }

//     int sumRegion(int r1, int c1, int r2, int c2)
//     {
//         return s[r2 + 1][c2 + 1] - s[r2 + 1][c1] - s[r1][c2 + 1] + s[r1][c1];
//     }

// private:
//     vector<vector<int>> s;
// };

// day-2024-9-26
//  剑指 Offer II 014. 字符串中的变位词
//  给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的 排列。如果是，返回 true ；否则，返回 false 。
//  换句话说，s1 的排列之一是 s2 的 子串 。

// class Solution
// {
// public:
//     bool checkInclusion(string s1, string s2)
//     {
//         int hash[26] = {0};
//         for (char c : s1)
//         {
//             hash[c - 'a']++;
//         }

//         int hash2[26] = {0};
//         for (int i = 0; i < s1.size() && i < s2.size(); i++)
//         {
//             hash2[s2[i] - 'a']++;
//         }

//         if (memcmp(hash, hash2, sizeof(hash)) == 0)
//         {
//             return true;
//         }

//         for (int i = s1.size(); i < s2.size(); i++)
//         {
//             hash2[s2[i] - 'a']++;
//             hash2[s2[i - s1.size()] - 'a']--;

//             if (memcmp(hash, hash2, sizeof(hash)) == 0)
//             {
//                 for (int i = 0; i < 26; ++i)
//                 {
//                     cout << hash[i] << " " << hash2[i] << endl;
//                 }
//                 return true;
//             }
//         }

//         return false;
//     }
// };

// 剑指 Offer II 015. 字符串中的所有变位词
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

// class Solution
// {
// public:
//     vector<int> findAnagrams(string s, string p)
//     {
//         int hash[26], hash2[26];
//         vector<int> res;

//         for (auto c : p)
//         {
//             hash[c - 'a']++;
//         }
//         for (int i = 0; i < p.size() && i < s.size(); i++)
//         {
//             hash2[s[i] - 'a']++;
//         }
//         if (memcmp(hash, hash2, sizeof(hash)) == 0)
//             res.push_back(0);
//         for (int i = p.size(); i < s.size(); ++i)
//         {
//             hash2[s[i] - 'a']++;
//             hash2[s[i - p.size()] - 'a']--;
//             if (memcmp(hash, hash2, sizeof(hash)) == 0)
//                 res.push_back(i - p.size() + 1);
//         }
//         return res;
//     }
// };

// class Solution {
// public:
//     vector<int> findAnagrams(string s, string p) {
//         vector<int> res;
//         unordered_map<char,int> freq;
//         for(auto c : p)
//             freq[c]++;
//         int l = 0, r = 0, cnt = p.size();
//         while(r < s.size())
//         {
//             if(freq[s[r]] > 0)
//             {
//                 cnt--;
//             }
//             freq[s[r]] --;
//             r++;
//             if(cnt == 0)
//                 res.push_back(l);
//             if(r - l == p.size())
//             {
//                 if(freq[s[l]] >= 0)
//                     cnt++;
//                 freq[s[l]]++;
//                 l++;
//             }
//         }
//         return res;
//     }
// };