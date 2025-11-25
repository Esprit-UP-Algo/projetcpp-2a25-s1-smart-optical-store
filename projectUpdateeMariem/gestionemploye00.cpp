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
#include <QSqlQuery>
#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include "WindowManager.h"

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
    , birthdayCount(0)
{
    ui->setupUi(this);

    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Employés", 1200, 800);

    // Create birthday notification button
    birthdayButton = new QPushButton(this);
    birthdayButton->setFixedSize(70, 70);
    birthdayButton->move(1000, 120); // Moved further right and down
    birthdayButton->setCursor(Qt::PointingHandCursor);
    birthdayButton->setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "       stop:0 #FF1493, stop:0.5 #FFD700, stop:1 #FF1493);"
        "   border: 4px solid #FFD700;"
        "   border-radius: 35px;"
        "   font-size: 32px;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "       stop:0 #FF69B4, stop:0.5 #FFE44D, stop:1 #FF69B4);"
        "   border: 5px solid #FFD700;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF1493;"
        "}"
        );
    birthdayButton->setText("🎂");
    birthdayButton->setToolTip("Cliquez pour voir les anniversaires");
    birthdayButton->raise(); // Bring to front
    birthdayButton->show(); // Always show for testing
    qDebug() << "✅ Birthday button created and shown at position:" << birthdayButton->pos();
    connect(birthdayButton, &QPushButton::clicked, this, &gestionemploye00::onBirthdayButtonClicked);

    // ID field is auto-generated (read-only)
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setPlaceholderText(tr("Auto"));

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

    // Initialize birthday check timer
    birthdayCheckTimer = new QTimer(this);
    connect(birthdayCheckTimer, &QTimer::timeout, this, &gestionemploye00::checkBirthdays);

    // Check birthdays immediately on startup (without showing alert)
    QTimer::singleShot(500, this, &gestionemploye00::updateBirthdayButton);

    // Check birthdays every 30 minutes
    birthdayCheckTimer->start(1800000); // 30 minutes in milliseconds

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
    if (birthdayCheckTimer) {
        birthdayCheckTimer->stop();
    }
    delete ui;
}

void gestionemploye00::on_pushButton_6_clicked()
{
    Statistique *h = new Statistique();
    h->show();
}

void gestionemploye00::on_pushButton_10_clicked()
{
    Exporter *h = new Exporter();
    h->show();
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

void gestionemploye00::checkBirthdays()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Birthday check: Database not available";
        return;
    }

    QDate today = QDate::currentDate();
    qDebug() << "========================================";
    qDebug() << "🎂 Checking birthdays for date:" << today.toString("dd/MM/yyyy");
    qDebug() << "Current day:" << today.day() << "month:" << today.month();
    qDebug() << "========================================";

    QStringList birthdayToday;
    QStringList upcomingBirthdays;

    QSqlQuery query(db);
    query.prepare("SELECT nom, prenom, d_naissance FROM employe WHERE d_naissance IS NOT NULL");

    if (query.exec()) {
        int employeeCount = 0;
        while (query.next()) {
            employeeCount++;
            QString nom = query.value(0).toString();
            QString prenom = query.value(1).toString();
            QDate birthDate = query.value(2).toDate();

            qDebug() << "Employee" << employeeCount << ":" << prenom << nom;
            qDebug() << "  Birth date:" << birthDate.toString("dd/MM/yyyy");
            qDebug() << "  Birth day:" << birthDate.day() << "month:" << birthDate.month();

            if (birthDate.isValid()) {
                // Check if birthday is today
                if (birthDate.day() == today.day() && birthDate.month() == today.month()) {
                    qDebug() << "  ✅ BIRTHDAY TODAY!";
                    birthdayToday << QString("%1 %2").arg(prenom, nom);
                }
                // Check if birthday is in the next 7 days
                else {
                    QDate nextBirthday(today.year(), birthDate.month(), birthDate.day());
                    if (nextBirthday < today) {
                        nextBirthday = nextBirthday.addYears(1);
                    }

                    int daysUntil = today.daysTo(nextBirthday);
                    qDebug() << "  Days until birthday:" << daysUntil;

                    if (daysUntil > 0 && daysUntil <= 7) {
                        qDebug() << "  ✅ UPCOMING BIRTHDAY!";
                        upcomingBirthdays << QString("%1 %2 (%3 jours)").arg(prenom, nom).arg(daysUntil);
                    }
                }
            } else {
                qDebug() << "  ⚠️ Invalid birth date";
            }
        }
        qDebug() << "========================================";
        qDebug() << "Total employees checked:" << employeeCount;
        qDebug() << "Birthdays today:" << birthdayToday.size();
        qDebug() << "Upcoming birthdays:" << upcomingBirthdays.size();
        qDebug() << "========================================";
    } else {
        qDebug() << "⚠️ Query failed:" << query.lastError().text();
    }

    if (!birthdayToday.isEmpty() || !upcomingBirthdays.isEmpty()) {
        qDebug() << "📢 Showing birthday alert!";
        showBirthdayAlert(birthdayToday, upcomingBirthdays);
    } else {
        qDebug() << "ℹ️ No birthdays to show";
    }
}

