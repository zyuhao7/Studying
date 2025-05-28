package main

import (
	"fmt"
)

func quick_sort(q []int, l int, r int) {
	if l >= r {
		return
	}
	i, j := l-1, r+1
	x := q[(l+r)>>1]
	for i < j {
		for {
			i++
			if q[i] >= x {
				break
			}
		}
		for {
			j--
			if q[j] <= x {
				break
			}
		}
		if i < j {
			q[i], q[j] = q[j], q[i]
		}
	}
	quick_sort(q, l, j)
	quick_sort(q, j+1, r)
}

func insert_sort(slice []int) {
	if len(slice) <= 1 {
		return
	}
	for i := 1; i < len(slice); i++ {
		tmp := slice[i]
		j := i - 1
		for ; j >= 0 && slice[j] > tmp; j-- {
			slice[j+1] = slice[j] // 后移
		}
		slice[j+1] = tmp
	}
}

func bubble_sort(slice []int) {
	for i := 0; i < len(slice)-1; i++ {
		for j := 0; j < len(slice)-1-i; j++ {
			if slice[j+1] < slice[j] {
				slice[j+1], slice[j] = slice[j], slice[j+1]
			}
		}
	}
}

func select_sort(slice []int) {
	for i := 0; i < len(slice); i++ {
		for j := i + 1; j < len(slice); j++ {
			if slice[j] < slice[i] {
				slice[i], slice[j] = slice[j], slice[i]
			}
		}
	}
}

func main() {

	q := []int{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}
	// quick_sort(q, 0, len(q)-1)
	// insert_sort(q)
	// bubble_sort(q)
	// select_sort(q)

	fmt.Println(q) // 输出排序后的数组
}
