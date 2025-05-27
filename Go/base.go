package main

import "fmt"

// var v1 int
// var v2 string
// var v3 [10]int
// var v4 []int    // 切片
// var v5 struct { // 结构体
// 	f int
// }
// var v6 *int            // 指针
// var v7 map[string]int  // map, key 为 string, value 为 int
// var v8 func(a int) int // 函数类型
// var (
// 	v9  int
// 	v10 string
// )

func main() {
	var v1 int
	v1 = 10

	v2 := "hello"
	fmt.Println("v1:", v1)
	fmt.Println("v2:", v2)

	v11 := "day-2025-5-27"
	fmt.Println("v11:", v11)

	v12 := 12
	// 变量交换
	v1, v12 = v12, v1
	fmt.Printf("v1: %v, v12: %v\n", v1, v12)

	_, _, nickName := GetName() // 只获取第三个返回值
	fmt.Println("nickName:", nickName)

	const Pi float64 = 3.1415926535
	const zero = 0.0
	const (
		size int64 = 1024
		eof        = -1
	)
	const u, v float32 = 0, 3
	const a, b, c = 3, 4, "foo"

	const (
		c0 = iota // 0
		c1 = iota // 1
		c2 = iota // 2
	)
	const (
		a1 = 1 << iota // 1 << 0 = 1
		a2 = 1 << iota // 1 << 1 = 2
		a3 = 1 << iota // 1 << 2 = 4
	)
	fmt.Printf("a1: %v, a2: %v, a3: %v \n", a1, a2, a3)

	const (
		Sunday = iota
		Monday
		Tuesday
		Wednesday
		Thursday
		Friday
		Saturday
		numberOfDays // 这个常量没有导出
	)
	//  同Go语言的其他符号（symbol）一样，以大写字母开头的常量在包外可见

	fmt.Printf("Sunday: %v, Monday: %v, Tuesday: %v, Wednesday: %v, Thursday: %v, Friday: %v, Saturday: %v\n",
		Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday)
	fmt.Println("numberOfDays:", numberOfDays)

	//bool 类型
	var bv bool
	bv = true
	b2v := (1 == 2)
	fmt.Printf("b: %v, b2: %v\n", bv, b2v)

	var str string
	str = "hello, world"
	ch := str[0]
	fmt.Printf("the length of \"%s\" is %d \n", str, len(str))
	fmt.Printf("the first character of \"%s\" is %c \n", str, ch)

	hellos := "hello, 世界"
	for i := 0; i < len(hellos); i++ {
		fmt.Printf("%c", hellos[i])
	}
	fmt.Println()

	for i, ch := range hellos {
		fmt.Printf("%c \t", ch)
		fmt.Printf("%d\n", i)
	}
}

func GetName() (string, string, string) {
	return "first", "last", "nickname"
}
