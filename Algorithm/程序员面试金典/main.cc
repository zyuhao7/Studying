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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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

// day-2025-8-6
// 面试题 04.02. 最小高度树
// class Solution
// {
// public:
//     TreeNode *CreateTree(vector<int> &nums, int l, int r)
//     {
//         if (l > r)
//             return nullptr;
//         int m = (l + r) >> 1;
//         TreeNode *node = new TreeNode(nums[m]);
//         node->left = CreateTree(nums, l, m - 1);
//         node->right = CreateTree(nums, m + 1, r);
//         return node;
//     }
//     TreeNode *sortedArrayToBST(vector<int> &nums)
//     {
//         if (nums.empty())
//             return nullptr;
//         return CreateTree(nums, 0, nums.size() - 1);
//     }
// };

// 面试题 04.03. 特定深度节点链表
// 等价于层序遍历
// class Solution
// {
// public:
//     vector<ListNode *> listOfDepth(TreeNode *tree)
//     {
//         vector<ListNode *> vec;
//         queue<TreeNode *> q;
//         q.push(tree);
//         while (!q.empty())
//         {
//             ListNode *head = new ListNode(-1);
//             ListNode *cur = head;
//             int Size = q.size();
//             for (int i = 0; i < Size; ++i)
//             {
//                 TreeNode *t = q.front();
//                 q.pop();
//                 cur->next = new ListNode(t->val);
//                 if (t->left)
//                     q.push(t->left);
//                 if (t->right)
//                     q.push(t->right);
//                 cur = cur->next;
//             }
//             vec.push_back(head->next);
//         }
//         return vec;
//     }
// };

// 面试题 04.04. 检查平衡性
// class Solution
// {
// public:
//     int DFS(TreeNode *root)
//     {
//         if (root == nullptr)
//             return 0;
//         int leftDepth = DFS(root->left);
//         int rightDepth = DFS(root->right);
//         return max(leftDepth, rightDepth) + 1;
//     }
//     bool isBalanced(TreeNode *root)
//     {
//         if (!root)
//             return true;
//         int leftDepth = DFS(root->left);
//         int rightDepth = DFS(root->right);
//         return abs(leftDepth - rightDepth) <= 1 && isBalanced(root->left) && isBalanced(root->right);
//     }
// };

// 面试题 04.05. 合法二叉搜索树
// 前序
// class Solution
// {
// public:
//     bool isValidBST(TreeNode *root, long long left = LONG_MIN, long long right = LONG_MAX)
//     {
//         if (!root)
//             return true;
//         int x = root->val;
//         return left < x && x < right && isValidBST(root->left, left, x) && isValidBST(root->right, x, right);
//     }
// };

// 中序
// class Solution
// {
// public:
//     long long prev = LONG_MIN;
//     bool isValidBST(TreeNode *root)
//     {
//         if (!root)
//             return true;
//         if (!isValidBST(root->left) || root->val <= prev)
//             return false;
//         prev = root->val;
//         return isValidBST(root->right);
//     }
// };
// 后序
// class Solution
// {
// public:
//     pair<long, long> dfs(TreeNode *node)
//     {
//         if (!node)
//             return {LONG_MAX, LONG_MIN};
//         auto [l_min, l_max] = dfs(node->left);
//         auto [r_min, r_max] = dfs(node->right);
//         long x = node->val;
//         if (x <= l_max || x >= r_min)
//             return {LONG_MIN, LONG_MAX};
//         return {min(l_min, x), max(r_max, x)};
//     }
//     bool isValidBST(TreeNode *root)
//     {
//         return dfs(root).second != LONG_MAX;
//     }
// };

// 面试题 04.06. 后继者
// class Solution
// {
// public:
//     TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
//     {

//         TreeNode *ans = nullptr;
//         while (root)
//         {
//             if (root->val > p->val)
//             {
//                 ans = root;
//                 root = root->left;
//             }
//             else
//                 root = root->right;
//         }
//         return ans;
//     }
// };

// 面试题 04.08. 首个共同祖先 mid
// class Solution
// {
// public:
//     TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
//     {
//         if (!root || root == p || root == q)
//             return root;
//         TreeNode *left = lowestCommonAncestor(root->left, p, q);
//         TreeNode *right = lowestCommonAncestor(root->right, p, q);
//         if (!left)
//             return right;
//         if (!right)
//             return left;
//         return root;
//     }
// };
#include <deque>
// 面试题 04.09. 二叉搜索树序列 hard
// class Solution
// {
// public:
//     void dfs(deque<TreeNode *> &dq, vector<int> &path, vector<vector<int>> &ans)
//     {
//         if (dq.empty())
//         {
//             ans.push_back(path);
//             return;
//         }
//         int Size = dq.size();
//         for (int i = 0; i < Size; ++i)
//         {
//             TreeNode *t = dq.front();
//             dq.pop_front();
//             // 将当前值加入路径

//             path.push_back(t->val);
//             if (t->left)
//                 dq.push_back(t->left);
//             if (t->right)
//                 dq.push_back(t->right);
//             // 递归
//             dfs(dq, path, ans);
//             // 回溯
//             if (t->left)
//                 dq.pop_back();
//             if (t->right)
//                 dq.pop_back();
//             dq.push_back(t);
//             path.pop_back();
//         }
//     }
//     vector<vector<int>> BSTSequences(TreeNode *root)
//     {
//         vector<vector<int>> ans;
//         if (!root)
//             return {{}};
//         vector<int> path;
//         deque<TreeNode *> dq;
//         dq.push_back(root);

//         dfs(dq, path, ans);
//         return ans;
//     }
// };

// 面试题 04.10. 检查子树 mid
// class Solution
// {
// public:
//     bool isSubTtree(TreeNode *t1, TreeNode *t2)
//     {
//         if (!t2 && !t1)
//             return true;
//         if (!t1 || !t2)
//             return false;
//         return t1->val == t2->val && isSubTtree(t1->left, t2->left) && isSubTtree(t1->right, t2->right);
//     }
//     bool checkSubTree(TreeNode *t1, TreeNode *t2)
//     {
//         if (!t1)
//             return false;
//         if (isSubTtree(t1, t2))
//             return true;
//         return checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
//     }
// };

// 面试题 04.12. 求和路径 mid
// class Solution
// {
// public:
//     int pathSum(TreeNode *root, int sum)
//     {
//         if (!root)
//             return 0;
//         return dfs(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
//     }
//     int dfs(TreeNode *root, int sum)
//     {
//         if (!root)
//             return 0;
//         sum -= root->val;
//         return (sum == 0) + dfs(root->left, sum) + dfs(root->right, sum);
//     }
// };

// 面试题 05.01. 插入
// class Solution
// {
// public:
//     int insertBits(int N, int M, int i, int j)
//     {
//         for (int k = i; k <= j; ++k)
//         {
//             N &= ~(1 << k);
//         }
//         return N | (M << i);
//     }
// };

// class Solution
// {
// public:
//     int insertBits(int N, int M, int i, int j)
//     {
//         for (int k = i; k <= j; ++k)
//         {
//             N = (N & ~(1 << k)) | (((M >> (k - i)) & 1) << k);
//         }
//         return N;
//     }
// };

// day-2025-8-8
// 面试题 05.02. 二进制数转字符串 mid
// class Solution
// {
// public:
//     string printBin(double num)
//     {
//         string ans = "0.";
//         while (num > 0 && ans.size() <= 32)
//         {
//             num *= 2;
//             int t = num;
//             ans += to_string(t);
//             num -= t;
//         }
//         return ans.size() > 32 ? "ERROR" : ans;
//     }
// };

// 面试题 05.03. 翻转数位 mid  to review
// class Solution
// {
// public:
//     int reverseBits(int num)
//     {
//         int current = 0, reverse = 0;
//         int ans = 0;
//         for (int i = 0; i < 32; ++i)
//         {
//             if (num & 1)
//             {
//                 current++;
//                 reverse++;
//             }
//             else
//             {
//                 reverse = current + 1;
//                 current = 0;
//             }
//             ans = max(ans, reverse);
//             if (!num)
//                 break;
//             num >>= 1;
//         }
//         return ans;
//     }
// };

// 面试题 05.04. 下一个数 mid
// class Solution
// {
// public:
//     int cntBits(long long x)
//     {
//         long long cnt = 0;
//         while (x)
//         {
//             if (x & 1)
//                 cnt++;
//             x >>= 1;
//         }
//         return cnt;
//     }
//     vector<int> findClosedNumbers(int num)
//     {
//         vector<int> ans(2, -1);
//         long long x = 0;
//         if (num == INT_MAX)
//         {
//             ans[0] = -1;
//         }
//         else
//         {
//             x = num + 1;
//             while (true)
//             {
//                 if (cntBits(x) == cntBits((long long)num))
//                 {
//                     ans[0] = x;
//                     break;
//                 }
//                 x++;
//             }
//         }

