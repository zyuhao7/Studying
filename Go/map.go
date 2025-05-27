package main

import (
	"fmt"
	"sort"
)

type PersonInfo struct {
	id      string
	Name    string
	Address string
}

var personDB map[string]PersonInfo

func main() {
	personDB = make(map[string]PersonInfo)

	// 添加数据
	personDB["123456"] = PersonInfo{"123456", "张三", "北京市海淀区"}
	personDB["654321"] = PersonInfo{"654321", "李四", "上海市浦东新区"}

	// 访问数据
	if person, exists := personDB["123456"]; exists {
		println("ID:", person.id, "Name:", person.Name, "Address:", person.Address)
	} else {
		println("Person not found")
	}

	// 删除数据
	delete(personDB, "123456")

	// 遍历 map
	for id, info := range personDB {
		println("ID:", id, "Name:", info.Name, "Address:", info.Address)
	}

	var data map[string]int = map[string]int{"Bob": 18, "luce": 20}
	modify(data, "lily", 19)
	modify(data, "luce", 22)
}

func modify(data map[string]int, key string, value int) {
	v, res := data[key]
	if !res {
		fmt.Println("Key not found")
		return
	}
	fmt.Println("key is ", key, "value is ", v)
	data[key] = value

	fmt.Println(len(data))

	var data2 map[string]int = make(map[string]int, 3)
	data2["sven"] = 19
	data2["sven"] = 20
	data2["bob"] = 178
	data2["Arean"] = 33

	fmt.Println(data2)

	for key, value := range data2 {
		fmt.Println("key is ", key, "value is ", value)
	}

	sortPrintMap(data2)
	fmt.Println("After sort:")
	for key, value := range data2 {
		fmt.Println("key is ", key, "value is ", value)
	}

	// 二维map
	var userdata map[string]map[string]int
	userdata = make(map[string]map[string]int)
	userdata["Bob"] = make(map[string]int)
	userdata["Bob"]["age"] = 18
	userdata["Bob"]["height"] = 180

	userdata["Alice"] = make(map[string]int)
	userdata["Alice"]["age"] = 20
	userdata["Alice"]["height"] = 170
	for k, v := range userdata {
		for k2, v2 := range v {
			fmt.Println(k, ":", k2, "=", v2)
		}
	}

	// slice 中存储map
	slicemap := make([]map[string]int, 5)
	for i := 0; i < 5; i++ {
		slicemap[i] = make(map[string]int)
	}
	fmt.Println(slicemap)

	rvmap := make(map[int]string)
	for k, v := range data2 {
		rvmap[v] = k
	}
	fmt.Println(rvmap)
	fmt.Println(data2)
}

func sortPrintMap(data map[string]int) {
	slice := make([]string, 0)
	for k, _ := range data {
		slice = append(slice, k)
	}
	sort.Strings(slice)
	for _, s := range slice {
		d, e := data[s]
		if !e {
			continue
		}
		fmt.Println("key is ", s, "value is ", d)
	}
}
