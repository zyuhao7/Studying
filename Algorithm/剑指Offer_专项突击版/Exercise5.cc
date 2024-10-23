#include <iostream>
#include <vector>
using namespace std;

// day-2024-10-19
// 剑指 Offer II 058. 日程表

// class MyCalendar
// {
// public:
//     MyCalendar()
//     {
//     }
//     vector<pair<int, int>> booked;
//     bool book(int start, int end)
//     {
//         for (auto &[l, r] : booked)
//         {
//             if (l < end && r > start)
//                 return false;
//         }
//         booked.emplace_back(start, end);
//         return true;
//     }
// };

// class MyCalendar
// {
// public:
//     MyCalendar() {}

//     struct schedule
//     {
//         int begin;
//         int end;
//     };
//     vector<schedule> Scheds;

//     bool book(int start, int end)
//     {
//         for (const auto &sched : Scheds)
//         {
//             if (max(sched.begin, start) < min(sched.end, end))
//                 return false;
//         }
//         Scheds.push_back({start, end});
//         return true;
//     }
// };

// 剑指 Offer II 059. 数据流的第 K 大数值

// 数组
// class KthLargest
// {
// public:
//     vector<int> v;
//     int k;
//     KthLargest(int k, vector<int> &nums)
//     {
//         for (auto &n : nums)
//             v.push_back(n);
//         this->k = k;
//         sort(v.begin(), v.end());
//     }

//     int add(int val)
//     {
//         if (v.empty() || val > v.back())
//             v.push_back(val);
//         else
//         {
//             auto it = lower_bound(v.begin(), v.end(), val);
//             v.insert(it, val);
//         }
//         return v[v.size() - k];
//     }
// };

// 最小堆
// class KthLargest {
// public:
//     priority_queue<int,vector<int>, greater<int>> pq;  // 最小堆.
//     int k;
//     KthLargest(int k, vector<int>& nums) {
//         this->k = k;
//         for(auto& n : nums)
//         {
//             pq.push(n);
//             if(pq.size() > k)
//                 pq.pop();
//         }
//     }

//     int add(int val) {
//         pq.push(val);
//         if(pq.size() > k) pq.pop();
//         return pq.top();
//     }
// };

// 剑指 Offer II 060. 出现频率最高的 k 个数字

// typedef pair<int, int> PII;
// class Solution
// {
// public:
//     vector<int> topKFrequent(vector<int> &nums, int k)
//     {
//         unordered_map<int, int> hash;
//         for (int i = 0; i < nums.size(); ++i)
//             hash[nums[i]]++;
//         priority_queue<PII, vector<PII>, greater<PII>> pq;
//         for (auto &[num, freq] : hash)
//         {
//             pq.push({freq, num});
//             if (pq.size() > k)
//                 pq.pop();
//         }
//         vector<int> res;
//         for (int i = 0; i < k; ++i)
//         {
//             res.push_back(pq.top().second);
//             pq.pop();
//         }
//         return res;
//     }
// };

// class Solution
// {
// public:
//     vector<int> topKFrequent(vector<int> &nums, int k)
//     {
//         unordered_map<int, int> cnt;
//         for (auto &n : nums)
//             cnt[n]++;
//         struct comp
//         {
//             bool operator()(const pair<int, int> &p1, const pair<int, int> &p2)
//             {
//                 return p1.second > p2.second;
//             }
//         };
//         priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;

//         for (auto &c : cnt)
//         {
//             pq.push(c);
//             if (pq.size() > k)
//                 pq.pop();
//         }
//         vector<int> res;
//         while (!pq.empty())
//         {
//             res.push_back(pq.top().first);
//             pq.pop();
//         }
//         return res;
//     }
// };

// day-2024-10-20
// 剑指 Offer II 061. 和最小的 k 个数对
// class Solution
// {
// public:
//     vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
//     {
//         auto cmp = [&nums1, &nums2](const pair<int, int> &a, const pair<int, int> &b)
//         {
//             return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; // 小根堆.
//         };

//         int m = nums1.size();
//         int n = nums2.size();
//         vector<vector<int>> ans;
//         priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
//         for (int i = 0; i < min(k, m); ++i)
//             pq.emplace(i, 0);

//         while (k-- > 0 && !pq.empty())
//         {
//             auto [x, y] = pq.top();
//             pq.pop();

//             ans.emplace_back(initializer_list<int>{nums1[x], nums2[y]});
//             if (y + 1 < n)
//                 pq.emplace(x, y + 1);
//         }
//         return ans;
//     }
// };

// day-2024-10-22
// 剑指 Offer II 062. 实现前缀树
// struct TrieNode
// {
//     TrieNode *child[26];
//     bool isEnd;

//     TrieNode()
//         : isEnd(false)
//     {
//         for (int i = 0; i < 26; ++i)
//         {
//             child[i] = nullptr;
//         }
//     }
// };

// class Trie
// {
// public:
//     TrieNode *root;

//     Trie()
//     {
//         root = new TrieNode();
//     }

//     void insert(string word)
//     {
//         TrieNode *node = root;
//         for (char c : word)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//                 node->child[i] = new TrieNode();
//             node = node->child[i];
//         }
//         node->isEnd = true;
//     }

