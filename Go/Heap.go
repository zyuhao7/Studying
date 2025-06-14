package main

import "fmt"

type HeapSort struct {
}

// 大根堆
func (hs *HeapSort) adjustHeap(array []int, parent, length int) {

	for {
		left := parent*2 + 1
		right := left + 1
		maxChild := left

		if left >= length {
			break
		}

		if right < length && array[right] > array[left] {
			maxChild = right
		}
		if array[parent] < array[maxChild] {
			hs.swap(array, parent, maxChild)
			parent = maxChild
		} else {
			break
		}
	}
}

func (hs *HeapSort) swap(array []int, parent, child int) {
	if parent >= len(array) || child >= len(array) {
		return
	}
	tmp := array[parent]
	array[parent] = array[child]
	array[child] = tmp
}

func (hs *HeapSort) sort(array []int) {
	for length := len(array); length > 1; length-- {
		// 最后一个非叶子节点索引
		NoneLeaf := length/2 - 1
		for i := NoneLeaf; i >= 0; i-- {
			hs.adjustHeap(array, i, length)
		}

		hs.swap(array, 0, length-1)
		fmt.Println(array)
	}
}

func main() {
	//数组初始化
	array := []int{6, 1, 0, 5, 2, 9, 6}
	hs := new(HeapSort)
	hs.sort(array)
}