//         if (num == 1 || num == INT_MAX)
//         {
//             ans[1] = -1;
//             return ans;
//         }
//         x = num - 1;
//         while (true)
//         {
//             if (cntBits(x) == cntBits((long long)num))
//             {
//                 ans[1] = x;
//                 break;
//             }
//             x--;
//         }
//         return ans;
//     }
// };

// 面试题 05.06. 整数转换
// class Solution
// {
// public:
//     int convertInteger(int A, int B)
//     {
//         int ans = 0;
//         for (int i = 0; i < 32; ++i)
//         {
//             ans += (A & 1) != (B & 1);
//             A >>= 1;
//             B >>= 1;
//             if (!A && !B)
//                 return ans;
//         }
//         return ans;
//     }
// };

// 面试题 05.07. 配对交换
// class Solution
// {
// public:
//     int exchangeBits(int num)
//     {
//         // 奇数
//         int odd = num & 0x55555555;
//         // 偶数
//         int even = num & 0xaaaaaaaa;
//         odd = odd << 1;
//         even = even >> 1;
//         return odd | even;
//     }
// };

// day-2025-8-9
// 面试题 05.08. 绘制直线 mid to review
// class Solution
// {
// public:
//     vector<int> drawLine(int length, int w, int x1, int x2, int y)
//     {
//         vector<int> ans(length, 0);
//         int start = x1 + y * w;
//         int end = x2 + y * w;
//         for (int i = start; i <= end; ++i)
//         {
//             int idx = i / 32;
//             int offset = 31 - (i % 32);
//             ans[idx] |= (1 << offset);
//         }
//         return ans;
//     }
// };

// 面试题 08.01. 三步问题
// class Solution
// {
// public:
//     int waysToStep(int n)
//     {
//         if (n <= 2)
//             return n;
//         vector<int> dp(n + 1, 0);
//         dp[1] = 1;
//         dp[2] = 2;
//         dp[3] = 4;
//         for (int i = 4; i <= n; ++i)
//         {
//             dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % 1000000007;
//         }
//         return dp[n];
//     }
// };

// 面试题 08.02. 迷路的机器人 mid
// class Solution
// {
// public:
//     vector<vector<int>> pathWithObstacles(vector<vector<int>> &obs)
//     {
//         vector<vector<int>> ans;
//         if (obs.empty() || obs[0].empty() || obs[0][0] == 1)
//             return ans;
//         int m = obs.size(), n = obs[0].size();
//         vector<vector<bool>> dp(m, vector<bool>(n, false)); // dp[i][j] 表示 (i,j) 是否可达
//         dp[0][0] = true;                                    // 起点可达
//         // 初始化第一行和第一列
//         for (int j = 1; j < n && !obs[0][j]; ++j)
//             dp[0][j] = dp[0][j - 1];
//         for (int i = 1; i < m && !obs[i][0]; ++i)
//             dp[i][0] = dp[i - 1][0];
//         for (int i = 1; i < m; ++i)
//         {
//             for (int j = 1; j < n; ++j)
//             {
//                 if (obs[i][j] == 0)
//                 {
//                     dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
//                 }
//             }
//         }
//         if (!dp[m - 1][n - 1])
//             return ans; // 终点不可达
//         // 回溯路径
//         int i = m - 1, j = n - 1;
//         stack<pair<int, int>> st;
//         while (i >= 0 && j >= 0)
//         {
//             st.push({i, j});
//             if (i == 0 && j == 0)
//                 break;
//             if (i > 0 && dp[i - 1][j])
//                 --i; // 优先向上走
//             else
//                 --j; // 否则向左走
//         }
//         while (!st.empty())
//         {
//             ans.push_back({st.top().first, st.top().second});
//             st.pop();
//         }
//         return ans;
//     }
// };

// 面试题 08.03. 魔术索引
// class Solution
// {
// public:
//     int findMagicIndex(vector<int> &nums)
//     {
//         for (int i = 0; i < nums.size(); ++i)
//             if (nums[i] == i)
//                 return i;
//         return -1;
//     }
// };

// class Solution
// {
// public:
//     int findMagicIndex(vector<int> &nums)
//     {
//         function<int(int, int)> dfs = [&](int i, int j)
//         {
//             if (i > j)
//                 return -1;
//             int m = i + j >> 1;
//             int l = dfs(i, m - 1);
//             if (l != -1)
//                 return l;
//             if (nums[m] == m)
//                 return m;
//             return dfs(m + 1, j);
//         };
//         return dfs(0, nums.size() - 1);
//     }
// };

// 面试题 08.04. 幂集 mid
// class Solution
// {
// public:
//     vector<vector<int>> ans;
//     vector<int> path;
//     void dfs(vector<int> &nums, int index, int n)
//     {
//         if (index >= n)
//         {
//             if (!path.empty())
//                 ans.push_back(path);
//             return;
//         }
//         ans.push_back(path);

//         for (int i = index; i < n; ++i)
//         {
//             path.push_back(nums[i]);
//             dfs(nums, i + 1, n);
//             path.pop_back();
//         }
//     }
//     vector<vector<int>> subsets(vector<int> &nums)
//     {
//         dfs(nums, 0, nums.size());
//         return ans;
//     }
// };

// day-2025-8-10
// 面试题 08.05. 递归乘法 mid
// class Solution
// {
// public:
//     int multiply(int A, int B)
//     {
//         if (A == 0 || B == 0)
//             return 0;
//         if (A == 1)
//             return B;
//         if (B == 1)
//             return A;
//         int ans = 0;
//         for (int i = 0; i < A; ++i)
//             ans += B;
//         return ans;
//     }
// };
// class Solution
// {
// public:
//     int multiply(int A, int B)
//     {
//         if (B == 1)
//             return A;
//         // 如果 B 为奇数, 将 B 右移一位, 然后递归调用函数, 将最后结果左移一位加上 A
//         if (B & 1)
//             return (multiply(A, B >> 1) << 1) + A * 1;
//         else // 否则不需要加 A
//             return multiply(A, B >> 1) << 1;
//     }
// };

// 面试题 08.06. 汉诺塔问题
// class Solution {
// public:
//     void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
//         int n = A.size();
//         dfs(n, A, B, C);
//     }
//     void dfs(int n, vector<int>& A, vector<int>& B, vector<int>& C)
//     {
//         // 如果 A柱上只有一个值, 直接移到 C
//         if(n == 1)
//         {
//             C.push_back(A.back());
//             A.pop_back();
//             return;
//         }
//         // 否则, 先用 B 存放 A 的值
//         dfs(n - 1,A, C, B);
//         // 将 A 的值加入到 C
//         C.push_back(A.back());
//         A.pop_back();
//         // 将 B 作为 A, 继续
//         dfs(n - 1, B, A, C);
//     }
// };

// 面试题 08.07. 无重复字符串的排列组合 mid
// 需要 vis 数组
// class Solution
// {
// public:
//     vector<string> ans;
//     string str;
//     void dfs(string &S,  vector<bool> &vis, int n)
//     {
//         if (str.size() == n)
//         {
//             ans.emplace_back(str);
//             return;
//         }
//         for (int i = 0; i < n; ++i)
//         {
//             if (vis[i])
//                 continue;
//             vis[i] = true;
//             str += S[i];
//             dfs(S, vis, n);
//             str.pop_back();
//             vis[i] = false;
//         }
//     }
//     vector<string> permutation(string S)
//     {
//         vector<bool> vis(S.size(), 0);
//         dfs(S, vis, S.size());
//         return ans;
//     }
// };

// 交换代替 vis 数组
// class Solution
// {
// public:
//     vector<string> permutation(string S)
//     {
//         vector<string> res;
//         backtrack(res, S, 0);
//         return res;
//     }

//     void backtrack(vector<string> &res, string &S, int start)
//     {
//         if (start == S.size())
//         {
//             res.push_back(S);
//             return;
//         }
//         for (int i = start; i < S.size(); i++)
//         {
//             swap(S[start], S[i]);
//             backtrack(res, S, start + 1);
//             swap(S[start], S[i]);
//         }
//     }
// };

// 面试题 08.08. 有重复字符串的排列组合 mid
// class Solution
// {
// public:
//     vector<string> ans;
//     string str;
//     void backtrack(string &S, vector<bool> &vis, int n)
//     {
//         if (str.size() == n)
//         {
//             ans.emplace_back(str);
//             return;
//         }
//         for (int i = 0; i < n; ++i)
//         {
//             // 剪枝条件：
//             // 1. 如果当前字符已被使用，跳过
//             // 2. 如果当前字符与前一个字符相同，且前一个字符未被使用，跳过（避免重复）
//             if (vis[i] || (i > 0 && S[i] == S[i - 1] && !vis[i - 1]))
//                 continue;
//             vis[i] = true;
//             str += S[i];
//             backtrack(S, vis, n);
//             str.pop_back();
//             vis[i] = false;
//         }
//     }
//     vector<string> permutation(string S)
//     {
//         sort(S.begin(), S.end());
//         vector<bool> vis(S.size(), 0);
//         backtrack(S, vis, S.size());
//         return ans;
//     }
// };

