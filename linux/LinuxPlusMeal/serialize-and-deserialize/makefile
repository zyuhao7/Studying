.PHONY:all
all:tcpclient tcpserver

# LDFLAG=-DSELF=1
tcpclient:TcpClientMain.cc
	g++ -o $@ $^ $(LDFLAG) -ljsoncpp -std=c++14 
tcpserver:TcpServerMain.cc
	g++ -o $@ $^ $(LDFLAG) -ljsoncpp -std=c++14 -lpthread

.PHONY:clean
clean:
	rm -f tcpclient tcpserver