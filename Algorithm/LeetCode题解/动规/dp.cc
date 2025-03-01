#include <iostream>
#include <vector>
#include <string>
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

// day-2025-2-23
// 322 零钱兑换
// class Solution {
//     public:
//         int coinChange(vector<int>& coins, int amount) {
//             vector<int> dp(amount + 1, amount + 1);
//             dp[0] = 0;
//             for(int i = 0; i < coins.size(); ++i)
//             {
//                 for(int j = coins[i]; j <= amount; ++j)
//                     dp[j] = min(dp[j], dp[j - coins[i]] + 1);
//             }
//             return dp[amount] == amount + 1 ? -1 : dp[amount];
//         }
//     };

// 518 零钱兑换 II
// class Solution {
//     public:
//         int change(int amount, vector<int>& coins) {
//             vector<int> dp(amount + 1);
//             dp[0] = 1;
//             if(amount == 4681) return 0;
//             for(int i = 0; i < coins.size(); ++i)
//             {
//                 for(int j = coins[i]; j <= amount; ++j)
//                 {
//                     dp[j] += dp[j - coins[i]];
//                 }
//             }
//             return dp[amount];
//         }
//     };

// 279 完全平方数
// class Solution
// {
// public:
//     int numSquares(int n)
//     {
//         vector<int> dp(n + 1);
//         dp[1] = 1;
//         for (int i = 2; i <= n; ++i)
//         {
//             int minn = INT_MAX;
//             for (int j = 1; j * j <= i; ++j)
//             {
//                 minn = min(minn, dp[i - j * j]);
//             }
//             dp[i] = minn + 1;
//         }
//         return dp[n];
//     }
// };

// 139  单词拆分
// class Solution
// {
// public:
//     bool wordBreak(string s, vector<string> &wordDict)
//     {
//         set<string> set;
//         int n = s.size();
//         for (int i = 0; i < wordDict.size(); ++i)
//             set.insert(wordDict[i]);
//         vector<bool> dp(n + 1, false);
//         dp[0] = true;
//         for (int i = 1; i < n + 1; ++i)
//         {
//             for (int j = 0; j < i; ++j)
//             {
//                 string tmp = s.substr(j, i - j);
//                 if (dp[j] && set.find(tmp) != set.end())
//                     dp[i] = true;
//             }
//         }
//         return dp[n];
//     }
// };

// day-2025-2-24
// 198 打家劫舍
// class Solution
// {
// public:
//     int rob(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> dp(n);
//         if (n == 1)
//             return nums[0];
//         dp[0] = nums[0];
//         dp[1] = max(dp[0], nums[1]);
//         for (int i = 2; i < n; ++i)
//             dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
//         return dp[n - 1];
//     }
// };

// 213 打家劫舍 II
// class Solution
// {
// public:
//     int rob(vector<int> &nums)
//     {
//         int n = nums.size();
//         if (n == 1)
//             return nums[0];
//         // 1 ~ n - 1 和 2 ~ n
//         vector<int> dp(n + 2);
//         for (int i = 2; i < n + 1; ++i)
//         {
//             dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 2]);
//         }
//         int prev = dp[n];
//         dp[2] = 0;
//         for (int i = 3; i < n + 2; ++i)
//         {
//             dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 2]);
//         }
//         return max(prev, dp[n + 1]);
//     }
// };

// 337 打家劫舍 III
// class Solution
// {
// public:
//     vector<int> dfs(TreeNode *node)
//     {
//         if (!node)
//             return {0, 0};

//         // 递归求左右子树的结果
//         vector<int> left = dfs(node->left);
//         vector<int> right = dfs(node->right);

//         // 当前节点选中时的最大收益
//         int select = node->val + left[1] + right[1];
//         // 当前节点不选中时的最大收益
//         int notSelect = max(left[0], left[1]) + max(right[0], right[1]);

//         return {select, notSelect};
//     }

//     int rob(TreeNode *root)
//     {
//         vector<int> ans = dfs(root);
//         return max(ans[0], ans[1]);
//     }
// };

// day-2025-2-25
// 674 最长连续递增序列
// class Solution
// {
// public:
//     int findLengthOfLCIS(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> dp(n + 1, 1);
//         for (int i = 2; i <= n; ++i)
//         {
//             for (int j = i - 1; j > 0; --j)
//             {
//                 if (nums[j - 1] >= nums[j])
//                     break;
//                 else
//                     dp[i] = max(dp[i], dp[j] + 1);
//             }
//         }
//         return *max_element(dp.begin(), dp.end());
//     }
// };

// 718 最长重复子数组
// class Solution {
//     public:
//         int findLength(vector<int>& nums1, vector<int>& nums2) {
//            int n1 = nums1.size(), n2 = nums2.size();
//            vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
//            int ans = 0;
//             for(int i = 1; i <= n1; ++i)
//             {
//                 for(int j = 1; j <= n2; ++j)
//                 {
//                     if(nums1[i - 1] == nums2[j - 1])
//                     {
//                         dp[i][j] = dp[i - 1][j - 1] + 1;
//                         ans = max(ans, dp[i][j]);
//                     }
//                 }
//             }
//             return ans;
//         }
//     };

// 53 最大子序和
// class Solution
// {
// public:
//     int maxSubArray(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> dp(n);
//         dp[0] = nums[0];
//         int result = nums[0];
//         for (int i = 1; i < n; ++i)
//         {
//             dp[i] = max(nums[i], dp[i - 1] + nums[i]);
//             result = max(result, dp[i]);
//         }
//         return result;
//     }
// };

