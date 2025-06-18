package main

import (
	"fmt"
	"math/rand"
)

// type IOInter interface {
// 	write() int
// 	read() int
// }

// func WriteFunc(io IOInter) {
// 	io.write()
// }

// type Hero struct {
// 	Name    string
// 	Attack  int
// 	Defence int
// 	GenTime int64
// }

// func (hl HeroList) Len() int {
// 	return len(hl)
// }

// func (hl HeroList) Less(i, j int) bool {
// 	if i < 0 || j < 0 {
// 		return true
// 	}
// 	length := hl.Len()
// 	if i >= length || j >= length {
// 		return true
// 	}

// 	if hl[i].Attack != hl[j].Attack {
// 		return hl[i].Attack < hl[j].Attack
// 	}

// 	if hl[i].Defence != hl[j].Defence {
// 		return hl[i].Defence < hl[j].Defence
// 	}

// 	return hl[i].GenTime < hl[j].GenTime
// }
// func (hl HeroList) Swap(i, j int) {
// 	if i < 0 || j < 0 {
// 		return
// 	}

// 	length := len(hl)
// 	if i >= length || j >= length {
// 		return
// 	}

// 	hl[i], hl[j] = hl[j], hl[i]

// }

// type HeroList []*Hero

// interface实现万能类型双向链表
type LinkEle struct {
	Data interface{}
	Pre  *LinkEle
	Next *LinkEle
}
type LinkList struct {
	Head *LinkEle
	Tail *LinkEle
}

func (le *LinkEle) GetData() interface{} {
	return le.Data
}

func (ll *LinkList) InsertHead(le *LinkEle) {
	if ll.Head == nil && ll.Tail == nil {
		ll.Tail = le
		ll.Head = ll.Tail
		return
	}
	//   le <-> Head   Tail
	ll.Head.Pre = le
	le.Next = ll.Head
	le.Pre = nil
	ll.Head = le
}

func (ll *LinkList) InsertTail(le *LinkEle) {
	if ll.Head == nil && ll.Tail == nil {
		ll.Tail = le
		ll.Head = ll.Tail
		return
	}
	ll.Tail.Next = le
	le.Next = nil
	le.Pre = ll.Tail
	ll.Tail = le
}

func (ll *LinkList) InsertIndex(le *LinkEle, idx int) {
	if idx < 0 {
		return
	}
	if ll.Head == nil {
		ll.Head = le
		ll.Tail = ll.Head
		return
	}
	node := ll.Head
	FindIdx := 0

	for ; FindIdx < idx; FindIdx++ {
		if node.Next == nil {
			break
		}
		node = node.Next
	}
	if FindIdx != idx {
		fmt.Println("index is out of range")
		return
	}
	Next := node.Next
	node.Next = le
	le.Pre = node

	if node == ll.Tail {
		ll.Tail = le
		return
	}

	if Next != nil {
		le.Next = Next
		Next.Pre = node
	}
}

func (ll *LinkList) DelIndex(idx int) {
	if idx < 0 || ll.Head == nil {
		return
	}

	node := ll.Head
	FindIdx := 0
	for ; FindIdx < idx; FindIdx++ {
		if node.Next == nil {
			break
		}
		node = node.Next
	}
	if FindIdx != idx {
		fmt.Println("index out of range")
		return
	}
	// 只有一个节点
	if ll.Head == ll.Tail {
		ll.Head = nil
		ll.Tail = ll.Head
		return
	}
	// 如果是头结点
	if node == ll.Head {
		ll.Head = node.Next
		node.Next.Pre = nil
		return
	}
	// 如果是尾结点
	if node == ll.Tail {
		ll.Tail = node.Pre
		node.Pre.Next = nil
		return
	}

	// 直接断开
	node.Next.Pre = node.Pre
	node.Pre.Next = node.Next

}

// interface万能接口

