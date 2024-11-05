#include <iostream>
using namespace std;

// day-2024-11-2
// 剑指 Offer II 090. 环形房屋偷盗
// class Solution
// {
// public:
//     int rob(vector<int> &nums)
//     {
//         int n = nums.size();
//         if (n == 1)
//             return nums[0];
//         if (n == 2)
//             return max(nums[1], nums[0]);
//         vector<int> dp(n + 2, 0);
//         int prev;
//         // 从 1 到 n - 1
//         for (int i = 2; i < n + 1; i++)
//         {
//             dp[i] = max(dp[i - 2] + nums[i - 2], dp[i - 1]);
//         }
//         prev = dp[n];
//         dp[2] = 0;
//         //  2 - n
//         for (int i = 3; i < n + 2; ++i)
//         {
//             dp[i] = max(dp[i - 2] + nums[i - 2], dp[i - 1]);
//         }
//         return max(prev, dp[n + 1]);
//     }
// };
// 剑指 Offer II 091. 粉刷房子
// class Solution
// {
// public:
//     int minCost(vector<vector<int>> &costs)
//     {
//         int n = costs.size();
//         vector<vector<int>> dp(n, vector<int>(3, 0));
//         dp[0][0] = costs[0][0];
//         dp[0][1] = costs[0][1];
//         dp[0][2] = costs[0][2];
//         for (int i = 1; i < n; ++i)
//         {
//             dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
//             dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i][1];
//             dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i][2];
//         }
//         return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
//     }
// };

// 滚动数组
// class Solution
// {
// public:
//     int minCost(vector<vector<int>> &costs)
//     {
//         int n = costs.size();
//         vector<int> dp(3);
//         for (int j = 0; j < 3; ++j)
//             dp[j] = costs[0][j];

//         for (int i = 1; i < n; ++i)
//         {
//             vector<int> dpNew(3);
//             for (int j = 0; j < 3; ++j)
//             {
//                 dpNew[j] = min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
//             }
//             dp = dpNew;
//         }
//         return *min_element(dp.begin(), dp.end());
//     }
// };

// 剑指 Offer II 092. 翻转字符
// class Solution
// {
// public:
//     int minFlipsMonoIncr(string s)
//     {
//         int n = s.size();
//         vector<vector<int>> dp(n, vector<int>(2, 0));

//         dp[0][0] = s[0] == '0' ? 0 : 1;
//         dp[0][1] = s[0] == '1' ? 0 : 1;

//         for (int i = 1; i < n; ++i)
//         {
//             dp[i][0] = dp[i - 1][0] + (s[i] == '0' ? 0 : 1);                    // 保持当前为为 0 需要翻转的次数.
//             dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + (s[i] == '1' ? 0 : 1); // 1
//         }
//         return min(dp[n - 1][0], dp[n - 1][1]);
//     }
// };

// 滑动数组
// class Solution
// {
// public:
//     int minFlipsMonoIncr(string s)
//     {
//         int dp0 = (s[0] == '0' ? 0 : 1);
//         int dp1 = (s[0] == '1' ? 0 : 1);
//         for (int i = 1; i < s.size(); ++i)
//         {
//             dp1 = min(dp0, dp1) + (s[i] == '0');
//             dp0 += s[i] == '1';
//         }
//         return min(dp0, dp1);
//     }
// };

// 剑指 Offer II 093. 最长斐波那契数列
// class Solution {
// public:
//     int lenLongestFibSubseq(vector<int>& arr) {
//         int n = arr.size();
//         unordered_map<int, int> mp;
//         for(int i = 0; i < n; ++i) mp[arr[i]] = i;
//         int ans = 0;
//         vector<vector<int>> dp(n, vector<int>(n));
//         for(int i = 0; i < n; ++i)
//         {
//             for(int j = i - 1; j >=0 && arr[j] * 2 > arr[i]; --j)
//             {
//                 int k = -1;
//                 if(mp.count(arr[i] - arr[j]))
//                     k = mp[arr[i] - arr[j]];
//                 if(k >= 0)
//                     dp[j][i] = max(dp[k][j] + 1, 3);
//                 ans = max(ans, dp[j][i]);
//             }
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 094. 最少回文分割
// class Solution
// {
// public:
//     int minCut(string s)
//     {
//         int n = s.size();
//         if (n <= 1)
//             return 0;

//         // Create a DP table to store palindromic information
//         vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
//         for (int i = 0; i < n; ++i)
//         {
//             isPalindrome[i][i] = true; // Each character is a palindrome by itself
//             if (i < n - 1 && s[i] == s[i + 1])
//             {
//                 isPalindrome[i][i + 1] = true; // Check two consecutive equal characters
//             }
//         }

//         // Fill the DP table for palindromes of length greater than 2
//         for (int len = 3; len <= n; ++len)
//         {
//             for (int i = 0; i <= n - len; ++i)
//             {
//                 int j = i + len - 1;
//                 if (s[i] == s[j] && isPalindrome[i + 1][j - 1])
//                 {
//                     isPalindrome[i][j] = true;
//                 }
//             }
//         }

//         // Create a DP array for minimum cuts
//         vector<int> cuts(n, n - 1);
//         for (int i = 0; i < n; ++i)
//         {
//             if (isPalindrome[0][i])
//             {
//                 cuts[i] = 0; // No cuts needed if s[0..i] is a palindrome
//             }
//             else
//             {
//                 for (int j = 0; j < i; ++j)
//                 {
//                     if (isPalindrome[j + 1][i])
//                     {
//                         cuts[i] = min(cuts[i], cuts[j] + 1);
//                     }
//                 }
//             }
//         }

