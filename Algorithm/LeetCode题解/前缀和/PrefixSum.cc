#include <iostream>
#include <vector>
using namespace std;
// day-2025-3-8
// 303. 区域和检索 - 数组不可变
// class NumArray
// {
// public:
//     vector<int> PreSum;
//     NumArray(vector<int> &nums)
//     {
//         int n = nums.size();
//         PreSum.resize(n + 1);
//         for (int i = 1; i <= n; ++i)
//             PreSum[i] = PreSum[i - 1] + nums[i - 1];
//     }

//     int sumRange(int left, int right)
//     {
//         return PreSum[right + 1] - PreSum[left];
//     }
// };

// 3427. 变长子数组求和
// class Solution
// {
// public:
//     int subarraySum(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> subnums(n + 1);
//         vector<int> Prefix(n + 1);
//         for (int i = 1; i <= n; ++i)
//             Prefix[i] = Prefix[i - 1] + nums[i - 1];
//         for (int i = 0; i < n; ++i)
//         {
//             int start = max(0, i - nums[i]);
//             subnums[i] = Prefix[i + 1] - Prefix[start];
//         }

//         return accumulate(subnums.begin(), subnums.end(), 0);
//     }
// };
int main()
{

    return 0;
}