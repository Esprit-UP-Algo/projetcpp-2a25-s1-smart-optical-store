#include "gclient1.h"

// Qt includes
#include <QAction>
#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QDesktopServices>
#include <QEvent>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPageSize>
#include <QPrinter>
#include <QProgressBar>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextTable>
#include <QUrl>

// Project includes
#include "dashboardwindow.h"
#include "fournisseurwindow.h"
#include "gestionemploye00.h"
#include "mainwindow.h"
#include "saleswindow.h"
#include "windowmanager.h"

// UI generated header (must be included after the class definition)
#include "ui_gclient1.h"

// No using namespace QtCharts; - we'll use QtCharts:: prefix for all chart classes

// Initialize static instance pointer
Gclient1* Gclient1::instance = nullptr;

Gclient1* Gclient1::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new Gclient1(parent);
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

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients),
    isEditing(false),
    currentClientId(-1),
    genderChartView(nullptr),
    ageChartView(nullptr),
    addressChartView(nullptr),
    lblAgeDistribution(nullptr),
    lblAddressDistribution(nullptr)
{
    ui->setupUi(this);

    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion Clients");

    // Redimensionner la fenêtre
    this->resize(1200, 800);
    this->showMaximized();

    // Configuration de la table
    if (ui->tableWidgetClients) {
        ui->tableWidgetClients->setColumnCount(9); // Updated to match UI form
        ui->tableWidgetClients->setHorizontalHeaderLabels(
            QStringList() << "ID" << "Nom" << "Prénom" << "Date Naissance"
                          << "Sexe" << "Adresse" << "Téléphone" << "Email" << "Date Inscription");
        ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidgetClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidgetClients->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // Configuration du formulaire
    if (ui->lineEditID) {
        ui->lineEditID->setReadOnly(true);
        ui->lineEditID->setPlaceholderText("Auto-généré");
    }
    if (ui->dateEditNaissance) {
        ui->dateEditNaissance->setDate(QDate::currentDate());
        ui->dateEditNaissance->setCalendarPopup(true);
    }

    // Configuration du ComboBox Sexe
    if (ui->comboBoxSexe) {
        ui->comboBoxSexe->clear();
        ui->comboBoxSexe->addItem("Homme");
        ui->comboBoxSexe->addItem("Femme");
    }

    // Charger le logo
    QString logoPath = "./smart_logo.png";
    QPixmap logo(logoPath);

    if (!logo.isNull() && ui->labelLogoTopRight) {
        ui->labelLogoTopRight->setPixmap(logo);
        ui->labelLogoTopRight->setScaledContents(true);
        ui->labelLogoTopRight->setMaximumSize(50, 50);
        
        // Configuration du logo cliquable
        ui->labelLogoTopRight->raise();
        ui->labelLogoTopRight->setCursor(Qt::PointingHandCursor);
        ui->labelLogoTopRight->installEventFilter(this);
        ui->labelLogoTopRight->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        ui->labelLogoTopRight->setStyleSheet(
            "QLabel { border: 2px solid #48a4d6; border-radius: 6px; padding: 2px; }"
            "QLabel:hover { border-color: #5ab5e3; }"
        );
    } else {
        qDebug() << "Erreur: Impossible de charger le logo à partir de" << logoPath;
    }

    // Connecter les signaux
    if (ui->lineEditSearch) {
        connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &Gclient1::on_lineEditSearch_textChanged);
    }
    
    if (ui->comboBoxTri) {
        connect(ui->comboBoxTri, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &Gclient1::on_comboBoxTri_currentIndexChanged);
    }
    
    if (ui->tableWidgetClients) {
        connect(ui->tableWidgetClients, &QTableWidget::cellDoubleClicked,
                this, &Gclient1::on_tableWidgetClients_cellDoubleClicked);
    }
    
    if (ui->tabWidgetMain) {
        connect(ui->tabWidgetMain, &QTabWidget::currentChanged,
                this, &Gclient1::on_tabWidgetMain_currentChanged);
    }
    
    if (ui->btnExport) {
        connect(ui->btnExport, &QPushButton::clicked, this, &Gclient1::on_btnExport_clicked);
    }

    // Initialiser le formulaire
    clearForm();
    
    // Load clients data on startup
    loadClients();
    
    // Setup the simple controls table
    setupSimpleControlsTable();
    
    qDebug() << "✅ Interface GestionClients initialisée avec succès";
}

Gclient1::~Gclient1()
{
    // Delete chart views if they exist
    if (genderChartView) {
        delete genderChartView->chart();
        delete genderChartView;
    }
    if (ageChartView) {
        delete ageChartView->chart();
        delete ageChartView;
    }
    if (addressChartView) {
        delete addressChartView->chart();
        delete addressChartView;
    }
    
    delete ui;
}

void Gclient1::loadClients()
{
    refreshTable();
}

void Gclient1::refreshTable(const QString &searchText, int sortIndex)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Base de données non connectée lors du rafraîchissement";
        return;
    }

    QSqlQuery query(db);
    QString sqlQuery = "SELECT ID_CLIENT, NOM, PRENOM, D_NAISSANCE, SEXE, ADRESSE, TELEPHONE, EMAIL FROM CLIENTS WHERE 1=1";

    if (!searchText.isEmpty()) {
        sqlQuery += " AND (UPPER(NOM) LIKE UPPER(:search) OR UPPER(PRENOM) LIKE UPPER(:search) "
                    "OR TO_CHAR(ID_CLIENT) LIKE :search OR TELEPHONE LIKE :search)";
    }

    switch (sortIndex) {
    case 0: sqlQuery += " ORDER BY NOM ASC"; break;
    case 1: sqlQuery += " ORDER BY NOM DESC"; break;
    case 2: sqlQuery += " ORDER BY ID_CLIENT ASC"; break;
    case 3: sqlQuery += " ORDER BY ID_CLIENT DESC"; break;
    default: sqlQuery += " ORDER BY ID_CLIENT ASC"; break;
    }

    if (!query.prepare(sqlQuery)) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la préparation de la requête: " + query.lastError().text());
        qDebug() << "Erreur de préparation SQL:" << query.lastError().text();
        return;
    }

    if (!searchText.isEmpty()) {
        QString searchPattern = "%" + searchText + "%";
        query.bindValue(":search", searchPattern);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors du chargement des clients: " + query.lastError().text());
        qDebug() << "Erreur SQL:" << query.lastError().text();
        qDebug() << "Requête SQL:" << sqlQuery;
        return;
    }

    ui->tableWidgetClients->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tableWidgetClients->insertRow(row);
        ui->tableWidgetClients->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidgetClients->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidgetClients->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

        QVariant dateVar = query.value(3);
        QString dateStr = "";
        if (!dateVar.isNull()) {
            QDate date = dateVar.toDate();
            if (date.isValid()) dateStr = date.toString("dd/MM/yyyy");
        }
        ui->tableWidgetClients->setItem(row, 3, new QTableWidgetItem(dateStr));
        ui->tableWidgetClients->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidgetClients->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidgetClients->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidgetClients->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
        row++;
    }

    qDebug() << "✅ " << row << " clients chargés";
}

