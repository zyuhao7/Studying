#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <functional.hpp>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;
// 程序员面试金典
// day-2025-8-1
// 01.01 判定字符是否唯一	数组	简单
// 法1 统计字符出现次数
// class Solution
// {
// public:
//     bool isUnique(string s)
//     {
//         char dict[26] = {0};
//         for (int i = 0; i < s.size(); ++i)
//             dict[s[i] - 'a']++;
//         for (int i = 0; i < s.size(); ++i)
//             if (dict[s[i] - 'a'] > 1)
//                 return false;
//         return true;
//     }
// };
// 法2: 位运算.
// class Solution
// {
// public:
//     bool isUnique(string s)
//     {
//         // 用一个 32 位整数来记录每个字符是否出现过.
//         int a = 0;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             int x = s[i] - 'a';
//             if (a & (1 << x))
//                 return false;
//             a |= (1 << x);
//         }
//         return true;
//     }
// };

// 01.02 判定是否互为字符重排	数组,字符串	简单
// class Solution
// {
// public:
//     bool CheckPermutation(string s1, string s2)
//     {
//         if (s1.size() != s2.size())
//             return false;
//         char cnt[26] = {0};
//         for(auto& c : s1)
//             cnt[c - 'a']++;
//         for(auto&c : s2)
//             cnt[c - 'a']--;
//         for(int i = 0; i < 26; ++i)
//             if(cnt[i] != 0)
//                 return false;
//         return true;
//     }
// };

// 01.03	URL 化	字符串	简单
// class Solution
// {
// public:
//     string replaceSpaces(string s, int length)
//     {
//         string t = "";
//         for (int i = 0; i < length; ++i)
//         {
//             if (s[i] == ' ')
//                 t += "%20";
//             else
//                 t += s[i];
//         }
//         return t;
//     }
// };

// class Solution
// {
// public:
//     string replaceSpaces(string s, int length)
//     {
//         int j = s.size();
//         for (int i = length - 1; i >= 0; --i)
//         {
//             if (s[i] == ' ')
//             {
//                 s[--j] = '0';
//                 s[--j] = '2';
//                 s[--j] = '%';
//             }
//             else
//                 s[--j] = s[i];
//         }
//         return s.substr(j, s.size() - j);
//     }
// };

// 01.04	回文排列	哈希表,字符串	简单
// class Solution
// {
// public:
//     bool canPermutePalindrome(string s)
//     {
//         unordered_map<char, int> cnt;
//         for (auto &c : s)
//             cnt[c]++;
//         int odd = 0;
//         for (auto &[c, v] : cnt)
//             if (v % 2)
//                 odd++;
//         return odd <= 1;
//     }
// };

// 01.05	一次编辑	字符串,动态规划	中等
// class Solution
// {
// public:
//     bool oneEditAway(string s, string t)
//     {
//         if (t.size() > s.size())
//             swap(s, t);
//         if (s.size() - t.size() > 1)
//             return false;
//         for (int i = 0; i < t.size(); ++i)
//         {
//             if (s[i] == t[i])
//                 continue;
//             // 替换
//             if (s.size() == t.size())
//                 return s.substr(i + 1) == t.substr(i + 1);
//             // 删除/插入
//             if (s.size() > t.size())
//                 return s.substr(i + 1) == t.substr(i);
//         }
//         return true;
//     }
// };

// 01.06 字符串压缩 字符串 简单
// class Solution
// {
// public:
//     string compressString(string S)
//     {
//         string t = "";
//         for (int i = 0; i < S.size();)
//         {
//             int j = i;
//             while (j < S.size() && S[j] == S[i])
//                 j++;
//             t += S[i];
//             t += to_string(j - i);
//             i = j;
//         }
//         return t.size() < S.size() ? t : S;
//     }
// };

