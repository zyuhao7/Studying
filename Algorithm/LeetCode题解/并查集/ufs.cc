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

// day-2025-5-3
// 990. 等式方程的可满足性
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
//             if (rootx == rooty)
//                 return;
//             pa[rooty] = rootx;
//         }
//     };

// public:
//     bool equationsPossible(vector<string> &equations)
//     {
//         UFS ufs(26);
//         for (int i = 0; i < equations.size(); ++i)
//         {
//             int a = equations[i][0] - 'a';
//             int b = equations[i][3] - 'a';
//             char op = equations[i][1];
//             if (op == '=')
//                 ufs.Union(a, b);
//         }
//         for (int i = 0; i < equations.size(); ++i)
//         {
//             int a = equations[i][0] - 'a';
//             int b = equations[i][3] - 'a';
//             char op = equations[i][1];
//             if (op == '!' && ufs.find(a) == ufs.find(b))
//                 return false;
//         }
//         return true;
//     }
// };

// 1579. 保证图可完全遍历
// class UFS
// {
// public:
//     vector<int> pa;
//     UFS(int n) : pa(n)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }

//     int find(int x)
//     {
//         if (x == pa[x])
//             return x;
//         return pa[x] = find(pa[x]);
//     }

//     void Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx == rooty)
//             return;
//         pa[rooty] = rootx;
//     }

//     bool isConnect(int x, int y)
//     {
//         return find(x) == find(y);
//     }

//     bool IsGraphy(int n)
//     {
//         int sz = 0;
//         for (int i = 1; i <= n; ++i)
//         {
//             if (pa[i] == i)
//                 sz++;
//         }
//         return sz == 1;
//     }
// };

// class Solution
// {
// public:
//     int maxNumEdgesToRemove(int n, vector<vector<int>> &edges)
//     {
//         UFS ufs1(n + 1), ufs2(n + 1);
//         int ans = 0;

//         // 处理类型3的边
//         for (int i = 0; i < edges.size(); ++i)
//         {
//             int type = edges[i][0], u = edges[i][1], v = edges[i][2];
//             if (type == 3)
//             {
//                 if (ufs1.isConnect(u, v))
//                 {
//                     ans++;
//                 }
//                 else
//                 {
//                     ufs1.Union(u, v);
//                     ufs2.Union(u, v);
//                 }
//             }
//         }

//         // 处理类型1和类型2的边
//         for (int i = 0; i < edges.size(); ++i)
//         {
//             int type = edges[i][0], u = edges[i][1], v = edges[i][2];
//             if (type == 1)
//             {
//                 if (ufs1.isConnect(u, v))
//                     ans++;
//                 else
//                     ufs1.Union(u, v);
//             }
//             else if (type == 2)
//             {
//                 if (ufs2.isConnect(u, v))
//                     ans++;
//                 else
//                     ufs2.Union(u, v);
//             }
//         }

//         // 判断 Alice 和 Bob 是否都能连通
//         if (ufs1.IsGraphy(n) && ufs2.IsGraphy(n))
//             return ans;
//         return -1;
//     }
// };

// 1202. 交换字符串中的元素
// class UFS
// {
// public:
//     vector<int> parent;
//     UFS(int n) : parent(n)
//     {
//         iota(parent.begin(), parent.end(), 0);
//     }

//     int find(int x)
//     {
//         if (x != parent[x])
//         {
//             parent[x] = find(parent[x]);
//         }
//         return parent[x];
//     }

//     void Union(int x, int y)
//     {
//         int rootX = find(x);
//         int rootY = find(y);
//         if (rootX != rootY)
//         {
//             parent[rootY] = rootX;
//         }
//     }
// };
// class Solution
// {
// public:
//     string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
//     {
//         int n = s.size();
//         UFS ufs(n);
//         unordered_map<int, vector<int>> group;
//         for (auto &pair : pairs)
//         {
//             ufs.Union(pair[0], pair[1]);
//         }

//         for (int i = 0; i < n; ++i)
//         {
//             int root = ufs.find(i);
//             group[root].push_back(i);
//         }

//         for (auto &[root, indices] : group)
//         {
//             vector<char> chars;
//             for (auto &idx : indices)
//                 chars.push_back(s[idx]);
//             sort(chars.begin(), chars.end());
//             int i = 0;
//             for (auto &idx : indices)
//                 s[idx] = chars[i++];
//         }
//         return s;
//     }
// };