void Gclient1::on_btnSave_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "La connexion à la base de données n'est pas ouverte. Veuillez vérifier la connexion.");
        return;
    }

    QString nom = ui->lineEditNom->text().trimmed();
    QString prenom = ui->lineEditPrenom->text().trimmed();
    QString telephone = ui->lineEditTelephone->text().trimmed();
    QString email = ui->lineEditEmail->text().trimmed();

    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom est obligatoire!");
        ui->lineEditNom->setFocus();
        return;
    }

    if (prenom.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le prénom est obligatoire!");
        ui->lineEditPrenom->setFocus();
        return;
    }

    // ✅ Contrôle de saisie téléphone (8 chiffres)
    QRegularExpression regexTel("^\\d{8}$");
    if (!regexTel.match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        ui->lineEditTelephone->setFocus();
        return;
    }

    // ✅ Contrôle de saisie email (doit contenir '@')
    if (!email.contains('@')) {
        QMessageBox::warning(this, "Validation", "L'adresse e-mail doit contenir le caractère '@'.");
        ui->lineEditEmail->setFocus();
        return;
    }

    QSqlQuery query(db);

    if (isEditing && currentClientId > 0) {
        query.prepare("UPDATE CLIENTS SET NOM = :nom, PRENOM = :prenom, D_NAISSANCE = :dateNaissance, "
                      "SEXE = :sexe, ADRESSE = :adresse, EMAIL = :email, TELEPHONE = :telephone "
                      "WHERE ID_CLIENT = :id");
        query.bindValue(":id", currentClientId);
    } else {
        query.prepare("INSERT INTO CLIENTS (NOM, PRENOM, D_NAISSANCE, SEXE, ADRESSE, EMAIL, TELEPHONE) "
                      "VALUES (:nom, :prenom, :dateNaissance, :sexe, :adresse, :email, :telephone)");
    }

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", ui->dateEditNaissance->date());
    query.bindValue(":sexe", ui->comboBoxSexe->currentText().trimmed());
    query.bindValue(":adresse", ui->lineEditAdresse->text().trimmed());
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement: " + query.lastError().text());
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return;
    }

    QString message = isEditing ? "Client modifié avec succès!" : "Client ajouté avec succès!";
    QMessageBox::information(this, "Succès", message);

    refreshTable(ui->lineEditSearch->text(), ui->comboBoxTri->currentIndex());
    clearForm();
    ui->tabWidgetMain->setCurrentIndex(0);
}

void Gclient1::on_btnCancel_clicked()
{
    clearForm();
    ui->tabWidgetMain->setCurrentIndex(0);
}

void Gclient1::on_btnDelete_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "La connexion à la base de données n'est pas ouverte. Veuillez vérifier la connexion.");
        return;
    }

    int currentRow = ui->tableWidgetClients->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un client à supprimer!");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidgetClients->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Attention", "Impossible de récupérer l'ID du client!");
        return;
    }

    int clientId = idItem->text().toInt();
    QString nom = ui->tableWidgetClients->item(currentRow, 1)->text();
    QString prenom = ui->tableWidgetClients->item(currentRow, 2)->text();

    int ret = QMessageBox::question(this, "Confirmation",
                                    QString("Êtes-vous sûr de vouloir supprimer le client %1 %2 (ID: %3) ?")
                                        .arg(prenom).arg(nom).arg(clientId),
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT = :id");
        query.bindValue(":id", clientId);

        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression: " + query.lastError().text());
            qDebug() << "Erreur SQL:" << query.lastError().text();
            return;
        }

        QMessageBox::information(this, "Succès", "Client supprimé avec succès!");
        refreshTable(ui->lineEditSearch->text(), ui->comboBoxTri->currentIndex());
    }
}

void Gclient1::on_tableWidgetClients_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    fillForm(row);
    ui->tabWidgetMain->setCurrentIndex(1);
}

void Gclient1::on_lineEditSearch_textChanged(const QString &text)
{
    refreshTable(text, ui->comboBoxTri->currentIndex());
}

void Gclient1::on_comboBoxTri_currentIndexChanged(int index)
{
    refreshTable(ui->lineEditSearch->text(), index);
}

void Gclient1::on_tabWidgetMain_currentChanged(int index)
{
    if (ui->tabWidgetMain->widget(index) == ui->tabDashboard) {
        updateDashboard();
    }
}

void Gclient1::clearForm()
{
    isEditing = false;
    currentClientId = -1;
    ui->lineEditID->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->dateEditNaissance->setDate(QDate::currentDate());
    ui->comboBoxSexe->setCurrentIndex(0);
    ui->lineEditAdresse->clear();
    ui->lineEditTelephone->clear();
    ui->lineEditEmail->clear();
    ui->lineEditNom->setFocus();
}

void Gclient1::fillForm(int row)
{
    if (row < 0 || row >= ui->tableWidgetClients->rowCount()) return;

    isEditing = true;

    QTableWidgetItem *idItem = ui->tableWidgetClients->item(row, 0);
    if (idItem) {
        currentClientId = idItem->text().toInt();
        ui->lineEditID->setText(idItem->text());
    }

    QTableWidgetItem *item = ui->tableWidgetClients->item(row, 1);
    if (item) ui->lineEditNom->setText(item->text());

    item = ui->tableWidgetClients->item(row, 2);
    if (item) ui->lineEditPrenom->setText(item->text());

    item = ui->tableWidgetClients->item(row, 3);
    if (item) {
        QDate date = QDate::fromString(item->text(), "dd/MM/yyyy");
        if (date.isValid()) ui->dateEditNaissance->setDate(date);
    }

    item = ui->tableWidgetClients->item(row, 4);
    if (item) {
        QString sexeValue = item->text().trimmed();
        int index = ui->comboBoxSexe->findText(sexeValue);
        ui->comboBoxSexe->setCurrentIndex(index >= 0 ? index : 0);
    }

    item = ui->tableWidgetClients->item(row, 5);
    if (item) ui->lineEditAdresse->setText(item->text());

    item = ui->tableWidgetClients->item(row, 6);
    if (item) ui->lineEditTelephone->setText(item->text());

    item = ui->tableWidgetClients->item(row, 7);
    if (item) ui->lineEditEmail->setText(item->text());
}

void Gclient1::on_b1_clicked()
{
    MainWindow::getInstance();
    this->close();
}

void Gclient1::on_b2_clicked()
{
    SalesWindow::getInstance();
    this->close();
}

void Gclient1::on_b3_clicked()
{
    gestionemploye00::getInstance();
    this->close();
}

void Gclient1::on_b4_clicked()
{
    // Already in clients window; keep focus
    this->raise();
    this->activateWindow();
}

void Gclient1::on_b5_clicked()
{
    this->hide();
    FournisseurWindow::getInstance()->show();
    FournisseurWindow::getInstance()->raise();
    FournisseurWindow::getInstance()->activateWindow();
}

