package main

import "fmt"

// type Integer int

// func (a Integer) Less(b Integer) bool {
// 	return a < b
// }

// type Rect struct {
// 	x, y          float64
// 	width, height float64
// }

// func (r *Rect) Area() float64 {
// 	return r.width * r.height
// }

// func (r *Rect) GetX() float64 {
// 	return r.x
// }

// func (r *Rect) GetY() float64 {
// 	return r.y
// }

// func (r *Rect) GetWidth() float64 {
// 	return r.width
// }

// func (r *Rect) GetHeight() float64 {
// 	return r.height
// }

// type Inner struct {
// 	Name string
// 	Num  int
// }

// type Wrappers struct {
// 	inner Inner
// 	Name  string
// }

// func (wp *Wrappers) PrintInfo() {
// 	fmt.Println(wp.Name)
// 	fmt.Println(wp.inner.Name)
// 	fmt.Println(wp.inner.Num)
// }

type Base struct {
	Name string
}

func (base *Base) Foo() {
	fmt.Println("this is Base Foo")
}

func (base *Base) Bar() {
	fmt.Println("this is base Bar")
}

type Foo struct {
	Base
}

func (foo *Foo) Foo() {
	foo.Base.Foo()
	fmt.Println("this is Foo Foo")
}

type DerivePoint struct {
	*Base
}

func (derivep *DerivePoint) Foo() bool {
	fmt.Println("this is DerivePoint Foo")
	fmt.Println("inherit base, name is ", derivep.Name)
	return true
}

func main() {

	dr := &DerivePoint{Base: &Base{Name: "base"}}
	dr.Foo()

	// foo := &Foo{}
	// foo.Name = "foobase"
	// foo.Foo()

	// foo.Bar()

	// foo.Base.Foo()

	// wp := &Wrappers{Name: "wrapper", inner: Inner{Name: "inner", Num: 100}}
	// wp.PrintInfo()

	// var variant1 Integer = 100
	// var variant2 Integer = 200
	// fmt.Println(variant1.Less(variant2))

}
