package main

import (
	"fmt"
	"time"
)

// 定时器实现(小根堆)
// day-2025-6-15

// 定时器结构
type heapEle struct {
	// 任务的回调函数
	callback func(interface{}) bool
	// 回调函数参数
	params interface{}
	//任务设置的定时器时间
	deadline int64
}

/*
	当我们将任务加入定时器时, 实际就是将回调函数(callback) 以及截止时间(deadline)保存好放在小根堆中。
	每次从堆顶 pop 出截止日期最小的任务, 调用回调函数执行任务。如果一次性任务执行完成后不需要入堆。
	如果是轮询任务,则执行完成后继续入堆。
*/

type SmallRootHeap struct {
	array []int
}

func (sh *SmallRootHeap) swap(array []int, i, j int) {
	if i >= len(array) || j >= len(array) {
		return
	}
	tmp := array[i]
	array[i] = array[j]
	array[j] = tmp
}

func (sh *SmallRootHeap) InitHeap(array []int) {
	sh.array = make([]int, len(array))
	copy(sh.array, array)
	length := len(array)
	for index := length/2 - 1; index >= 0; index-- {
		sh.adJustDown(sh.array, index, length)
	}
}

func (sh *SmallRootHeap) adJustDown(array []int, parent, length int) {
	left := parent*2 + 1
	right := parent*2 + 2
	maxChild := left

	for {
		if left >= length {
			break
		}

		if right < length && array[right] < array[left] {
			maxChild = right
		}

		if array[parent] > array[maxChild] {
			sh.swap(array, parent, maxChild)
			parent = maxChild
			left = parent*2 + 1
			right = parent*2 + 2
			maxChild = left
		} else {
			break
		}
	}
}

func (sh *SmallRootHeap) adjustUp(array []int, child, length int) {
	parent := child/2 - 1
	for {
		if child <= 0 {
			break
		}
		if sh.array[child] < sh.array[parent] {
			sh.swap(sh.array, child, parent)
			child = parent
			parent = child/2 - 1
		} else {
			break
		}
	}
}

func (sh *SmallRootHeap) insertNode(node int) {
	sh.array = append(sh.array, node)
	length := len(sh.array)
	index := length - 1
	sh.adjustUp(sh.array, index, length)
}

func (sh *SmallRootHeap) popSmallRoot() (bool, int) {
	length := len(sh.array)
	if length <= 0 {
		return false, 0
	}
	tmp := sh.array[0]
	sh.swap(sh.array, 0, length-1)
	sh.array = append(sh.array[0:length-1], sh.array[length:]...)
	sh.adJustDown(sh.array, 0, len(sh.array))
	return true, tmp
}

func main() {
	// 任务截止时间
	deadline := time.Now().Unix() + int64(10)
	heape := new(heapEle)
	heape.deadline = deadline
	//任务参数
	heape.params = []int{1, 2, 3}
	// 任务回调函数
	heape.callback = func(params interface{}) bool {
		switch params.(type) {
		case string:
			fmt.Println(params)
		case []string:
			strs := params.([]string)
			for _, str := range strs {
				fmt.Println(str)
			}
		case []int:
			nums := params.([]int)
			for _, num := range nums {
				fmt.Println(num)
			}
		}
		return true
	}

	time.Sleep(time.Duration(time.Second * 11))
	if time.Now().Unix() >= heape.deadline {
		heape.callback(heape.params)
	}
}
