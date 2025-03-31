#include <iostream>
#include <vector>
using namespace std;

// 选择排序 基本版
void SelectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[idx])
            {
                idx = j;
            }
        }
        swap(arr[i], arr[idx]);
    }
}

// 选择排序 优化版
void SelectionSortOptimized(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIdx = i, maxIdx = i;
        for (int j = i + 1; j < n - i; ++j)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
            if (arr[j] > arr[maxIdx])
            {
                maxIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
        if (maxIdx == i) // 如果最大值在当前范围内，更新最大值的索引
            maxIdx = minIdx;
        swap(arr[n - 1 - i], arr[maxIdx]);
    }
}

// 堆排序
// 向下调整
void AdjustDown(vector<int> &arr, int n, int parent)
{
    int child = parent * 2 + 1;
    while (child < n)
    {
        if (child + 1 < n && arr[child + 1] > arr[child])
            child++;
        if (arr[child] > arr[parent])
        {
            swap(arr[child], arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
            break;
    }
}

// 构建最大堆
void BuildHeap(vector<int> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; --i)
        AdjustDown(arr, n, i);
}

void HeapSort(vector<int> &arr)
{
    int n = arr.size();
    BuildHeap(arr, n);

    for (int i = n - 1; i > 0; --i)
    {
        swap(arr[0], arr[i]);
        AdjustDown(arr, i, 0);
    }
}

int main()
{
    // vector<int> arr = {9, 5, 1, 4, 3};
    // SelectionSort(arr);
    // for (int i : arr)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;
    vector<int> arr = {10, 3, 2, 5, 8, 7, 6, 4, 1, 9};
    HeapSort(arr);
    for (int num : arr)
        cout << num << " ";

    return 0;
}