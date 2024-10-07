#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>
using namespace std;
// day-2024-10-3
// 剑指 Offer II 016. 不含重复字符的最长子字符串
// class Solution
// {
// public:
//     int lengthOfLongestSubstring(string s)
//     {
//         unordered_map<char, int> mp;

//         int l = 0, r = 0, maxLen = 0;
//         while (r < s.size())
//         {
//             if (!mp[s[r]])
//             {
//                 mp[s[r++]]++;
//                 maxLen = max(maxLen, r - l);
//             }
//             else
//             {
//                 mp[s[l++]]--;
//             }
//         }
//         return maxLen;
//     }
// };

// 剑指 Offer II 017. 含有所有字符的最短字符串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

// class Solution
// {
// public:
//     string minWindow(string s, string t)
//     {
//         int l = 0;
//         int len1 = s.size();
//         int len2 = t.size();
//         int pos = -1;
//         int n = len2;
//         int minLen = len1 + 1;
//         unordered_map<char, int> cnt;
//         for (auto c : t)
//             cnt[c]++;
//         for (int r = 0; r < len1; ++r)
//         {
//             cnt[s[r]]--;
//             if (cnt[s[r]] >= 0)
//                 n--;

//             while (n == 0)
//             {
//                 if (r - l + 1 < minLen)
//                 {
//                     pos = l;
//                     minLen = r - l + 1;
//                 }
//                 cnt[s[l]]++;
//                 if (cnt[s[l]] > 0)
//                 {
//                     n++;
//                 }
//                 l++;
//             }
//         }
//         if (pos == -1)
//             return "";
//         return s.substr(pos, minLen);
//     }
// };

// 剑指 Offer II 018. 有效的回文
// 给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false
// class Solution
// {
// public:
//     bool isPalindrome(string s)
//     {
//         int i = 0, j = s.size() - 1;
//         while (i < j)
//         {
//             while (i < j && !isalnum(s[i]))
//             {
//                 i++;
//             }
//             while (i < j && !isalnum(s[j]))
//             {
//                 j--;
//             }
//             if (tolower(s[i]) != tolower(s[j]))
//             {
//                 return false;
//             }
//             i++;
//             j--;
//         }
//         return true;
//     }
// };

// day-2024-10-4
// 剑指 Offer II 019. 最多删除一个字符得到回文
// class Solution
// {
// public:
//     bool validPalindrome(string s)
//     {
//         auto check = [&](int i, int j)
//         {
//             for (; i < j; ++i, --j)
//             {
//                 if (s[i] != s[j])
//                     return false;
//             }
//             return true;
//         };

//         for (int i = 0, j = s.size() - 1; i < j; ++i, --j)
//         {
//             if (s[i] != s[j])
//                 return check(i + 1, j) || check(i, j - 1);
//         }
//         return true;
//     }
// };

// day-2024-10-5
// 剑指 Offer II 020. 回文子字符串的个数
// class Solution
// {
// public:
//     int countSubstrings(string s)
//     {
//         int res = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             res += extendStrings(s, i, i);     // odd
//             res += extendStrings(s, i, i + 1); // even
//         }
//         return res;
//     }

//     int extendStrings(string s, int l, int r)
//     {
//         int cnt = 0;
//         while (l >= 0 && r < s.size() && s[l] == s[r])
//         {
//             l--;
//             ++r;
//             ++cnt;
//         }
//         return cnt;
//     }
// };

// 剑指 Offer II 021. 删除链表的倒数第 n 个结点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// class Solution
// {
// public:
//     ListNode *removeNthFromEnd(ListNode *head, int n)
//     {
//         if (head->next == nullptr && n == 1)
//             return nullptr;
//         ListNode *slow = head;
//         ListNode *fast = head;
//         while (n--)
//         {
//             fast = fast->next;
//         }
//         if (!fast)
//             return head->next;

//         while (fast && fast->next)
//         {
//             fast = fast->next;
//             slow = slow->next;
//         }
//         if (slow->next)
//             slow->next = slow->next->next;

//         return head;
//     }
// };

// 剑指 Offer II 022. 链表中环的入口节点
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

// 剑指 Offer II 023. 两个链表的第一个重合节点
// class Solution
// {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
//     {
//         int lenA = 0, lenB = 0;
//         ListNode *curA = headA, *curB = headB;
//         while (curA)
//             lenA++, curA = curA->next;
//         while (curB)
//             lenB++, curB = curB->next;

//         ListNode *nodeA = headA, *nodeB = headB;
//         if (lenB > lenA)
//             nodeA = headB, nodeB = headA;
//         int gap = abs(lenA - lenB);

//         while (gap--)
//             nodeA = nodeA->next;
//         while (nodeA && nodeA != nodeB)
//         {
//             nodeA = nodeA->next;
//             nodeB = nodeB->next;
//         }
//         return nodeA;
//     }
// };

// 剑指 Offer II 024. 反转链表
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         if (!head)
//             return nullptr;
//         ListNode *prev = nullptr, *cur = head;
//         while (cur)
//         {
//             ListNode *tmp = cur->next;
//             cur->next = prev;
//             prev = cur;
//             if (tmp)
//                 cur = tmp;
//             else
//                 break;
//         }
//         return cur;
//     }
// };

// 剑指 Offer II 025. 链表中的两数相加
// class Solution
// {
// public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         ListNode *cur1 = reverseList(l1);
//         ListNode *cur2 = reverseList(l2);

//         int carry = 0;
//         ListNode *newHead = nullptr;
//         ListNode *prev = nullptr;
//         while (cur1 || cur2 || carry)
//         {
//             int sum = carry;
//             if (cur1)
//             {
//                 sum += cur1->val;
//                 cur1 = cur1->next;
//             }
//             if (cur2)
//             {
//                 sum += cur2->val;
//                 cur2 = cur2->next;
//             }
//             ListNode *newNode = new ListNode(sum % 10);
//             carry = sum / 10;
//             newNode->next = newHead;
//             newHead = newNode;
//         }
//         return newHead;
//     }

//     ListNode *reverseList(ListNode *head)
//     {
//         ListNode *prev = nullptr, *cur = head;
//         while (cur)
//         {
//             ListNode *tmp = cur->next;
//             cur->next = prev;
//             prev = cur;
//             cur = tmp;
//         }
//         return prev;
//     }
// };

// 剑指 Offer II 026. 重排链表
// class Solution
// {
// public:
//     void reorderList(ListNode *head)
//     {
//         ListNode *mid = middleNode(head);
//         ListNode *rhead = reverseList(mid);

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
//         ListNode *slow = head;
//         ListNode *fast = head;
//         while (fast && fast->next)
//         {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         return slow;
//     }

//     ListNode *reverseList(ListNode *head)
//     {
//         ListNode *prev = nullptr, *cur = head;
//         while (cur)
//         {
//             ListNode *tmp = cur->next;
//             cur->next = prev;
//             prev = cur;
//             cur = tmp;
//         }
//         return prev;
//     }
// };

// 剑指 Offer II 027. 回文链表
// class Solution
// {
// public:
//     bool isPalindrome(ListNode *head)
//     {
//         vector<int> vec;
//         while (head)
//         {
//             vec.push_back(head->val);
//             head = head->next;
//         }
//         for (int i = 0, j = vec.size() - 1; i < j; --j, ++i)
//         {
//             if (vec[i] != vec[j])
//                 return false;
//         }
//         return true;
//     }
// };
// 法二: 先找到中间节点, 然后翻转后半部分, 1 2 2 1 -> 1 2 1 2 然后再比较, 从 rhead 和 head.

// day-2024-10-7


int main()
{

    return 0;
}