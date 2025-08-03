#include <iostream>
#include <vector>
using namespace std;
/*
    归并排序 (Merge Sort)
    - 原理 ：分治思想，将数组分成两半，分别排序后合并
    - 时间复杂度 ：O(nlogn)
    - 空间复杂度 ：O(n)
    - 稳定性 ：稳定
    - 考点 ：
    - 递归实现
    - 迭代实现
    - 与快速排序的对比（平均情况下更快，最坏情况下更稳定）
*/
void merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> tmp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
    {
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }
    while (i <= m)
        tmp[k++] = arr[i++];
    while (j <= r)
        tmp[k++] = arr[j++];
    for (int k = 0, i = l; i < r; ++i, ++k)
        arr[i] = tmp[k];
}
// 归并排序
void mergeSort(vector<int> &arr, int l, int r)
{
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);     // 先排左边
    mergeSort(arr, m + 1, r); // 再排右边
    merge(arr, l, m, r);      // 合并两个有序区间
}
int main()
{
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sort end: ";
    for (int num : arr)
        cout << num << " ";
    return 0;
}