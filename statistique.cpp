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
    resize(1200, 800);
    
    // --- Force Override Stylesheet for the Main Window ---
    // We use ID selectors to ensure specificity overrides the UI file's styles
    QString mainStyle = R"(
        QDialog {
            background-color: #19232D; /* Dark Blue-Grey Background */
            color: #ffffff;
        }
        QLabel {
            color: #ffffff;
            font-family: 'Segoe UI', sans-serif;
        }
        QLabel#titleLabel {
            color: #3daee9; /* Light Blue Title */
            font-size: 24px;
            font-weight: bold;
        }
        /* GroupBoxes - Dark Background with Blue Border */
        QGroupBox {
            background-color: #232629; /* Slightly lighter than main bg */
            border: 1px solid #3daee9;
            border-radius: 8px;
            margin-top: 20px;
            font-weight: bold;
            color: #3daee9; /* Title color */
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 5px 10px;
            background-color: #232629;
            border-radius: 5px;
        }
        /* Specific Labels inside GroupBoxes */
        QLabel#totalEmployeesLabel, QLabel#avgSalaryLabel, QLabel#availableLabel, QLabel#unavailableLabel {
            font-size: 36px;
            font-weight: bold;
            color: #ffffff;
            background-color: transparent;
        }
        QLabel#totalSubtitleLabel, QLabel#avgSalarySubtitleLabel, QLabel#availableSubtitleLabel, QLabel#unavailableSubtitleLabel {
            color: #aaaaaa;
            font-size: 12px;
            background-color: transparent;
        }
        /* TextEdits - Dark with White Text */
        QTextEdit {
            background-color: #232629;
            color: #ffffff;
            border: 1px solid #3daee9;
            border-radius: 4px;
        }
        /* Buttons */
        QPushButton {
            background-color: #3daee9;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #50c0ff;
        }
        QPushButton:pressed {
            background-color: #2c9cd0;
        }
        /* Chart Widgets Container */
        QWidget#availabilityChartWidget, QWidget#positionsChartWidget {
            background-color: transparent; 
            border: none;
        }
    )";
    this->setStyleSheet(mainStyle);
    
    // --- Explicitly clear conflicting stylesheets from UI file ---
    // The UI file sets specific stylesheets on these widgets which overrides the parent stylesheet.
    // We must clear them or set them to match our theme.
    QList<QWidget*> widgetsToFix = {
        ui->totalGroupBox, ui->avgSalaryGroupBox, ui->availableGroupBox, ui->unavailableGroupBox,
        ui->availabilityGroupBox, ui->positionsGroupBox,
        ui->availabilityChartWidget, ui->positionsChartWidget,
        ui->availabilityText, ui->topPositionsText,
        ui->refreshButton, ui->exportButton
    };
    
    for (QWidget* w : widgetsToFix) {
        w->setStyleSheet(""); // Clear specific style so it inherits or uses the global stylesheet
    }
    
    // Re-apply specific styles if clearing them isn't enough (sometimes needed for GroupBoxes)
    QString boxStyle = "QGroupBox { background-color: #232629; border: 1px solid #3daee9; border-radius: 8px; margin-top: 20px; color: #3daee9; } "
                       "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0px 5px; }";
    ui->totalGroupBox->setStyleSheet(boxStyle);
    ui->avgSalaryGroupBox->setStyleSheet(boxStyle);
    ui->availableGroupBox->setStyleSheet(boxStyle);
    ui->unavailableGroupBox->setStyleSheet(boxStyle);
    ui->availabilityGroupBox->setStyleSheet(boxStyle);
    ui->positionsGroupBox->setStyleSheet(boxStyle);

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
            layout->setContentsMargins(0, 0, 0, 0);
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
        chartView->setBackgroundBrush(QColor("#232629")); // Match GroupBox background
        chartView->setStyleSheet("background: transparent;");
        layout->addWidget(chartView);
    };
    
    // --- 1. Total Employees ---
    int totalEmployees = 0;
    QString sql = "SELECT COUNT(*) FROM employe";
    if (!query.exec(sql)) {
        // Fallback queries
        if (!query.exec("SELECT COUNT(*) FROM EMPLOYE") && 
            !query.exec("SELECT COUNT(*) FROM \"Employe\"")) {
            qDebug() << "Error counting employees:" << query.lastError().text();
        }
    }
    if (query.next()) totalEmployees = query.value(0).toInt();
    ui->totalEmployeesLabel->setText(QString::number(totalEmployees));
    ui->totalEmployeesLabel->setStyleSheet("color: #00d4ff; font-size: 42px; font-weight: bold;");

    // --- 2. Average Salary ---
    double avgSalary = 0.0;
    if (!query.exec("SELECT AVG(salaire) FROM employe WHERE salaire IS NOT NULL")) {
        if (!query.exec("SELECT AVG(SALAIRE) FROM EMPLOYE WHERE SALAIRE IS NOT NULL") &&
            !query.exec("SELECT AVG(\"Salaire\") FROM \"Employe\" WHERE \"Salaire\" IS NOT NULL")) {
             qDebug() << "Error calculating avg salary:" << query.lastError().text();
        }
    }
    if (query.next()) avgSalary = query.value(0).toDouble();
    ui->avgSalaryLabel->setText(QString::number(avgSalary, 'f', 2) + " DT");
    ui->avgSalaryLabel->setStyleSheet("color: #50fa7b; font-size: 42px; font-weight: bold;"); // Green for money

    // --- 3. Availability ---
    int available = 0;
    int unavailable = 0;
    
    // Count Available
    if (!query.exec("SELECT COUNT(*) FROM employe WHERE UPPER(dispo) = 'O'")) {
        query.exec("SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(DISPO) = 'O'");
    }
    if (query.next()) available = query.value(0).toInt();
    
    // Count Unavailable
    if (!query.exec("SELECT COUNT(*) FROM employe WHERE UPPER(dispo) = 'N'")) {
        query.exec("SELECT COUNT(*) FROM EMPLOYE WHERE UPPER(DISPO) = 'N'");
    }
    if (query.next()) unavailable = query.value(0).toInt();

    ui->availableLabel->setText(QString::number(available));
    ui->availableLabel->setStyleSheet("color: #50fa7b; font-size: 42px; font-weight: bold;");
    
    ui->unavailableLabel->setText(QString::number(unavailable));
    ui->unavailableLabel->setStyleSheet("color: #ff5555; font-size: 42px; font-weight: bold;");

    // --- 4. Availability Chart (Donut) ---
    QPieSeries *availabilitySeries = new QPieSeries();
    availabilitySeries->setHoleSize(0.4); // Make it a donut
    
    QPieSlice *sliceAvail = availabilitySeries->append("Disponibles", available);
    QPieSlice *sliceUnavail = availabilitySeries->append("Indisponibles", unavailable);
    
    sliceAvail->setBrush(QColor("#50fa7b")); // Green
    sliceAvail->setLabelColor(Qt::white);
    sliceAvail->setLabelVisible(true);
    
    sliceUnavail->setBrush(QColor("#ff5555")); // Red
    sliceUnavail->setLabelColor(Qt::white);
    sliceUnavail->setLabelVisible(true);
    
    // Explode if unavailable exists to highlight it
    if (unavailable > 0) {
        sliceUnavail->setExploded(true);
        sliceUnavail->setExplodeDistanceFactor(0.1);
    }

    QChart *availabilityChart = new QChart();
    availabilityChart->addSeries(availabilitySeries);
    availabilityChart->setTitle("Statut de Disponibilité");
    availabilityChart->setTitleBrush(QBrush(Qt::white));
    availabilityChart->setTitleFont(QFont("Segoe UI", 12, QFont::Bold));
    availabilityChart->setBackgroundBrush(QBrush(QColor("#232629")));
    availabilityChart->legend()->setVisible(true);
    availabilityChart->legend()->setAlignment(Qt::AlignBottom);
    availabilityChart->legend()->setLabelBrush(QBrush(Qt::white));
    
    renderChartInWidget(ui->availabilityChartWidget, availabilityChart);

    // --- 5. Top Positions Chart (Donut) ---
    // Try multiple query formats for compatibility
    QStringList positionQueries = {
        "SELECT poste, COUNT(*) as count FROM employe GROUP BY poste ORDER BY count DESC LIMIT 5",
        "SELECT POSTE, COUNT(*) as count FROM EMPLOYE GROUP BY POSTE ORDER BY count DESC FETCH FIRST 5 ROWS ONLY",
        "SELECT * FROM (SELECT POSTE, COUNT(*) as count FROM EMPLOYE GROUP BY POSTE ORDER BY count DESC) WHERE ROWNUM <= 5",
        "SELECT \"Poste\", COUNT(*) as count FROM \"Employe\" GROUP BY \"Poste\" ORDER BY count DESC LIMIT 5"
    };

    bool querySuccess = false;
    for (const QString &q : positionQueries) {
        if (query.exec(q)) {
            querySuccess = true;
            break;
        }
    }

    QVector<QPair<QString,int>> positionData;
    ui->topPositionsText->clear();
    QString positionsText;
    int rank = 1;
    
    if (querySuccess) {
        while (query.next()) {
            QString poste = query.value(0).toString();
            if (poste.isEmpty()) poste = "Non spécifié";
            int count = query.value(1).toInt();
            positionData.append(qMakePair(poste, count));
            positionsText += QString("%1. %2 (%3)\n").arg(rank).arg(poste).arg(count);
            rank++;
        }
    } else {
        qDebug() << "All position queries failed. Last error:" << query.lastError().text();
    }
    
    if (!positionData.isEmpty()) {
        ui->topPositionsText->setText(positionsText);
        
        // Create Donut Chart for Positions
        QPieSeries *positionsSeries = new QPieSeries();
        positionsSeries->setHoleSize(0.35);
        
        // Vibrant colors for the chart
        QList<QColor> colors = {
            QColor("#00d4ff"), // Cyan
            QColor("#bd93f9"), // Purple
            QColor("#ff79c6"), // Pink
            QColor("#f1fa8c"), // Yellow
            QColor("#ffb86c")  // Orange
        };
        
        int colorIdx = 0;
        for (const auto &item : positionData) {
            QPieSlice *slice = positionsSeries->append(item.first, item.second);
            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setBrush(colors[colorIdx % colors.size()]);
            
            // Highlight the top position
            if (colorIdx == 0) {
                slice->setExploded(true);
                slice->setExplodeDistanceFactor(0.1);
            }
            
            colorIdx++;
        }
        
        QChart *positionsChart = new QChart();
        positionsChart->addSeries(positionsSeries);
        positionsChart->setTitle("Top 5 des Postes");
        positionsChart->setTitleBrush(QBrush(Qt::white));
        positionsChart->setTitleFont(QFont("Segoe UI", 12, QFont::Bold));
        positionsChart->setBackgroundBrush(QBrush(QColor("#232629")));
        positionsChart->legend()->setVisible(true);
        positionsChart->legend()->setAlignment(Qt::AlignRight);
        positionsChart->legend()->setLabelBrush(QBrush(Qt::white));
        
        renderChartInWidget(ui->positionsChartWidget, positionsChart);
        
    } else {
        ui->topPositionsText->setText("Aucune donnée de poste disponible.");
        
        // Show an empty placeholder chart
        QChart *emptyChart = new QChart();
        emptyChart->setTitle("Aucune donnée");
        emptyChart->setTitleBrush(QBrush(Qt::white));
        emptyChart->setBackgroundBrush(QBrush(QColor("#232629")));
        renderChartInWidget(ui->positionsChartWidget, emptyChart);
    }

    // Update text summary for export
    if (totalEmployees > 0) {
        double availablePercent = (available * 100.0) / totalEmployees;
        double unavailablePercent = (unavailable * 100.0) / totalEmployees;
        QString distText = QString("Disponibles: %1% (%2)\n")
                          .arg(availablePercent, 0, 'f', 1)
                          .arg(available);
        distText += QString("Indisponibles: %1% (%2)")
                   .arg(unavailablePercent, 0, 'f', 1)
                   .arg(unavailable);
        ui->availabilityText->setText(distText);
    } else {
        ui->availabilityText->setText("Pas de données.");
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
    out << "========================================\n";
    out << "       STATISTIQUES DES EMPLOYÉS        \n";
    out << "========================================\n";
    out << "Date: " << QDate::currentDate().toString("dd/MM/yyyy") << "\n\n";
    out << "Total employés: " << ui->totalEmployeesLabel->text() << "\n";
    out << "Salaire moyen: " << ui->avgSalaryLabel->text() << "\n";
    out << "Disponibles: " << ui->availableLabel->text() << "\n";
    out << "Indisponibles: " << ui->unavailableLabel->text() << "\n\n";
    out << "----------------------------------------\n";
    out << "TOP 5 DES POSTES:\n";
    out << ui->topPositionsText->toPlainText() << "\n";
    out << "----------------------------------------\n";
    out << "RÉPARTITION DE LA DISPONIBILITÉ:\n";
    out << ui->availabilityText->toPlainText() << "\n";
    out << "========================================\n";
    
    file.close();
    QMessageBox::information(this, "Succès", "Statistiques exportées avec succès!");
}
