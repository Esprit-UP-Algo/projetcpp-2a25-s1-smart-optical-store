/**
 * @file connexion.h
 * @brief Database connection class for Oracle database
 * @details Handles connection to Oracle database using ODBC driver
 */

#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlError>

/**
 * @class Connexion
 * @brief Manages database connection to Oracle database
 * @details Uses ODBC driver to connect to Oracle database named "DS_SmartCity" 
 */
class Connexion
{
public:
    /**
     * @brief Default constructor
     */
    Connexion();

    /**
     * @brief Establishes connection to the database
     * @return true if connection successful, false otherwise
     * @details Connects to Oracle database using ODBC with:
     *          - Database name: DS_SmartCity
     *          - Username: SmartCity
     *          - Password: 0000
     */
    bool connect();

    /**
     * @brief Closes the database connection
     * @details Removes the database connection from Qt's database connections
     */
    static void closeConnection();

private:
    QSqlDatabase db; ///< Database connection object
};

#endif // CONNEXION_H
