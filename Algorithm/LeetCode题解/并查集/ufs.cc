// day-2025-4-18
// LeetCode 547. 省份数量
// class Solution
// {
// public:
//     class UFS
//     {
//     public:
//         vector<int> pa;

//         UFS(int sz)
//             : pa(sz)
//         {
//             for (int i = 0; i < sz; ++i)
//                 pa[i] = i;
//         }
//         int find(int x)
//         {
//             if (x == pa[x])
//                 return x;
//             return pa[x] = find(pa[x]);
//         }

//         void Union(int i, int j)
//         {
//             int rx = find(i);
//             int ry = find(j);
//             if (rx == ry)
//                 return;
//             if (rx != ry)
//             {
//                 pa[ry] = rx;
//             }
//         }

//         int count()
//         {
//             int num = 0;
//             for (int i = 0; i < pa.size(); ++i)
//             {
//                 if (pa[i] == i)
//                     num++;
//             }
//             return num;
//         }
//     };

//     int findCircleNum(vector<vector<int>> &isConnected)
//     {

//         UFS ufs(isConnected.size());
//         for (int i = 0; i < isConnected.size(); ++i)
//         {
//             for (int j = 0; j < isConnected[i].size(); ++j)
//             {
//                 if (isConnected[i][j] == 1)
//                     ufs.Union(i, j);
//             }
//         }
//         return ufs.count();
//     }
// };

// 2025-4-19
// 684. 冗余连接
// class Solution
// {
// public:
//     class UFS
//     {
//     public:
//         vector<int> pa;
//         UFS(int n)
//             : pa(n)
//         {
//             iota(pa.begin(), pa.end(), 0);
//         }

//     public:
//         int find(int x)
//         {
//             if (x == pa[x])
//                 return x;
//             return pa[x] = find(pa[x]);
//         }
//         void Union(int x, int y)
//         {
//             int rootx = find(x);
//             int rooty = find(y);
//             if (rootx != rooty)
//             {
//                 pa[rooty] = rootx;
//             }
//         }
//         bool isConnected(int x, int y)
//         {
//             return find(x) == find(y);
//         }
//     };

//     vector<int> findRedundantConnection(vector<vector<int>> &edges)
//     {
//         int n = edges.size();
//         UFS ufs(n + 1);
//         for (int i = 0; i < n; ++i)
//         {
//             if (ufs.isConnected(edges[i][0], edges[i][1]))
//                 return {edges[i][0], edges[i][1]};
//             ufs.Union(edges[i][0], edges[i][1]);
//         }

//         return {-1, -1};
//     }
// };

// day-2025-4-28
// 1319 . 连通网络的操作次数
// class Solution
// {
// public:
//     class UFS
//     {
//     public:
//         vector<int> pa;
//         UFS(int n)
//             : pa(n)
//         {
//             iota(pa.begin(), pa.end(), 0);
//         }
//         int find(int x)
//         {
//             if (x == pa[x])
//                 return x;
//             return pa[x] = find(pa[x]);
//         }
//             bool Union(int x, int y)
//             {
//                 int rootx = find(x);
//                 int rooty = find(y);
//                 // 说明是冗余边
//                 if (rootx == rooty)
//                     return false;
//                 pa[rooty] = rootx;
//                 return true;
//             }
//             int count()
//             {
//                 int cnt = 0;
//                 for (int i = 0; i < pa.size(); ++i)
//                 {
//                     if (pa[i] == i)
//                         cnt++;
//                 }
//                 return cnt;
//             }
//         };

//     public:
//         int makeConnected(int n, vector<vector<int>> &conns)
//         {
//             if (conns.size() < n - 1)
//                 return -1;

//             UFS ufs(n);
//             // 冗余变数量
//             int extra = 0;
//             for (auto &con : conns)
//             {
//                 int x = con[0], y = con[1];
//                 if (!ufs.Union(x, y))
//                     extra++;
//             }

//             return ufs.count() - 1;
//         }
//     };

// 130. 被围绕的区域
// class Solution
// {
//     class UFS
//     {
//     public:
//         vector<int> pa;
//         UFS(int n)
//             : pa(n)
//         {
//             iota(pa.begin(), pa.end(), 0);
//         }
//         int find(int x)
//         {
//             if (x == pa[x])
//                 return x;
//             return pa[x] = find(pa[x]);
//         }
//         void Union(int x, int y)
//         {
//             int rootx = find(x);
//             int rooty = find(y);
//             if (rootx != rooty)
//                 pa[rooty] = rootx;
//         }
//         bool isConnected(int i, int j)
//         {
//             return find(i) == find(j);
//         }
//     };

// public:
//     void solve(vector<vector<char>> &board)
//     {
//         int n = board.size();
//         int m = board[0].size();
//         UFS ufs(m * n + 1);
//         int dummy = m * n;
//         auto index = [&](int i, int j)
//         { return i * m + j; };

//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < m; ++j)
//             {
//                 if (board[i][j] == 'O')
//                 {
//                     if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
//                         ufs.Union(index(i, j), dummy);
//                     else
//                     {
//                         if (i > 0 && board[i - 1][j] == 'O')
//                             ufs.Union(index(i - 1, j), index(i, j));
//                         if (i < n - 1 && board[i + 1][j] == 'O')
//                             ufs.Union(index(i + 1, j), index(i, j));
//                         if (j > 0 && board[i][j - 1] == 'O')
//                             ufs.Union(index(i, j - 1), index(i, j));
//                         if (j < m - 1 && board[i][j + 1] == 'O')
//                             ufs.Union(index(i, j + 1), index(i, j));
//                     }
//                 }
//             }
//         }

//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < m; ++j)
//             {
//                 if (ufs.isConnected(index(i, j), dummy))
//                     board[i][j] = 'O';
//                 else
//                     board[i][j] = 'X';
//             }
//         }
//     }
// };

// class Solution
// {
// public:
//     class UFS
//     {
//     public:
//         vector<int> pa;

//         UFS(int sz)
//             : pa(sz)
//         {
//             for (int i = 0; i < sz; ++i)
//                 pa[i] = i;
//         }
//         int find(int x)
//         {
//             if (x == pa[x])
//                 return x;
//             return pa[x] = find(pa[x]);
//         }

//         void Union(int i, int j)
//         {
//             int rx = find(i);
//             int ry = find(j);
//             if (rx == ry)
//                 return;
//             if (rx != ry)
//             {
//                 pa[ry] = rx;
//             }
//         }

//         int count()
//         {
//             int num = 0;
//             for (int i = 0; i < pa.size(); ++i)
//             {
//                 if (pa[i] == i)
//                     num++;
//             }
//             return num;
//         }
//     };

//     int findCircleNum(vector<vector<int>> &isConnected)
//     {

//         UFS ufs(isConnected.size());
//         for (int i = 0; i < isConnected.size(); ++i)
//         {
//             for (int j = 0; j < isConnected[i].size(); ++j)
//             {
//                 if (isConnected[i][j] == 1)
//                     ufs.Union(i, j);
//             }
//         }
//         return ufs.count();
//     }
// };
