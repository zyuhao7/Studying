#include <iostream>

using namespace std;

// day-2025-3-5
// §0.1 枚举右，维护左
// 1 两数之和
// class Solution
// {
// public:
//     vector<int> twoSum(vector<int> &nums, int target)
//     {
//         unordered_map<int, int> mp;
//         for (int i = 0; i < nums.size(); ++i)
//             mp[nums[i]] = i;
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             auto it = mp.find(target - nums[i]);
//             if (it != mp.end())
//             {
//                 if (i == (*it).second)
//                     continue;
//                 else
//                     return {i, (*it).second};
//             }
//         }
//         return {};
//     }
// };

// day-2025-3-6
// 1512. 好数对的数目
// class Solution
// {
// public:
//     int numIdenticalPairs(vector<int> &nums)
//     {
//         int ans = 0;
//         unordered_map<int, int> mp;
//         for (auto &n : nums)
//         {
//             if (mp.count(n))
//                 ans += mp[n];
//             mp[n]++;
//         }
//         return ans;
//     }
// };

// day-2025-3-8
//  2001. 可互换矩形的组数
// class Solution
// {
// public:
//     long long interchangeableRectangles(vector<vector<int>> &rect)
//     {
//         long long ans = 0;
//         unordered_map<double, int> mp;
//         for (auto &x : rect)
//             ans += mp[(double)x[0] / x[1]]++;
//         return ans;
//     }
// };