#include "gestionemploye00.h"
#include "./ui_gestionemploye00.h"
#include "statistique.h"
#include "exporter.h"
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include "employe.h"
#include "Connection.h"
#include "employeeditdialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QDate>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include "WindowManager.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QFileInfo>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

// Initialize static instance pointer
gestionemploye00* gestionemploye00::instance = nullptr;

gestionemploye00* gestionemploye00::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new gestionemploye00(parent);
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

gestionemploye00::gestionemploye00(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gestionemploye00)
{
    ui->setupUi(this);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Employés", 1200, 800);
    
    // ID field is auto-generated (read-only)
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setPlaceholderText(tr("Auto"));
    
    // Setup input validators
    // Email validator - must contain "@"
    // (No placeholder text)
    
    // Telephone validator - exactly 8 digits
    if (ui->lineEdit_6) {
        QRegularExpressionValidator *telValidator = new QRegularExpressionValidator(
            QRegularExpression("^\\d{8}$"), this);
        ui->lineEdit_6->setValidator(telValidator);
        ui->lineEdit_6->setMaxLength(8);
    }
    
    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
        return; // Don't continue if connection fails
    }
    
    // Verify connection is active
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "La connexion à la base de données n'est pas active!");
        return;
    }
    
    // Configure table widget - 13 columns including action buttons
    ui->tableWidget->setColumnCount(13);
    QStringList headers = {"ID", "Nom", "Prenom", "Email", "Telephone", "Date Naissance", 
                           "Adresse", "Poste", "Salaire", "Nb Enfants", "Disponibilite", "Modifier", "Supprimer"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Configure tri combo box - use findChild to access it safely
    QComboBox* comboBox_tri = this->findChild<QComboBox*>("comboBox_tri");
    if (comboBox_tri) {
        comboBox_tri->clear();
        comboBox_tri->addItem(tr("Nom (A-Z)"), "nom_asc");
        comboBox_tri->addItem(tr("Salaire (desc)"), "salaire_desc");
        comboBox_tri->setCurrentIndex(0);
    } else {
        qDebug() << "comboBox_tri not found in UI, sorting will use default";
    }
    
    // Configure disponibilite combo box - ensure it always has O and N options
    QComboBox* comboBox_disponibilite = this->findChild<QComboBox*>("comboBox_disponibilite");
    if (comboBox_disponibilite) {
        // Clear and ensure it has the right items
        comboBox_disponibilite->clear();
        comboBox_disponibilite->addItem("O", "O");
        comboBox_disponibilite->addItem("N", "N");
        comboBox_disponibilite->setCurrentIndex(0); // Default to "O"
    } else {
        qDebug() << "⚠️ comboBox_disponibilite not found in UI, will use lineEdit_11 as fallback";
        // Fallback to lineEdit_11 if it exists
        QLineEdit* lineEdit_11 = this->findChild<QLineEdit*>("lineEdit_11");
        if (lineEdit_11) {
            lineEdit_11->setPlaceholderText("O ou N");
        }
    }
    
    // Make logo clickable
    if (ui->logoLabel) {
        ui->logoLabel->setCursor(Qt::PointingHandCursor);
        ui->logoLabel->installEventFilter(this);
        ui->logoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Load data on startup
    afficherTableau();
    
    // Connect table selection signal
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, 
            this, &gestionemploye00::on_tableWidget_itemSelectionChanged);
    
    // Connect search signal
    if (ui->lineEdit_12) {
        connect(ui->lineEdit_12, &QLineEdit::textChanged, 
                this, &gestionemploye00::on_lineEdit_12_textChanged);
    }
}

gestionemploye00::~gestionemploye00()
{
    delete ui;
}

void gestionemploye00::on_pushButton_6_clicked()
{
    Statistique *h = new Statistique(this);
    h->setAttribute(Qt::WA_DeleteOnClose);
    h->loadEmployeeStatistics();
    h->show();
}

void gestionemploye00::on_pushButton_10_clicked()
{
    exportEmployeesToPdf();
}