// 1631. 最小体力消耗路径
// class UFS
// {
// public:
//     vector<int> pa;
//     UFS(int n)
//         : pa(n)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }
//     int find(int x)
//     {
//         if (x == pa[x])
//             return x;
//         return pa[x] = find(pa[x]);
//     }
//     void Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx == rooty)
//             return;
//         pa[rootx] = rooty;
//     }
//     bool Connected(int x, int y)
//     {
//         return find(x) == find(y);
//     }
// };
// class Solution
// {
// public:
//     int minimumEffortPath(vector<vector<int>> &heights)
//     {
//         int m = heights.size();
//         int n = heights[0].size();
//         vector<tuple<int, int, int>> edges;
//         auto index = [&](int i, int j)
//         {
//             return n * i + j;
//         };
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 int id = index(i, j);
//                 if (i > 0)
//                     edges.emplace_back(id - n, id, abs(heights[i][j] - heights[i - 1][j]));
//                 if (j > 0)
//                     edges.emplace_back(id - 1, id, abs(heights[i][j] - heights[i][j - 1]));
//             }
//         }
//         sort(edges.begin(), edges.end(), [](const auto &e1, const auto &e2)
//              {
//              auto&& [x1, y1, v1] = e1;
//             auto&& [x2, y2, v2] = e2;
//             return v1 < v2; });

//         UFS ufs(m * n);
//         int ans = 0;
//         for (const auto [x, y, v] : edges)
//         {
//             ufs.Union(x, y);
//             if (ufs.Connected(0, m * n - 1))
//             {
//                 ans = v;
//                 break;
//             }
//         }
//         return ans;
//     }
// };

// 778. 水位上升的泳池中游泳
// class UFS
// {
// public:
//     vector<int> pa;
//     UFS(int n)
//         : pa(n)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }
//     int find(int x)
//     {
//         if (x == pa[x])
//             return x;
//         return pa[x] = find(pa[x]);
//     }
//     void Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx == rooty)
//             return;
//         pa[rootx] = rooty;
//     }
//     bool Connected(int x, int y)
//     {
//         return find(x) == find(y);
//     }
// };
// class Solution
// {
// public:
//     int swimInWater(vector<vector<int>> &grid)
//     {
//         int m = grid.size();
//         int n = grid[0].size();
//         vector<tuple<int, int, int>> edges;
//         auto index = [&](int i, int j)
//         {
//             return n * i + j;
//         };
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 int id = index(i, j);
//                 if (i > 0)
//                     edges.emplace_back(id - n, id, max(grid[i - 1][j], grid[i][j]));
//                 if (j > 0)
//                     edges.emplace_back(id - 1, id, max(grid[i][j - 1], grid[i][j]));
//             }
//         }
//         sort(edges.begin(), edges.end(), [](const auto &e1, const auto &e2)
//              {
//              auto&& [x1, y1, v1] = e1;
//             auto&& [x2, y2, v2] = e2;
//             return v1 < v2; });

//         UFS ufs(m * n);
//         int ans = 0;
//         for (const auto [x, y, v] : edges)
//         {
//             ufs.Union(x, y);
//             if (ufs.Connected(0, m * n - 1))
//             {
//                 ans = v;
//                 break;
//             }
//         }
//         return ans;
//     }
// };

// day-2025-5-8
// 1584. 连接所有点的最小费用
// class UFS
// {
// public:
//     vector<int> pa;
//     UFS(int n)
//         : pa(n)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }
//     int find(int x)
//     {
//         if (x == pa[x])
//             return x;
//         return pa[x] = find(pa[x]);
//     }

//     bool Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx == rooty)
//             return false;
//         pa[rooty] = rootx;
//         return true;
//     }
// };
// struct edge
// {
// public:
//     int len, x, y;
//     edge(int _len, int _x, int _y)
//         : len(_len), x(_x), y(_y)
//     {
//     }
// };
// class Solution
// {
// public:
//     int minCostConnectPoints(vector<vector<int>> &points)
//     {
//         int n = points.size();
//         UFS ufs(n);
//         auto dist = [points](int i, int j)
//         {
//             return abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
//         };

//         vector<edge> edges;
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 edges.emplace_back(dist(i, j), i, j);
//             }
//         }
//         int ret = 0, num = 1;
//         sort(edges.begin(), edges.end(), [](edge a, edge b)
//              { return a.len < b.len; });
//         for (auto &[len, x, y] : edges)
//         {
//             if (ufs.Union(x, y))
//             {
//                 ret += len;
//                 num++;
//             }
//             if (num == n)
//                 break;
//         }

//         return ret;
//     }
// };