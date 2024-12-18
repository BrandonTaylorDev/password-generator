package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
)

func main() {
	passwordLength := getPasswordLength()
	useUppers := userWants("Use uppercase letters? (Y/n)")
	useLowers := userWants("Use lowercase letters? (Y/n)")
	useNumerals := userWants("Use numbers? (Y/n)")
	useSymbols := userWants("Use symbols? (Y/n)")

	password := genPassword(passwordLength, useUppers, useLowers, useNumerals, useSymbols)

	fmt.Printf("Password: %s\n", password)
}

func getPasswordLength() int {
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print("Enter password length.\n> ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)

		length, err := strconv.Atoi(input)
		if err != nil || length <= 0 {
			fmt.Println("Invalid number.")
		} else {
			return length
		}
	}
}

func userWants(prompt string) bool {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("%s\n> ", prompt)
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(strings.ToLower(input))

	return input == "y"
}

func genPassword(length int, upper, lower, numeral, symbol bool) string {
	var chars []rune

	if !(upper || lower || numeral || symbol) {
		upper, lower, numeral, symbol = true, true, true, true
	}

	if upper {
		chars = append(chars, []rune("ABCDEFGHIJKLMNOPQRSTUVWXYZ")...)
	}
	if lower {
		chars = append(chars, []rune("abcdefghijklmnopqrstuvwxyz")...)
	}
	if numeral {
		chars = append(chars, []rune("0123456789")...)
	}
	if symbol {
		chars = append(chars, []rune("!@#$%^&*()_+-=[]{}|;:,.<>")...)
	}

	password := make([]rune, length)
	for i := 0; i < length; i++ {
		password[i] = chars[rand.Intn(len(chars))]
	}

	return string(password)
}