void gestionemploye00::on_pushButton_14_clicked()
{
    // Stock
    MainWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_8_clicked()
{
    // Ventes
    SalesWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_9_clicked()
{
    // Client
    Gclient1::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_7_clicked()
{
    // Produit -> go to stock page (MainWindow)
    MainWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_11_clicked()
{
    // Fournisseur
    FournisseurWindow::getInstance();
    this->close();
}

void gestionemploye00::on_logoClicked()
{
    DashboardWindow::getInstance();
    this->close();
}

bool gestionemploye00::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->logoLabel && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            on_logoClicked();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

// ============ CRUD OPERATIONS ============

// Ajouter/Valider un employé
void gestionemploye00::on_pushButton_13_clicked()
{
    // Get data from form
    QString nom = ui->lineEdit_5->text().trimmed();
    QString prenom = ui->lineEdit_3->text().trimmed();
    QString telephone = ui->lineEdit_6->text().trimmed();
    QDate date = ui->dateEdit->date();
    QString adresse = ui->lineEdit_7->text().trimmed();
    QString email = ui->lineEdit_4->text().trimmed();
    QString nombre_enfants_str = ui->lineEdit_8->text().trimmed();
    QString poste = ui->lineEdit_9->text().trimmed();
    QString salaire_str = ui->lineEdit_10->text().trimmed();
    
    // Get disponibilite from comboBox - must be O or N
    QString disponibilite = "O"; // Default
    QComboBox* comboBox_disponibilite = this->findChild<QComboBox*>("comboBox_disponibilite");
    if (comboBox_disponibilite) {
        QVariant data = comboBox_disponibilite->currentData();
        if (data.isValid() && !data.toString().isEmpty()) {
            disponibilite = data.toString().toUpper();
        } else {
            QString text = comboBox_disponibilite->currentText().trimmed().toUpper();
            if (text == "O" || text == "N") {
                disponibilite = text;
            }
        }
    } else {
        QLineEdit* lineEdit_11 = this->findChild<QLineEdit*>("lineEdit_11");
        if (lineEdit_11) {
            QString text = lineEdit_11->text().trimmed().toUpper();
            if (text == "O" || text == "N") {
                disponibilite = text;
            }
        }
    }
    
    // Validate required fields
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires (Nom, Prénom, Email)!");
        return;
    }
    
    // Validation email - must contain "@"
    if (!email.isEmpty() && !email.contains('@')) {
        QMessageBox::warning(this, "Validation", "L'adresse e-mail doit contenir le caractère '@'.");
        if (ui->lineEdit_4) {
            ui->lineEdit_4->setFocus();
            ui->lineEdit_4->selectAll();
        }
        return;
    }
    
    // Validation telephone - must be exactly 8 digits
    if (!telephone.isEmpty()) {
        QRegularExpression regexTel("^\\d{8}$");
        if (!regexTel.match(telephone).hasMatch()) {
            QMessageBox::warning(this, "Validation", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
            if (ui->lineEdit_6) {
                ui->lineEdit_6->setFocus();
                ui->lineEdit_6->selectAll();
            }
            return;
        }
    }
    
    // Validate disponibilite
    if (disponibilite != "O" && disponibilite != "N") {
        QMessageBox::warning(this, "Erreur", "Disponibilité doit être 'O' (Oui) ou 'N' (Non)!");
        return;
    }
    
    // Convert and validate numeric fields
    bool ok;
    int nombre_enfants = nombre_enfants_str.toInt(&ok);
    if (!ok && !nombre_enfants_str.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nombre d'enfants doit être un nombre valide!");
        return;
    }
    if (nombre_enfants < 0) nombre_enfants = 0;
    
    double salaire = salaire_str.toDouble(&ok);
    if (!ok && !salaire_str.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Salaire doit être un nombre valide!");
        return;
    }
    if (salaire < 0) salaire = 0.0;
    
    Employe e;
    e.setNom(nom);
    e.setPrenom(prenom);
    e.setTelephone(telephone);
    e.setDate(date);
    e.setAdresse(adresse);
    e.setEmail(email);
    e.setNombreEnfants(nombre_enfants);
    e.setPoste(poste);
    e.setSalaire(salaire);
    e.setDisponibilite(disponibilite);
    
    // Check if editing (ID field filled) or adding new
    QString idText = ui->lineEdit->text().trimmed();
    bool isEditing = !idText.isEmpty();
    
    if (isEditing) {
        e.setId(idText.toInt());
        if (e.modifier()) {
            QMessageBox::information(this, "Succès", QString("Employé modifié avec succès (ID %1)!").arg(e.getId()));
            on_pushButton_12_clicked();
            afficherTableau(); // Always refresh table after modifying
        } else {
            QSqlDatabase db = QSqlDatabase::database();
            QSqlError error = db.lastError();
            QString errorMsg = error.text();
            if (errorMsg.isEmpty()) {
                errorMsg = "Erreur inconnue lors de la modification de l'employé.";
            }
            QMessageBox::critical(this, "Erreur", QString("Erreur lors de la modification: %1").arg(errorMsg));
        }
    } else {
        // Adding new employee
        qDebug() << "🔄 Attempting to add new employee...";
        qDebug() << "  Nom:" << nom;
        qDebug() << "  Prenom:" << prenom;
        qDebug() << "  Email:" << email;
        qDebug() << "  Disponibilite:" << disponibilite;
        
        if (e.ajouter()) {
            int newId = e.getId();
            QString successMsg = QString("Employé ajouté avec succès!");
            if (newId > 0) {
                successMsg += QString("\nID: %1").arg(newId);
            }
            QMessageBox::information(this, "Succès", successMsg);
            on_pushButton_12_clicked();
            // Force refresh of table to show new employee
            QTimer::singleShot(100, this, [this]() {
                afficherTableau();
            });
        } else {
            // Get the last database error for more details
            QSqlDatabase db = QSqlDatabase::database();
            QSqlError error = db.lastError();
            QString errorMsg = error.text();
            
            if (errorMsg.isEmpty() || error.type() == QSqlError::NoError) {
                errorMsg = "Erreur inconnue lors de l'ajout de l'employé.\n\n"
                          "Veuillez vérifier:\n"
                          "1. Que tous les champs obligatoires sont remplis\n"
                          "2. Que la disponibilité est 'O' ou 'N'\n"
                          "3. Que la connexion à la base de données est active\n"
                          "4. Consultez les logs de l'application pour plus de détails";
            }
            
            QString fullError = QString("Erreur lors de l'ajout de l'employé!\n\n")
                              + QString("Message: %1").arg(errorMsg);
            QString nativeErrorCode = error.nativeErrorCode();
            if (!nativeErrorCode.isEmpty()) {
                fullError += QString("\nCode d'erreur: %1").arg(nativeErrorCode);
            }
            QString databaseText = error.databaseText();
            if (!databaseText.isEmpty() && databaseText != errorMsg) {
                fullError += QString("\nDétails base de données: %1").arg(databaseText);
            }
            
            QMessageBox::critical(this, "Erreur", fullError);
            qDebug() << "❌ === ERREUR DANS L'UI ===";
            qDebug() << "Database error:" << error.text();
            qDebug() << "Database error text:" << error.databaseText();
            qDebug() << "Driver error text:" << error.driverText();
            qDebug() << "Native error code:" << nativeErrorCode;
            qDebug() << "Error type:" << error.type();
        }
    }
}

// Effacer le formulaire
void gestionemploye00::on_pushButton_12_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_6->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_7->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    
    // Reset disponibilite to default "O"
    QComboBox* comboBox_disponibilite = this->findChild<QComboBox*>("comboBox_disponibilite");
    if (comboBox_disponibilite) {
        // Ensure combo box has O and N options
        if (comboBox_disponibilite->count() < 2) {
            comboBox_disponibilite->clear();
            comboBox_disponibilite->addItem("O", "O");
            comboBox_disponibilite->addItem("N", "N");
        }
        comboBox_disponibilite->setCurrentIndex(0); // Default to "O"
    } else {
        QLineEdit* lineEdit_11 = this->findChild<QLineEdit*>("lineEdit_11");
        if (lineEdit_11) {
            lineEdit_11->clear();
            lineEdit_11->setPlaceholderText("O ou N");
        }
    }
    
    ui->tableWidget->clearSelection();
}

// Afficher tous les employés
void gestionemploye00::on_pushButton_3_clicked()
{
    afficherTableau();
}

// Afficher tous les employés (duplicate button)
void gestionemploye00::on_pushButton_15_clicked()
{
    afficherTableau();
}

// Rechercher un employé
void gestionemploye00::on_pushButton_4_clicked()
{
    searchEmployees(ui->lineEdit_12->text());
}

void gestionemploye00::on_lineEdit_12_textChanged(const QString &text)
{
    searchEmployees(text);
}

// Modifier un employé
void gestionemploye00::on_pushButton_16_clicked()
{
    int id = selectedEmployeId();
    if (id < 0) {
        QMessageBox::warning(this, "Modifier", "Veuillez sélectionner un employé dans le tableau.");
        return;
    }

    modifyEmployeeById(id);
}

// Supprimer un employé
void gestionemploye00::on_pushButton_17_clicked()
{
    int id = selectedEmployeId();
    if (id < 0) {
        QMessageBox::warning(this, "Supprimer", "Veuillez sélectionner un employé dans le tableau.");
        return;
    }

    deleteEmployeeById(id);
}

// Trier les employés
void gestionemploye00::on_pushButton_5_clicked()
{
    Employe e;
    QComboBox* comboBox_tri = this->findChild<QComboBox*>("comboBox_tri");
    QString key = "nom_asc"; // Default
    
    if (comboBox_tri) {
        key = comboBox_tri->currentData().toString();
    }
    
    QSqlQueryModel* model = nullptr;

    if (key == "salaire_desc") {
        model = e.trierParSalaire();
    } else {
        model = e.trierParNom();
    }

    populateTable(model);
}

// Afficher le tableau des employés
void gestionemploye00::afficherTableau()
{
    // Ensure database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not connected, attempting to reconnect...";
        Connection c;
        if (!c.createconnect()) {
            QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
            return;
        }
        db = QSqlDatabase::database(); // Get the new connection
    }
    
    qDebug() << "🔄 Loading employees from database...";
    Employe e;
    QSqlQueryModel* model = e.afficher();
    
    if (model) {
        int rowCount = model->rowCount();
        qDebug() << "📊 Model created with" << rowCount << "rows";
        
        // Check for query errors
        if (model->lastError().isValid()) {
            qDebug() << "❌ Query error:" << model->lastError().text();
            QMessageBox::warning(this, "Erreur", 
                QString("Erreur lors du chargement des employés:\n%1").arg(model->lastError().text()));
        }
        
        populateTable(model);
        qDebug() << "✅ Tableau des employés chargé avec" << rowCount << "lignes";
        
        if (rowCount == 0) {
            qDebug() << "ℹ️ Aucun employé trouvé dans la base de données";
        }
    } else {
        qDebug() << "❌ Erreur: modèle null lors du chargement des employés";
        QMessageBox::warning(this, "Attention", "Erreur lors de la création du modèle de données.");
    }
}

// Remplir le formulaire lorsqu'une ligne est sélectionnée
void gestionemploye00::on_tableWidget_itemSelectionChanged()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* item = ui->tableWidget->item(currentRow, 0);
        if (item) {
            remplirFormulaire(item->text().toInt());
        }
    }
}

