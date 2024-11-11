#include <iostream>
using namespace std;

// day-2024-11-7
// 剑指 Offer II 105. 岛屿的最大面积
// 解法一: 并查集
// class UFS
// {
// public:
//     UFS(int n)
//         : pa(n),
//           rank(n, 0),
//           area(n, 1)
//     {
//         for (int i = 0; i < n; ++i)
//             pa[i] = i;
//     }
//     int find(int x)
//     {
//         if (pa[x] == x)
//             return x;
//         return pa[x] = find(pa[x]);
//     }
//     void Union(int x, int y)
//     {
//         int rootX = find(x);
//         int rootY = find(y);
//         if (rootX != rootY)
//         {
//             if (rank[rootX] > rank[rootY])
//             {
//                 pa[rootY] = rootX;
//                 area[rootX] += area[rootY];
//             }
//             else if (rank[rootX] < rank[rootY])
//             {
//                 pa[rootX] = rootY;
//                 area[rootY] += area[rootX];
//             }
//             else
//             {
//                 pa[rootY] = rootX;
//                 area[rootX] += area[rootY];
//                 rank[rootX]++;
//             }
//         }
//     }
//     int getArea(int x)
//     {
//         return area[find(x)];
//     }

// private:
//     vector<int> pa;
//     vector<int> rank;
//     vector<int> area;
// };
// class Solution
// {
// public:
//     int maxAreaOfIsland(vector<vector<int>> &grid)
//     {
//         int m = grid.size();
//         int n = grid[0].size();
//         UFS uf(m * n);
//         auto index = [&](int r, int c)
//         { return r * n + c; };

//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (grid[i][j] == 1)
//                 {
//                     if (i > 0 && grid[i - 1][j] == 1)
//                     {
//                         uf.Union(index(i - 1, j), index(i, j));
//                     }
//                     if (j > 0 && grid[i][j - 1] == 1)
//                     {
//                         uf.Union(index(i, j - 1), index(i, j));
//                     }
//                 }
//             }
//         }
//         int MaxArea = 0;
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (grid[i][j] == 1)
//                     MaxArea = max(MaxArea, uf.getArea(index(i, j)));
//             }
//         }
//         return MaxArea;
//     }
// };

// 解法二: 宽搜
// class Solution
// {
// public:
//     int BFS(vector<vector<int>> &grid, vector<vector<int>> &dirs, vector<vector<bool>> &visited, int i, int j)
//     {
//         queue<pair<int, int>> q;
//         q.push({i, j});
//         visited[i][j] = true;
//         int area = 0;
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             area++;
//             for (auto &d : dirs)
//             {
//                 int x = t.first + d[0];
//                 int y = t.second + d[1];
//                 if (x >= 0 && x < grid.size() &&
//                     y >= 0 && y < grid[0].size() &&
//                     grid[x][y] == 1 && !visited[x][y])
//                 {
//                     q.push({x, y});
//                     visited[x][y] = true;
//                 }
//             }
//         }
//         return area;
//     }
//     int maxAreaOfIsland(vector<vector<int>> &grid)
//     {
//         int m = grid.size(), n = grid[0].size();
//         vector<vector<bool>> visited(m, vector<bool>(n, false));
//         int maxArea = 0;
//         vector<vector<int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (grid[i][j] == 1 && !visited[i][j])
//                 {
//                     maxArea = max(maxArea, BFS(grid, dirs, visited, i, j));
//                 }
//             }
//         }
//         return maxArea;
//     }
// };

// day-2024-11-10
// 剑指 Offer II 106. 二分图
// class Solution
// {
// private:
//     static constexpr int UNCOLORED = 0;
//     static constexpr int RED = 1;
//     static constexpr int GREEN = 2;
//     vector<int> color;
//     bool valid;

// public:
//     void dfs(int node, int c, const vector<vector<int>> &graph)
//     {
//         color[node] = c;
//         int cNei = (c == RED ? GREEN : RED);
//         for (int ne : graph[node])
//         {
//             if (color[ne] == UNCOLORED)
//             {
//                 dfs(ne, cNei, graph);
//                 if (!valid)
//                     return;
//             }
//             else if (color[ne] != cNei)
//             {
//                 valid = false;
//                 return;
//             }
//         }
//     }

