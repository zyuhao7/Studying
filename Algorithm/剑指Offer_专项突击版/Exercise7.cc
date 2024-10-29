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

int main()
{

    return 0;
}