// Remplir le formulaire avec les données d'un employé
void gestionemploye00::remplirFormulaire(int id)
{
    Employe e;
    if (e.rechercherParId(id)) {
        ui->lineEdit->setText(QString::number(e.getId()));
        ui->lineEdit_5->setText(e.getNom());
        ui->lineEdit_3->setText(e.getPrenom());
        ui->lineEdit_6->setText(e.getTelephone());
        ui->dateEdit->setDate(e.getDate());
        ui->lineEdit_7->setText(e.getAdresse());
        ui->lineEdit_4->setText(e.getEmail());
        ui->lineEdit_8->setText(QString::number(e.getNombreEnfants()));
        ui->lineEdit_9->setText(e.getPoste());
        ui->lineEdit_10->setText(QString::number(e.getSalaire()));
        
        const QString disp = e.getDisponibilite().toUpper();
        QComboBox* comboBox_disponibilite = this->findChild<QComboBox*>("comboBox_disponibilite");
        if (comboBox_disponibilite) {
            int index = comboBox_disponibilite->findData(disp);
            if (index < 0) {
                index = comboBox_disponibilite->findText(disp == "O" ? "O" : "N");
            }
            if (index >= 0) {
                comboBox_disponibilite->setCurrentIndex(index);
            }
        } else {
            QLineEdit* lineEdit_11 = this->findChild<QLineEdit*>("lineEdit_11");
            if (lineEdit_11) {
                lineEdit_11->setText(disp == "O" ? "O" : "N");
            }
        }
    }
}

