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

// 2025-4-11
//  160. 相交链表
// class Solution
// {
// public:
//     ListNode *getIntersectionNode(ListNode *l1, ListNode *l2)
//     {
//         if (!l1 || !l2)
//             return nullptr;
//         ListNode *t1 = l1, *t2 = l2;
//         while (t1 != t2)
//         {
//             if (t1 == nullptr)
//                 t1 = l2;
//             else
//                 t1 = t1->next;

//             if (t2 == nullptr)
//                 t2 = l1;
//             else
//                 t2 = t2->next;
//         }
//         return t1;
//     }
// };

// 234  . 回文链表
// 快慢指针 + 反转链表
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *prev, *cur = head, *next = head->next;
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
//     bool isPalindrome(ListNode *head)
//     {
//         if (!head || !head->next)
//             return true;
//         ListNode *fast = head, *slow = head;
//         ListNode *prev = nullptr;
//         while (fast && fast->next)
//         {
//             prev = slow;
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         prev->next = nullptr;
//         ListNode *rhead = reverseList(slow);
//         ListNode *cur = head;
//         while (cur)
//         {
//             if (cur->val != rhead->val)
//                 return false;
//             cur = cur->next;
//             rhead = rhead->next;
//         }
//         return true;
//     }
// };

// 递归
// class Solution
// {
// public:
//     bool checkPalindrome(ListNode *&front, ListNode *cur)
//     {
//         if (cur == nullptr)
//             return true;
//         if (!checkPalindrome(front, cur->next))
//             return false;
//         if (front->val != cur->val)
//             return false;
//         front = front->next;
//         return true;
//     }

//     bool isPalindrome(ListNode *head)
//     {
//         return checkPalindrome(head, head);
//     }
// };

// day-2025-4-12
//
// 143  重排链表
// class Solution
// {
// public:
//     void reorderList(ListNode *head)
//     {
//         ListNode *mid = middleNode(head);
//         ListNode *rhead = ReverseList(mid);
//         while (rhead->next)
//         {
//             ListNode *tmp = head->next;
//             ListNode *tmp2 = rhead->next;
//             head->next = rhead;
//             rhead->next = tmp;
//             head = tmp;
//             rhead = tmp2;
//         }
//     }

//     ListNode *middleNode(ListNode *head)
//     {
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next)
//         {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         return slow;
//     }

//     ListNode *ReverseList(ListNode *head)
//     {
//         ListNode *prev = nullptr, *cur = head, *next = head->next;
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

//  86. 分隔链表
// class Solution
// {
// public:
//     ListNode *partition(ListNode *head, int x)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *dummy = new ListNode(0);
//         ListNode *tail = dummy;
//         ListNode *rhead = nullptr;
//         ListNode *high = nullptr;
//         ListNode *cur = head;
//         while (cur)
//         {
//             ListNode *next = cur->next;
//             cur->next = nullptr;
//             if (cur->val < x)
//             {
//                 tail->next = cur;
//                 tail = cur;
//             }
//             else
//             {
//                 if (!high)
//                 {
//                     high = cur;
//                     rhead = cur;
//                 }
//                 else
//                 {
//                     high->next = cur;
//                     high = cur;
//                 }
//             }
//             cur = next;
//         }

//         tail->next = rhead;
//         return dummy->next;
//     }
// };

// 2025-4-13
// 2 . 两数相加
// class Solution
// {
// public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         int carry = 0;
//         ListNode *dummy = new ListNode(-1);
//         ListNode *cur = dummy;
//         while (l1 || l2)
//         {
//             int t = 0;
//             if (l1)
//             {
//                 t += l1->val;
//                 l1 = l1->next;
//             }
//             if (l2)
//             {
//                 t += l2->val;
//                 l2 = l2->next;
//             }
//             t += carry;
//             carry = t / 10;
//             ListNode *node = new ListNode(t % 10);
//             cur->next = node;
//             cur = node;
//         }
//         if (carry)
//         {
//             ListNode *node = new ListNode(1);
//             cur->next = node;
//         }
//         return dummy->next;
//     }
// };

// 142 . 环形链表 II
// class Solution
// {
// public:
//     ListNode *detectCycle(ListNode *head)
//     {
//         if (!head || !head->next)
//             return nullptr;

//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next)
//         {
//             slow = slow->next;
//             fast = fast->next->next;
//             if (slow == fast)
//                 break;
//         }
//         if (slow != fast)
//             return nullptr;
//         ListNode *p = slow, *q = head;
//         while (p != q)
//         {
//             q = q->next;
//             p = p->next;
//         }
//         return p;
//     }
// };

// f = 2s
// f = s + nb
// f = 2nb, s = nb
// k = a + nb => s = nb => s 还需要 a 步
// h 走 a 步到环入口正好和 slow 相遇

// day-2025-5-8
// 82. 删除排序链表中的重复元素 II
// class Solution {
//     public:
//         ListNode* deleteDuplicates(ListNode* head) {
//             if(!head) return nullptr;
//             ListNode* dummyNode = new ListNode(-1);
//             dummyNode->next = head;
//             ListNode* prev = dummyNode;
//             ListNode* cur = head;
//             while(cur)
//             {
//                 if(cur->next && cur->val == cur->next->val)
//                 {
//                     int v = cur->val;
//                     while(cur && cur->val == v)
//                     {
//                         ListNode* tmp = cur;
//                         cur = cur->next;
//                         delete tmp;
//                     }
//                     prev->next = cur;
//                 }
//                 else
//                 {
//                     prev  = cur;
//                     cur = cur->next;
//                 }
//             }
//             ListNode* res = dummyNode->next;
//             delete dummyNode;
//             return res;
//         }
//     };

// 83. 删除排序链表中的重复元素
// class Solution
// {
// public:
//     ListNode *deleteDuplicates(ListNode *head)
//     {
//         if (!head)
//             return head;
//         ListNode *prev = head;
//         ListNode *cur = head->next;
//         while (cur)
//         {
//             if (cur->val == prev->val)
//                 prev->next = cur->next;
//             else
//                 prev = cur;
//             cur = cur->next;
//         }
//         return head;
//     }
// };