#include <iostream>
#include <cstring>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;

// hdu 1159	Common Subsequence
// const int N = 1010;
// int dp[N][N];

// int main()
// {
//     string A, B;
//     while (cin >> A >> B)
//     {
//         int n = A.size();
//         int m = B.size();
//         memset(dp, 0, sizeof(dp));

//         for (int i = 1; i <= n; ++i)
//         {
//             for (int j = 1; j <= m; ++j)
//             {
//                 if (A[i - 1] == B[j - 1])
//                     dp[i][j] = dp[i - 1][j - 1] + 1;
//                 else
//                     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
//             }
//         }
//         cout << dp[n][m] << endl;
//     }
// }

// P2347 [NOIP1996 提高组] 砝码称重
// const int N = 6, M = 1010;
// int m[N], v[N] = {1, 2, 3, 5, 10, 20};
// int new_v[M];
// int dp[M];

// // 多重背包二进制优化
// int main()
// {
//     for (int i = 0; i < 6; ++i)
//         scanf("%d", &m[i]);

//     int sum = 0, new_n = 0;

//     for (int i = 0; i < N; ++i)
//     {
//         int weight = v[i];
//         for (int j = 1; j <= m[i]; j <<= 1)
//         {
//             m[i] -= j;
//             new_v[new_n++] = j * weight;
//             sum += j * weight;
//         }
//         if (m[i] > 0)
//         {
//             new_v[new_n++] = m[i] * weight;
//             sum += m[i] * weight;
//         }
//     }

//     dp[0] = 1;
//     for (int i = 0; i < new_n; ++i)
//     {
//         for (int j = sum; j >= new_v[i]; --j)
//         {
//             dp[j] |= dp[j - new_v[i]];
//         }
//     }

//     int cnt = 0;
//     for (int i = 1; i <= sum; ++i)
//     {
//         if (dp[i])
//             cnt++;
//     }

//     cout << "Total=" << cnt << endl;
// }

// day-2024-11-2
// using namespace std;
// 多重背包
// 宝物筛选(洛谷 P1776)
// 二进制拆分优化
// const int N = 1e5 + 10;
// int v[N], w[N], m[N];
// int new_n;
// int new_v[N], new_w[N], new_m[N]; // 二进制拆分后的新物品

// int n, C, dp[N];
// int main()
// {
//     cin >> n >> C;
//     for (int i = 1; i <= n; ++i)
//         cin >> w[i] >> v[i] >> m[i];
//     new_n = 0;
//     // 二进制拆分
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = 1; j <= m[i]; j <<= 1) // 二进制枚举 1 2 4 ...
//         {
//             m[i] -= j;
//             new_v[++new_n] = j * v[i];
//             new_w[new_n] = j * w[i];
//         }
//         if (m[i]) // 最后一个是余数.
//         {
//             new_v[++new_n] = m[i] * v[i];
//             new_w[new_n] = m[i] * w[i];
//         }
//     }

//     for (int i = 1; i <= new_n; ++i) // 枚举物品
//     {
//         for (int j = C; j >= new_v[i]; --j) // 枚举背包容量
//         {
//             dp[j] = max(dp[j], dp[j - new_v[i]] + new_w[i]);
//         }
//     }
//     cout << dp[C] << endl;
//     return 0;
// }

// 解法一 滚动数组版本的多重背包(超时) 90
// const int N = 1e5 + 10;
// int v[N], w[N], m[N];
// int n, C, dp[N];
// int main()
// {
//     cin >> n >> C;
//     for (int i = 1; i <= n; ++i)
//         cin >> w[i] >> v[i] >> m[i];
//     for (int i = 1; i <= n; ++i) // 枚举物品
//     {
//         for (int j = C; j >= v[i]; --j) // 枚举背包容量
//         {
//             for (int k = 1; k <= m[i] && j >= k * v[i]; ++k)
//             {
//                 dp[j] = max(dp[j], dp[j - k * v[i]] + k * w[i]);
//             }
//         }
//     }
//     cout << dp[C] << endl;
//     return 0;
// }

// ACboy needs your help(hdu 1712) 分组背包.
// const int N = 105;
// int dp[N];
// int v[N][N], w[N][N];
// int n, m;
// int main()
// {
//     while (scanf("%d%d", &n, &m))
//     {
//         for (int i = 1; i <= n; ++i)
//         {
//             for (int k = 1; k <= m; ++k)
//             {
//                 scanf("%d", &w[i][k]);
//                 v[i][k] = k;
//             }
//         }
//         memset(dp, 0, sizeof(dp));