// 面试题 08.09. 括号 mid
// class Solution {
// public:
//     vector<string> ans;
//     void backTrack(int n, string path, int left, int right)
//     {
//         if(path.size() == n * 2)
//         {
//             ans.push_back(path);
//             return;
//         }

//         if(left > 0)
//           backTrack(n, path + '(', left - 1, right);
//          if(right > left)
//           backTrack(n, path + ')', left, right - 1);

//     }
//     vector<string> generateParenthesis(int n) {
//         backTrack(n, "", n, n);
//         return ans;
//     }
// };

// class Solution
// {
// public:
//     vector<string> res;
//     vector<string> generateParenthesis(int n)
//     {
//         backtrack("", 0, 0, n);
//         return res;
//     }
//     void backtrack(string str, int left, int right, int n)
//     {
//         if (str.size() == n * 2)
//         {
//             res.emplace_back(str);
//             return;
//         }
//         if (left < n)
//             backtrack(str + '(', left + 1, right, n);
//         if (right < left)
//             backtrack(str + ')', left, right + 1, n);
//     }
// };

// 2025.8.11
// 面试题 08.10. 颜色填充
// BFS
// class Solution
// {
// public:
//     vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//     vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
//     {
//         queue<pair<int, int>> q;
//         int m = image.size(), n = image[0].size();
//         vector<vector<bool>> vis(m, vector<bool>(n, false));
//         q.push({sr, sc});
//         int color = image[sr][sc];
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             int x = t.first;
//             int y = t.second;
//             vis[x][y] = true;
//             image[x][y] = newColor;

//             for (int i = 0; i < 4; ++i)
//             {
//                 int dx = t.first + dirs[i][0];
//                 int dy = t.second + dirs[i][1];
//                 if (dx >= 0 && dx < m && dy >= 0 && dy < n && !vis[dx][dy] && image[dx][dy] == color)
//                 {
//                     q.push({dx, dy});
//                 }
//             }
//         }
//         return image;
//     }
// };

// DFS
// class Solution {
// public:
//     vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
//         int m = image.size(), n = image[0].size();
//         int color = image[sr][sc];
//         int dirs[5] = {-1, 0, 1, 0, -1};
//         function<void(int, int)> dfs = [&](int i, int j){
//             if(i < 0 || i >= m || j < 0 || j >= n || image[i][j] != color || image[i][j] == newColor)
//                 return;

//             image[i][j] = newColor;
//             for(int k = 0; k < 4; ++k)
//             {
//                 dfs(i + dirs[k], j + dirs[k + 1]);
//             }
//         };
//         dfs(sr, sc);
//         return image;
//     }
// };

// 面试题 08.11. 硬币 mid
// class Solution
// {
// public:
//     int waysToChange(int n)
//     {
//         int mod = 1000000007;
//         vector<int> dp(n + 1);
//         vector<int> coins = {25, 10, 5, 1};
//         dp[0] = 1;
//         for (auto coin : coins)
//         {
//             for (int j = coin; j <= n; ++j)
//                 dp[j] = (dp[j] + dp[j - coin]) % mod;
//         }
//         return dp[n];
//     }
// };

// 面试题 08.12. 八皇后 hard
// class Solution
// {
// public:
//     vector<vector<string>> ans;
//     vector<string> board;
//     vector<vector<string>> solveNQueens(int n)
//     {
//         board.resize(n, string(n, '.'));
//         backtrack(0, n);
//         return ans;
//     }
//     void backtrack(int r, int n)
//     {
//         if (r == n)
//         {
//             ans.push_back(board);
//             return;
//         }
//         for (int c = 0; c < n; ++c)
//         {
//             if (isValid(board, r, c, n))
//             {
//                 board[r][c] = 'Q';
//                 backtrack(r + 1, n);
//                 board[r][c] = '.';
//             }
//         }
//     }

//     bool isValid(vector<string> &board, int r, int c, int n)
//     {
//         //[. . . .]
//         //[. . . .]
//         //[. . Q .]
//         //[. . . .]
//         // 先检查 Q 同列前面行的数据
//         for (int i = 0; i < r; ++i)
//         {
//             if (board[i][c] == 'Q')
//                 return false;
//         }
//         // 再检查正对角线
//         for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; --j, --i)
//         {
//             if (board[i][j] == 'Q')
//                 return false;
//         }
//         // 反对角线
//         for (int i = r - 1, j = c + 1; i >= 0 && j < n; ++j, --i)
//         {
//             if (board[i][j] == 'Q')
//                 return false;
//         }
//         return true;
//     }
// };

// 面试题 08.13. 堆箱子 hard
// class Solution
// {
// public:
//     int pileBox(vector<vector<int>> &box)
//     {
//         // 按照体积排序
//         int n = box.size();
//         sort(box.begin(), box.end(), [&](auto &a, auto &b)
//              { return a[0] + a[1] + a[2] < b[0] + b[1] + b[2]; });
//         vector<int> dp(3001, 0);
//         int res = 0;
//         for (int i = 0; i < n; ++i)
//         {
//             dp[i] = box[i][2];
//             for (int j = 0; j < i; ++j)
//             {
//                 if (box[i][0] > box[j][0] && box[i][1] > box[j][1] && box[i][2] > box[j][2])
//                 {
//                     dp[i] = max(dp[i], dp[j] + box[i][2]);
//                 }
//             }
//             res = max(res, dp[i]);
//         }
//         return res;
//     }
// };

// 面试题 08.14. 布尔运算 mid
/*
    使用三维动态规划数组 dp[i][j][k] ：
    - i 和 j 表示子表达式的起始和结束索引
    - k 表示计算结果（0 或 1）
    - dp[i][j][k] 表示从索引 i 到 j 的子表达式计算结果为 k 的方法数
*/
// class Solution
// {
// public:
//     int countEval(string s, int result)
//     {
//         int n = s.size();
//         vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
//         for (int i = 0; i < n; i += 2)
//         {
//             // // 单个数字的情况
//             dp[i][i][s[i] - '0'] = 1;
//         }
//         // 子表达式长度
//         for (int len = 3; len <= n; len += 2)
//         {
//             // 子表达式起始位置
//             for (int i = 0; i + len - 1 < n; ++i)
//             {
//                 int j = i + len - 1;               // 子表达式结束位置
//                 for (int k = i + 1; k < j; k += 2) // 运算符位置
//                 {
//                     if (s[k] == '&')
//                     {
//                         // // 与运算：只有两边都是1时结果才是1 （1 & 1）
//                         dp[i][j][1] += dp[i][k - 1][1] * dp[k + 1][j][1];
//                         dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][0] +
//                                        dp[i][k - 1][0] * dp[k + 1][j][1] +
//                                        dp[i][k - 1][1] * dp[k + 1][j][0];
//                     }
//                     else if (s[k] == '|')
//                     {
//                         dp[i][j][1] += dp[i][k - 1][1] * dp[k + 1][j][1] +
//                                        dp[i][k - 1][0] * dp[k + 1][j][1] +
//                                        dp[i][k - 1][1] * dp[k + 1][j][0];
//                         dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][0];
//                     }
//                     else if (s[k] == '^')
//                     {
//                         dp[i][j][1] += dp[i][k - 1][0] * dp[k + 1][j][1] +
//                                        dp[i][k - 1][1] * dp[k + 1][j][0];
//                         dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][0] +
//                                        dp[i][k - 1][1] * dp[k + 1][j][1];
//                     }
//                 }
//             }
//         }
//         return dp[0][n - 1][result];
//     }
// };

// class Solution
// {
// public:
//     unordered_map<string, vector<int>> memo;

//     int countEval(string s, int result)
//     {
//         vector<int> ans = dfs(s);
//         return result == 0 || result == 1 ? ans[result] : 0;
//     }

//     vector<int> dfs(string s)
//     {
//         if (memo.count(s))
//             return memo[s];
//         vector<int> res(2);
//         if (s.size() == 1)
//         {
//             res[s[0] - '0'] = 1;
//             return res;
//         }
//         for (int k = 0; k < s.size(); ++k)
//         {
//             if (s[k] == '0' || s[k] == '1')
//                 continue;
//             vector<int> left = dfs(s.substr(0, k));
//             vector<int> right = dfs(s.substr(k + 1, s.size() - k));
//             for (int i = 0; i < 2; ++i)
//             {
//                 for (int j = 0; j < 2; ++j)
//                 {
//                     int v = 0;
//                     if (s[k] == '&')
//                         v = i & j;
//                     else if (s[k] == '|')
//                         v = i | j;
//                     else if (s[k] == '^')
//                         v = i ^ j;
//                     res[v] += left[i] * right[j];
//                 }
//             }
//         }
//         memo[s] = res;
//         return res;
//     }
// };

// day-2025-8-13
// 面试题 10.01. 合并排序的数组
// class Solution {
// public:
//     void merge(vector<int> &A, int m, vector<int> &B, int n) {
//         // 处理特殊情况
//         if (n == 0) return;
//         if (m == 0) {
//             A = B;  // 直接将 B 赋值给 A
//             return;
//         }

//         // 确保 A 有足够空间
//         A.resize(m + n);

