#include "salesstatistique.h"
#include "ui_salesstatistique.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QTextEdit>
#include <QPushButton>
#include <QDate>
#include <QFile>
#include <QIODevice>
#include <QVBoxLayout>
#include <QLayout>
#include <QLayoutItem>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegend>
#include <QColor>
#include <QBrush>
#include <QPainter>
#include <QShowEvent>
#include <QCloseEvent>
#include <QApplication>
#include <QFont>
#include <QMargins>
#include <QTimer>
#include <algorithm>

// Static instance pointer
SalesStatistique* SalesStatistique::instance = nullptr;

SalesStatistique* SalesStatistique::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new SalesStatistique(parent);
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

void SalesStatistique::refreshIfOpen()
{
    if (instance && instance->isVisible()) {
        qDebug() << "🔄 Rafraîchissement automatique des statistiques...";
        instance->loadSalesStatistics();
        qDebug() << "✅ Statistiques rafraîchies";
    } else {
        qDebug() << "ℹ️ Fenêtre des statistiques non ouverte, pas de rafraîchissement nécessaire";
    }
}

// Constructor implementation
SalesStatistique::SalesStatistique(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SalesStatistique)
    , exportDialogOpen(false)
{
    ui->setupUi(this);
    setWindowTitle("Statistiques des ventes");
    resize(1200, 800);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose, false);
    
    // Ensure chart widgets have layouts
    if (!ui->paymentChartWidget->layout()) {
        ui->paymentChartWidget->setLayout(new QVBoxLayout());
    }
    if (!ui->clientsChartWidget->layout()) {
        ui->clientsChartWidget->setLayout(new QVBoxLayout());
    }
    if (!ui->statusChartWidget->layout()) {
        ui->statusChartWidget->setLayout(new QVBoxLayout());
    }
    
    // Load statistics
    loadSalesStatistics();
    
    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked, this, &SalesStatistique::on_refreshButton_clicked);
    // Manually connect export button to avoid auto-connection issues
    connect(ui->exportButton, &QPushButton::clicked, this, &SalesStatistique::exportStatistics);
}

void SalesStatistique::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    // Refresh statistics when window is shown
    loadSalesStatistics();
}

void SalesStatistique::closeEvent(QCloseEvent *event)
{
    // Prevent dialog from reopening
    event->accept();
}

SalesStatistique::~SalesStatistique()
{
    delete ui;
}