//     bool isBipartite(vector<vector<int>> &graph)
//     {
//         int n = graph.size();
//         valid = true;
//         color.assign(n, UNCOLORED);
//         for (int i = 0; i < n && valid; ++i)
//         {
//             if (color[i] == UNCOLORED)
//             {
//                 dfs(i, RED, graph);
//             }
//         }
//         return valid;
//     }
// };

// 剑指 Offer II 107. 矩阵中的距离
// class Solution
// {
// public:
//     vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
//     {
//         int m = mat.size(), n = mat[0].size();
//         vector<vector<int>> ans(m, vector<int>(n, -1));
//         queue<pair<int, int>> q;
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (mat[i][j] == 0)
//                 {
//                     ans[i][j] = 0;
//                     q.emplace(i, j);
//                 }
//             }
//         }

//         int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             for (int i = 0; i < 4; ++i)
//             {
//                 int x = dirs[i][0] + t.first;
//                 int y = dirs[i][1] + t.second;
//                 if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1)
//                 {
//                     ans[x][y] = ans[t.first][t.second] + 1;
//                     q.emplace(x, y);
//                 }
//             }
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 108. 单词演变
// class Solution
// {
// public:
//     int ladderLength(string beginWord, string endWord, vector<string> &wordList)
//     {
//         unordered_set<string> words(wordList.begin(), wordList.end());
//         queue<string> q{{beginWord}};

//         int ans = 1;
//         while (!q.empty())
//         {
//             for (int i = q.size(); i > 0; --i)
//             {
//                 string s = q.front();
//                 q.pop();
//                 for (int j = 0; j < s.size(); ++j)
//                 {
//                     char tmp = s[j];
//                     for (char k = 'a'; k <= 'z'; ++k)
//                     {
//                         s[j] = k;
//                         if (!words.count(s))
//                             continue;
//                         if (s == endWord)
//                             return ans + 1;
//                         q.push(s);
//                         words.erase(s);
//                     }
//                     s[j] = tmp;
//                 }
//             }
//             ans++;
//         }
//         return 0;
//     }
// };

// 剑指 Offer II 109. 开密码锁

// class Solution
// {
// public:
//     int openLock(vector<string> &deadends, string target)
//     {
//         unordered_set<string> set(deadends.begin(), deadends.end());
//         if (set.count(target) || set.count("0000"))
//             return -1;
//         if (target == "0000")
//             return 0;
//         unordered_set<string> vis;
//         queue<string> q;
//         q.push("0000");
//         int step = 0;
//         while (!q.empty())
//         {
//             ++step;
//             for (int i = q.size(); i > 0; --i)
//             {
//                 auto s = q.front();
//                 q.pop();
//                 for (auto &t : get(s))
//                 {
//                     if (set.count(t) || vis.count(t))
//                         continue;
//                     if (t == target)
//                         return step;
//                     q.push(t);
//                     vis.insert(t);
//                 }
//             }
//         }
//         return -1;
//     }

//     char prev(char c)
//     {
//         return c == '0' ? '9' : (char)(c - 1);
//     }

//     char next(char c)
//     {
//         return c == '9' ? '0' : (char)(c + 1);
//     }
//     vector<string> get(string &t)
//     {
//         vector<string> res;
//         for (int i = 0; i < 4; ++i)
//         {
//             char c = t[i];
//             t[i] = prev(c);
//             res.push_back(t);
//             t[i] = next(c);
//             res.push_back(t);
//             t[i] = c;
//         }
//         return res;
//     }
// };

// day-2024-11-11
// 剑指 Offer II 110. 所有路径
// class Solution
// {
// public:
//     vector<vector<int>> graph;
//     vector<vector<int>> ans;

//     vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
//     {
//         this->graph = graph;
//         vector<int> path;
//         path.push_back(0);
//         dfs(0, path);
//         return ans;
//     }
//     void dfs(int i, vector<int> &path)
//     {
//         if (i == graph.size() - 1)
//         {
//             ans.push_back(path);
//             return;
//         }
//         for (int g : graph[i])
//         {
//             path.push_back(g);
//             dfs(g, path);
//             path.pop_back();
//         }
//     }
// };

// 剑指 Offer II 116. 朋友圈
// class ufs
// {
// public:
//     vector<int> pa, size;
//     ufs(int n)
//         : pa(n),
//           size(n, 1)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }

