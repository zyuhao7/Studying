#include <iostream>
#include <list>
using namespace std;

// day-2025-2-1
// LeetCode 234 回文链表

// 迭代法
// class Solution
// {
// public:
//     bool isPalindrome(ListNode *head)
//     {
//         ListNode *fast = head, *slow = head;
//         while (fast != nullptr && fast->next != nullptr)
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//         }
//         ListNode *newHhead = reverseList(slow);
//         ListNode *cur = head;
//         while (cur != nullptr && newHhead != nullptr)
//         {
//             if (cur->val != newHhead->val)
//                 return false;
//             cur = cur->next;
//             newHhead = newHhead->next;
//         }
//         return true;
//     }
//     ListNode *reverseList(ListNode *head)
//     {
//         if (head == nullptr)
//             return nullptr;
//         ListNode *prev = nullptr, *cur = head, *next = head->next;
//         while (cur != nullptr)
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

// 递归法
// class Solution
// {
// public:
//     bool isPalindrome(ListNode *head)
//     {
//         ListNode *front = head;
//         return check(front, head);
//     }
//     bool check(ListNode *&front, ListNode *cur)
//     {
//         // 递归终止条件
//         if (cur == nullptr)
//             return true;
//         // 递归调用
//         if (!check(front, cur->next))
//             return false;
//         // 逻辑处理
//         if (front->val != cur->val)
//             return false;
//         // 下一层递归
//         front = front->next;
//         return true;
//     }
// };

// 160. 相交链表
// class Solution
// {
// public:
//     ListNode *getIntersectionNode(ListNode *h1, ListNode *h2)
//     {
//         if (!h1 || !h2)
//             return nullptr;
//         ListNode *t1 = h1;
//         ListNode *t2 = h2;
//         while (t1 != t2)
//         {
//             if (t1 == nullptr)
//                 t1 = h2;
//             else
//                 t1 = t1->next;
//             if (t2 == nullptr)
//                 t2 = h1;
//             else
//                 t2 = t2->next;
//         }
//         return t1;
//     }
// };

// 206. 反转链表
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         if (!head)
//             return nullptr;
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

// day-2025-2-4
//  21. 合并两个有序链表
// 递归法
// class Solution
// {
// public:
//     ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
//     {
//         if (!l1)
//             return l2;
//         if (!l2)
//             return l1;
//         ListNode *dummy = new ListNode(-1);
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
//         cur->next = l1 ? l1 : l2;
//         return dummy->next;
//     }

// 递归法
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
//         if (!head || head->next == nullptr)
//             return false;
//         ListNode *fast = head, *slow = head;
//         while (fast && fast->next)
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//             if (fast == slow)
//                 return true;
//         }
//         return false;
//     }
// };
// 142. 环形链表 II
// class Solution
// {
// public:
//     ListNode *detectCycle(ListNode *head)
//     {
//         if (!head || !head->next)
//             return nullptr;
//         ListNode *slow = head;
//         ListNode *fast = head;

//         while (fast && fast->next)
//         {
//             slow = slow->next;
//             fast = fast->next->next;
//             if (slow == fast)
//                 break;
//         }
//         if (slow != fast)
//             return nullptr;

//         ListNode *p = head, *q = fast;
//         while (p != q)
//         {
//             p = p->next;
//             q = q->next;
//         }
//         return p;
//     }
// };

// 19. 删除链表的倒数第 N 个结点
// class Solution
// {
// public:
//     ListNode *removeNthFromEnd(ListNode *head, int n)
//     {
//         if (!head)
//             return nullptr;
//         ListNode *fast = head, *slow = head;
//         while (n--)
//             fast = fast->next;
//         if(!fast) return head->next;
//         while (fast->next)
//         {
//             fast = fast->next;
//             slow = slow->next;
//         }
//         ListNode *tmp = slow->next;
//         slow->next = slow->next->next;
//         delete tmp;
//         return head;
//     }
// };

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         if(head == nullptr)
//             return head;
//         head->next = removeNthFromEnd(head->next, n);
//         cnt++;
//         return cnt == n ? head->next : head;
//     }
//     int cnt = 0;
// };

// 2025-2-5
//  24. 两两交换链表中的节点
// class Solution
// {
// public:
//     ListNode *swapPairs(ListNode *head)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *cur = head->next;
//         ListNode *tmp = cur->next;
//         cur->next = head;
//         head->next = swapPairs(tmp);
//         return cur;
//     }
// };

// 2. 两数相加
// class Solution
// {
// public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         ListNode *dummy = new ListNode(-1);
//         ListNode *cur = dummy;
//         int carry = 0;
//         while (l1 || l2)
//         {
//             int t = carry;
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
//             carry = t / 10;
//             t %= 10;
//             ListNode *node = new ListNode(t);
//             cur->next = node;
//             cur = cur->next;
//         }
//         if (carry)
//         {
//             ListNode *node = new ListNode(carry);
//             cur->next = node;
//         }
//         return dummy->next;
//     }
// };

// 445. 两数相加 II
// class Solution
// {
// public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         ListNode *dummy = new ListNode(-1);
//         ListNode *cur = dummy;
//         int carry = 0;
//         l1 = reverse(l1);
//         l2 = reverse(l2);
//         while (l1 || l2 || carry)
//         {
//             int t = carry;
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
//             ListNode *node = new ListNode(t % 10);
//             carry = t / 10;
//             cur->next = node;
//             cur = cur->next;
//         }
//         return reverse(dummy->next);
//     }

//     ListNode *reverse(ListNode *head)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *tmp = reverse(head->next);
//         head->next->next = head;
//         head->next = nullptr;
//         return tmp;
//     }
// };