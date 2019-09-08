all: test

#CXX=clang++
CXX=g++
CXXFLAGS= -g -Wall -Wno-sign-compare -Wno-unused-value -std=c++17 -I /opt/miniconda3/envs/info-111/include/
LDFLAGS=-lpthread

timer-test: timer-test.cpp timer.hpp

laby-test: laby-test.cpp laby.hpp

laby-widget-test: laby-widget-test.cpp laby-widget.hpp laby.hpp

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: laby-test timer-test laby-widget-test.o
	laby-test
	timer-test

clean:
	-rm *.o laby-test timer-test laby-widget-test
