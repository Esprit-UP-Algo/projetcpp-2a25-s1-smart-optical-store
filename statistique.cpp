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
    
    // Apply dark theme styling
    QString style = R"(
        QDialog {
            background-color: #0f172a;
            color: #e2e8f0;
        }
        QGroupBox {
            background-color: #1e293b;
            border: 2px solid #38bdf8;
            border-radius: 12px;
            padding: 12px;
            color: #e2e8f0;
        }
        QLabel {
            color: #e2e8f0;
        }
        QTextEdit {
            background-color: #0f172a;
            color: #e2e8f0;
            border: 1px solid #334155;
        }
        QPushButton {
            background-color: #2563eb;
            color: white;
            border-radius: 6px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #3b82f6;
        }
    )";
    
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
    
    auto renderChartInWidget = [](QWidget *container, QChart *chart) {
        if (!container || !chart) {
            return;
        }
        QLayout *layout = container->layout();
        if (!layout) {
            layout = new QVBoxLayout(container);
            container->setLayout(layout);
        } else {
            QLayoutItem *item = nullptr;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        }
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        layout->addWidget(chartView);
    };
    
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
    
    // Availability pie chart
    QPieSeries *availabilitySeries = new QPieSeries();
    availabilitySeries->append("Disponibles", available);
    availabilitySeries->append("Indisponibles", unavailable);
    for (QPieSlice *slice : availabilitySeries->slices()) {
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1 (%2)").arg(slice->label()).arg(slice->value()));
    }
    QChart *availabilityChart = new QChart();
    availabilityChart->addSeries(availabilitySeries);
    availabilityChart->setTitle("Répartition de la disponibilité");
    availabilityChart->legend()->setVisible(true);
    availabilityChart->legend()->setAlignment(Qt::AlignBottom);
    renderChartInWidget(ui->availabilityChartWidget, availabilityChart);
    
    // Top 5 positions (data collection)
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
    
    QVector<QPair<QString,int>> positionData;
    ui->topPositionsText->clear();
    QString positionsText;
    int rank = 1;
    while (query.next()) {
        QString poste = query.value(0).toString();
        int count = query.value(1).toInt();
        positionData.append(qMakePair(poste, count));
        positionsText += QString("%1. %2 (%3 employés)\n").arg(rank).arg(poste).arg(count);
        rank++;
    }
    
    if (!positionData.isEmpty()) {
        ui->topPositionsText->setText(positionsText);
    } else {
        ui->topPositionsText->setText("Aucune donnée de poste disponible.");
    }
    
    // Positions bar chart
    if (!positionData.isEmpty()) {
        QBarSet *positionsSet = new QBarSet("Employés");
        QStringList categories;
        for (const auto &item : positionData) {
            categories << item.first;
            *positionsSet << item.second;
        }
        
        QBarSeries *positionsSeries = new QBarSeries();
        positionsSeries->append(positionsSet);
        
        QChart *positionsChart = new QChart();
        positionsChart->addSeries(positionsSeries);
        positionsChart->setTitle("Répartition des postes");
        positionsChart->setAnimationOptions(QChart::SeriesAnimations);
        
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        positionsChart->addAxis(axisX, Qt::AlignBottom);
        positionsSeries->attachAxis(axisX);
        
        QValueAxis *axisY = new QValueAxis();
        int maxValue = 0;
        for (const auto &item : positionData) {
            maxValue = std::max(maxValue, item.second);
        }
        axisY->setRange(0, maxValue > 0 ? maxValue + 1 : 5);
        positionsChart->addAxis(axisY, Qt::AlignLeft);
        positionsSeries->attachAxis(axisY);
        positionsChart->legend()->setVisible(false);
        
        renderChartInWidget(ui->positionsChartWidget, positionsChart);
    } else {
        // Clear widget if no data
        renderChartInWidget(ui->positionsChartWidget, new QChart());
    }
    
    // Availability text summary (kept for export)
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
    } else {
        ui->availabilityText->setText("Pas encore de données de disponibilité.");
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
