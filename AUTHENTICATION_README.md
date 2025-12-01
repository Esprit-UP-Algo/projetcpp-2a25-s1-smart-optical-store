# Employee Authentication System Setup

This document explains how to set up and use the employee authentication system for the Smart Optical Store Management System.

## Database Setup

1. Run the `database_updates.sql` script to add authentication fields to your existing employee table:

```sql
ALTER TABLE EMPLOYE ADD COLUMN username VARCHAR2(50) UNIQUE;
ALTER TABLE EMPLOYE ADD COLUMN password VARCHAR2(255);
ALTER TABLE EMPLOYE ADD COLUMN role VARCHAR2(20) DEFAULT 'employee';
```

2. Create an index for faster username lookups:
```sql
CREATE INDEX idx_employe_username ON EMPLOYE(username);
```

3. Update existing employees with default credentials:
```sql
UPDATE EMPLOYE SET 
    username = 'admin', 
    password = '5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8', 
    role = 'admin' 
WHERE id_employe = (SELECT MIN(id_employe) FROM EMPLOYE);
```

## Password Security

The system uses SHA256 hashing with a salt for password security. The default salt is "SmartOpticalStoreSalt". For production use, you should:

1. Change the salt value in the `hashPassword` function in `employe.cpp`
2. Use a unique salt for each user
3. Consider using a more robust password hashing library like bcrypt

To generate hashed passwords, you can use:
- Python: `hashlib.sha256(("your_password" + "salt").encode()).hexdigest()`
- Online SHA256 generators (for testing only)

## Authentication Flow

1. Users enter their username and password in the login form
2. The system hashes the entered password and compares it with the stored hash
3. If authentication is successful:
   - Admin users are directed to the full dashboard
   - Regular employees are directed to the employee management section
4. Failed authentication attempts show an error message

## Adding New Employees

When adding new employees through the system:

1. Fill in all employee details including username and password
2. The system automatically hashes the password before storing it
3. Set the appropriate role ("admin" or "employee")

## Modifying Employee Accounts

When modifying employee accounts:
1. Passwords are automatically re-hashed if changed
2. All other employee details are updated normally

## Security Recommendations

1. Change the default admin password immediately after setup
2. Use strong, unique passwords for all accounts
3. Regularly update the salt value in the code
4. Consider implementing account lockout after multiple failed attempts
5. Add password complexity requirements
6. Implement session management and timeouts