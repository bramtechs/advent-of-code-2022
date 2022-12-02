package main

import (
	"fmt"
	"strings"
)

func getBonusScore(you rune, opp rune) int {
	// check if draw
	if you == 'X' && opp == 'A' || you == 'Y' && opp == 'B' || you == 'Z' && opp == 'C' {
		return 3
	}

	// check if won
	if you == 'X' && opp == 'C' || you == 'Y' && opp == 'A' || you == 'Z' && opp == 'B' {
		return 6
	}
	return 0
}

func getRoundScore(you rune, opp rune) int {
	score := 0
	switch you {
	case 'X':
		score = 1
	case 'Y':
		score = 2
	case 'Z':
		score = 3
	}
	score += getBonusScore(you, opp)
	// fmt.Println(string(you), string(opp), score)
	return score
}

func main() {
	content := readFile("input02")
	lines := strings.Split(content, "\n")
	score := 0
	for _, line := range lines {
		if len(line) > 0 {
			you := rune(line[2])
			opp := rune(line[0])
			score += getRoundScore(you, opp)
		}
	}
	fmt.Println(score)
}