void Gclient1::on_btnExport_clicked()
{
    if (ui->tableWidgetClients->rowCount() == 0) {
        QMessageBox::warning(this, "Export PDF", "Aucune donnée à exporter !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", 
                                                  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + 
                                                  "/liste_clients.pdf", 
                                                  "Fichiers PDF (*.pdf)");
    
    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);
    
    // Style du document
    QTextCharFormat titleFormat;
    titleFormat.setFontPointSize(16);
    titleFormat.setFontWeight(QFont::Bold);
    titleFormat.setForeground(Qt::darkBlue);
    
    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(10);
    headerFormat.setFontWeight(QFont::Bold);
    headerFormat.setBackground(Qt::lightGray);
    
    QTextCharFormat cellFormat;
    cellFormat.setFontPointSize(9);
    
    // Titre
    cursor.insertText("Liste des Clients\n", titleFormat);
    cursor.insertText("Date d'édition: " + QDate::currentDate().toString("dd/MM/yyyy") + "\n\n");
    
    // Création du tableau
    int columns = ui->tableWidgetClients->columnCount();
    int rows = ui->tableWidgetClients->rowCount();
    
    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setBorder(1);
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(4);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    
    QTextTable *table = cursor.insertTable(rows + 1, columns, tableFormat);
    
    // En-têtes
    for (int col = 0; col < columns; ++col) {
        QTableWidgetItem *header = ui->tableWidgetClients->horizontalHeaderItem(col);
        if (header) {
            QTextTableCell cell = table->cellAt(0, col);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText(header->text(), headerFormat);
        }
    }
    
    // Données
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QTableWidgetItem *item = ui->tableWidgetClients->item(row, col);
            if (item) {
                QTextTableCell cell = table->cellAt(row + 1, col);
                QTextCursor cellCursor = cell.firstCursorPosition();
                cellCursor.insertText(item->text(), cellFormat);
            }
        }
    }
    
    // Centrer le tableau
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("\n");
    
    // Exporter en PDF
    doc.print(&printer);
    
    QMessageBox::information(this, "Export PDF", "Le fichier PDF a été enregistré avec succès !");
}

bool Gclient1::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->labelLogoTopRight && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            DashboardWindow::getInstance();
            this->close();
            return true;
        }
    }
    
    // Handle custom styling for controls table
    if (obj == ui->tableControles->viewport() && event->type() == QEvent::Paint) {
        // Let the default painting happen first
        QApplication::sendEvent(obj, event);
        
        // Apply our custom styling
        QPainter painter(ui->tableControles->viewport());
        for (int row = 0; row < ui->tableControles->rowCount(); ++row) {
            for (int col = 0; col < ui->tableControles->columnCount(); ++col) {
                if (QTableWidgetItem *item = ui->tableControles->item(row, col)) {
                    QRect rect = ui->tableControles->visualItemRect(item);
                    QString status = item->data(Qt::UserRole + 1).toString();
                    
                    if (status == "overdue") {
                        painter.fillRect(rect, QColor(254, 226, 226, 120));
                    } else if (status == "soon") {
                        painter.fillRect(rect, QColor(254, 243, 199, 120));
                    } else {
                        painter.fillRect(rect, QColor(220, 252, 231, 120));
                    }
                }
            }
        }
        return true;
    }
    
    return QMainWindow::eventFilter(obj, event);
}

