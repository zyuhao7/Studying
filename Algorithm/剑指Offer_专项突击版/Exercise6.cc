#include <iostream>
using namespace std;
// day-2024-10-23
// 剑指 Offer II 066. 单词之和
// class TrieNode
// {
// public:
//     bool isEnd;
//     int Val;
//     TrieNode *child[26];
//     TrieNode()
//     {
//         isEnd = false;
//         for (int i = 0; i < 26; ++i)
//             child[i] = nullptr;
//     }
// };

// class Trie
// {
// private:
//     TrieNode *root;

// public:
//     Trie()
//     {
//         root = new TrieNode();
//     }
//     void insert(string &key, int val)
//     {
//         TrieNode *node = root;
//         for (char c : key)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//                 node->child[i] = new TrieNode();
//             node = node->child[i];
//         }
//         node->isEnd = true;
//         node->Val = val;
//     }

//     int sumAllValues(TrieNode *node)
//     {
//         if (node == nullptr)
//             return 0;
//         int sum = node->isEnd ? node->Val : 0;
//         for (int i = 0; i < 26; ++i)
//         {
//             if (node->child[i])
//                 sum += sumAllValues(node->child[i]);
//         }
//         return sum;
//     }

//     int query(string &prefix)
//     {
//         TrieNode *node = root;
//         for (char c : prefix)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//                 return 0;
//             node = node->child[i];
//         }
//         return sumAllValues(node);
//     }
// };
// class MapSum
// {
// public:
//     Trie trie;
//     MapSum() {}

//     void insert(string key, int val)
//     {
//         trie.insert(key, val);
//     }

//     int sum(string prefix)
//     {
//         return trie.query(prefix);
//     }
// };

// 剑指 Offer II 067. 最大的异或
// class TrieNode
// {
// public:
//     TrieNode *child[2];
//     TrieNode()
//     {
//         for (int i = 0; i < 2; ++i)
//             child[i] = nullptr;
//     }
// };

// class Trie
// {
// private:
//     TrieNode *root;

// public:
//     Trie()
//     {
//         root = new TrieNode();
//     }

//     void insert(int x)
//     {
//         TrieNode *node = root;
//         for (int j = 30; ~j; --j)
//         {
//             int k = (x >> j) & 1;
//             if (node->child[k] == nullptr)
//                 node->child[k] = new TrieNode();
//             node = node->child[k];
//         }
//     }
//     int maxXornum(int x)
//     {
//         int res = 0;
//         TrieNode *node = root;
//         for (int i = 30; ~i; --i)
//         {
//             int v = (x >> i) & 1;
//             if (node->child[v ^ 1])
//             {
//                 res = (res << 1) | 1;
//                 node = node->child[v ^ 1];
//             }
//             else
//             {
//                 res <<= 1;
//                 node = node->child[v];
//             }
//         }
//         return res;
//     }
// };
// class Solution
// {
// public:
//     int findMaximumXOR(vector<int> &nums)
//     {
//         Trie trie;
//         int maxNum = 0;

//         for (int i = 0; i < nums.size(); ++i)
//         {
//             trie.insert(nums[i]);
//             maxNum = max(maxNum, trie.maxXornum(nums[i]));
//         }
//         return maxNum;
//     }
// };

int main()
{

    return 0;
}