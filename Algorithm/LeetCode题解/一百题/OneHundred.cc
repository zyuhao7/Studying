#include <iostream>

using namespace std;
// day-2025-4-17
//   91 解码方法 动态规划
// class Solution
// {
// public:
//     int numDecodings(string s)
//     {
//         int n = s.size();
//         if (s[0] == '0')
//             return 0;
//         for (int i = 1; i < n; ++i)
//         {
//             if (s[i] == '0' && (s[i - 1] == '0' || s[i - 1] > '2'))
//                 return 0;
//         }
//         vector<int> dp(n + 1, 0);
//         dp[0] = 1;
//         dp[1] = 1;
//         for (int i = 2; i <= n; ++i)
//         {
//             if (s[i - 1] != '0')
//                 dp[i] += dp[i - 1];
//             if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))
//                 dp[i] += dp[i - 2];
//         }
//         return dp[n];
//     }
// };

// day-2025-4-18
// 53 最大子序和
// class Solution
// {
// public:
//     int maxSubArray(vector<int> &nums)
//     {
//         int maxSum = 0;
//         int ans = INT_MIN;
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             maxSum = max(nums[i], nums[i] + maxSum);
//             ans = max(ans, maxSum);
//         }

//         return ans;
//     }
// };

// 60 第k个排列
// class Solution
// {
// public:
//     int g = 0;
//     string res;
//     void Permutation(string &s, string current, vector<bool> &used, int k)
//     {

//         if (g == k)
//             return;
//         if (current.size() == s.size())
//         {
//             g++;
//             if (g == k)
//                 res = current;
//             return;
//         }
//         for (int i = 0; i < s.size(); ++i)
//         {
//             if (!used[i])
//             {
//                 used[i] = true;
//                 Permutation(s, current + s[i], used, k);
//                 used[i] = false;
//             }
//         }
//     }

//     string getPermutation(int n, int k)
//     {
//         string s;
//         for (int i = 1; i <= n; ++i)
//         {
//             s += i + '0';
//         }
//         vector<bool> used(n, false);
//         Permutation(s, "", used, k);
//         return res;
//     }
// };

int main()
{
}
