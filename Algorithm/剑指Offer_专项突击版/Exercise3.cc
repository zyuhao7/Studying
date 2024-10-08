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

int main()
{
    return 0;
}