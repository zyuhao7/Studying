package main

import "net"

type User struct {
	Name string
	Addr string
	C    chan string
	conn net.Conn
}

// 创建一个用户的 API
func NewUser(conn_ net.Conn) *User {
	userAddr := conn_.RemoteAddr().String()
	user := &User{
		Name: userAddr,
		Addr: userAddr,
		C:    make(chan string),
		conn: conn_,
	}
	// 启动监听当前 user channel消息的goroutine
	go user.ListenMessage()
	return user
}

// 监听当前 User channel 的方法，一旦有消息，就直接发送给对端客户端
func (this *User) ListenMessage() {
	for {
		msg := <-this.C
		this.conn.Write([]byte(msg + "\n"))
	}
}
