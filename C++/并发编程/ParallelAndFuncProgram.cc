#include <iostream>
#include <list>
using namespace std;

// 并行和函数式编程提高运算效率

// day-2025-3-9

// 快速排序
// template <typename T>
// void quick_sort(T arr[], int l, int r)
// {
//     if (l >= r)
//         return;
//     T x = arr[l + r >> 1];
//     int i = l - 1, j = r + 1;
//     while (i < j)
//     {
//         do
//             ++i;
//         while (arr[i] < x);
//         do
//             --j;
//         while (arr[j] > x);
//         if (i < j)
//             std::swap(arr[i], arr[j]);
//     }
//     quick_sort(arr, l, j);
//     quick_sort(arr, j + 1, r);
// }
// int num_arr[] = {1, 5, 2, 6, 4, 1, 0, 2, 9, 12, 8};

// int main()
// {
//     int length = sizeof(num_arr) / sizeof(int);
//     for (int i = 0; i < length; i++)
//     {
//         std::cout << " " << num_arr[i];
//     }
//     std::cout << std::endl;
//     quick_sort<int>(num_arr, 0, length - 1);
//     for (int i = 0; i < length; i++)
//     {
//         std::cout << " " << num_arr[i];
//     }
//     std::cout << std::endl;
// }
// #include <algorithm>
// // 函数式编程
// // 基于链表的快速排序算法
// template <typename T>
// std::list<T> sequential_quick_sort(std::list<T> input)
// {
//     if (input.empty())
//         return input;

//     std::list<T> result;
//     // 先获取基准元素 pivot, 将基准元素放到 result的头
//     result.splice(result.begin(), input, input.begin());

//     // 确定基础元素
//     T const &pivot = *result.begin();

//     // 此时 dp 指向的是第一个大于等于 pivot 的位置
//     auto divide_point = std::partition(input.begin(), input.end(), [&](T const &t)
//                                        { return t < pivot; });

//     // 然后找出 lower 和 higher
//     std::list<T> lower_part;
//     lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
//     auto new_lower(sequential_quick_sort(std::move(lower_part)));

//     // 我们剩余的input列表传递给sequential_quick_sort递归调用，input中都是大于divide_point的值。
//     auto new_higher(sequential_quick_sort(std::move(input)));

//     // 到此时new_higher和new_lower都是从小到大排序好的列表
//     //  将new_higher 拼接到result的尾部
//     result.splice(result.end(), new_higher);
//     // 将new_lower 拼接到result的头部
//     result.splice(result.begin(), new_lower);
//     return result;
// }

// void test_sequential_quick()
// {
//     std::list<int> numlists = {6, 1, 0, 7, 5, 2, 9, -1};
//     auto sort_result = sequential_quick_sort(numlists);
//     std::cout << "sorted result is ";
//     for (auto iter = sort_result.begin(); iter != sort_result.end(); iter++)
//     {
//         std::cout << " " << (*iter);
//     }
//     std::cout << std::endl;
// }
// int main()
// {
//     test_sequential_quick();
// }
