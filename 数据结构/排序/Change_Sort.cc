#include <iostream>
#include <list>
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
#include <algorithm>
template <typename T>
list<T> qsort_list(std::list<T> input)
{
    if (input.empty())
        return input;
    list<T> result;
    result.splice(result.begin(), input, input.begin());

    T const &pivot = *result.begin();
    // 此时 dp 指向的是第一个大于等于 pivot 的位置
    auto divide_point = std::partition(input.begin(), input.end(), [&](const &t)
                                       { return t < pivot; });
    list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
    auto new_lower(qsort_list(std::move(lower_part)));

    auto new_higher(qsort_list(std::move(input)));
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);
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
    test_sequential_quick();
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