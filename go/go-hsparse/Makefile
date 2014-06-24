## simple makefile to log workflow
.PHONY: all test clean build install run

GOFLAGS ?= $(GOFLAGS:)

all: install test run


build:
	@go build $(GOFLAGS) ./...

install:
	@go get $(GOFLAGS) ./...

test: install
	@go test $(GOFLAGS) ./...

clean:
	@go clean $(GOFLAGS) -i ./...

run: install
	@go-hsparse

## EOF