int gestionemploye00::selectedEmployeId() const
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        return -1;
    }

    QTableWidgetItem* item = ui->tableWidget->item(currentRow, 0);
    if (!item) {
        return -1;
    }

    bool ok = false;
    int id = item->text().toInt(&ok);
    return ok ? id : -1;
}

void gestionemploye00::createActionButtonsForRow(int row)
{
    // Modify button
    auto *modifyBtn = new QPushButton(tr("Modifier"), ui->tableWidget);
    modifyBtn->setProperty("row", row);
    modifyBtn->setStyleSheet("background-color:#0c66ed;color:white;padding:4px 8px;border-radius:6px;");
    connect(modifyBtn, &QPushButton::clicked, this, &gestionemploye00::handleModifyFromTable);
    ui->tableWidget->setCellWidget(row, 11, modifyBtn);

    // Delete button
    auto *deleteBtn = new QPushButton(tr("Supprimer"), ui->tableWidget);
    deleteBtn->setProperty("row", row);
    deleteBtn->setStyleSheet("background-color:#b00020;color:white;padding:4px 8px;border-radius:6px;");
    connect(deleteBtn, &QPushButton::clicked, this, &gestionemploye00::handleDeleteFromTable);
    ui->tableWidget->setCellWidget(row, 12, deleteBtn);
}

