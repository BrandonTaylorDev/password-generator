const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function getPasswordLength() {
  return new Promise((resolve) => {
    rl.question("Enter password length.\n> ", (input) => {
      const length = parseInt(input, 10);
      if (isNaN(length)) {
        console.log("Invalid number.");
        resolve(getPasswordLength());
      } else {
        resolve(length);
      }
    });
  });
}

function userWantsUppers() {
  return new Promise((resolve) => {
    rl.question("Use uppercase letters? (Y/n)\n> ", (input) => {
      resolve(input.trim().toLowerCase() === "y");
    });
  });
}

function userWantsLowers() {
  return new Promise((resolve) => {
    rl.question("Use lowercase letters? (Y/n)\n> ", (input) => {
      resolve(input.trim().toLowerCase() === "y");
    });
  });
}

function userWantsNumerals() {
  return new Promise((resolve) => {
    rl.question("Use numbers? (Y/n)\n> ", (input) => {
      resolve(input.trim().toLowerCase() === "y");
    });
  });
}

function userWantsSymbols() {
  return new Promise((resolve) => {
    rl.question("Use symbols? (Y/n)\n> ", (input) => {
      resolve(input.trim().toLowerCase() === "y");
    });
  });
}

function genPassword(length, upper, lower, numeral, symbol) {
  let chars = "";

  if (!upper && !lower && !numeral && !symbol) {
    upper = lower = numeral = symbol = true;
  }

  if (upper) chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (lower) chars += "abcdefghijklmnopqrstuvwxyz";
  if (numeral) chars += "0123456789";
  if (symbol) chars += "!@#$%^&*()_+-=[]{}|;:,.<>";

  let password = "";
  for (let i = 0; i < length; i++) {
    password += chars.charAt(Math.floor(Math.random() * chars.length));
  }

  return password;
}

(async function main() {
  const passwordLength = await getPasswordLength();
  const useUppers = await userWantsUppers();
  const useLowers = await userWantsLowers();
  const useNumerals = await userWantsNumerals();
  const useSymbols = await userWantsSymbols();

  const password = genPassword(passwordLength, useUppers, useLowers, useNumerals, useSymbols);

  console.log(`Password: ${password}`);
  rl.close();
})();
