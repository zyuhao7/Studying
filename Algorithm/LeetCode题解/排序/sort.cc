#include <iostream>

// day-2025-4-12
// 215  数组中的第K个最大元素
// class Solution
// {
// public:
//     int quick_sort(vector<int> &nums, int l, int r, int k)
//     {
//         if (l >= r)
//             return nums[l];
//         int i = l - 1, j = r + 1, x = nums[l + r >> 1];
//         while (i < j)
//         {
//             do
//                 ++i;
//             while (nums[i] < x);
//             do
//                 --j;
//             while (nums[j] > x);
//             if (i < j)
//                 swap(nums[i], nums[j]);
//         }
//         if (k <= j)
//             return quick_sort(nums, l, j, k);
//         return quick_sort(nums, j + 1, r, k);
//     }

//     int findKthLargest(vector<int> &nums, int k)
//     {
//         return quick_sort(nums, 0, nums.size() - 1, nums.size() - k);
//     }
// };