//         // 从后往前合并
//         int k = m + n - 1;  // 正确的最后一个元素位置
//         int i = m - 1, j = n - 1;

//         while (i >= 0 && j >= 0) {
//             if (A[i] >= B[j]) {
//                 A[k--] = A[i--];
//             } else {
//                 A[k--] = B[j--];
//             }
//         }

//         // 处理剩余元素
//         while (j >= 0) {
//             A[k--] = B[j--];
//         }
//         // 无需处理 A 的剩余元素，因为它们已经在正确位置
//     }
// };

// 面试题 10.02. 变位词组 MID
// class Solution
// {
// public:
//     vector<vector<string>> groupAnagrams(vector<string> &strs)
//     {
//         vector<vector<string>> res;
//         unordered_map<string, vector<string>> map;
//         for (int i = 0; i < strs.size(); ++i)
//         {
//             string s = strs[i];
//             sort(strs[i].begin(), strs[i].end());
//             map[strs[i]].push_back(s);
//         }
//         for (auto it = map.begin(); it != map.end(); ++it)
//         {
//             vector<string> tmp;
//             for (string s : it->second)
//                 tmp.push_back(s);
//             res.push_back(tmp);
//         }
//         return res;
//     }
// };

// 面试题 10.03. 搜索旋转数组 mid
// class Solution
// {
// public:
//     int search(vector<int> &nums, int target)
//     {
//         int l = 0, r = nums.size() - 1;
//         if (r == -1)
//             return -1;
//         while (l < r)
//         {
//             int m = l + (r - l) / 2;
//             if (nums[l] < nums[m]) // 左半边有序
//             {
//                 if (target >= nums[l] && target <= nums[m])
//                     r = m;
//                 else
//                     l = m + 1;
//             }
//             else if (nums[l] > nums[m]) // 左半边无序, 右半边有序
//             {
//                 if (target >= nums[l] || target <= nums[m])
//                     r = m;
//                 else
//                     l = m + 1;
//             }
//             else if (nums[l] == nums[m])
//             {
//                 if (nums[l] != target)
//                     l++;
//                 else
//                     r = l;
//             }
//         }
//         return (nums[l] == target) ? l : -1;
//     }
// };

// 面试题 10.05. 稀疏数组搜索 Nb
// class Solution
// {
// public:
//     int findString(vector<string> &words, string s)
//     {
//         function<int(int, int)> dfs = [&](int i, int j)
//         {
//             if (i > j)
//                 return -1;
//             int m = i + j >> 1;
//             int l = dfs(i, m - 1);
//             if (l != -1)
//                 return l;
//             if (words[m] == s)
//                 return m;
//             return dfs(m + 1, j);
//         };
//         return dfs(0, words.size() - 1);
//     }
// };

// 面试题 10.05. 稀疏数组搜索
// class Solution
// {
// public:
//     bool searchMatrix(vector<vector<int>> &matrix, int target)
//     {
//         if (matrix.empty() || matrix[0].empty())
//             return false;
//         int m = matrix.size(), n = matrix[0].size();
//         int i = 0, j = n - 1;
//         while (i < m && j >= 0)
//         {
//             if (matrix[i][j] == target)
//                 return true;
//             else if (matrix[i][j] < target)
//                 i++;
//             else
//                 j--;
//         }
//         return false;
//     }
// };

// 法2.
// class Solution
// {
// public:
//     bool searchMatrix(vector<vector<int>> &matrix, int target)
//     {
//         for (auto &row : matrix)
//         {
//             auto j = lower_bound(row.begin(), row.end(), target) - row.begin();
//             if (j < matrix[0].size() && row[j] == target)
//                 return true;
//         }
//         return false;
//     }
// };
#include <memory>
// day-2025-8-14
// 10.10. 数字流的秩 mid
// class BIT
// {
// public:
//     vector<int> tree;
//     int n;
//     BIT(int n)
//         : n(n), tree(n + 1) {}
//     int lowbit(int x)
//     {
//         return x & (-x);
//     }
//     int query(int x)
//     {
//         int ans = 0;
//         for (int i = x; i; i -= lowbit(i))
//             ans += tree[i];
//         return ans;
//     }
//     void add(int x, int val)
//     {
//         for (int i = x; i <= n; i += lowbit(i))
//             tree[i] += val;
//     }
//     int query(int l, int r)
//     {
//         return query(r) - query(l - 1);
//     }
// };
// class StreamRank
// {
// public:
//     StreamRank()
//     {
//     }

//     void track(int x)
//     {
//         tree->add(x + 1, 1);
//     }

//     int getRankOfNumber(int x)
//     {
//         return tree->query(x + 1);
//     }

// private:
//     BIT *tree = new BIT(50010);
// };

// 面试题 10.11. 峰与谷 mid
// class Solution
// {
// public:
//     void wiggleSort(vector<int> &nums)
//     {
//         // 偶数为峰, 奇数为谷.
//         for (int i = 1; i < nums.size(); ++i)
//         {
//             if (i % 2)
//             {
//                 if (nums[i] > nums[i - 1])
//                     swap(nums[i - 1], nums[i]);
//             }
//             else
//             {
//                 if (nums[i] < nums[i - 1])
//                     swap(nums[i - 1], nums[i]);
//             }
//         }
//     }
// };

// 面试题 16.01. 交换数字 mid
// class Solution {
// public:
//     vector<int> swapNumbers(vector<int>& numbers) {
//         numbers[0] ^= numbers[1];
//         numbers[1] ^= numbers[0];
//         numbers[0] ^= numbers[1];
//         return numbers;
//     }
// };

// day-2025-8-15
// 面试题 16.02. 单词频率 mid
// 法1 字典树
// class TrieNode
// {
// public:
//     TrieNode *child[26];
//     bool isEnd;
//     int n;
//     TrieNode()
//         : isEnd(false),
//           n(0)
//     {
//         for (int i = 0; i < 26; ++i)
//             child[i] = nullptr;
//     }
// };

// class Trie
// {
// public:
//     TrieNode *root;
//     Trie()
//         : root(new TrieNode)
//     {
//     }
//     void insert(string word)
//     {
//         TrieNode *cur = root;
//         for (int i = 0; i < word.size(); ++i)
//         {
//             char c = word[i] - 'a';
//             if (cur->child[c] == nullptr)
//             {
//                 cur->child[c] = new TrieNode();
//             }
//             cur = cur->child[c];
//         }
//         cur->n++;
//         cur->isEnd = true;
//     }
//     int get(string word)
//     {
//         TrieNode *cur = root;
//         for (int i = 0; i < word.size(); ++i)
//         {
//             char c = word[i] - 'a';
//             if (cur->child[c] == nullptr)
//                 return false;
//             cur = cur->child[c];
//         }
//         return cur->n;
//     }
// };
// class WordsFrequency
// {
// public:
//     Trie trie;

//     WordsFrequency(vector<string> &book)
//     {
//         for (int i = 0; i < book.size(); ++i)
//             trie.insert(book[i]);
//     }

//     int get(string word)
//     {
//         return trie.get(word);
//     }
// };

// 法 2 哈希
// class WordsFrequency
// {
// public:
//     unordered_map<string, int> cnt;
//     WordsFrequency(vector<string> &book)
//     {
//         for (auto &bk : book)
//             cnt[bk]++;
//     }

//     int get(string word)
//     {
//         return cnt[word];
//     }
// };

// 16.03. 交点 hard dnt do liao

// 16.04. 井字游戏 mid
// 可以将 O 和 X 优化成 1和 -1.
// class Solution
// {
// public:
//     string tictactoe(vector<string> &board)
//     {
//         bool Empty = false;
//         int m = board.size();
//         vector<int> rows(m * 2), cols(m * 2);
//         vector<int> diagonal(4, 0);
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < m; ++j)
//             {
//                 if (!Empty && board[i][j] == ' ')
//                     Empty = true;
//                 if (board[i][j] == 'O')
//                 {
//                     rows[i]++, cols[j]++;
//                     if (i == j)
//                         diagonal[0]++;
//                     if (i + j == m - 1)
//                         diagonal[1]++;
//                 }
//                 if (board[i][j] == 'X')
//                 {
//                     rows[i + m]++, cols[j + m]++;
//                     if (i == j)
//                         diagonal[2]++;
//                     if (i + j == m - 1)
//                         diagonal[3]++;
//                 }
//             }
//         }
//         for (int i = 0; i < 2 * m; ++i)
//         {
//             if (i < m && rows[i] == m)
//                 return "O";
//             else if (i > m && rows[i] == m)
//                 return "X";
//         }
//         for (int i = 0; i < 2 * m; ++i)
//         {
//             if (i < m && cols[i] == m)
//                 return "O";
//             else if (i >= m && cols[i] == m)
//                 return "X";
//         }
//         for (int i = 0; i < 4; ++i)
//         {
//             if (i < 2 && diagonal[i] == m)
//                 return "O";
//             else if (i >= 2 && diagonal[i] == m)
//                 return "X";
//         }
//         if (Empty)
//             return "Pending";
//         return "Draw";
//     }
// };

