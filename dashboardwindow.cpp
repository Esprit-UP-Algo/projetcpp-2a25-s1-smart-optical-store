#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include "saleswindow.h"
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "arduino.h"
#include <QApplication>
#include "WindowManager.h"
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QTimer>

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
    ui->todaySalesLabel->setText("0.00 DT");
    ui->todayRevenueLabel->setText("0.00 DT");
    ui->lowStockLabel->setText("0.00 DT");
    
    // Make logo clickable (refresh/raise dashboard)
    if (ui->topRightLogoLabel) {
        ui->topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        ui->topRightLogoLabel->installEventFilter(this);
        ui->topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }

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
    
    // Load dashboard data on startup
    loadDashboardData();
    
    // Initialize Arduino (background only, no UI)
    arduino = new Arduino(this);
    
    // Try to auto-connect to Arduino on startup
    qDebug() << "========================================";
    qDebug() << "[DASHBOARD] Auto-connecting to Arduino on startup...";
    qDebug() << "========================================";
    int result = arduino->connect_arduino();
    if (result == 0) {
        qDebug() << "[DASHBOARD] ✓ Arduino auto-connected successfully on port:" << arduino->getarduino_port_name();
        qDebug() << "[DASHBOARD] Status:" << arduino->get_connection_status();
        qDebug() << "========================================";
    } else {
        qDebug() << "[DASHBOARD] ✗ Arduino auto-connection failed";
        qDebug() << "[DASHBOARD] Status:" << arduino->get_connection_status();
        qDebug() << "========================================";
    }
}

DashboardWindow::~DashboardWindow()
{
    if (arduino) {
        qDebug() << "[DASHBOARD] Closing Arduino connection...";
        arduino->close_arduino();
    }
    delete ui;
}

bool DashboardWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->topRightLogoLabel && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            on_logoClicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void DashboardWindow::on_logoClicked()
{
    // Already on dashboard, just refresh/raise it and reload data
    loadDashboardData();
    this->raise();
    this->activateWindow();
}

void DashboardWindow::loadDashboardData()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Database not connected in dashboard";
        return;
    }
    
    QSqlQuery query(db);
    QDate today = QDate::currentDate();
    QDate weekStart = today.addDays(-today.dayOfWeek() + 1);  // Start of week (Monday)
    QDate monthStart = QDate(today.year(), today.month(), 1);
    
    // Today's Sales Count
    QString sql = "SELECT COUNT(*) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(:today)";
    query.prepare(sql);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        ui->customersCountLabel->setText(QString::number(query.value(0).toInt()));
    }
    
    // This Week Sales Count
    sql = "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= :weekStart AND DATE_VENTE <= :today";
    query.prepare(sql);
    query.bindValue(":weekStart", weekStart);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        ui->productsCountLabel->setText(QString::number(query.value(0).toInt()));
    }
    
    // This Month Sales Count
    sql = "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= :monthStart AND DATE_VENTE <= :today";
    query.prepare(sql);
    query.bindValue(":monthStart", monthStart);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        ui->salesCountLabel->setText(QString::number(query.value(0).toInt()));
    }
    
    // Today's Revenue
    sql = "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(:today)";
    query.prepare(sql);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        double revenue = query.value(0).toDouble();
        ui->todaySalesLabel->setText(QString("%1 DT").arg(revenue, 0, 'f', 2));
    }
    
    // This Week Revenue
    sql = "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= :weekStart AND DATE_VENTE <= :today";
    query.prepare(sql);
    query.bindValue(":weekStart", weekStart);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        double revenue = query.value(0).toDouble();
        ui->todayRevenueLabel->setText(QString("%1 DT").arg(revenue, 0, 'f', 2));
    }
    
    // This Month Revenue
    sql = "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= :monthStart AND DATE_VENTE <= :today";
    query.prepare(sql);
    query.bindValue(":monthStart", monthStart);
    query.bindValue(":today", today);
    if (query.exec() && query.next()) {
        double revenue = query.value(0).toDouble();
        ui->lowStockLabel->setText(QString("%1 DT").arg(revenue, 0, 'f', 2));
    }
    
    // Update date/time label with time (without seconds)
    QDateTime now = QDateTime::currentDateTime();
    ui->dateTimeLabel->setText(QString("Today: %1 - %2").arg(now.toString("dddd, MMMM dd, yyyy")).arg(now.toString("hh:mm")));
    
    // Load recent sales
    loadRecentSales();
}

