## simple makefile to log workflow
.PHONY: all clean install run

GOFLAGS ?= $(GOFLAGS:)

MYGOPATH := $(shell pwd)
export GOPATH=$(MYGOPATH)

all: install run

install:
	@go get $(GOFLAGS) ./...

clean:
	go clean $(GOFLAGS) -i ./...
	/bin/rm -rf pkg bin

run: install
	./bin/go-hsparse

## EOF