// 面试题 16.05. 阶乘尾数
// class Solution
// {
// public:
//     int trailingZeroes(int n)
//     {
//         int ans = 0;
//         while (n)
//         {
//             n /= 5;
//             ans += n;
//         }
//         return ans;
//     }
// };

// 2025-8-16
// 面试题 16.06. 最小差 mid
// class Solution
// {
// public:
//     int smallestDifference(vector<int> &a, vector<int> &b)
//     {
//         sort(b.begin(), b.end());
//         long long ans = LONG_LONG_MAX;
//         for (int x : a)
//         {
//             auto it = lower_bound(b.begin(), b.end(), x);
//             if (it != b.end())
//                 ans = min(ans, (long long)*it - x);
//             if (it != b.begin())
//                 ans = min(ans, x - (long long)*prev(it));
//         }
//         return ans;
//     }
// };

// 面试题 16.07. 最大数值
// class Solution
// {
// public:
//     int maximum(int a, int b)
//     {
//         return a > b ? a : b;
//     }
// };

// 面试题 16.10. 生存人数 mid
// class Solution
// {
// public:
//     int maxAliveYear(vector<int> &birth, vector<int> &death)
//     {
//         // 差分思想
//         vector<int> a(105);
//         for (int i = 0; i < birth.size(); ++i)
//         {
//             int x = birth[i] - 1900, y = death[i] - 1900;
//             a[x]++;
//             a[y + 1]--;
//         }
//         int mx = 0, idx = 0, sum = 0;
//         for (int i = 1900; i <= 2000; ++i)
//         {
//             sum += a[i - 1900];
//             if (sum > mx)
//             {
//                 mx = sum;
//                 idx = i;
//             }
//         }
//         return idx;
//     }
// };

// 面试题 16.11. 跳水板
// class Solution
// {
// public:
//     vector<int> divingBoard(int shorter, int longer, int k)
//     {
//         vector<int> ans;
//         if (k == 0)
//             return {};
//         if (shorter == longer)
//             return {shorter * k};
//         for (int i = 0; i < k + 1; ++i)
//         {
//             ans.push_back(longer * i + (k - i) * shorter);
//         }
//         return ans;
//     }
// };

// day-2025-8-17
// 面试题 16.14. 最佳直线 mid
// class Solution
// {
// public:
//     vector<int> bestLine(vector<vector<int>> &points)
//     {
//         int n = points.size();
//         // 保存最大的数量和对应的序号数组
//         int maxCnt = 0;
//         vector<int> res(2, 0);
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 int cnt = 2;
//                 // 坑： 这里计算需要用long避免乘法时候的溢出
//                 long x1 = points[i][0] - points[j][0];
//                 long y1 = points[i][1] - points[j][1];
//                 for (int k = j + 1; k < n; ++k)
//                 {
//                     long x2 = points[i][0] - points[k][0];
//                     long y2 = points[i][1] - points[k][1];
//                     if (x1 * y2 == x2 * y1)
//                     {
//                         ++cnt;
//                     }
//                 }
//                 if (cnt > maxCnt)
//                 {
//                     maxCnt = cnt;
//                     res[0] = i;
//                     res[1] = j;
//                 }
//             }
//         }
//         return res;
//     }
// };

// 面试题 16.15. 珠玑妙算
// class Solution
// {
// public:
//     vector<int> masterMind(string solution, string guess)
//     {
//         vector<int> ans(2, 0);

//         unordered_map<char, int> cnt;
//         for (int i = 0; i < solution.size(); ++i)
//         {
//             if (solution[i] == guess[i])
//             {
//                 ans[0]++;
//                 solution[i] = ' ';
//                 guess[i] = ' ';
//             }
//         }
//         for (int i = 0; i < solution.size(); ++i)
//             cnt[solution[i]]++;
//         for (int i = 0; i < guess.size(); ++i)
//         {
//             if (guess[i] != ' ')
//             {
//                 if (cnt[guess[i]] > 0)
//                 {
//                     ans[1] += 1;
//                     cnt[guess[i]]--;
//                 }
//             }
//         }
//         return ans;
//     }
// };

// 面试题 16.16. 部分排序 mid
// class Solution
// {
// public:
//     vector<int> subSort(vector<int> &array)
//     {
//         vector<int> ans(2, -1);
//         int n = array.size();
//         int mx = INT_MIN, mn = INT_MAX;
//         for (int i = n - 1; i >= 0; --i)
//         {
//             if (array[i] > mn)
//                 ans[0] = i;
//             else
//                 mn = array[i];
//         }
//         for (int i = 0; i < n; ++i)
//         {
//             if (array[i] < mx)
//                 ans[1] = i;
//             else
//                 mx = array[i];
//         }
//         return ans;
//     }
// };

// 面试题 16.17. 连续数列
// class Solution
// {
// public:
//     int maxSubArray(vector<int> &nums)
//     {
//         int sum = 0;
//         int ans = INT_MIN;
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             sum = max(nums[i], nums[i] + sum);
//             ans = max(ans, sum);
//         }
//         return ans;
//     }
// };

// 面试题 16.19. 水域大小 mid
// class Solution BFS
// {
// public:
//     int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}};
//     void bfs(vector<vector<int>> &land, vector<vector<bool>> &vis, vector<int> &pools, int i, int j)
//     {
//         int m = land.size(), n = land[0].size();
//         queue<pair<int, int>> q;
//         q.push({i, j});
//         vis[i][j] = true;
//         int pool = 1;
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             for (int k = 0; k < 8; ++k)
//             {
//                 auto x = t.first + dirs[k][0];
//                 auto y = t.second + dirs[k][1];
//                 if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && land[x][y] == 0)
//                 {
//                     pool++;
//                     q.push({x, y});
//                     vis[x][y] = true;
//                 }
//             }
//         }
//         pools.push_back(pool);
//     }

//     vector<int> pondSizes(vector<vector<int>> &land)
//     {
//         vector<int> pools;
//         int m = land.size();
//         if (m == 0)
//             return pools;
//         int n = land[0].size();
//         vector<vector<bool>> vis(m, vector<bool>(n, false));
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (!vis[i][j] && land[i][j] == 0)
//                 {
//                     bfs(land, vis, pools, i, j);
//                 }
//             }
//         }
//         sort(pools.begin(), pools.end());
//         return pools;
//     }
// };

// class Solution DFS
// {
// public:
//     vector<int> pondSizes(vector<vector<int>> &land)
//     {
//         int m = land.size(), n = land[0].size();
//         function<int(int, int)> dfs = [&](int i, int j)
//         {
//             land[i][j] = 1;
//             int res = 1;
//             for (int x = i - 1; x <= i + 1; x++)
//             {
//                 for (int y = j - 1; y <= j + 1; y++)
//                 {
//                     if (x >= 0 && x < m && y >= 0 && y < n && land[x][y] == 0)
//                     {
//                         res += dfs(x, y);
//                     }
//                 }
//             }
//             return res;
//         };
//         vector<int> ans;
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (land[i][j] == 0)
//                     ans.push_back(dfs(i, j));
//             }
//         }
//         sort(ans.begin(), ans.end());
//         return ans;
//     }
// };

// day-2025-8-18
// 面试题 16.20. T9键盘 mid
// class Solution {
// public:
//     vector<string> getValidT9Words(string num, vector<string>& words) {
//         unordered_map<char,int> hash{
//             {'a', 2}, {'b', 2}, {'c', 2},
//             {'d', 3}, {'e', 3}, {'f', 3},
//             {'g', 4}, {'h', 4}, {'i', 4},
//             {'j', 5}, {'k', 5}, {'l', 5},
//             {'m', 6}, {'n', 6}, {'o', 6},
//             {'p', 7}, {'q', 7}, {'r', 7},{'s',7},
//             {'t', 8}, {'u', 8}, {'v', 8},
//             {'w', 9}, {'x', 9}, {'y', 9},{'z',9}
//         };
//         vector<string> ans;
//         for(int i = 0; i < words.size(); ++i)
//         {
//             int j = 0;
//             for(; j < words[i].size(); ++j)
//             {
//                 if(hash[words[i][j]] != (num[j] - '0'))
//                     break;
//             }
//             if(j == words[i].size())
//                 ans.push_back(words[i]);
//         }
//         return ans;
//     }
// };

// 面试题 16.21. 交换和 mid
// class Solution
// {
// public:
//     vector<int> findSwapValues(vector<int> &array1, vector<int> &array2)
//     {
//         long long sum1 = accumulate(array1.begin(), array1.end(), 0LL);
//         long long sum2 = accumulate(array2.begin(), array2.end(), 0LL);
//         long long dif = sum1 - sum2;
//         if (dif & 1)
//             return {};
//         // x - y = diff / 2;
//         // x = y + dif / 2
//         dif >>= 1;
//         unordered_set<int> set(array2.begin(), array2.end());
//         for (auto &x : array1)
//         {
//             int y = x - dif;
//             if (set.count(y))
//                 return {x, y};
//         }
//         return {};
//     }
// };

