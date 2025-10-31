#include <bits/stdc++.h>
using namespace std;

// day-2025-9-20
// 3674. 数组元素相等的最小操作次数 easy
// https://leetcode.cn/problems/minimum-operations-to-equalize-array/description/

/*
    只要数组中有不相等的元素, 就可以通过一次操作让所有元素相等
    否则不需要操作
*/

/*
    class Solution
    {
    public:
        int minOperations(vector<int> &nums)
        {
            int n = nums.size();
            for (int i = 1; i < n; ++i)
                if (nums[i] != nums[0])
                    return 1;
            return 0;
        }
    };
*/
// 3675. 转换字符串的最小操作次数 middle
// https://leetcode.cn/problems/minimum-operations-to-transform-string/description/
/*
    贪心, 先排序, 然后计算相邻字符的差值
    但是, 也可以直接计算每个字符到 'a' 的差值
*/

/*
class Solution
{
public:
    int minOperations(string s)
    {
        int cnt = 0;
        sort(s.begin(), s.end());
        for (int i = 0; i < s.size() - 1; ++i)
        {
            if (s[i] == 'a')
                continue;
            if (s[i] != s[i + 1])
            {
                cnt += s[i + 1] - s[i];
            }
        }
        if (s.back() != 'a')
            cnt += 'z' - s.back() + 1;
        return cnt;
    }
};

class Solution
{
public:
    int minOperations(string s)
    {
        int cnt = 0;
        for (char c : s)
        {
            if (c != 'a')
            {
                cnt = max(cnt, 26 - (c - 'a'));
            }
        }
        return cnt;
    }
};

*/

// 3676. 碗子数组的数目 middle
// https://leetcode.cn/problems/count-bowl-subarrays/description/
/*
    单调栈
    统计每个元素左边和右边是否有比它大的元素
*/

/*
class Solution
{
public:
    long long bowlSubarrays(vector<int> &nums)
    {
        int n = nums.size(), l[n], r[n];
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        for (int i = 0, mx = 0; i < n; ++i)
        {
            if (nums[i] < mx)
                l[i] = 1;
            mx = max(mx, nums[i]);
        }
        for (int i = n - 1, mx = 0; i >= 0; --i)
        {
            if (nums[i] < mx)
                r[i] = 1;
            mx = max(mx, nums[i]);
        }
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (l[i] && r[i])
                res++;
        }
        return res;
    }
};

*/

// 3677. 统计二进制回文数字的数目 hard
// 较难数位dp, 2200 往上暂不考虑.