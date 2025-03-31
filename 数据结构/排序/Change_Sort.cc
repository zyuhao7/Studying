#include <iostream>
#include <vector>
using namespace std;

// 冒泡排序
void BubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 快速排序
void quick_sort(vector<int> &arr, int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, x = arr[l + r >> 1];
    while (i < j)
    {
        do
            ++i;
        while (arr[i] < x);
        do
            --j;
        while (arr[j] > x);
        if (i < j)
            swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}
int main()
{
    vector<int> arr = {9, 5, 1, 4, 3};
    BubbleSort(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;

    vector<int> arr2 = {9, 5, 1, 4, 3};
    quick_sort(arr2, 0, arr2.size() - 1);
    for (int i : arr2)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}