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

int main()
{
}