//         for (int i = 1; i <= n; ++i)
//         {
//             for (int j = m; j > 0; --j)
//             {
//                 for (int k = 1; k <= m; ++k)
//                 {
//                     if (j >= v[i][k]) // 考虑同一组内选择的最大价值.
//                         dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k]);
//                 }
//             }
//         }
//         cout << dp[m] << endl;
//     }
//     return 0;
// }
// const int N = 105;
// int dp[N][N];
// int v[N][N], w[N][N];
// int n, m;
// int main()
// {
//     while (scanf("%d%d", &n, &m))
//     {
//         memset(dp, 0, sizeof(dp));
//         for (int i = 1; i <= n; ++i)
//         {
//             for (int k = 1; k <= m; ++k)
//             {
//                 scanf("%d", &w[i][k]);
//                 v[i][k] = k;
//             }
//         }
//         for (int i = 1; i <= n; ++i)
//         {
//             for (int j = m; j > 0; --j)
//             {
//                 for (int k = 1; k <= m; ++k)
//                 {
//                     if (j >= v[i][k]) // 考虑同一组内选择的最大价值.
//                         dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i][k]] + w[i][k]);
//                 }
//             }
//         }
//         cout << dp[n][m] << endl;
//     }

//     return 0;
// }

// ---------------------

// Bone collector (hdu 2602)
// const int N = 1010;
// int dp[N]; // 自我滚动.
// int v[N], w[N];
// int solve(int n, int C)
// {
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = C; j >= v[i]; --j)
//         {
//             dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
//         }
//     }
//     return dp[C];
// }

// const int N = 1010;
// int dp[2][N]; // 滑动数组 交替滚动.
// int v[N], w[N];
// int solve(int n, int C)
// {
//     int now = 1, old = 0;
//     for (int i = 1; i <= n; ++i)
//     {
//         swap(old, now);
//         for (int j = 0; j <= C; ++j)
//         {
//             if (j < v[i])
//                 dp[now][j] = dp[old][j];
//             else
//                 dp[now][j] = max(dp[old][j], dp[old][j - v[i]] + w[i]);
//         }
//     }
//     return dp[now][C];
// }
// int main()
// {
//     int n, N, C;
//     cin >> n;
//     while (n--)
//     {
//         cin >> N >> C;
//         for (int i = 1; i <= N; ++i)
//         {
//             cin >> w[i]; // 输入每个骨头的价值
//         }

//         for (int i = 1; i <= N; ++i)
//         {
//             cin >> v[i]; // 输入每个骨头的体积.
//         }
//         cout << solve(N, C);
//     }
// }

// #include <iostream>
// day-2024-10-31
// using namespace std;

// Bone collector (hdu 2602)
// const int N = 1010;
// int dp[N][N]; // dp[i][j] 表示前 i 个骨头, 背包容量为 j 时候的最大价值.
// int v[N], w[N];
// int main()
// {
//     int n, N, C;
//     cin >> n;
//     while (n--)
//     {
//         cin >> N >> C;
//         for (int i = 1; i <= N; ++i)
//         {
//             for (int j = 0; j <= C; ++j)
//             {
//                 dp[i][j] = 0;
//             }
//         }

//         for (int i = 1; i <= N; ++i)
//         {
//             cin >> w[i]; // 输入每个骨头的价值
//         }

//         for (int i = 1; i <= N; ++i)
//         {
//             cin >> v[i]; // 输入每个骨头的体积.
//         }

//         for (int i = 1; i <= N; ++i)
//         {
//             for (int j = 0; j <= C; ++j)
//             {
//                 if (v[i] > j)
//                     dp[i][j] = dp[i - 1][j];
//                 else
//                 {
//                     dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
//                 }
//             }
//         }
//         cout << dp[N][C] << endl;

//         // 打印路径
//         int j = C; // 当前剩余容量
//         for (int i = N; i >= 1; --i)
//         {
//             if (j >= v[i] && dp[i][j] == dp[i - 1][j - v[i]] + w[i])
//             {
//                 cout << "Selected item " << i << " worth: " << w[i] << endl;
//                 j -= v[i]; // 更新剩余容量
//             }
//         }
//     }
//     return 0;
// }
