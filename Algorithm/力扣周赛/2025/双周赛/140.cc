#include <bits/stdc++.h>
using namespace std;

// day-2026-01-06
// 3300. 替换为数位和以后的最小元素 easy
// https://leetcode.cn/problems/minimum-element-after-replacement-with-digit-sum/description/
/*
    对每个数求数位和, 取最小值
*/
class Solution
{
public:
    int sumOfdigits(int n)
    {
        int sum = 0;
        while (n)
        {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }
    int minElement(vector<int> &nums)
    {
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i)
            ans = min(ans, sumOfdigits(nums[i]));
        return ans;
    }
};

// 3301. 高度互不相同的最大塔高和 mid
// https://leetcode.cn/problems/maximize-the-total-height-of-unique-towers/description/
/*
    贪心 + 哈希表
    先将数组降序排序
    然后从大到小遍历每个数 mh[i]
    维护一个变量 t, 表示当前可选的最大高度
    对于每个 mh[i], 令 t = min(t, mh[i])
    然后不断将 t 减小, 直到 t 不在哈希表中出现过为止
    若 t 减小到 0 则无法构造出合法的高度, 返回 -1
    否则将 t 插入哈希表中, 并将其加入答案中
*/
class Solution
{
public:
    long long maximumTotalSum(vector<int> &mh)
    {
        long long ans = 0;
        int n = mh.size();
        sort(mh.begin(), mh.end(), greater<int>());
        unordered_set<int> st;
        int t = mh[0];
        for (int i = 0; i < n; ++i)
        {
            t = min(t, mh[i]);
            while (st.count(t))
                t--;
            if (t == 0)
                return -1;
            st.insert(t);
            ans += t;
        }
        return ans;
    }
};
/*
    优化版本:
    贪心 + 排序
    先将数组降序排序
    然后从大到小遍历每个数 mh[i]
    维护一个变量 prev, 表示上一个选择的高度
    对于每个 mh[i], 令 cur = min(mh[i], prev - 1)
    若 cur 减小到 0 则无法构造出合法的高度, 返回 -1
*/
class Solution
{
public:
    long long maximumTotalSum(vector<int> &mh)
    {
        long long ans = 0;
        int n = mh.size();
        sort(mh.begin(), mh.end(), greater<int>());
        int prev = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            int cur = min(mh[i], prev - 1);
            if (cur <= 0)
                return -1;
            ans += cur;
            prev = cur;
        }
        return ans;
    }
};