// 面试题 16.22. 兰顿蚂蚁 mid
// #include <set>
// class Solution
// {
// public:
//     vector<string> printKMoves(int K)
//     {
//         // 最小的坐标       最大的坐标
//         int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
//         int x = 0, y = 0, p = 0; // 当前位置和方向 p
//         int dirs[5] = {0, 1, 0, -1, 0};
//         string d = "RDLU";
//         set<pair<int, int>> black;
//         while (K--)
//         {
//             auto t = make_pair(x, y);
//             if (black.count(t))
//             {
//                 black.erase(t);
//                 p = (p + 3) % 4; // 顺时针走三步, 相当于逆时针走一步
//             }
//             else
//             {
//                 black.insert(t);
//                 p = (p + 1) % 4;
//             }
//             x += dirs[p];
//             y += dirs[p + 1];
//             x1 = min(x1, x);
//             y1 = min(y1, y);
//             x2 = max(x2, x);
//             y2 = max(y2, y);
//         }
//         int m = x2 - x1 + 1, n = y2 - y1 + 1;
//         vector<string> g(m, string(n, '_'));
//         for (auto &[a, b] : black)
//         {
//             g[a - x1][b - y1] = 'X';
//         }
//         g[x - x1][y - y1] = d[p];
//         return g;
//     }
// };

// 面试题 16.24. 数对和 mid
// class Solution
// {
// public:
//     vector<vector<int>> pairSums(vector<int> &nums, int target)
//     {
//         vector<vector<int>> ans;
//         int n = nums.size();
//         unordered_map<int, int> mp;
//         for (auto &x : nums)
//         {
//             int y = target - x;
//             if (mp[y])
//             {
//                 --mp[y];
//                 ans.push_back({x, y});
//             }
//             else
//                 ++mp[x];
//         }
//         return ans;
//     }
// };

// day-2025-8-19
// 面试题 16.25. LRU缓存 mid
// struct Node
// {
//     int k;
//     int v;
//     Node* next;
//     Node* prev;
//     Node(){}
//     Node(int key, int value)
//     :k(key), v(value){}
// };

// class LRUCache {
// public:
//     LRUCache(int capacity)
//     :cap(capacity),
//     size(0) {
//         head = new Node();
//         tail = new Node();
//         head->next = tail;
//         tail->prev = head;
//     }

//     int get(int key) {
//         if(!cache.count(key)) return -1;
//         Node* node = cache[key];
//         moveToHead(node);
//         return node->v;
//     }

//     void put(int key, int value) {
//         if(cache.count(key)) // cunzai
//         {
//             Node* node = cache[key];
//             node->v = value;
//             moveToHead(node);
//         }
//         else
//         {
//             Node* node = new Node(key, value);
//             addToHead(node);
//             ++size;
//             cache[key] = node;
//             if(size > cap)
//             {
//                 node = removeTail();
//                 cache.erase(node->k);
//                 --size;
//             }
//         }
//     }
//     unordered_map<int, Node*> cache;
//     Node* head;
//     Node* tail;
//     int cap;
//     int size;
//      void moveToHead(Node* node)
//      {
//         removeNode(node);
//         addToHead(node);
//      }
//     void removeNode(Node* node)
//     {
//         // prev node  next
//         node->prev->next = node->next;
//         node->next->prev = node->prev;
//     }
//     void addToHead(Node* node) {
//         // head node next
//         node->next = head->next;
//         node->prev = head;
//         head->next->prev = node;
//         head->next = node;
//     }
//     Node* removeTail()
//     {
//         // node tail
//         Node* node = tail->prev;
//         removeNode(node);
//         return node;
//     }
// };

// 面试题 16.26. 计算器 mid
// class Solution
// {
// public:
//     int calculate(string s)
//     {
//         stack<int> st;
//         int n = s.size();
//         int x = 0;
//         char sign = '+';
//         for (int i = 0; i < n; ++i)
//         {
//             char c = s[i];
//             if (isdigit(c))
//             {
//                 x = x * 10 + (c - '0');
//             }
//             if (i == n - 1 || !isdigit(c) && !isspace(c))
//             {
//                 if (sign == '+')
//                     st.push(x);
//                 else if (sign == '-')
//                     st.push(-x);
//                 else if (sign == '*')
//                 {
//                     int t = st.top();
//                     st.pop();
//                     st.push(t * x);
//                 }
//                 else if (sign == '/')
//                 {
//                     int t = st.top();
//                     st.pop();
//                     st.push(t / x);
//                 }
//                 x = 0;
//                 sign = c;
//             }
//         }
//         int ans = 0;
//         while (!st.empty())
//         {
//             ans += st.top();
//             st.pop();
//         }
//         return ans;
//     }
// };

// 面试题 17.01. 不用加号的加法
// class Solution
// {
// public:
//     int add(int a, int b)
//     {
//         while (b != 0)
//         {
//             unsigned int carry = (unsigned int)(a & b) << 1;
//             a = a ^ b;
//             b = carry;
//         }
//         return a;
//     }
// };

// 面试题 17.04. 消失的数字
// class Solution
// {
// public:
//     int missingNumber(vector<int> &nums)
//     {
//         int x = 0;
//         int i;
//         for (int i = 0; i <= nums.size(); ++i)
//         {
//             x ^= i;
//         }
//         for (int i = 0; i < nums.size(); ++i)
//         {
//             x ^= nums[i];
//         }
//         return x;
//     }
// };

// 面试题 17.05. 字母与数字 mid
// class Solution
// {
// public:
//     vector<string> findLongestSubarray(vector<string> &array)
//     {
//         unordered_map<int, int> vis{{0, -1}};
//         int s = 0, mx = 0, k = 0;
//         for (int i = 0; i < array.size(); ++i)
//         {
//             s += array[i][0] >= 'A' ? 1 : -1;
//             if (vis.count(s))
//             {
//                 int j = vis[s];
//                 if (mx < i - j)
//                 {
//                     mx = i - j;
//                     k = j + 1;
//                 }
//             }
//             else
//             {
//                 vis[s] = i;
//             }
//         }
//         return vector<string>(array.begin() + k, array.begin() + k + mx);
//     }
// };

// #include <memory>
// day-2025-8-20
// 面试题 17.06. 2出现的次数 hard
// class Solution
// {
// public:
//     int numberOf2sInRange(int n)
//     {
//         auto s = to_string(n); // 将数字转换为字符串，方便逐位处理
//         int m = s.length();
//         int dp[m][m];               // dp[i][j]表示处理到第i位时，已出现j个2的方案数
//         memset(dp, -1, sizeof(dp)); // 初始化为-1，表示未计算过

//         // 递归函数：i表示当前处理的位置，cnt2表示已统计的2的个数，is_limit表示当前位是否受限于原数的上界
//         function<int(int, int, bool)> f = [&](int i, int cnt2, bool is_limit) -> int
//         {
//             if (i == m)      // 处理完所有位
//                 return cnt2; // 返回统计的2的个数

//             // 如果当前位不受限制且该状态已计算过，直接返回缓存结果
//             if (!is_limit && dp[i][cnt2] >= 0)
//                 return dp[i][cnt2];

//             int res = 0;
//             // 确定当前位可以填的最大数字
//             int up = is_limit ? (s[i] - '0') : 9;

//             // 枚举当前位可能的数字
//             for (int d = 0; d <= up; ++d)
//             {
//                 // 递归处理下一位，更新2的计数，并判断下一位是否受限
//                 res += f(i + 1, cnt2 + (d == 2), is_limit && (d == up));
//             }

//             // 如果当前位不受限制，缓存结果
//             if (!is_limit)
//                 dp[i][cnt2] = res;

//             return res;
//         };
//         // 从第0位开始处理，初始2的计数为0，初始状态受限制
//         return f(0, 0, true);
//     }
// };

// day-2025-8-22
// 面试题 17.07. 婴儿名字 mid
// class Solution
// {
// public:
//     vector<string> trulyMostPopular(vector<string> &names, vector<string> &synonyms)
//     {
//         unordered_map<string, vector<string>> g;
//         unordered_map<string, int> cnt;
//         for (auto &sy : synonyms)
//         {
//             auto i = sy.find(',');
//             string a = sy.substr(1, i - 1);
//             string b = sy.substr(i + 1, sy.size() - i - 2);
//             g[a].emplace_back(b);
//             g[b].emplace_back(a);
//         }
//         unordered_set<string> s;
//         for (auto &e : names)
//         {
//             auto i = e.find('(');
//             string name = e.substr(0, i);
//             s.insert(name);
//             cnt[name] = stoi(e.substr(i + 1, e.size() - i - 2));
//         }
//         unordered_set<string> vis;
//         int freq = 0;
//         function<string(string)> dfs = [&](string a) -> string
//         {
//             string res = a;
//             vis.insert(a);
//             freq += cnt[a];
//             for (auto &b : g[a])
//             {
//                 if (!vis.count(b))
//                 {
//                     string t = dfs(b);
//                     if (t < res)
//                         res = move(t);
//                 }
//             }
//             return move(res);
//         };

