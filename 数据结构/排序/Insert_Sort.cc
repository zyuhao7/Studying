#include <iostream>
#include <vector>
using namespace std;

// 插入排序
// void insertionSort(vector<int> &arr)
// {
//     int n = arr.size();
//     for (int i = 1; i < n; ++i)
//     {
//         int key = arr[i];
//         int j = i - 1;
//         while (j >= 0 && arr[j] > key)
//         {
//             arr[j + 1] = arr[j];
//             --j;
//         }
//         arr[j + 1] = key;
//     }
// }

// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(nullptr) {}
// };

// ListNode *insertionSortList(ListNode *head)
// {
//     if (!head || !head->next)
//         return head;
//     ListNode dummy(0);
//     ListNode *cur = head, *prev = &dummy;
//     while (cur)
//     {
//         ListNode *next = cur->next;
//         prev = &dummy;
//         while (prev->next && prev->next->val < cur->val)
//         {
//             prev = prev->next;
//         }
//         cur->next = prev->next;
//         prev->next = cur;
//         cur = next;
//     }
//     return dummy.next;
// }

int BinarySearch(const vector<int> &arr, int l, int r, int key)
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
        int pos = BinarySearch(arr, 0, i, key);
        for (int j = i; j > pos; --j)
        {
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

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