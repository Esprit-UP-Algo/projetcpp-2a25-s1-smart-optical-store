#!/usr/bin/env python3
"""
Simple script to generate SHA256 hashed passwords for the employee authentication system.
"""

import hashlib
import sys

def hash_password(password, salt="SmartOpticalStoreSalt"):
    """
    Hash a password with the given salt using SHA256.
    
    Args:
        password (str): The password to hash
        salt (str): The salt to use (default: "SmartOpticalStoreSalt")
    
    Returns:
        str: The hashed password as a hexadecimal string
    """
    salted_password = password + salt
    hashed = hashlib.sha256(salted_password.encode('utf-8')).hexdigest()
    return hashed

def main():
    if len(sys.argv) < 2:
        print("Usage: python hash_password.py <password> [salt]")
        print("Example: python hash_password.py mypassword")
        print("Example with custom salt: python hash_password.py mypassword MyCustomSalt")
        return
    
    password = sys.argv[1]
    salt = sys.argv[2] if len(sys.argv) > 2 else "SmartOpticalStoreSalt"
    
    hashed = hash_password(password, salt)
    print(f"Password: {password}")
    print(f"Salt: {salt}")
    print(f"Hashed: {hashed}")
    
    # Also show the SQL update statement
    print("\nSQL Update Statement:")
    print(f"UPDATE EMPLOYE SET password = '{hashed}' WHERE username = 'your_username';")

if __name__ == "__main__":
    main()