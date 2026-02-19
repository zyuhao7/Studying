
def binary_insertion_sort(collection: list) -> list:
    """
    二分插入排序:
        利用插入排序的做法, 结合二分查找的思想.
        从第二个数开始, 查找第二个数在前面所有数当中应该插入的位置.
        然后利用 for 循环将所有比这个数大的都往后移一位, 然后插入在这.
        tips:
            二分过程中, low <= high 而不是 <.
            因为 只要"可能插入的位置区间" 还没被排除干净，就必须继续二分.
    """
    n = len(collection)
    for i in range(1, n):
        value_to_insert = collection[i]
        low = 0
        high = i - 1

        while low <= high:
            mid = (low + high) // 2
            if value_to_insert < collection[mid]:
                high = mid - 1
            else:  # value_to_insert >= collection[mid]
                low = mid + 1
        for j in range(i, low, -1):
            collection[j] = collection[j - 1]
        collection[low] = value_to_insert
    return collection


if __name__ == "__main__":
    user_input = input("Enter numbers separated by a comma:\n").strip()
    try:
        unsorted = [int(item) for item in user_input.split(",")]
    except ValueError:
        print("Invalid input. Please enter valid integers separated by commas.")
        raise
    print(f"{binary_insertion_sort(unsorted) = }")