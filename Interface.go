package main

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
