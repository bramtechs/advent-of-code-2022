package main

import (
	"fmt"
	"strings"
)

func runeSliceContains(slice []rune, match rune) bool {
	for _, run := range slice {
		if run == match {
			return true
		}
	}
	return false
}

func getDupes(first_str string, second_str string) []rune {
	var dupes []rune
	for _, first := range first_str {
		for _, second := range second_str {
			if first == second && !runeSliceContains(dupes, first) {
				// also check if already registered
				dupes = append(dupes, first)
			}
		}
	}
	return dupes
}

func main() {
	content := readFile("input03")
	sacks := strings.Split(content, "\n")
	priority := 0
	for _, sack := range sacks {
		half := len(sack) / 2
		first_half := sack[:half]
		second_half := sack[half:]

		// remove windows awfulness
		second_half = strings.ReplaceAll(second_half, "\r", "")

		// find duplicates
		dupes := getDupes(first_half, second_half)
		//fmt.Println(string(dupes))

		// calculate priority
		for _, dupe := range dupes {
			// lowercase
			if dupe >= 'a' && dupe <= 'z' {
				priority += int(dupe-'a') + 1
			} else if dupe >= 'A' && dupe <= 'Z' {
				priority += int(dupe - 'A' + 27)
			} else {
				panic(fmt.Sprint("Unparsable character ", dupe))
			}
		}
	}
	fmt.Println(priority)
}
