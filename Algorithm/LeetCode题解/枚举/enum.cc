#include <iostream>

using namespace std;

// day-2025-3-5
// §0.1 枚举右，维护左
// 1 两数之和
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); ++i)
            mp[nums[i]] = i;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto it = mp.find(target - nums[i]);
            if (it != mp.end())
            {
                if (i == (*it).second)
                    continue;
                else
                    return {i, (*it).second};
            }
        }
        return {};
    }
};