void Gclient1::updateStatistics()
{
    qDebug() << "Updating statistics...";
    
    try {
        // Clear existing widgets from the statistics tab
        QLayout* layout = ui->tabStatistics->layout();
        if (!layout) {
            layout = new QVBoxLayout(ui->tabStatistics);
        } else {
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr) {
                if (item->widget()) {
                    item->widget()->deleteLater();
                }
                delete item;
            }
        }

        // Set up main layout
        layout->setSpacing(20);
        layout->setContentsMargins(20, 20, 20, 20);

        // Create a scroll area
        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::NoFrame);
        
        // Create a widget to contain the scroll area's contents
        QWidget *scrollContent = new QWidget();
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setSpacing(20);
        scrollLayout->setContentsMargins(10, 10, 10, 10);

        // Style for the statistics boxes
        QString boxStyle = "QFrame {"
                        "background-color: #ffffff;"
                        "border-radius: 10px;"
                        "border: 1px solid #e0e0e0;"
                        "padding: 20px;"
                        "box-shadow: 0 2px 5px rgba(0,0,0,0.05);"
                        "}";
        
        QString titleStyle = "QLabel {"
                           "font-weight: 600;"
                           "font-size: 16px;"
                           "color: #2c3e50;"
                           "margin-bottom: 15px;"
                           "padding-bottom: 8px;"
                           "border-bottom: 2px solid #f0f0f0;"
                           "}";
                           
        QString valueStyle = "QLabel {"
                           "font-size: 24px;"
                           "font-weight: 600;"
                           "color: #2c3e50;"
                           "}";
                           
        QString labelStyle = "QLabel {"
                           "font-size: 12px;"
                           "color: #7f8c8d;"
                           "}";

        // Summary Cards
        QHBoxLayout *summaryLayout = new QHBoxLayout();
        summaryLayout->setSpacing(15);
        
        // Total Clients Card
        QFrame *totalClientsCard = createStatCard(
            "TOTAL CLIENTS", 
            QString::number(getTotalClients()), 
            "👥", 
            QColor("#3498db")
        );
        summaryLayout->addWidget(totalClientsCard);
        
        // Active Clients Card
        QFrame *activeClientsCard = createStatCard(
            "CLIENTS ACTIFS", 
            QString::number(getActiveClients()), 
            "✓", 
            QColor("#2ecc71")
        );
        summaryLayout->addWidget(activeClientsCard);
        
        // New This Month Card
        QFrame *newClientsCard = createStatCard(
            "NOUVEAUX CE MOIS", 
            QString::number(getNewClientsThisMonth()), 
            "🆕", 
            QColor("#e67e22")
        );
        summaryLayout->addWidget(newClientsCard);
        
        // Inactive Clients Card
        QFrame *inactiveClientsCard = createStatCard(
            "CLIENTS INACTIFS", 
            QString::number(getInactiveClientCount()), 
            "⏸", 
            QColor("#95a5a6")
        );
        summaryLayout->addWidget(inactiveClientsCard);
        
        scrollLayout->addLayout(summaryLayout);
        
        // Gender Distribution Box
        QFrame *genderBox = new QFrame();
        genderBox->setStyleSheet(boxStyle);
        QVBoxLayout *genderLayout = new QVBoxLayout(genderBox);
        
        QLabel *genderTitle = new QLabel("📊 RÉPARTITION PAR GENRE");
        genderTitle->setStyleSheet(titleStyle);
        genderLayout->addWidget(genderTitle);
        
        // Get and display gender distribution
        QMap<QString, int> genderDist = getGenderDistribution();
        int total = 0;
        for (int count : genderDist) {
            total += count;
        }
        
        // Add total count
        QLabel *totalLabel = new QLabel(QString("Total: %1 clients").arg(total));
        totalLabel->setStyleSheet("color: #6c757d; font-size: 13px; margin-bottom: 15px; font-family: 'Segoe UI', Arial, sans-serif;");
        genderLayout->addWidget(totalLabel);
        
        // Sort by count (descending)
        QList<QPair<QString, int>> sortedGenders;
        for (auto it = genderDist.begin(); it != genderDist.end(); ++it) {
            sortedGenders.append(qMakePair(it.key(), it.value()));
        }
        std::sort(sortedGenders.begin(), sortedGenders.end(), 
                 [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                     return a.second > b.second;
                 });
        
        // Display sorted genders with progress bars
        for (const auto &pair : sortedGenders) {
            double percentage = total > 0 ? (pair.second * 100.0) / total : 0;
            QString gender = pair.first.isEmpty() ? "Not Specified" : pair.first;
            
            QHBoxLayout *itemLayout = new QHBoxLayout();
            itemLayout->setSpacing(10);
            
            // Gender label with count
            QLabel *genderLabel = new QLabel(QString("%1 (%2)").arg(gender).arg(pair.second));
            genderLabel->setStyleSheet("color: #2c3e50; font-size: 13px; min-width: 120px;");
            
            // Percentage label
            QLabel *percentLabel = new QLabel(QString("%1%").arg(percentage, 0, 'f', 1));
            percentLabel->setStyleSheet("color: #7f8c8d; font-size: 12px; min-width: 40px; text-align: right;");
            
            // Progress bar with custom style
            QProgressBar *progressBar = new QProgressBar();
            progressBar->setMaximum(100);
            progressBar->setTextVisible(false);
            progressBar->setValue(static_cast<int>(percentage));
            
            // Set progress bar color based on gender
            QString progressStyle = 
                "QProgressBar { "
                "  border: 1px solid #e0e0e0; "
                "  border-radius: 4px; "
                "  background-color: #f8f9fa; "
                "  height: 10px; "
                "  margin: 2px 0; "
                "} "
                "QProgressBar::chunk { "
                "  background-color: %1; "
                "  border-radius: 3px; "
                "}";
                
            if (gender.contains("Femme", Qt::CaseInsensitive)) {
                progressBar->setStyleSheet(progressStyle.arg("#e91e63"));
            } else if (gender.contains("Homme", Qt::CaseInsensitive)) {
                progressBar->setStyleSheet(progressStyle.arg("#2196f3"));
            } else {
                progressBar->setStyleSheet(progressStyle.arg("#9c27b0"));
            }
            
            itemLayout->addWidget(genderLabel, 1);
            itemLayout->addWidget(progressBar, 3);
            itemLayout->addWidget(percentLabel);
            
            genderLayout->addLayout(itemLayout);
        }

        // Age Distribution Box
        QFrame *ageBox = new QFrame();
        ageBox->setStyleSheet(boxStyle);
        QVBoxLayout *ageLayout = new QVBoxLayout(ageBox);
        
        QLabel *ageTitle = new QLabel("👥 RÉPARTITION PAR ÂGE");
        ageTitle->setStyleSheet(titleStyle);
        ageLayout->addWidget(ageTitle);
        
        // Get and display age distribution
        QMap<QString, double> ageDist = getAgeDistribution();
        
        // Sort age groups in a logical order
        QStringList ageGroups = {"0-17", "18-25", "26-35", "36-50", "51-65", "65+"};
        
        for (const QString &ageGroup : ageGroups) {
            if (!ageDist.contains(ageGroup)) continue;
            
            double percentage = ageDist[ageGroup];
            
            QHBoxLayout *itemLayout = new QHBoxLayout();
            itemLayout->setSpacing(10);
            
            // Age group label
            QLabel *ageLabel = new QLabel(ageGroup + " years");
            ageLabel->setStyleSheet("color: #2c3e50; font-size: 13px; min-width: 100px;");
            
            // Percentage label
            QLabel *percentLabel = new QLabel(QString("%1%").arg(percentage, 0, 'f', 1));
            percentLabel->setStyleSheet("color: #7f8c8d; font-size: 12px; min-width: 40px; text-align: right;");
            
            // Progress bar with gradient color based on age
            QProgressBar *progressBar = new QProgressBar();
            progressBar->setMaximum(100);
            progressBar->setTextVisible(false);
            progressBar->setValue(static_cast<int>(percentage));
            
            // Calculate color based on age group
            QString color;
            if (ageGroup == "0-17") color = "#3498db";
            else if (ageGroup == "18-25") color = "#2ecc71";
            else if (ageGroup == "26-35") color = "#f1c40f";
            else if (ageGroup == "36-50") color = "#e67e22";
            else if (ageGroup == "51-65") color = "#e74c3c";
            else color = "#9b59b6";
            
            progressBar->setStyleSheet(
                "QProgressBar { "
                "  border: 1px solid #e0e0e0; "
                "  border-radius: 4px; "
                "  background-color: #f8f9fa; "
                "  height: 10px; "
                "  margin: 2px 0; "
                "} "
                "QProgressBar::chunk { "
                "  background-color: " + color + "; "
                "  border-radius: 3px; "
                "}");
            
            itemLayout->addWidget(ageLabel, 1);
            itemLayout->addWidget(progressBar, 3);
            itemLayout->addWidget(percentLabel);
            
            ageLayout->addLayout(itemLayout);
        }

        // Client Growth Chart (Last 6 Months)
        QFrame *growthBox = new QFrame();
        growthBox->setStyleSheet(boxStyle);
        QVBoxLayout *growthLayout = new QVBoxLayout(growthBox);
        
        QLabel *growthTitle = new QLabel("📈 ÉVOLUTION DES CLIENTS (6 DERNIERS MOIS)");
        growthTitle->setStyleSheet(titleStyle);
        growthLayout->addWidget(growthTitle);
        
        // Get client growth data
        QMap<QString, int> growthData = getClientGrowthData();
        
        if (!growthData.isEmpty()) {
            // Create a chart view
            QChartView *chartView = new QChartView();
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setMinimumHeight(300);
            
            QChart *chart = new QChart();
            chart->setTitle("Client Growth Over Time");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->legend()->setVisible(false);
            
            // Create a line series
            QLineSeries *series = new QLineSeries();
            
            // Add data points
            for (auto it = growthData.begin(); it != growthData.end(); ++it) {
                series->append(QDateTime::fromString(it.key(), "MMM yy").toMSecsSinceEpoch(), it.value());
            }
            
            // Add series to chart
            chart->addSeries(series);
            
            // Customize the chart appearance
            chart->createDefaultAxes();
            
            // Create and configure axes
            QDateTimeAxis *axisX = new QDateTimeAxis();
            axisX->setFormat("MMM yy");
            axisX->setTitleText("Month");
            
            QValueAxis *axisY = new QValueAxis();
            axisY->setLabelFormat("%d");
            axisY->setTitleText("Number of Clients");
            
            // Add axes to chart
            chart->addAxis(axisX, Qt::AlignBottom);
            chart->addAxis(axisY, Qt::AlignLeft);
            
            // Attach axes to series
            series->attachAxis(axisX);
            series->attachAxis(axisY);
            
            // Set chart theme
            chart->setTheme(QChart::ChartThemeLight);
            
            // Apply custom colors
            QLinearGradient gradient(0, 0, 0, 1);
            gradient.setColorAt(0.0, QColor("#3498db"));
            gradient.setColorAt(1.0, QColor("#2980b9"));
            gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
            
            series->setPen(QPen(QBrush("#3498db"), 2));
            series->setBrush(gradient);
            
            // Set chart to the view
            chartView->setChart(chart);
            growthLayout->addWidget(chartView);
        } else {
            QLabel *noDataLabel = new QLabel("No growth data available");
            noDataLabel->setStyleSheet("color: #7f8c8d; font-style: italic;");
            noDataLabel->setAlignment(Qt::AlignCenter);
            growthLayout->addWidget(noDataLabel);
        }

        // Add boxes to scroll layout in a grid
        QGridLayout *gridLayout = new QGridLayout();
        gridLayout->setSpacing(20);
        
        // First row: Gender and Age distribution
        gridLayout->addWidget(genderBox, 0, 0);
        gridLayout->addWidget(ageBox, 0, 1);
        
        // Second row: Growth chart (full width)
        gridLayout->addWidget(growthBox, 1, 0, 1, 2);
        
        // Set column stretch
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        
        scrollLayout->addLayout(gridLayout);
        scrollLayout->addStretch();

        // Set up the scroll area
        scrollArea->setWidget(scrollContent);
        
        // Add scroll area to main layout
        layout->addWidget(scrollArea);

        // Force a refresh of the layout
        ui->tabStatistics->layout()->activate();
        
        qDebug() << "Statistics updated successfully";
        
    } catch (const std::exception &e) {
        qCritical() << "Error updating statistics:" << e.what();
        QMessageBox::critical(this, "Error", 
            tr("An error occurred while updating statistics. Please try again."));
    } catch (...) {
        qCritical() << "Unknown error updating statistics";
        QMessageBox::critical(this, "Error", 
            tr("An unknown error occurred while updating statistics."));
    }
}

