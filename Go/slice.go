package main

import "fmt"

func main() {
	var array [8]byte
	fmt.Println(array)

	var PtrArray [4]*float64
	fmt.Println(PtrArray)

	var mulArray [3][5]int
	fmt.Println(mulArray)

	for i := 0; i < len(PtrArray); i++ {
		fmt.Println("Element ", i, "of array is", PtrArray[i])
	}

	for i, v := range PtrArray {
		fmt.Println("Array element[", i, "] =", v)
	}

	ary := [5]int{1, 2, 3, 4, 5}
	modify(ary)
	fmt.Println("After modify(), array: ", ary)

	newArray := [5]int{1, 2, 3, 4, 5}
	var mySlice []int = newArray[:3]
	for _, v := range ary {
		fmt.Print(v, " ")
	}
	fmt.Println("\nElements of mySlice: ")
	for _, v := range mySlice {
		fmt.Print(v, " ")
	}

	mkslice := make([]int, 5)
	fmt.Println("\n", mkslice)

	mkslice2 := make([]int, 5, 10)
	fmt.Println("mkslice2:", mkslice2)

	mkslice3 := []int{1, 2, 3, 4, 5}
	fmt.Println("mkslice3:", mkslice3)

	for i := 0; i < len(mkslice3); i++ {
		fmt.Println("mkslice3[", i, "]=", mkslice3[i])
	}

	for i, v := range mkslice3 {
		fmt.Println("mkslice3[", i, "]=", v)
	}

	mkslice4 := make([]int, 5, 10)
	fmt.Println("len(mkslice4):", len(mkslice4))
	fmt.Println("cap(mkslice4):", cap(mkslice4))

	mkslice4 = append(mkslice4, 1, 2, 3)
	fmt.Println("mkslice4 after append:", mkslice4)

	mkslice4 = append(mkslice4, mkslice3...)
	fmt.Println("mkslice4 after append mkslice3:", mkslice4)

	mkslice5 := make([]int, 0)
	mkslice5 = append(mkslice5, 1, 2, 3)
	fmt.Println("mkslice5:", mkslice5)
	mkslice5 = append(mkslice5, mkslice3...)
	fmt.Println("mkslice5 after append mkslice3:", mkslice5)

	mkslice5 = append(mkslice5[:5-1], mkslice5[5:]...)
	fmt.Println("mkslice5 after delete last element:", mkslice5)

	oldslice := []int{1, 2, 3, 4, 5}
	newslice := oldslice[:3]
	newslice2 := oldslice

	fmt.Println("newslice:", newslice)
	fmt.Println("newslice2:", newslice2)
	fmt.Printf("newslice  addr is : %p \n", &newslice)
	fmt.Printf("newslice2 addr is:  %p \n", &newslice2)

	oldslice[0] = 100
	fmt.Println("newslice is :", newslice)
	fmt.Println("newslice2 is :", newslice2)

	slice1 := []int{1, 2, 3, 4, 5}
	slice2 := []int{5, 4, 3}

	copy(slice2, slice1)

	fmt.Println("after copy.....")
	fmt.Println("slice1:", slice1)
	fmt.Println("slice2:", slice2)

	slice2[0] = 1024
	slice2[1] = 999
	slice2[2] = 2999

	fmt.Println("after modify slice2.....")
	fmt.Println("slice1:", slice1)
	fmt.Println("slice2:", slice2)

	copy(slice1, slice2)
	fmt.Println("after copy slice2 to slice1.....")
	fmt.Println("slice1:", slice1)
	fmt.Println("slice2:", slice2)
}

func modify(array [5]int) {
	array[0] = 200
	fmt.Println("in modify(), array: ", array)
}
