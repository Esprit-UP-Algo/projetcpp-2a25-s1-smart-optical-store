
#include "dashboardwindow.h"
#include <QApplication>
#include <QFile>
#include "gestionemploye00.h"
#include "login.h"
#include "tab.h"
#include "mainwindow.h"
#include "dashboardwindow.h"
#include "Connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set application style
    a.setStyle("Fusion");
    
    // Load and apply stylesheet
    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
        styleFile.close();
    }
    
    // Start with dashboard window
    DashboardWindow dashboardWindow;
    dashboardWindow.show();
    
    return a.exec();
}

    login l;
    l.show();
    return a.exec();
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
        QMessageBox::critical(nullptr, QObject::tr("Database Connection Error"),
                              QObject::tr("Failed to connect to database.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return 1; // Exit with error
    }
}
