#include "gestionemploye00.h"
#include "login.h"
#include "tab.h"
#include "mainwindow.h"
#include "dashboardwindow.h"
#include "Connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();
    
    if(test)
    {
        // Start directly with login window without showing the connection message
        login loginWindow;
        loginWindow.show();
        return a.exec();
    }
    else
    {
        // Get the actual database error for better debugging
        QSqlDatabase db = QSqlDatabase::database();
        QSqlError error = db.lastError();
        QString errorMsg = QObject::tr("Failed to connect to database.\n\n");
        
        if (error.isValid()) {
            errorMsg += QObject::tr("Error: %1\n").arg(error.text());
            if (!error.driverText().isEmpty()) {
                errorMsg += QObject::tr("Driver Error: %1\n").arg(error.driverText());
            }
            if (!error.databaseText().isEmpty()) {
                errorMsg += QObject::tr("Database Error: %1\n").arg(error.databaseText());
            }
        } else {
            errorMsg += QObject::tr("Please check:\n");
            errorMsg += QObject::tr("1. ODBC driver is installed\n");
            errorMsg += QObject::tr("2. DSN 'project' is configured in ODBC Data Sources\n");
            errorMsg += QObject::tr("3. Database server is running\n");
            errorMsg += QObject::tr("4. Credentials are correct\n");
        }
        
        errorMsg += QObject::tr("\nCheck the console output for detailed error information.");
        
        QMessageBox::critical(nullptr, QObject::tr("Database Connection Error"),
                              errorMsg, QMessageBox::Cancel);
        return 1; // Exit with error
    }
}
