// package main

// import (
// 	"fmt"
// 	"reflect"
// )

// // Kind和Type有何不同？
// type Hero struct {
// 	name string
// 	id   int
// }

// func ReflectTypeValue(inter interface{}) {
// 	rtype := reflect.TypeOf(inter)
// 	fmt.Println("reflect type is ", rtype)

// 	rvalue := reflect.ValueOf(inter)
// 	fmt.Println("reflect value is ", rvalue)
// 	fmt.Println("reflect value  kind is ", rvalue.Kind())
// 	fmt.Println("reflect type kind is ", rvalue.Kind())
// 	fmt.Println("reflect value type is ", rvalue.Type())
// }

// // 通过reflect.Value的 NumField 函数获取结构体成员数量.
// func ReflectStructElem(inter interface{}) {
// 	rvalue := reflect.ValueOf(inter)
// 	for i := 0; i < rvalue.NumField(); i++ {
// 		e := rvalue.Field(i)
// 		fmt.Println("element ", i, "its type is ", e.Type())
// 		fmt.Println("element ", i, "its kind is ", e.Kind())
// 		fmt.Println("element ", i, "its value is ", e)
// 	}
// }

// func ReflectStructPtrElem(itf interface{}) {
// 	rvalue := reflect.ValueOf(itf)
// 	for i := 0; i < rvalue.Elem().NumField(); i++ {
// 		elevalue := rvalue.Elem().Field(i)
// 		fmt.Println("element ", i, " its type is ", elevalue.Type())
// 		fmt.Println("element ", i, " its kind is ", elevalue.Kind())
// 		fmt.Println("element ", i, " its value is ", elevalue)
// 	}
// }

// func main() {

// 	// ReflectStructPtrElem(&Hero{name: "Ro", id: 20})
// 	// ReflectStructElem(Hero{name: "jack", id: 1})

// 	// ReflectTypeValue(Hero{name: "jack", id: 1})
// 	// ReflectTypeValue(&Hero{name: "love", id: 1})

// 	// var num float64 = 13.14
// 	// rtype := reflect.TypeOf(num)
// 	// fmt.Println("reflect type is ", rtype)
// 	// rvalue := reflect.ValueOf(num)
// 	// fmt.Println("reflect value is ", rvalue)
// 	// fmt.Println("reflect  value kind is", rvalue.Kind())
// 	// fmt.Println("reflect type kind is", rtype.Kind())
// 	// fmt.Println("reflect  value type is", rvalue.Type())

// 	// rptrvalue := reflect.ValueOf(&num)
// 	// fmt.Println("reflect value is ", rptrvalue)
// 	// fmt.Println("reflect  value kind is", rptrvalue.Kind())
// 	// fmt.Println("reflect type kind is", rptrvalue.Kind())
// 	// fmt.Println("reflect  value type is", rptrvalue.Type())
// 	// if rptrvalue.Elem().CanSet() {
// 	// 	rptrvalue.Elem().SetFloat(131.4)
// 	// }

// 	// fmt.Println(num)

// 	// // rvalue 为 reflect包的 Value类型
// 	// // 可通过 Interface() 转换为 interface{} 类型, 进而转化为原始类型
// 	// rawValue := rvalue.Interface().(float64)
// 	// fmt.Println("rawValue is ", rawValue)

// 	// rawPtrValue := rptrvalue.Interface().(*float64)
// 	// fmt.Println("rawPtrValue is ", *rawPtrValue)
// }