// 01.07	旋转矩阵	数组	中等
// class Solution
// {
// public:
//     void rotate(vector<vector<int>> &mat)
//     {
//         // 先上下翻转, 然后按次对角线对折.
//         int n = mat.size();
//         for (int i = 0; i < n / 2; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 swap(mat[i][j], mat[n - i - 1][j]); // 列不变, 行交换.
//             }
//         }
//         // 主对角线对折
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < n - i - 1; ++j)
//             {
//                 swap(mat[i][j], mat[n - j - 1][n - i - 1]);
//             }
//         }
//         // 次对角线对折.
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < i; ++j)
//             {
//                 swap(mat[i][j], mat[j][i]);
//             }
//         }
//     }
// };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// day-2025-8-3
// 面试题 01.08. 零矩阵
// class Solution
// {
// public:
//     void setZeroes(vector<vector<int>> &matrix)
//     {
//         int m = matrix.size(), n = matrix[0].size();
//         vector<int> rows(m), cols(n);
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (matrix[i][j] == 0)
//                 {
//                     rows[i] = 1;
//                     cols[j] = 1;
//                 }
//             }
//         }
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (rows[i] || cols[j])
//                     matrix[i][j] = 0;
//             }
//         }
//     }
// };

// 面试题 01.09. 字符串轮转
// class Solution
// {
// public:
//     bool isFlipedString(string s1, string s2)
//     {
//         if (s1.size() != s2.size())
//             return false;
//         s2 += s2;
//         if (s2.find(s1) != std::string::npos)
//             return true;
//         return false;
//     }
// };

// 面试题 02.01. 移除重复节点
// class Solution
// {
// public:
//     ListNode *removeDuplicateNodes(ListNode *head)
//     {
//         unordered_set<int> st;
//         ListNode *prev = nullptr, *cur = head;
//         while (cur)
//         {
//             if (st.count(cur->val))
//                 prev->next = cur->next;
//             else
//             {
//                 st.insert(cur->val);
//                 prev = cur;
//             }
//             cur = cur->next;
//         }
//         return head;
//     }
// };

// 面试题 02.02. 返回倒数第 k 个节点
// class Solution
// {
// public:
//     int kthToLast(ListNode *head, int k)
//     {
//         ListNode *fast = head;
//         ListNode *slow = head;
//         while (k--)
//             fast = fast->next;
//         while (fast)
//         {
//             fast = fast->next;
//             slow = slow->next;
//         }
//         return slow->val;
//     }
// };

// 面试题 02.03. 删除中间节点
// class Solution
// {
// public:
//     void deleteNode(ListNode *node)
//     {
//         // node是要删除的节点
//         node->val = node->next->val;
//         node->next = node->next->next;
//     }
// };

// 面试题 02.04. 分割链表
/*
    dummyNode: 哑节点, 用于处理头节点的情况.
    pre: 小于x的链表的前一个节点.
    cur: 当前节点.
*/
// class Solution
// {
// public:
//     ListNode *partition(ListNode *head, int x)
//     {
//         if (!head)
//             return nullptr;
//         ListNode *dummy = new ListNode(-1);
//         ListNode *prev = dummy;
//         ListNode *cur = head;
//         ListNode *newHead = nullptr;
//         while (cur)
//         {
//             if (cur->val < x)
//             {
//                 prev->next = cur;
//                 prev = cur;
//                 if (newHead)
//                     newHead->next = cur->next;
//             }
//             else
//             {
//                 if (!newHead)
//                 {
//                     newHead = cur;
//                     head = cur;
//                 }
//                 else
//                 {
//                     newHead->next = cur;
//                     newHead = cur;
//                 }
//                 prev->next = cur->next;
//             }
//             cur = cur->next;
//         }
//         if (newHead)
//             newHead->next = nullptr;
//         if (head->val >= x)
//             prev->next = head;
//         else
//             prev->next = nullptr;
//         ListNode *res = dummy->next;
//         delete dummy;
//         return res;
//     }
// };

// 面试题 02.05. 链表求和
// class Solution
// {
// public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         if (!l1)
//             return l2;
//         if (!l2)
//             return l1;
//         ListNode *head = nullptr;
//         ListNode *cur = nullptr;
//         int carry = 0;
//         while (l1 || l2 || carry)
//         {
//             int sum = 0;
//             if (l1)
//             {
//                 sum += l1->val;
//                 l1 = l1->next;
//             }
//             if (l2)
//             {
//                 sum += l2->val;
//                 l2 = l2->next;
//             }
//             sum += carry;
//             int val = sum % 10;
//             carry = sum / 10;
//             ListNode *node = new ListNode(val);
//             if (!head)
//             {
//                 head = node;
//                 cur = node;
//             }
//             else
//             {
//                 cur->next = node;
//                 cur = node;
//             }
//         }
//         return head;
//     }
// };

