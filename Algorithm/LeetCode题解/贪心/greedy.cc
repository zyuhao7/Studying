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


int main()
{
    return 0;
}