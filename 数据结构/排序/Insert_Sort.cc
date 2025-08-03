#include <iostream>
#include <vector>
using namespace std;

/*
    插入排序 (Insertion Sort)
    - 原理 ：将元素插入到已排序部分的合适位置
    - 时间复杂度 ：O(n²)，最好情况O(n)（已排序）
    - 空间复杂度 ：O(1)
    - 稳定性 ：稳定
    - 考点 ：
    - 二分查找优化（减少比较次数）
    - 链表实现
    - 适用于小规模数据或几乎已排序的数据
*/
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i) // 从第二个元素开始，假设第一个元素已排序
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
    链表的插入排序
*/
ListNode *insertionSortList(ListNode *head)
{
    //  3 -> 1 -> 2 -> 4 -> 7
    if (!head || !head->next)
        return head;
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = head, *prev = dummy;
    while (cur)
    {
        //  3 -> 1 -> 2 -> 4 -> 7
        //  1 -> 3 -> 2 -> 4 -> 7
        //  1 -> 2 -> 3 -> 4 -> 7
        //  1 -> 2 -> 3 -> 4 -> 7
        //  1 -> 2 -> 3 -> 4 -> 7
        ListNode *next = cur->next;
        prev = dummy;
        //  找到插入位置
        while (prev->next && prev->next->val < cur->val)
        {
            prev = prev->next;
        }
        cur->next = prev->next;
        prev->next = cur;
        cur = next;
    }
    return dummy->next;
}
/*
    二分查找优化
    - 原理 ：利用二分查找找到插入位置，减少比较次数
    - 时间复杂度 ：O(n log n)
    - 空间复杂度 ：O(1)
    - 稳定性 ：稳定
*/
int BinarySearch(const vector<int> &arr, int l, int r, int key) // 找到第一个大于key的元素位置
{
    while (l < r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] > key)
        {
            r = m;
        }
        else
            l = m + 1;
    }
    return l;
}

void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int pos = BinarySearch(arr, 0, i, key); // 找到第一个大于key的元素位置
        for (int j = i; j > pos; --j)
        {
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}
/*
       希尔排序 (Shell Sort)
        - 原理 ：分组插入排序，逐步缩小间隔
        - 时间复杂度 ：取决于间隔序列，平均O(n^1.3)
        - 空间复杂度 ：O(1)
        - 稳定性 ：不稳定
        - 考点 ：
            - 间隔序列的选择
            - 与插入排序的关系
*/
void ShellSort(vector<int> &arr)
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

int main()
{
    // std::vector<int> arr = {9, 5, 1, 4, 3, 8, 6, 2, 7};
    // shellSort(arr);
    // for (int num : arr) {
    //     std::cout << num << " ";
    // }
    // ListNode *head = new ListNode(4);
    // head->next = new ListNode(2);
    // head->next->next = new ListNode(1);
    // head->next->next->next = new ListNode(3);
    // head->next->next->next->next = new ListNode(5);
    // ListNode *sortedList = insertionSortList(head);
    // ListNode *current = sortedList;
    // while (current)
    // {
    //     std::cout << current->val << " ";
    //     current = current->next;
    // }
    // std::cout << std::endl;

    // std::vector<int> arr = {9, 5, 1, 4, 3};
    // insertionSort(arr);
    // for (int num : arr)
    // {
    //     std::cout << num << " ";
    // }
    return 0;
}