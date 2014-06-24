package main

import (
	"fmt"
	"time"

	"github.com/go-hep/dao"
	"github.com/go-hep/random"
)

var tests = []func(n int){
	test_h1d,
}

func main() {

	var entries = 10000000
	for _, f := range tests {
		f(entries)
	}
}

func test_h1d(entries int) {
	gauss := random.Gauss(1, 2, nil)
	h1d := dao.NewH1D(100, -5, +5)
	start := time.Now()
	for i := 0; i < entries; i++ {
		h1d.Fill(gauss(), 1.4)
	}
	delta := time.Since(start)
	fmt.Printf(" h1d.Fill(%d) = %v\n", entries, delta)
}
