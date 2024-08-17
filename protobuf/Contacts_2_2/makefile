all:write read

read:read.cc contacts.pb.cc
	g++ -o $@ $^ -std=c++11 -lprotobuf

write:write.cc contacts.pb.cc
	g++ -o $@ $^ -std=c++11 -lprotobuf

.PHONY:clean
clean:
	rm -f write read

