def caesar_cipher(text, shift, mode='encrypt'):
    result = ""
    if mode == 'decrypt':
        shift = -shift
    for char in text:
        if char.isupper():
            shifted_char = chr((ord(char) - 65 + shift) % 26 + 65)
            result += shifted_char
        elif char.islower():
            shifted_char = chr((ord(char) - 97 + shift) % 26 + 97)
            result += shifted_char
        else:
            result += char
    return result

plaintext = input("Enter the message to encrypt: ")

while True:
    try:
        shift_key = int(input("Enter the shift key (an integer): "))
        break
    except ValueError:
        print("Please enter a valid whole number.")

ciphertext = caesar_cipher(plaintext, shift_key, mode='encrypt')

decrypted_text = caesar_cipher(ciphertext, shift_key, mode='decrypt')

print("--- Results ---")
print(f"Original Text:  {plaintext}")
print(f"Encrypted Text: {ciphertext}")
print(f"Decrypted Text: {decrypted_text}")
