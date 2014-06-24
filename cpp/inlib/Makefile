## simple makefile to log workflow
.PHONY: all clean build 

CXXFLAGS ?= -O3

all: build run

build: hcontest.cpp
	$(CXX) $(CXXFLAGS) -I. hcontest.cpp -o cxx-hcontest

run: build cxx-hcontest
	./cxx-hcontest

clean:
	/bin/rm -f cxx-hcontest
