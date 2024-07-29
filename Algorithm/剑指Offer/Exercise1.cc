#include <iostream>
using namespace std;
// 查找和数组
// 面试题 8 旋转数组的最小数字
//     把一个数组最开始的若干元素搬到数组的末尾,
//     我们称之为数组的旋转.例如{3, 4, 5, 1, 2} 为{1, 2, 3, 4, 5} 的一个旋转, 该数组的最小值为 1. 自解.

#if 0
int find(int q[], int len)
{
    int l = -1, r = len;
    int m;
    while (l + 1 < r)
    {
        m = q[l + r >> 1];
        if (q[l] < m)
            l = m;
        if (q[r] > m)
            r = m;
    }
    return m;
}

int MinInOrder(int q[], int l, int r);
// 书解, 类似上述我的思路.
int Min(int q[], int len)
{
    if (q == NULL || len <= 0)
        return -1;
    int l = 0, r = len - 1, m = l;

    while (q[l] >= q[r])
    {
        if (r - l == 1)
        {
            m = r;
            break;
        }
        m = l + r >> 1;

        // 如果下标为 l m r 指向的三个数字相等,循序查找.
        if (q[l] == q[m] && q[m] == q[r])
            return MinInOrder(q, l, r);
        if (q[m] > q[l])
            l = m;
        else if (q[m] <= q[r])
            r = m;
    }
    return q[m];
}

int MinInOrder(int q[], int l, int r)
{
    int res = q[l];
    for (int i = l + 1; i <= r; ++i)
    {
        if (res > q[i])
            res = q[i];
    }
    return res;
}

int main()
{
    int arr[] = {3, 4, 5, -3, -1, 0, 1, 2};
    int Min_num = find(arr, 8);
    int Min_num2 = Min(arr, 8);

    cout << Min_num << endl;
    cout << Min_num2 << endl;

    int arr2[] = {1, 0, 1, 1, 1};
    int Min_num3 = find(arr2, 5);
    int Min_num4 = Min(arr2, 5);

    cout << Min_num3 << endl;
    cout << Min_num4 << endl;

    return 0;
}

#endif

#if 0
// 面试题 9 斐波那契序列
// 递归低效, 写出可以回去等通知了.

long long Fibonacci(unsigned int n)
{
    if (n <= 1)
        return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

long long Fibonacci2(unsigned int n)
{
    int n1 = 0, n2 = 1;
    for (int i = 2; i <= n; ++i)
    {
        int t = n2;
        n2 = n1 + n2;
        n1 = t;
    }
    return n2;
}

int main()
{
    cout << Fibonacci2(10) << endl;

    return 0;
}
#endif