user_password = input("Enter your password: ").strip()

MIN_LENGTH = 8
GOOD_LENGTH = 12
SPECIAL_SYMBOLS = "!@#$%^&*()-_+="

breached_passwords = []
try:
    with open("breached_passwords.txt", "r") as file:
        breached_passwords = [line.strip().lower() for line in file]
except FileNotFoundError:
    print("'breached_passwords.txt' file not found, skipping that check.")

if len(user_password) < MIN_LENGTH:
    print("Password Strength: Weak (Password must be at least 8 characters long)")
elif user_password.lower() in breached_passwords:
    print("Password Strength: Weak (This is a highly common/leaked password)")
else:
    has_lower = any(char.islower() for char in user_password)
    has_upper = any(char.isupper() for char in user_password)
    has_digit = any(char.isdigit() for char in user_password)
    has_symbol = any(char in SPECIAL_SYMBOLS for char in user_password)

    length_bonus = 1 if len(user_password) >= GOOD_LENGTH else 0

    total_score = has_lower + has_upper + has_digit + has_symbol + length_bonus

    if total_score <= 2:
        strength = "Weak"
    elif total_score in (3, 4):
        strength = "Medium"
    else:
        strength = "Strong"

    print(f"Password Strength: {strength}")
