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
#include <QApplication>
#include <QFont>
#include <QMargins>

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
{
    ui->setupUi(this);
    setWindowTitle("Statistiques des ventes");
    resize(1200, 800);
    
    // Load statistics
    loadSalesStatistics();
    
    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked, this, &SalesStatistique::on_refreshButton_clicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &SalesStatistique::on_exportButton_clicked);
}

void SalesStatistique::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    // Refresh statistics when window is shown
    loadSalesStatistics();
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
    
    // Sales by day of week - Create Bar Chart (one bar per day)
    ui->paymentMethodsText->clear();
    query.clear();
    
    // Use full day names for better visibility
    QStringList dayNames = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    QStringList categories;
    QString methodsText = "Ventes par jour de la semaine:\n\n";
    
    int maxSales = 0;
    
    // Initialize arrays for all 7 days (Monday=0, Tuesday=1, ..., Sunday=6)
    QList<int> salesByDay(7, 0);
    
    // Get all sales and process dates in C++ for accurate day-of-week calculation
    // This is more reliable than SQL date functions which vary by database
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
            int dayOfWeek = saleDate.dayOfWeek(); // Qt: 1=Monday, 7=Sunday
            int index = dayOfWeek - 1; // Convert to 0-6 (Monday=0, Sunday=6)
            if (index >= 0 && index < 7) {
                salesByDay[index]++;
                if (salesByDay[index] > maxSales) maxSales = salesByDay[index];
            }
            qDebug() << "Sale date:" << saleDate.toString("yyyy-MM-dd") << "Day of week:" << dayOfWeek << "Index:" << index;
        } else {
            qDebug() << "Invalid date from database:" << dateVar.toString() << "Type:" << dateVar.typeName();
        }
    }
    
    // Always create the chart, even with zero values
    {
        
        // Create individual bar sets for each day with different colors (gradient)
        QList<QColor> gradientColors;
        gradientColors << QColor(255, 0, 0)      // Red
                       << QColor(255, 127, 0)    // Orange
                       << QColor(255, 255, 0)    // Yellow
                       << QColor(127, 255, 0)    // Yellow-Green
                       << QColor(0, 255, 0)      // Green
                       << QColor(0, 255, 127)    // Green-Cyan
                       << QColor(0, 255, 255);   // Cyan
        
        // Create a single bar set with all days (simple bar chart like the example)
        QBarSet *weekBarSet = new QBarSet("Ventes");
        
        // Add data for each day to the single bar set
        for (int i = 0; i < 7; ++i) {
            QString dayName = dayNames[i];
            categories << dayName;
            *weekBarSet << salesByDay[i];
            
            methodsText += QString("%1: %2 ventes\n")
                          .arg(dayName)
                          .arg(salesByDay[i]);
        }
        
        // Use a single color for all bars (like the example)
        weekBarSet->setColor(QColor(41, 102, 148)); // Blue color
        weekBarSet->setBorderColor(QColor(41, 102, 148).darker(150));
        weekBarSet->setLabelColor(Qt::black);
        
        // Create bar series with single bar set
        QBarSeries *weekBarSeries = new QBarSeries();
        weekBarSeries->append(weekBarSet);
        
        // Set bar width to make bars wider and well-spaced (0.5 = 50% width, 50% spacing)
        // This creates more space between bars like in the example
        weekBarSeries->setBarWidth(0.5);
        
        ui->paymentMethodsText->setText(methodsText);
        
        // Create bar chart
        QChart *weekChart = new QChart();
        weekChart->addSeries(weekBarSeries);
        weekChart->setTitle("Ventes par jour de la semaine");
        weekChart->setAnimationOptions(QChart::SeriesAnimations);
        weekChart->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
        
        // Set margins to add space around the chart (more space at bottom for labels)
        weekChart->setMargins(QMargins(30, 20, 30, 60));
        
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        // Keep labels horizontal and clearly visible
        axisX->setLabelsAngle(0);
        axisX->setLabelsFont(QFont("Arial", 10, QFont::Bold));
        axisX->setLabelsColor(Qt::black);
        weekChart->addAxis(axisX, Qt::AlignBottom);
        weekBarSeries->attachAxis(axisX);
        
        QValueAxis *axisY = new QValueAxis();
        // Ensure minimum range even if maxSales is 0
        int maxRange = qMax(maxSales, 5); // At least show 0-5 range
        axisY->setRange(0, maxRange * 1.1);
        axisY->setLabelFormat("%d");
        axisY->setTickCount(6);
        weekChart->addAxis(axisY, Qt::AlignLeft);
        weekBarSeries->attachAxis(axisY);
        
        weekChart->legend()->setVisible(false);
        
        QChartView *weekChartView = new QChartView(weekChart);
        weekChartView->setRenderHint(QPainter::Antialiasing);
        weekChartView->setMinimumHeight(300);
        
        QLayout *layout = ui->paymentChartWidget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        QVBoxLayout *chartLayout = new QVBoxLayout(ui->paymentChartWidget);
        chartLayout->setContentsMargins(0, 0, 0, 0);
        chartLayout->addWidget(weekChartView);
        
        ui->paymentMethodsText->setText(methodsText);
    }
    
    // Top 5 clients - Create Bar Chart
    ui->topClientsText->clear();
    query.clear();
    sql = "SELECT c.nom, c.prenom, COUNT(v.id_vente) as count, SUM(v.prix_ttc) as total "
          "FROM vente v JOIN clients c ON v.id_client = c.id_client "
          "GROUP BY c.id_client, c.nom, c.prenom ORDER BY total DESC LIMIT 5";
    if (!query.exec(sql)) {
        qDebug() << "Error with top clients query:" << query.lastError().text();
        query.clear();
        sql = "SELECT c.NOM, c.PRENOM, COUNT(v.ID_VENTE) as count, SUM(v.PRIX_TTC) as total "
              "FROM VENTE v JOIN CLIENTS c ON v.ID_CLIENT = c.ID_CLIENT "
              "GROUP BY c.ID_CLIENT, c.NOM, c.PRENOM ORDER BY total DESC FETCH FIRST 5 ROWS ONLY";
        query.exec(sql);
    }
    
    if (query.size() > 0) {
        QString clientsText;
        QBarSet *clientsBarSet = new QBarSet("Revenu (DT)");
        QStringList clientCategories;
        int rank = 1;
        
        while (query.next()) {
            QString nom = query.value(0).toString();
            QString prenom = query.value(1).toString();
            int count = query.value(2).toInt();
            double total = query.value(3).toDouble();
            clientsText += QString("%1. %2 %3 - %4 ventes (%5 DT)\n")
                          .arg(rank)
                          .arg(nom)
                          .arg(prenom)
                          .arg(count)
                          .arg(total, 0, 'f', 2);
            *clientsBarSet << total;
            clientCategories << (nom + " " + prenom.left(1) + ".");
            rank++;
        }
        ui->topClientsText->setText(clientsText);
        
        QBarSeries *clientsBarSeries = new QBarSeries();
        clientsBarSeries->append(clientsBarSet);
        clientsBarSet->setColor(QColor(41, 102, 148));
        
        QChart *clientsChart = new QChart();
        clientsChart->addSeries(clientsBarSeries);
        clientsChart->setTitle("Top 5 clients (Revenu)");
        clientsChart->setAnimationOptions(QChart::SeriesAnimations);
        clientsChart->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
        
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(clientCategories);
        clientsChart->addAxis(axisX, Qt::AlignBottom);
        clientsBarSeries->attachAxis(axisX);
        
        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelFormat("%.0f DT");
        clientsChart->addAxis(axisY, Qt::AlignLeft);
        clientsBarSeries->attachAxis(axisY);
        
        clientsChart->legend()->setVisible(false);
        
        QChartView *clientsChartView = new QChartView(clientsChart);
        clientsChartView->setRenderHint(QPainter::Antialiasing);
        
        QLayout *layout = ui->clientsChartWidget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        QVBoxLayout *chartLayout = new QVBoxLayout(ui->clientsChartWidget);
        chartLayout->setContentsMargins(0, 0, 0, 0);
        chartLayout->addWidget(clientsChartView);
    } else {
        ui->topClientsText->setText("Aucune donnée de client disponible.");
    }
    
    // Sales status distribution
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
        
        // Create pie chart for sales status
        QPieSeries *statusPieSeries = new QPieSeries();
        if (completed > 0) {
            QPieSlice *completedSlice = statusPieSeries->append("Complétées", completed);
            completedSlice->setColor(QColor(76, 175, 80)); // Green
            completedSlice->setLabelVisible(true);
        }
        if (pending > 0) {
            QPieSlice *pendingSlice = statusPieSeries->append("En cours/Attente", pending);
            pendingSlice->setColor(QColor(255, 152, 0)); // Orange
            pendingSlice->setLabelVisible(true);
        }
        if (cancelled > 0) {
            QPieSlice *cancelledSlice = statusPieSeries->append("Annulées", cancelled);
            cancelledSlice->setColor(QColor(244, 67, 54)); // Red
            cancelledSlice->setLabelVisible(true);
        }
        
        QChart *statusChart = new QChart();
        statusChart->addSeries(statusPieSeries);
        statusChart->setTitle("Statut des ventes");
        statusChart->legend()->setAlignment(Qt::AlignBottom);
        statusChart->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
        
        QChartView *statusChartView = new QChartView(statusChart);
        statusChartView->setRenderHint(QPainter::Antialiasing);
        
        QLayout *layout = ui->statusChartWidget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        QVBoxLayout *chartLayout = new QVBoxLayout(ui->statusChartWidget);
        chartLayout->setContentsMargins(0, 0, 0, 0);
        chartLayout->addWidget(statusChartView);
    } else {
        ui->statusText->setText("Pas encore de données de vente.");
    }
}

void SalesStatistique::on_refreshButton_clicked()
{
    loadSalesStatistics();
}

void SalesStatistique::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les statistiques", 
                                                    "statistiques_ventes.txt", 
                                                    "Fichiers texte (*.txt)");
    if (fileName.isEmpty()) return;
    
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

