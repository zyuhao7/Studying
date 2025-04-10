#include <iostream>
using namespace std;

// day-2025-4-10
//  206. 反转链表
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         if (head == nullptr)
//             return nullptr;
//         ListNode *prev = nullptr, *cur = head, *next = cur->next;
//         while (cur)
//         {
//             cur->next = prev;
//             prev = cur;
//             cur = next;
//             if (next)
//                 next = next->next;
//         }
//         return prev;
//     }
// };

// 21. 合并两个有序链表
// 迭代
// class Solution
// {
// public:
//     ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
//     {
//         if (!list1)
//             return list2;
//         if (!list2)
//             return list1;
//         ListNode *head = nullptr;
//         if (list1->val < list2->val)
//         {
//             head = list1;
//             list1 = list1->next;
//         }
//         else
//         {
//             head = list2;
//             list2 = list2->next;
//         }
//         ListNode *tmp = head;
//         while (list1 && list2)
//         {
//             if (list1->val < list2->val)
//             {
//                 tmp->next = list1;
//                 list1 = list1->next;
//             }
//             else
//             {
//                 tmp->next = list2;
//                 list2 = list2->next;
//             }
//             tmp = tmp->next;
//         }
//         if (list1)
//             tmp->next = list1;
//         if (list2)
//             tmp->next = list2;
//         return head;
//     }
// };

// 递归
// class Solution
// {
// public:
//     ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
//     {
//         if (!l1)
//             return l2;
//         if (!l2)
//             return l1;
//         if (l1->val < l2->val)
//         {
//             l1->next = mergeTwoLists(l1->next, l2);
//             return l1;
//         }
//         else
//         {
//             l2->next = mergeTwoLists(l1, l2->next);
//             return l2;
//         }
//     }
// };

// 141. 环形链表
// class Solution
// {
// public:
//     bool hasCycle(ListNode *head)
//     {
//         if (!head || !head->next)
//             return false;
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next)
//         {
//             slow = slow->next;
//             fast = fast->next->next;
//             if (slow == fast)
//                 return true;
//         }
//         return false;
//     }
// };

// 19. 删除链表的倒数第 N 个结点
// class Solution
// {
// public:
//     ListNode *removeNthFromEnd(ListNode *head, int n)
//     {
//         if (head->next == nullptr)
//             return nullptr;
//         ListNode *slow = head, *fast = head;
//         while (n > 1 && fast)
//         {
//             fast = fast->next;
//             n--;
//         }
//         ListNode *prev = nullptr;
//         while (fast && fast->next)
//         {
//             prev = slow;
//             slow = slow->next;
//             fast = fast->next;
//         }
//         if (prev)
//         {
//             prev->next = slow->next;
//             return head;
//         }
//         return head->next;
//     }
// };