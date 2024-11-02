#include <iostream>
using namespace std;

// day-2024-10-29
// 剑指 Offer II 078. 合并排序链表

// merge 1
// class Solution
// {
// public:
//     ListNode *mergeKLists(vector<ListNode *> &lists)
//     {
//         if (lists.empty())
//             return nullptr;
//         ListNode *res = nullptr;
//         for (int i = 0; i < lists.size(); ++i)
//         {
//             res = merge(res, lists[i]);
//         }
//         return res;
//     }

//     ListNode *merge(ListNode *l1, ListNode *l2)
//     {
//         ListNode *dummy = new ListNode(0);
//         ListNode *tail = dummy;
//         while (l1 && l2)
//         {
//             if (l1->val < l2->val)
//             {
//                 tail->next = l1;
//                 l1 = l1->next;
//             }
//             else
//             {
//                 tail->next = l2;
//                 l2 = l2->next;
//             }
//             tail = tail->next;
//         }
//         if (l1)
//             tail->next = l1;
//         if (l2)
//             tail->next = l2;
//         return dummy->next;
//     }
// };

// merge 2
// class Solution
// {
// public:
//     ListNode *mergeKLists(vector<ListNode *> &lists)
//     {
//         return merge(lists, 0, lists.size() - 1);
//     }

// private:
//     ListNode *merge(vector<ListNode *> lists, int l, int r)
//     {
//         if (l > r)
//             return nullptr;
//         if (l == r)
//             return lists[l];
//         int m = (l + r) / 2;
//         ListNode *l1 = merge(lists, l, m);
//         ListNode *l2 = merge(lists, m + 1, r);

//         return mergeTwoLists(l1, l2);
//     }

//     ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
//     {
//         if (l1 == nullptr)
//             return l2;
//         if (l2 == nullptr)
//             return l1;
//         if (l1->val < l2->val)
//         {
//             l1->next = mergeTwoLists(l1->next, l2);
//             return l1;
//         }
//         else
//         {
//             l2->next = mergeTwoLists(l2->next, l1);
//             return l2;
//         }
//     }
// };

// 剑指 Offer II 079. 所有子集
// class Solution
// {
// public:
//     vector<vector<int>> res;
//     vector<vector<int>> subsets(vector<int> &nums)
//     {
//         res.push_back({});
//         dfs(nums, vector<int>(), 0);
//         return res;
//     }
//     void dfs(vector<int> nums, vector<int> tmp, int idx)
//     {
//         for (int i = idx; i < nums.size(); ++i)
//         {
//             tmp.push_back(nums[i]);
//             res.push_back(tmp);
//             dfs(nums, tmp, i + 1);
//             tmp.pop_back();
//         }
//     }
// };

// 剑指 Offer II 080. 含有 k 个元素的组合
// class Solution
// {
// public:
//     vector<vector<int>> res;
//     vector<vector<int>> combine(int n, int k)
//     {
//         dfs(n, k, 1, vector<int>());
//         return res;
//     }
//     void dfs(int n, int k, int idx, vector<int> path)
//     {
//         if (path.size() == k)
//         {
//             res.push_back(path);
//             path.clear();
//         }
//         else
//         {
//             for (int i = idx; i <= n; ++i)
//             {
//                 path.push_back(i);
//                 dfs(n, k, i + 1, path);
//                 path.pop_back();
//             }
//         }
//     }
// };

// 剑指 Offer II 081. 允许重复选择元素的组合
// class Solution
// {
// public:
//     vector<vector<int>> res;
//     vector<int> path;
//     vector<vector<int>> combinationSum(vector<int> &candidates, int target)
//     {
//         dfs(candidates, 0, candidates.size(), target, 0);
//         return res;
//     }

//     void dfs(vector<int>& candis, int idx, int n, int target, int CurSum)
//     {
//         if (idx == n || CurSum > target)
//             return;
//         if (CurSum == target)
//         {
//             res.push_back(path);
//         }

//         for (int i = idx; i < n; ++i)
//         {
//             path.push_back(candis[i]);
//             dfs(candis, i, n, target, candis[i] + CurSum);
//             path.pop_back();
//         }
//     }
// };

// 剑指 Offer II 082. 含有重复元素集合的组合
// class Solution
// {
// public:
//     vector<vector<int>> res;
//     vector<int> path;
//     vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
//     {
//         sort(candidates.begin(), candidates.end());
//         dfs(candidates, 0, candidates.size(), 0, target);
//         return res;
//     }

//     void dfs(vector<int> &candis, int idx, int n, int CurSum, int target)
//     {
//         if (idx > n || CurSum > target)
//             return;
//         if (CurSum == target)
//             res.push_back(path);

//         for (int i = idx; i < n; ++i)
//         {
//             if (i > idx && candis[i] == candis[i - 1])
//                 continue;
//             path.push_back(candis[i]);
//             dfs(candis, i + 1, n, CurSum + candis[i], target);
//             path.pop_back();
//         }
//     }
// };

// 剑指 Offer II 083. 没有重复元素集合的全排列
// class Solution {
// public:
//     vector<vector<int>> res;
//     vector<int> path;
//     vector<vector<int>> permute(vector<int>& nums) {
//         dfs(nums,0);
//         return res;
//     }
// void dfs(vector<int>& nums, int idx)
// {
//     if(idx == nums.size())
//     {
//         res.push_back(path);
//         return;
//     }
//     for(int i = idx; i < nums.size(); ++i)
//     {
//         path.push_back(nums[i]);
//         swap(nums[i], nums[idx]);
//         dfs(nums, idx + 1);
//         swap(nums[i], nums[idx]);
//         path.pop_back();
//     }
// }
// };

