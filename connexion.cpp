/**
 * @file connexion.cpp
 * @brief Implementation of database connection class
 */

#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Constructor
 * @details Initializes the connection object
 */
Connexion::Connexion() {}

/**
 * @brief Establishes connection to Oracle database
 * @return true if connection successful, false otherwise
 *
 * @todo TODO: Add error logging for connection failures
 * @todo TODO: Consider moving database credentials to configuration file
 * @todo TODO: Add connection retry mechanism
 * @todo TODO: Implement connection pooling for better performance
 */
bool Connexion::connect()
{
    bool test = false;

    // Add ODBC database driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Configure database connection parameters
    db.setDatabaseName("ousema");
    db.setUserName("smartoptical");
    db.setPassword("1234");

    // Attempt to open the connection
    if (db.open()) {
        test = true;
        qDebug() << "Database connection successful: Connected to Oracle database";
    } else {
        // Log connection error
        QSqlError error = db.lastError();
        qDebug() << "Database connection failed:" << error.text();
        qDebug() << "Error code:" << error.nativeErrorCode();
    }

    return test;
}

/**
 * @brief Closes the database connection
 * @details Removes the default database connection
 */
void Connexion::closeConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed";
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}