// day-2025-8-4
// 面试题 02.06. 回文链表
// class Solution
// {
// public:
//     ListNode *reverse(ListNode *head)
//     {
//         if (!head)
//             return nullptr;

//         ListNode *prev = nullptr;
//         ListNode *cur = head;
//         while (cur)
//         {
//             ListNode *next = cur->next;
//             cur->next = prev;
//             prev = cur;
//             cur = next;
//         }
//         return prev;
//     }
//     bool isPalindrome(ListNode *head)
//     {
//         if (!head || !head->next)
//             return true;
//         ListNode *fast = head, *slow = head;
//         while (fast && fast->next)
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//         }
//         fast = head;
//         slow = reverse(slow);
//         while (slow)
//         {
//             if (fast->val != slow->val)
//                 return false;
//             fast = fast->next;
//             slow = slow->next;
//         }
//         return true;
//     }
// };

// 面试题 02.07. 链表相交
// class Solution
// {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
//     {
//         if (!headA || !headB)
//             return nullptr;

//         ListNode *pA = headA, *pB = headB;

//         while (pA != pB)
//         {
//             pA = pA ? pA->next : headB;
//             pB = pB ? pB->next : headA;
//         }
//         return pA;
//     }
// };

// 面试题 02.08. 环路检测
// class Solution
// {
// public:
//     ListNode *detectCycle(ListNode *head)
//     {
//         if (!head || !head->next)
//             return nullptr;
//         ListNode *fast = head, *slow = head;
//         while (fast && fast->next)
//         {
//             fast = fast->next->next;
//             slow = slow->next;
//             if (slow == fast)
//                 break;
//         }
//         if (slow != fast)
//             return nullptr;
//         fast = head;
//         while (fast != slow)
//         {
//             fast = fast->next;
//             slow = slow->next;
//         }
//         return fast;
//     }
// };

// 面试题 03.01. 三合一
// class TripleInOne
// {
// public:
//     vector<vector<int>> st;
//     int Size;
//     TripleInOne(int stackSize)
//     {
//         Size = stackSize;
//         st.resize(3);
//     }

//     void push(int stackNum, int value)
//     {
//         if (st[stackNum].size() == Size)
//             return;
//         st[stackNum].push_back(value);
//     }

//     int pop(int stackNum)
//     {
//         if (isEmpty(stackNum))
//             return -1;
//         int top = st[stackNum][st[stackNum].size() - 1];
//         st[stackNum].pop_back();
//         return top;
//     }

//     int peek(int stackNum)
//     {
//         if (isEmpty(stackNum))
//             return -1;
//         return st[stackNum][st[stackNum].size() - 1];
//     }

//     bool isEmpty(int stackNum)
//     {
//         return st[stackNum].empty();
//     }
// };

// 面试题 03.02. 栈的最小值
// class MinStack
// {
// public:
//     /** initialize your data structure here. */
//     stack<int> st;
//     stack<int> min;
//     MinStack()
//     {
//     }

//     void push(int x)
//     {
//         st.push(x);
//         if (min.empty() || x < min.top())
//             min.push(x);
//         else
//             min.push(min.top());
//     }

//     void pop()
//     {
//         st.pop();
//         min.pop();
//     }

//     int top()
//     {
//         return st.top();
//     }

//     int getMin()
//     {
//         return min.top();
//     }
// };

// 面试题 03.03. 堆盘子
// class StackOfPlates
// {
// public:
//     int c;
//     int idx;
//     vector<vector<int>> v;

//     StackOfPlates(int cap)
//     {
//         c = cap;
//         idx = -1;
//     }

//     void push(int val)
//     {
//         if (c <= 0)
//             return;

//         // 如果没有栈或者当前栈已满，创建新栈
//         if (idx == -1 || v[idx].size() == c)
//         {
//             v.push_back({val});
//             idx++;
//         }
//         else
//             v[idx].push_back(val);
//     }

//     int pop()
//     {
//         return popAt(idx);
//     }

//     int popAt(int index)
//     {
//         if (index > idx || v.empty() || v[index].empty())
//             return -1;

//         int top = v[index].back();
//         v[index].pop_back();
//         // 如果该栈变空，删除它
//         if (v[index].empty())
//         {
//             v.erase(v.begin() + index);
//             idx--;
//         }
//         return top;
//     }
// };

// day-2025-8-5
// 面试题 03.04. 化栈为队
// class MyQueue
// {
// public:
//     /** Initialize your data structure here. */
//     stack<int> in;
//     stack<int> out;
//     MyQueue()
//     {
//     }

