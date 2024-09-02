#include <iostream>
#include <vector>
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