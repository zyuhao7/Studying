#include <iostream>
#include <vector>

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
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;
const int N = 1e5 + 10;
int a[N], b[N], c[N], f[N];
int n, m, blood;

// P1462 通往奥格瑞玛的道路

int main()
{
    cin >> n >> m >> blood;

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &f[i]);
    }
    // 公路信息.
    for (int j = 0; j < m; ++j)
    {
        scanf("%d %d %d", &a[j], &b[j], &c[j]);
    }
    
    return 0;
}

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