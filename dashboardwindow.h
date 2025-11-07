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

private slots:
    void on_dashboardButton_clicked();
    void on_salesButton_clicked();
    void on_logoutButton_clicked();
    
    // Singleton pattern
    static DashboardWindow* getInstance(QWidget *parent = nullptr);
    static DashboardWindow* instance;

private:
    Ui::DashboardWindow *ui;
};

#endif // DASHBOARDWINDOW_H
