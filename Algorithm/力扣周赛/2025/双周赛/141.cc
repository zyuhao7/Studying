#include <bits/stdc++.h>
using namespace std;

// day-2026-01-05
// 3314. 构造最小位运算数组 I easy
// https://leetcode.cn/problems/construct-the-minimum-bitwise-array-i/description/
/*
    枚举每个数 nums[i] 前比其小的数 j
    判断 j 和 j + 1 的按位或是否等于 nums[i]
    若相等, 则 j 为所求答案
    否则继续枚举下一个 j
*/
class Solution
{
public:
    vector<int> minBitwiseArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ans(n, -1);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < nums[i]; j++)
            {
                if ((j | (j + 1)) == nums[i])
                {
                    ans[i] = j;
                    break;
                }
            }
        }
        return ans;
    }
};

// 3315. 构造最小位运算数组 II mid
// https://leetcode.cn/problems/construct-the-minimum-bitwise-array-ii/description/

/*
    对于每个数 nums[i], 找出其二进制表示中从最低位开始的连续 1 的长度 p
    将该数的第 p - 1 位变为 0 即为所求答案
*/
class Solution
{
public:
    vector<int> minBitwiseArray(vector<int> &nums)
    {
        vector<int> ans;
        for (int x : nums)
        {
            if (x == 2)
                ans.push_back(-1);
            else
            {
                // 求从最低位开始的连续 1
                int p;
                for (p = 0; x >> p & 1; p++)
                    ;
                // 把连续 1 的最后一位变成 0
                ans.push_back(x ^ (1 << (p - 1)));
            }
        }
        return ans;
    }
};

// 3316. 从原字符串里进行删除操作的最多次数 mid
// https://leetcode.cn/problems/find-maximum-removals-from-source-string/description/
/*
    维护 f(i,j) 表示用 source 的前 i 位匹配 pattern 的前 j 位，最多能进行多少删除操作
    设 f[i][j] 表示 source 的前 i 个字符与 pattern 的前 j 个字符匹配时
    则状态转移方程为:
    f[i][j] = max(f[i-1][j] + (i 是否在 flag数组 ? 1:0),  // 跳过 source 的第 i 位
                  f[i-1][j-1] )                           // 用 source 的第 i 位 匹配 pattern 的第 j 位

*/
#define MAXN 3000
int f[MAXN + 10][MAXN + 10];
class Solution
{
public:
    int maxRemovals(string source, string pattern, vector<int> &targetIndices)
    {
        int n = source.size(), m = pattern.size();
        bool flag[n + 1];
        memset(flag, 0, sizeof flag);
        for (int x : targetIndices)
            flag[x + 1] = true;
        const int INF = 1e9;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                f[i][j] = -INF;
        f[0][0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                // 跳过 source的第 i 位
                f[i][j] = f[i - 1][j];
                if (flag[i])
                    f[i][j]++;
                // 用source 的第 i 位 匹配 pattern 的第 j 位
                if (j > 0 && source[i - 1] == pattern[j - 1])
                    f[i][j] = max(f[i][j], f[i - 1][j - 1]);
            }
            cout << endl;
        }
        return f[n][m];
    }
};