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

int main()
{
    return 0;
}