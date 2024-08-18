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

// day-2024-8-18
//                                            位运算

// 面试题 10 二进制中 1的个数.
// 实现函数满足输入一个数, 输出该数二进制中 1的 个数, 比如 9, 1001, 输出 2.
/*
int NumOneOfBinary1(int x)
{
    int cnt = 0;
    for (int i = 0; i < 32; ++i)
    {
        if (x & (1 << i))
            cnt++;
    }
    return cnt;
}

int NumOneOfBinary2(int x)
{
    int cnt = 0;
    while (x)
    {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

int main()
{


    cout << NumOneOfBinary1(0x7FFFFFFF) << endl;
    cout << NumOneOfBinary2(0x7FFFFFFF) << endl;
    cout << NumOneOfBinary1(0xC0000000) << endl;
    cout << NumOneOfBinary2(0xC0000000);
    return 0;
}
*/

// 面试题 11 数值的整数次方
// 实现函数 double Power(double base, int exponent), 求 base 的 exponent 次方.

/*
double Power1(double base, int exp)
{
    double res = 1.0;
    while (exp)
    {
        res *= base;
        exp--;
    }
    return res;
}

// 书解.

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    // double result = 1.0;
    // for (int i = 1; i <= exponent; ++i)
    //     result *= base;
    // return result;

    if (exponent == 0)
        return 1.0;
    if (exponent == 1)
        return base;
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result; // 快速幂同法.
    if (exponent & 0x1 == 1)
        result *= base;
    return result;
}

bool Equal(double num1, double num2)
{
    return (num1 - num2 > -0.0000001 && num1 - num2 < 0.0000001) ? true : false;
}

double Power2(double base, int exponent)
{
    if (Equal(base, 0.0))
        return 0.0;
    if (exponent == 0)
        return 1.0;

    unsigned int absExponent = (unsigned int)exponent;
    if (exponent < 0)
        absExponent = (unsigned int)(-exponent);

    double result = PowerWithUnsignedExponent(base, absExponent);
    if (exponent < 0)
        result = 1.0 / result;

    return result;
}

int main()
{
    // cout << Power1(3.0, -3) << endl; // 负数？
    cout << Power2(3.0, -3) << endl;
    cout << Power2(3.0, 3) << endl;
    cout << Power2(3.0, 0) << endl;

    return 0;
}
*/

