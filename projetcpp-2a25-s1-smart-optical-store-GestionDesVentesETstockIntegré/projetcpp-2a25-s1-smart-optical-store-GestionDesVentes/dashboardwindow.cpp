#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include "saleswindow.h"
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include <QApplication>
#include "WindowManager.h"

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
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Dashboard", 1024, 768);

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
