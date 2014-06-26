## simple makefile to log workflow
.PHONY: all clean build 

CXXFLAGS ?= -O3

all: build run

build: hcontest.cpp
	$(CXX) $(CXXFLAGS) -I. hcontest.cpp -o hcontest

run: build data/gauss.txt hcontest
	./hcontest

bin/gen-data: gen-data.cxx
	@mkdir -p bin data
	$(CXX) $(CXXFLAGS) -I. gen-data.cxx -o bin/gen-data

data/gauss.txt: bin/gen-data
	./bin/gen-data

clean:
	/bin/rm -f hcontest 
	/bin/rm -rf data bin
