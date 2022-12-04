package main

import (
	"os"
	"strconv"
)

func main() {
	args := os.Args[1:]
	if len(args) > 0 {
		num, err := strconv.Atoi(args[0])
		check(err)
		switch num {
		case 1:
			day01()
		case 2:
			day02()
		case 3:
			day03()
		default:
			panic("Unknown day given")
		}
	} else {
		panic("No day number given")
	}
}
