#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include <QEvent>

namespace Ui {
class DashboardWindow;
}

class Arduino;

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWindow(const QString &role = "admin", QWidget *parent = nullptr);
    ~DashboardWindow();


    static DashboardWindow* getInstance(const QString &role = "admin", QWidget *parent = nullptr);

    static DashboardWindow* instance;

    void setRole(const QString &role);


private slots:
    void on_logoClicked();  // Logo click -> Refresh dashboard
    void on_logoutButton_clicked();  // Logout button

private:
    Ui::DashboardWindow *ui;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void loadDashboardData();  // Load all dashboard statistics
    void loadRecentSales();     // Load recent sales table
    Arduino *arduino;
    QString currentUserRole;
    //void setRoleBasedAccess(const QString &role);           // Arduino connection object (background only)
};

#endif // DASHBOARDWINDOW_H