//     /** Push element x to the back of queue. */
//     void push(int x)
//     {
//         in.push(x);
//     }

//     /** Removes the element from in front of queue and returns that element. */
//     int pop()
//     {
//         if (out.empty())
//         {
//             while (!in.empty())
//             {
//                 out.push(in.top());
//                 in.pop();
//             }
//         }
//         int t = out.top();
//         out.pop();
//         return t;
//     }

//     /** Get the front element. */
//     int peek()
//     {
//         if (out.empty())
//         {
//             while (!in.empty())
//             {
//                 out.push(in.top());
//                 in.pop();
//             }
//         }
//         return out.top();
//     }

//     /** Returns whether the queue is empty. */
//     bool empty()
//     {
//         return out.empty() && in.empty();
//     }
// };

// 面试题 03.05. 栈排序
// class SortedStack
// {
// public:
//     stack<int> st;
//     stack<int> st2;
//     SortedStack()
//     {
//     }

//     void push(int val)
//     {
//         if (st.empty())
//             st.push(val);
//         else
//         {
//             while (!st.empty() && val > st.top())
//             {
//                 st2.push(st.top());
//                 st.pop();
//             }
//             st.push(val);
//             while (!st2.empty())
//             {
//                 st.push(st2.top());
//                 st2.pop();
//             }
//         }
//     }

//     void pop()
//     {

//         if (st.empty())
//             return;
//         st.pop();
//     }

//     int peek()
//     {
//         if (st.empty())
//             return -1;
//         return st.top();
//     }

//     bool isEmpty()
//     {
//         return st.empty();
//     }
// };

// 面试题 03.06. 动物收容所
// class AnimalShelf
// {
// public:
//     int count = 0;
//     typedef pair<int, int> pii;
//     queue<pii> cats;
//     queue<pii> dogs;

//     AnimalShelf()
//     {
//     }

//     void enqueue(vector<int> animal)
//     {
//         if (animal[1] == 0)
//             cats.push({animal[0], count++});
//         else
//             dogs.push({animal[0], count++});
//     }

//     vector<int> dequeueAny()
//     {
//         if (cats.empty() || (!dogs.empty() && dogs.front().second < cats.front().second))
//             return dequeueDog();
//         return dequeueCat();
//         return {-1, -1};
//     }

//     vector<int> dequeueDog()
//     {
//         vector<int> res{-1, -1};
//         if (dogs.empty())
//             return res;
//         res[1] = 1;
//         res[0] = dogs.front().first;
//         dogs.pop();
//         return res;
//     }

//     vector<int> dequeueCat()
//     {
//         vector<int> res{-1, -1};
//         if (cats.empty())
//             return res;
//         res[1] = 0;
//         res[0] = cats.front().first;
//         cats.pop();
//         return res;
//     }
// };

// 面试题 04.01. 节点间通路
// BFS
// class Solution
// {
// public:
//     bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start, int target)
//     {
//         vector<vector<int>> g(n);   // 邻接表 g[i] 表示从节点 i 出发的所有邻居节点
//         vector<bool> vis(n, false); // 初始化大小为n的访问标记数组

//         for (auto &e : graph)
//             g[e[0]].push_back(e[1]);

//         queue<int> q;
//         q.push(start);
//         vis[start] = true;

//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();

//             for (auto &ne : g[t])
//             {
//                 if (ne == target) // 提前检查目标节点
//                     return true;

//                 if (!vis[ne])
//                 {
//                     vis[ne] = true;
//                     q.push(ne);
//                 }
//             }
//         }

//         return false;
//     }
// };

// DFS
// class Solution
// {
// public:
//     bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start, int target)
//     {
//         vector<vector<int>> g(n);   // 邻接表 g[i] 表示从节点 i 出发的所有邻居节点
//         vector<bool> vis(n, false); // 初始化大小为n的访问标记数组

//         for (auto &e : graph)
//             g[e[0]].push_back(e[1]);

//         function<bool(int)> dfs = [&](int u) -> bool
//         {
//             if (u == target)
//                 return true;
//             vis[u] = true;
//             for (auto &ne : g[u])
//                 if (!vis[ne] && dfs(ne))
//                     return true;
//             return false;
//         };
//         return dfs(start);
//     }
// };