#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <vector>
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
        if (res < q[i])
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

// 面试题 12 打印 1 到 最大的 n 位数.
// 输入数字 n, 打印出从 1 到 n 位十进制数, 比如输入3, 则 1,2,3...999.

/*
// 自解.
typedef long long ll;
// 假如最大数不超过 long long.
void Print1ToNdigits(int n)
{
    if (n == 0)
        return;
    ll maxNum = 1;
    for (int i = 0; i < n; ++i)
    {
        maxNum *= 10;
    }
    for (int i = 1; i < maxNum; ++i)
    {
        cout << i << " ";
    }
    cout << endl;
}

// 假如最大数超过 ll.
// 想法: 先将最大的 n 位数 + 1 用字符串拼接出来, 比如 n = 7, 则  MaxNum = "10000000", 然后给一个空串,初始化为 1, 比较与MaxNum的
// 大小, 如果小于的话则 string "++", 定义一个字符输出, 如果小于 8的话, 直接用下一个字符替换, 如果是 9 的话需要增加一个长度,
// 但是还需要将 9 替换为 1 后面拼接个0.
void Print1ToNdigits2(int n)
{
    if (n == 0)
        return;
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    string MaxNum = "1";
    for (int i = 1; i <= n; ++i)
        MaxNum += "0";
    string num = "1";

    while (num.size() <= MaxNum.size())
    {
        cout << num << " ";
        int t = num[num.size() - 1] - '0'; // 求得最后一位的整数值.
        int len = num.size() - 1;
        if (t == 9) // 如果最后一位是 9.
        {
            num[len] = '1';
            num += '0';
        }
        else
        {
            num[len] = digits[t + 1];
        }

        if (num.size() == MaxNum.size())
            break;
    }
} // 有点毛病, 有点难整.

// 书解.
bool Increment(char *number)
{
    bool isOverFlow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);

    for (int i = nLength - 1; i >= 0; i--)
    {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1)
            nSum++;
        if (nSum >= 10)
        {
            if (i == 0)
                isOverFlow = true;
            else
            {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }
        else
        {
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverFlow;
}

void PrintNumber(char *number)
{

    bool isBeginning0 = true;
    int nLength = strlen(number);

    for (int i = 0; i < nLength; ++i)
    {
        if (isBeginning0 && number[i] != '0')
            isBeginning0 = false;
        if (!isBeginning0)
        {
            printf("%c", number[i]);
        }
    }
    cout << " ";
}

void Print1ToNdigits3(int n)
{
    if (n <= 0)
        return;
    char *number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';

    while (!Increment(number))
    {
        PrintNumber(number);
    }
    delete[] number;
}

int main()
{
    // Print1ToNdigits(2);
    Print1ToNdigits3(2);

    return 0;
}
*/

void dfs(std::string &number, int n, int index)
{
    // 000 3 0
    if (index == n)
    {
        // 去掉前导0
        int pos = 0;
        while (pos < n && number[pos] == '0')
            ++pos;
        if (pos != n)
        {
            std::cout << number.substr(pos) << " ";
        }
        return;
    }

    for (char c = '0'; c <= '9'; ++c)
    {
        number[index] = c;
        dfs(number, n, index + 1);
    }
}

void printNumbers(int n)
{
    std::string number(n, '0'); // 000
    dfs(number, n, 0);
    std::cout << std::endl;
}

// int main()
// {
//     int n;
//     std::cin >> n;
//     printNumbers(n);
//     return 0;
// }

// 面试题 13 在 O(1) 时间删除链表节点
/*
struct ListNode
{
    int _Val;
    ListNode *_next;
};

void DeleteNode(ListNode **pListHead, ListNode *pToBeDeleted)
{
    if (pListHead == nullptr || *pListHead == nullptr)
        return;
    // 思路.
    // Node1 -> Node2 -> DeleteNode -> Node3
    //   Node2->next = DeleteNode->next ？ 完了？ ..
    // 考虑: 1. delete 是头 ? other
    // 如果是头的话. 就需要重新构造头, 但是结构中没有头结点, 故 直接置空就行了吧? other的话, 直接指向下一个就行.
    // if (*pListHead == pToBeDeleted)
    // {
    //     *pListHead = pToBeDeleted->_next;
    //     delete pToBeDeleted;
    //     return;
    // }
    // 不是, Node2 不遍历怎么找？？

    //  Node1 -> Node2 -> DeleteNode -> Node3 -> Node4
    //  Node1 -> Node2 -> Node3 -> Node3 -> Node4
    //  Node1 -> Node2 -> Node3-> Node4
    // 妙~
    // 要删除的节点不是尾结点.
    if (pToBeDeleted->_next != NULL)
    {
        ListNode *pNext = pToBeDeleted->_next;
        pToBeDeleted->_Val = pNext->_Val;
        pToBeDeleted->_next = pNext->_next;
        delete pNext;
        pNext = NULL;
    }
    // 链表只有一个节点.
    else if (*pListHead == pToBeDeleted)
    {
        delete pToBeDeleted;
        pToBeDeleted = NULL;
        *pListHead = NULL;
    }
    // 链表有多个节点, 删除尾结点.
    else
    {
        ListNode *pNode = *pListHead;
        while (pNode->_next != pToBeDeleted)
        {
            pNode = pNode->_next;
        }
        pNode->_next = NULL;
        delete pToBeDeleted;
        pToBeDeleted = NULL;
    }
}
*/

// 面试题 14 调整数组顺序使奇数位于偶数前面
// 实现函数调整数组中数组顺序, 使得所有奇数位于数组的前半部分, 偶数后半部分.
/*
void solve(int a[], int n)
{
    int i = -1, j = n;
    while (i < j)
    {
        do
            ++i;
        while (a[i] % 2 != 0);
        do
            --j;
        while (a[j] % 2 == 0);
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]); // 3 7 3 1 7 9 4 8 2 2 4
                             // 考虑代码整体框架不变, 只是变得比较函数, 因此可以把比较函数抽离出来,构成一个函数指针的形式.
}

int main()
{
    int a[] = {2, 7, 3, 1, 4, 9, 7, 8, 2, 3, 4};
    solve(a, sizeof(a) / sizeof(a[0]));

    return 0;
}
*/