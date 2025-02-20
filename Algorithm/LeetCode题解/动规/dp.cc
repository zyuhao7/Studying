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

// day-2025-2-19
// 377 组合总和 Ⅳ
// class Solution
// {
// public:
//     int combinationSum4(vector<int> &nums, int target)
//     {
//         vector<unsigned> dp(target + 1);
//         dp[0] = 1;
//         for (int i = 1; i <= target; ++i)
//         {
//             for (auto num : nums)
//             {
//                 if (i >= num)
//                     dp[i] += dp[i - num];
//             }
//         }
//         return dp[target];
//     }
// };

// 64   最小路径和
// class Solution {
//     public:
//         int minPathSum(vector<vector<int>>& grid) {
//             int m = grid.size(), n = grid[0].size();
//             vector<vector<int>> dp(m, vector<int>(n));
//             for(int i = 0; i < m; ++i)
//             {
//                 for(int j = 0; j < n; ++j)
//                 {
//                     if(i == 0 && j == 0) dp[i][j] = grid[i][j];
//                     else if(i == 0)
//                         dp[i][j] = dp[i][j - 1] + grid[i][j];
//                     else if(j == 0)
//                         dp[i][j] = dp[i - 1][j] + grid[i][j];
//                     else
//                         dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
//                 }
//             }
//             return dp[m - 1][n - 1];
//         }
//     };

// 滚动数组
// class Solution
// {
// public:
//     int minPathSum(vector<vector<int>> &grid)
//     {
//         int m = grid.size(), n = grid[0].size();
//         vector<int> dp(n);
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (i == 0 && j == 0)
//                     dp[j] = grid[i][j];
//                 else if (i == 0)
//                     dp[j] = dp[j - 1] + grid[i][j];
//                 else if (j == 0)
//                     dp[j] += grid[i][j];
//                 else
//                     dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
//             }
//         }
//         return dp[n - 1];
//     }
// };

// day-2025-2-20
// 416 分割等和子集
// class Solution
// {
// public:
//     bool canPartition(vector<int> &nums)
//     {
//         int sum = accumulate(nums.begin(), nums.end(), 0);

//         if (sum % 2 == 1)
//             return false;
//         int target = sum / 2;
//         vector<int> dp(target + 1, 0);

//         for (int i = 0; i < nums.size(); ++i)
//         {
//             for (int j = target; j >= nums[i]; --j)
//             {
//                 dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
//             }
//         }
//         return dp[target] == target;
//     }
// };

// 1049 最后一块石头的重量 II
// class Solution
// {
// public:
//     int lastStoneWeightII(vector<int> &st)
//     {
//         int sum = accumulate(st.begin(), st.end(), 0);
//         int target = sum / 2;
//         vector<int> dp(target + 1);

//         for (int i = 0; i < st.size(); ++i)
//         {
//             for (int j = target; j >= st[i]; --j)
//             {
//                 dp[j] = max(dp[j], dp[j - st[i]] + st[i]);
//             }
//         }
//         return sum - 2 * dp[target];
//     }
// };

// 494 目标和
// class Solution {
//     public:
//         int findTargetSumWays(vector<int>& nums, int target) {

//             int sum = accumulate(nums.begin(), nums.end(), 0);
//             if(abs(target)  >sum || (sum - target) % 2) return 0;
//             int neg = (sum - target) / 2;
//              vector<int> dp(neg + 1);
//              dp[0] = 1;
//             for(int i = 0; i < nums.size(); ++i)
//             {
//                 for(int j = neg; j >= nums[i]; --j)
//                     dp[j] += dp[j - nums[i]];
//             }
//             return dp[neg];
//         }
//     };

// 474 一和零
// class Solution
// {
// public:
//     vector<int> getZerosOnes(string &s)
//     {
//         vector<int> zo(2);
//         for (int i = 0; i < s.size(); ++i)
//         {
//             zo[s[i] - '0']++;
//         }
//         return zo;
//     }
//     int findMaxForm(vector<string> &strs, int m, int n)
//     {
//         int l = strs.size();
//         vector<vector<vector<int>>> dp(l + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
//         for (int i = 1; i <= l; ++i)
//         {
//             vector<int> &&zo = getZerosOnes(strs[i - 1]);
//             int zeros = zo[0], ones = zo[1];
//             for (int j = 0; j <= m; ++j)
//             {
//                 for (int k = 0; k <= n; ++k)
//                 {
//                     dp[i][j][k] = dp[i - 1][j][k];
//                     if (j >= zeros && k >= ones)
//                         dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - zeros][k - ones] + 1);
//                 }
//             }
//         }
//         return dp[l][m][n];
//     }
// };

// class Solution {
//     public:
//         vector<int> getZerosOnes(string& s)
//         {
//             vector<int> zo(2);
//             for(int i = 0; i < s.size(); ++i)
//             {
//                 zo[s[i] - '0'] ++;
//             }
//             return zo;
//         }
//         int findMaxForm(vector<string>& strs, int m, int n) {
//             vector<vector<int>> dp(m + 1, vector<int>(n + 1));
//             for(int i = 1; i <= strs.size(); ++i)
//             {
//                 vector<int>&& zo = getZerosOnes(strs[i - 1]);
//                 int zeros = zo[0], ones = zo[1];
//                 for(int j = m; j >=zeros; --j)
//                 {
//                     for(int k = n; k >= ones; --k)
//                     {
//                         dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
//                     }
//                 }
//             }

//             return dp[m][n];
//         }
//     };
int main()
{

    return 0;
}