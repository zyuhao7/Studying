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
int main()
{
    return 0;
}