//     bool search(string word)
//     {
//         TrieNode *node = root;
//         for (auto &c : word)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//                 return false;
//             node = node->child[i];
//         }
//         return node->isEnd;
//     }

//     bool startsWith(string prefix)
//     {
//         TrieNode *node = root;
//         for (auto &c : prefix)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//                 return false;
//             node = node->child[i];
//         }
//         return true;
//     }
// };

// day-2024-10-23
// 剑指 Offer II 063. 替换单词              648. 单词替换
// struct TrieNode
// {
//     TrieNode *child[26];
//     bool isEnd;

//     TrieNode()
//     {
//         isEnd = false;
//         for (int i = 0; i < 26; i++)
//         {
//             child[i] = nullptr;
//         }
//     }
// };

// class Trie
// {
//     TrieNode *root;

// public:
//     Trie()
//     {
//         root = new TrieNode();
//     }

//     void insert(const string &word)
//     {
//         TrieNode *node = root;
//         for (char c : word)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//             {
//                 node->child[i] = new TrieNode();
//             }
//             node = node->child[i];
//         }
//         node->isEnd = true;
//     }

//     string startsWith(const string &prefix)
//     {
//         TrieNode *node = root;
//         string result;
//         for (char c : prefix)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//             {
//                 return "";
//             }
//             result += c;
//             node = node->child[i];
//             if (node->isEnd)
//             {
//                 return result;
//             }
//         }
//         return "";
//     }
// };

// class Solution
// {
// public:
//     string replaceWords(vector<string> &dictionary, string sentence)
//     {
//         Trie trie;
//         for (const auto &str : dictionary)
//         {
//             trie.insert(str);
//         }

//         string res;
//         string tmp;
//         int j = 0;

//         for (int i = 0; i <= sentence.size(); ++i)
//         {
//             if (i == sentence.size() || sentence[i] == ' ')
//             {
//                 tmp = sentence.substr(j, i - j);
//                 j = i + 1;
//                 string prefix = trie.startsWith(tmp);
//                 if (prefix.empty())
//                 {
//                     res += tmp; // 如果不存在词根, 则加入原串.
//                 }
//                 else
//                 {
//                     res += prefix; // 否则加入词根
//                 }
//                 if (i != sentence.size())
//                 {
//                     res += ' ';
//                 }
//             }
//         }
//         return res;
//     }
// };

// 剑指 Offer II 064. 神奇的字典
// struct TrieNode
// {
//     TrieNode *child[26];
//     bool isEnd;
//     TrieNode()
//     {
//         isEnd = false;
//         for (int i = 0; i < 26; i++)
//         {
//             child[i] = nullptr;
//         }
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

//     // 插入一个单词
//     void insert(const string &word)
//     {
//         TrieNode *node = root;
//         for (char c : word)
//         {
//             int i = c - 'a';
//             if (node->child[i] == nullptr)
//             {
//                 node->child[i] = new TrieNode();
//             }
//             node = node->child[i];
//         }
//         node->isEnd = true;
//     }

//     bool searchWithOneDifference(TrieNode *node, const string &word, int pos, bool modified)
//     {
//         if (pos == word.size())
//             return modified && node->isEnd;

//         int i = word[pos] - 'a';
//         if (node->child[i])
//         {
//             if (searchWithOneDifference(node->child[i], word, pos + 1, modified))
//                 return true;
//         }
//         if (!modified)
//         {
//             for (int j = 0; j < 26; ++j)
//             {
//                 if (j != i && node->child[j])
//                     if (searchWithOneDifference(node->child[j], word, pos + 1, true))
//                         return true;
//             }
//         }

//         return false;
//     }

//     bool query(const string &word)
//     {
//         return searchWithOneDifference(root, word, 0, false);
//     }
// };

// class MagicDictionary
// {
// public:
//     Trie trie;
//     MagicDictionary()
//     {
//     }

//     void buildDict(vector<string> dictionary)
//     {
//         for (auto str : dictionary)
//         {
//             trie.insert(str);
//         }
//     }

//     bool search(string Word)
//     {
//         return trie.query(Word);
//     }
// };

// 剑指 Offer II 065. 最短的单词编码
// class TrieNode
// {
// public:
//     bool isEnd;
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

//     bool insert(const string &word)
//     {
//         TrieNode *node = root;
//         bool isNewWord = false;

//         for (char c : word)
//         {
//             int i = c - 'a';
//             if (!node->child[i])
//             {
//                 node->child[i] = new TrieNode();
//                 isNewWord = true;
//             }
//             node = node->child[i];
//         }
//         node->isEnd = true;
//         return isNewWord;
//     }
// };
// class Solution
// {
// public:
//     int minimumLengthEncoding(vector<string> &words)
//     {
//         sort(words.begin(), words.end(), [](const string &a, const string &b)
//              { return a.size() > b.size(); });

//         Trie trie;
//         int totalLen = 0;

//         for (const string &str : words)
//         {
//             string reverseWord = str;
//             reverse(reverseWord.begin(), reverseWord.end());

//             if (trie.insert(reverseWord))
//             {
//                 totalLen += reverseWord.size() + 1;
//             }
//         }
//         return totalLen;
//     }
// };

int main()
{

    return 0;
}