#include "WindowManager.h"
#include <QWidget>
#include <QString>

void WindowManager::setupWindow(QWidget* window, const QString& title, int width, int height)
{
    if (!window) return;
    
    window->setWindowTitle(title);
    
    if (width > 0 && height > 0) {
        window->resize(width, height);
    }
}

