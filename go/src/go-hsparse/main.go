package main

import (
	"fmt"
	"time"

	"github.com/go-hep/dao"
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
	h1d := dao.NewH1D(100, -5, +5)
	start := time.Now()
	for i := 0; i < entries; i++ {
		x := float64(i%10) - 5
		h1d.Fill(x, 1.4)
	}
	delta := time.Since(start)
	fmt.Printf(" h1d.Fill(%d) = %v (mean=%v rms=%v)\n", entries, delta, h1d.Mean(), h1d.RMS())
}
