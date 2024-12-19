using System;
using System.Text;

class PasswordGenerator
{
    static void Main(string[] args)
    {
        int passwordLength = GetPasswordLength();
        bool useUppers = UserWantsOption("Use uppercase letters?");
        bool useLowers = UserWantsOption("Use lowercase letters?");
        bool useNumerals = UserWantsOption("Use numbers?");
        bool useSymbols = UserWantsOption("Use symbols?");

        string password = GeneratePassword(passwordLength, useUppers, useLowers, useNumerals, useSymbols);

        Console.WriteLine($"Password: {password}");
    }

    static int GetPasswordLength()
    {
        Console.WriteLine("Enter password length.\n> ");
        string input = Console.ReadLine();

        if (int.TryParse(input, out int length) && length > 0)
        {
            return length;
        }

        Console.WriteLine("Invalid number.");
        return GetPasswordLength();
    }

    static bool UserWantsOption(string prompt)
    {
        Console.WriteLine($"{prompt} (Y/n)\n> ");
        string input = Console.ReadLine();

        return string.IsNullOrEmpty(input) || input.ToLower() == "y";
    }

    static string GeneratePassword(int length, bool upper, bool lower, bool numeral, bool symbol)
    {
        const string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const string lowerChars = "abcdefghijklmnopqrstuvwxyz";
        const string numberChars = "0123456789";
        const string symbolChars = "!@#$%^&*()_+-=[]{}|;:,.<>";

        StringBuilder chars = new StringBuilder();

        if (!upper && !lower && !numeral && !symbol)
        {
            upper = lower = numeral = symbol = true;
        }

        if (upper)
        {
            chars.Append(upperChars);
        }
        if (lower)
        {
            chars.Append(lowerChars);
        }
        if (numeral)
        {
            chars.Append(numberChars);
        }
        if (symbol)
        {
            chars.Append(symbolChars);
        }

        StringBuilder password = new StringBuilder();
        Random random = new Random();

        for (int i = 0; i < length; i++)
        {
            password.Append(chars[random.Next(chars.Length)]);
        }

        return password.ToString();
    }
}
