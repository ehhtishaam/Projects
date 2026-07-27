# Basic Encryption & Decryption (Caesar Cipher)

This project implements a Caesar Cipher — a classic substitution cipher that shifts each letter of a message by a fixed number of positions in the alphabet. It demonstrates the fundamental Input → Process → Output model used in all cryptographic systems: plaintext goes in, an algorithm + key transforms it, ciphertext comes out — and the same key reverses the process.

## What It Does

- Encrypts user-provided text using a shift-based substitution cipher
- Decrypts the encrypted text back to the original message
- Displays the original, encrypted, and decrypted text side by side to verify correctness
- Validates that the shift key entered is a valid integer before proceeding

## How It Works

Each letter is converted to its ASCII value using `ord()`, shifted by the key, wrapped using modulo arithmetic so it stays within the 26-letter alphabet, and converted back to a character using `chr()`.

**Encryption formula:**
```
E(x) = (x + n) % 26
```

**Decryption formula:**
```
D(x) = (x - n) % 26
```

Where `x` is the letter's position in the alphabet (A=0 ... Z=25) and `n` is the shift key.

Uppercase and lowercase letters are handled separately since they sit at different ASCII base values (65 for 'A', 97 for 'a'). Non-alphabetic characters — spaces, numbers, punctuation — are passed through unchanged.

Decryption reuses the same function as encryption, simply negating the shift key. This works safely in Python because Python's modulo operator correctly handles negative numbers, unlike some other languages.

## Key Concepts Used

- ASCII character conversion (`ord()`, `chr()`)
- Modular arithmetic to wrap around the alphabet
- Single reusable function for both encryption and decryption
- Input validation using a `try`/`except` loop
- Edge case handling for non-letter characters

## Example

```
Enter the message to encrypt: Hello World!
Enter the shift key (an integer): 3

--- Results ---
Original Text:  Hello World!
Encrypted Text: Khoor Zruog!
Decrypted Text: Hello World!
```

## Limitations

The Caesar Cipher is a mono-alphabetic substitution cipher — it preserves the underlying letter-frequency pattern of the original text, and with only 25 possible keys, it's trivially brute-forceable. It's a foundational learning exercise, not a production-grade encryption method. Real-world confidentiality relies on modern algorithms like AES-256.
