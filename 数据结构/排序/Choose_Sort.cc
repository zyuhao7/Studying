#include <iostream>
#include <vector>
using namespace std;

/*
    选择排序 基本版
    - 原理 ：每次选择未排序部分的最小元素，放到已排序部分末尾
    - 时间复杂度 ：O(n²)，无论何种情况
    - 空间复杂度 ：O(1)
    - 稳定性 ：不稳定
    - 考点 ：
    - 优化方式（如同时找最大和最小元素）
    - 与冒泡排序的区别（交换次数更少）
    - 与插入排序的区别（插入排序在接近有序的情况下更高效）
 */
void SelectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) // 外层循环，控制选择的轮数
    {
        int idx = i;
        for (int j = i + 1; j < n; ++j) // 内层循环，控制每轮选择的次数
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
    for (int i = 0; i < n / 2; ++i)
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

/*
    堆排序 (Heap Sort)
    - 原理 ：构建最大堆，依次取出堆顶元素放到数组末尾
    - 时间复杂度 ：O(nlogn)，最坏情况也是O(nlogn)
    - 空间复杂度 ：O(1)
    - 稳定性 ：不稳定
    - 考点 ：
    - 最大堆的构建与调整
    - 向下调整和向上调整操作
    - 与快速排序的对比（最坏情况下更稳定，平均情况下更快）
*/

/*
     向下调整
     - 原理 ：
        将父节点与子节点进行比较，将较大的子节点与父节点交换，直到父节点大于等于子节点或没有子节点为止
*/
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
/*
    向上调整
    - 原理 ：
        将子节点与父节点进行比较，将较大的子节点与父节点交换，直到子节点小于等于父节点或没有父节点为止
*/
void AdjustUp(vector<int> &arr, int n, int child)
{
    int parent = (child - 1) / 2;
    while (child > 0)
    {
        if (arr[child] > arr[parent])
        {
            swap(arr[child], arr[parent]);
            child = parent;
            parent = (child - 1) / 2;
        }
        else
            break;
    }
}

/*
    构建最大堆
    - 原理 ：从最后一个非叶子节点开始，依次向上调整，直到根节点
    - 时间复杂度 ：O(n)
*/
void BuildHeap(vector<int> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        // O(n)
        AdjustDown(arr, n, i);
    }
    // for (int i = n / 2 - 1; i >= 0; --i)
    // {
    //     // O(nlogn) 而且不保证叶子结点有序
    //     AdjustUp(arr, n, i);
    // }
}

void HeapSort(vector<int> &arr)
{
    int n = arr.size();
    BuildHeap(arr, n);
    for (int i = n - 1; i > 0; --i)
    {
        // cout << "arr[0]: " << arr[0] << endl;
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