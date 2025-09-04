#include <iostream>
#include <vector>
#include <string>
using namespace std;

// day-2025-2-27
// 455 分发饼干
// class Solution
// {
// public:
//     int findContentChildren(vector<int> &g, vector<int> &s)
//     {
//         int m = g.size(), n = s.size(), ans = 0;
//         sort(g.begin(), g.end());
//         sort(s.begin(), s.end());
//         int j = 0, i = 0;
//         while (i < m && j < n)
//         {
//             if (s[j] >= g[i])
//             {
//                 j++;
//                 i++;
//                 ans++;
//             }
//             else
//                 j++;
//         }
//         return ans;
//     }
// };

// 1005 K 次取反后最大化的数组和
// class Solution
// {
// public:
//     static bool cmp(int a, int b)
//     {
//         return abs(a) > abs(b);
//     }
//     int largestSumAfterKNegations(vector<int> &nums, int k)
//     {
//         sort(nums.begin(), nums.end(), cmp);
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             if (nums[i] < 0 && k)
//             {
//                 nums[i] *= -1;
//                 k--;
//             }
//         }
//         if (k % 2 == 1)
//             nums[nums.size() - 1] *= -1;
//         return accumulate(nums.begin(), nums.end(), 0);
//     }
// };

// 860 柠檬水找零
// class Solution
// {
// public:
//     bool lemonadeChange(vector<int> &bills)
//     {
//         int fives = 0, tens = 0;
//         for (auto &bil : bills)
//         {
//             if (bil == 5)
//                 fives++;
//             else if (bil == 10)
//             {
//                 if (fives >= 1)
//                     fives--, tens++;
//                 else
//                     return false;
//             }
//             else
//             {
//                 if (fives >= 1 && tens >= 1)
//                     fives--, tens--;
//                 else if (fives >= 3)
//                     fives -= 3;
//                 else
//                     return false;
//             }
//         }
//         return true;
//     }
// };

// day-2025-4-19
//  135 分发糖果
// class Solution
// {
// public:
//     int candy(vector<int> &ratings)
//     {
//         int n = ratings.size();
//         vector<int> candys(n, 1);

//         for (int i = 1; i < n; ++i)
//         {
//             if (ratings[i] > ratings[i - 1])
//                 candys[i] = candys[i - 1] + 1;
//         }

//         for (int i = n - 2; i >= 0; --i)
//         {
//             if (ratings[i] > ratings[i + 1])
//                 candys[i] = max(candys[i], candys[i + 1] + 1);
//         }
//         int res = 0;
//         for (auto c : candys)
//             res += c;
//         return res;
//     }
// };

// day-2025-4-29
// 406 根据身高重建队列
// class Solution
// {
// public:
//     vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
//     {
//         sort(people.begin(), people.end(), [](vector<int> &u, vector<int> &v)
//              { return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]); });
//         // [7, 0] [7, 1] [6, 1] [5, 0] [5, 2] [4, 4]
//         vector<vector<int>> ans;
//         for (const vector<int> &person : people)
//         {
//             ans.insert(ans.begin() + person[1], person);
//         }
//         return ans;
//     }
// };

// 452. 用最少数量的箭引爆气球
// class Solution
// {
// public:
//     int findMinArrowShots(vector<vector<int>> &points)
//     {
//         sort(points.begin(), points.end());
//         int ans = 1;
//         int end = points[0][1];
//         for (int i = 1; i < points.size(); ++i)
//         {
//             int left = points[i][0], right = points[i][1];
//             if (left <= end)
//             {
//                 end = min(end, right);
//             }
//             else
//             {
//                 end = right;
//                 ans++;
//             }
//         }
//         return ans;
//     }
// };

// day-2025-4-30
// 435 无重叠区间
// class Solution {
//     public:
//         int eraseOverlapIntervals(vector<vector<int>>& intervals) {
//             sort(intervals.begin(), intervals.end());
//             int n = intervals.size();
//             vector<vector<int>> ans;
//             ans.push_back({intervals[0][0], intervals[0][1]});
//             for(int i = 1; i < n; ++i)
//             {
//                 int l = intervals[i][0], r = intervals[i][1];
//                 if(l < ans.back()[1])
//                 {
//                     ans.back()[1] = min(ans.back()[1], r);
//                 }
//                 else
//                     ans.push_back({l, r});
//             }
//             return n - ans.size();
//         }
//     };

