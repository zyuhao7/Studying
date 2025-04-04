#include <iostream>
using namespace std;
// day-2024-10-8
// 剑指 Offer II 031. 最近最少使用缓存
// struct DLinkedNode
// {
//     int key;
//     int val;
//     DLinkedNode *prev;
//     DLinkedNode *next;
//     DLinkedNode()
//         : key(0),
//           val(0),
//           prev(nullptr),
//           next(nullptr)
//     {
//     }
//     DLinkedNode(int _key, int _val)
//         : key(_key),
//           val(_val),
//           prev(nullptr),
//           next(nullptr)
//     {
//     }
// };
// class LRUCache
// {
//     unordered_map<int, DLinkedNode *> mp;
//     DLinkedNode *head;
//     DLinkedNode *tail;
//     int size;
//     int capacity;

// public:
//     LRUCache(int _capacity)
//         : capacity(_capacity),
//           size(0)
//     {
//         head = new DLinkedNode();
//         tail = new DLinkedNode();
//         head->next = tail;
//         tail->prev = head;
//     }

//     int get(int key)
//     {
//         if (!mp.count(key))
//             return -1;
//         DLinkedNode *node = mp[key];
//         moveToHead(node);
//         return node->val;
//     }

//     void put(int key, int value)
//     {
//         if (!mp.count(key))
//         {
//             DLinkedNode *node = new DLinkedNode(key, value);
//             mp[key] = node;
//             addToHead(node);
//             ++size;
//             if (size > capacity)
//             {
//                 DLinkedNode *rm = removeTail();
//                 mp.erase(rm->key);
//                 delete rm;
//                 --size;
//             }
//         }
//         else
//         {
//             DLinkedNode *node = mp[key];
//             node->val = value;
//             moveToHead(node);
//         }
//     }

//     void addToHead(DLinkedNode * node)
//     {
//         node->next = head->next;
//         head->next->prev = node;
//         node->prev = head;
//         head->next = node;
//     }

//     void removeNode(DLinkedNode * node)
//     {
//         node->next->prev = node->prev;
//         node->prev->next = node->next;
//     }
//     void moveToHead(DLinkedNode * node)
//     {
//         removeNode(node);
//         addToHead(node);
//     }
//     DLinkedNode *removeTail()
//     {
//         DLinkedNode *node = tail->prev;
//         removeNode(node);
//         return node;
//     }
// };

// 剑指 Offer II 032. 有效的变位词
// class Solution
// {
// public:
//     bool isAnagram(string s, string t)
//     {
//         if (s.size() != t.size())
//             return false;
//         int cnt[27] = {0};
//         for (int i = 0; i < s.size(); ++i)
//         {
//             cnt[s[i] - 'a']++;
//         }
//         for (int j = 0; j < t.size(); ++j)
//         {
//             cnt[t[j] - 'a']--;
//         }
//         for (int i = 0; i <= 26; ++i)
//         {
//             if (cnt[i] != 0)
//                 return false;
//         }
//         return true;
//     }
// };

// 剑指 Offer II 033. 变位词组
// class Solution
// {
// public:
//     vector<vector<string>> groupAnagrams(vector<string> &strs)
//     {
//         map<string, vector<string>> mp;
//         for (auto &s : strs)
//         {
//             string key = s;
//             sort(key.begin(), key.end());
//             mp[key].emplace_back(s);
//         }
//         vector<vector<string>> res;
//         auto it = mp.begin();
//         while (it != mp.end())
//         {
//             res.emplace_back(it->second);
//             it++;
//         }
//         return res;
//     }
// };

// day-2024-10-9
// 剑指 Offer II 034. 外星语言是否排序
// class Solution
// {
// public:
//     bool isAlienSorted(vector<string> &words, string order)
//     {
//         int i = 1;
//         unordered_map<char, int> mp;
//         for (auto c : order)
//             mp[c] = i++;
//         if (words.size() == 1)
//             return true;
//         for (int i = 0, j = 1; i < words.size() && j < words.size(); ++i, ++j)
//         {
//             int k = 0, z = 0;
//             int n = words[i].size(), m = words[j].size();
//             while (k < n && z < m && words[i][k] == words[j][z])
//             {
//                 k++;
//                 z++;
//             }
//             if (mp[words[i][k]] > mp[words[j][z]])
//                 return false;
//         }
//         return true;
//     }
// };

// 剑指 Offer II 035. 最小时间差
// class Solution
// {
// public:
//     int findMinDifference(vector<string> &timePoints)
//     {
//         int res = 1440;
//         sort(timePoints.begin(), timePoints.end());
//         for (int i = 0; i < timePoints.size() - 1; ++i)
//         {
//             int n1 = atoi(timePoints[i].substr(0, 2).c_str());
//             int n2 = atoi(timePoints[i].substr(3, 2).c_str());
//             int n3 = atoi(timePoints[i + 1].substr(0, 2).c_str());
//             int n4 = atoi(timePoints[i + 1].substr(3, 2).c_str());
//             int gap;
//             if (n4 < n2)
//                 gap = abs(n3 - n1) * 60 - abs(n4 - n2);
//             else
//                 gap = abs(n3 - n1) * 60 + abs(n4 - n2);

//             gap = min(1440, gap);
//             gap = min(gap, 1440 - gap);
//             res = min(res, gap);
//         }

//         int n1 = atoi(timePoints[0].substr(0, 2).c_str());
//         int n2 = atoi(timePoints[0].substr(3, 2).c_str());
//         int n3 = atoi(timePoints[timePoints.size() - 1].substr(0, 2).c_str());
//         int n4 = atoi(timePoints[timePoints.size() - 1].substr(3, 2).c_str());
//         int gap;
//         if (n4 < n2)
//             gap = abs(n3 - n1) * 60 - abs(n4 - n2);
//         else
//             gap = abs(n3 - n1) * 60 + abs(n4 - n2);