void Gclient1::updateDashboardCards()
{
    QHBoxLayout *cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(15);
    cardsLayout->setContentsMargins(0, 0, 0, 20);
    
    // Card 1: Total Clients
    int totalClients = getTotalClients();
    QFrame *totalClientsCard = createStatCard(
        "TOTAL CLIENTS", 
        QString::number(totalClients), 
        "👥", 
        QColor("#2ecc71")
    );
    cardsLayout->addWidget(totalClientsCard);
    
    // Card 2: Active Clients
    int activeClients = getActiveClients();
    QFrame *activeClientsCard = createStatCard(
        "CLIENTS ACTIFS", 
        QString::number(activeClients), 
        "✓", 
        QColor("#3498db")
    );
    cardsLayout->addWidget(activeClientsCard);
    
    // Card 3: New Clients This Month
    int newClients = getNewClientsThisMonth();
    QFrame *newClientsCard = createStatCard(
        "NOUVEAUX CLIENTS", 
        QString::number(newClients), 
        "🆕", 
        QColor("#e67e22")
    );
    cardsLayout->addWidget(newClientsCard);
    
    // Card 4: Appointments
    int appointments = getAppointmentsCount();
    QFrame *appointmentsCard = createStatCard(
        "RENDEZ-VOUS", 
        QString::number(appointments), 
        "📅", 
        QColor("#9b59b6")
    );
    cardsLayout->addWidget(appointmentsCard);
    
    // Create a container widget for the scroll area
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->addLayout(cardsLayout);
    scrollLayout->addStretch();
    
    // Set up the scroll area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);
    
    // Clear existing content and add the scroll area
    QLayoutItem* child;
    while ((child = ui->tabStatistics->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    
    // Add the scroll area to the tab
    ui->tabStatistics->layout()->addWidget(scrollArea);
}

QFrame* Gclient1::createStatCard(const QString &title, const QString &value, const QString &icon, const QColor &color)
{
    QFrame *card = new QFrame();
    card->setMinimumHeight(120);
    card->setStyleSheet(
        QString("QFrame { background-color: %1; border-radius: 10px; padding: 15px; color: white; }"
               "QLabel#value { font-size: 28px; font-weight: bold; }"
               "QLabel#title { font-size: 14px; margin-top: 5px; }"
               "QLabel#icon { font-size: 24px; }").arg(color.name())
    );
    
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(10);
    
    // Add icon
    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setObjectName("icon");
    iconLabel->setAlignment(Qt::AlignRight);
    
    // Add value
    QLabel *valueLabel = new QLabel(value);
    valueLabel->setObjectName("value");
    
    // Add title
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setObjectName("title");
    
    // Add widgets to layout
    layout->addWidget(iconLabel);
    layout->addStretch();
    layout->addWidget(valueLabel);
    layout->addWidget(titleLabel);
    
    return card;
}

void Gclient1::applyShadowEffect(QWidget *widget)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(widget);
    effect->setBlurRadius(15);
    effect->setXOffset(0);
    effect->setYOffset(5);
    effect->setColor(QColor(0, 0, 0, 30));
    widget->setGraphicsEffect(effect);
}

void Gclient1::updateDashboard()
{
    // Initialize dashboard UI if not already done
    if (!lblTotalClientsValue) {
        setupDashboardUI();
    }

    // Update dashboard cards with current data
    updateDashboardCards();

    // Update all charts
    updateCharts();

    // Update statistics
    updateStatistics();

    // Update client growth chart
    updateClientGrowthChart();

    // Update gender distribution chart
    updateGenderDistributionChart();

    // Update status bar with last update time
    updateStatusBar();
}

void Gclient1::setupDashboardUI()
{
    // Create a scroll area for the dashboard
    QScrollArea *scrollArea = new QScrollArea(ui->tabDashboard);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // Create a widget to hold the dashboard content
    QWidget *dashboardContent = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(dashboardContent);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Create a container for the statistics cards
    QWidget *statsContainer = new QWidget();
    QHBoxLayout *statsLayout = new QHBoxLayout(statsContainer);
    statsLayout->setSpacing(15);
    statsLayout->setContentsMargins(0, 0, 0, 0);

    // Add stats cards to the layout
    statsLayout->addWidget(createStatCard("Clients totaux", QString::number(getTotalClients()), "👥", QColor("#3498db")));
    statsLayout->addWidget(createStatCard("Clients actifs", QString::number(getActiveClients()), "✅", QColor("#2ecc71")));
    statsLayout->addWidget(createStatCard("Nouveaux clients", QString::number(getNewClientsThisMonth()), "🆕", QColor("#e74c3c")));
    statsLayout->addWidget(createStatCard("Rendez-vous", QString::number(getAppointmentsCount()), "📅", QColor("#9b59b6")));

    // Add stats container to main layout
    mainLayout->addWidget(statsContainer);

    // Create a container for the charts
    QWidget *chartContainer = new QWidget();
    QVBoxLayout *chartLayout = new QVBoxLayout(chartContainer);
    chartLayout->setSpacing(20);
    chartLayout->setContentsMargins(0, 0, 0, 0);

    // Initialize chart views
    genderChartView = new QChartView(this);
    ageChartView = new QChartView(this);
    addressChartView = new QChartView(this);

    // Add chart views to layout
    chartLayout->addWidget(genderChartView);
    chartLayout->addWidget(ageChartView);
    chartLayout->addWidget(addressChartView);

    // Add chart container to main layout
    mainLayout->addWidget(chartContainer);

    // Set the scroll area's widget
    scrollArea->setWidget(dashboardContent);

    // Add the scroll area to the dashboard tab
    QVBoxLayout *dashboardLayout = new QVBoxLayout(ui->tabDashboard);
    dashboardLayout->setContentsMargins(0, 0, 0, 0);
    dashboardLayout->addWidget(scrollArea);

    // Store references to the labels for later updates
    lblTotalClientsValue = statsContainer->findChild<QLabel*>("lblTotalClientsValue");
}

void Gclient1::updateCharts()
{
    updateGenderChart();
    updateAgeDistributionChart();
    updateAddressDistributionChart();
}

void Gclient1::updateGenderChart()
{
    if (!genderChartView) {
        genderChartView = new QChartView(this);
        genderChartView->setRenderHint(QPainter::Antialiasing);
    }

    // Get gender distribution data
    QMap<QString, int> genderData = getGenderDistribution();

    // Create chart and series
    auto *chart = new QChart();
    chart->setTitle("Répartition par sexe");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *series = new QPieSeries();

    // Add data to series
    for (auto it = genderData.constBegin(); it != genderData.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    // Add series to chart
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Update the chart view
    genderChartView->setChart(chart);
}

void Gclient1::updateAgeDistributionChart()
{
    if (!ageChartView) {
        ageChartView = new QChartView(this);
        ageChartView->setRenderHint(QPainter::Antialiasing);
    }

    // Get age distribution data
    QMap<QString, double> ageData = getAgeDistribution();

    // Create chart and series
    auto *chart = new QChart();
    chart->setTitle("Répartition par âge");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *series = new QBarSeries();
    auto *set = new QBarSet("Tranches d'âge");

    // Add data to series
    QStringList categories;
    for (auto it = ageData.constBegin(); it != ageData.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    series->append(set);
    chart->addSeries(series);

    // Create axis
    auto *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de clients");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Update the chart view
    ageChartView->setChart(chart);
}

void Gclient1::updateAddressDistributionChart()
{
    if (!addressChartView) {
        addressChartView = new QChartView(this);
        addressChartView->setRenderHint(QPainter::Antialiasing);
    }

    // Get address distribution data
    QMap<QString, double> addressData = getAddressDistribution();

    // Create chart and series
    auto *chart = new QChart();
    chart->setTitle("Répartition par adresse");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *series = new QPieSeries();

    // Add data to series
    for (auto it = addressData.constBegin(); it != addressData.constEnd(); ++it) {
        series->append(it.key() + " (" + QString::number(it.value(), 'f', 1) + "%)", it.value());
    }

    // Add series to chart
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Update the chart view
    addressChartView->setChart(chart);
}

void Gclient1::updateClientGrowthChart()
{
    QChartView *chartView = ui->tabStatistics->findChild<QChartView*>();
    if (!chartView) return;
    
    QChart *chart = new QChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setBackgroundVisible(false);
    chart->legend()->setVisible(false);
    
    // Create line series for client growth
    QLineSeries *series = new QLineSeries();
    
    // Get client growth data (example data)
    QMap<QString, int> growthData = getClientGrowthData();
    
    // Add data points to the series
    for (auto it = growthData.begin(); it != growthData.end(); ++it) {
        series->append(it.key().toDouble(), it.value());
    }
    
    // Customize the series
    series->setName("Clients");
    series->setColor(QColor("#3498db"));
    series->setPointsVisible(true);
    
    // Add series to chart
    chart->addSeries(series);
    
    // Create axes
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de clients");
    axisY->setLabelFormat("%d");
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for (const QString &month : growthData.keys()) {
        axisX->append(month);
    }
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    
    // Update the chart view
    chartView->setChart(chart);
}

void Gclient1::updateGenderDistributionChart()
{
    QChartView *chartView = ui->tabStatistics->findChild<QChartView*>(QString(), Qt::FindDirectChildrenOnly);
    if (!chartView) return;
    
    QChart *chart = new QChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setBackgroundVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create pie series for gender distribution
    QPieSeries *series = new QPieSeries();
    
    // Get gender distribution data
    QMap<QString, int> genderData = getGenderDistribution();
    
    // Add data to the series
    for (auto it = genderData.begin(); it != genderData.end(); ++it) {
        QPieSlice *slice = series->append(it.key() + " " + QString::number(it.value()), it.value());
        slice->setLabelVisible(true);
        
        // Set colors based on gender
        if (it.key().contains("Femme", Qt::CaseInsensitive)) {
            slice->setColor(QColor("#e74c3c"));
        } else {
            slice->setColor(QColor("#3498db"));
        }
    }
    
    // Customize the series
    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);
    
    // Add series to chart
    chart->addSeries(series);
    
    // Update the chart view
    chartView->setChart(chart);
}

// Data retrieval methods
int Gclient1::getTotalClients()
{
    QSqlQuery query("SELECT COUNT(*) FROM clients");
    if (query.next()) {
        return query.value(0).toInt();
    }
    qDebug() << "Error getting total clients:" << query.lastError().text();
    return 0;
}

int Gclient1::getActiveClients()
{
    // Since there's no 'status' column, we'll consider all clients as active
    // If you want to track active clients, you might want to add a status column
    return getTotalClients();
}

int Gclient1::getNewClientsThisMonth()
{
    QSqlQuery query;
    // Using TRUNC to get the first day of month in Oracle
    if (query.exec("SELECT COUNT(*) FROM clients WHERE d_naissance >= TRUNC(SYSDATE, 'MM') AND d_naissance <= LAST_DAY(SYSDATE)")) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }
    qDebug() << "Error getting new clients this month:" << query.lastError().text();
    return 0;
}

int Gclient1::getAppointmentsCount()
{
    // Since there's no RENDEZ_VOUS table in the provided schema,
    // we'll return 0 or you can implement this if you have a different table
    return 0;
    
    // If you add the RENDEZ_VOUS table later, you can use this query:
    // QSqlQuery query("SELECT COUNT(*) FROM rendez_vous WHERE rdv_date >= TRUNC(SYSDATE)");
    // if (query.next()) {
    //     return query.value(0).toInt();
    // }
    // return 0;
}

QMap<QString, int> Gclient1::getClientGrowthData()
{
    QMap<QString, int> growthData;
    
    // Initialize with 0 for the last 6 months
    QDate currentDate = QDate::currentDate();
    QStringList monthNames = {"Jan", "Fév", "Mar", "Avr", "Mai", "Juin", 
                             "Juil", "Août", "Sep", "Oct", "Nov", "Déc"};
    
    // First, initialize all months with 0
    for (int i = 5; i >= 0; --i) {
        QDate monthDate = currentDate.addMonths(-i);
        QString monthKey = monthNames[monthDate.month() - 1] + " " + QString::number(monthDate.year()).right(2);
        growthData[monthKey] = 0;
    }
    
    // Get client count by month for the last 6 months
    QSqlQuery query;
    QString queryStr = 
        "SELECT TO_CHAR(TRUNC(d_naissance, 'MM'), 'Mon YY') as month, COUNT(*) as count "
        "FROM clients "
        "WHERE d_naissance >= ADD_MONTHS(TRUNC(SYSDATE, 'MM'), -5) "
        "GROUP BY TRUNC(d_naissance, 'MM') "
        "ORDER BY TRUNC(d_naissance, 'MM')";
    
    if (query.exec(queryStr)) {
        while (query.next()) {
            QString month = query.value(0).toString().trimmed();
            // Convert to proper case (first letter uppercase, rest lowercase)
            if (!month.isEmpty()) {
                month = month.left(1).toUpper() + month.mid(1).toLower();
                growthData[month] = query.value(1).toInt();
            }
        }
    } else {
        qDebug() << "Error getting client growth data:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
    }
    
    // Calculate cumulative growth
    int runningTotal = 0;
    for (auto it = growthData.begin(); it != growthData.end(); ++it) {
        runningTotal += it.value();
        it.value() = runningTotal;
    }
    
    return growthData;
}

QMap<QString, int> Gclient1::getGenderDistribution()
{
    QMap<QString, int> genderData;
    
    QSqlQuery query;
    if (!query.exec("SELECT sexe, COUNT(*) FROM clients GROUP BY sexe")) {
        qDebug() << "Error getting gender distribution:" << query.lastError().text();
        return genderData;
    }
    
    while (query.next()) {
        QString gender = query.value(0).toString();
        if (gender.isEmpty()) gender = "Inconnu";
        genderData[gender] = query.value(1).toInt();
    }
    
    // Ensure we have at least the main gender categories
    if (!genderData.contains("Homme")) genderData["Homme"] = 0;
    if (!genderData.contains("Femme")) genderData["Femme"] = 0;
    
    return genderData;
}

int Gclient1::getClientCount()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS");
    
    if (!query.exec()) {
        qDebug() << "Error getting client count:" << query.lastError().text();
        return 0;
    }
    
    if (query.next()) {
        return query.value(0).toInt();
    }
    
    return 0;
}

