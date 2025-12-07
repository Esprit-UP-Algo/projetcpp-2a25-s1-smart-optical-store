#include "mainwindow.h"
//#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QMessageBox>
#include "saleswindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include <QApplication>
#include "WindowManager.h"
#include <QMouseEvent>
#include "produit.h"
#include "Connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDate>
#include <QAbstractItemView>

#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPainter>

#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include <QPainterPath>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QPdfWriter>
#include <QPagedPaintDevice>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextFrameFormat>
#include <QLocale>

#include <QProcess>
#include <QTemporaryFile>
#include <QFile>


MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new MainWindow(parent);
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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);



//arduino
    int ret = A.connect_arduino();
    if (ret == 0) {
        QObject::connect(A.getserial(), SIGNAL(readyRead()),
                         this, SLOT(readSerialData()));
    }



    Produit p;
    p.afficher(ui);

    ui->lineEdit_5->setPlaceholderText("Tapez la référence ou designation");
    ui->lineEdit_6->setPlaceholderText("Tapez la référence");

    connect(ui->comboBox_2, &QComboBox::currentTextChanged,
            this, &MainWindow::loadFournisseursByCategorie);

    connect(ui->pushButton_12, &QPushButton::clicked, this, [=](){
        ui->travaille->setCurrentIndex(0);
    });

    connect(ui->pushButton_7, &QPushButton::clicked, this, [=](){
        ui->travaille->setCurrentIndex(1);


    });
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion de Stock", 1200, 800);

    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
    }

    qDebug() << "Chemin courant =" << QDir::currentPath();
    ui->logoLabel->setPixmap(QPixmap(":/images/logof.jpg"));
    ui->logoLabel->setScaledContents(true);


    loadFournisseursByCategorie("Lunettes");


    if (ui->logoLabel) {
        ui->logoLabel->setCursor(Qt::PointingHandCursor);
        ui->logoLabel->installEventFilter(this);
        ui->logoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }

    // Setup table widget
    /*ui->tableWidget->setColumnCount(9);
    QStringList headers = {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    */ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);





    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                this->raise();
                this->activateWindow();
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->travaille->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->travaille->setCurrentIndex(1);
}




void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->logoLabel && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            on_logoClicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_logoClicked()
{
    DashboardWindow::getInstance();
    this->close();
}

