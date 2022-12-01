package main

import (
	"fmt"
	"os"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func readFile(name string) string {
	path := fmt.Sprintf("./inputs/%s.txt", name)
	dat, err := os.ReadFile(path)
	check(err)
	return string(dat)
}