int Gclient1::getInactiveClientCount()
{
    // Since we don't have purchase history, consider clients without recent controls as inactive
    QDate threeMonthsAgo = QDate::currentDate().addMonths(-3);
    
    // First, get all clients
    int totalClients = getTotalClients();
    if (totalClients == 0) return 0;
    
    // Count clients with recent controls (in the last 3 months)
    QSqlQuery query;
    query.prepare(
        "SELECT COUNT(DISTINCT c.ID_CLIENT) "
        "FROM CLIENTS c "
        "JOIN CONTROLES ct ON c.ID_CLIENT = ct.ID_CLIENT "
        "WHERE ct.DATE_CONTROLE >= :date"
    );
    
    query.bindValue(":date", threeMonthsAgo.toString("yyyy-MM-dd"));
    
    if (!query.exec()) {
        qDebug() << "Error getting active client count:" << query.lastError().text();
        // If there's an error (maybe CONTROLES table doesn't exist), return 0 inactive
        return 0;
    }
    
    int activeClients = 0;
    if (query.next()) {
        activeClients = query.value(0).toInt();
    }
    
    // Inactive clients = total clients - active clients
    int inactiveClients = totalClients - activeClients;
    return qMax(0, inactiveClients); // Ensure we don't return negative numbers
}

QMap<QString, double> Gclient1::getAgeDistribution()
{
    QMap<QString, double> ageDistribution;
    QSqlQuery query;
    int totalClients = getClientCount();
    
    if (totalClients == 0) {
        return ageDistribution;
    }

    // Age groups with their SQL conditions
    QList<QPair<QString, QString>> ageGroups = {
        {"0-17", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) < 18"},
        {"18-25", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) BETWEEN 18 AND 25"},
        {"26-35", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) BETWEEN 26 AND 35"},
        {"36-50", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) BETWEEN 36 AND 50"},
        {"51-65", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) BETWEEN 51 AND 65"},
        {"65+", "TRUNC(MONTHS_BETWEEN(SYSDATE, d_naissance)/12) > 65"}
    };

    bool hasError = false;
    for (const auto &group : ageGroups) {
        QString queryStr = QString("SELECT COUNT(*) FROM CLIENTS WHERE %1").arg(group.second);
        if (!query.exec(queryStr)) {
            qDebug() << "Error in age group" << group.first << ":" << query.lastError().text();
            qDebug() << "Query:" << queryStr;
            hasError = true;
            continue;
        }
        
        if (query.next()) {
            int count = query.value(0).toInt();
            double percentage = (count * 100.0) / totalClients;
            ageDistribution[group.first] = percentage;
            qDebug() << "Age group" << group.first << ":" << count << "clients (" << QString::number(percentage, 'f', 1) << "%)";
        }
    }
    
    if (hasError) {
        qDebug() << "Some errors occurred while calculating age distribution";
    }
    
    return ageDistribution;
}

