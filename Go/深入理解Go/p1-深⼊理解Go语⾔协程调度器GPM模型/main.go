package main

import (
	"fmt"
	"time"
)

func main() {
	// $ GODEBUG=schedtrace=1000 ./main.exe
	for i := 0; i < 5; i++ {
		time.Sleep(time.Second)
		fmt.Println("hello world")
	}
}