void SalesStatistique::loadSalesStatistics()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données non disponible!");
        return;
    }
    
    QSqlQuery query(db);
    
    // Total sales
    int totalSales = 0;
    QString sql = "SELECT COUNT(*) FROM vente";
    if (!query.exec(sql)) {
        qDebug() << "Error with lowercase vente:" << query.lastError().text();
        query.clear();
        sql = "SELECT COUNT(*) FROM VENTE";
        if (!query.exec(sql)) {
            qDebug() << "Error with uppercase VENTE:" << query.lastError().text();
            query.clear();
            sql = "SELECT COUNT(*) FROM Vente";
            query.exec(sql);
        }
    }
    if (query.next()) {
        totalSales = query.value(0).toInt();
        qDebug() << "Total sales found:" << totalSales;
    } else {
        qDebug() << "No result for total sales query";
    }
    ui->totalSalesLabel->setText(QString::number(totalSales));
    
    // Total revenue
    double totalRevenue = 0.0;
    query.clear();
    sql = "SELECT SUM(prix_ttc) FROM vente WHERE prix_ttc IS NOT NULL";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT SUM(PRIX_TTC) FROM VENTE WHERE PRIX_TTC IS NOT NULL";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT SUM(prix_ttc) FROM Vente WHERE prix_ttc IS NOT NULL";
            query.exec(sql);
        }
    }
    if (query.next()) {
        totalRevenue = query.value(0).toDouble();
        qDebug() << "Total revenue:" << totalRevenue;
    }
    ui->totalRevenueLabel->setText(QString::number(totalRevenue, 'f', 2) + " DT");
    
    // Average sale amount
    double avgSale = 0.0;
    query.clear();
    sql = "SELECT AVG(prix_ttc) FROM vente WHERE prix_ttc IS NOT NULL";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT AVG(PRIX_TTC) FROM VENTE WHERE PRIX_TTC IS NOT NULL";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT AVG(prix_ttc) FROM Vente WHERE prix_ttc IS NOT NULL";
            query.exec(sql);
        }
    }
    if (query.next()) {
        avgSale = query.value(0).toDouble();
        qDebug() << "Average sale:" << avgSale;
    }
    ui->avgSaleLabel->setText(QString::number(avgSale, 'f', 2) + " DT");
    
    // Sales today - Use TRUNC for Oracle date comparison (ignores time component)
    int salesToday = 0;
    query.clear();
    QDate today = QDate::currentDate();
    sql = "SELECT COUNT(*) FROM vente WHERE TRUNC(date_vente) = TRUNC(:today)";
    query.prepare(sql);
    query.bindValue(":today", today);
    if (!query.exec()) {
        query.clear();
        sql = "SELECT COUNT(*) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(SYSDATE)";
        if (!query.exec()) {
            query.clear();
            // Fallback: use string comparison
            QString todayStr = today.toString("yyyy-MM-dd");
            sql = QString("SELECT COUNT(*) FROM vente WHERE TO_CHAR(date_vente, 'YYYY-MM-DD') = '%1'").arg(todayStr);
            query.exec(sql);
        }
    }
    if (query.next()) {
        salesToday = query.value(0).toInt();
        qDebug() << "Sales today:" << salesToday << "Date:" << today.toString("yyyy-MM-dd");
    }
    ui->salesTodayLabel->setText(QString::number(salesToday));
    
    // Revenue today - Use TRUNC for Oracle date comparison
    double revenueToday = 0.0;
    query.clear();
    sql = "SELECT NVL(SUM(prix_ttc), 0) FROM vente WHERE TRUNC(date_vente) = TRUNC(:today) AND prix_ttc IS NOT NULL";
    query.prepare(sql);
    query.bindValue(":today", today);
    if (!query.exec()) {
        query.clear();
        sql = "SELECT NVL(SUM(PRIX_TTC), 0) FROM VENTE WHERE TRUNC(DATE_VENTE) = TRUNC(SYSDATE) AND PRIX_TTC IS NOT NULL";
        if (!query.exec()) {
            query.clear();
            // Fallback: use string comparison
            QString todayStr = today.toString("yyyy-MM-dd");
            sql = QString("SELECT NVL(SUM(prix_ttc), 0) FROM vente WHERE TO_CHAR(date_vente, 'YYYY-MM-DD') = '%1' AND prix_ttc IS NOT NULL").arg(todayStr);
            query.exec(sql);
        }
    }
    if (query.next()) {
        revenueToday = query.value(0).toDouble();
        qDebug() << "Revenue today:" << revenueToday;
    }
    ui->revenueTodayLabel->setText(QString::number(revenueToday, 'f', 2) + " DT");
    
    // Completed sales
    int completed = 0;
    query.clear();
    sql = "SELECT COUNT(*) FROM vente WHERE UPPER(statut_vente) = 'COMPLÉTÉE' OR UPPER(statut_vente) = 'COMPLETEE' OR UPPER(statut_vente) = 'COMPLETE'";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT COUNT(*) FROM VENTE WHERE UPPER(STATUT_VENTE) = 'COMPLÉTÉE' OR UPPER(STATUT_VENTE) = 'COMPLETEE'";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT COUNT(*) FROM vente WHERE UPPER(statut_vente) = 'COMPLÉTÉE' OR UPPER(statut_vente) = 'COMPLETEE'";
            query.exec(sql);
        }
    }
    if (query.next()) {
        completed = query.value(0).toInt();
        qDebug() << "Completed sales:" << completed;
    }
    ui->completedLabel->setText(QString::number(completed));
    
    // Sales by day of week - Create bar chart
    ui->paymentMethodsText->clear();
    query.clear();
    
    // Use full day names for better visibility
    QStringList dayNames = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    QDate startOfWeek = today.addDays(1 - today.dayOfWeek()); // Monday of current week
    QDate endOfWeek = startOfWeek.addDays(6);
    QString methodsText = QString("Ventes par jour (semaine du %1 au %2):\n\n")
                              .arg(startOfWeek.toString("dd/MM"))
                              .arg(endOfWeek.toString("dd/MM"));
    
    // Initialize arrays for all 7 days (Monday=0, Tuesday=1, ..., Sunday=6)
    QList<int> salesByDay(7, 0);
    
    // Get all sales and process dates in C++ for accurate day-of-week calculation
    query.clear();
    sql = "SELECT date_vente FROM vente";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT DATE_VENTE FROM VENTE";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT date_vente FROM Vente";
            query.exec(sql);
        }
    }
    
    // Process all sales dates to calculate day of week
    while (query.next()) {
        QVariant dateVar = query.value(0);
        QDate saleDate;
        
        if (dateVar.typeId() == QMetaType::QDate) {
            saleDate = dateVar.toDate();
        } else if (dateVar.typeId() == QMetaType::QString) {
            saleDate = QDate::fromString(dateVar.toString(), "yyyy-MM-dd");
            if (!saleDate.isValid()) {
                saleDate = QDate::fromString(dateVar.toString(), "dd/MM/yyyy");
            }
            if (!saleDate.isValid()) {
                saleDate = QDate::fromString(dateVar.toString(), "dd-MM-yyyy");
            }
        } else if (dateVar.typeId() == QMetaType::QDateTime) {
            saleDate = dateVar.toDateTime().date();
        }
        
        if (saleDate.isValid()) {
            if (saleDate < startOfWeek || saleDate > today) {
                continue; // Ignore dates outside current week or in the future
            }
            int dayOfWeek = saleDate.dayOfWeek(); // Qt: 1=Monday, 7=Sunday
            int index = dayOfWeek - 1; // Convert to 0-6 (Monday=0, Sunday=6)
            if (index >= 0 && index < 7) {
                salesByDay[index]++;
            }
        }
    }
    
    // Create bar chart for day statistics
    QBarSet *barSet = new QBarSet("Ventes");
    for (int i = 0; i < 7; ++i) {
        *barSet << salesByDay[i];
        methodsText += QString("%1: %2\n").arg(dayNames[i]).arg(salesByDay[i]);
    }
    
    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);
    barSet->setColor(QColor(41, 102, 148));
    
    QChart *dayChart = new QChart();
    dayChart->addSeries(barSeries);
    dayChart->setTitle("Ventes par jour de la semaine");
    dayChart->setAnimationOptions(QChart::SeriesAnimations);
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(dayNames);
    dayChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    int maxValue = *std::max_element(salesByDay.begin(), salesByDay.end());
    axisY->setRange(0, maxValue > 0 ? maxValue + 1 : 5);
    dayChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
    
    dayChart->legend()->setVisible(false);
    dayChart->setBackgroundBrush(QBrush(QColor(45, 45, 45))); // Dark background
    dayChart->setTitleBrush(QBrush(QColor(74, 158, 255))); // Light blue title
    dayChart->setTheme(QChart::ChartThemeDark);
    
    // Set axis colors for dark theme
    axisX->setLabelsColor(QColor(224, 224, 224));
    axisY->setLabelsColor(QColor(224, 224, 224));
    axisY->setGridLineColor(QColor(60, 60, 60));
    axisY->setLinePenColor(QColor(224, 224, 224));
    axisX->setLinePenColor(QColor(224, 224, 224));
    
    // Clear existing chart view and add new one
    QLayout *layout = ui->paymentChartWidget->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->paymentChartWidget);
        ui->paymentChartWidget->setLayout(layout);
    } else {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }
    
    QChartView *chartView = new QChartView(dayChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
    
    ui->paymentMethodsText->setText(methodsText);
    
    // Top 5 clients - Create pyramid/bar chart
    ui->topClientsText->clear();
    query.clear();
    
    QStringList clientNames;
    QList<double> clientTotals;
    QString clientsText;
    int rank = 1;
    bool hasData = false;
    
    // First, let's check if we have any sales with client IDs
    qDebug() << "=== Starting Top Clients Query ===";
    query.clear();
    sql = "SELECT COUNT(*) FROM VENTE WHERE ID_CLIENT IS NOT NULL";
    if (!query.exec(sql)) {
        qDebug() << "Uppercase COUNT query failed:" << query.lastError().text();
        query.clear();
        sql = "SELECT COUNT(*) FROM vente WHERE id_client IS NOT NULL";
        if (!query.exec(sql)) {
            qDebug() << "Lowercase COUNT query also failed:" << query.lastError().text();
        }
    }
    if (query.next()) {
        int salesWithClients = query.value(0).toInt();
        qDebug() << "Sales with client IDs:" << salesWithClients;
        if (salesWithClients == 0) {
            qDebug() << "WARNING: No sales found with client IDs!";
        }
    }
    
    // Try the simplest query first - get client IDs and totals from sales
    // Try without PRIX_TTC requirement first, just get any sales with client IDs
    query.clear();
    // First try with ROWNUM for Oracle
    sql = "SELECT * FROM ("
          "SELECT v.ID_CLIENT, COUNT(v.ID_VENTE) as count, NVL(SUM(NVL(v.PRIX_TTC, 0)), 0) as total "
          "FROM VENTE v "
          "WHERE v.ID_CLIENT IS NOT NULL "
          "GROUP BY v.ID_CLIENT "
          "ORDER BY total DESC"
          ") WHERE ROWNUM <= 5";
    
    bool querySuccess = query.exec(sql);
    if (!querySuccess) {
        qDebug() << "Error with ROWNUM query:" << query.lastError().text();
        query.clear();
        // Try FETCH FIRST
        sql = "SELECT v.ID_CLIENT, COUNT(v.ID_VENTE) as count, NVL(SUM(NVL(v.PRIX_TTC, 0)), 0) as total "
              "FROM VENTE v "
              "WHERE v.ID_CLIENT IS NOT NULL "
              "GROUP BY v.ID_CLIENT "
              "ORDER BY total DESC "
              "FETCH FIRST 5 ROWS ONLY";
        querySuccess = query.exec(sql);
        if (!querySuccess) {
            qDebug() << "Error with FETCH FIRST query:" << query.lastError().text();
            query.clear();
            // Try even simpler - just count and sum without NVL
            sql = "SELECT v.ID_CLIENT, COUNT(v.ID_VENTE) as count, SUM(v.PRIX_TTC) as total "
                  "FROM VENTE v "
                  "WHERE v.ID_CLIENT IS NOT NULL "
                  "GROUP BY v.ID_CLIENT "
                  "ORDER BY total DESC "
                  "FETCH FIRST 5 ROWS ONLY";
            querySuccess = query.exec(sql);
            if (!querySuccess) {
                qDebug() << "Error with simpler uppercase query:" << query.lastError().text();
                query.clear();
                // Try lowercase
                sql = "SELECT v.id_client, COUNT(v.id_vente) as count, COALESCE(SUM(v.prix_ttc), 0) as total "
                      "FROM vente v "
                      "WHERE v.id_client IS NOT NULL "
                      "GROUP BY v.id_client "
                      "ORDER BY total DESC "
                      "LIMIT 5";
                querySuccess = query.exec(sql);
                if (!querySuccess) {
                    qDebug() << "Error with lowercase query:" << query.lastError().text();
                }
            }
        }
    }
    
    if (querySuccess) {
        qDebug() << "Query executed successfully, processing results...";
        int rowCount = 0;
        while (query.next()) {
            rowCount++;
            int clientId = query.value(0).toInt();
            int count = query.value(1).toInt();
            double total = query.value(2).toDouble();
            
            qDebug() << "Row" << rowCount << "- Client ID:" << clientId << "Count:" << count << "Total:" << total;
            
            // Accept any total, even if 0 (might be NULL in database)
            double actualTotal = (total > 0) ? total : 0.0;
            
            // Get client name from CLIENTS table
            QSqlQuery nameQuery;
            QString fullName;
            
            // Try uppercase first
            nameQuery.prepare("SELECT NVL(NOM, 'N/A'), NVL(PRENOM, '') FROM CLIENTS WHERE ID_CLIENT = :id");
            nameQuery.bindValue(":id", clientId);
            if (!nameQuery.exec()) {
                nameQuery.clear();
                // Try lowercase
                nameQuery.prepare("SELECT COALESCE(nom, 'N/A'), COALESCE(prenom, '') FROM clients WHERE id_client = :id");
                nameQuery.bindValue(":id", clientId);
                if (!nameQuery.exec()) {
                    qDebug() << "Error getting client name for ID" << clientId << ":" << nameQuery.lastError().text();
                    fullName = QString("Client #%1").arg(clientId);
                } else if (nameQuery.next()) {
                    QString nom = nameQuery.value(0).toString().trimmed();
                    QString prenom = nameQuery.value(1).toString().trimmed();
                    if (nom == "N/A" && prenom.isEmpty()) {
                        fullName = QString("Client #%1").arg(clientId);
                    } else if (nom.isEmpty() && prenom.isEmpty()) {
                        fullName = QString("Client #%1").arg(clientId);
                    } else if (nom.isEmpty()) {
                        fullName = prenom;
                    } else if (prenom.isEmpty()) {
                        fullName = nom;
                    } else {
                        fullName = QString("%1 %2").arg(nom).arg(prenom);
                    }
                } else {
                    fullName = QString("Client #%1").arg(clientId);
                }
            } else if (nameQuery.next()) {
                QString nom = nameQuery.value(0).toString().trimmed();
                QString prenom = nameQuery.value(1).toString().trimmed();
                if (nom == "N/A" && prenom.isEmpty()) {
                    fullName = QString("Client #%1").arg(clientId);
                } else if (nom.isEmpty() && prenom.isEmpty()) {
                    fullName = QString("Client #%1").arg(clientId);
                } else if (nom.isEmpty()) {
                    fullName = prenom;
                } else if (prenom.isEmpty()) {
                    fullName = nom;
                } else {
                    fullName = QString("%1 %2").arg(nom).arg(prenom);
                }
            } else {
                fullName = QString("Client #%1").arg(clientId);
            }
            
            clientNames.append(fullName);
            clientTotals.append(actualTotal);
            clientsText += QString("%1. %2 - %3 ventes (%4 DT)\n")
                          .arg(rank)
                          .arg(fullName)
                          .arg(count)
                          .arg(actualTotal, 0, 'f', 2);
            rank++;
            hasData = true;
            qDebug() << "Added client:" << fullName << "ID:" << clientId << "Count:" << count << "Total:" << actualTotal;
        }
        qDebug() << "Total rows processed:" << rowCount << "Clients added:" << clientNames.size();
    } else {
        qDebug() << "All queries failed for top clients";
    }
    
    qDebug() << "=== Final Check ===";
    qDebug() << "hasData:" << hasData;
    qDebug() << "clientNames.size():" << clientNames.size();
    qDebug() << "clientTotals.size():" << clientTotals.size();
    
    if (hasData && clientNames.size() > 0 && clientTotals.size() > 0) {
        qDebug() << "Creating pyramid chart with" << clientNames.size() << "clients";
        ui->topClientsText->setText(clientsText);
        
        // Sort data in descending order for pyramid effect (highest first)
        QList<QPair<double, QString>> clientData;
        for (int i = 0; i < clientTotals.size(); ++i) {
            clientData.append(qMakePair(clientTotals[i], clientNames[i]));
        }
        std::sort(clientData.begin(), clientData.end(), [](const QPair<double, QString> &a, const QPair<double, QString> &b) {
            return a.first > b.first; // Descending order
        });
        
        // Extract sorted data
        QList<double> sortedTotals;
        QStringList sortedNames;
        for (const auto &pair : clientData) {
            sortedTotals.append(pair.first);
            sortedNames.append(pair.second);
            qDebug() << "Sorted client:" << pair.second << "Total:" << pair.first;
        }
        
        // Create pyramid/bar chart for top clients with gradient colors
        // Use vertical bars with proper spacing for pyramid effect
        QBarSeries *clientBarSeries = new QBarSeries();
        clientBarSeries->setBarWidth(0.8); // Make bars slightly narrower for better visibility
        
        QList<QColor> pyramidColors = {
            QColor(255, 215, 0),   // Gold for #1 (most valuable)
            QColor(255, 165, 0),   // Orange for #2
            QColor(255, 140, 0),   // Dark orange for #3
            QColor(255, 100, 0),   // Red-orange for #4
            QColor(200, 40, 0)     // Dark red for #5
        };
        
        // Create a bar set for each client with individual colors
        // Keep order: highest first (pyramid base at bottom)
        for (int i = 0; i < sortedTotals.size(); ++i) {
            QBarSet *barSet = new QBarSet(sortedNames[i]);
            *barSet << sortedTotals[i];
            if (i < pyramidColors.size()) {
                QColor barColor = pyramidColors[i];
                barSet->setColor(barColor);
            } else {
                barSet->setColor(QColor(255, 140, 0)); // Default orange
            }
            clientBarSeries->append(barSet);
            qDebug() << "Added bar set #" << (i+1) << ":" << sortedNames[i] << "Value:" << sortedTotals[i];
        }
        
        QChart *clientChart = new QChart();
        clientChart->addSeries(clientBarSeries);
        clientChart->setTitle("Top 5 Clients - Pyramide");
        clientChart->setAnimationOptions(QChart::SeriesAnimations);
        
        // Use vertical bars (categories on X-axis, values on Y-axis)
        QBarCategoryAxis *clientAxisX = new QBarCategoryAxis();
        clientAxisX->append(sortedNames);
        clientChart->addAxis(clientAxisX, Qt::AlignBottom);
        clientBarSeries->attachAxis(clientAxisX);
        
        QValueAxis *clientAxisY = new QValueAxis();
        double maxTotal = *std::max_element(sortedTotals.begin(), sortedTotals.end());
        clientAxisY->setRange(0, maxTotal > 0 ? maxTotal * 1.15 : 100);
        clientAxisY->setLabelFormat("%.0f DT");
        clientChart->addAxis(clientAxisY, Qt::AlignLeft);
        clientBarSeries->attachAxis(clientAxisY);
        
        clientChart->legend()->setVisible(false);
        clientChart->setBackgroundBrush(QBrush(QColor(45, 45, 45))); // Dark background
        clientChart->setTitleBrush(QBrush(QColor(74, 158, 255))); // Light blue title
        clientChart->setTheme(QChart::ChartThemeDark);
        
        // Set axis colors for dark theme
        clientAxisX->setLabelsColor(QColor(224, 224, 224));
        clientAxisY->setLabelsColor(QColor(224, 224, 224));
        clientAxisY->setGridLineColor(QColor(60, 60, 60));
        clientAxisY->setGridLineVisible(true);
        clientAxisY->setLinePenColor(QColor(224, 224, 224));
        clientAxisX->setLinePenColor(QColor(224, 224, 224));
        
        // Rotate X-axis labels for better readability
        clientAxisX->setLabelsAngle(-45);
        
        // Clear existing chart view and add new one
        QLayout *clientLayout = ui->clientsChartWidget->layout();
        if (!clientLayout) {
            qDebug() << "Creating new layout for clientsChartWidget";
            clientLayout = new QVBoxLayout(ui->clientsChartWidget);
            ui->clientsChartWidget->setLayout(clientLayout);
        } else {
            qDebug() << "Clearing existing layout items";
            QLayoutItem *clientItem;
            while ((clientItem = clientLayout->takeAt(0)) != nullptr) {
                if (clientItem->widget()) {
                    qDebug() << "Deleting widget from layout";
                    delete clientItem->widget();
                }
                delete clientItem;
            }
        }
        
        QChartView *clientChartView = new QChartView(clientChart);
        clientChartView->setRenderHint(QPainter::Antialiasing);
        clientChartView->setBackgroundBrush(QBrush(QColor(45, 45, 45))); // Dark background for chart view
        clientChartView->setMinimumSize(200, 150);
        clientChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        clientChartView->setVisible(true);
        clientLayout->addWidget(clientChartView);
        clientLayout->setContentsMargins(0, 0, 0, 0);
        clientLayout->setSpacing(0);
        
        // Force widget to show and update
        ui->clientsChartWidget->setVisible(true);
        ui->clientsChartWidget->show();
        ui->clientsChartWidget->update();
        ui->clientsChartWidget->repaint();
        clientChartView->show();
        clientChartView->update();
        clientChartView->repaint();
        
        qDebug() << "✓ Pyramid chart created and added with" << sortedTotals.size() << "clients";
        qDebug() << "Chart view size:" << clientChartView->size();
        qDebug() << "Widget size:" << ui->clientsChartWidget->size();
        qDebug() << "Widget visible:" << ui->clientsChartWidget->isVisible();
        qDebug() << "Chart view visible:" << clientChartView->isVisible();
    } else {
        qDebug() << "✗ No client data available for pyramid chart";
        qDebug() << "hasData:" << hasData << "clientNames.size():" << clientNames.size() << "clientTotals.size():" << clientTotals.size();
        ui->topClientsText->setText("Aucune donnée de client disponible.\n\nVérifiez que:\n- Les ventes ont des ID_CLIENT\n- Les clients existent dans la table CLIENTS");
        // Clear chart widget if no data
        QLayout *clientLayout = ui->clientsChartWidget->layout();
        if (clientLayout) {
            QLayoutItem *item;
            while ((item = clientLayout->takeAt(0)) != nullptr) {
                if (item->widget()) {
                    delete item->widget();
                }
                delete item;
            }
        }
    }
    
    // Sales status distribution - Create pie chart (circle chart)
    if (totalSales > 0) {
        int pending = 0;
        query.clear();
        sql = "SELECT COUNT(*) FROM vente WHERE UPPER(statut_vente) = 'EN COURS' OR UPPER(statut_vente) = 'EN ATTENTE' OR UPPER(statut_vente) LIKE '%ATTENTE%'";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT COUNT(*) FROM VENTE WHERE UPPER(STATUT_VENTE) = 'EN COURS' OR UPPER(STATUT_VENTE) = 'EN ATTENTE'";
            query.exec(sql);
        }
        if (query.next()) {
            pending = query.value(0).toInt();
        }
        
        int cancelled = 0;
        query.clear();
        sql = "SELECT COUNT(*) FROM vente WHERE UPPER(statut_vente) = 'ANNULÉE' OR UPPER(statut_vente) = 'ANNULEE' OR UPPER(statut_vente) LIKE '%ANNULE%'";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT COUNT(*) FROM VENTE WHERE UPPER(STATUT_VENTE) = 'ANNULÉE' OR UPPER(STATUT_VENTE) = 'ANNULEE'";
            query.exec(sql);
        }
        if (query.next()) {
            cancelled = query.value(0).toInt();
        }
        
        // Create pie chart for complete/incomplete sales
        QPieSeries *pieSeries = new QPieSeries();
        
        if (completed > 0) {
            QPieSlice *completedSlice = pieSeries->append("Complétées", completed);
            completedSlice->setColor(QColor(34, 139, 34)); // Green
            completedSlice->setLabelVisible(true);
        }
        
        if (pending > 0) {
            QPieSlice *pendingSlice = pieSeries->append("En cours", pending);
            pendingSlice->setColor(QColor(255, 165, 0)); // Orange
            pendingSlice->setLabelVisible(true);
        }
        
        if (cancelled > 0) {
            QPieSlice *cancelledSlice = pieSeries->append("Annulées", cancelled);
            cancelledSlice->setColor(QColor(220, 20, 60)); // Red
            cancelledSlice->setLabelVisible(true);
        }
        
        QChart *statusChart = new QChart();
        statusChart->addSeries(pieSeries);
        statusChart->setTitle("Statut des ventes");
        statusChart->legend()->setAlignment(Qt::AlignRight);
        statusChart->setBackgroundBrush(QBrush(QColor(45, 45, 45))); // Dark background
        statusChart->setTitleBrush(QBrush(QColor(74, 158, 255))); // Light blue title
        statusChart->setTheme(QChart::ChartThemeDark);
        
        // Set legend colors for dark theme
        statusChart->legend()->setLabelColor(QColor(224, 224, 224));
        
        // Clear existing chart view and add new one
        QLayout *statusLayout = ui->statusChartWidget->layout();
        if (!statusLayout) {
            statusLayout = new QVBoxLayout(ui->statusChartWidget);
            ui->statusChartWidget->setLayout(statusLayout);
        } else {
            QLayoutItem *statusItem;
            while ((statusItem = statusLayout->takeAt(0)) != nullptr) {
                delete statusItem->widget();
                delete statusItem;
            }
        }
        
        QChartView *statusChartView = new QChartView(statusChart);
        statusChartView->setRenderHint(QPainter::Antialiasing);
        statusLayout->addWidget(statusChartView);
        
        QString statusText = QString("Complétées: %1 (%2%)\n")
                            .arg(completed)
                            .arg((completed * 100.0) / totalSales, 0, 'f', 1);
        statusText += QString("En cours/Attente: %1 (%2%)\n")
                     .arg(pending)
                     .arg((pending * 100.0) / totalSales, 0, 'f', 1);
        statusText += QString("Annulées: %1 (%2%)")
                     .arg(cancelled)
                     .arg((cancelled * 100.0) / totalSales, 0, 'f', 1);
        ui->statusText->setText(statusText);
    } else {
        ui->statusText->setText("Pas encore de données de vente.");
    }
}

