#include <iostream>
#include <vector>
using namespace std;

// day-2025-2-18
// 509   斐波那契数
// class Solution
// {
// public:
//     int fib(int n)
//     {
//         if (n == 0)
//             return 0;
//         vector<int> dp(n + 1);
//         dp[0] = 0;
//         dp[1] = 1;
//         for (int i = 2; i <= n; ++i)
//             dp[i] = dp[i - 1] + dp[i - 2];
//         return dp[n];
//     }
// };

// 70 爬楼梯
// class Solution {
//     public:
//         int climbStairs(int n) {
//             vector<int> dp(n + 1);
//             dp[0] = 1;
//             dp[1] = 1;
//             for(int i = 2; i <=n; ++i)
//                 dp[i] = dp[i - 1] + dp[i - 2];
//             return dp[n];
//         }
//     };

// 746 使用最小花费爬楼梯
// class Solution
// {
// public:
//     int minCostClimbingStairs(vector<int> &cost)
//     {
//         int n = cost.size();
//         vector<int> dp(n + 1);
//         dp[0] = 0;
//         dp[1] = 0;
//         for (int i = 2; i <= n; ++i)
//         {

//             dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
//         }
//         return dp[n];
//     }
// };

// 62 不同路径
// class Solution
// {
// public:
//     int uniquePaths(int m, int n)
//     {
//         vector<vector<int>> dp(m, vector<int>(n, 0));
//         for (int i = 0; i < n; ++i)
//             dp[0][i] = 1;
//         for (int j = 0; j < m; ++j)
//             dp[j][0] = 1;
//         for (int i = 1; i < m; ++i)
//         {
//             for (int j = 1; j < n; ++j)
//             {
//                 dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
//             }
//         }
//         return dp[m - 1][n - 1];
//     }
// };

// 滚动数组
// class Solution
// {
// public:
//     int uniquePaths(int m, int n)
//     {
//         vector<int> dp(n);
//         for (int i = 0; i < n; ++i)
//             dp[i] = 1;
//         for (int i = 1; i < m; ++i)
//         {
//             for (int j = 1; j < n; ++j)
//                 dp[j] += dp[j - 1];
//         }
//         return dp[n - 1];
//     }
// };

// 63 不同路径 II
// class Solution {
//     public:
//         int uniquePathsWithObstacles(vector<vector<int>>& obs) {
//             int m = obs.size(), n = obs[0].size();
//             if(obs[0][0] == 1 || obs[m - 1][n - 1] == 1) return 0;
//             vector<vector<int>> dp(m, vector<int>(n));
//             for(int i = 0; i < n && !obs[0][i]; ++i) dp[0][i] = 1;
//             for(int j = 0; j < m && !obs[j][0]; ++j) dp[j][0] = 1;
//             for(int i = 1; i < m; ++i)
//             {
//                 for(int j = 1; j < n; ++j)
//                 {
//                     if(obs[i][j] == 1) continue;
//                     dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
//                 }
//             }
//             return dp[m - 1][n - 1];
//         }
//     };

// 滚动数组
// class Solution
// {
// public:
//     int uniquePathsWithObstacles(vector<vector<int>> &obs)
//     {
//         int m = obs.size(), n = obs[0].size();
//         if (obs[0][0] == 1 || obs[m - 1][n - 1] == 1)
//             return 0;
//         vector<int> dp(n);
//         for (int i = 0; i < n && !obs[0][i]; ++i)
//             dp[i] = 1;
//         for (int i = 1; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (obs[i][j] == 1)
//                     dp[j] = 0;

//                 else if (j != 0)
//                     dp[j] += dp[j - 1];
//             }
//         }
//         return dp[n - 1];
//     }
// };

// 343 整数拆分
// class Solution
// {
// public:
//     int integerBreak(int n)
//     {
//         // j i - j
//         // dp[n] 表示可拆分的数乘积的最大化.
//         vector<int> dp(n + 1);
//         for (int i = 2; i <= n; ++i)
//         {
//             for (int j = 1; j <= i / 2; ++j)
//                 dp[i] = max(max(dp[i], j * (i - j)), j * dp[i - j]);
//         }
//         return dp[n];
//     }
// };

int main()
{
    return 0;
}