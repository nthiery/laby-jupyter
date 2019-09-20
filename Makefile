PREFIX=$(CONDA_PREFIX)

#CXX=clang++
CXX=g++
CXXFLAGS= -g -Wall -Wno-sign-compare -Wno-unused-value -std=c++17 -I include -I $(PREFIX)/include
LDFLAGS=-lpthread

all: test

timer-test: timer-test.cpp include/laby/timer.hpp

laby-test: laby-test.cpp include/laby/laby.hpp

laby-widget-test: laby-widget-test.cpp include/laby/laby-widget.hpp include/laby/laby.hpp

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: laby-test timer-test laby-widget-test.o
	laby-test
	timer-test

clean:
	-rm *.o laby-test timer-test laby-widget-test
