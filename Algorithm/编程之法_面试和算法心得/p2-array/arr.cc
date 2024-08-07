#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;
//  数组
// 寻找最小的 k 个数.
// 排序 或者 堆.
#if 0
void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, m = q[l + r >> 1];
    while (i < j)
    {
        do
            ++i;
        while (q[i] < m);

        do
            --j;
        while (q[j] > m);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

class Solution
{
public:
    vector<int> smallestK(vector<int> &arr, int k)
    {
        priority_queue<int,vector<int>, greater<int>> pq;
        int size = arr.size();
        for (int i = 0; i < size; ++i)
        {
            pq.push(arr[i]);
        }
        vector<int> res;

        while (k--)
        {
            res.push_back(pq.top());
            pq.pop();
        }
        return res;
    }
};

int main()
{
    int arr[] = {1, 7, 5, 9, 2, 6, 4, 11, 3};
    quick_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
    int k, i = 0;
    cin >> k;
    while (k--)
    {
        cout << arr[i++] << " ";
    }
    return 0;
}
#endif

// 寻找和为定值的两个数.
// 输入一个整数数组和一个整数,例如输入数组[1.2.4.5.7.11.15] 和整数 15, 那么 由于 4 + 11 = 15 因此输出 4 和 11.
// 自解.
#if 0
void twoSum(int a[], int length, int n)
{
    sort(a, a + length);
    for (int l = 0, r = length - 1; l < r;)
    {
        if (a[l] + a[r] == n)
        {
            cout << a[l] << " " << a[r] << endl;
        }
        else if (a[l] + a[r] > n)
        {
            r--;
        }
        else
            l++;
    }

    cout << "Not Find! " << endl;
}

// 书解.
void twoSum(int a[], int length, int sum)
{
    // sort(a, a+n); 如果数组非有序, 就先排成有序的, 时间复杂度 O(nlogn)
    int begin = 0;
    int end = length - 1;
    while (begin < end)
    {
        long currSum = a[begin] + a[end];
        if (currSum == sum)
        {
            printf("%d %d \n", a[begin], a[end]);
            break;
        }
        else
        {
            if (currSum < sum)
                begin++;
            else
                end--;
        }
    }
}

int main()
{
    int k;
    cin >> k;
    int a[] = {1, 2, 4, 5, 7, 11, 15};
    twoSum(a, sizeof(a) / sizeof(a[0]), k);
}
#endif

// 寻找和为定值的多个数
