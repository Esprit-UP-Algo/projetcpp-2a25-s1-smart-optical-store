#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>
#include <QString>

class WindowManager
{
public:
    static void setupWindow(QWidget* window, const QString& title, int width = 0, int height = 0);
};

#endif // WINDOWMANAGER_H

