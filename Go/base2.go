package main

import (
	"fmt"
	"image"
)

// type Vertex struct {
// 	X, Y float64
// }

// func (v Vertex) Abs() float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// func Abs(v Vertex) float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// type MyFloat float64

// func (f MyFloat) Abs() float64 {
// 	if f < 0 {
// 		return float64(-f)
// 	}
// 	return float64(f)
// }

type Vertex struct {
	X, Y float64
}

// func (v Vertex) Abs() float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

//	func (v *Vertex) Scale(f float64) {
//		v.X = v.X * f
//		v.Y = v.Y * f
//	}
// func Abs(v Vertex) float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }
// func Scale(v *Vertex, f float64) {
// 	v.X = v.X * f
// 	v.Y = v.Y * f
// }

// func (v *Vertex) Scale(f float64) {
// 	v.X = v.X * f
// 	v.Y = v.Y * f
// }

// func ScaleFunc(v *Vertex, f float64) {
// 	v.X = v.X * f
// 	v.Y = v.Y * f
// }

// func (v Vertex) Abs() float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// func AbsFunc(v Vertex) float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// func (v *Vertex) Scale(f float64) {
// 	v.X = v.X * f
// 	v.Y = v.Y * f
// }

// func (v *Vertex) Abs() float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// type Abser interface {
// 	Abs() float64
// }

// type MyFloat float64

// func (f MyFloat) Abs() float64 {
// 	if f < 0 {
// 		return float64(-f)
// 	}
// 	return float64(f)
// }

// func (v *Vertex) Abs() float64 {
// 	return math.Sqrt(v.X*v.X + v.Y*v.Y)
// }

// type I interface {
// 	M()
// }

// type T struct {
// 	S string
// }

// func (t *T) M() {
// 	fmt.Println(t.S)
// }

// type F float64

// func (f F) M() {
// 	fmt.Println(f)
// }
// func describe(i I) {
// 	fmt.Printf("(%v, %T)", i, i)
// }

// type I interface {
// 	M()
// }
// type T struct {
// 	S string
// }

// func (t *T) M() {
// 	if t == nil {
// 		fmt.Println("<nil>")
// 		return
// 	}
// 	fmt.Println(t.S)
// }

// func describe(i I) {
// 	fmt.Printf("(%v, %T)", i, i)
// }

// type I interface{
// 	M()
// }

// func describe(i interface{}) {
// 	fmt.Printf("(%v, %T)\n", i, i)
// }

// func do(i interface{}) {
// 	switch v := i.(type) {
// 	case int:
// 		fmt.Printf("Twice %v is %v \n", v, v*2)
// 	case string:
// 		fmt.Printf("%q is %v bytes long\n", v, len(v))
// 	default:
// 		fmt.Printf("i don't know about type %T !\n", v)
// 	}
// }

// type Person struct {
// 	Name string
// 	Age  int
// }

// func (p Person) String() string {
// 	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
// }

// type IPAddr [4]byte

// func (ip IPAddr) String() string {
// 	return fmt.Sprintf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3])
// }

// type MyError struct {
// 	When time.Time
// 	What string
// }

// func (e *MyError) Error() string {
// 	return fmt.Sprintf("at %v, %s", e.When, e.What)
// }

// func run() error {
// 	return &MyError{
// 		time.Now(),
// 		"It didn't work",
// 	}
// }

// type ErrNegativeSqrt float64

// func (e ErrNegativeSqrt) Error() string {
// 	return fmt.Sprintf("cannot Sqrt negative number: %v", float64(e))
// }

// func Sqrt(x float64) (float64, error) {
// 	if x < 0 {
// 		return 0, ErrNegativeSqrt(x)
// 	}
// 	z := 1.0
// 	for i := 0; i < 10; i++ {
// 		z -= (z*z - x) / (2 * z)
// 	}
// 	return z, nil
// }

func main() {
	m := image.NewRGBA(image.Rect(0, 0, 100, 100))
	fmt.Println(m.Bounds())
	fmt.Println(m.At(0, 0).RGBA())

	// r := strings.NewReader("Hello, Reader!")

	// b := make([]byte, 8)
	// for {
	// 	n, err := r.Read(b)
	// 	fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
	// 	fmt.Printf("b[:n] = %q\n", b[:n])
	// 	if err == io.EOF {
	// 		break
	// 	}
	// }

	// fmt.Println(Sqrt(2))
	// fmt.Println(Sqrt(-2))

	// if err := run(); err != nil {
	// 	fmt.Println(err)
	// }

	// hosts := map[string]IPAddr{
	// 	"loopback":  {127, 0, 0, 1},
	// 	"googleDNS": {8, 8, 8, 8},
	// }
	// for name, ip := range hosts {
	// 	fmt.Printf("%v: %v\n", name, ip)
	// }

	// a := Person{"Arthur Dent", 42}
	// z := Person{"Zaphod Beeblebrox", 9001}
	// fmt.Println(a, z)

	// do(21)
	// do("hel")
	// do(true)

	// var i interface{} = "hello"
	// s := i.(string)
	// fmt.Println(s)

	// s, ok := i.(string)
	// fmt.Println(s, ok)

	// f, ok := i.(float64)
	// fmt.Println(f, ok)

	// f = i.(float64) // panic: interface conversion: interface {} is string, not float64

	// fmt.Println(f)

	// var i interface{}
	// describe(i)
	// i = 42
	// describe(i)
	// i = "hello"
	// describe(i)

	// var i I
	// describe(i)
	// i.M()

	// var i I
	// var t *T
	// i = t
	// describe(i)
	// i.M()

	// i = &T{"Hello"}
	// describe(i)
	// i.M()

	// var i I
	// i = &T{"Hello"}
	// describe(i)
	// i.M()

	// i = F(math.Pi)
	// describe(i)
	// i.M()

	// var a Abser
	// f := MyFloat(-math.Sqrt2)
	// v := Vertex{3, 4}

	// a = f  // a MyFloat implements Abser
	// a = &v // a *Vertex implements Abser

	// In the following line, v is a Vertex (not *Vertex)
	// and does NOT implement Abser.
	// a = v

	// fmt.Println(a.Abs())

	// v := &Vertex{3, 4}
	// fmt.Printf("Before scaling: %+v, Abs: %v\n", v, v.Abs())
	// v.Scale(5)
	// fmt.Printf("After scaling: %+v, Abs: %v\n", v, v.Abs())

	// v := Vertex{3, 4}
	// fmt.Println(v.Abs())
	// fmt.Println(AbsFunc(v))

	// p := &Vertex{4, 3}
	// fmt.Println(p.Abs())
	// fmt.Println(AbsFunc(*p))

	// v := Vertex{3, 4}
	// v.Scale(2)
	// ScaleFunc(&v, 10)

	// p := &Vertex{4, 3}
	// p.Scale(3)
	// ScaleFunc(p, 8)

	// fmt.Println(v, p)

	// v := Vertex{3, 4}
	// Scale(&v, 10)
	// fmt.Println(Abs(v))

	// v := Vertex{3, 4}
	// v.Scale(10)
	// fmt.Println(v.Abs())

	// f := MyFloat(-math.Sqrt2)
	// fmt.Println(f.Abs())

	// v := Vertex{3, 4}
	// fmt.Println(Abs(v))

	// v := Vertex{3, 4}
	// fmt.Println(v.Abs())
}

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

// func main() {
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

// }