//         return cuts[n - 1];
//     }
// };

// ## day-2024-11-4

// 剑指 Offer II 095. 最长公共子序列
// class Solution
// {
// public:
//     int longestCommonSubsequence(string text1, string text2)
//     {
//         int n1 = text1.size();
//         int n2 = text2.size();
//         vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
//         for (int i = 1; i <= n1; ++i)
//         {
//             for (int j = 1; j <= n2; ++j)
//             {
//                 if (text1[i - 1] == text2[j - 1])
//                     dp[i][j] = dp[i - 1][j - 1] + 1;
//                 else
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//             }
//         }
//         return dp[n1][n2];
//     }
// };

// 剑指 Offer II 096. 字符串交织
// class Solution
// {
// public:
//     bool isInterleave(string s1, string s2, string s3)
//     {
//         int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
//         if (n1 + n2 != n3)
//             return false;
//         vector<vector<int>> f(n1 + 1, vector<int>(n2 + 1, 0));
//         f[0][0] = 1;

//         for (int i = 0; i <= n1; ++i)
//         {
//             for (int j = 0; j <= n2; ++j)
//             {
//                 int p = i + j - 1;
//                 if (i > 0)
//                     f[i][j] |= (f[i - 1][j] && s1[i - 1] == s3[p]);
//                 if (j > 0)
//                     f[i][j] |= (f[i][j - 1] && s2[j - 1] == s3[p]);
//             }
//         }
//         return f[n1][n2];
//     }
// };

// 剑指 Offer II 097. 子序列的数目
// class Solution {
// public:
//     int mod = 1e9 + 7;
//     int numDistinct(string s, string t) {
//         int m = s.size(), n = t.size();
//         vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
//         for(int i = 0; i <= m; ++i)
//             dp[i][0] = 1;
//         for(int i = 1; i<=m; ++i)
//         {
//             for(int j = 1; j <= i && j <= n; ++j)
//             {
//                 if(s[i - 1] == t[j - 1])
//                     dp[i][j] = (dp[i - 1][j - 1] % mod + dp[i - 1][j] %mod) %mod;
//                 else
//                     dp[i][j] = dp[i - 1][j];
//             }
//         }
//         return dp[m][n];
//     }
// };

// ##  day-2024-11-5

// 剑指 Offer II 098. 路径的数目
// class Solution
// {
// public:
//     int uniquePaths(int m, int n)
//     {
//         vector<vector<int>> dp(m, vector<int>(n, 1));
//         for (int i = 1; i < m; ++i)
//         {
//             for (int j = 1; j < n; ++j)
//             {
//                 dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
//             }
//         }
//         return dp[m - 1][n - 1];
//     }
// };

// 滚动数组
// class Solution {
// public:
//     int uniquePaths(int m, int n) {
//         vector<int> dp(n, 1);
//         for(int i = 1; i < m; ++i)
//         {
//             for(int j = 1; j < n; ++j)
//             {
//                 dp[j] += dp[j - 1];
//                 cout<<dp[j]<<" ";
//             }
//             cout<<endl;
//         }
//         return dp[n - 1];
//     }
// };

// 剑指 Offer II 099. 最小路径之和
// class Solution
// {
// public:
//     int minPathSum(vector<vector<int>> &grid)
//     {
//         int m = grid.size(), n = grid[0].size();
//         vector<int> dp(n, 0);
//         dp[0] = grid[0][0];

//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (i == 0 && j == 0)
//                     dp[0] = grid[0][0];
//                 else if (i == 0)
//                     dp[j] = dp[j - 1] + grid[i][j];
//                 else if (j == 0)
//                     dp[j] = dp[j] + grid[i][j];
//                 else
//                     dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
//             }
//         }
//         return dp[n - 1];
//     }
// };

// 剑指 Offer II 100. 三角形中最小路径之和
// 自底向上
// class Solution
// {
// public:
//     int minimumTotal(vector<vector<int>> &triangle)
//     {
//         int m = triangle.size();
//         vector<int> dp(m);
//         for (int i = 0; i < m; ++i)
//             dp[i] = triangle[m - 1][i];
//         for (int i = m - 2; i >= 0; --i)
//         {
//             for (int j = 0; j <= i; ++j)
//             {
//                 dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
//             }
//         }
//         return dp[0];
//     }
// };
// 自顶向下
// class Solution
// {
// public:
//     int minimumTotal(vector<vector<int>> &triangle)
//     {
//         int n = triangle.size();
//         vector<int> f(n);
//         f[0] = triangle[0][0];
//         for (int i = 1; i < n; ++i)
//         {
//             f[i] = f[i - 1] + triangle[i][i];
//             for (int j = i - 1; j > 0; --j)
//             {
//                 f[j] = min(f[j], f[j - 1]) + triangle[i][j];
//             }
//             f[0] += triangle[i][0];
//         }
//         return *min_element(f.begin(), f.end());
//     }
// };

// 剑指 Offer II 101. 分割等和子串
// class Solution {
// public:
//     bool canPartition(vector<int>& nums) {
//         int sum = 0;
//         for(int i = 0; i < nums.size(); ++i) sum += nums[i];
//         vector<int> dp(10001, 0);
//         if(sum % 2 == 1) return false;
//         int target = sum / 2;
//         for(int i = 0; i < nums.size(); ++i)
//         {
//             for(int j = target; j >= nums[i]; --j)
//             {
//                 dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
//             }
//         }
//         return dp[target] == target;
//     }
// };

int main()
{

    return 0;
}