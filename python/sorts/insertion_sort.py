from typing import List, Any

def insertion_sort(arr : List[Any]) -> List[Any]:
    """
        插入排序
        从第二个元素开始, 查找在前面的元素第一个比他小的.
    """
    n = len(arr)
    for i in range(1, n):
        key = arr[i]  # 当前插入的元素
        j = i - 1

        # 向左找插入位置
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j] # 元素右移
            j -= 1
        arr[j + 1] = key # 插入正确位置
    return arr


if __name__ == "__main__":
    from doctest import testmod

    testmod()

    user_input = input("Enter numbers separated by a comma:\n").strip()
    unsorted = [int(item) for item in user_input.split(",")]
    print(f"{insertion_sort(unsorted) = }")