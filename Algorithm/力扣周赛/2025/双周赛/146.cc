#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

// day-2025-12-28
//  3392. 统计符合条件长度为 3 的子数组数目 easy
//  https://leetcode.cn/problems/count-subarrays-of-length-three-with-a-condition/description/
/*
    遍历数组, 对于每个长度为3的子数组, 判断是否满足条件
    如果满足条件则计数器加1
*/

// class Solution
// {
// public:
//     int countSubarrays(vector<int> &nums)
//     {
//         int cnt = 0;
//         for (int i = 0; i < nums.size() - 2; ++i)
//         {
//             if ((nums[i] + nums[i + 2]) * 2 == nums[i + 1])
//                 cnt++;
//         }
//         return cnt;
//     }
// };

// 3393. 统计异或值为给定值的路径数目 middle
// https://leetcode.cn/problems/count-paths-with-the-given-xor-value/description/
/*
    使用深度优先搜索(DFS)遍历网格的所有路径, 并在每条路径上计算异或值
    使用记忆化搜索来存储中间结果以避免重复计算
*/

class Solution
{
public:
    int countPathsWithXorValue(vector<vector<int>> &grid, int k)
    {
        int mod = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(16, -1)));

        auto dfs = [&](auto &&dfs, int i, int j, int x) -> int
        {
            if (i >= m || j >= n)
                return 0;
            x ^= grid[i][j];
            if (i == m - 1 && j == n - 1)
                return x == k ? 1 : 0;
            if (memo[i][j][x] != -1)
                return memo[i][j][x];
            int paths = (dfs(dfs, i + 1, j, x) + dfs(dfs, i, j + 1, x)) % mod;
            memo[i][j][x] = paths;
            return paths;
        };
        return dfs(dfs, 0, 0, 0);
    }
};

// 3394. 判断网格图能否被切割成块 middle
// https://leetcode.cn/problems/check-if-grid-can-be-cut-into-sections/description/
/*
    将每个矩形的横坐标和纵坐标分别存储在两个数组中
    对这两个数组进行排序, 然后检查是否存在可以将网格图切割成至少三块的切割线
*/
class Solution
{
public:
    typedef pair<int, int> pii;
    bool canCut(vector<pii> &intervels)
    {
        // 按照可分割的段的数量判断
        int ret = 0, R = -1e9;
        for (int i = 0; i < intervels.size(); ++i)
        {
            int l = intervels[i].first;
            int r = intervels[i].second;
            if (l >= R)
                ret++;
            R = max(R, r);
        }
        return ret >= 3;
    }

    bool checkValidCuts(int n, vector<vector<int>> &rectangles)
    {
        vector<pii> intervels1;
        vector<pii> intervels2;
        for (int i = 0; i < rectangles.size(); ++i)
        {
            intervels1.push_back({rectangles[i][0], rectangles[i][2]});
            intervels2.push_back({rectangles[i][1], rectangles[i][3]});
        }
        sort(intervels1.begin(), intervels1.end());
        sort(intervels2.begin(), intervels2.end());
        if (canCut(intervels1) || canCut(intervels2))
            return true;
        return false;
    }
};