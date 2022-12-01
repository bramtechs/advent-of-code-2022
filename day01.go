package main

import (
	"fmt"
	"sort"
	"strconv"
	"strings"
)

func main() {
	content := readFile("input01")
	lines := strings.Split(content, "\n")

	var weights []int
	elfID := 0
	weight := 0
	for _, line := range lines {
		// check if line empty
		line = strings.ReplaceAll(line, "\r", "")
		w, err := strconv.Atoi(line)
		if err != nil {
			weights = append(weights, weight)
			weight = 0
			elfID++
		} else {
			weight += w
		}
	}

	// part one
	heaviest := -1
	for _, weight := range weights {
		if weight > heaviest {
			heaviest = weight
		}
	}
	fmt.Println(heaviest)

	// part two
	sort.Slice(weights, func(i, j int) bool {
		return weights[i] < weights[j]
	})

	top3 := weights[len(weights)-1] + weights[len(weights)-2] + weights[len(weights)-3]
	fmt.Println(top3)
}
