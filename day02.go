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
	default:
		panic("Unexpected char")
	}
	score += getBonusScore(you, opp)
	// fmt.Println(string(you), string(opp), score)
	return score
}

func simulateLosing(opp rune) rune {
	switch opp {
	case 'A':
		return 'Z'
	case 'B':
		return 'X'
	case 'C':
		return 'Y'
	default:
		panic("Unexpected char")
	}
}

func simulateWinning(opp rune) rune {
	switch opp {
	case 'A':
		return 'Y'
	case 'B':
		return 'Z'
	case 'C':
		return 'X'
	default:
		panic("Unexpected char")
	}
}

func simulateDraw(opp rune) rune {
	return opp + 23 // see ascii table
}

func getSimulatedScore(opp rune, outcome rune) int {
	you := '?'
	switch outcome {
	case 'X':
		you = simulateLosing(opp)
	case 'Y':
		you = simulateDraw(opp)
	case 'Z':
		you = simulateWinning(opp)
	default:
		panic("Unexpected char")
	}
	return getRoundScore(you, opp)
}

func day02() {
	content := readFile("input02")
	lines := strings.Split(content, "\n")
	score := 0
	score2 := 0
	for _, line := range lines {
		if len(line) > 0 {
			you := rune(line[2])
			opp := rune(line[0])
			score += getRoundScore(you, opp)
			score2 += getSimulatedScore(opp, you)
		}
	}
	fmt.Println(score)
	fmt.Println(score2)
}
