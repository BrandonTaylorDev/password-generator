import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class PasswordGenerator {

    private final Scanner scanner;
    private final Random random;

    public PasswordGenerator() {
        this.scanner = new Scanner(System.in);
        this.random = new Random();
    }

    public static void main(String[] args) {
        PasswordGenerator generator = new PasswordGenerator();

        int passwordLength = generator.getPasswordLength();
        boolean useUppers = generator.userWants("Use uppercase letters? (Y/n)");
        boolean useLowers = generator.userWants("Use lowercase letters? (Y/n)");
        boolean useNumerals = generator.userWants("Use numbers? (Y/n)");
        boolean useSymbols = generator.userWants("Use symbols? (Y/n)");

        String password = generator.generatePassword(passwordLength, useUppers, useLowers, useNumerals, useSymbols);

        System.out.println("Password: " + password);
        generator.closeScanner();
    }

    public int getPasswordLength() {
        while (true) {
            System.out.print("Enter password length.\n> ");
            String input = scanner.nextLine();

            try {
                int length = Integer.parseInt(input);
                if (length > 0) {
                    return length;
                }
                System.out.println("Please enter a positive number.");
            } catch (NumberFormatException e) {
                System.out.println("Invalid number.");
            }
        }
    }

    public boolean userWants(String prompt) {
        System.out.print(prompt + "\n> ");
        String input = scanner.nextLine().trim().toLowerCase();
        return input.equals("y");
    }

    public String generatePassword(int length, boolean upper, boolean lower, boolean numeral, boolean symbol) {
        List<Character> charPool = new ArrayList<>();

        if (!(upper || lower || numeral || symbol)) {
            upper = lower = numeral = symbol = true;
        }

        if (upper) {
            for (char c = 'A'; c <= 'Z'; c++) {
                charPool.add(c);
            }
        }
        if (lower) {
            for (char c = 'a'; c <= 'z'; c++) {
                charPool.add(c);
            }
        }
        if (numeral) {
            for (char c = '0'; c <= '9'; c++) {
                charPool.add(c);
            }
        }
        if (symbol) {
            for (char c : "!@#$%^&*()_+-=[]{}|;:,.<>".toCharArray()) {
                charPool.add(c);
            }
        }

        if (charPool.isEmpty()) {
            throw new IllegalArgumentException("No character types selected for password generation.");
        }

        StringBuilder password = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            password.append(charPool.get(random.nextInt(charPool.size())));
        }

        return password.toString();
    }

    public void closeScanner() {
        scanner.close();
    }
}