//         vector<string> ans;
//         for (auto &name : s)
//         {
//             if (!vis.count(name))
//             {
//                 freq = 0;
//                 string x = dfs(name);
//                 ans.emplace_back(x + "(" + to_string(freq) + ")");
//             }
//         }
//         return ans;
//     }
// };

// 面试题 17.08. 马戏团人塔 mid
// class Solution
// {
// public:
//     int bestSeqAtIndex(vector<int> &height, vector<int> &weight)
//     {
//         // 1. 将身高和体重配对
//         vector<pair<int, int>> tmp;
//         for (int i = 0; i < height.size(); i++)
//             tmp.push_back({height[i], weight[i]});

//         // 2. 排序：先按身高升序，身高相同时按体重降序
//         sort(tmp.begin(), tmp.end(), [](const pair<int, int> &a, const pair<int, int> &b)
//              { return a.first == b.first ? a.second > b.second : a.first < b.first; });

//         // 3. 求解最长递增子序列（LIS）
//         vector<int> dp; // dp[i]表示长度为i+1的子序列中，末尾元素的最小值
//         for (const auto &[h, w] : tmp)
//         {
//             // 二分查找第一个大于等于w的位置
//             auto p = lower_bound(dp.begin(), dp.end(), w);
//             if (p == dp.end())
//                 dp.push_back(w); // 找到更长的子序列
//             else
//                 *p = w; // 优化现有长度的子序列
//         }
//         return dp.size(); // dp的长度即为最长递增子序列的长度
//     }
// };

// 面试题 17.09. 第 k 个数 mid
// class Solution {
//     const vector<int> vec{3, 5, 7};
// public:
//     int getKthMagicNumber(int k) {
//         priority_queue<long, vector<long>, greater<long>> pq;
//         unordered_set<long> vis;
//         pq.push(1L);
//         vis.insert(1L);
//         for(int i = 0; i < k - 1; ++i)
//         {
//             auto t = pq.top(); pq.pop();
//             for(auto& v : vec)
//             {
//                 long n = v * t;
//                 if(!vis.count(n))
//                 {
//                     vis.insert(n);
//                     pq.push(n);
//                 }
//             }
//         }
//         return (int)pq.top();
//     }
// };

// 面试题 17.10. 主要元素
// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         sort(nums.begin(), nums.end());
//         int mainElement = nums[nums.size() / 2];
//         int n = 0;
//         for(int i = 0; i < nums.size(); ++i)
//         {
//             if(nums[i] == mainElement) n++;
//         }
//         return n > nums.size() / 2 ? mainElement : -1;
//     }
// };

// 面试题 17.11. 单词距离 mid
// class Solution
// {
// public:
//     int findClosest(vector<string> &words, string word1, string word2)
//     {
//         int i = -1, j = -1;
//         int ans = INT_MAX;
//         for (int k = 0; k < words.size(); ++k)
//         {
//             if (words[k] == word1)
//                 i = k;
//             if (words[k] == word2)
//                 j = k;
//             if (i != -1 && j != -1)
//                 ans = min(ans, abs(i - j));
//         }
//         return ans == INT_MAX ? -1 : ans;
//     }
// };

// day-2025-8-23
// 面试题 17.12. BiNode
// class Solution
// {
// public:
//     TreeNode *convertBiNode(TreeNode *root)
//     {
//         TreeNode *ans = new TreeNode(0), *cur = ans;
//         stack<TreeNode *> st;
//         while (!st.empty() || root)
//         {
//             while (root)
//             {
//                 st.push(root);
//                 root = root->left;
//             }
//             root = st.top();
//             st.pop();
//             root->left = nullptr;
//             cur->right = root;
//             cur = root;
//             root = root->right;
//         }
//         return ans->right;
//     }
// };

// 面试题 17.13. 恢复空格 mid

// class Solution
// {
// public:
//     int respace(vector<string> &dictionary, string sentence)
//     {
//         unordered_set<string> s(dictionary.begin(), dictionary.end());
//         int n = sentence.size();
//         vector<int> dp(n + 1);
//         for (int i = 1; i <= n; ++i)
//         {
//             dp[i] = dp[i - 1] + 1;
//             for (int j = 0; j < i; ++j)
//             {
//                 if (s.count(sentence.substr(j, i - j)))
//                     dp[i] = min(dp[i], dp[j]);
//             }
//         }
//         return dp[n];
//     }
// };

// class Trie
// {
// public:
//     Trie *next[26] = {nullptr};
//     bool isEnd;

//     Trie()
//     {
//         isEnd = false;
//     }

//     void insert(string s)
//     {
//         Trie *curPos = this;

//         for (int i = s.length() - 1; i >= 0; --i)
//         {
//             int t = s[i] - 'a';
//             if (curPos->next[t] == nullptr)
//             {
//                 curPos->next[t] = new Trie();
//             }
//             curPos = curPos->next[t];
//         }
//         curPos->isEnd = true;
//     }
// };

// class Solution
// {
// public:
//     int respace(vector<string> &dictionary, string sentence)
//     {
//         int n = sentence.length(), inf = 0x3f3f3f3f;

//         Trie *root = new Trie();
//         for (auto &word : dictionary)
//         {
//             root->insert(word);
//         }

//         vector<int> dp(n + 1, inf);
//         dp[0] = 0;
//         for (int i = 1; i <= n; ++i)
//         {
//             dp[i] = dp[i - 1] + 1;

//             Trie *curPos = root;
//             for (int j = i; j >= 1; --j)
//             {
//                 int t = sentence[j - 1] - 'a';
//                 if (curPos->next[t] == nullptr)
//                 {
//                     break;
//                 }
//                 else if (curPos->next[t]->isEnd)
//                 {
//                     dp[i] = min(dp[i], dp[j - 1]);
//                 }
//                 if (dp[i] == 0)
//                 {
//                     break;
//                 }
//                 curPos = curPos->next[t];
//             }
//         }
//         return dp[n];
//     }
// };

// day-2025-8-24
//  面试题 17.14. 最小K个数 mid
// class Solution {
// public:
//     int partition(vector<int>& nums, int l, int r)
//     {
//         int pivot = nums[r];
//         int i = l - 1;
//         for(int j = l; j < r; ++j)
//         {
//             if(nums[j] <= pivot)
//                 swap(nums[++i], nums[j]);
//         }
//         swap(nums[i + 1], nums[r]);
//         return i + 1;
//     }

//     int randomize_partition(vector<int>& nums, int l, int r)
//     {
//         int i = rand() % (r - l + 1) + l;
//         swap(nums[i], nums[r]);
//         return partition(nums, l, r);
//     }

//     void randomize_selected(vector<int>& nums, int l, int r, int k)
//     {
//         if(l >= r) return;
//         int pos = randomize_partition(nums, l, r);
//         int n = pos - l + 1;
//         if(n == k)
//             return;
//         else if(n < k)
//              randomize_selected(nums, pos + 1, r, k - n);
//         else
//              randomize_selected(nums, l, pos - 1, k);

//     }
//     vector<int> smallestK(vector<int>& arr, int k) {
//         srand(time(0));
//         randomize_selected(arr, 0, arr.size() - 1, k);
//         vector<int> res;
//         for(int i=0;i<k;++i)
//             res.push_back(arr[i]);
//         return res;
//     }
// };

// class Solution {
// public:
//     vector<int> smallestK(vector<int>& arr, int k) {
//         priority_queue<int> pq;
//         for(int i = 0; i < arr.size(); ++i)
//         {
//             pq.push(arr[i]);
//             if(pq.size() > k)
//                 pq.pop();
//         }
//         vector<int> ans;
//         while(!pq.empty())
//         {
//             ans.push_back(pq.top());
//             pq.pop();
//         }
//         return ans;
//     }
// };
// 面试题 17.15. 最长单词 mid
// class Solution
// {
// public:
//     string longestWord(vector<string> &words)
//     {
//         unordered_set<string> s(words.begin(), words.end());
//         ranges::sort(words.begin(), words.end(), [&](const string &a, const string &b)
//                      { return a.size() > b.size() || (a.size() == b.size() && a < b); });

//         auto dfs = [&](this auto &&dfs, string w) -> bool
//         {
//             if (w.empty())
//                 return true;
//             for (int i = 1; i <= w.size(); ++i)
//             {
//                 if (s.contains(w.substr(0, i)) && dfs(w.substr(i)))
//                     return true;
//             }
//             return false;
//         };
//         for (auto &word : words)
//         {
//             s.erase(word);
//             if (dfs(word))
//                 return word;
//         }
//         return "";
//     }
// };

// 面试题 17.16. 按摩师
// class Solution {
// public:
//     int massage(vector<int>& nums) {
//         if(nums.size() == 0) return 0;
//         if(nums.size() == 1) return nums[0];
//         if(nums.size() == 2) return max(nums[0], nums[1]);
//         int n = nums.size();
//         vector<int> dp(n + 1);
//         dp[1] = nums[0];
//         dp[2] = nums[1];
//         for(int i = 2; i <= n; ++i)
//         {
//             dp[i] = max(dp[i - 2] + nums[i - 1], dp[i - 1]);
//         }
//         return dp[n];
//     }
// };