QMap<QString, double> Gclient1::getAddressDistribution()
{
    QMap<QString, double> addressDistribution;
    QSqlQuery query;
    int totalClients = getClientCount();
    
    if (totalClients == 0) {
        return addressDistribution;
    }

    // Get distribution by address
    if (query.exec("SELECT ADRESSE, COUNT(*) as count FROM CLIENTS GROUP BY ADRESSE")) {
        while (query.next()) {
            QString address = query.value(0).toString();
            if (address.isEmpty()) {
                address = "Unknown";
            }
            int count = query.value(1).toInt();
            double percentage = (count * 100.0) / totalClients;
            addressDistribution[address] = percentage;
        }
    }

    return addressDistribution;
}

// Simple Controls Table Implementation
void Gclient1::setupSimpleControlsTable()
{
    if (!ui->tableControles) {
        qWarning() << "tableControles is null in setupSimpleControlsTable";
        return;
    }

    qDebug() << "Setting up controls table...";
    
    // Configure table
    ui->tableControles->setColumnCount(4); // Client, Téléphone, Prochain contrôle, Jours restants
    ui->tableControles->setHorizontalHeaderLabels({"Client", "Téléphone", "Prochain contrôle", "Jours restants"});
    
    // Set column widths
    ui->tableControles->setColumnWidth(0, 200); // Client
    ui->tableControles->setColumnWidth(1, 150); // Téléphone
    ui->tableControles->setColumnWidth(2, 150); // Prochain contrôle
    ui->tableControles->setColumnWidth(3, 100); // Jours restants
    
    // Enable sorting and selection
    ui->tableControles->setSortingEnabled(true);
    ui->tableControles->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableControles->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Enable context menu
    ui->tableControles->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableControles, &QTableWidget::customContextMenuRequested,
            this, &Gclient1::showControlsContextMenu);
    
    // Connect tab changed signal
    connect(ui->tabWidgetMain, &QTabWidget::currentChanged, this, [this](int index) {
        if (ui->tabWidgetMain->tabText(index) == "Contrôles à venir") {
            refreshSimpleControlsTable();
        }
    });
    
    // Initial refresh
    refreshSimpleControlsTable();
    
    qDebug() << "Controls table setup complete";
}

