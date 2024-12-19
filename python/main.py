import random
import string

def get_password_length() -> int:
  stdin = input("Enter password length.\n> ")
  
  try:
    return int(stdin)
  except ValueError:
    print("Invalid number.")
    return get_password_length()

def user_wants_uppers() -> bool:
  stdin = input("Use uppercase letters? (Y/n)\n> ")

  return stdin.lower() == "y" or stdin == ""

def user_wants_lowers() -> bool:
  stdin = input("Use lowercase letters? (Y/n)\n> ")

  return stdin.lower() == "y" or stdin == ""

def user_wants_numberals() -> bool:
  stdin = input("Use numbers? (Y/n)\n> ")

  return stdin.lower() == "y" or stdin == ""

def user_wants_symbols() -> bool:
  stdin = input("Use symbols? (Y/n)\n> ")

  return stdin.lower() == "y" or stdin == ""

def gen_password(length: int, upper: bool, lower: bool, numeral: bool, symbol: bool) -> str:
  
  chars = []

  if not upper and not lower and not numeral and not symbol:
    upper = lower = numeral = symbol = True
    
  print(upper, lower, numeral, symbol)

  if upper:
    chars.extend(string.ascii_uppercase)
  if lower:
    chars.extend(string.ascii_lowercase)
  if numeral:
    chars.extend(string.digits)
  if symbol:
    chars.extend("!@#$%^&*()_+-=[]{}|;:,.<>")
    
  return ''.join(random.choice(chars) for _ in range(length))
  
if __name__ == "__main__":
  password_length = get_password_length()

  use_uppers = user_wants_uppers()
  use_lowers = user_wants_lowers()
  use_numerals = user_wants_numberals()
  use_symbols = user_wants_symbols()

  password = gen_password(
    length=password_length,
    upper=use_uppers,
    lower=use_lowers,
    numeral=use_numerals,
    symbol=use_symbols
  )
  
  print(f"Password: {password}")
