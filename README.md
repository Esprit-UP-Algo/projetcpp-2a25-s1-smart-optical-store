# Smart Optical Store Management System

A comprehensive management system for optical stores built with Qt/C++.

## Features

- Employee management with authentication
- Product inventory management
- Customer relationship management
- Sales processing
- Supplier management
- Dashboard with analytics
- Prescription tracking

## Authentication System

This system now includes a full employee authentication system:

- Username/password authentication
- Password hashing with SHA256
- Role-based access control (admin/employee)
- Secure password storage

### Setup

1. Run the database update script: `database_updates.sql`
2. Use the default admin account (username: admin, password: password) or create your own
3. Change the default password immediately for security

### Password Management

Use the provided `hash_password.py` script to generate hashed passwords for manual database updates.

## Prerequisites

- Qt 6.7.3 or later
- C++17 compatible compiler
- Qt Widgets, SQL, SerialPort modules
- Oracle, MySQL, or SQLite database

## Building

### Using CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
make
```

### Using qmake

```bash
qmake projectqtttt.pro
make
```

## Database Configuration

1. Set up your database connection in `Connection.cpp`
2. Update the ODBC connection details:
   - Database name
   - Username
   - Password

## Usage

1. Start the application
2. Log in with employee credentials
3. Access features based on your role:
   - Admin: Full system access
   - Employee: Limited access based on permissions

## Security Notes

- Always change default passwords
- Use strong, unique passwords
- Regularly update the system
- Backup your database regularly

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.