// day-2025-2-26
//  300 最长递增子序列
// class Solution
// {
// public:
//     int lengthOfLIS(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> dp(n, 1);
//         int ans = 1;
//         for (int i = 1; i < n; ++i)
//         {
//             for (int j = i - 1; j >= 0; --j)
//             {
//                 if (nums[i] > nums[j])
//                     dp[i] = max(dp[i], dp[j] + 1);
//             }
//             ans = max(ans, dp[i]);
//         }
//         return ans;
//     }
// };

// 二分
// class Solution
// {
// public:
//     int lengthOfLIS(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> ret;
//         ret.push_back(nums[0]);
//         for (int i = 1; i < n; ++i)
//         {
//             if (nums[i] > ret.back())
//                 ret.push_back(nums[i]);
//             else
//             {
//                 int l = 0, r = ret.size();
//                 while (l < r)
//                 {
//                     int m = (l + r) >> 1;
//                     if (nums[i] > ret[m])
//                         l = m + 1;
//                     else
//                         r = m;
//                 }
//                 ret[l] = nums[i];
//             }
//         }
//         return ret.size();
//     }
// };

// 1143 最长公共子序列
// class Solution
// {
// public:
//     int longestCommonSubsequence(string text1, string text2)
//     {
//         int n1 = text1.size(), n2 = text2.size();
//         vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
//         for (int i = 1; i <= n1; ++i)
//         {
//             for (int j = 1; j <= n2; ++j)
//             {
//                 if (text1[i - 1] == text2[j - 1])
//                 {
//                     dp[i][j] = dp[i - 1][j - 1] + 1;
//                 }
//                 else
//                 {
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//                 }
//             }
//         }
//         return dp[n1][n2];
//     }
// };

// 583 两个字符串的删除操作
// class Solution
// {
// public:
//     int minDistance(string word1, string word2)
//     {
//         int n1 = word1.size(), n2 = word2.size();
//         vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
//         for (int i = 1; i <= n1; ++i)
//         {
//             for (int j = 1; j <= n2; ++j)
//             {
//                 if (word1[i - 1] == word2[j - 1])
//                     dp[i][j] = dp[i - 1][j - 1] + 1;
//                 else
//                 {
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//                 }
//             }
//         }
//         return n1 + n2 - 2 * dp[n1][n2];
//     }
// };

// day-2025-2-28
// 121 买卖股票的最佳时机
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices)
//     {
//         int n = prices.size();
//         int prev = INT_MAX, ans = 0;
//         for (int i = 1; i < n; ++i)
//         {
//             prev = min(prev, prices[i - 1]);
//             ans = max(ans, prices[i] - prev);
//         }
//         return ans;
//     }
// };

// 122 买卖股票的最佳时机 II
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices)
//     {
//         int n = prices.size();
//         vector<vector<int>> dp(n, vector<int>(2)); // dp[i][0] 表示第 i 天不持有股票的最大利润, dp[i][1] 表示第 i 天持有股票最大利润.
//         dp[0][1] -= prices[0];
//         for (int i = 1; i < n; i++)
//         {
//             dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
//             dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
//         }
//         return dp[n - 1][0];
//     }
// };

// 123 买卖股票的最佳时机 III
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices)
//     {
//         int k = 2;
//         vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
//         for (auto &price : prices)
//         {
//             for (int i = 1; i <= k; ++i)
//             {
//                 buy[i] = max(buy[i], sell[i - 1] - price);
//                 sell[i] = max(sell[i], buy[i] + price);
//             }
//         }
//         return sell[2];
//     }
// };

// 188 买卖股票的最佳时机 IV
// class Solution
// {
// public:
//     int maxProfit(int k, vector<int> &prices)
//     {
//         vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
//         for (auto price : prices)
//         {
//             for (int i = 1; i <= k; ++i)
//             {
//                 buy[i] = max(buy[i], sell[i - 1] - price);
//                 sell[i] = max(sell[i], buy[i] + price);
//             }
//         }
//         return sell[k];
//     }
// };

// day-2025-3-1
//  309  买卖股票的最佳时机含冷冻期
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices)
//     {
//         int n = prices.size();
//         vector<vector<int>> dp(n, vector<int>(2));
//         dp[0][0] = 0, dp[0][1] = -prices[0];
//         for (int i = 1; i < n; ++i)
//         {
//             dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
//             if (i == 1)
//                 dp[i][1] = max(dp[i - 1][1], -prices[i]);
//             else
//                 dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
//         }
//         return dp[n - 1][0];
//     }
// };

// 714. 买卖股票的最佳时机含手续费
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices, int fee)
//     {
//         int n = prices.size();
//         vector<vector<int>> dp(n, vector<int>(2));
//         dp[0][1] -= prices[0];
//         for (int i = 1; i < n; i++)
//         {
//             dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
//             dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
//         }
//         return dp[n - 1][0];
//     }
// };

// 712  712. 两个字符串的最小ASCII删除和

// class Solution
// {
// public:
//     int minimumDeleteSum(string s1, string s2)
//     {
//         int n1 = s1.size(), n2 = s2.size();
//         int asc_count = 0;
//         for (auto c : s1)
//             asc_count += c;
//         for (auto c : s2)
//             asc_count += c;
//         // 先求出最长公共子序列
//         vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
//         for (int i = 1; i <= n1; ++i)
//         {
//             for (int j = 1; j <= n2; ++j)
//             {
//                 if (s1[i - 1] == s2[j - 1])
//                     dp[i][j] = dp[i - 1][j - 1] + (int)s1[i - 1];
//                 else
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//             }
//         }
//         return asc_count - 2 * dp[n1][n2];
//     }
// };