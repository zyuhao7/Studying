CXXFLAGS := -g -std=c++11 -Wall

all: logger test

logger: logger.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ -lpthread

test: test.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ -lpthread

.PHONY: all clean
clean:
	rm -f logger test
