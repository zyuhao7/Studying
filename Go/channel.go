package main

// 非缓冲chan, 读写对称
// 非缓冲channel,要求一端读取，一端写入。channel大小为零，所以读写操作一定要匹配

// func main() {
// 	nochan := make(chan int)

// 	nochan <- 5 // 死锁
// 	go func(ch chan int) {
// 		data := <-ch
// 		fmt.Println("receive data", data)
// 	}(nochan)

// 	fmt.Println("send data 5")
// }

// func main() {
// 	nochan := make(chan int)
// 	waiter := &sync.WaitGroup{}

// 	waiter.Add(2)

// 	go func(ch chan int, wgrp *sync.WaitGroup) {
// 		data := <-ch
// 		fmt.Println("receive data ", data)
// 		wgrp.Done()
// 	}(nochan, waiter)

// 	go func(ch chan int, wgrp *sync.WaitGroup) {
// 		ch <- 5
// 		fmt.Println("send data 5")
// 		waiter.Done()
// 	}(nochan, waiter)

// 	waiter.Wait()
// }

// range 自动读取
// 缓冲channel, 先进先出
// func main() {
// 	catchan := make(chan int, 2)

// 	go func(ch chan int) {
// 		for i := 0; i < 2; i++ {
// 			ch <- i
// 			fmt.Println("send data is", i)
// 		}
// 		// close(ch) // 不关闭 ch, 主协程无法range退出
// 	}(catchan)

// 	// for data := range catchan {
// 	// 	fmt.Println("receive data is ", data)
// 	// }
// 	for i := 0; i < 2; i++ {
// 		data := <-catchan
// 		fmt.Println("receive data is ", data)
// 	}
// }

// 读取关闭的channel
// func main() {
// 	nochan := make(chan int)

// 	go func(ch chan int) {
// 		ch <- 100
// 		fmt.Println("send data is", 100)
// 		close(ch)
// 		fmt.Println("goroutine exit")
// 	}(nochan)

// 	data := <-nochan
// 	fmt.Println("receive data is ", data)

// 	data, ok := <-nochan
// 	if !ok {
// 		fmt.Println("receive close chan")
// 		fmt.Println("receive data is ", data)
// 	}
// 	close(nochan) // 二次关闭
// 	fmt.Println("main exited")

// }

// select 多路复用，大巧不工
// select 内部可以写多个协程读写，通过case完成多路复用，其结构如下

// select {
//     case ch <- 100:
//         ...
//     case <- ch2:
//         ...
//     dafault:
//         ...
// }
// 如果有多个case满足条件，则select随机选择一个执行。否则进入dafault执行。 我们可以利用上面的九种原理配合select创造出各种并发场景

// 并发实战
/*
	1 主协程启动两个协程，协程1负责发送数据给协程2，协程2负责接收并累加获得的数据。
	2 主协程等待两个子协程退出，当主协程意外退出时通知两个子协程退出。
	3 当发送协程崩溃和主动退出时通知接收协程也要退出，然后主协程退出
	4 当接收协程崩溃或主动退出时通知发送协程退出，然后主协程退出。
	5 无论三个协程主动退出还是panic，都要保证所有资源手动回收。
*/

// func main() {
// 	datachan := make(chan int)
// 	groutineclose := make(chan struct{})
// 	mainclose := make(chan struct{})
// 	var onceclose sync.Once
// 	var readclose sync.Once
// 	var sendclose sync.Once
// 	var waitgroup sync.WaitGroup
// 	waitgroup.Add(2)

// 	go func(datachan chan int, gclose chan struct{}, mclose chan struct{}, group *sync.WaitGroup) {
// 		defer func() {
// 			onceclose.Do(func() {
// 				close(gclose)
// 			})
// 			sendclose.Do(func() {
// 				close(datachan)
// 				fmt.Println("send goroutine closed !")
// 				group.Done()
// 			})
// 		}()

// 		for i := 0; i < 100; i++ {
// 			select {
// 			case <-gclose:
// 				fmt.Println("other goroutine exited")
// 				return
// 			case <-mclose:
// 				fmt.Println("main goroutine exited")
// 				return
// 				/*
// 				   default:
// 				       datachan <- i
// 				*/
// 			case datachan <- i:
// 			}
// 		}
// 	}(datachan, groutineclose, mainclose, &waitgroup)

// 	go func(datachan chan int, gclose chan struct{}, mclose chan struct{}, group *sync.WaitGroup) {
// 		sum := 0
// 		defer func() {
// 			onceclose.Do(func() {
// 				close(gclose)
// 			})
// 			readclose.Do(func() {
// 				fmt.Println("sum is ", sum)
// 				fmt.Println("receive goroutine closed !")
// 				group.Done()
// 			})
// 		}()

// 		for i := 0; ; i++ {
// 			select {
// 			case <-gclose:
// 				fmt.Println("other goroutine exited")
// 				return
// 			case <-mclose:
// 				fmt.Println("main goroutine exited")
// 				return
// 				// case data, ok := <-datachan:
// 				// 	if !ok {
// 				// 		fmt.Println("receive close chan data")
// 				// 		return
// 				// 	}
// 			case data, ok := <-datachan:
// 				if !ok {
// 					fmt.Println("receive close chan data")
// 					return
// 				}
// 				sum += data
// 				if i >= 20 {
// 					panic("receive goroutine test panic !!")
// 				}
// 				sum += data
// 			}
// 		}
// 	}(datachan, groutineclose, mainclose, &waitgroup)

// 	waitgroup.Wait()
// 	fmt.Println("main exited")
// }
