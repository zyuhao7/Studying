#include <bits/stdc++.h>
using namespace std;

// day-2026-01-04
// 3330. 找到初始输入字符串 I easy
// https://leetcode.cn/problems/find-the-original-typed-string-i/description/

/*
    统计字符串中连续相同字符的组数即为答案
    互不相同的字母本身是一个方案, 初始值为1.
*/
class Solution
{
public:
    int possibleStringCount(string word)
    {
        int ans = 1;
        for (int i = 1; i < word.size(); ++i)
        {
            if (word[i] == word[i - 1])
                ans++;
        }
        return ans;
    }
};

// 3331. 修改后子树的大小 mid
// https://leetcode.cn/problems/find-subtree-sizes-after-changes/description/

/*
    构建新树, 新树中每个节点的父节点为其最近的同字母祖先节点
    计算新树中每个节点的子树大小即为答案
*/
class Solution
{
public:
    vector<int> findSubtreeSizes(vector<int> &parent, string s)
    {
        int n = parent.size();
        vector<int> e[n], E[n];
        for (int i = 1; i < n; ++i)
            e[parent[i]].push_back(i);

        vector<int> vec[26];
        auto dfs1 = [&](auto &&self, int sn, int fa) -> void
        {
            int c = s[sn] - 'a';
            if (sn > 0) // 不是根节点
            {
                if (vec[c].size() > 0) //
                    E[vec[c].back()].push_back(sn);
                else
                    E[fa].push_back(sn);
            }

            vec[c].push_back(sn);
            for (int fn : e[sn])
                self(self, fn, sn);
            vec[c].pop_back();
        };
        dfs1(dfs1, 0, -1);
        vector<int> ans(n);
        auto dfs2 = [&](auto &&self, int sn) -> int
        {
            ans[sn] = 1;
            for (auto fn : E[sn])
                ans[sn] += self(self, fn);
            return ans[sn];
        };
        dfs2(dfs2, 0);
        return ans;
    }
};

// 3332. 旅客可以得到的最多点数 mid
// https://leetcode.cn/problems/maximum-points-tourist-can-earn/description/

/*
    使用动态规划计算每一天在每个城市的最大点数
    最终答案为第 k 天在所有城市的最大点数
*/
class Solution
{
public:
    int maxScore(int n, int k, vector<vector<int>> &stayScore, vector<vector<int>> &travelScore)
    {
        // f[i][j] 表示游客第 i 天(1开始)结束时,位于城市 j 的最多点数.
        const long long INF = 1e18;
        long long f[k + 1][n];
        for (int i = 1; i <= k; ++i)
            for (int j = 0; j < n; ++j)
                f[i][j] = -INF;
        for (int j = 0; j < n; ++j)
            f[0][j] = 0;

        for (int i = 1; i <= k; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // 第 i 天留在城市 j
                f[i][j] = f[i - 1][j] + stayScore[i - 1][j];
                for (int t = 0; t < n; ++t)
                {
                    if (t != j)
                    {
                        // 从 t 到 j
                        f[i][j] = max(f[i][j], f[i - 1][t] + travelScore[t][j]);
                    }
                }
            }
        }
        long long ans = 0;
        for (int j = 0; j < n; ++j)
        {
            ans = max(ans, f[k][j]);
        }
        return ans;
    }
};