void Gclient1::refreshSimpleControlsTable()
{
    if (!ui->tableControles) {
        qWarning() << "tableControles is null in refreshSimpleControlsTable";
        return;
    }

    qDebug() << "Refreshing controls table...";
    
    // Disable sorting while updating
    ui->tableControles->setSortingEnabled(false);
    ui->tableControles->setRowCount(0);

    // Query to get all clients with their next control date
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "   id_client, "
        "   nom, "
        "   prenom, "
        "   NVL(telephone, 'Non renseigné') as telephone, "
        "   d_naissance "
        "FROM clients "
        "ORDER BY nom, prenom"
    );

    if (!query.exec()) {
        qWarning() << "Failed to fetch clients:" << query.lastError().text();
        return;
    }
    
    QDate today = QDate::currentDate();
    int row = 0;
    
    while (query.next()) {
        int clientId = query.value("id_client").toInt();
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        QString telephone = query.value("telephone").toString();
        QDate birthDate = query.value("d_naissance").toDate();
        
        // Calculate next control date using the client ID for some variation
        QDate nextControlDate = calculateNextControlDate(clientId);
        int daysUntil = today.daysTo(nextControlDate);
        
        // Add row to table
        int newRow = ui->tableControles->rowCount();
        ui->tableControles->insertRow(newRow);
        
        // Client name
        QTableWidgetItem *nameItem = new QTableWidgetItem(nom + " " + prenom);
        nameItem->setData(Qt::UserRole, clientId); // Store client ID for later use
        ui->tableControles->setItem(newRow, 0, nameItem);
        
        // Phone
        QTableWidgetItem *phoneItem = new QTableWidgetItem(telephone);
        phoneItem->setTextAlignment(Qt::AlignCenter);
        ui->tableControles->setItem(newRow, 1, phoneItem);
        
        // Next control date
        QTableWidgetItem *dateItem = new QTableWidgetItem(nextControlDate.toString("dd/MM/yyyy"));
        dateItem->setTextAlignment(Qt::AlignCenter);
        dateItem->setData(Qt::UserRole + 1, nextControlDate); // Store the date for sorting
        ui->tableControles->setItem(newRow, 2, dateItem);
        
        // Days remaining
        QTableWidgetItem *daysItem = new QTableWidgetItem(QString::number(daysUntil));
        daysItem->setTextAlignment(Qt::AlignCenter);
        daysItem->setData(Qt::UserRole + 1, daysUntil); // Store the number for proper sorting
        ui->tableControles->setItem(newRow, 3, daysItem);
        
        // Apply row styling based on days until control
        QString statusStyle;
        QColor bgColor;
        
        if (daysUntil <= 0) {
            statusStyle = "overdue";
            bgColor = QColor(254, 226, 226); // Light red
        } else if (daysUntil <= 30) {
            statusStyle = "soon";
            bgColor = QColor(254, 243, 199); // Light yellow
        } else {
            statusStyle = "ok";
            bgColor = Qt::white;
        }
        
        // Apply styling to all cells in the row
        for (int col = 0; col < ui->tableControles->columnCount(); ++col) {
            if (QTableWidgetItem *item = ui->tableControles->item(newRow, col)) {
                item->setData(Qt::UserRole + 1, statusStyle);
                item->setBackground(bgColor);
                
                // Make text color darker for better contrast
                if (statusStyle == "overdue") {
                    item->setForeground(Qt::black);
                }
            }
        }
        
        row++;
    }
    
    // Re-enable sorting
    ui->tableControles->setSortingEnabled(true);
    
    // Update status bar
    updateStatusBar();
    
    qDebug() << "Refreshed controls table with" << row << "clients";
}

QDate Gclient1::calculateNextControlDate(int clientId) const
{
    // Use a combination of client ID and current date to generate a predictable but varied date
    uint hash = qHash(QString::number(clientId) + QDate::currentDate().toString("yyyy"));
    QDate today = QDate::currentDate();
    
    // Generate a day in the next 6-18 months
    int daysToAdd = 180 + (hash % 365); // Between 6 and 18 months
    QDate nextControl = today.addDays(daysToAdd);
    
    // Ensure the date is in the future
    if (nextControl < today) {
        nextControl = nextControl.addYears(1);
    }
    
    return nextControl;
}

QString Gclient1::getControlStatus(const QDate &nextControlDate) const
{
    int daysUntil = QDate::currentDate().daysTo(nextControlDate);
    
    if (daysUntil < 0) {
        return "⚠️ En retard";
    } else if (daysUntil == 0) {
        return "⚠️ Aujourd'hui";
    } else if (daysUntil <= 7) {
        return "🔔 Cette semaine";
    } else if (daysUntil <= 30) {
        return "📅 Ce mois";
    } else {
        return "✅ À jour";
    }
}

QString Gclient1::getControlStatusStyle(const QDate &nextControlDate) const
{
    int daysUntil = QDate::currentDate().daysTo(nextControlDate);
    
    if (daysUntil <= 0) {
        return "overdue";
    } else if (daysUntil <= 30) {
        return "soon";
    } else {
        return "ok";
    }
}

void Gclient1::showControlsContextMenu(const QPoint &pos)
{
    QTableWidgetItem *item = ui->tableControles->itemAt(pos);
    if (!item) return;
    
    int row = item->row();
    int clientId = ui->tableControles->item(row, 0)->text().toInt();
    QString clientName = ui->tableControles->item(row, 1)->text();
    QString phone = ui->tableControles->item(row, 2)->text();
    
    QMenu menu(this);
    
    QAction *callAction = menu.addAction("📞 Appeler " + clientName);
    QAction *messageAction = menu.addAction("💬 Envoyer un message");
    menu.addSeparator();
    QAction *renewAction = menu.addAction("🔄 Renouveler le contrôle");
    
    QAction *selected = menu.exec(ui->tableControles->viewport()->mapToGlobal(pos));
    if (!selected) return;
    
    if (selected == callAction) {
        onCallClient(phone);
    } else if (selected == messageAction) {
        onMessageClient(phone);
    } else if (selected == renewAction) {
        onRenewControl(clientId, row);
    }
}

void Gclient1::onCallClient(const QString &phoneNumber)
{
    QMessageBox::information(this, "Appel", "Appel vers " + phoneNumber);
}

void Gclient1::onMessageClient(const QString &phoneNumber)
{
    QMessageBox::information(this, "Message", "Message à " + phoneNumber);
}

void Gclient1::onRenewControl(int /* clientId */, int row)
{
    QDate newDate = QDate::currentDate().addYears(1);
    
    if (row >= 0 && row < ui->tableControles->rowCount()) {
        QTableWidgetItem *dateItem = ui->tableControles->item(row, 3);
        QTableWidgetItem *daysItem = ui->tableControles->item(row, 4);
        QTableWidgetItem *statusItem = ui->tableControles->item(row, 5);
        
        dateItem->setText(newDate.toString("dd/MM/yyyy"));
        dateItem->setData(Qt::UserRole, newDate);
        
        int daysUntil = QDate::currentDate().daysTo(newDate);
        daysItem->setData(Qt::DisplayRole, daysUntil);
        
        QString status = getControlStatus(newDate);
        QString statusStyle = getControlStatusStyle(newDate);
        
        statusItem->setText(status);
        statusItem->setData(Qt::UserRole, statusStyle);
        
        // Update row styling
        for (int col = 0; col < ui->tableControles->columnCount(); ++col) {
            if (QTableWidgetItem *item = ui->tableControles->item(row, col)) {
                item->setData(Qt::UserRole + 1, statusStyle);
            }
        }
        
        QMessageBox::information(this, "Succès", 
            "Le contrôle a été renouvelé jusqu'au " + newDate.toString("dd/MM/yyyy"));
    }
}

void Gclient1::updateStatusBar()
{
    if (!statusBar()) {
        return;
    }
    
    int total = ui->tableControles->rowCount();
    int overdue = 0;
    int dueSoon = 0;
    
    for (int i = 0; i < total; ++i) {
        // Get the status from the first cell of each row
        if (QTableWidgetItem *item = ui->tableControles->item(i, 0)) {
            QString status = item->data(Qt::UserRole + 1).toString();
            if (status == "overdue") {
                overdue++;
            } else if (status == "soon") {
                dueSoon++;
            }
        }
    }
    
    QString statusText = QString("Total: %1  |  En retard: %2  |  Bientôt dû: %3")
                        .arg(total).arg(overdue).arg(dueSoon);
    
    statusBar()->showMessage(statusText);
    qDebug() << "Status bar updated - Total:" << total << "Overdue:" << overdue << "Due soon:" << dueSoon;
}

