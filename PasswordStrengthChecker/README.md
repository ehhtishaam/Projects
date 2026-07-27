# Password Strength Checker

A terminal-based password validation utility built to analyze password complexity, structural entropy, and cross-reference against known credential leaks.

## Features
- **Fail-Fast Baseline Checks:** Rejects passwords that are under 8 characters or found in a known leaked credentials database (`breached_passwords.txt`).
- **File Handling Integration:** Parses external threat-intelligence lists safely with custom fallback exception management.
- **Optimized Pythonic Analysis:** Employs `any()` generator expressions for fast, C-optimized string tracking.
- **Weighted Multi-Vector Scoring:** Dynamically grades character variations (case distribution, digits, symbols) alongside a length bonus.