func main() {
	ll := &LinkList{nil, nil}
	fmt.Println("insert head .....................")
	for i := 0; i < 2; i++ {
		num := rand.Intn(100)
		node1 := &LinkEle{Data: num, Next: nil, Pre: nil}
		ll.InsertHead(node1)
		fmt.Println(num)
	}
	fmt.Println("after insert head .................")
	for node := ll.Head; node != nil; node = node.Next {
		val, ok := node.GetData().(int)
		if !ok {
			fmt.Println("interface transfer error")
			break
		}
		fmt.Println(val)
	}

	fmt.Println("insert tail .....................")
	for i := 0; i < 2; i++ {
		num := rand.Intn(100)
		node1 := &LinkEle{Data: num, Next: nil, Pre: nil}
		ll.InsertTail(node1)
		fmt.Println(num)
	}

	fmt.Println("after insert tail .................")
	for node := ll.Head; node != nil; node = node.Next {
		val, ok := node.GetData().(int)
		if !ok {
			fmt.Println("interface transfer error")
			break
		}
		fmt.Println(val)
	}
	fmt.Println("insert after third element........")
	{
		num := rand.Intn(100)
		node1 := &LinkEle{Data: num, Next: nil, Pre: nil}
		ll.InsertIndex(node1, 2)
		fmt.Println(num)
	}

	fmt.Println("after insert index .................")
	for node := ll.Head; node != nil; node = node.Next {
		val, ok := node.GetData().(int)
		if !ok {
			fmt.Println("interface transfer error")
			break
		}
		fmt.Println(val)
	}

	fmt.Println("delete second element, its index is 1")
	ll.DelIndex(1)
	fmt.Println("after delete second element, its index is 1")
	for node := ll.Head; node != nil; node = node.Next {
		val, ok := node.GetData().(int)
		if !ok {
			fmt.Println("interface transfer error")
			break
		}
		fmt.Println(val)
	}

	// var herolists HeroList
	// var inter interface{}
	// inter = herolists
	// val, ok := inter.(HeroList)
	// if !ok {
	// 	fmt.Println("inter can't transfer to HeroList!")
	// 	return
	// }
	// fmt.Println("herolists's len is:", val.Len())

	// for i := 0; i < 10; i++ {
	// 	generate := time.Now().Unix()
	// 	name := fmt.Sprintf("Hero%d", generate)
	// 	hero := Hero{
	// 		Name:    name,
	// 		Attack:  rand.Intn(10),
	// 		Defence: rand.Intn(20),
	// 		GenTime: generate,
	// 	}
	// 	herolists = append(herolists, &hero)
	// 	time.Sleep(time.Duration(1) * time.Second)
	// }

	// sort.Sort(herolists)
	// for _, value := range herolists {
	// 	fmt.Print(value.Name, " ", value.Attack, " ", value.Defence, " ", value.GenTime, "\n")
	// }

	// array := []int{6, 1, 0, 5, 2, 7}
	// sort.Ints(array)
	// fmt.Println(array)
}

// type Bird interface {
// 	Fly() string
// }

// type Plane struct {
// 	name string
// }

// func (p *Plane) Fly() string {
// 	fmt.Println(p.name, "can fly like a bird")
// 	return p.name
// }

// type Butterfly struct {
// 	name string
// }

// func (bf *Butterfly) Fly() string {
// 	fmt.Println(bf.name, "can fly like a bird")
// 	return bf.name
// }

// func FlyLikeBird(bird Bird) {
// 	bird.Fly()
// }

// func GetFlyType(bird Bird) {
// 	_, ok := bird.(*Butterfly)
// 	if ok {
// 		fmt.Println("type is butterfly")
// 		return
// 	}
// 	_, ok = bird.(*Plane)
// 	if ok {
// 		fmt.Println("type is *Plane")
// 		return
// 	}
// 	fmt.Println("unknown type")
// }

// type Human struct {
// }

// func (*Human) Walk() {

// }

// func GetFlyType2(inter interface{}) {
// 	_, ok := inter.(*Butterfly)
// 	if ok {
// 		fmt.Println("type is *butterfly")
// 		return
// 	}

// 	_, ok = inter.(*Plane)
// 	if ok {
// 		fmt.Println("type is *Plane")
// 		return
// 	}

// 	_, ok = inter.(*Human)
// 	if ok {
// 		fmt.Println("type is *Human")
// 		return
// 	}
// 	fmt.Println("Unknown type")
// }

// func GetFlyType3(inter interface{}) {
// 	switch inter.(type) {
// 	case *Butterfly:
// 		fmt.Println("type is *Butterfly")
// 	case *Plane:
// 		fmt.Println("type is *Plane")
// 	case *Human:
// 		fmt.Println("type is *Human")
// 	default:
// 		fmt.Println("Unknown type")
// 	}
// }

// func main() {
// 	p1 := &Plane{name: "plane"}
// 	p1.Fly()

// 	bf := &Butterfly{name: "butterfly"}
// 	bf.Fly()

// 	hu := &Human{}

// 	FlyLikeBird(p1)
// 	FlyLikeBird(bf)

// 	GetFlyType(p1)
// 	GetFlyType(bf)

// 	GetFlyType2(p1)
// 	GetFlyType2(bf)
// 	GetFlyType2(hu)

// 	GetFlyType3(p1)
// 	GetFlyType3(bf)
// 	GetFlyType3(hu)
// }
