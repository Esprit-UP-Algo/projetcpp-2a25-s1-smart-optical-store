#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QIcon>
#include <QDebug>
#include <QResizeEvent>
#include <QEvent>

class WindowManager
{
public:
    // Apply common window settings and add fullscreen toggle button for QMainWindow
    static void setupWindow(QMainWindow* window, const QString& title, int defaultWidth = 1200, int defaultHeight = 800)
    {
        if (!window) return;
        
        // Set window properties
        window->resize(defaultWidth, defaultHeight);
        window->setWindowTitle("Smart Optical Store - " + title);
        
        // Create fullscreen toggle button
        QPushButton* btnToggleFullscreen = new QPushButton(window);
        btnToggleFullscreen->setObjectName("btnToggleFullscreen");
        btnToggleFullscreen->setIcon(QIcon::fromTheme("view-fullscreen"));
        btnToggleFullscreen->setText("🔍");
        btnToggleFullscreen->setToolTip("Basculer en plein écran");
        btnToggleFullscreen->setFixedSize(40, 40);
        btnToggleFullscreen->setStyleSheet(
            "QPushButton {"
            "  background-color: #357fa3;"
            "  color: white;"
            "  border-radius: 20px;"
            "  font-size: 16px;"
            "  font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "  background-color: #48a4d6;"
            "}"
        );
        
        // Position in bottom-left corner
        btnToggleFullscreen->move(10, window->height() - 50);
        btnToggleFullscreen->raise();
        
        // Connect fullscreen toggle button
        QObject::connect(btnToggleFullscreen, &QPushButton::clicked, window, [window, btnToggleFullscreen]() {
            if (window->isFullScreen()) {
                window->showNormal();
                btnToggleFullscreen->setText("🔍");
                btnToggleFullscreen->setToolTip("Basculer en plein écran");
            } else {
                window->showFullScreen();
                btnToggleFullscreen->setText("⤢");
                btnToggleFullscreen->setToolTip("Quitter le plein écran");
            }
        });
        
        // Install event filter to handle resize events
        class ResizeEventFilter : public QObject {
        public:
            ResizeEventFilter(QObject* parent, QPushButton* button) : 
                QObject(parent), m_button(button) {}
                
            bool eventFilter(QObject* obj, QEvent* event) override {
                if (event->type() == QEvent::Resize) {
                    QWidget* widget = qobject_cast<QWidget*>(obj);
                    if (widget) {
                        m_button->move(10, widget->height() - 50);
                    }
                }
                return QObject::eventFilter(obj, event);
            }
            
        private:
            QPushButton* m_button;
        };
        
        window->installEventFilter(new ResizeEventFilter(window, btnToggleFullscreen));
        
        // Ensure fullscreen button stays on top after a short delay
        QTimer::singleShot(0, window, [btnToggleFullscreen]() {
            btnToggleFullscreen->raise();
        });
        
        qDebug() << "✅ Window Manager setup completed for:" << title;
    }
    
    // Overloaded version for QWidget
    static void setupWindow(QWidget* widget, const QString& title, int defaultWidth = 1200, int defaultHeight = 800)
    {
        if (!widget) return;
        
        // Set window properties
        widget->resize(defaultWidth, defaultHeight);
        widget->setWindowTitle("Smart Optical Store - " + title);
        
        // Create fullscreen toggle button
        QPushButton* btnToggleFullscreen = new QPushButton(widget);
        btnToggleFullscreen->setObjectName("btnToggleFullscreen");
        btnToggleFullscreen->setIcon(QIcon::fromTheme("view-fullscreen"));
        btnToggleFullscreen->setText("🔍");
        btnToggleFullscreen->setToolTip("Basculer en plein écran");
        btnToggleFullscreen->setFixedSize(40, 40);
        btnToggleFullscreen->setStyleSheet(
            "QPushButton {"
            "  background-color: #357fa3;"
            "  color: white;"
            "  border-radius: 20px;"
            "  font-size: 16px;"
            "  font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "  background-color: #48a4d6;"
            "}"
        );
        
        // Position in bottom-left corner
        btnToggleFullscreen->move(10, widget->height() - 50);
        btnToggleFullscreen->raise();
        
        // Connect fullscreen toggle button
        QObject::connect(btnToggleFullscreen, &QPushButton::clicked, widget, [widget, btnToggleFullscreen]() {
            if (widget->isFullScreen()) {
                widget->showNormal();
                btnToggleFullscreen->setText("🔍");
                btnToggleFullscreen->setToolTip("Basculer en plein écran");
            } else {
                widget->showFullScreen();
                btnToggleFullscreen->setText("⤢");
                btnToggleFullscreen->setToolTip("Quitter le plein écran");
            }
        });
        
        // Install event filter to handle resize events
        class ResizeEventFilter : public QObject {
        public:
            ResizeEventFilter(QObject* parent, QPushButton* button) : 
                QObject(parent), m_button(button) {}
                
            bool eventFilter(QObject* obj, QEvent* event) override {
                if (event->type() == QEvent::Resize) {
                    QWidget* widget = qobject_cast<QWidget*>(obj);
                    if (widget) {
                        m_button->move(10, widget->height() - 50);
                    }
                }
                return QObject::eventFilter(obj, event);
            }
            
        private:
            QPushButton* m_button;
        };
        
        widget->installEventFilter(new ResizeEventFilter(widget, btnToggleFullscreen));
        
        // Ensure fullscreen button stays on top after a short delay
        QTimer::singleShot(0, widget, [btnToggleFullscreen]() {
            btnToggleFullscreen->raise();
        });
        
        qDebug() << "✅ Window Manager setup completed for:" << title;
    }
};

#endif // WINDOWMANAGER_H
