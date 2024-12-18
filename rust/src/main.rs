use std::io::{self, Write};
use rand::{thread_rng, Rng};
use rand::distributions::Uniform;

fn get_password_length() -> Result<u8, io::Error> {
  println!("Enter password length.");
  print!("> ");
  io::stdout().flush()?;

  let mut input = String::new();

  io::stdin().read_line(&mut input)?;
  match input.trim().parse::<u8>() {
    Ok(num) => Ok(num),
    Err(_) => {
      println!("Invalid number.");
      get_password_length()
    }
  }
}

fn user_wants_uppers() -> Result<bool, io::Error> {
  println!("Use uppercase letters? (Y/n)");
  print!("> ");
  io::stdout().flush()?;

  let mut input = String::new();

  io::stdin().read_line(&mut input)?;
  if input.trim().to_lowercase() == "y" {
    Ok(true)
  } else {
    Ok(false)
  }
}

fn user_wants_lowers() -> Result<bool, io::Error> {
  println!("Use lowercase letters? (Y/n)");
  print!("> ");
  io::stdout().flush()?;

  let mut input = String::new();

  io::stdin().read_line(&mut input)?;
  if input.trim().to_lowercase() == "y" {
    Ok(true)
  } else {
    Ok(false)
  }
}

fn user_wants_numerals() -> Result<bool, io::Error> {
  println!("Use numbers? (Y/n)");
  print!("> ");
  io::stdout().flush()?;

  let mut input = String::new();

  io::stdin().read_line(&mut input)?;
  if input.trim().to_lowercase() == "y" {
    Ok(true)
  } else {
    Ok(false)
  }
}

fn user_wants_symbols() -> Result<bool, io::Error> {
  println!("Use symbols? (Y/n)");
  print!("> ");
  io::stdout().flush()?;

  let mut input = String::new();

  io::stdin().read_line(&mut input)?;
  if input.trim().to_lowercase() == "y" {
    Ok(true)
  } else {
    Ok(false)
  }
}

fn gen_password(len: u8, mut upper: bool, mut lower: bool, mut numerals: bool, mut symbols: bool) -> String {
  let mut rng = thread_rng();

  let mut chars: Vec<char> = Vec::new();

  if !upper && !lower && !numerals && !symbols {
    upper = true;
    lower = true;
    numerals = true;
    symbols = true;
  }

  if upper {
      chars.extend("ABCDEFGHIJKLMNOPQRSTUVWXYZ".chars());
  }
  if lower {
      chars.extend("abcdefghijklmnopqrstuvwxyz".chars());
  }
  if numerals {
      chars.extend("0123456789".chars());
  }
  if symbols {
      chars.extend("!@#$%^&*()_+-=[]{}|;:,.<>".chars());
  }
  
  let range = Uniform::new(0, chars.len());

  (0..len)
      .map(|_| chars[rng.sample(&range)])
      .collect()
}

fn main() {
  let password_length = match get_password_length() {
    Ok(num) => num,
    Err(err) => {
      println!("Error: {}", err);
      return;
    }
  };

  let use_uppers = match user_wants_uppers() {
    Ok(val) => val,
    Err(err) => {
      println!("Error: {}", err);
      return;
    }
  };

  let use_lowers = match user_wants_lowers() {
    Ok(val) => val,
    Err(err) => {
      println!("Error: {}", err);
      return;
    }
  };

  let use_numerals = match user_wants_numerals() {
    Ok(val) => val,
    Err(err) => {
      println!("Error: {}", err);
      return;
    }
  };

  let use_symbols = match user_wants_symbols() {
    Ok(val) => val,
    Err(err) => {
      println!("Error: {}", err);
      return;
    }
  };

  let password = gen_password(
    password_length,
    use_uppers,
    use_lowers,
    use_numerals,
    use_symbols
  );

  println!("Password: {}", password);
}
