package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	var n1, n2, n3 int = 0, 0, 1
	return func() int {
		n1 = n2
		n2 = n3
		n3 = n1 + n2
		return n3
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
