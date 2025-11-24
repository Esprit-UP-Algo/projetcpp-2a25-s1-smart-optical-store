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
    
    // Singleton pattern
    static DashboardWindow* getInstance(const QString &role = "admin", QWidget *parent = nullptr);
    static DashboardWindow* instance;

private slots:
    void on_logoClicked();  // Logo click -> Refresh dashboard
    void openPromoManager();  // Promo codes management (renamed to avoid auto-connection)

private:
    Ui::DashboardWindow *ui;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void loadDashboardData();  // Load all dashboard statistics
    void loadRecentSales();     // Load recent sales table
    Arduino *arduino;
    QString currentUserRole;
    void setRoleBasedAccess(const QString &role);           // Arduino connection object (background only)
    bool promoManagerOpen;  // Guard to prevent multiple opens
};

#endif // DASHBOARDWINDOW_H
