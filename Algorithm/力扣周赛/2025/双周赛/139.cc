#include <bits/stdc++.h>
using namespace std;

// day-2026-01-07
// 3285. 找到稳定山的下标 easy
// https://leetcode.cn/problems/find-indices-of-stable-mountains/
/*
    遍历数组 height
    若 height[i-1] > threshold, 则将 i 加入答案中
*/
class Solution
{
public:
    vector<int> stableMountains(vector<int> &height, int threshold)
    {
        vector<int> ans;
        for (int i = 1; i < height.size(); ++i)
        {
            if (height[i - 1] > threshold)
                ans.push_back(i);
        }
        return ans;
    }
};

// 3286. 穿越网格图的安全路径 mid
// https://leetcode.cn/problems/find-a-safe-walk-through-a-grid/description/

/*
    Dijkstra
    使用优先队列维护当前路径消耗的生命值最小的点
    对于每个点, 遍历其四个方向的邻居, 更新邻居的最小生命值消耗
    若到达终点时的生命值消耗小于给定的生命值, 则存在一条安全路径
*/
class Solution
{
public:
    typedef pair<int, pair<int, int>> pipii;
    bool findSafeWalk(vector<vector<int>> &grid, int health)
    {
        int n = grid.size(), m = grid[0].size();
        const int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(m, INF));
        priority_queue<pipii, vector<pipii>, greater<>> pq;

        dist[0][0] = grid[0][0];
        pq.push({dist[0][0], {0, 0}});
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (!pq.empty())
        {
            auto [cost, pos] = pq.top();
            pq.pop();
            auto [x, y] = pos;
            if (cost >= health)
                continue;
            if (x == n - 1 && y == m - 1)
                return true;

            for (auto &d : dir)
            {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;
                int nc = cost + grid[nx][ny];
                if (nc < dist[nx][ny])
                {
                    dist[nx][ny] = nc;
                    pq.push({nc, {nx, ny}});
                }
            }
        }
        return false;
    }
};