// 121 买卖股票的最佳时机
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices)
//     {
//         int prev = INT_MAX, ans = 0;
//         for (int i = 1; i < prices.size(); ++i)
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
//         int ans = 0;
//         for (int i = 0; i < prices.size(); ++i)
//         {
//             if (i + 1 < prices.size() && prices[i + 1] > prices[i])
//                 ans += prices[i + 1] - prices[i];
//         }
//         return ans;
//     }
// };

// 763 划分字母区间
// class Solution
// {
// public:
//     vector<int> partitionLabels(string s)
//     {
//         vector<int> ans;
//         vector<int> last(26);
//         for (int i = 0; i < s.size(); ++i)
//             last[s[i] - 'a'] = i;

//         int start = 0, end = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             end = max(end, last[s[i] - 'a']);
//             if (i == end)
//             {
//                 ans.push_back(end - start + 1);
//                 start = end + 1;
//             }
//         }
//         return ans;
//     }
// };

// day-2025-5-5
// 55. 跳跃游戏
// class Solution
// {
// public:
//     bool canJump(vector<int> &nums)
//     {
//         int n = nums.size();
//         int r = 0;
//         for (int i = 0; i < n; ++i)
//         {
//             if (r < i)
//                 return false;
//             r = max(i + nums[i], r);
//             if (r >= n - 1)
//                 return true;
//         }
//         return false;
//     }
// };

// 45. 跳跃游戏 II
// class Solution
// {
// public:
//     int jump(vector<int> &nums)
//     {
//         int n = nums.size();
//         int hopcnt = 0;
//         int r = 0, maxPos = 0;
//         for (int i = 0; i < n - 1; ++i)
//         {
//             maxPos = max(maxPos, i + nums[i]);
//             if (i >= r)
//             {
//                 r = maxPos;
//                 hopcnt++;
//             }
//         }
//         return hopcnt;
//     }
// };

// day-2025-5-6
//  134 加油站
//  class Solution
//  {
//  public:
//      int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
//      {
//          int n = gas.size();
//          int total = 0, sum = 0, st = 0;
//          for (int i = 0; i < n; ++i)
//          {
//              total += gas[i] - cost[i];
//              sum += gas[i] - cost[i];
//              if (sum < 0)
//              {
//                  st = i + 1;
//                  sum = 0;
//              }
//          }
//          return total < 0 ? -1 : st;
//      }
//  };

// 714 买卖股票的最佳时机含手续费
// class Solution
// {
// public:
//     int maxProfit(vector<int> &prices, int fee)
//     {
//         int n = prices.size();
//         vector<vector<int>> dp(n, vector<int>(2));
//         dp[0][1] = -prices[0];
//         // dp[i][0] 表示不持股, dp[i][1] 持股.
//         for (int i = 1; i < n; ++i)
//         {
//             dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
//             dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
//         }
//         return dp[n - 1][0];
//     }
// };

// day-2025-9-4
// 3633. 最早完成陆地和水上游乐设施的时间 I II
// class Solution
// {
// public:
//     int solove(vector<int> &firstTime, vector<int> &firstDuration, vector<int> &secondTime, vector<int> &secondDuration)
//     {
//         int Minfirstend = INT_MAX;
//         int ans = INT_MAX;
//         for (int i = 0; i < firstTime.size(); ++i)
//             Minfirstend = min(Minfirstend, firstTime[i] + firstDuration[i]);

//         for (int i = 0; i < secondTime.size(); ++i)
//             ans = min(ans, max(Minfirstend, secondTime[i]) + secondDuration[i]);
//         return ans;
//     }
//     int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration, vector<int> &waterStartTime, vector<int> &waterDuration)
//     {
//         int earliest1 = solove(landStartTime, landDuration, waterStartTime, waterDuration);
//         int earliest2 = solove(waterStartTime, waterDuration, landStartTime, landDuration);
//         return min(earliest1, earliest2);
//     }
// };