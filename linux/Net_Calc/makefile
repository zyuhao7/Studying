.PHONY:all
all:tcpServer tcpClient
tcpServer:TcpServerMain.cc
	g++ -o $@ $^ -std=c++14 -lpthread
tcpClient:TcpClientMain.cc
	g++ -o $@ $^ -std=c++14 

.PHONY:clean
clean:
	rm -f  tcpServer tcpClient