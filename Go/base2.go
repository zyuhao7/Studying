package main

// func sqrt(x float64) string {
// 	if x < 0 {
// 		return sqrt(-x) + "i"
// 	}
// 	return fmt.Sprint(math.Sqrt(x))
// }

// func pow(x, n, lim float64) float64 {
// 	if v := math.Pow(x, n); v < lim {
// 		return v
// 	} else {
// 		fmt.Printf("%g >= %g \n", v, lim)
// 	}
// 	return lim
// }

// type Vertex struct {
// 	X, Y int
// }

// var (
// 	v1 = Vertex{1, 2}
// 	v2 = Vertex{X: 1}
// 	v3 = Vertex{}
// 	p  = &Vertex{1, 2}
// )

// func printSlice(s string, x []int) {
// 	fmt.Printf("%s len = %d cap = %d %v \n", s, len(x), cap(x), x)
// }

// func printSlice(s []int) {
// 	fmt.Printf("len = %d cap = %d %v \n", len(s), cap(s), s)
// }

// var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

// type Vertex struct {
// 	Lat, Long float64
// }

// var m = map[string]Vertex{
// 	"Bell Labs": {40.68433, -74.39967},
// 	"Google":    {37.42202, -122.08408},
// }

// func adder() func(int) int {
// 	sum := 0
// 	return func(x int) int {
// 		sum += x
// 		return sum
// 	}
// }
// func fibonacci() func() int {
// 	a, b := 0, 1
// 	return func() int {
// 		t := a
// 		a, b = b, a+b
// 		return t
// 	}
// }

func main() {
	// f := fibonacci()
	// for i := 0; i < 10; i++ {
	// 	fmt.Println(f())
	// }

	// pos, neg := adder(), adder()
	// for i := 0; i < 10; i++ {
	// 	fmt.Println(pos(i), neg(-2*i))
	// }

	// m := make(map[string]int)
	// m["Answer"] = 42
	// fmt.Println("The val: ", m["Answer"])

	// m["Answer"] = 48
	// fmt.Println("The val: ", m["Answer"])

	// delete(m, "Answer")
	// fmt.Println("The val: ", m["Answer"])

	// v, ok := m["Answer"]
	// fmt.Println("The Value: ", v, "Present?", ok)

	// fmt.Println(m)

	// fmt.Println(m["Bell Labs"])

	// pow := make([]int, 10)
	// for i := range pow {
	// 	pow[i] = 1 << uint(i) // 2 ** i
	// }
	// for _, value := range pow {
	// 	fmt.Printf("%d \n", value)
	// }

	// for i, v := range pow {
	// 	fmt.Printf("2 ** %d = %d\n", i, v)
	// }

	// var s []int
	// printSlice(s)

	// s = append(s, 0)
	// printSlice(s)

	// s = append(s, 1)
	// printSlice(s)

	// s = append(s, 2, 3, 4)
	// printSlice(s)

	// board := [][]string{
	// 	[]string{"_", "_", "_"},
	// 	[]string{"_", "_", "_"},
	// 	[]string{"_", "_", "_"},
	// }

	// board[0][0] = "X"
	// board[2][2] = "O"
	// board[1][2] = "X"
	// board[1][0] = "0"
	// board[0][2] = "X"
	// for i := 0; i < len(board); i++ {
	// 	fmt.Printf("%s\n", strings.Join(board[i], " "))
	// }

	// a := make([]int, 5)
	// printSlice("a", a)

	// b := make([]int, 0, 5)
	// printSlice("b", b)

	// c := b[:2]
	// printSlice("c", c)

	// d := c[2:5]
	// printSlice("d", d)

	// var s []int
	// fmt.Println(s, len(s), cap(s))
	// if s == nil {
	// 	fmt.Println("nil!")
	// }

	// s := []int{2, 3, 5, 7, 11, 13}
	// printSlice(s)

	// s = s[:0]
	// printSlice(s)

	// s = s[2:]
	// printSlice(s)

	// s := []int{2, 3, 5, 7, 11, 13}

	// s = s[1:4]
	// fmt.Println(s)

	// s = s[:2]
	// fmt.Println(s)

	// s = s[1:]
	// fmt.Println(s)

	// q := []int{2, 3, 5, 7, 11, 13}
	// fmt.Println(q)
	// r := []bool{true, true, true, false, false, true}
	// fmt.Println(r)

	// s := []struct {
	// 	i int
	// 	b bool
	// }{
	// 	{2, true},
	// 	{3, false},
	// 	{5, true},
	// 	{7, true},
	// 	{11, false},
	// 	{13, true},
	// }
	// fmt.Println(s)

	// names := [4]string{
	// 	"John",
	// 	"Paul",
	// 	"George",
	// 	"Ringo",
	// }
	// fmt.Println(names)
	// a := names[0:2]
	// b := names[1:3]
	// fmt.Println(a, b)
	// b[0] = "XXX"
	// fmt.Println(a, b)
	// fmt.Println(names)

	// primes := [6]int{2, 3, 5, 7, 11, 13}
	// var s []int = primes[1:4]
	// fmt.Println(s)

	// var a [2]string
	// a[0] = "Hello"
	// a[1] = "world"
	// fmt.Println(a[0], a[1])
	// fmt.Println(a)

	// primes := [6]int{2, 3, 5, 7, 11}
	// fmt.Println(primes)

	// fmt.Println(v1, p, v2, v3)

	// fmt.Println(Vertex{1, 2})
	// v := Vertex{1, 2}
	// v.X = 4
	// fmt.Println(v.X)
	// p := &v
	// p.X = 1e9
	// fmt.Println(v)

	// fmt.Println(sqrt(2), sqrt(-4))
	// fmt.Println(pow(3, 2, 10),
	// 	pow(3, 3, 20))
	// defer fmt.Println("world")
	// fmt.Println("Hello")

	// fmt.Println("counting")
	// for i := 0; i < 10; i++ {
	// 	defer fmt.Println(i)
	// }
	// fmt.Println("done")

	// i, j := 42, 2701
	// p := &i
	// fmt.Println(*p)
	// *p = 21
	// fmt.Println(i)

	// p = &j
	// *p = *p / 37
	// fmt.Println(j)

}
