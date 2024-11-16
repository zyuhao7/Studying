#include <iostream>
using namespace std;
// day-2024-11-13

// 112	最长递增路径
// class Solution {
// public:
//     static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//     int rows;
//     int colums;
//     int longestIncreasingPath(vector<vector<int>>& matrix) {
//         if(matrix.empty() || matrix[0].size() == 0) return 0;
//         rows = matrix.size();
//         colums = matrix[0].size();

//         vector<vector<int>> memo(rows, vector<int>(colums, 0));
//         int ans = 0;
//         for(int i = 0; i < rows;++i)
//         {
//             for(int j = 0; j < colums; ++j)
//             {
//                 ans = max(ans, dfs(matrix, i, j, memo));
//             }
//         }
//         return ans;
//     }
//     int dfs(vector<vector<int>>& mat, int row, int col, vector<vector<int>>& memo)
//     {
//         if(memo[row][col] != 0)
//         {
//             return memo[row][col];
//         }
//         ++memo[row][col];

//         for(int i = 0; i < 4; ++i)
//         {
//             int nx = row + dirs[i][0], ny = col + dirs[i][1];
//             if(nx >=0 && nx < mat.size() && ny>=0 &&ny< mat[0].size() && mat[nx][ny] > mat[row][col])
//             {
//                 memo[row][col] = max(memo[row][col], dfs(mat, nx, ny, memo) + 1);
//             }
//         }
//         return memo[row][col];
//     }
// };


int main()
{

    return 0;
}