#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include <QEvent>

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

private slots:
    void on_logoClicked();  // Logo click -> Refresh dashboard

private:
    Ui::DashboardWindow *ui;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void loadDashboardData();  // Load all dashboard statistics
    void loadRecentSales();     // Load recent sales table
};

#endif // DASHBOARDWINDOW_H
