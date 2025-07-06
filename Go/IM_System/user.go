package main

import (
	"net"
	"strings"
)

type User struct {
	Name string
	Addr string
	C    chan string
	conn net.Conn

	server* Server
}

// 创建一个用户的 API
func NewUser(conn_ net.Conn, server_ *Server) *User {
	userAddr := conn_.RemoteAddr().String()
	user := &User{
		Name: userAddr,
		Addr: userAddr,
		C:    make(chan string),
		conn: conn_,
		server: server_,
	}
	// 启动监听当前 user channel 消息的goroutine
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

// 用户的上线业务
func(this* User) Online(){
	this.server.mapLock.Lock()
	this.server.OnlineMap[this.Name] = this
	this.server.mapLock.Unlock()

	// 广播当前用户上线消息
	this.server.BroadCst(this, "Online now...")
}

// 用户的下线业务
func(this* User) Offline(){
	this.server.mapLock.Lock()
	delete(this.server.OnlineMap, this.Name)
	this.server.mapLock.Unlock()

	// 广播当前用户下线消息
	this.server.BroadCst(this, "Offline now...")
}

// 用户处理消息的业务
func(this* User) DoMessage(msg string){
	if msg == "who"{
		// 查询当前在线用户
		this.server.mapLock.Lock()
		for _, user := range this.server.OnlineMap{
			onlineMsg := "[" + user.Addr + "]" + user.Name  + ":" + "在线...\n"
			this.SendMsg(onlineMsg)
		}
		this.server.mapLock.Unlock()
	} else if len(msg) > 7 && msg[:7] == "rename|"{
		//消息格式 rename|张3
		newName := strings.Split(msg, "|")[1]

		// 判断newName是否存在
		_, ok := this.server.OnlineMap[newName]
		if ok{
			this.SendMsg("当前用户名已经被占用, 请重新输入\n")
		}else{
			this.server.mapLock.Lock()
			delete(this.server.OnlineMap, this.Name)
			this.server.OnlineMap[newName] = this 
			this.server.mapLock.Unlock()

			this.Name = newName
			this.SendMsg("您已经成功更新用户名：" + this.Name + "\n")
		}
	} else if len(msg) > 4 && msg[:3] == "to|"{
		// 私聊模式: 消息格式: to|张三|msg
		remoteName := strings.Split(msg,"|")[1]
		if(remoteName ==""){
			this.SendMsg("消息格式不正确, 请使用 \"to|张三|msg\" 格式. \n")
			return
		}
		remoteUser, ok := this.server.OnlineMap[remoteName]
		if !ok{
			this.SendMsg("该用户不存在!\n")
			return
		}
		content := strings.Split(msg, "|")[2]
		if content == ""{
			this.SendMsg("空消息内容, 请重新发送 \n")
			return
		}
		remoteUser.SendMsg(this.Name + " 对你说的悄悄话: " + content)
	} else{
		this.server.BroadCst(this, msg)
	}
}

// 给当前用户对应的客户端发送消息
func(this* User) SendMsg(msg string){
	this.conn.Write([]byte(msg + "\n"))
}