void DashboardWindow::loadRecentSales()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not connected in loadRecentSales()";
        return;
    }
    
    ui->recentSalesTable->setRowCount(0);
    
    QSqlQuery query(db);
    // Try Oracle ROWNUM syntax first (for older Oracle versions)
    QString sql = "SELECT * FROM ("
                  "SELECT v.id_vente, v.date_vente, c.nom || ' ' || c.prenom AS client, "
                  "v.prix_ttc, v.mode_paiement "
                  "FROM vente v "
                  "LEFT JOIN clients c ON v.id_client = c.id_client "
                  "ORDER BY v.date_vente DESC, v.id_vente DESC"
                  ") WHERE ROWNUM <= 10";
    
    if (!query.exec(sql)) {
        qDebug() << "❌ Error with ROWNUM query:" << query.lastError().text();
        qDebug() << "Trying FETCH FIRST syntax...";
        
        // Try FETCH FIRST syntax (for Oracle 12c+)
        query.clear();
        sql = "SELECT v.id_vente, v.date_vente, c.nom || ' ' || c.prenom AS client, "
              "v.prix_ttc, v.mode_paiement "
              "FROM vente v "
              "LEFT JOIN clients c ON v.id_client = c.id_client "
              "ORDER BY v.date_vente DESC, v.id_vente DESC "
              "FETCH FIRST 10 ROWS ONLY";
        
        if (!query.exec(sql)) {
            qDebug() << "❌ Error with FETCH FIRST:" << query.lastError().text();
            qDebug() << "Database error:" << query.lastError().databaseText();
            qDebug() << "Driver error:" << query.lastError().driverText();
            
            // Try with uppercase table names as final fallback
            query.clear();
            sql = "SELECT * FROM ("
                  "SELECT v.ID_VENTE, v.DATE_VENTE, c.NOM || ' ' || c.PRENOM AS CLIENT, "
                  "v.PRIX_TTC, v.MODE_PAIEMENT "
                  "FROM VENTE v "
                  "LEFT JOIN CLIENTS c ON v.ID_CLIENT = c.ID_CLIENT "
                  "ORDER BY v.DATE_VENTE DESC, v.ID_VENTE DESC"
                  ") WHERE ROWNUM <= 10";
            if (!query.exec(sql)) {
                qDebug() << "❌ Error with uppercase ROWNUM query:" << query.lastError().text();
                return;
            }
        }
    }
    
    int row = 0;
    int salesCount = 0;
    
    while (query.next()) {
        ui->recentSalesTable->insertRow(row);
        
        // Sale ID
        ui->recentSalesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        
        // Date with time (without seconds)
        QDateTime dateTime = query.value(1).toDateTime();
        if (dateTime.isValid()) {
            ui->recentSalesTable->setItem(row, 1, new QTableWidgetItem(dateTime.toString("yyyy-MM-dd hh:mm")));
        } else {
            QDate date = query.value(1).toDate();
            if (date.isValid()) {
                ui->recentSalesTable->setItem(row, 1, new QTableWidgetItem(date.toString("yyyy-MM-dd")));
            } else {
                ui->recentSalesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            }
        }
        
        // Customer name (handle NULL)
        QString customerName = query.value(2).toString();
        if (customerName.isEmpty() || customerName.trimmed().isEmpty()) {
            customerName = "N/A";
        }
        ui->recentSalesTable->setItem(row, 2, new QTableWidgetItem(customerName));
        
        // Amount
        double amount = query.value(3).toDouble();
        ui->recentSalesTable->setItem(row, 3, new QTableWidgetItem(QString("%1 DT").arg(amount, 0, 'f', 2)));
        
        // Payment Method (handle NULL)
        QString paymentMethod = query.value(4).toString();
        if (paymentMethod.isEmpty()) {
            paymentMethod = "N/A";
        }
        ui->recentSalesTable->setItem(row, 4, new QTableWidgetItem(paymentMethod));
        
        row++;
        salesCount++;
    }
    
    qDebug() << "✅ Loaded" << salesCount << "recent sales into dashboard table";
}
