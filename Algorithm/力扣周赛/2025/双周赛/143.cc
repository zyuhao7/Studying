#include <bits/stdc++.h>
using namespace std;

// day-2026-01-03
// 3345. 最小可整除数位乘积 I easy
// https://leetcode.cn/problems/smallest-divisible-digit-product-i/description/
/*
    枚举从 n 开始的每个数, 计算其各位数字乘积
    当乘积能被 t 整除时, 返回该数
*/
class Solution
{
public:
    int smallestNumber(int n, int t)
    {
        auto prodOfdigits = [&](int n) -> int
        {
            int res = 1, t = 0;
            while (n)
            {
                t = n % 10;
                n /= 10;
                res *= t;
            }
            return res;
        };
        for (int i = n;; i++)
        {
            if (prodOfdigits(i) % t == 0)
                return i;
        }
        return -1;
    }
};

// 3346. 执行操作后元素的最高频率 I II  mid
// https://leetcode.cn/problems/maximum-frequency-of-an-element-after-performing-operations-i/description/
/*
    枚举每个可能的目标值 x
    计算区间 (x , x + k] 和 [x - k, x) 中的元素个数
    最终答案为 mp[x] + min(区间内元素个数, numOperations) 的最大值
*/
class Solution
{
public:
    int maxFrequency(vector<int> &nums, int k, int numOperations)
    {
        unordered_set<int> st;
        unordered_map<int, int> mp;
        for (auto x : nums)
        {
            st.insert(x);
            st.insert(x - k);
            mp[x]++;
        }
        sort(nums.begin(), nums.end());
        int ans = 0;
        for (auto x : st)
        {
            int tmp = 0;
            // 计算 (x, x + k] 有几个数
            tmp += upper_bound(nums.begin(), nums.end(), x + k) - upper_bound(nums.begin(), nums.end(), x);
            // 计算 [x - k, x) 有几个数
            tmp += lower_bound(nums.begin(), nums.end(), x) - lower_bound(nums.begin(), nums.end(), x - k);
            tmp = min(tmp, numOperations);
            ans = max(ans, mp[x] + tmp);
        }
        return ans;
    }
};