#include "statistique.h"
#include "ui_statistique.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QTextEdit>
#include <QDate>
#include <QFile>
#include <QVBoxLayout>
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
#include <QLayout>
#include <QLayoutItem>

Statistique::Statistique(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Statistique)
{
    ui->setupUi(this);
    setWindowTitle("Statistiques des employés");
    resize(1000, 700);
    
    // Load statistics
    loadEmployeeStatistics();
    
    // Connect refresh button
    connect(ui->refreshButton, &QPushButton::clicked, this, &Statistique::on_refreshButton_clicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &Statistique::on_exportButton_clicked);
}

Statistique::~Statistique()
{
    delete ui;
}

void Statistique::loadEmployeeStatistics()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données non disponible!");
        return;
    }
    
    QSqlQuery query(db);
    
    // Total employees
    int totalEmployees = 0;
    QString sql = "SELECT COUNT(*) FROM employe";
    if (!query.exec(sql)) {
        qDebug() << "Error with lowercase employe:" << query.lastError().text();
        query.clear();
        sql = "SELECT COUNT(*) FROM EMPLOYE";
        if (!query.exec(sql)) {
            qDebug() << "Error with uppercase EMPLOYE:" << query.lastError().text();
            query.clear();
            sql = "SELECT COUNT(*) FROM Employe";
            if (!query.exec(sql)) {
                qDebug() << "Error with mixed case Employe:" << query.lastError().text();
                query.clear();
                sql = "SELECT COUNT(*) FROM \"Employe\"";
                query.exec(sql);
            }
        }
    }
    if (query.next()) {
        totalEmployees = query.value(0).toInt();
        qDebug() << "Total employees found:" << totalEmployees;
    } else {
        qDebug() << "No result for total employees query";
    }
    ui->totalEmployeesLabel->setText(QString::number(totalEmployees));
    
    // Average salary
    double avgSalary = 0.0;
    query.clear();
    sql = "SELECT AVG(salaire) FROM employe WHERE salaire IS NOT NULL";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT AVG(SALAIRE) FROM EMPLOYE WHERE SALAIRE IS NOT NULL";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT AVG(Salaire) FROM Employe WHERE Salaire IS NOT NULL";
            if (!query.exec(sql)) {
                query.clear();
                sql = "SELECT AVG(\"Salaire\") FROM \"Employe\" WHERE \"Salaire\" IS NOT NULL";
                query.exec(sql);
            }
        }
    }
    if (query.next()) {
        avgSalary = query.value(0).toDouble();
        qDebug() << "Average salary:" << avgSalary;
    }
    ui->avgSalaryLabel->setText(QString::number(avgSalary, 'f', 2) + " DT");
    
    // Available employees
    int available = 0;
    query.clear();
    sql = "SELECT COUNT(*) FROM employe WHERE UPPER(dispo) = 'O'";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(DISPO) = 'O'";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT COUNT(*) FROM Employe WHERE UPPER(Dispo) = 'O'";
            if (!query.exec(sql)) {
                query.clear();
                sql = "SELECT COUNT(*) FROM \"Employe\" WHERE UPPER(\"Dispo\") = 'O'";
                query.exec(sql);
            }
        }
    }
    if (query.next()) {
        available = query.value(0).toInt();
        qDebug() << "Available employees:" << available;
    }
    ui->availableLabel->setText(QString::number(available));
    
    // Unavailable employees
    int unavailable = 0;
    query.clear();
    sql = "SELECT COUNT(*) FROM employe WHERE UPPER(dispo) = 'N'";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(DISPO) = 'N'";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT COUNT(*) FROM Employe WHERE UPPER(Dispo) = 'N'";
            if (!query.exec(sql)) {
                query.clear();
                sql = "SELECT COUNT(*) FROM \"Employe\" WHERE UPPER(\"Dispo\") = 'N'";
                query.exec(sql);
            }
        }
    }
    if (query.next()) {
        unavailable = query.value(0).toInt();
        qDebug() << "Unavailable employees:" << unavailable;
    }
    ui->unavailableLabel->setText(QString::number(unavailable));
    
    // Top 5 positions
    ui->topPositionsText->clear();
    query.clear();
    sql = "SELECT poste, COUNT(*) as count FROM employe GROUP BY poste ORDER BY count DESC LIMIT 5";
    if (!query.exec(sql)) {
        qDebug() << "Error with lowercase poste:" << query.lastError().text();
        query.clear();
        sql = "SELECT POSTE, COUNT(*) as count FROM EMPLOYE GROUP BY POSTE ORDER BY count DESC FETCH FIRST 5 ROWS ONLY";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT Poste, COUNT(*) as count FROM Employe GROUP BY Poste ORDER BY count DESC LIMIT 5";
            if (!query.exec(sql)) {
                query.clear();
                sql = "SELECT \"Poste\", COUNT(*) as count FROM \"Employe\" GROUP BY \"Poste\" ORDER BY count DESC LIMIT 5";
                query.exec(sql);
            }
        }
    }
    
    if (query.size() > 0) {
        QString positionsText;
        int rank = 1;
        while (query.next()) {
            QString poste = query.value(0).toString();
            int count = query.value(1).toInt();
            positionsText += QString("%1. %2 (%3 employés)\n").arg(rank).arg(poste).arg(count);
            rank++;
        }
        ui->topPositionsText->setText(positionsText);
    } else {
        ui->topPositionsText->setText("Aucune donnée de poste disponible.");
    }
    
    // Availability distribution - Create Pie Chart
    if (totalEmployees > 0) {
        double availablePercent = (available * 100.0) / totalEmployees;
        double unavailablePercent = (unavailable * 100.0) / totalEmployees;
        QString distText = QString("Disponibles: %1% (%2 employés)\n")
                          .arg(availablePercent, 0, 'f', 1)
                          .arg(available);
        distText += QString("Indisponibles: %1% (%2 employés)")
                   .arg(unavailablePercent, 0, 'f', 1)
                   .arg(unavailable);
        ui->availabilityText->setText(distText);
        
        // Create pie chart for availability
        QPieSeries *pieSeries = new QPieSeries();
        if (available > 0) {
            QPieSlice *availableSlice = pieSeries->append("Disponibles", available);
            availableSlice->setColor(QColor(76, 175, 80)); // Green
            availableSlice->setLabelVisible(true);
        }
        if (unavailable > 0) {
            QPieSlice *unavailableSlice = pieSeries->append("Indisponibles", unavailable);
            unavailableSlice->setColor(QColor(244, 67, 54)); // Red
            unavailableSlice->setLabelVisible(true);
        }
        
        QChart *chart = new QChart();
        chart->addSeries(pieSeries);
        chart->setTitle("Répartition de la disponibilité");
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
        
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        
        // Clear previous layout and add chart
        QLayout *layout = ui->availabilityChartWidget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        QVBoxLayout *chartLayout = new QVBoxLayout(ui->availabilityChartWidget);
        chartLayout->setContentsMargins(0, 0, 0, 0);
        chartLayout->addWidget(chartView);
    } else {
        ui->availabilityText->setText("Pas encore de données de disponibilité.");
    }
    
    // Create bar chart for top positions
    query.clear();
    sql = "SELECT poste, COUNT(*) as count FROM employe GROUP BY poste ORDER BY count DESC LIMIT 5";
    if (!query.exec(sql)) {
        query.clear();
        sql = "SELECT POSTE, COUNT(*) as count FROM EMPLOYE GROUP BY POSTE ORDER BY count DESC FETCH FIRST 5 ROWS ONLY";
        if (!query.exec(sql)) {
            query.clear();
            sql = "SELECT Poste, COUNT(*) as count FROM Employe GROUP BY Poste ORDER BY count DESC LIMIT 5";
            if (!query.exec(sql)) {
                query.clear();
                sql = "SELECT \"Poste\", COUNT(*) as count FROM \"Employe\" GROUP BY \"Poste\" ORDER BY count DESC LIMIT 5";
                query.exec(sql);
            }
        }
    }
    
    if (query.size() > 0) {
        QBarSet *barSet = new QBarSet("Nombre d'employés");
        QStringList categories;
        
        while (query.next()) {
            QString poste = query.value(0).toString();
            int count = query.value(1).toInt();
            *barSet << count;
            categories << poste;
        }
        
        QBarSeries *barSeries = new QBarSeries();
        barSeries->append(barSet);
        barSet->setColor(QColor(41, 102, 148));
        
        QChart *barChart = new QChart();
        barChart->addSeries(barSeries);
        barChart->setTitle("Top 5 des postes");
        barChart->setAnimationOptions(QChart::SeriesAnimations);
        barChart->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
        
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        barChart->addAxis(axisX, Qt::AlignBottom);
        barSeries->attachAxis(axisX);
        
        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelFormat("%d");
        barChart->addAxis(axisY, Qt::AlignLeft);
        barSeries->attachAxis(axisY);
        
        barChart->legend()->setVisible(false);
        
        QChartView *barChartView = new QChartView(barChart);
        barChartView->setRenderHint(QPainter::Antialiasing);
        
        // Clear previous layout and add chart
        QLayout *layout = ui->positionsChartWidget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        QVBoxLayout *chartLayout = new QVBoxLayout(ui->positionsChartWidget);
        chartLayout->setContentsMargins(0, 0, 0, 0);
        chartLayout->addWidget(barChartView);
    }
}

void Statistique::on_refreshButton_clicked()
{
    loadEmployeeStatistics();
}

void Statistique::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les statistiques", 
                                                    "statistiques_employes.txt", 
                                                    "Fichiers texte (*.txt)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le fichier!");
        return;
    }
    
    QTextStream out(&file);
    out << "STATISTIQUES DES EMPLOYÉS\n";
    out << "Date: " << QDate::currentDate().toString("dd/MM/yyyy") << "\n\n";
    out << "Total employés: " << ui->totalEmployeesLabel->text() << "\n";
    out << "Salaire moyen: " << ui->avgSalaryLabel->text() << "\n";
    out << "Disponibles: " << ui->availableLabel->text() << "\n";
    out << "Indisponibles: " << ui->unavailableLabel->text() << "\n\n";
    out << "Top 5 des postes:\n" << ui->topPositionsText->toPlainText() << "\n";
    out << "Répartition de la disponibilité:\n" << ui->availabilityText->toPlainText() << "\n";
    
    file.close();
    QMessageBox::information(this, "Succès", "Statistiques exportées avec succès!");
}
