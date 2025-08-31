#include <vector>
using namespace std;
// day-2025-8-31
// 33. 搜索旋转排序数组 mid
// class Solution
// {
// public:
//     int search(vector<int> &nums, int target)
//     {
//         int l = 0, r = nums.size() - 1;
//         while (l <= r)
//         {
//             int m = l + r >> 1;
//             if (nums[m] == target)
//                 return m;
//             if (nums[m] >= nums[l]) // 左区间上升的
//             {                       // 并且 target 在左区间
//                 if (nums[l] <= target && target < nums[m])
//                     r = m - 1;
//                 else
//                     l = m + 1;
//             }
//             else // 左区间下降
//             {
//                 if (nums[m] < target && target <= nums[r])
//                     l = m + 1;
//                 else
//                     r = m - 1;
//             }
//         }
//         return -1;
//     }
// };