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



int main()
{

    return 0;
}