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

int main()
{

    return 0;
}