void gestionemploye00::modifyEmployeeById(int id)
{
    Employe employe;
    if (!employe.rechercherParId(id)) {
        QMessageBox::critical(this, tr("Modifier"), tr("Impossible de récupérer les informations de l'employé sélectionné."));
        return;
    }

    EmployeEditDialog dialog(employe, this);
    if (dialog.exec() != QDialog::Accepted) return;

    if (dialog.nom().isEmpty() || dialog.prenom().isEmpty() || dialog.email().isEmpty()) {
        QMessageBox::warning(this, tr("Modifier"), tr("Les champs Nom, Prénom et Email sont obligatoires."));
        return;
    }
    const QString disponibilite = dialog.disponibilite().toUpper();
    if (disponibilite != "O" && disponibilite != "N") {
        QMessageBox::warning(this, tr("Modifier"), tr("La disponibilité doit être 'O' ou 'N'."));
        return;
    }

    employe.setNom(dialog.nom());
    employe.setPrenom(dialog.prenom());
    employe.setEmail(dialog.email());
    employe.setTelephone(dialog.telephone());
    employe.setDate(dialog.dateNaissance());
    employe.setAdresse(dialog.adresse());
    employe.setPoste(dialog.poste());
    employe.setSalaire(dialog.salaire());
    employe.setNombreEnfants(dialog.nombreEnfants());
    employe.setDisponibilite(disponibilite);
    employe.setId(id);

    if (employe.modifier()) {
        QMessageBox::information(this, tr("Modifier"), tr("Employé modifié avec succès."));
        on_pushButton_12_clicked();
        afficherTableau(); // Always refresh table after modifying
    } else {
        QMessageBox::critical(this, tr("Modifier"), tr("Erreur lors de la modification de l'employé."));
    }
}

void gestionemploye00::deleteEmployeeById(int id)
{
    const auto reply = QMessageBox::question(this, tr("Supprimer"), tr("Êtes-vous sûr de vouloir supprimer cet employé ?"), QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    Employe employe;
    if (employe.supprimer(id)) {
        QMessageBox::information(this, tr("Supprimer"), tr("Employé supprimé avec succès."));
        on_pushButton_12_clicked();
        afficherTableau(); // Always refresh table after deleting
    } else {
        QMessageBox::critical(this, tr("Supprimer"), tr("Erreur lors de la suppression de l'employé."));
    }
}

void gestionemploye00::handleModifyFromTable()
{
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    bool ok = false;
    int row = btn->property("row").toInt(&ok);
    if (!ok) return;
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) return;
    int id = idItem->text().toInt(&ok);
    if (!ok) return;
    modifyEmployeeById(id);
}

void gestionemploye00::handleDeleteFromTable()
{
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    bool ok = false;
    int row = btn->property("row").toInt(&ok);
    if (!ok) return;
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) return;
    int id = idItem->text().toInt(&ok);
    if (!ok) return;
    deleteEmployeeById(id);
}

