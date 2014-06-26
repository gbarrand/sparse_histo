## simple makefile to log workflow
.PHONY: all clean build 

CXXFLAGS ?= -O3

all: build run

build: hcontest.cpp
	$(CXX) $(CXXFLAGS) -I. hcontest.cpp -o hcontest

run: build gauss.txt hcontest
	./hcontest

gen_data: gen_data.cpp
	$(CXX) $(CXXFLAGS) -I. gen_data.cpp -o gen_data

gauss.txt: gen_data
	./gen_data

clean:
	/bin/rm -f hcontest 
