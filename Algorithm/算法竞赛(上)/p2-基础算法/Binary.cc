#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// day-2024-11-25
// P1824 进击的奶牛

// int main()
// {
//     int n, C;
//     cin >> n >> C;
//     vector<int> stalls(n);
//     for (int i = 0; i < n; ++i)
//         cin >> stalls[i];

//     sort(stalls.begin(), stalls.end());
//     auto check = [&](int dis)
//     {
//         int cnt = 1, place = 0;
//         for (int i = 1; i < n; ++i)
//         {
//             if (stalls[i] - stalls[place] >= dis)
//             {
//                 cnt++;
//                 place = i;
//             }
//         }
//         if (cnt >= C)
//             return true;
//         return false;
//     };

//     int l = stalls[0], r = stalls[n - 1] - stalls[0], result = 0;
//     while (l < r)
//     {
//         int m = l + (r - l) / 2;
//         if (check(m))
//         {
//             result = m;
//             l = m + 1;
//         }
//         else
//         {
//             r = m;
//         }
//     }
//     cout << result;
//     return 0;
// }

// day-2024-11-19
// 二分. 整数二分 实数二分
// [left, right) 左闭右开
// int binary_search(int *a, int n, int x)
// {
//     // 此时数据是 a[0] - a[n - 1]
//     int left = 0, right = n;
//     while (left < right)
//     {
//         int mid = left + (right - left) / 2;
//         if (a[mid] >= x))
//             right = mid;
//         else
//             left = mid + 1;
//     }
//     return l;
// }

// 找 x 或者 x 的前驱.
// int binary_search2(int *a, int n, int x)
// {
//     int left = 0, right = n;
//     while (left < right)
//     {
//         int mid = left + (right - left + 1) / 2;
//         if (a[mid] <= x))
//             left = mid;
//         else
//             right = mid - 1;
//     }
// }
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <queue>
// #include <numeric>
// #include <climits>
// using namespace std;

// struct Edge
// {
//     int to, cost;
// };

// const int inf = INT_MAX;

// bool CanReach(int maxFee, int n, int b, vector<int> &f, vector<vector<Edge>> &g)
// {
//     vector<int> Health(n + 1, -1);

//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
//     pq.push({b, 1});
//     Health[1] = b;

//     while (!pq.empty())
//     {
//         auto [curHealth, node] = pq.top();
//         pq.pop();
//         if (curHealth < Health[node])
//             continue;
//         for (auto &edge : g[node])
//         {
//             int next = edge.to;
//             int cost = edge.cost;
//             if (f[next] > maxFee)
//                 continue;

//             int NewHealth = curHealth - cost;

//             if (NewHealth < 0)
//                 continue;

//             if (NewHealth > Health[next])
//             {
//                 Health[next] = NewHealth;
//                 pq.emplace(NewHealth, next);
//             }
//         }
//     }
//     return Health[n] >= 0;
// }

// int main()
// {
//     int n, m, b;
//     cin >> n >> m >> b;
//     vector<int> f(n + 1);
//     for (int i = 1; i <= n; ++i)
//         scanf("%d", &f[i]);

//     vector<vector<Edge>> g(n + 1);
//     for (int j = 0; j < m; ++j)
//     {
//         int a, b, c;
//         scanf("%d%d%d", &a, &b, &c);
//         g[a].push_back({b, c});
//         g[b].push_back({a, c});
//     }
//     long long l = f[1], r = *max_element(f.begin() + 1, f.end()), ans = -1;
//     while (l <= r)
//     {
//         int m = l + (r - l) / 2;
//         if (CanReach(m, n, b, f, g))
//         {
//             ans = m;
//             r = m - 1;
//         }
//         else
//             l = m + 1;
//     }
//     if (ans == -1)
//     {
//         cout << "AFK";
//     }
//     else
//         cout << ans << endl;
//     return 0;
// }

// int main()
// {
//     // 序列化分

//     vector<int> seq({2, 2, 3, 4, 5, 1});
//     int n = seq.size(), k = 3;
//     int l = *max_element(seq.begin(), seq.end());
//     int r = accumulate(seq.begin(), seq.end(), 0);
//     cout << l << " " << r << endl;

//     auto check = [&](int target)
//     {
//         int sum = 0, cnt = 1;
//         for (auto s : seq)
//         {
//             if (sum + s > target)
//             {
//                 ++cnt;
//                 if (cnt > k)
//                     return false;
//                 sum = s;
//             }
//             else
//                 sum += s;
//         }
//         return true;
//     };

//     while (l < r)
//     {
//         int m = l + r >> 1;
//         if (check(m))
//             r = m;
//         else
//             l = m + 1;
//     }
//     cout << l << endl;
//     return 0;
// }