void SalesStatistique::on_refreshButton_clicked()
{
    loadSalesStatistics();
}

void SalesStatistique::exportStatistics()
{
    // Prevent multiple dialog opens
    if (exportDialogOpen) {
        return;
    }
    
    exportDialogOpen = true;
    
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les statistiques", 
                                                    "statistiques_ventes.txt", 
                                                    "Fichiers texte (*.txt)");
    
    // Reset flag after a delay
    QTimer::singleShot(500, [this]() {
        exportDialogOpen = false;
    });
    
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le fichier!");
        return;
    }
    
    QTextStream out(&file);
    out << "STATISTIQUES DES VENTES\n";
    out << "Date: " << QDate::currentDate().toString("dd/MM/yyyy") << "\n\n";
    out << "Total ventes: " << ui->totalSalesLabel->text() << "\n";
    out << "Revenu total: " << ui->totalRevenueLabel->text() << "\n";
    out << "Vente moyenne: " << ui->avgSaleLabel->text() << "\n";
    out << "Ventes aujourd'hui: " << ui->salesTodayLabel->text() << "\n";
    out << "Revenu aujourd'hui: " << ui->revenueTodayLabel->text() << "\n";
    out << "Ventes complétées: " << ui->completedLabel->text() << "\n\n";
    out << "Ventes de la semaine:\n" << ui->paymentMethodsText->toPlainText() << "\n";
    out << "Top 5 clients:\n" << ui->topClientsText->toPlainText() << "\n";
    out << "Statut des ventes:\n" << ui->statusText->toPlainText() << "\n";
    
    file.close();
    QMessageBox::information(this, "Succès", "Statistiques exportées avec succès!");
}

