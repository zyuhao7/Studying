#include <bits/stdc++.h>
using namespace std;

// day-2026-01-01
// 3375. 使数组的值全部为 K 的最少操作次数  easy
// https://leetcode.cn/problems/minimum-operations-to-make-array-values-equal-to-k/description/

/*
    遍历数组, 统计大于k的不同元素个数
    如果存在小于k的元素, 则无法完成任务, 返回-1
    否则返回不同元素个数
*/

class Solution
{
public:
    int minOperations(vector<int> &nums, int k)
    {
        unordered_set<int> set;
        for (auto x : nums)
        {
            if (x < k)
                return -1;
            else if (x > k)
                set.insert(x);
        }
        return set.size();
    }
};

// 3376. 破解锁的最少时间 I mid
// https://leetcode.cn/problems/minimum-time-to-break-locks-i/description/
/*
    尝试所有排列组合, 对每种排列计算所需时间, 取最小值
*/
class Solution
{
public:
    int findMinimumTime(vector<int> &strength, int k)
    {
        int n = strength.size();
        int fac = 1;
        for (int i = 1; i <= n; ++i)
            fac *= i;

        auto gao = [&]()
        {
            long long X = 1, ret = 0;
            for (auto v : strength)
            {
                long long tmp = (v + X - 1) / X;
                ret += tmp;
                X += k;
            }
            return ret;
        };
        long long ans = 1e18;
        while (fac--)
        {
            ans = min(ans, gao());
            next_permutation(strength.begin(), strength.end());
        }
        return ans;
    }
};

//  3377. 使两个整数相等的数位操作 mid
// https://leetcode.cn/problems/digit-operations-to-make-two-integers-equal/description/
/*
    使用Dijkstra算法在状态空间中搜索从n到m的最小代价路径
    每个状态表示当前整数的值, 边表示允许的数位操作
*/

// 筛法预处理质数
#define MAXN ((int)1e4)
bool flag[MAXN + 3], inited = false;
void init()
{
    if (inited)
        return;
    inited = true;
    memset(flag, 0, sizeof flag);
    flag[0] = flag[1] = true;
    for (int i = 2; i <= MAXN; ++i)
    {
        if (!flag[i])
            for (int j = i * 2; j <= MAXN; j += i)
                flag[j] = true;
    }
}

class Solution
{
public:
    int minOperations(int n, int m)
    {
        init();
        if (!flag[n] || !flag[m])
            return -1;

        int lim = 1;
        for (; lim <= max(n, m); lim *= 10)
            ;

        long long dis[lim];
        memset(dis, -1, sizeof dis); // 距离 x 最少代价
        typedef pair<long long, long long> pll;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({n, n}); // {spend, target}

        // dijkstra
        while (!pq.empty())
        {
            pll p = pq.top();
            pq.pop();
            int x = p.second; // 11
            if (dis[x] >= 0)
                continue;
            dis[x] = p.first; // 11 21
            // 尝试从 x -> y
            auto gao = [&](int y)
            {
                if (dis[y] >= 0 || !flag[y] || y < lim / 10)
                    return;
                pq.push({dis[x] + y, y});
            };

            // 枚举操作的数位
            for (int t = 1; t < lim; t *= 10)
            {
                if (x / t % 10 < 9)
                    gao(x + t);
                if (x / t % 10 > 0)
                    gao(x - t);
            }
        }
        return dis[m];
    }
};