// 剑指 Offer II 084. 含有重复元素集合的全排列
// class Solution
// {
// public:
//     vector<vector<int>> res;
//     vector<int> path;
//     vector<vector<int>> permuteUnique(vector<int> &nums)
//     {
//         sort(nums.begin(), nums.end());
//         dfs(nums, 0);
//         return res;
//     }
//     void dfs(vector<int> &nums, int idx)
//     {
//         if (idx == nums.size())
//         {
//             auto it = find(res.begin(), res.end(), path);
//             if (it == res.end())
//                 res.push_back(path);
//         }
//         for (int i = idx; i < nums.size(); ++i)
//         {
//             if (i > idx && nums[i] == nums[i - 1])
//                 continue;
//             path.push_back(nums[i]);
//             swap(nums[i], nums[idx]);
//             dfs(nums, idx + 1);
//             swap(nums[i], nums[idx]);
//             path.pop_back();
//         }
//     }
// };

// class Solution {
// public:
//     vector<int> vis;
//     vector<vector<int>> res;
//     vector<int> path;
//     vector<vector<int>> permuteUnique(vector<int>& nums) {
//         sort(nums.begin(), nums.end());
//         vis.resize(nums.size());
//         dfs(nums, 0);
//         return res;
//     }
//     void dfs(vector<int>& nums, int idx)
//     {
//         if(idx == nums.size())
//         {
//             res.emplace_back(path);
//             return;
//         }
//         for(int i = 0; i < nums.size(); ++i)
//         {
//             if(vis[i]  || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) continue;
//             path.emplace_back(nums[i]);
//             vis[i] = 1;
//             dfs(nums, idx + 1);
//             vis[i] = 0;
//             path.pop_back();
//         }
//     }
// };

// day-2024-10-31
// 剑指 Offer II 085. 生成匹配的括号
// class Solution
// {
// public:
//     vector<string> generateParenthesis(int n)
//     {
//         vector<string> ans;
//         dfs(0, 0, "", n, ans);
//         return ans;
//     }
//     void dfs(int l, int r, string s, int n, vector<string> &ans)
//     {
//         if (n == l && n == r)
//         {
//             ans.push_back(s);
//             return;
//         }
//         if (l < n)
//             dfs(l + 1, r, s + '(', n, ans);
//         if (r < l)
//             dfs(l, r + 1, s + ')', n, ans);
//     }
// };

// 剑指 Offer II 086. 分割回文子字符串
// class Solution
// {
// public:
//     vector<vector<string>> partition(string s)
//     {
//         vector<vector<string>> ans;
//         vector<string> path;
//         dfs(s, 0, ans, path);
//         return ans;
//     }
//     void dfs(string &s, int idx, vector<vector<string>> &ans, vector<string> &path)
//     {
//         if (idx == s.size())
//         {
//             ans.push_back(path);
//             return;
//         }
//         for (int i = idx; i < s.size(); ++i)
//         {
//             if (isPalindrome(s, idx, i))
//             {
//                 path.push_back(s.substr(idx, i - idx + 1));
//                 dfs(s, i + 1, ans, path);
//                 path.pop_back();
//             }
//         }
//     }
//     bool isPalindrome(string &s, int l, int r)
//     {
//         while (l < r)
//         {
//             if (s[l] != s[r])
//                 return false;
//             l++;
//             r--;
//         }
//         return true;
//     }
// };

// day-2024-11-1
// 剑指 Offer II 087. 复原 IP
// class Solution
// {
// public:
//     vector<string> restoreIpAddresses(string s)
//     {
//         vector<string> ans;
//         dfs(s, "", 0, 0, ans);
//         return ans;
//     }
//     void dfs(string &s, string path, int idx, int segments, vector<string> &ans)
//     {
//         if (segments == 4)
//         {
//             if (idx == s.size())
//             {
//                 ans.push_back(path.substr(0, path.size() - 1));
//                 return;
//             }
//         }

//         for (int len = 1; len <= 3 && idx + len <= s.size(); ++len)
//         {
//             string segment = s.substr(idx, len);
//             if (IsValid(segment))
//                 dfs(s, path + segment + '.', idx + len, segments + 1, ans);
//         }
//     }

//     bool IsValid(string &s)
//     {
//         if (s.size() > 1 && s[0] == '0')
//             return false;
//         int n = stoi(s);
//         if (n >= 0 && n <= 255)
//             return true;
//         return false;
//     }
// };

// 剑指 Offer II 088. 爬楼梯的最少成本
// class Solution
// {
// public:
//     int minCostClimbingStairs(vector<int> &cost)
//     {
//         int n = cost.size();
//         vector<int> dp(n + 1, 0);
//         dp[0] = 0;
//         dp[1] = 0;
//         for (int i = 2; i <= n; ++i)
//         {
//             dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
//             cout << dp[i - 1] + cost[i - 1] << " " << dp[i - 2] + cost[i - 2] << endl;
//         }
//         return dp[n];
//     }
//     // dp[2] = min(10, 15) = 10
//     // dp[3] = min(10 + 20, 0 + 15) = 15
// };

// 剑指 Offer II 089. 房屋偷盗
// class Solution
// {
// public:
//     int rob(vector<int> &nums)
//     {
//         int n = nums.size();
//         vector<int> dp(n, 0);
//         if (n == 1)
//             return nums[0];
//         if (n == 2)
//             return max(nums[0], nums[1]);

//         dp[0] = nums[0];
//         dp[1] = max(nums[1], nums[0]);
//         for (int i = 2; i < n; ++i)
//         {
//             dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
//         }
//         return dp[n - 1];
//     }
// };
//