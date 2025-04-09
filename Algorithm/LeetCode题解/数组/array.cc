#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// day-2025-4-8 for interview
// 1.两数之和
// class Solution
// {
// public:
//     vector<int> twoSum(vector<int> &nums, int target)
//     {
//         unordered_map<int, int> hash;
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             if (hash.count(target - nums[i]))
//                 return {i, hash[target - nums[i]]};
//             hash[nums[i]] = i;
//         }
//         return {};
//     }
// };

// 283. 移动零
// class Solution
// {
// public:
//     void moveZeroes(vector<int> &nums)
//     {
//         int i = 0, j = 0, n = nums.size();
//         while (j < n)
//         {
//             if (nums[j])
//             {
//                 swap(nums[i], nums[j]);
//                 i++;
//             }
//             j++;
//         }
//     }
// };

// 88. 合并两个有序数组

// class Solution
// {
// public:
//     void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
//     {
//         int t = m + n - 1;
//         int i = m - 1, j = n - 1;
//         while (i >= 0 && j >= 0)
//         {
//             if (nums1[i] > nums2[j])
//                 nums1[t--] = nums1[i--];
//             else
//                 nums1[t--] = nums2[j--];
//         }
//         while (i >= 0)
//             nums1[t--] = nums1[i--];
//         while (j >= 0)
//             nums1[t--] = nums2[j--];
//     }
// };

// 53. 最大子数组和
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

// 167. 两数之和 II - 输入有序数组
// 双指针
// class Solution
// {
// public:
//     vector<int> twoSum(vector<int> &nums, int target)
//     {
//         // 双指针
//         int i = 0, j = nums.size() - 1;
//         while (i < j)
//         {
//             if (nums[i] + nums[j] == target)
//                 return {i + 1, j + 1};
//             else if (nums[i] + nums[j] < target)
//                 i++;
//             else
//                 j--;
//         }
//         return {};
//     }
// };
// 二分法
// class Solution
// {
// public:
//     vector<int> twoSum(vector<int> &nums, int target)
//     {
//         // 二分
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             int l = i + 1, r = nums.size() - 1;
//             int x = target - nums[i];
//             while (l <= r)
//             {
//                 int m = l + r >> 1;
//                 if (nums[m] == x)
//                     return {i + 1, m + 1};
//                 else if (nums[m] < x)
//                     l = m + 1;
//                 else
//                     r = m - 1;
//             }
//         }
//         return {-1, -1};
//     }
// };

