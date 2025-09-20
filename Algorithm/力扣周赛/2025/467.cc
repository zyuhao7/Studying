#include <bits/stdc++.h>
using namespace std;
// day-2025-9-19
// 3683. 完成一个任务的最早时间 easy
// https://leetcode.cn/problems/number-of-stable-subsequences/description/
/*
    将开始时间和持续时间相加, 排序得到最早完成时间
*/

/*

class Solution
{
public:
    int earliestTime(vector<vector<int>> &tasks)
    {
        vector<int> v;
        for (int i = 0; i < tasks.size(); ++i)
            v.push_back(tasks[i][0] + tasks[i][1]);
        sort(v.begin(), v.end());
        return *v.begin();
    }
};

*/

// 3684. 至多 K 个不同元素的最大和 easy
// https://leetcode.cn/problems/maximize-sum-of-at-most-k-distinct-elements/description/
/*
    贪心, 先排序, 去重, 取前 k 个
*/

/*
class Solution
{
public:
    vector<int> maxKDistinct(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end(), greater<int>());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        vector<int> ans;
        for (int i = 0; i < min(k, (int)nums.size()); ++i)
            ans.push_back(nums[i]);
        return ans;
    }
};
*/

// 3685. 含上限元素的子序列和 middle
// https://leetcode.cn/problems/subsequence-sum-after-capping-elements/description/
/*
    dp 背包
    对每个 x 都做一次 O(nk) 的背包，整体为 O(n^2 * k)
*/

/*
class Solution
{
public:
    bool Up(vector<int> nums, int x, int k)
    {

        for (int i = 0; i < nums.size(); ++i)
            nums[i] = min(nums[i], x);

        return IsSubsequence(nums, k);
    }

    bool IsSubsequence(vector<int> &nums, int k)
    {
        // nums[i ~ j] 有没有和为 k
        int n = nums.size();
        vector<bool> dp(k + 1, false);
        dp[0] = true;
        for (auto num : nums)
        {
            for (int j = k; j >= num; j--)
                if (dp[j - num])
                {
                    dp[j] = true;
                    if (j == k)
                        return true;
                }
        }
        return false; // dp[k]
    }
    vector<bool> subsequenceSumAfterCapping(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<bool> ans(n, false);
        for (int i = 0; i < n; ++i)
            ans[i] = Up(nums, i + 1, k);
        return ans;
    }
};
*/

// 优化到 O(nk)
// f_dp 记录前缀 01 背包的状态
/*
class Solution
{
public:
    // f_dp: 前缀 01 背包的状态（长度为 K+1），x: 上限值，y: 超出上限的元素个数，K: 目标和
    bool check_cap_with_over(const vector<char> &f_dp, int x, int y, int K)
    {
        for (int cnt = 0; cnt <= y; ++cnt)
        {
            int det = K - x * cnt;
            if (det < 0)
                break;
            if (f_dp[det])
                return true;
        }
        return false;
    }

    vector<bool> subsequenceSumAfterCapping(vector<int> &nums, int K)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<char> f(K + 1, 0);
        f[0] = 1;

        vector<bool> ans;
        ans.reserve(n);

        for (int x = 1; x < (n > 0 ? nums[0] : 1); ++x)
        {
            ans.push_back(check_cap_with_over(f, x, n, K)); // 全部元素都 <= x
        }

        for (int i = 0; i < n; ++i)
        {
            int val = nums[i];
            if (val <= K)
            {
                for (int j = K; j >= val; --j)
                    if (f[j - val])
                        f[j] = 1;
            }
            for (int x = val; x < (i + 1 < n ? nums[i + 1] : n + 1); ++x)
            {
                ans.push_back(check_cap_with_over(f, x, n - 1 - i, K));
            }
        }

        return ans;
    }
};
*/

// 3686. 稳定子序列的数目 hard
// https://leetcode.cn/problems/number-of-stable-subsequences/description/
// class Solution
// {
// public:
//     int countStableSubsequences(vector<int> &nums)
//     {
//         int mod = 1e9 + 7;
//         int n = nums.size();
//         long long ans = 0;
//         long long f[6] = {0};
//         for (int i = 0; i < n; ++i)
//         {
//             long long g[6] = {0};
//             if (nums[i] & 1)
//             {
//                 g[1] = (f[0] + f[2] + f[4]) % mod; // 偶奇 结尾
//                 g[3] = (f[1] + f[5]) % mod;        // 奇奇 结尾
//                 g[5] = 1;
//             }
//             else
//             {
//                  g[0] = (f[1] + f[3] + f[5]) % mod;
//                  g[2] = (f[0] + f[4]) % mod;
//                  g[4] = 1;
//             }
//             for (int j = 0; j < 6; j++)
//                 ans = (ans + g[j]) % mod;
//             for (int j = 0; j < 6; j++)
//                 f[j] = (f[j] + g[j]) % mod;
//         }

//         return ans;
//     }
// };
