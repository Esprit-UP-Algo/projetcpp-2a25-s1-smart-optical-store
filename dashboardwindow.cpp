#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include "saleswindow.h"
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "promomanager.h"
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
#include <QShowEvent>

// Initialize static instance pointer
DashboardWindow* DashboardWindow::instance = nullptr;

DashboardWindow* DashboardWindow::getInstance(const QString &role, QWidget *parent)
{
    if (!instance) {
        instance = new DashboardWindow(role, parent);
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

DashboardWindow::DashboardWindow(const QString &role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow),
    currentUserRole(role),
    promoManagerOpen(false),
    todayRevenue(0.0)
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
            if (currentUserRole == "admin" || currentUserRole == "stock") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    MainWindow::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            if (currentUserRole == "admin" || currentUserRole == "vente") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    SalesWindow::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            if (currentUserRole == "admin" || currentUserRole == "employe") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    gestionemploye00::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            if (currentUserRole == "admin" || currentUserRole == "client") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    Gclient1::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            if (currentUserRole == "admin" || currentUserRole == "fournisseur") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    FournisseurWindow::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        }
        // Codes Promo button removed from dashboard - now only in SalesWindow sidebar
    }
    
    // Set role-based access control
    setRoleBasedAccess(currentUserRole);
    
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

void DashboardWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    // Refresh dashboard data every time the window is shown
    qDebug() << "🔄 Dashboard window shown, refreshing data...";
    loadDashboardData();
}

void DashboardWindow::on_logoClicked()
{
    // Already on dashboard, just refresh/raise it and reload data
    loadDashboardData();
    this->raise();
    this->activateWindow();
}

void DashboardWindow::openPromoManager()
{
    // Prevent multiple opens
    if (promoManagerOpen) {
        qDebug() << "PromoManager already open, ignoring request";
        return;
    }
    
    promoManagerOpen = true;
    qDebug() << "Opening PromoManager, promoManagerOpen set to true";
    
    // Open promo code management dialog
    PromoManager *promoManager = new PromoManager(this);
    promoManager->setAttribute(Qt::WA_DeleteOnClose, true);
    promoManager->setModal(true);
    
    // Connect to finished signal to reset flag when dialog closes
    QObject::connect(promoManager, &QDialog::finished, this, [this](int result) {
        Q_UNUSED(result);
        QTimer::singleShot(200, this, [this]() {
            promoManagerOpen = false;
            qDebug() << "PromoManager flag reset after dialog finished";
        });
    });
    
    promoManager->exec();
    // Dialog will be auto-deleted due to WA_DeleteOnClose
}

void DashboardWindow::setRoleBasedAccess(const QString &role)
{
    // Disable all navigation buttons by default
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "stock") {
                btn->setEnabled(true);
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "vente") {
                btn->setEnabled(true);
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            if (role == "admin" || role == "employe") {
                btn->setEnabled(true);
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            if (role == "admin" || role == "client") {
                btn->setEnabled(true);
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "fournisseur") {
                btn->setEnabled(true);
            } else {
                btn->setEnabled(false);
            }
        }
    }
}

