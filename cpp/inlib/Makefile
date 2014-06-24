## simple makefile to log workflow
.PHONY: all clean build 

CXXFLAGS ?= -O3

all: build run

build: hcontest.cpp
	$(CXX) $(CXXFLAGS) -I. hcontest.cpp -o hcontest

run: build hcontest
	./hcontest

clean:
	/bin/rm -f hcontest
