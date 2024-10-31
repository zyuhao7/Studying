#include <iostream>
// day-2024-10-31
using namespace std;
// Bone collector (hdu 2602)
const int N = 1010;
int dp[N][N]; // dp[i][j] 表示前 i 个骨头, 背包容量为 j 时候的最大价值.
int v[N], w[N];
int main()
{
    int n, N, C;
    cin >> n;
    while (n--)
    {
        cin >> N >> C;
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 0; j <= C; ++j)
            {
                dp[i][j] = 0;
            }
        }

        for (int i = 1; i <= N; ++i)
        {
            cin >> w[i]; // 输入每个骨头的价值
        }

        for (int i = 1; i <= N; ++i)
        {
            cin >> v[i]; // 输入每个骨头的体积.
        }

        for (int i = 1; i <= N; ++i)
        {
            for (int j = 0; j <= C; ++j)
            {
                if (v[i] > j)
                    dp[i][j] = dp[i - 1][j];
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
                }
            }
        }
        cout << dp[N][C] << endl;

        // 打印路径
        int j = C; // 当前剩余容量
        for (int i = N; i >= 1; --i)
        {
            if (j >= v[i] && dp[i][j] == dp[i - 1][j - v[i]] + w[i])
            {
                cout << "Selected item " << i << " worth: " << w[i] << endl;
                j -= v[i]; // 更新剩余容量
            }
        }
    }
    return 0;
}