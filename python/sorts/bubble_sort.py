from typing import  Any




def bubble_sort_iterative(collection: list[Any]) -> list[Any]:
    length = len(collection)
    for i in reversed(range(length)): # 从 length - 1 到 0
        swapped = False
        for j in range(i):
            if collection[j] > collection[j + 1]:
                swapped = True
                collection[j], collection[j + 1] = collection[j + 1], collection[j]
        if not swapped:
            break # 停止迭代,如果列表有序
    return collection

def bubble_sort_recursive(collection: list[Any]) -> list[Any]:
    length = len(collection)
    swapped= False
    for i in range(length - 1):
        if collection[i] > collection[i + 1]:
            collection[i], collection[i + 1] = collection[i + 1], collection[i]
            swapped = True
    return collection if not swapped else bubble_sort_recursive(collection)

if __name__ == "__main__":
    import doctest
    from random import sample
    from timeit import timeit

    doctest.testmod()
    # benchmark:
    num_runs = 10000
    unsorted = sample(range(-50, 50), 100)
    timer_iterative = timeit(
         "bubble_sort_iterative(unsorted[:])", globals=globals(), number=num_runs)

    print("\nIterative bubble sort:")
    print(*bubble_sort_iterative(unsorted), sep=",")
    print(f"Processing time (iterative): {timer_iterative:.5f}s for {num_runs:,} runs")

    unsorted = sample(range(-50, 50), 100)
    timer_recursive = timeit(
        "bubble_sort_recursive(unsorted[:])", globals=globals(), number=num_runs
    )
    print("\nRecursive bubble sort:")
    print(*bubble_sort_recursive(unsorted), sep=",")
    print(f"Processing time (recursive): {timer_recursive:.5f}s for {num_runs:,} runs")