void gestionemploye00::showBirthdayAlert(const QStringList &birthdayEmployees, const QStringList &upcomingBirthdays)
{
    // Create a beautiful custom message box
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("🎂 Alertes Anniversaires");

    QString message;

    // Birthday today section
    if (!birthdayEmployees.isEmpty()) {
        message += "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #FFD700, stop:1 #FFA500); "
                   "padding: 15px; border-radius: 10px; margin-bottom: 10px;'>";
        message += "<h2 style='color: #8B4513; margin: 0;'>🎉 Anniversaire Aujourd'hui! 🎉</h2>";
        message += "<ul style='color: #2F4F4F; font-size: 14px; font-weight: bold;'>";
        for (const QString &name : birthdayEmployees) {
            message += QString("<li style='margin: 5px 0;'>🎈 <b>%1</b></li>").arg(name);
        }
        message += "</ul>";
        message += "<p style='color: #8B4513; font-style: italic; margin: 10px 0 0 0;'>";
        message += "N'oubliez pas de souhaiter un joyeux anniversaire! 🎁</p>";
        message += "</div>";
    }

    // Upcoming birthdays section
    if (!upcomingBirthdays.isEmpty()) {
        message += "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #E6F3FF, stop:1 #CCE5FF); "
                   "padding: 15px; border-radius: 10px; margin-top: 10px;'>";
        message += "<h3 style='color: #2C5F8D; margin: 0 0 10px 0;'>📅 Anniversaires à Venir (7 jours)</h3>";
        message += "<ul style='color: #2F4F4F; font-size: 13px;'>";
        for (const QString &info : upcomingBirthdays) {
            message += QString("<li style='margin: 5px 0;'>🗓️ %1</li>").arg(info);
        }
        message += "</ul>";
        message += "</div>";
    }

    msgBox.setText(message);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);

    // Style the message box
    msgBox.setStyleSheet(
        "QMessageBox { "
        "   background-color: #FFFAF0; "
        "   min-width: 400px; "
        "}"
        "QMessageBox QLabel { "
        "   font-family: 'Segoe UI', Arial; "
        "   font-size: 14px; "
        "}"
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   border: none; "
        "   padding: 8px 20px; "
        "   border-radius: 5px; "
        "   font-weight: bold; "
        "   min-width: 80px; "
        "}"
        "QPushButton:hover { "
        "   background-color: #45a049; "
        "}"
        );

    msgBox.exec();
}

void gestionemploye00::updateBirthdayButton()
{
    qDebug() << "🔍 updateBirthdayButton() called";
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not valid or not open";
        return;
    }

    QDate today = QDate::currentDate();
    qDebug() << "📅 Today's date:" << today.toString("dd/MM/yyyy");
    int count = 0;

    QSqlQuery query(db);
    query.prepare("SELECT nom, prenom, d_naissance FROM employe WHERE d_naissance IS NOT NULL");

    if (query.exec()) {
        qDebug() << "✅ Query executed successfully";
        while (query.next()) {
            QString nom = query.value(0).toString();
            QString prenom = query.value(1).toString();
            QDate birthDate = query.value(2).toDate();

            qDebug() << "Employee:" << prenom << nom << "Birth date:" << birthDate.toString("dd/MM/yyyy");

            if (birthDate.isValid()) {
                // Check if birthday is today or in next 7 days
                if (birthDate.day() == today.day() && birthDate.month() == today.month()) {
                    qDebug() << "🎉 BIRTHDAY TODAY for" << prenom << nom;
                    count++;
                } else {
                    QDate nextBirthday(today.year(), birthDate.month(), birthDate.day());
                    if (nextBirthday < today) {
                        nextBirthday = nextBirthday.addYears(1);
                    }
                    int daysUntil = today.daysTo(nextBirthday);
                    qDebug() << "  Days until birthday:" << daysUntil;
                    if (daysUntil > 0 && daysUntil <= 7) {
                        qDebug() << "📅 UPCOMING BIRTHDAY for" << prenom << nom << "in" << daysUntil << "days";
                        count++;
                    }
                }
            } else {
                qDebug() << "⚠️ Invalid birth date for" << prenom << nom;
            }
        }
    } else {
        qDebug() << "❌ Query failed:" << query.lastError().text();
        return;
    }

    qDebug() << "📊 Total birthdays found:" << count;
    birthdayCount = count;

    if (count > 0) {
        birthdayButton->show();
        birthdayButton->setToolTip(QString("🎉 %1 anniversaire(s) ! Cliquez pour voir").arg(count));
        qDebug() << "🔔 Birthday button shown with count:" << count;

        // Add pulsing animation effect
        birthdayButton->setStyleSheet(
            "QPushButton {"
            "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
            "       stop:0 #FF1493, stop:0.5 #FFD700, stop:1 #FF1493);"
            "   border: 4px solid #FFD700;"
            "   border-radius: 35px;"
            "   font-size: 32px;"
            "   color: white;"
            "   font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
            "       stop:0 #FF69B4, stop:0.5 #FFE44D, stop:1 #FF69B4);"
            "   border: 5px solid #FFD700;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #FF1493;"
            "}"
            );
    } else {
        birthdayButton->hide();
        qDebug() << "🔕 No birthdays found, button hidden";
    }
}

void gestionemploye00::onBirthdayButtonClicked()
{
    // When user clicks the button, show the full birthday alert
    checkBirthdays();
}