// 面试题 17.17. 多次搜索 mid
// class trieNode
// {
// public:
//     trieNode *child[26] = {nullptr};
//     int idx = -1;
//     trieNode() {}
// };

// class Trie
// {
// public:
//     trieNode *root;
//     Trie()
//         : root(new trieNode) {}
//     void insert(string &words, int idx)
//     {
//         trieNode *cur = root;
//         for (auto &c : words)
//         {
//             if (cur->child[c - 'a'] == nullptr)
//             {
//                 cur->child[c - 'a'] = new trieNode();
//             }
//             cur = cur->child[c - 'a'];
//         }
//         cur->idx = idx;
//     }
//     void searchFromPosition(string &big, int start, vector<vector<int>> &ans)
//     {
//         trieNode *cur = root;
//         for (int i = start; i < big.size(); ++i)
//         {
//             char c = big[i];
//             if (cur->child[c - 'a'] == nullptr)
//                 break;

//             cur = cur->child[c - 'a'];
//             if (cur->idx != -1)
//             {
//                 ans[cur->idx].push_back(start);
//             }
//         }
//     }
// };

// class Solution
// {
// public:
//     vector<vector<int>> multiSearch(string big, vector<string> &smalls)
//     {
//         Trie trie;
//         for (int i = 0; i < smalls.size(); ++i)
//         {
//             trie.insert(smalls[i], i);
//         }
//         vector<vector<int>> ans(smalls.size());

//         for (int i = 0; i < big.size(); ++i)
//         {
//             trie.searchFromPosition(big, i, ans);
//         }
//         return ans;
//     }
// };

// day-2025-8-25
// 面试题 17.18. 最短超串 mid
// class Solution
// {
// public:
//     vector<int> shortestSeq(vector<int> &big, vector<int> &small)
//     {
//         int cnt = small.size();
//         unordered_map<int, int> mp;
//         for (int sm : small)
//             mp[sm]++;

//         int minLen = INT_MAX, st = -1, end = -1;
//         int l = 0;
//         int req = mp.size();
//         int hasFound = 0;
//         for (int r = 0; r < big.size(); ++r)
//         {
//             int n = big[r];
//             if (mp.count(n))
//             {
//                 mp[n]--;
//                 if (mp[n] == 0)
//                     hasFound++;
//             }
//             while (hasFound == req)
//             {
//                 if (r - l + 1 < minLen)
//                 {
//                     minLen = r - l + 1;
//                     st = l;
//                     end = r;
//                 }
//                 int left = big[l];
//                 mp[left]++;
//                 if (mp[left] > 0)
//                     hasFound--;
//                 l++;
//             }
//         }
//         if (st == -1)
//             return {};

//         return {st, end};
//     }
// };

// 面试题 17.19. 消失的两个数字 hard
// class Solution
// {
// public:
//     vector<int> missingTwo(vector<int> &nums)
//     {
//         int ans = 0, n = nums.size();
//         for (int i = 1; i <= n + 2; i++)
//             ans ^= i;
//         for (auto x : nums)
//             ans ^= x;
//         // ans = one ^ two;
//         int one = 0;
//         int diff = ans & -ans;
//         for (int i = 1; i <= n + 2; i++)
//             if (diff & i)
//                 one ^= i; // ?
//         for (auto x : nums)
//             if (diff & x)
//                 one ^= x;
//         return {one, one ^ ans};
//     }
// };

// 面试题 17.20. 连续中值 hard
// 建两个堆, 一个大根堆一个小根堆。
// class MedianFinder
// {
// public:
//     /** initialize your data structure here. */
//     MedianFinder()
//     {
//         maxHeap.push(INT_MIN);
//         minHeap.push(INT_MAX);
//     }

//     void addNum(int num)
//     {
//         if (num <= maxHeap.top())
//         {
//             maxHeap.push(num);
//         }
//         else
//         {
//             minHeap.push(num);
//         }
//         if (maxHeap.size() > minHeap.size() + 1)
//         {
//             minHeap.push(maxHeap.top());
//             maxHeap.pop();
//         }
//         else if (minHeap.size() > maxHeap.size() + 1)
//         {
//             maxHeap.push(minHeap.top());
//             minHeap.pop();
//         }
//     }

//     double findMedian()
//     {
//         if (maxHeap.size() == minHeap.size())
//         {
//             return (maxHeap.top() + minHeap.top()) / 2.0;
//         }
//         else if (maxHeap.size() > minHeap.size())
//         {
//             return maxHeap.top();
//         }
//         else
//         {
//             return minHeap.top();
//         }
//     }

//     priority_queue<int> maxHeap;
//     priority_queue<int, vector<int>, greater<int>> minHeap;
// };

// day-2025-8-27
// 面试题 17.21. 直方图的水量 hard
// class Solution
// {
// public:
//     int trap(vector<int> &height)
//     {
//         if (height.size() == 0)
//             return 0;
//         int n = height.size();
//         vector<int> left(n);
//         vector<int> right(n);
//         left[0] = height[0];
//         right[n - 1] = height[n - 1];
//         for (int i = 1; i < n; ++i)
//             left[i] = max(left[i - 1], height[i]);
//         for (int i = n - 2; i >= 0; --i)
//             right[i] = max(right[i + 1], height[i]);
//         int ans = 0;
//         for (int i = 0; i < n; ++i)
//             ans += min(left[i], right[i]) - height[i];
//         return ans;
//     }
// };

// 面试题 17.22. 单词转换 mid
// class Solution
// {
// public:
//     vector<string> findLadders(string beginWord, string endWord, vector<string> &wordList)
//     {
//         unordered_set<string> wordSet(wordList.begin(), wordList.end());
//         // 检查终点是否在字典中
//         if (wordSet.find(endWord) == wordSet.end())
//         {
//             return {};
//         }

//         queue<vector<string>> q;       // 队列中存储路径
//         unordered_set<string> visited; // 记录已访问的单词

//         q.push({beginWord});
//         visited.insert(beginWord);

//         while (!q.empty())
//         {
//             int size = q.size();
//             for (int i = 0; i < size; ++i)
//             {
//                 vector<string> path = q.front();
//                 q.pop();
//                 string cur = path.back();

//                 // 找到终点，返回路径
//                 if (cur == endWord)
//                 {
//                     return path;
//                 }

//                 // 尝试修改每个字符
//                 for (int j = 0; j < cur.size(); ++j)
//                 {
//                     char original = cur[j];
//                     for (char c = 'a'; c <= 'z'; ++c)
//                     {
//                         cur[j] = c;
//                         // 如果修改后的单词在字典中且未访问过
//                         if (wordSet.count(cur) && !visited.count(cur))
//                         {
//                             vector<string> newPath = path;
//                             newPath.push_back(cur);
//                             q.push(newPath);
//                             visited.insert(cur); // 标记为已访问
//                         }
//                     }
//                     cur[j] = original; // 恢复原字符
//                 }
//             }
//         }

//         return {}; // 无法找到路径
//     }
// };

// 面试题 17.23. 最大黑方阵 mid
// class Solution {
// public:
//     vector<int> findSquare(vector<vector<int>> &matrix) {
//         vector<int> ans;
//         int n = matrix.size();
//         if (n == 0) return ans;

//         // 两个二维数组分别记录每个位置向右和向下连续0的个数
//         vector<vector<int>> right(n, vector<int>(n, 0));
//         vector<vector<int>> down(n, vector<int>(n, 0));

//         // 初始化边界
//         for (int i = 0; i < n; ++i) {
//             right[i][n-1] = (matrix[i][n-1] == 0) ? 1 : 0;
//             down[n-1][i] = (matrix[n-1][i] == 0) ? 1 : 0;
//         }

//         // 从右到左，从下到上填充right和down数组
//         for (int i = 0; i < n; ++i) {
//             for (int j = n - 2; j >= 0; --j) {
//                 right[i][j] = (matrix[i][j] == 0) ? (right[i][j+1] + 1) : 0;
//             }
//         }

//         for (int i = n - 2; i >= 0; --i) {
//             for (int j = 0; j < n; ++j) {
//                 down[i][j] = (matrix[i][j] == 0) ? (down[i+1][j] + 1) : 0;
//             }
//         }

//         int maxSize = 0;
//         int startX = -1, startY = -1;

//         // 从大到小尝试正方形边长
//         for (int size = n; size > 0; --size) {
//             for (int i = 0; i <= n - size; ++i) {
//                 for (int j = 0; j <= n - size; ++j) {
//                     // 检查以(i,j)为左上角，边长为size的正方形是否全为0
//                     // 检查四个角点的right和down是否满足条件
//                     if (right[i][j] >= size && down[i][j] >= size &&
//                         right[i + size - 1][j] >= size && down[i][j + size - 1] >= size) {
//                         startX = i;
//                         startY = j;
//                         maxSize = size;
//                         return {startX, startY, maxSize};
//                     }
//                 }
//             }
//         }

//         return ans;
//     }
// };