void gestionemploye00::populateTable(QSqlQueryModel *model)
{
    if (!model) {
        qDebug() << "⚠️ populateTable: model is null";
        return;
    }

    int rowCount = model->rowCount();
    qDebug() << "📋 populateTable: Populating table with" << rowCount << "rows";

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(rowCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < 11; ++col) {
            QModelIndex index = model->index(row, col);
            QString value = model->data(index).toString();
            
            // Handle date formatting for column 5 (Date Naissance)
            if (col == 5 && !value.isEmpty()) {
                QDate date = model->data(index).toDate();
                if (date.isValid()) {
                    value = date.toString("dd/MM/yyyy");
                }
            }
            
            QTableWidgetItem *item = new QTableWidgetItem(value);
            if (col == 0 || col == 8 || col == 9 || col == 10) {
                item->setTextAlignment(Qt::AlignCenter);
            } else {
                item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(row, col, item);
        }
        createActionButtonsForRow(row);
    }

    qDebug() << "✅ populateTable: Successfully populated" << rowCount << "rows";
    delete model;
}

void gestionemploye00::searchEmployees(const QString &text)
{
    QString trimmed = text.trimmed();
    if (trimmed.isEmpty()) {
        afficherTableau();
        return;
    }

    Employe e;
    populateTable(e.rechercherParNom(trimmed));
}

