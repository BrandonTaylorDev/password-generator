<?php

function get_password_length(): int {
    echo "Enter password length.\n> ";
    $input = trim(fgets(STDIN));

    if (is_numeric($input) && (int)$input > 0) {
        return (int)$input;
    }

    echo "Invalid number.\n";
    return get_password_length();
}

function user_wants_option(string $prompt): bool {
    echo "$prompt (Y/n)\n> ";
    $input = trim(fgets(STDIN));

    return $input === '' || strtolower($input) === 'y';
}

function gen_password(int $length, bool $upper, bool $lower, bool $numeral, bool $symbol): string {
    $upper_chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $lower_chars = 'abcdefghijklmnopqrstuvwxyz';
    $number_chars = '0123456789';
    $symbol_chars = '!@#$%^&*()_+-=[]{}|;:,.<>'; 

    $chars = '';

    if (!$upper && !$lower && !$numeral && !$symbol) {
        $upper = $lower = $numeral = $symbol = true;
    }

    if ($upper) {
        $chars .= $upper_chars;
    }
    if ($lower) {
        $chars .= $lower_chars;
    }
    if ($numeral) {
        $chars .= $number_chars;
    }
    if ($symbol) {
        $chars .= $symbol_chars;
    }

    $password = '';
    for ($i = 0; $i < $length; $i++) {
        $password .= $chars[random_int(0, strlen($chars) - 1)];
    }

    return $password;
}

$password_length = get_password_length();
$use_uppers = user_wants_option("Use uppercase letters?");
$use_lowers = user_wants_option("Use lowercase letters?");
$use_numerals = user_wants_option("Use numbers?");
$use_symbols = user_wants_option("Use symbols?");

$password = gen_password($password_length, $use_uppers, $use_lowers, $use_numerals, $use_symbols);

echo "Password: $password\n";

?>
