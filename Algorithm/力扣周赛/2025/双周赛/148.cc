#include <iostream>
#include <vector>
using namespace std;

// day-2025-11-01
// 3423. 循环数组中相邻元素的最大差值 easy
// https:leetcode.cn/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/description/
/*
    计算循环数组中相邻元素的差值, 包括首尾元素的差值
    遍历数组计算相邻元素的差值并更新最大差值
*/
class Solution
{
public:
    int maxAdjacentDistance(vector<int> &nums)
    {
        int n = nums.size();
        int ans = abs(nums[n - 1] - nums[0]);
        for (int i = 1; i < n; ++i)
        {
            ans = max(ans, abs(nums[i] - nums[i - 1]));
        }
        return ans;
    }
};
#include <algorithm>
// 3424. 将数组变相同的最小代价 mid
// https://leetcode.cn/problems/minimum-cost-to-make-arrays-identical/description/
/*
    计算将两个数组变为相同所需的最小代价
    计算两个数组元素差值的绝对值之和, 然后排序两个数组
    计算排序后两个数组元素差值的绝对值之和, 加上排序的代价k
    返回两种方式的最小值
*/
class Solution
{
public:
    long long minCost(vector<int> &arr, vector<int> &brr, long long k)
    {
        int n = arr.size();
        auto calc = [&]()
        {
            long long ret = 0;
            for (int i = 0; i < n; ++i)
                ret += abs(brr[i] - arr[i]);
            return ret;
        };
        long long ans1 = calc();
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        long long ans2 = calc() + k;
        return min(ans1, ans2);
    }
};

// 