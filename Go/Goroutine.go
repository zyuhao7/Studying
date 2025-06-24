// package main

// import (
// 	"fmt"
// 	"sync"
// )

// /*
// 	1. Goroutine 的特点
// 	（1）轻量级
// 	一个 Goroutine 的初始栈大小仅 2KB（可动态扩展），而普通线程通常需要 1MB~2MB。

// 	创建和销毁 Goroutine 的开销极小，可以轻松创建成千上万个。

// 	（2）由 Go 运行时调度
// 	不依赖操作系统线程，而是由 Go 的 调度器（Scheduler） 在用户态管理。

// 	采用 M:N 调度模型（M 个 Goroutine 映射到 N 个 OS 线程），减少线程切换的开销。

// 	（3）通信推荐使用 Channel
// 	Goroutine 之间通常用 Channel（通道） 通信，而不是共享内存（避免竞态条件）.

// 	遵循 CSP（Communicating Sequential Processes）并发模型。
// */

// func sayHello() {
// 	fmt.Println("Hello from Goroutine!")
// }

// // （1）使用 sync.WaitGroup 等待多个 Goroutine
// func worker(id int, wg *sync.WaitGroup) {
// 	defer wg.Done() // 通知 WaitGroup 当前 Goroutine 完成
// 	fmt.Printf("Worker %d done\n", id)
// }

// // （2）使用 Channel 进行通信
// func sendData(ch chan string) {
// 	ch <- "Hello from Channel!" // 发送数据到 Channel
// }

// func main() {

// 	// ch := make(chan string) // 创建一个字符串 Channel
// 	// go sendData(ch)

// 	// msg := <-ch
// 	// fmt.Println(msg)

// 	// var wg sync.WaitGroup

// 	// for i := 1; i <= 3; i++ {
// 	// 	wg.Add(1)
// 	// 	go worker(i, &wg)
// 	// }
// 	// wg.Wait()
// 	// fmt.Println("All workers done")

// 	// go sayHello()               // 启动一个 Goroutine
// 	// time.Sleep(1 * time.Second) // 等待 Goroutine 执行（仅示例，实际应用用 Channel 或 WaitGroup）
// }
