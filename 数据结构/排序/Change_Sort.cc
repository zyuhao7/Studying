#include <iostream>
#include <list>
#include <vector>
using namespace std;

// 冒泡排序
/*
     冒泡排序 (Bubble Sort)
    - 原理 ：通过相邻元素比较和交换，逐步将最大元素"冒泡"到数组末尾
    - 时间复杂度 ：O(n²)，最好情况O(n)（已排序）
    - 空间复杂度 ：O(1)
    - 稳定性 ：稳定
    - 考点 ：
        - 优化方式（如设置标志位提前结束）
        - 理解稳定排序的概念
        - 适用于小规模数据或几乎已排序的数据
*/
void BubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) // 外层循环，控制冒泡的轮数
    {
        for (int j = 0; j < n - i - 1; ++j) // 内层循环，控制每轮冒泡的次数
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 快速排序
/*
     快速排序 (Quick Sort)
    - 原理 ：通过选择一个基准元素，将数组分为两个子数组，
    一个子数组的所有元素都小于基准元素，另一个子数组的所有元素都大于基准元素。
    然后递归地对两个子数组进行快速排序。
    - 时间复杂度 ：O(nlogn)，最好情况O(nlogn)（已排序）
    - 空间复杂度 ：O(logn)
    - 稳定性 ：不稳定
    - 考点 ：
        - 优化方式（如三数取中法选择基准元素）
        - 理解不稳定排序的概念
        - 适用于大规模数据
*/
void quick_sort(vector<int> &arr, int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, x = arr[l + r >> 1];
    while (i < j)
    {
        do
            ++i;
        while (arr[i] < x); // 找到第一个大于等于 x 的元素
        do
            --j;
        while (arr[j] > x); // 找到第一个小于等于 x 的元素
        if (i < j)
            swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}
#include <algorithm>
/*
    链表的快速排序
*/
template <typename T>
list<T> qsort_list(std::list<T> input)
{
    if (input.empty())
        return input;
    list<T> result;                                      // 用于存储排序后的结果
    result.splice(result.begin(), input, input.begin()); // 取第一个元素作为基准元素

    T const &pivot = *result.begin();
    // 此时 divide_point 指向的是第一个大于等于 pivot 的位置
    auto divide_point = std::partition(input.begin(), input.end(), [&](const &t)
                                       { return t < pivot; });

    list<T> lower_part;                                                      // 用于存储小于 pivot 的元素
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point); // 将小于 pivot 的元素.splice 到 lower_part 中
    auto new_lower(qsort_list(std::move(lower_part)));                       // 递归地对 lower_part 进行快速排序

    auto new_higher(qsort_list(std::move(input))); // 递归地对 higher_part 进行快速排序
    result.splice(result.end(), new_higher);       // 将 higher_part .splice 到 result 中

    result.splice(result.begin(), new_lower); // 将 lower_part .splice 到 result 中
    return result;
}

void test_sequential_quick()
{
    std::list<int> numlists = {6, 1, 0, 7, 5, 2, 9, -1};
    auto sort_result = qsort_list(numlists);
    std::cout << "sorted result is ";
    for (auto iter = sort_result.begin(); iter != sort_result.end(); iter++)
    {
        std::cout << " " << (*iter);
    }
    std::cout << std::endl;
}

int main()
{
    // test_sequential_quick();
    // vector<int> arr = {9, 5, 1, 4, 3};
    // BubbleSort(arr);
    // for (int i : arr)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    // vector<int> arr2 = {9, 5, 1, 4, 3};
    // quick_sort(arr2, 0, arr2.size() - 1);
    // for (int i : arr2)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;
    return 0;
}
