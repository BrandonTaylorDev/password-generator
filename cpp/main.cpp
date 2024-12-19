#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#define SYMBOLS "!@#$%^&*()_+-=[]{}|;:,.<>"
#define NUMBERS "0123456789"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"

int get_password_length() {
    std::string input;
    int length;

    std::cout << "Enter password length.\n> ";
    std::getline(std::cin, input);

    try {
        length = std::stoi(input);
        if (length > 0) {
            return length;
        }
    } catch (std::exception&) {
        // Fall through to error message
    }

    std::cout << "Invalid number.\n";
    return get_password_length();
}

bool user_wants_option(const std::string& prompt) {
    std::string input;

    std::cout << prompt << " (Y/n)\n> ";
    std::getline(std::cin, input);

    return input.empty() || input[0] == 'y' || input[0] == 'Y';
}

std::string gen_password(int length, bool upper, bool lower, bool numeral, bool symbol) {
    std::string chars;

    if (!upper && !lower && !numeral && !symbol) {
        upper = lower = numeral = symbol = true;
    }

    if (upper) {
        chars += UPPERCASE;
    }
    if (lower) {
        chars += LOWERCASE;
    }
    if (numeral) {
        chars += NUMBERS;
    }
    if (symbol) {
        chars += SYMBOLS;
    }

    std::string password;
    for (int i = 0; i < length; ++i) {
        password += chars[std::rand() % chars.size()];
    }

    return password;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int password_length = get_password_length();
    bool use_uppers = user_wants_option("Use uppercase letters?");
    bool use_lowers = user_wants_option("Use lowercase letters?");
    bool use_numerals = user_wants_option("Use numbers?");
    bool use_symbols = user_wants_option("Use symbols?");

    std::string password = gen_password(password_length, use_uppers, use_lowers, use_numerals, use_symbols);

    std::cout << "Password: " << password << '\n';

    return 0;
}
