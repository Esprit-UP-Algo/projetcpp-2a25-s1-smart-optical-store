#include "gclient1.h"
#include "ui_gclient1.h"
//#include "ui_mainwindow.h"

#include "connexion.h"
#include <QHeaderView>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QAbstractItemView>
#include <QRegularExpression>

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients),
    isEditing(false),
    currentClientId(-1)
{
    ui->setupUi(this);

    // Redimensionner la fenêtre
    this->resize(1200, 800);
    this->showMaximized();

    // Configuration de la table
    if (ui->tableWidgetClients) {
        ui->tableWidgetClients->setColumnCount(8);
        ui->tableWidgetClients->setHorizontalHeaderLabels(
            QStringList() << "ID" << "Nom" << "Prénom" << "Date Naissance"
                          << "Sexe" << "Adresse" << "Téléphone" << "Email");
        ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidgetClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidgetClients->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // Configuration du formulaire
    ui->lineEditID->setReadOnly(true);
    ui->lineEditID->setPlaceholderText("Auto-généré");
    ui->dateEditNaissance->setDate(QDate::currentDate());
    ui->dateEditNaissance->setCalendarPopup(true);

    // Configuration du ComboBox Sexe
    ui->comboBoxSexe->clear();
    ui->comboBoxSexe->addItem("Homme");
    ui->comboBoxSexe->addItem("Femme");

    // Charger le logo
    QString logoPath = "./smart_logo.png";
    QPixmap logo(logoPath);

    if (!logo.isNull()) {
        ui->labelLogoTopRight->setPixmap(logo);
        ui->labelLogoTopRight->setScaledContents(true);
        ui->labelLogoTopRight->setMaximumSize(50, 50);
    } else {
        qDebug() << "⚠️ Logo non trouvé à " << logoPath;
    }

    // Connecter les signaux
    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &Gclient1::on_lineEditSearch_textChanged);
    connect(ui->comboBoxTri, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Gclient1::on_comboBoxTri_currentIndexChanged);
    connect(ui->tableWidgetClients, &QTableWidget::cellDoubleClicked,
            this, &Gclient1::on_tableWidgetClients_cellDoubleClicked);
    connect(ui->tabWidgetMain, &QTabWidget::currentChanged,
            this, &Gclient1::on_tabWidgetMain_currentChanged);

    // Initialiser le formulaire
    clearForm();

    qDebug() << "✅ Interface GestionClients initialisée avec succès";
}

Gclient1::~Gclient1()
{
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
    QString sqlQuery = "SELECT ID_CLIENT, NOM, PRENOM, DATE_NAISSANCE, SEXE, ADRESSE, TELEPHONE, EMAIL FROM CLIENT WHERE 1=1";

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
        query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, DATE_NAISSANCE = :dateNaissance, "
                      "SEXE = :sexe, ADRESSE = :adresse, EMAIL = :email, TELEPHONE = :telephone "
                      "WHERE ID_CLIENT = :id");
        query.bindValue(":id", currentClientId);
    } else {
        query.prepare("INSERT INTO CLIENT (NOM, PRENOM, DATE_NAISSANCE, SEXE, ADRESSE, EMAIL, TELEPHONE) "
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
        query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
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
    if (index == 1 && !isEditing) {
        clearForm();
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
