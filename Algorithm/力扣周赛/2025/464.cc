#include <bits/stdc++.h>
using namespace std;

// day-2025-9-24
// 3658. 奇数和与偶数和的最大公约数 easy
// https://leetcode.cn/problems/gcd-of-odd-and-even-sums/
/*
    计算奇数和与偶数和, 然后求最大公约数
*/

/*
class Solution
{
public:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    int gcdOfOddEvenSums(int n)
    {
        int x = 1, sumOdd = 0, sumEven = 0;
        int t = n;
        while (t--)
        {
            sumOdd += x;
            x += 2;
        }
        t = n, x = 2;
        while (t--)
        {
            sumEven += x;
            x += 2;
        }
        return gcd(sumOdd, sumEven);
    }
};
*/

// 3659. 数组元素分组 middle
// https://leetcode.cn/problems/partition-array-into-k-distinct-groups/description/
/*
    统计每个数字出现的次数, 如果有数字出现次数大于 n/k 则无法分组

*/

/*
class Solution
{
public:
    bool partitionArray(vector<int> &nums, int k)
    {
        int n = nums.size();
        if (n % k != 0)
            return false;
        vector<int> cnt(100001, 0);
        for (int i = 0; i < n; ++i)
        {
            cnt[nums[i]]++;
            if (cnt[nums[i]] > n / k)
                return false;
        }
        return true;
    }
};
*/

//  跳跃游戏 合集
// 55. 跳跃游戏 middle
// https://leetcode.cn/problems/jump-game/description/
/*
    贪心算法, 维护一个能跳到的最远距离
    如果当前位置i在能跳到的最远距离r内, 则更新r为 max(r, i + nums[i])
    如果r能到达或超过最后一个位置, 则返回true
    否则返回false
*/

/*
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int n = nums.size();
        int r = 0;
        for (int i = 0; i <= r; ++i)
        {
            r = max(r, i + nums[i]);
            if (r >= n - 1)
                return true;
        }
        return false;
    }
};
*/

// 45. 跳跃游戏 II middle
// https://leetcode.cn/problems/jump-game-ii/description/
/*
    贪心算法, 维护一个能跳到的最远距离r, 当前步数step, 当前步数能跳到的最远位置end
    遍历数组, 更新r为 max(r, i + nums[i])
    如果当前位置i到达了end, 则说明需要增加一步跳跃, step++, 并更新end为r
    最后返回step
 */

/*
class Solution
{
public:
   int jump(vector<int> &nums)
   {
       int n = nums.size();
       int r = 0, step = 0, end = 0;
       for(int i = 0; i < n - 1; ++i)
       {
           r = max(r, i + nums[i]);
           if(i == end)
           {
               step++;
               end = r;
           }
       }
       return step;
   }
};
*/

//  1306. 跳跃游戏 III middle
// https://leetcode.cn/problems/jump-game-iii/description/

/*
    深度优先搜索, 从起点开始, 每次可以跳到 idx + arr[idx] 或 idx - arr[idx]
    如果跳到的位置值为0, 则返回true
    使用一个数组记录访问过的位置, 避免死循环
*/

/*
class Solution
{
public:
    bool dfs(vector<int> &arr, int idx, vector<bool> &vis)
    {
        if (arr[idx] == 0)
            return true;
        vis[idx] = true;
        int l = idx - arr[idx];
        int r = idx + arr[idx];
        if (l >= 0 && !vis[l])
            if (dfs(arr, l, vis))
                return true;
        if (r < arr.size() && !vis[r])
            if (dfs(arr, r, vis))
                return true;
        return false;
    }

    bool canReach(vector<int> &arr, int start)
    {
        vector<bool> vis(arr.size(), false);
        return dfs(arr, start, vis);
    }
};
*/