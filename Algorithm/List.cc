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
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return nullptr;
        ListNode *prev = nullptr, *cur = head, *next = head->next;
        while (cur)
        {
            cur->next = prev;
            prev = cur;
            cur = next;
            if (next)
                next = next->next;
        }
        return prev;
    }
};