void gestionemploye00::exportEmployeesToPdf()
{
    // Check database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "La connexion à la base de données n'est pas active!");
        return;
    }
    
    // Get all employees from database
    Employe e;
    QSqlQueryModel* model = e.afficher();
    
    if (!model || model->rowCount() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucun employé à exporter.");
        if (model) delete model;
        return;
    }
    
    // Get file path for saving PDF
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Exporter les employés en PDF", 
        QString("employes_%1.pdf").arg(QDate::currentDate().toString("yyyy-MM-dd")),
        "PDF Files (*.pdf)");
    
    if (fileName.isEmpty()) {
        delete model;
        return;
    }
    
    // Ensure .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }
    
    // Check if file exists and can be written
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists() && !fileInfo.isWritable()) {
        QMessageBox::critical(this, "Erreur", "Le fichier existe déjà et ne peut pas être modifié.\nVeuillez choisir un autre nom ou fermer le fichier s'il est ouvert.");
        delete model;
        return;
    }
    
    // Create PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    // Create painter
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Check if PDF writer is valid
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.\nVérifiez que le fichier n'est pas ouvert dans une autre application.");
        delete model;
        return;
    }
    
    // Company information
    QString companyName = "Smart Optical Store";
    QString companyAddress = "123 Rue Principale, Tunis, Tunisie";
    QString companyPhone = "+216 12 345 678";
    QString companyEmail = "contact@smartopticalstore.com";
    
    // Page dimensions (in pixels)
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();
    int margin = 60;
    int yPos = margin;
    int lineHeight = 20;
    int tableStartY = 0;
    
    // Setup fonts
    QFont titleFont("Arial", 24, QFont::Bold);
    QFont headerFont("Arial", 11, QFont::Bold);
    QFont normalFont("Arial", 9);
    QFont smallFont("Arial", 8);
    QFont tableHeaderFont("Arial", 9, QFont::Bold);
    QFont tableFont("Arial", 8);
    
    // Draw header on first page
    painter.setFont(titleFont);
    painter.setPen(QPen(Qt::black));
    painter.drawText(QRect(0, yPos, pageWidth, 40), Qt::AlignCenter, companyName);
    yPos += 50;
    
    painter.setFont(headerFont);
    painter.drawText(QRect(0, yPos, pageWidth, 20), Qt::AlignCenter, "Liste des Employés");
    yPos += 30;
    
    painter.setFont(smallFont);
    painter.drawText(QRect(0, yPos, pageWidth, 15), Qt::AlignCenter, 
                     QString("Généré le: %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));
    yPos += 25;
    
    // Draw company info
    painter.setFont(smallFont);
    painter.drawText(QRect(margin, yPos, pageWidth - 2*margin, 15), 
                     QString("Adresse: %1 | Tél: %2 | Email: %3").arg(companyAddress).arg(companyPhone).arg(companyEmail));
    yPos += 30;
    
    // Table header
    tableStartY = yPos;
    painter.setFont(tableHeaderFont);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(QColor(200, 200, 200)));
    
    // Column widths (proportional to page width)
    int colWidths[] = {60, 100, 100, 120, 80, 80, 100, 100, 80, 60, 80};
    int xPos = margin;
    QStringList headers = {"ID", "Nom", "Prénom", "Email", "Téléphone", "Date Naiss.", 
                          "Adresse", "Poste", "Salaire", "Enfants", "Disponibilité"};
    
    // Draw table header
    for (int col = 0; col < headers.size() && col < 11; ++col) {
        painter.drawRect(xPos, yPos, colWidths[col], lineHeight + 5);
        painter.drawText(QRect(xPos + 2, yPos + 2, colWidths[col] - 4, lineHeight + 1), 
                        Qt::AlignLeft | Qt::AlignVCenter, headers[col]);
        xPos += colWidths[col];
    }
    yPos += lineHeight + 7;
    
    // Draw table rows
    painter.setFont(tableFont);
    painter.setBrush(QBrush(Qt::white));
    int rowHeight = lineHeight + 3;
    int maxRowsPerPage = (pageHeight - yPos - margin) / rowHeight;
    int currentRow = 0;
    int pageNum = 1;
    
    for (int row = 0; row < model->rowCount(); ++row) {
        // Check if we need a new page
        if (currentRow >= maxRowsPerPage) {
            pdfWriter.newPage();
            yPos = margin;
            currentRow = 0;
            pageNum++;
            
            // Redraw header on new page
            painter.setFont(smallFont);
            painter.drawText(QRect(0, yPos, pageWidth, 15), Qt::AlignCenter, 
                           QString("Page %1 - %2").arg(pageNum).arg(companyName));
            yPos += 20;
            
            // Redraw table header
            painter.setFont(tableHeaderFont);
            painter.setBrush(QBrush(QColor(200, 200, 200)));
            xPos = margin;
            for (int col = 0; col < headers.size() && col < 11; ++col) {
                painter.drawRect(xPos, yPos, colWidths[col], lineHeight + 5);
                painter.drawText(QRect(xPos + 2, yPos + 2, colWidths[col] - 4, lineHeight + 1), 
                                Qt::AlignLeft | Qt::AlignVCenter, headers[col]);
                xPos += colWidths[col];
            }
            yPos += lineHeight + 7;
            painter.setFont(tableFont);
            painter.setBrush(QBrush(Qt::white));
        }
        
        // Get data from model
        QString id = model->data(model->index(row, 0)).toString();
        QString nom = model->data(model->index(row, 1)).toString();
        QString prenom = model->data(model->index(row, 2)).toString();
        QString email = model->data(model->index(row, 3)).toString();
        QString telephone = model->data(model->index(row, 4)).toString();
        QString dateNaiss = model->data(model->index(row, 5)).toString();
        QString adresse = model->data(model->index(row, 6)).toString();
        QString poste = model->data(model->index(row, 7)).toString();
        QString salaire = model->data(model->index(row, 8)).toString();
        QString nEnfants = model->data(model->index(row, 9)).toString();
        QString disponibilite = model->data(model->index(row, 10)).toString();
        
        // Truncate long strings
        if (email.length() > 15) email = email.left(12) + "...";
        if (adresse.length() > 12) adresse = adresse.left(10) + "...";
        
        // Draw row
        xPos = margin;
        QStringList rowData = {id, nom, prenom, email, telephone, dateNaiss, 
                              adresse, poste, salaire, nEnfants, disponibilite};
        
        for (int col = 0; col < rowData.size() && col < 11; ++col) {
            painter.setPen(QPen(Qt::black, 0.5));
            painter.drawRect(xPos, yPos, colWidths[col], rowHeight);
            painter.setPen(QPen(Qt::black));
            painter.drawText(QRect(xPos + 2, yPos + 2, colWidths[col] - 4, rowHeight - 4), 
                           Qt::AlignLeft | Qt::AlignVCenter, rowData[col]);
            xPos += colWidths[col];
        }
        
        yPos += rowHeight;
        currentRow++;
    }
    
    // Draw footer on last page
    painter.setFont(smallFont);
    painter.setPen(QPen(Qt::gray));
    painter.drawText(QRect(0, pageHeight - 30, pageWidth, 20), Qt::AlignCenter, 
                    QString("Total: %1 employé(s)").arg(model->rowCount()));
    
    painter.end();
    delete model;
    
    QMessageBox::information(this, "Succès", 
                            QString("Les employés ont été exportés avec succès dans:\n%1").arg(fileName));
}
