#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define SYMBOLS "!@#$%^&*()_+-=[]{}|;:,.<>"
#define NUMBERS "0123456789"

int get_password_length() {
    char input[256];
    int length;

    printf("Enter password length.\n> ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        if (sscanf(input, "%d", &length) == 1 && length > 0) {
            return length;
        }
    }

    printf("Invalid number.\n");
    return get_password_length();
}

bool user_wants_option(const char *prompt) {
    char input[256];

    printf("%s (Y/n)\n> ", prompt);
    if (fgets(input, sizeof(input), stdin) != NULL) {
        if (input[0] == 'y' || input[0] == 'Y' || input[0] == '\n') {
            return true;
        }
    }
    return false;
}

void gen_password(int length, bool upper, bool lower, bool numeral, bool symbol, char *output) {
    char chars[256] = "";
    size_t chars_len = 0;

    if (!upper && !lower && !numeral && !symbol) {
        upper = lower = numeral = symbol = true;
    }

    if (upper) {
        strcat(chars, UPPERCASE);
    }
    if (lower) {
        strcat(chars, LOWERCASE);
    }
    if (numeral) {
        strcat(chars, NUMBERS);
    }
    if (symbol) {
        strcat(chars, SYMBOLS);
    }

    chars_len = strlen(chars);

    for (int i = 0; i < length; i++) {
        output[i] = chars[rand() % chars_len];
    }
    output[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));

    int password_length = get_password_length();
    bool use_uppers = user_wants_option("Use uppercase letters?");
    bool use_lowers = user_wants_option("Use lowercase letters?");
    bool use_numerals = user_wants_option("Use numbers?");
    bool use_symbols = user_wants_option("Use symbols?");

    char password[1024];
    gen_password(password_length, use_uppers, use_lowers, use_numerals, use_symbols, password);

    printf("Password: %s\n", password);

    return 0;
}
