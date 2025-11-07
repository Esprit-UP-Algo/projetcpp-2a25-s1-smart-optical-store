#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include "saleswindow.h"


#include <QMessageBox>

#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include <QApplication>

// Initialize static instance pointer
DashboardWindow* DashboardWindow::instance = nullptr;

DashboardWindow* DashboardWindow::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new DashboardWindow(parent);
        instance->setAttribute(Qt::WA_DeleteOnClose);
        QObject::connect(instance, &QObject::destroyed, []() {
            instance = nullptr;
        });
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}

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
    setWindowTitle("Smart Optical Store - Dashboard");
    setMinimumSize(1024, 768);

    ui->customersCountLabel->setText("0");
    ui->productsCountLabel->setText("0");
    ui->salesCountLabel->setText("0");
    ui->todaySalesLabel->setText("$0.00");
    ui->todayRevenueLabel->setText("$0.00");
    ui->lowStockLabel->setText("$0.00");

    // Wire tableau de bord buttons by visible text to be resilient to object names
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                MainWindow::getInstance();
                this->close();
            });
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                SalesWindow::getInstance();
                this->close();
            });
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                gestionemploye00::getInstance();
                this->close();
            });
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                Gclient1::getInstance();
                this->close();
            });
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                FournisseurWindow::getInstance();
                this->close();
            });
        }
    }
}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}
