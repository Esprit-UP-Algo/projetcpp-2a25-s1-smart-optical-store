#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include "saleswindow.h"

#include <QMessageBox>

DashboardWindow::DashboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);
    
    // Set window properties
    setWindowTitle("Smart Optical Store - Dashboard");
    setMinimumSize(1024, 768);
    
    // Set default values for sales-focused dashboard statistics
    ui->customersCountLabel->setText("0");        // Today's Sales
    ui->productsCountLabel->setText("0");         // This Week Sales
    ui->salesCountLabel->setText("0");            // This Month Sales
    ui->todaySalesLabel->setText("$0.00");        // Today's Revenue
    ui->todayRevenueLabel->setText("$0.00");      // This Week Revenue
    ui->lowStockLabel->setText("$0.00");          // This Month Revenue
    
    // Connect signals and slots
    // Only keep Sales (Ventes) functional; other sidebar buttons are non-functional
    connect(ui->pushButton_2, &QPushButton::clicked, this, &DashboardWindow::on_salesButton_clicked);
}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}

void DashboardWindow::on_dashboardButton_clicked()
{
    // Already in dashboard, do nothing or refresh
    // Could add refresh functionality here if needed
}

void DashboardWindow::on_salesButton_clicked()
{
    // Find existing sales window or create new one
    SalesWindow *salesWindow = nullptr;
    QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    
    for (QWidget *widget : topLevelWidgets) {
        if (SalesWindow *sales = qobject_cast<SalesWindow*>(widget)) {
            salesWindow = sales;
            break;
        }
    }
    
    if (!salesWindow) {
        salesWindow = new SalesWindow();
    }
    
    salesWindow->show();
    salesWindow->raise();
    salesWindow->activateWindow();
    this->hide();
}

void DashboardWindow::on_logoutButton_clicked()
{
    // Logout/Exit disabled: prevent application from closing
    QMessageBox::information(this, "Logout", "Logout is disabled in this build.");
}
