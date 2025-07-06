package main

import (
	"fmt"
	"io"
	"net"
	"sync"
	"time"
)

type Server struct {
	Ip   string
	Port int

	// 在线用户列表
	OnlineMap map[string]*User
	mapLock   sync.RWMutex

	// 消息广播的 channel
	Message chan string
}

// 创建一个 server 接口
func NewServer(ip string, port int) *Server {
	server := &Server{
		Ip:        ip,
		Port:      port,
		OnlineMap: make(map[string]*User),
		Message:   make(chan string),
	}
	return server
}

// 启动服务器的接口
func (this *Server) Start() {
	// listen
	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", this.Ip, this.Port))
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	// close listener
	defer listener.Close()

	// 启动监听 Message的goroutine
	go this.ListenMessager()

	for {
		// accept
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listener.Accept() err, ", err)
			continue
		}
		// do handler
		go this.Handler(conn)
	}
}

func (this *Server) Handler(conn net.Conn) {

	remoteAddr := conn.RemoteAddr().String()
	fmt.Printf("来自 %s 的连接建立成功\n", remoteAddr)

	user := NewUser(conn, this)

	user.Online()
	
	// 监听用户是否活跃的 channel
	isLive := make(chan bool)

	// 接收客户端发来的数据
	go func ()  {
		buf := make([] byte, 4096)
		for{
			n, err := conn.Read(buf)
			if n == 0{
				user.Offline()
				return
			}
			if err != nil && err != io.EOF{
				fmt.Println("Conn Read err : ", err)
				return
			}
			// 提取用户的消息, 去除 \n
			msg := string(buf[:n - 1])
			user.DoMessage(msg)

			// 任意的消息代表当前用户是活跃状态
			isLive <- true
		}
	}()

	// 当前 handler 阻塞
	for{
		select {
		case <- isLive:
			 // 当前用户是活跃的, 重置定时器.
			 // do nonthing 为了激活 select 更新下面的定时器
		case <- time.After(time.Second * 300):
			// 已经超时, 强制踢掉用户
			user.SendMsg("超时未发送消息, 你被踢了!\n")
			close(user.C)
			conn.Close()
			return
		}
	}
}

// 新增广播方法

func (this *Server) BroadCst(user *User, msg string) {
	sendMsg := "[" + user.Addr + "]" + user.Name + ":" + msg

	this.Message <- sendMsg
}

// 监听 Message 广播消息 channel 的 goroutine, 一旦有消息就发送给全部在线User
func (this *Server) ListenMessager() {
	for {
		msg := <-this.Message

		this.mapLock.Lock()

		for _, cli := range this.OnlineMap {
			cli.C <- msg
		}
		this.mapLock.Unlock()
	}
}
