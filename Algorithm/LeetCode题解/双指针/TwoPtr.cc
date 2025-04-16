#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// day-2025-4-16
// 15 三数之和
// class Solution
// {
// public:
//     vector<vector<int>> threeSum(vector<int> &nums)
//     {
//         vector<vector<int>> res;
//         sort(nums.begin(), nums.end());
//         int n = nums.size();

//         for (int i = 0; i < n - 2; ++i)
//         {
//             int l = i + 1, r = n - 1;
//             if (i && nums[i - 1] == nums[i])
//                 continue;
//             int t = -nums[i];
//             while (l < r)
//             {
//                 if (nums[l] + nums[r] == t)
//                 {
//                     res.push_back({-t, nums[l], nums[r]});
//                     while (l < r && nums[l + 1] == nums[l])
//                         l++;
//                     while (l < r && nums[r - 1] == nums[r])
//                         r--;
//                     l++;
//                     r--;
//                 }
//                 else if (nums[l] + nums[r] < t)
//                     l++;
//                 else
//                     r--;
//             }
//         }
//         return res;
//     }
// };

// 11 盛最多水的容器
// class Solution
// {
// public:
//     int maxArea(vector<int> &height)
//     {
//         int res = 0;
//         int i = 0, j = height.size() - 1;
//         while (i < j)
//         {
//             res = height[i] < height[j] ? max(res, (j - i) * height[i++]) : max(res, (j - i) * height[j--]);
//         }
//         return res;
//     }
// };

// 42  接雨水
// class Solution
// {
// public:
//     int trap(vector<int> &height)
//     {
//         int n = height.size();
//         int l = 0, r = n - 1;
//         int ans = 0;
//         int leftMax = 0;
//         int rightMax = 0;
//         while (l < r)
//         {
//             leftMax = max(leftMax, height[l]);
//             rightMax = max(rightMax, height[r]);
//             if (height[l] < height[r])
//             {
//                 ans += leftMax - height[l];
//                 l++;
//             }
//             else
//             {
//                 ans += rightMax - height[r];
//                 r--;
//             }
//         }
//         return ans;
//     }
// };
int main()
{

    return 0;
}