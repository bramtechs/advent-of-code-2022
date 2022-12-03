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

func findCommon(first_str string, second_str string, third_str string) rune {
	for _, c1 := range first_str {
		for _, c2 := range second_str {
			if c1 == c2 {
				for _, c3 := range third_str {
					if c1 == c3 {
						return c1
					}
				}
			}
		}
	}
	panic("No common badge found")
}

func getPriority(char rune) int {
	if char >= 'a' && char <= 'z' {
		return int(char-'a') + 1
	} else if char >= 'A' && char <= 'Z' {
		return int(char - 'A' + 27)
	}
	panic(fmt.Sprint("Can't get priority of character ", char))
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
			priority += getPriority(dupe)
		}
	}
	fmt.Println(priority)

	priority2 := 0
	for i := 0; i < len(sacks)-1; i += 3 {
		first := sacks[i+0]
		second := sacks[i+1]
		third := sacks[i+2]
		badge := findCommon(first, second, third)
		priority2 += getPriority(badge)
	}
	fmt.Println(priority2)
}
