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

// day-2025-2-6
// 725. 分隔链表
// class Solution
// {
// public:
//     vector<ListNode *> splitListToParts(ListNode *head, int k)
//     {
//         vector<ListNode *> res(k, nullptr);
//         int len = 0;
//         ListNode *cur = head;
//         while (cur)
//         {
//             len++;
//             cur = cur->next;
//         }
//         int t = len / k;
//         int m = len % k;
//         cur = head;
//         for (int i = 0; i < k && cur; ++i)
//         {
//             res[i] = cur;
//             int n = t + (i < m ? 1 : 0);
//             for (int j = 1; j < n; ++j)
//             {
//                 cur = cur->next;
//             }
//             ListNode *next = cur->next;
//             cur->next = nullptr;
//             cur = next;
//         }
//         return res;

//         return res;
//     }
// };

// 328. 奇偶链表
// class Solution
// {
// public:
//     ListNode *oddEvenList(ListNode *head)
//     {
//         if (!head || !head->next)
//             return head;
//         ListNode *odd = head;
//         ListNode *even = head->next;
//         ListNode *evenHead = even;
//         while (even && even->next)
//         {
//             odd->next = even->next;
//             odd = odd->next;
//             even->next = odd->next;
//             even = even->next;
//         }
//         odd->next = evenHead;
//         return head;
//     }
// };

//  92. 反转链表 II
//  递归法
// class Solution
// {
// public:
//     ListNode *reverseBetween(ListNode *head, int left, int right)
//     {
//         ListNode *dummy = new ListNode(-1);
//         dummy->next = head;
//         ListNode *pre = dummy;
//         for (int i = 0; i < left - 1; ++i)
//         {
//             pre = pre->next;
//         }
//         ListNode *cur = pre->next;
//         for (int i = 0; i < right - left; ++i)
//         {
//             ListNode *tmp = cur->next;
//             cur->next = tmp->next;
//             tmp->next = pre->next;
//             pre->next = tmp;
//         }
//         return dummy->next;
//     }
// };

// day-2025-2-7
//  83. 删除排序链表中的重复元素
// class Solution {
// public:
//     ListNode* deleteDuplicates(ListNode* head) {
//         if(!head || !head->next) return head;
//         ListNode* prev = nullptr;
//         ListNode* cur = head;
//         ListNode* next = cur->next;
//         while(cur)
//         {
//             if(prev == nullptr)
//             {
//                 prev = cur;
//             }
//             while(cur && cur->val == prev->val)
//             {
//                 prev->next = next;
//                 cur = next;
//                 if(next)
//                 next = next->next;
//             }
//             prev = cur;
//             cur = next;
//             if(next)
//                 next = next->next;
//         }
//         return head;
//     }
// };

//  25. K 个一组翻转链表
// class Solution
// {
// public:
//     ListNode *reverseKGroup(ListNode *head, int k)
//     {
//         ListNode *dummy = new ListNode(-1);
//         dummy->next = head;
//         ListNode *pre = dummy;
//         ListNode *end = dummy;
//         while (end->next)
//         {
//             for (int i = 0; i < k && end; ++i)
//             {
//                 end = end->next;
//             }
//             if (!end)
//                 break;
//             ListNode *start = pre->next;
//             ListNode *next = end->next;
//             end->next = nullptr;
//             pre->next = reverse(start);
//             start->next = next;
//             pre = start;
//             end = pre;
//         }
//         return dummy->next;
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

//  86. 分隔链表

//  61. 旋转链表

//  143. 重排链表

//  138. 复制带随机指针的链表

//  147. 对链表进行插入排序

//  148. 排序链表

//  234. 回文链表

//  237. 删除链表中的节点

//  203. 移除链表元素

//  82. 删除排序链表中的重复元素 II

//  328. 奇偶链表

//  143. 重排链表
