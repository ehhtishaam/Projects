# Java Secure Authentication System

A desktop login/registration system (Java Swing) built to understand how authentication is actually supposed to handle passwords — hashing, breach detection, and enforced password rules — instead of storing plaintext like a beginner project would.

## Features

- **Register / Login / Logout** flow with a simple Swing UI
- **SHA-256 password hashing** — passwords are never stored or compared in plaintext
- **Breach detection** — new passwords are checked (via hash comparison) against a list of known breached/common passwords before an account can be created
- **Password strength rules** — enforced length (6–64 chars), and requires uppercase, lowercase, a digit, and a special character
- **Live strength meter** on the registration screen (Weak / Fair / Strong) as the user types
- **Change password** from the dashboard, re-validated against the same rules
- **Show/hide password** toggle on login and register fields

## How it works

1. On registration, the password is checked against `breached_passwords.txt` — both sides of the comparison are SHA-256 hashed, so raw breached passwords are never compared directly either.
2. If it's not breached, `PasswordValidator` checks it against the password policy.
3. Only if both checks pass is the password hashed and the account saved to `accounts.txt` as `username,hashedPassword`.
4. Login re-hashes the entered password and compares hashes — the plaintext password is never persisted anywhere.

## Project structure

```
Java-Secure-Authentication-System/
├── README.md
├── .gitignore
└── src/
    └── SecureAuthenticationSystem/
        ├── Main.java                  # Entry point
        ├── StartScreen.java           # Login/Register chooser
        ├── LoginScreen.java
        ├── RegisterScreen.java        # Includes live strength meter
        ├── DashboardScreen.java       # Post-login, change password
        ├── AccountManager.java        # Reads/writes accounts.txt
        ├── PasswordHasher.java        # SHA-256 hashing
        ├── PasswordValidator.java     # Password policy rules
        ├── BreachChecker.java         # Checks against breached_passwords.txt
        └── breached_passwords.txt     # Sample list of common/breached passwords
```

`accounts.txt` is generated at runtime in the project root when you register a user, and is git-ignored since it's local runtime data, not source.

## How to run

From the project root:

```bash
javac -d out src/SecureAuthenticationSystem/*.java
java -cp out SecureAuthenticationSystem.Main
```

Or open the folder as a project in IntelliJ IDEA / Eclipse and run `Main.java` directly.

**Note:** run it from the project root so `BreachChecker` can find `src/SecureAuthenticationSystem/breached_passwords.txt` via its relative path.

## Tech

- Java (Swing for UI, `java.security.MessageDigest` for hashing)
- No external dependencies — flat text files as storage, by design, to keep the focus on the auth logic itself

## Notes / possible improvements

- Currently uses plain SHA-256 for password hashing. A production system would use a slow, salted hash (bcrypt, scrypt, or Argon2) to resist brute-force and rainbow-table attacks — this project intentionally isolates the breach-check and policy-enforcement logic first.
- `accounts.txt` is plaintext CSV for simplicity; a real system would use a proper database.
