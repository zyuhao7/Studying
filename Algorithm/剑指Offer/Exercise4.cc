#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
// 2024-9-2
// 面试题 30 最小的 K 个数
/*
class Solution
{
public:
    int partition(vector<int> &nums, int l, int r)
    {
        int pivot = nums[r];
        int i = l - 1;
        for (int j = l; j < r; ++j)
        {
            if (nums[j] <= pivot)
                swap(nums[++i], nums[j]);
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }

    int randomized_partition(vector<int> &nums, int l, int r)
    {
        int i = rand() % (r - l + 1) + l;
        swap(nums[i], nums[r]);
        return partition(nums, l, r);
    }

    void randomized_selected(vector<int> &arr, int l, int r, int k)
    {
        if (l >= r)
            return;
        int pos = randomized_partition(arr, l, r);
        int num = pos - l + 1;
        if (k == num)
            return;
        else if (num < k)
            return randomized_selected(arr, pos + 1, r, k - num);
        else
            return randomized_selected(arr, l, pos - 1, k);
    }

    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(0));
        randomized_selected(arr, 0, arr.size() - 1, k);
        vector<int> res;
        for (int i = 0; i < k; ++i)
            res.push_back(arr[i]);
        return res;
    }
};
*/

// 面试题 31 连续数组的最大和
// 输入一个整形数组, 数组中正负都有, 找到一个或连续多的整数组成子数组, 求所有子数组和中的最大值.

// 先从前往后依次相加, 如果小于等于 0, 则更新 result 为下一个可用值.
/*
int MaxSumOfConArray(int arr[], int length)
{
    int result = 0;
    for (int i = 0; i < length - 1; ++i)
    {
        int t = arr[i];
        if (result + t < 0)
        {
            result = arr[i + 1];
            i++;
        }
        else
            result += arr[i];
    }
    return result;
};

int dp(int arr[], int length)
{
    if (arr == NULL || length <= 0)
        return -1;

    vector<int> f(length);
    f[0] = arr[0];
    for (int i = 1; i < length; ++i)
        f[i] = max(arr[i], f[i - 1] + arr[i]);

    int max = 0;
    for (int i = 0; i < length; ++i)
    {
        if (f[i] >= max)
            max = f[i];
    }
    return max;
}
int main()
{
    int a[] = {1, -2, 3, 10, -4, 7, 2, -5};
    cout << MaxSumOfConArray(a, sizeof(a) / sizeof(a[0])) << endl;
    cout << dp(a, sizeof(a) / sizeof(a[0])) << endl;
    return 0;
}
*/

// day-2024-9-3
// 面试题 32 从 1 到 n 整数中 1出现的次数
// 例如 12,  从 1 到 12, 1出现的次数包括 1, 10, 11, 12 共五次.
// 暴力做法 - 从 1 到 n 遍历, 取每位值与 1 比较.
/*
int NumOneOfVal(int val)
{
    int one = 0;
    while (val)
    {
        if (val % 10 == 1)
            one++;
        val /= 10;
    }
    return one;
}

int FromOneToN(int n)
{
    int sumOne = 0;
    for (int i = 1; i <= n; ++i)
    {
        sumOne += NumOneOfVal(i);
    }
    return sumOne;
} // 效率太低!
// O(lgN) 的思路有点难想
// 比如 n = 21345, 先考虑 1 ~ 1345  再考虑 1346 ~ 21345 从 1346 ~ 21345 万位存在1 的情况 是 10000 ~ 19999 共 1^4 个.
// 如果 n 是 12345, 那么 1存在万位的个数是 1000~12345  共 2346 个了. 接下来分析 1345 ~ 21345 数字中后四位1出现的次数是
// 2000, 分成 1345 ~ 11345 和 11346 ~ 21345 ...
//

int main()
{
    cout << FromOneToN(21);
    return 0;
}
*/

// 面试题 33 把数组排成最小的数
// 输入一个正整数数组, 把数组中的所有数字排列成一个数, 打印能拼接出的所有数字中最小的一个. 例如输如 {3,32,321}
// 则打印出 321323
// 思路: 现将数组排序 -> 先根据数据大小 如果位数相同 降序  如果 位数不同, 则位数小的放在前面.

/*
class Solution
{
public:
    string crackPassword(vector<int> &password)
    {
        vector<string> strs;
        for (int i = 0; i < password.size(); ++i)
        {
            strs.push_back(to_string(password[i]));
        }
        sort(strs.begin(), strs.end(), [](string &a, string &b)
             { return a + b < b + a; });
        string res;
        for (auto s : strs)
            res += s;
        return res;
    }
};
*/

// 面试题 34 丑数
// 我们把只包含因子 2、 3、 5 的数称为 丑数 (Ugly Number). 求从小到大的顺序的第1500个丑数. 习惯 1 是第一个丑数.
/*
bool is_uglyNumer(int n)
{
    while (n % 2 == 0)
        n /= 2;
    while (n % 3 == 0)
        n /= 3;
    while (n % 5 == 0)
        n /= 5;
    return n == 1 ? true : false;
}

int GetUglyNumber(int index)
{
    if (index <= 0)
        return 0;
    int n = 0;
    int uglyFound = 0;

    while (uglyFound < index)
    {
        ++n;
        if (is_uglyNumer(n))
        {
            ++uglyFound;
        }
    }
    return n;
} // 耗时.

int Min(int n1, int n2, int n3);
int GetUglyNumber1(int index)
{
    if (index <= 0)
        return 0;
    int *pa = new int[index];
    pa[0] = 1;
    int nextUglyIndex = 1;

    int *p1 = pa;
    int *p2 = pa;
    int *p3 = pa;

    while (nextUglyIndex < index)
    {
        int MinNumber = Min(*p1 * 2, *p2 * 3, *p3 * 5);
        pa[nextUglyIndex] = MinNumber;

        while (*p1 * 2 <= pa[nextUglyIndex])
            ++p1;
        while (*p2 * 3 <= pa[nextUglyIndex])
            ++p2;
        while (*p3 * 5 <= pa[nextUglyIndex])
            ++p3;
        ++nextUglyIndex;
    }
    int ret = pa[nextUglyIndex - 1];
    delete[] pa;
    return ret;
}

int Min(int n1, int n2, int n3)
{
    int n = (n1 < n2) ? n1 : n2;
    return n < n3 ? n : n3;
}

int main()
{
    // cout << GetUglyNumber(1500);
    cout << GetUglyNumber1(1500);

    return 0;
}
*/

// 面试题 35 第一次只出现一次的字符
// 在字符串中查找第一个只出现一次的字符, 如输入 "abaccdeff", 则输出 b.
/*
#include <map>
char FirstCharOfAppearOne(const string &s)
{
    map<char, int> mp;
    char c;
    for (int i = 0; i < s.size(); ++i)
        mp[s[i]]++;

    for (int i = 0; i < s.size(); ++i)
        if (mp[s[i]] == 1)
            return s[i];
    return 0;
}
int main()
{
    char c = FirstCharOfAppearOne("abaccdeff");
    cout << c << endl;
    return 0;
}
*/