//         gap = min(1440, gap);
//         gap = min(gap, 1440 - gap);
//         res = min(res, gap);

//         return res;
//     }
// };

// day-2024-10-10
//  剑指 Offer II 036. 后缀表达式
// class Solution
// {
// public:
//     int evalRPN(vector<string> &tokens)
//     {
//         stack<int> stk;
//         for (auto &t : tokens)
//         {
//             if (t.size() > 1 || isdigit(t[0]))
//             {
//                 stk.push(stoi(t));
//             }
//             else
//             {
//                 int y = stk.top();
//                 stk.pop();
//                 int x = stk.top();
//                 stk.pop();
//                 if (t[0] == '+')
//                     stk.push(x + y);
//                 else if (t[0] == '-')
//                     stk.push(x - y);
//                 else if (t[0] == '*')
//                     stk.push(x * y);
//                 else
//                     stk.push(x / y);
//             }
//         }
//         return stk.top();
//     }
// };

// 剑指 Offer II 037. 小行星碰撞
// class Solution
// {
// public:
//     vector<int> asteroidCollision(vector<int> &a)
//     {
//         stack<int> st;
//         for (int i = 0; i < a.size(); ++i)
//         {
//             bool exploded = false;
//             while (!st.empty() && a[i] < 0 && st.top() > 0)
//             {
//                 if (abs(st.top()) > abs(a[i]))
//                 {
//                     exploded = true;
//                     break;
//                 }
//                 else if (abs(st.top()) == abs(a[i]))
//                 {
//                     exploded = true;
//                     st.pop();
//                     break;
//                 }
//                 else
//                 {
//                     st.pop();
//                 }
//             }
//             if (!exploded)
//                 st.push(a[i]);
//         }
//         vector<int> res(st.size());
//         for (int i = res.size() - 1; i >= 0; --i)
//         {
//             res[i] = st.top();
//             st.pop();
//         }
//         return res;
//     }
// };

// day-2024-10-11
// 剑指 Offer II 038. 每日温度
// class Solution
// {
// public:
//     vector<int> dailyTemperatures(vector<int> &t)
//     {
//         vector<int> ans(t.size());
//         stack<int> st;
//         st.push(0);
//         for (int i = 1; i < t.size(); ++i)
//         {
//             // 栈顶元素下标等于 i - top的下标.
//             while (!st.empty() && t[i] > t[st.top()])
//             {
//                 ans[st.top()] = i - st.top();
//                 st.pop();
//             }
//             st.push(i);
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 039. 直方图最大矩形面积
// class Solution
// {
// public:
//     int largestRectangleArea(vector<int> &h)
//     {
//         int n = h.size();
//         int ans = 0;
//         vector<int> l(n, -1), r(n, n);
//         stack<int> st;
//         for (int i = 0; i < h.size(); ++i)
//         {
//             while (!st.empty() && h[st.top()] >= h[i])
//             {
//                 st.pop();
//             }
//             if (!st.empty())
//                 l[i] = st.top();
//             st.push(i);
//         }
//         st = stack<int>();
//         for (int i = n - 1; ~i; --i)
//         {
//             while (!st.empty() && h[st.top()] >= h[i])
//                 st.pop();
//             if (!st.empty())
//                 r[i] = st.top();
//             st.push(i);
//         }
//         for (int i = 0; i < n; ++i)
//         {
//             ans = max(ans, (r[i] - l[i] - 1) * h[i]);
//         }
//         return ans;
//     }
// };

// day-2024-10-12
// 剑指 Offer II 040. 矩阵中最大的矩形
// class Solution
// {
// public:
//     int maximalRectangle(vector<vector<char>> &matrix)
//     {
//         int m = matrix.size();
//         if (m == 0)
//             return 0;
//         int n = matrix[0].size();
//         vector<vector<int>> left(m, vector<int>(n, 0));
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (matrix[i][j] == '1')
//                 {
//                     left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
//                 }
//             }
//         }
//         int ret = 0;
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (matrix[i][j] == '0')
//                     continue;

//                 int width = left[i][j];
//                 int area = width;
//                 for (int k = i - 1; k >= 0; --k)
//                 {
//                     width = min(width, left[k][j]);
//                     area = max(area, width * (i - k + 1));
//                 }
//                 ret = max(ret, area);
//             }
//         }
//         return ret;
//     }
// };

// 剑指 Offer II 041. 滑动窗口的平均值
// class MovingAverage
// {
// public:
//     MovingAverage(int size)
//     {
//         arr.resize(size);
//     }

//     double next(int val)
//     {
//         int idx = cnt % arr.size();
//         s += val - arr[idx];
//         arr[idx] = val;
//         ++cnt;
//         return (double)s / min(cnt, (int)arr.size());
//     }

// private:
//     vector<int> arr;
//     int cnt = 0;
//     int s = 0;
// };

// 剑指 Offer II 042. 最近请求次数
// class RecentCounter
// {
// public:
//     RecentCounter() {}

//     int ping(int t)
//     {
//         int cnt = 1;
//         for (int i = 0; i < v.size(); ++i)
//         {
//             if (v[i] >= t - 3000 && v[i] <= t)
//                 cnt++;
//         }
//         v.push_back(t);
//         return cnt;
//     }
//     vector<int> v;
// };

// class RecentCounter
// {
// public:
//     RecentCounter() {}

//     int ping(int t)
//     {
//         q.push_back(t);
//         while (q.front() < t - 3000)
//         {
//             q.pop_front();
//         }
//         return q.size();
//     }
//     deque<int> q;
// };

int main()
{
    return 0;
}