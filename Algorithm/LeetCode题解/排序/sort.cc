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

// 148 链表排序 (归并思想)
// class Solution
// {
// public:
//     ListNode *sortList(ListNode *head)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *slow = head, *fast = head;
//         while (fast->next && fast->next->next)
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//         }
//         ListNode *mid = slow->next;
//         slow->next = nullptr;
//         ListNode *left = sortList(head);
//         ListNode *right = sortList(mid);
//         return merge(left, right);
//     }

//     ListNode *merge(ListNode *l1, ListNode *l2)
//     {
//         if (!l1)
//             return l2;
//         if (!l2)
//             return l1;
//         ListNode *dummy = new ListNode(0);
//         ListNode *cur = dummy;
//         while (l1 && l2)
//         {
//             if (l1->val < l2->val)
//             {
//                 cur->next = l1;
//                 l1 = l1->next;
//             }
//             else
//             {
//                 cur->next = l2;
//                 l2 = l2->next;
//             }
//             cur = cur->next;
//         }
//         if (l1)
//             cur->next = l1;
//         if (l2)
//             cur->next = l2;
//         return dummy->next;
//     }
// };
