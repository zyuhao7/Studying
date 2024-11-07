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

// 

int main()
{

    return 0;
}