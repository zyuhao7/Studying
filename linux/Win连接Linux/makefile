.PHONY:all
all:tcp_server udp_server

tcp_server:TcpServer.cc
	g++ -o $@ $^ -std=c++14
udp_server:UdpServer.cc
	g++ -o $@ $^ -std=c++14

.PHONY:clean
clean:
	rm -rf tcp_server udp_server


