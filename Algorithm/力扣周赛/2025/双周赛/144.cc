#include <bits/stdc++.h>
using namespace std;

// day-2026-01-02
// 3360. 移除石头游戏 easy
// https://leetcode.cn/problems/stone-removal-game/description/
/*
    模拟游戏过程, 计算每次能移除的石头数
    当剩余石头数小于等于10时, 游戏结束
    判断最后一次能移除石头的玩家是谁
*/
class Solution
{
public:
    bool canAliceWin(int n)
    {
        int t = 10;
        while (n >= t)
        {
            n -= t;
            t--;
        }
        return t % 2 == 1;
    }
};

// 3361. 两个字符串的切换距离 mid
// https://leetcode.cn/problems/shift-distance-between-two-strings/description/

/*
    对每个位置分别计算从 s[i] 变为 t[i] 的最小代价
    累加所有位置的最小代价即为答案
*/
class Solution
{
public:
    long long shiftDistance(string s, string t, vector<int> &nextCost, vector<int> &previousCost)
    {
        int n = s.size();
        long long ans = 0ll;
        for (int i = 0; i < n; ++i)
        {
            char c = s[i];
            if (t[i] == c)
                continue;
            long long sum1 = 0, sum2 = 0;
            // 从 nextCost中计算代价
            while (t[i] != c)
            {
                sum1 += nextCost[c - 'a'];
                if (c == 'z')
                    c = 'a';
                else
                    c++;
            }

            // 从 previousCost 计算代价
            c = s[i];
            while (t[i] != c)
            {
                sum2 += previousCost[c - 'a'];
                if (c == 'a')
                    c = 'z';
                else
                    c--;
            }
            ans += (long long)min(sum1, sum2);
        }

        return ans;
    }
};

//  3362. 零数组变换 III mid
// https://leetcode.cn/problems/zero-array-transformation-iii/description/
/*
    使用贪心+优先队列维护当前可选区间的右端点
    遍历每个元素, 维护当前覆盖数, 如果覆盖数小于 nums[i], 则从优先队列中选择右端点最大的区间进行覆盖
    直到覆盖数满足要求或者无法满足要求为止
*/
class Solution
{
public:
    int maxRemoval(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size(), q = queries.size();
        // 将所有区间按左端点从小到大排序, 方便之后用单调指针维护.
        sort(queries.begin(), queries.end());
        // now: 当前元素的覆盖数
        // ans: 最少要选几个区间
        int now = 0, ans = 0;
        // pq: 优先队列(大根堆), 记录了所有左端点小于等于当前下标的, 且还未选择的区间的右端点
        // 这样, 如果堆顶元素大于等于当前下标,那么他就能覆盖当前元素且右端点尽量大的区间
        priority_queue<int> pq;
        // f: 差分数组, f[i] 表示有几个区间在下标 i 结束
        int f[n + 1];
        memset(f, 0, sizeof f);
        // i : 从左到右枚举每个元素， 检查覆盖数
        // j : 单调指针, 指向左端点大于当前下标的下一个区间
        for (int i = 0, j = 0; i < n; ++i)
        {
            now -= f[i];
            while (j < q && queries[j][0] <= i)
                pq.push(queries[j][1]), j++;
            while (now < nums[i] && !pq.empty())
            {
                int t = pq.top();
                pq.pop();
                if (t >= i)
                {
                    now++;
                    ans++;
                    f[t + 1] += 1;
                }
            }
            if (now < nums[i])
                return -1;
        }
        return q - ans;
    }
};

// 3363. 最多可收集的水果数目 hard
// https://leetcode.cn/problems/find-the-maximum-number-of-fruits-collected/description/
/*
    使用动态规划计算从左上和右下两个方向收集水果的最大值
    最终答案为两部分之和加上对角线的部分
*/
class Solution
{
public:
    typedef long long ll;
    int maxCollectedFruits(vector<vector<int>> &fruits)
    {
        int n = fruits.size();

        const long long INF = 1e18;
        long long f[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j] = -INF;

        // 先计算右上区域
        f[0][n - 1] = fruits[0][n - 1];
        for (int i = 1; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                f[i][j] = max(f[i - 1][j - 1], f[i - 1][j]) + fruits[i][j];
                if (j + 1 < n)
                    f[i][j] = max(f[i][j], f[i - 1][j + 1] + fruits[i][j]);
            }
        }
        // 计算左下区域
        f[n - 1][0] = fruits[n - 1][0];
        for (int j = 1; j < n; ++j)
        {
            for (int i = j + 1; i < n; ++i)
            {
                f[i][j] = max(f[i - 1][j - 1], f[i][j - 1]) + fruits[i][j];
                if (i + 1 < n)
                    f[i][j] = max(f[i][j], f[i + 1][j - 1] + fruits[i][j]);
            }
        }
        long long ans = f[n - 1][n - 2] + f[n - 2][n - 1];
        for (int i = 0; i < n; ++i)
            ans += fruits[i][i];
        return ans;
    }
};