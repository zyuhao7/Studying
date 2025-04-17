.PHONY:clean

pool_test :main.cc coroutine_pool.cc
	g++ -g -o pool_test main.cc coroutine_pool.cc -I../ -L../lib -lcolib -ldl -lpthread 

clean:
	rm -f pool_test