void MainWindow::loadFournisseursByCategorie(const QString &categorie)
{
    ui->comboBox_idFour->clear();

    QSqlQuery query;
    query.prepare(
        "SELECT ID_FOURNISSEUR, NOM_ENTREPRISE "
        "FROM FOURNISSEUR "
        "WHERE UPPER(TYPE_PRODUIT_FOURNIS) = UPPER(:category)"
        );

    query.bindValue(":category", categorie);

    if (!query.exec()) {
        qDebug() << "Erreur loadFournisseursByCategorie:" << query.lastError().text();
        return;
    }

    while (query.next())
    {
        QString id  = query.value(0).toString();
        QString nom = query.value(1).toString();

        ui->comboBox_idFour->addItem(id + " - " + nom, id);
    }

    if (ui->comboBox_idFour->count() == 0) {
        ui->comboBox_idFour->addItem("Aucun fournisseur disponible", -1);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données non disponible!");
        return;
    }

    QSqlQuery query(db);

    // 🔴 CRITIQUE
    int critique = 0;
    if (query.exec("SELECT COUNT(*) FROM PRODUIT WHERE DATEEXPIRATION BETWEEN SYSDATE AND SYSDATE + 7")) {
        if (query.next()) {
            critique = query.value(0).toInt();
        }
    }

    // 🟠 URGENT
    int urgent = 0;
    if (query.exec("SELECT COUNT(*) FROM PRODUIT WHERE DATEEXPIRATION BETWEEN SYSDATE + 8 AND SYSDATE + 15")) {
        if (query.next()) {
            urgent = query.value(0).toInt();
        }
    }

    // 🟡 ATTENTION
    int attention = 0;
    if (query.exec("SELECT COUNT(*) FROM PRODUIT WHERE DATEEXPIRATION BETWEEN SYSDATE + 16 AND SYSDATE + 30")) {
        if (query.next()) {
            attention = query.value(0).toInt();
        }
    }

    // ⚫ EXPIRÉS
    int expires = 0;
    if (query.exec("SELECT COUNT(*) FROM PRODUIT WHERE DATEEXPIRATION < SYSDATE")) {
        if (query.next()) {
            expires = query.value(0).toInt();
        }
    }

    // Create Bar Sets for each urgency level
    QBarSet *critiqueSet = new QBarSet(" CRITIQUE (0-7j)");
    QBarSet *urgentSet = new QBarSet(" URGENT (8-15j)");
    QBarSet *attentionSet = new QBarSet(" ATTENTION (16-30j)");
    QBarSet *expiresSet = new QBarSet(" EXPIRÉS");

    // Add data
    *critiqueSet << critique;
    *urgentSet << urgent;
    *attentionSet << attention;
    *expiresSet << expires;

    // Set colors
    critiqueSet->setColor(QColor(231, 76, 60));    // Rouge vif
    urgentSet->setColor(QColor(230, 126, 34));     // Orange
    attentionSet->setColor(QColor(241, 196, 15));  // Jaune
    expiresSet->setColor(QColor(44, 62, 80));      // Noir

    // Create bar series
    QBarSeries *series = new QBarSeries();
    series->append(critiqueSet);
    series->append(urgentSet);
    series->append(attentionSet);
    series->append(expiresSet);

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("📊 ALERTES D'EXPIRATION PAR URGENCE");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Set font for title
    QFont titleFont;
    titleFont.setPixelSize(18);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

    // Create axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Produits");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de produits");
    axisY->setLabelFormat("%d");
    axisY->setTickCount(6);

    // Find max value for better Y-axis range
    int maxValue = qMax(qMax(critique, urgent), qMax(attention, expires));
    axisY->setRange(0, maxValue + 5);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Legend positioning
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Create chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear any existing layout/widgets in the label's parent
    if (ui->label->layout()) {
        QLayoutItem *item;
        while ((item = ui->label->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->label->layout();
    }

    // Create new layout for the label
    QVBoxLayout *layout = new QVBoxLayout(ui->label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);

    // Add summary text below chart
    QString summaryText = QString(
                              "<div style='padding: 10px; background-color: #ecf0f1; border-radius: 5px;'>"
                              "<h3 style='color: #2c3e50; text-align: center; margin: 5px;'>📋 RÉSUMÉ</h3>"
                              "<p style='font-size: 13px; margin: 5px;'>"
                              "<span style='color: #e74c3c; font-weight: bold;'> CRITIQUE:</span><span style='color: #000000'> %1 produits (0-7 jours)</span><br>"
                              "<span style='color: #e67e22; font-weight: bold;'> URGENT:</span><span style='color: #000000'> %2 produits (8-15 jours)</span><br>"
                              "<span style='color: #f39c12; font-weight: bold;'> ATTENTION:</span><span style='color: #000000'> %3 produits (16-30 jours)</span><br>"
                              "<span style='color: #95a5a6; font-weight: bold;'> EXPIRÉS:</span><span style='color: #000000'> %4 produits</span><br>"
                              "<br><b><span style='color: #000000; font-weight: bold;'>TOTAL À RISQUE (30j):</span></b> <span style='color: #000000'>%5 produits</span>"
                              "</p></div>"
                              ).arg(critique).arg(urgent).arg(attention).arg(expires).arg(critique + urgent + attention);

    QLabel *summaryLabel = new QLabel(summaryText);
    summaryLabel->setTextFormat(Qt::RichText);
    summaryLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(summaryLabel);

    ui->label->setLayout(layout);
}




void MainWindow::on_pushButton_15_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter le Rapport Stock",
                                                    QString("Rapport_Stock_%1.pdf").arg(QDate::currentDate().toString("dd-MM-yyyy")),
                                                    "PDF (*.pdf)");

    if (fileName.isEmpty()) {
        return;
    }

    // Create PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20));
    pdfWriter.setResolution(300);

    // Create text document
    QTextDocument document;
    QTextCursor cursor(&document);

    // Format pour centrer le texte (utilisé dans tous les tableaux)
    QTextBlockFormat centerFormat;
    centerFormat.setAlignment(Qt::AlignCenter);
    centerFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

    // Configure French locale for date
    QLocale frenchLocale(QLocale::French, QLocale::France);
    QString dateStr = frenchLocale.toString(QDate::currentDate(), "dddd dd MMMM yyyy");
    dateStr[0] = dateStr[0].toUpper();

    // ========== HEADER ==========
    QTextBlockFormat headerFormat;
    headerFormat.setAlignment(Qt::AlignCenter);
    headerFormat.setBackground(QBrush(QColor(45, 52, 54))); // Gris anthracite élégant
    headerFormat.setTopMargin(20);
    headerFormat.setBottomMargin(20);

    QTextCharFormat headerTextFormat;
    headerTextFormat.setForeground(QBrush(Qt::white));
    headerTextFormat.setFontPointSize(24);
    headerTextFormat.setFontWeight(QFont::Bold);
    headerTextFormat.setFontFamily("Segoe UI");

    cursor.setBlockFormat(headerFormat);
    cursor.setCharFormat(headerTextFormat);
    cursor.insertText("RAPPORT DE STOCK");
    cursor.insertBlock();

    // Date
    QTextCharFormat dateHeaderFormat;
    dateHeaderFormat.setForeground(QBrush(Qt::white));
    dateHeaderFormat.setFontPointSize(11);
    dateHeaderFormat.setFontFamily("Segoe UI");

    cursor.setCharFormat(dateHeaderFormat);
    cursor.insertText(dateStr);
    cursor.insertBlock();
    cursor.insertBlock();

    // ========== VUE D'ENSEMBLE ==========
    QTextBlockFormat titleFormat;
    titleFormat.setAlignment(Qt::AlignLeft);
    titleFormat.setTopMargin(25);
    titleFormat.setBottomMargin(15);
    titleFormat.setLeftMargin(10);
    titleFormat.setBackground(QBrush(QColor(250, 250, 250))); // Gris très clair

    QTextCharFormat titleTextFormat;
    titleTextFormat.setFontPointSize(16);
    titleTextFormat.setFontWeight(QFont::Bold);
    titleTextFormat.setForeground(QBrush(QColor(45, 52, 54)));
    titleTextFormat.setFontFamily("Segoe UI");

    cursor.setBlockFormat(titleFormat);
    cursor.setCharFormat(titleTextFormat);
    cursor.insertText("Vue d'ensemble");
    cursor.insertBlock();
    cursor.insertBlock();

    // Récupérer les statistiques
    QSqlQuery statsQuery;
    int totalProduits = 0;
    int categoriesCount = 0;
    int stockFaible = 0;
    int produitsExpiration = 0;

    if (statsQuery.exec("SELECT COUNT(*) FROM PRODUIT")) {
        if (statsQuery.next()) totalProduits = statsQuery.value(0).toInt();
    }

    if (statsQuery.exec("SELECT COUNT(DISTINCT CATEGORIE) FROM PRODUIT")) {
        if (statsQuery.next()) categoriesCount = statsQuery.value(0).toInt();
    }

    if (statsQuery.exec("SELECT COUNT(*) FROM PRODUIT WHERE QUANTITE < 10")) {
        if (statsQuery.next()) stockFaible = statsQuery.value(0).toInt();
    }

    if (statsQuery.exec("SELECT COUNT(*) FROM PRODUIT WHERE DATEEXPIRATION BETWEEN SYSDATE AND SYSDATE + 15")) {
        if (statsQuery.next()) produitsExpiration = statsQuery.value(0).toInt();
    }

    // Stats en format simple
    QTextBlockFormat statsFormat;
    statsFormat.setLeftMargin(20);
    statsFormat.setLineHeight(150, QTextBlockFormat::ProportionalHeight); // Espacement 1.5

    QTextCharFormat statsTextFormat;
    statsTextFormat.setFontPointSize(11);
    statsTextFormat.setForeground(QBrush(QColor(45, 52, 54)));
    statsTextFormat.setFontFamily("Segoe UI");

    cursor.setBlockFormat(statsFormat);
    cursor.setCharFormat(statsTextFormat);
    cursor.insertText(QString("• Nombre total de produits : %1").arg(totalProduits));
    cursor.insertBlock();
    cursor.insertText(QString("• Catégories actives : %1").arg(categoriesCount));
    cursor.insertBlock();
    cursor.insertText(QString("• Produits en stock faible (< 10 unités) : %1").arg(stockFaible));
    cursor.insertBlock();
    cursor.insertText(QString("• Produits proche expiration (< 15 jours) : %1").arg(produitsExpiration));
    cursor.insertBlock();
    cursor.insertBlock();

    // ========== RÉPARTITION PAR CATÉGORIE ==========
    cursor.setBlockFormat(titleFormat);
    cursor.setCharFormat(titleTextFormat);
    cursor.insertText("Répartition par catégorie");
    cursor.insertBlock();
    cursor.insertBlock();

    // Table simple et élégante
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setCellPadding(12);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setBorder(1);
    tableFormat.setBorderBrush(QBrush(QColor(220, 220, 220))); // Bordure gris clair
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBackground(QBrush(Qt::white));
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 95));
    tableFormat.setTopMargin(10);
    tableFormat.setBottomMargin(10);

    QSqlQuery categoryQuery;
    categoryQuery.prepare("SELECT CATEGORIE, COUNT(*) as COUNT, SUM(QUANTITE) as TOTAL_QTE "
                          "FROM PRODUIT "
                          "GROUP BY CATEGORIE ORDER BY COUNT DESC");

    if (categoryQuery.exec()) {
        int rowCount = 0;
        categoryQuery.last();
        rowCount = categoryQuery.at() + 1;
        categoryQuery.first();
        categoryQuery.previous();

        QTextTable *table = cursor.insertTable(rowCount + 1, 3, tableFormat);

        // Format pour centrer le texte dans les cellules
        QTextBlockFormat centerFormat;
        centerFormat.setAlignment(Qt::AlignCenter);
        centerFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

        // Header élégant
        QTextCharFormat headerCellFormat;
        headerCellFormat.setBackground(QBrush(QColor(45, 52, 54))); // Gris anthracite
        headerCellFormat.setForeground(QBrush(Qt::white));
        headerCellFormat.setFontWeight(QFont::Bold);
        headerCellFormat.setFontPointSize(11);
        headerCellFormat.setFontFamily("Segoe UI");

        QTextTableCell cell;
        QTextCursor cellCursor;

        cell = table->cellAt(0, 0);
        cell.setFormat(headerCellFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Catégorie");

        cell = table->cellAt(0, 1);
        cell.setFormat(headerCellFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Nombre de produits");

        cell = table->cellAt(0, 2);
        cell.setFormat(headerCellFormat);
        cellCursor = cell.firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Quantité totale");

        // Lignes avec alternance subtile
        QTextCharFormat evenRowFormat;
        evenRowFormat.setBackground(QBrush(QColor(250, 250, 250))); // Gris très léger
        evenRowFormat.setFontPointSize(10);
        evenRowFormat.setFontFamily("Segoe UI");
        evenRowFormat.setForeground(QBrush(QColor(45, 52, 54)));

        QTextCharFormat oddRowFormat;
        oddRowFormat.setBackground(QBrush(Qt::white));
        oddRowFormat.setFontPointSize(10);
        oddRowFormat.setFontFamily("Segoe UI");
        oddRowFormat.setForeground(QBrush(QColor(45, 52, 54)));

        int row = 1;
        while (categoryQuery.next()) {
            QTextCharFormat rowFormat = (row % 2 == 0) ? evenRowFormat : oddRowFormat;

            cell = table->cellAt(row, 0);
            cell.setFormat(rowFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText(categoryQuery.value("CATEGORIE").toString());

            cell = table->cellAt(row, 1);
            cell.setFormat(rowFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText(QString::number(categoryQuery.value("COUNT").toInt()));

            cell = table->cellAt(row, 2);
            cell.setFormat(rowFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText(QString::number(categoryQuery.value("TOTAL_QTE").toInt()));

            row++;
        }

        cursor.movePosition(QTextCursor::End);
    }

    cursor.insertBlock();
    cursor.insertBlock();

    // ========== ALERTES D'EXPIRATION ==========
    QTextBlockFormat alertTitleFormat = titleFormat;
    alertTitleFormat.setBackground(QBrush(QColor(255, 245, 245))); // Rose très pâle

    QTextCharFormat alertTitleTextFormat = titleTextFormat;
    alertTitleTextFormat.setForeground(QBrush(QColor(220, 53, 69))); // Rouge élégant

    cursor.setBlockFormat(alertTitleFormat);
    cursor.setCharFormat(alertTitleTextFormat);
    cursor.insertText("Alertes d'expiration (< 15 jours)");
    cursor.insertBlock();
    cursor.insertBlock();

    QSqlQuery expirationQuery;
    expirationQuery.prepare(
        "SELECT REFERENCE, DESIGNATION, CATEGORIE, QUANTITE, DATEEXPIRATION, "
        "(DATEEXPIRATION - SYSDATE) as JOURS_RESTANTS "
        "FROM PRODUIT "
        "WHERE DATEEXPIRATION BETWEEN SYSDATE AND SYSDATE + 15 "
        "ORDER BY DATEEXPIRATION ASC"
        );

    if (expirationQuery.exec()) {
        int expRowCount = 0;
        expirationQuery.last();
        expRowCount = expirationQuery.at() + 1;
        expirationQuery.first();
        expirationQuery.previous();

        if (expRowCount > 0) {
            QTextTable *expTable = cursor.insertTable(expRowCount + 1, 5, tableFormat);

            // Format pour centrer le texte
            QTextBlockFormat centerFormat;
            centerFormat.setAlignment(Qt::AlignCenter);
            centerFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

            // Header
            QTextCharFormat expHeaderFormat;
            expHeaderFormat.setBackground(QBrush(QColor(220, 53, 69))); // Rouge élégant
            expHeaderFormat.setForeground(QBrush(Qt::white));
            expHeaderFormat.setFontWeight(QFont::Bold);
            expHeaderFormat.setFontPointSize(10);
            expHeaderFormat.setFontFamily("Segoe UI");

            QTextTableCell cell;
            QTextCursor cellCursor;

            cell = expTable->cellAt(0, 0);
            cell.setFormat(expHeaderFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText("Référence");

            cell = expTable->cellAt(0, 1);
            cell.setFormat(expHeaderFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText("Désignation");

            cell = expTable->cellAt(0, 2);
            cell.setFormat(expHeaderFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText("Catégorie");

            cell = expTable->cellAt(0, 3);
            cell.setFormat(expHeaderFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText("Quantité");

            cell = expTable->cellAt(0, 4);
            cell.setFormat(expHeaderFormat);
            cellCursor = cell.firstCursorPosition();
            cellCursor.setBlockFormat(centerFormat);
            cellCursor.insertText("Jours restants");

            // Lignes avec couleurs subtiles selon urgence
            int row = 1;
            while (expirationQuery.next()) {
                int joursRestants = expirationQuery.value("JOURS_RESTANTS").toInt();

                QTextCharFormat urgencyFormat;
                urgencyFormat.setFontPointSize(10);
                urgencyFormat.setFontFamily("Segoe UI");
                urgencyFormat.setForeground(QBrush(QColor(45, 52, 54)));

                // Couleurs subtiles selon urgence
                if (joursRestants <= 7) {
                    urgencyFormat.setBackground(QBrush(QColor(255, 235, 238))); // Rose très pâle
                } else {
                    urgencyFormat.setBackground(QBrush(QColor(255, 248, 240))); // Beige très pâle
                }

                cell = expTable->cellAt(row, 0);
                cell.setFormat(urgencyFormat);
                cellCursor = cell.firstCursorPosition();
                cellCursor.setBlockFormat(centerFormat);
                cellCursor.insertText(expirationQuery.value("REFERENCE").toString());

                cell = expTable->cellAt(row, 1);
                cell.setFormat(urgencyFormat);
                cellCursor = cell.firstCursorPosition();
                cellCursor.setBlockFormat(centerFormat);
                cellCursor.insertText(expirationQuery.value("DESIGNATION").toString());

                cell = expTable->cellAt(row, 2);
                cell.setFormat(urgencyFormat);
                cellCursor = cell.firstCursorPosition();
                cellCursor.setBlockFormat(centerFormat);
                cellCursor.insertText(expirationQuery.value("CATEGORIE").toString());

                cell = expTable->cellAt(row, 3);
                cell.setFormat(urgencyFormat);
                cellCursor = cell.firstCursorPosition();
                cellCursor.setBlockFormat(centerFormat);
                cellCursor.insertText(QString::number(expirationQuery.value("QUANTITE").toInt()));

                cell = expTable->cellAt(row, 4);

                // Colorer le texte des jours selon urgence
                QTextCharFormat daysFormat = urgencyFormat;
                if (joursRestants <= 3) {
                    daysFormat.setForeground(QBrush(QColor(220, 53, 69))); // Rouge
                    daysFormat.setFontWeight(QFont::Bold);
                } else if (joursRestants <= 7) {
                    daysFormat.setForeground(QBrush(QColor(255, 127, 80))); // Orange corail
                    daysFormat.setFontWeight(QFont::Bold);
                }

                cell.setFormat(daysFormat);
                cellCursor = cell.firstCursorPosition();
                cellCursor.setBlockFormat(centerFormat);
                cellCursor.insertText(QString("%1 jour%2").arg(joursRestants).arg(joursRestants > 1 ? "s" : ""));

                row++;
            }

            cursor.movePosition(QTextCursor::End);
        } else {
            QTextBlockFormat successFormat;
            successFormat.setAlignment(Qt::AlignCenter);
            successFormat.setTopMargin(15);
            successFormat.setBottomMargin(15);
            successFormat.setBackground(QBrush(QColor(240, 255, 244))); // Vert très pâle
            successFormat.setLeftMargin(20);
            successFormat.setRightMargin(20);

            QTextCharFormat successTextFormat;
            successTextFormat.setFontPointSize(11);
            successTextFormat.setForeground(QBrush(QColor(40, 167, 69))); // Vert
            successTextFormat.setFontFamily("Segoe UI");

            cursor.setBlockFormat(successFormat);
            cursor.setCharFormat(successTextFormat);
            cursor.insertText("✓ Aucun produit en situation critique");
        }
    }

    cursor.insertBlock();
    cursor.insertBlock();

    // ========== FOOTER ==========
    QTextBlockFormat footerFormat;
    footerFormat.setAlignment(Qt::AlignCenter);
    footerFormat.setTopMargin(40);

    QTextCharFormat footerTextFormat;
    footerTextFormat.setFontPointSize(8);
    footerTextFormat.setForeground(QBrush(QColor(150, 150, 150))); // Gris moyen
    footerTextFormat.setFontFamily("Segoe UI");

    cursor.setBlockFormat(footerFormat);
    cursor.setCharFormat(footerTextFormat);
    cursor.insertText("─────────────────────────────────────────");
    cursor.insertBlock();
    cursor.insertText("Document généré par le Système de Gestion de Stock");
    cursor.insertBlock();
    cursor.insertText(QString("© %1 - Tous droits réservés").arg(QDate::currentDate().year()));

    // Print document to PDF
    document.print(&pdfWriter);

    QMessageBox::information(this, "Succès",
                             QString("✅ Rapport exporté avec succès!\n\n📄 %1").arg(fileName));
}






void MainWindow::on_pushButton_2_clicked()
{
    QString reference = ui->lineEdit_3->text();
    QString designation = ui->lineEdit_des->text();
    QString marque     = ui->lineEdit_7->text();
    QString couleur    = ui->lineEdit_8->text();
    QString prix       = ui->lineEdit_29->text();
    QString quantite   = ui->lineEdit_9->text();

    QRegularExpression rxReference("^[A-Za-z]{2}[0-9]{5}$");
    QRegularExpression rxDesignation("^[A-Za-z]{5}[0-9]{2}$");
    QRegularExpression rxMarque("^[A-Za-z]+$");
    QRegularExpression rxCouleur("^[A-Za-z]+$");
    QRegularExpression rxPrix("^[0-9]+(\\.[0-9]+)?$");
    QRegularExpression rxQuantite("^[0-9]+$");

    if (!rxReference.match(reference).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La référence doit contenir 2 lettres + 5 chiffres (ex: AB12345).");
        return;
    }

    if (!rxDesignation.match(designation).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La désignation doit contenir 5 lettres + 2 chiffres (ex: ABCDE12).");
        return;
    }

    if (!rxMarque.match(marque).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La marque doit contenir seulement des lettres.");
        return;
    }

    if (!rxCouleur.match(couleur).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La couleur doit contenir seulement des lettres.");
        return;
    }

    if (!rxPrix.match(prix).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre (ex: 45 ou 45.6).");
        return;
    }

    if (!rxQuantite.match(quantite).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre.");
        return;
    }

    Produit p(ui);
    bool test=p.ajouter();
    if (test)
    {
        QMessageBox::information(this, tr("Ajouté"), tr("Produit ajouté avec succès !"));

    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout du produit."));
    }
    p.afficher(ui);


    MainWindow::on_pushButton_14_clicked();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->lineEdit_3->clear();   // Ref
    ui->lineEdit_des->clear();   // Designation
    ui->lineEdit_9->clear();   // Quantité
    ui->lineEdit_29->clear();  // Prix
    ui->comboBox_2->setCurrentIndex(0);  // Catégorie
    ui->lineEdit_8->clear();   // Couleur
    ui->lineEdit_7->clear();   // Marque
    ui->dateEdit->setDate(QDate::currentDate()); // Date d’expiration
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(true);


}





void MainWindow::on_pushButton_5_clicked()
{
    QString reference = ui->lineEdit_6->text();

    Produit c;
    bool test = c.supprimer(reference);

    if (test)
    {
        QMessageBox::information(this, tr("Suppression réussie"),tr("Le produit a été supprimé avec succès."));
        c.afficher(ui);
    }
    else
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échoué. Vérifiez la reference saisie.") );
    }
    ui->lineEdit_6->clear();
}


void MainWindow::on_pushButton_clicked()
{
    QString rech = ui->lineEdit_5->text();
    Produit c;

    if (!c.rech(rech, ui)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun produit trouvé !"));
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    QString trier = ui->comboBox->currentText();
    if (trier == "categories")
    {

        ui->tableWidget->sortItems(6, Qt::AscendingOrder);
    }
    else if (trier == "genre")
    {
        ui->tableWidget->sortItems(2, Qt::DescendingOrder );
    }
    else
    {
        QMessageBox::warning(this, "Tri", "Choisissez un critère valide !");
    }
}
void MainWindow::on_pushButton_16_clicked()
{
    Produit c(ui);
    if (c.existe(c.getReference()))
    {
        c.modifier();
        QMessageBox::information(this, " Modifié", "produit modifié avec succès");
    }
    else
    {

        QMessageBox::critical(this,tr("Erreur"),tr("produit pas trouvé") );
    }
    c.afficher(ui);
}

void MainWindow::on_tableWidget_cellClicked(int row)
{
    QString reference = ui->tableWidget->item(row, 0)->text();

    ui->lineEdit_3->setText(reference);

    ui->lineEdit_des->setText(ui->tableWidget->item(row, 7)->text());
    ui->comboBox_2->setCurrentText(ui->tableWidget->item(row, 6)->text());
    ui->lineEdit_7->setText(ui->tableWidget->item(row, 5)->text());
    ui->lineEdit_29->setText(ui->tableWidget->item(row, 3)->text());
    ui->lineEdit_9->setText(ui->tableWidget->item(row, 4)->text());
    ui->lineEdit_8->setText(ui->tableWidget->item(row, 1)->text());
    ui->dateEdit->setDate(QDate::fromString(ui->tableWidget->item(row, 8)->text(), "yyyy-MM-dd"));

    QString genre = ui->tableWidget->item(row, 2)->text();
    ui->radioButton->setChecked(genre == "Homme");
    ui->radioButton_2->setChecked(genre == "Femme");
}

void MainWindow::readSerialData()
{
    QByteArray data = A.read_from_arduino();
    qDebug() << "RAW SERIAL DATA:" << data;

    for (char c : data)
    {
        if (c >= '0' && c <= '9') {
            ui->lineEdit_29->insert(QString(c));
        }
        else if (c == '*') {
            ui->lineEdit_29->backspace();
        }
        else if (c == '#') {
            ui->lineEdit_29->clear();
        }
    }
}

