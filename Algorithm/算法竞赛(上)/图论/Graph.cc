#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
// day-2024-11-22
// 图的存储

// 法 1 : 邻接矩阵
// const int N = 1010, M = 1010;
// int n, m, a, b, c;
// int w[N][N]; // 边权.
// int vis[N];
// void dfs(int u)
// {
//     vis[u] = true;
//     for (int v = 1; v <= n; ++v)
//     {
//         if (w[u][v])
//         {
//             printf("%d %d %d\n", u, v, w[u][v]);
//             if (vis[v])
//                 continue;
//             dfs(v);
//         }
//     }
// }

// int main()
// {
//     cin >> n >> m;
//     for (int i = 1; i <= m; ++i)
//     {
//         cin >> a >> b >> c;
//         w[a][b] = c;
//         // w[b][a] = c;
//     }
//     dfs(1);
//     return 0;
// }

// 法 2 边集数组

// const int N = 1010, M = 1010;
// int n, m, a, b, c;
// struct edge
// {
//     int u, v, w;
// } e[M]; // 边集
// int vis[N];

// void dfs(int u)
// {
//     vis[u] = true;
//     for (int i = 1; i <= m; ++i)
//     {
//         if (e[i].u == u)
//         {
//             printf("%d ================= \n", i);
//             int u = e[i].u, v = e[i].v, w = e[i].w;
//             printf("%d %d %d\n", u, v, w);
//             if (vis[v])
//                 continue;
//             dfs(e[i].v);
//         }
//     }
// }

// int main()
// {
//     cin >> n >> m;
//     for (int i = 1; i <= m; ++i)
//     {
//         cin >> a >> b >> c;
//         e[i] = {a, b, c};
//     }
//     dfs(1);
//     return 0;
// }

// 方法 3 : 邻接表
// const int N = 510;
// int n, m, a, b, c;
// struct edge
// {
//     int v, w;
// };
// vector<edge> e[N];

// void dfs(int u, int fa)
// {
//     for (auto ed : e[u])
//     {
//         int v = ed.v, w = ed.w;
//         if (v == fa)
//             continue;
//         printf("%d %d %d \n", u, v, w);
//         dfs(v, u);
//     }
// }

// int main()
// {
//     cin >> n >> m;
//     for (int i = 1; i <= m; ++i)
//     {
//         cin >> a >> b >> c;
//         e[a].push_back({b, c});
//     }
//     dfs(1, 0);
//     return 0;
// }

// 方法 4 链式前向星
const int N = 510, M = 3000;
int n, m, a, b, c;
struct edge
{
    int v, w, ne;
};

edge e[M];     // 边集.
int idx, h[N]; // 点的第一条出边.

void add(int a, int b, int c)
{
    e[idx] = {b, c, h[a]};
    h[a] = idx++;
}
void dfs(int u, int fa)
{
    for (int i = h[u]; ~i; i = e[i].ne)
    {
        int v = e[i].v, w = e[i].w;
        if (v == fa)
            continue;
        printf("%d %d %d \n", u, v, w);
        dfs(v, u);
    }
}
int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i)
    {
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    dfs(1, 0);
}