void DashboardWindow::loadDashboardData()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "❌ Database not connected in dashboard";
        return;
    }
    
    qDebug() << "🔄 Loading dashboard data...";
    
    QSqlQuery query(db);
    QDate today = QDate::currentDate();
    QDate weekStart = today.addDays(-today.dayOfWeek() + 1);  // Start of week (Monday)
    QDate monthStart = QDate(today.year(), today.month(), 1);
    
    QString todayStr = today.toString("yyyy-MM-dd");
    QString weekStartStr = weekStart.toString("yyyy-MM-dd");
    QString monthStartStr = monthStart.toString("yyyy-MM-dd");
    
    // Today's Sales Count
    QStringList todaySalesQueries = {
        "SELECT COUNT(*) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(TO_DATE(:today, 'YYYY-MM-DD'))",
        "SELECT COUNT(*) FROM vente WHERE TRUNC(date_vente) = TRUNC(TO_DATE(:today, 'YYYY-MM-DD'))",
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:today, 'YYYY-MM-DD') AND DATE_VENTE < TO_DATE(:today, 'YYYY-MM-DD') + 1",
        "SELECT COUNT(*) FROM vente WHERE date_vente >= TO_DATE(:today, 'YYYY-MM-DD') AND date_vente < TO_DATE(:today, 'YYYY-MM-DD') + 1",
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE = :today",
        "SELECT COUNT(*) FROM vente WHERE date_vente = :today"
    };
    
    bool todaySalesLoaded = false;
    for (const QString &sql : todaySalesQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            ui->customersCountLabel->setText(QString::number(count));
            qDebug() << "✅ Today's Sales Count:" << count;
            todaySalesLoaded = true;
            break;
        }
    }
    if (!todaySalesLoaded) {
        qDebug() << "⚠️ Failed to load today's sales count";
        ui->customersCountLabel->setText("0");
    }
    
    // This Week Sales Count
    QStringList weekSalesQueries = {
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:weekStart, 'YYYY-MM-DD') AND DATE_VENTE <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COUNT(*) FROM vente WHERE date_vente >= TO_DATE(:weekStart, 'YYYY-MM-DD') AND date_vente <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= :weekStart AND DATE_VENTE <= :today",
        "SELECT COUNT(*) FROM vente WHERE date_vente >= :weekStart AND date_vente <= :today"
    };
    
    bool weekSalesLoaded = false;
    for (const QString &sql : weekSalesQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":weekStart", weekStartStr);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            ui->productsCountLabel->setText(QString::number(count));
            qDebug() << "✅ This Week Sales Count:" << count;
            weekSalesLoaded = true;
            break;
        }
    }
    if (!weekSalesLoaded) {
        qDebug() << "⚠️ Failed to load week sales count";
        ui->productsCountLabel->setText("0");
    }
    
    // This Month Sales Count
    QStringList monthSalesQueries = {
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:monthStart, 'YYYY-MM-DD') AND DATE_VENTE <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COUNT(*) FROM vente WHERE date_vente >= TO_DATE(:monthStart, 'YYYY-MM-DD') AND date_vente <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COUNT(*) FROM VENTE WHERE DATE_VENTE >= :monthStart AND DATE_VENTE <= :today",
        "SELECT COUNT(*) FROM vente WHERE date_vente >= :monthStart AND date_vente <= :today"
    };
    
    bool monthSalesLoaded = false;
    for (const QString &sql : monthSalesQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":monthStart", monthStartStr);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            ui->salesCountLabel->setText(QString::number(count));
            qDebug() << "✅ This Month Sales Count:" << count;
            monthSalesLoaded = true;
            break;
        }
    }
    if (!monthSalesLoaded) {
        qDebug() << "⚠️ Failed to load month sales count";
        ui->salesCountLabel->setText("0");
    }
    
    // Today's Revenue
    QStringList todayRevenueQueries = {
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(TO_DATE(:today, 'YYYY-MM-DD'))",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE TRUNC(date_vente) = TRUNC(TO_DATE(:today, 'YYYY-MM-DD'))",
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:today, 'YYYY-MM-DD') AND DATE_VENTE < TO_DATE(:today, 'YYYY-MM-DD') + 1",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE date_vente >= TO_DATE(:today, 'YYYY-MM-DD') AND date_vente < TO_DATE(:today, 'YYYY-MM-DD') + 1"
    };
    
    bool todayRevenueLoaded = false;
    for (const QString &sql : todayRevenueQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            todayRevenue = query.value(0).toDouble();  // Store in member variable
            ui->todaySalesLabel->setText(QString("%1 DT").arg(todayRevenue, 0, 'f', 2));
            qDebug() << "✅ Today's Revenue:" << todayRevenue;
            todayRevenueLoaded = true;
            
            // Check revenue threshold and notify Arduino if connected
            if (arduino && arduino->is_available()) {
                arduino->checkRevenueThreshold(todayRevenue);
            }
            break;
        }
    }
    if (!todayRevenueLoaded) {
        qDebug() << "⚠️ Failed to load today's revenue";
        ui->todaySalesLabel->setText("0.00 DT");
        todayRevenue = 0.0;
    }
    
    // This Week Revenue
    QStringList weekRevenueQueries = {
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:weekStart, 'YYYY-MM-DD') AND DATE_VENTE <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE date_vente >= TO_DATE(:weekStart, 'YYYY-MM-DD') AND date_vente <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= :weekStart AND DATE_VENTE <= :today",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE date_vente >= :weekStart AND date_vente <= :today"
    };
    
    bool weekRevenueLoaded = false;
    for (const QString &sql : weekRevenueQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":weekStart", weekStartStr);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            double revenue = query.value(0).toDouble();
            ui->todayRevenueLabel->setText(QString("%1 DT").arg(revenue, 0, 'f', 2));
            qDebug() << "✅ This Week Revenue:" << revenue;
            weekRevenueLoaded = true;
            break;
        }
    }
    if (!weekRevenueLoaded) {
        qDebug() << "⚠️ Failed to load week revenue";
        ui->todayRevenueLabel->setText("0.00 DT");
    }
    
    // This Month Revenue
    QStringList monthRevenueQueries = {
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= TO_DATE(:monthStart, 'YYYY-MM-DD') AND DATE_VENTE <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE date_vente >= TO_DATE(:monthStart, 'YYYY-MM-DD') AND date_vente <= TO_DATE(:today, 'YYYY-MM-DD')",
        "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE DATE_VENTE >= :monthStart AND DATE_VENTE <= :today",
        "SELECT COALESCE(SUM(prix_ttc), 0) FROM vente WHERE date_vente >= :monthStart AND date_vente <= :today"
    };
    
    bool monthRevenueLoaded = false;
    for (const QString &sql : monthRevenueQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":monthStart", monthStartStr);
        query.bindValue(":today", todayStr);
        if (query.exec() && query.next()) {
            double revenue = query.value(0).toDouble();
            ui->lowStockLabel->setText(QString("%1 DT").arg(revenue, 0, 'f', 2));
            qDebug() << "✅ This Month Revenue:" << revenue;
            monthRevenueLoaded = true;
            break;
        }
    }
    if (!monthRevenueLoaded) {
        qDebug() << "⚠️ Failed to load month revenue";
        ui->lowStockLabel->setText("0.00 DT");
    }
    
    // Update date/time label with time (without seconds)
    QDateTime now = QDateTime::currentDateTime();
    ui->dateTimeLabel->setText(QString("Today: %1 - %2").arg(now.toString("dddd, MMMM dd, yyyy")).arg(now.toString("hh:mm")));
    
    // Load recent sales
    loadRecentSales();
    
    qDebug() << "✅ Dashboard data loaded successfully";
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
    
    // Try multiple query formats for maximum compatibility
    QStringList recentSalesQueries = {
        // Oracle ROWNUM with lowercase
        "SELECT * FROM ("
        "SELECT v.id_vente, v.date_vente, c.nom || ' ' || c.prenom AS client, "
        "v.prix_ttc, v.mode_paiement "
        "FROM vente v "
        "LEFT JOIN clients c ON v.id_client = c.id_client "
        "ORDER BY v.date_vente DESC, v.id_vente DESC"
        ") WHERE ROWNUM <= 10",
        
        // Oracle FETCH FIRST with lowercase
        "SELECT v.id_vente, v.date_vente, c.nom || ' ' || c.prenom AS client, "
        "v.prix_ttc, v.mode_paiement "
        "FROM vente v "
        "LEFT JOIN clients c ON v.id_client = c.id_client "
        "ORDER BY v.date_vente DESC, v.id_vente DESC "
        "FETCH FIRST 10 ROWS ONLY",
        
        // Oracle ROWNUM with uppercase
        "SELECT * FROM ("
        "SELECT v.ID_VENTE, v.DATE_VENTE, c.NOM || ' ' || c.PRENOM AS CLIENT, "
        "v.PRIX_TTC, v.MODE_PAIEMENT "
        "FROM VENTE v "
        "LEFT JOIN CLIENTS c ON v.ID_CLIENT = c.ID_CLIENT "
        "ORDER BY v.DATE_VENTE DESC, v.ID_VENTE DESC"
        ") WHERE ROWNUM <= 10",
        
        // Oracle FETCH FIRST with uppercase
        "SELECT v.ID_VENTE, v.DATE_VENTE, c.NOM || ' ' || c.PRENOM AS CLIENT, "
        "v.PRIX_TTC, v.MODE_PAIEMENT "
        "FROM VENTE v "
        "LEFT JOIN CLIENTS c ON v.ID_CLIENT = c.ID_CLIENT "
        "ORDER BY v.DATE_VENTE DESC, v.ID_VENTE DESC "
        "FETCH FIRST 10 ROWS ONLY"
    };
    
    bool queryExecuted = false;
    for (const QString &sql : recentSalesQueries) {
        query.clear();
        if (query.exec(sql)) {
            queryExecuted = true;
            qDebug() << "✅ Recent sales query executed successfully";
            break;
        } else {
            qDebug() << "⚠️ Query failed:" << query.lastError().text();
        }
    }
    
    if (!queryExecuted) {
        qDebug() << "❌ All recent sales queries failed";
        return;
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
