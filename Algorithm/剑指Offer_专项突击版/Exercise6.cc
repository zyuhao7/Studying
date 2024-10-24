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

// day-2024-10-24
// 剑指 Offer II 068. 查找插入位置

// class Solution {
// public:
//     int searchInsert(vector<int>& nums, int target) {
//         int l = 0, r = nums.size() - 1;
//         while(l <= r)
//         {
//             int m = l + r >> 1;
//             if(nums[m] == target) return m;
//             else if(nums[m] > target) r = m - 1;
//             else l = m + 1;
//         }
//         return l;
//     }
// };

// 剑指 Offer II 069. 山峰数组的顶部
// class Solution {
// public:
//     int peakIndexInMountainArray(vector<int>& arr) {
//         if(arr.size() == 3) return 1;
//         int l = 1, r = arr.size() - 2;
//         while(l <= r)
//         {
//             int m = l + r >> 1;
//             if(arr[m] > arr[m - 1] && arr[m] > arr[m + 1])
//                 return m;
//             else if(arr[m] < arr[m - 1] && arr[m] > arr[m + 1])
//                 r = m - 1;
//             else
//                 l = m + 1;
//         }
//         return l;
//     }
// };

// 剑指 Offer II 070. 排序数组中只出现一次的数字
// ，其中每个元素都会出现两次，唯有一个数只会出现一次。
// 解法一: 异或求余
// class Solution
// {
// public:
//     int singleNonDuplicate(vector<int> &nums)
//     {
//         int x = 0;
//         for (int i = 0; i < nums.size(); ++i)
//             x ^= nums[i];
//         return x;
//     }
// };

// 二分异或判断
// class Solution {
// public:
//     int singleNonDuplicate(vector<int>& nums) {
//        int l = 0, r = nums.size() - 1;
//        while(l < r)
//        {
//             int m = l + r >> 1;
//             if(nums[m] == nums[m ^ 1])
//                 l = m + 1;
//             else
//                 r = m;
//        }
//        return nums[l];
//     }
// };

int main()
{

    return 0;
}