//     int find(int x)
//     {
//         if (pa[x] == x)
//             return x;
//         return pa[x] = find(pa[x]);
//     }

//     void Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx != rooty)
//         {
//             if (size[rootx] > size[rooty])
//                 swap(rootx, rooty);
//             pa[rootx] = rooty;
//             size[rooty] += size[rootx];
//         }
//     }

//     int count()
//     {
//         int cnt = 0;
//         for (int i = 0; i < pa.size(); ++i)
//             if (pa[i] == i)
//                 cnt++;
//         return cnt;
//     }
// };

// class Solution
// {
// public:
//     int findCircleNum(vector<vector<int>> &isConnected)
//     {
//         int m = isConnected.size(), n = isConnected[0].size();
//         ufs uf(m);
//         for (int i = 0; i < m; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 if (isConnected[i][j] == 1)
//                     uf.Union(i, j);
//             }
//         }
//         return uf.count();
//     }
// };

// 剑指 Offer II 117. 相似的字符串
// class UFS
// {
// private:
//     vector<int> pa, siz;

// public:
//     UFS(int n)
//         : pa(n),
//           siz(n, 1)
//     {
//         iota(pa.begin(), pa.end(), 0);
//     }
//     void Union(int x, int y)
//     {
//         int root1 = find(x);
//         int root2 = find(y);
//         if (root1 == root2)
//             return;
//         if (siz[root1] < siz[root2])
//             swap(root1, root2);

//         pa[root2] = root1;
//         siz[root1] += siz[root2];
//     }

//     int find(int x)
//     {
//         if (x == pa[x])
//             return x;
//         return pa[x] = find(pa[x]);
//     }

//     int Size()
//     {
//         int cnt = 0;
//         for (int i = 0; i < pa.size(); ++i)
//             if (pa[i] == i)
//                 cnt++;
//         return cnt;
//     }
// };

// class Solution
// {
// public:
//     int numSimilarGroups(vector<string> &strs)
//     {
//         int n = strs.size();
//         UFS ufs(n);
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 if (isSimilar(strs[i], strs[j]))
//                     ufs.Union(i, j);
//             }
//         }
//         return ufs.Size();
//     }

//     bool isSimilar(string &s1, string &s2)
//     {
//         int cnt = 0;
//         for (int i = 0; i < s1.size(); ++i)
//         {
//             if (s1[i] != s2[i])
//                 cnt++;
//             if (cnt > 2)
//                 return false;
//         }
//         return cnt == 0 || cnt == 2;
//     }
// };

// 剑指 Offer II 118. 多余的边
// class Solution
// {
// private:
//     vector<int> pa;
//     vector<int> size;

//     int find(int x)
//     {
//         if (pa[x] == x)
//             return x;
//         return pa[x] = find(pa[x]);
//     }
//     void Union(int x, int y)
//     {
//         int rootx = find(x);
//         int rooty = find(y);
//         if (rootx != rooty)
//         {

//             if (size[rootx] < size[rooty])
//             {
//                 swap(rootx, rooty);
//             }
//             pa[rooty] = rootx;
//             size[rootx] += size[rooty];
//         }
//     }
//     bool isConnect(int x, int y)
//     {
//         return find(x) == find(y);
//     }

// public:
//     vector<int> findRedundantConnection(vector<vector<int>> &edges)
//     {
//         int n = edges.size();
//         pa.resize(n + 1);
//         size.resize(n + 1, 1);
//         for (int i = 1; i <= n; ++i)
//         {
//             pa[i] = i;
//         }
//         for (int i = 0; i < n; ++i)
//         {
//             int e1 = edges[i][0], e2 = edges[i][1];
//             if (isConnect(e1, e2))
//                 return {e1, e2};
//             Union(e1, e2);
//         }
//         return {-1, -1};
//     }
// };

// 剑指 Offer II 119. 最长连续序列
// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         unordered_set<int> set;
//         for(auto& n : nums)
//             set.insert(n);
//         int ans = 0;
//         for(int i = 0; i < nums.size(); ++i)
//         {
//             int curNum = nums[i];
//             int curLen = 1;
//             if(!set.count(curNum - 1))
//             {
//                 while(set.count(curNum + 1))
//                 {
//                     curLen ++;
//                     curNum ++;
//                 }
//             }
//             ans = max(ans, curLen);
//         }
//         return ans;
//     }
// };

int main()
{

    return 0;
}