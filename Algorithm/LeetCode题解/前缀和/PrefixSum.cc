#include <iostream>
#include <vector>
using namespace std;
// day-2025-3-8
// §1.1 前缀和基础
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

// day-2025-3-10
// 2559. 统计范围内的元音字符串数
// class Solution
// {
// public:
//     bool is_vowel(char c)
//     {
//         return c == 'a' || c == 'e' ||
//                c == 'i' || c == 'o' ||
//                c == 'u';
//     }
//     vector<int> vowelStrings(vector<string> &words, vector<vector<int>> &queries)
//     {
//         int n = words.size();
//         vector<int> Prefix(n + 1);
//         for (int i = 1; i <= n; ++i)
//             Prefix[i] = Prefix[i - 1] + ((is_vowel(words[i - 1][0]) && is_vowel(words[i - 1][words[i - 1].size() - 1])) ? 1 : 0);
//         vector<int> res;
//         for (int i = 0; i < queries.size(); ++i)
//             res.push_back(Prefix[queries[i][1] + 1] - Prefix[queries[i][0]]);
//         return res;
//     }
// };

int main()
{

    return 0;
}