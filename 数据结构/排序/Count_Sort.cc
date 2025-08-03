#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    计数排序 (Counting Sort)
    - 原理 ：统计每个元素出现的次数，根据次数进行排序
    - 时间复杂度 ：O(n + k)，其中 n 是元素个数，k 是元素范围
    - 空间复杂度 ：O(n + k)
    - 稳定性 ：稳定
    - 考点 ：
    - 与桶排序的对比（桶排序是计数排序的推广）
*/
// 计数排序
void CountingSort(vector<int> &arr)
{
    if (arr.empty())
        return;

    // 找出数组中的最大值和最小值
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;

    // 创建计数数组和输出数组
    vector<int> count(range, 0);
    vector<int> output(arr.size());

    // 统计每个元素出现的次数
    for (int num : arr)
    {
        count[num - min_val]++;
    }

    // 计算前缀和（确定每个元素的最终位置）
    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    // 从后向前遍历原数组，确保排序的稳定性
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }

    // 将排序结果复制回原数组
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = output[i];
    }
}

// 测试函数
int main()
{
    // 测试用例1：正整数
    vector<int> arr1 = {4, 2, 2, 8, 3, 3, 1};
    /*
       count[] 1 2 2 1 0 0 0 1
       前缀和
               1 3 5 6 6 6 6 7
       从后向前遍历原数组
              output[0] = 1
              output[1] = 2
              output[2] = 2
              output[3] = 3
              output[4] = 3
              output[5] = 4
              output[6] = 8
    */
    CountingSort(arr1);
    cout << "排序后数组1: ";
    for (int num : arr1)
        cout << num << " ";
    cout << endl;

    // 测试用例2：包含负数
    vector<int> arr2 = {5, -2, 9, 0, -6, 3, -1};
    CountingSort(arr2);
    cout << "排序后数组2: ";
    for (int num : arr2)
        cout << num << " ";
    cout << endl;

    return 0;
}
