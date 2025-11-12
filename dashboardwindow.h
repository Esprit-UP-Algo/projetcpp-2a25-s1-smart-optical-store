#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow();
    
    // Singleton pattern
    static DashboardWindow* getInstance(QWidget *parent = nullptr);
    static DashboardWindow* instance;

private:
    Ui::DashboardWindow *ui;
};

#endif // DASHBOARDWINDOW_H
