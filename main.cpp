#include "dashboardwindow.h"

#include <QApplication>
#include <QFile>

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
