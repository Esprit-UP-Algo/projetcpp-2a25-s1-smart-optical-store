#include "fournisseurwindow.h"
#include "fournisseur.h"
#include "ui_fournisseurwindow.h"
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "gestionemploye00.h"
#include "dashboardwindow.h"
#include "WindowManager.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFileDialog>



#include <QMouseEvent>
#include "Connection.h"
#include "fournisseur.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDateEdit>
#include <QDate>

// Initialize static instance pointer
FournisseurWindow* FournisseurWindow::instance = nullptr;

FournisseurWindow* FournisseurWindow::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new FournisseurWindow(parent);
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

FournisseurWindow::FournisseurWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FournisseurWindow)
    , selectedId(-1)
    , currentFournisseurId(-1)
    , isEditing(false)
{
    ui->setupUi(this);

    afficherFournisseurs();

        // Désactiver le bouton Supprimer tant qu’aucune ligne n’est sélectionnée
        ui->pushButton_delete->setEnabled(false);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Fournisseurs", 1200, 800);
    
    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
    }
    
    // Configure table widget
    if (ui->tableWidget_2) {
        ui->tableWidget_2->setColumnCount(8);
        QStringList headers = {"ID", "Nom Entreprise", "Nom Contact", "Email", "Téléphone", 
                               "Type Produit", "Condition Paiement", "Historique"};
        ui->tableWidget_2->setHorizontalHeaderLabels(headers);
        ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    
    // ID field is read-only
    if (ui->lineEdit) {
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit->setPlaceholderText("Auto");
    }
    
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
    
    // Setup date picker
    if (ui->dateEdit) {
        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit->setDisplayFormat("dd/MM/yyyy");
        ui->dateEdit->setCalendarPopup(true);
    }
    
    // Make logo clickable
    if (ui->logoLabel) {
        ui->logoLabel->setCursor(Qt::PointingHandCursor);
        ui->logoLabel->installEventFilter(this);
        ui->logoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Wire tableau de bord buttons by their visible text to avoid object-name differences
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                MainWindow::getInstance();
                this->close();
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
                this->raise();
                this->activateWindow();
            });
        }
    }
    
    // Connect table double-click
    if (ui->tableWidget_2) {
        connect(ui->tableWidget_2, &QTableWidget::cellDoubleClicked, 
                this, &FournisseurWindow::on_tableWidget_2_cellDoubleClicked);
    }
    
    // Load data on startup
    loadFournisseurs();
    clearForm();
}

FournisseurWindow::~FournisseurWindow()
{
    delete ui;
}
void FournisseurWindow::afficherFournisseurs()
{
    QSqlQuery query("SELECT * FROM FOURNISSEUR");

    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->setRowCount(0);

    QStringList headers;
    headers << "ID" << "Entreprise" << "Contact" << "Email"
            << "Téléphone" << "Type Produit" << "Condition" << "Historique";
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next())
    {
        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(query.value(7).toDate().toString("dd/MM/yyyy")));
        row++;
    }

    ui->tableWidget_2->resizeColumnsToContents();
    qDebug() << "Affichage de" << row << "fournisseur(s)";
}

void FournisseurWindow::on_tableWidget_2_itemClicked()
{
    int row = ui->tableWidget_2->currentRow();

    if (row >= 0)
    {
        selectedId = ui->tableWidget_2->item(row, 0)->text().toInt();

        ui->lineEdit->setText(ui->tableWidget_2->item(row, 0)->text());
        ui->lineEdit_3->setText(ui->tableWidget_2->item(row, 1)->text());
        ui->lineEdit_4->setText(ui->tableWidget_2->item(row, 2)->text());
        ui->lineEdit_5->setText(ui->tableWidget_2->item(row, 3)->text());
        ui->lineEdit_6->setText(ui->tableWidget_2->item(row, 4)->text());
        ui->lineEdit_13->setText(ui->tableWidget_2->item(row, 5)->text());
        ui->lineEdit_12->setText(ui->tableWidget_2->item(row, 6)->text());
        ui->lineEdit_11->setText(ui->tableWidget_2->item(row, 7)->text());

        ui->pushButton_delete->setEnabled(true); // activer le bouton Supprimer
    }
}

// Removed duplicate function definitions - using newer implementations below

bool FournisseurWindow::eventFilter(QObject *obj, QEvent *event)
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

void FournisseurWindow::on_logoClicked()
{
    DashboardWindow::getInstance();
    this->close();
}

void FournisseurWindow::loadFournisseurs()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Database not connected in fournisseur window";
        return;
    }
    
    QSqlQuery query(db);
    QString sql = "SELECT ID_FOURNISSEUR, NOM_ENTREPRISE, NOM_CONTACT, EMAIL, TELEPHONE, "
                  "TYPE_PRODUIT_FOURNIS, CONDITION_PAIEMENT, HISTORIQUE_COMMANDE_PASSEE "
                  "FROM FOURNISSEUR ORDER BY ID_FOURNISSEUR";
    
    if (!query.exec(sql)) {
        // Try with lowercase
        query.clear();
        sql = "SELECT id_fournisseur, nom_entreprise, nom_contact, email, telephone, "
              "type_produit_fournis, condition_paiement, historique_commande_passee "
              "FROM fournisseur ORDER BY id_fournisseur";
        if (!query.exec(sql)) {
            QMessageBox::critical(this, "Erreur", "Erreur lors du chargement des fournisseurs: " + query.lastError().text());
            return;
        }
    }
    
    ui->tableWidget_2->setRowCount(0);
    int row = 0;
    
    while (query.next()) {
        ui->tableWidget_2->insertRow(row);
        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget_2->setItem(row, col, item);
        }
        row++;
    }
    
    qDebug() << "✅ " << row << " fournisseurs chargés";
}

void FournisseurWindow::clearForm()
{
    isEditing = false;
    currentFournisseurId = -1;
    if (ui->lineEdit) ui->lineEdit->clear();
    if (ui->lineEdit_3) ui->lineEdit_3->clear();
    if (ui->lineEdit_4) ui->lineEdit_4->clear();
    if (ui->lineEdit_5) ui->lineEdit_5->clear();
    if (ui->lineEdit_6) ui->lineEdit_6->clear();
    if (ui->lineEdit_11) ui->lineEdit_11->clear();
    if (ui->lineEdit_12) ui->lineEdit_12->clear();
    if (ui->dateEdit) ui->dateEdit->setDate(QDate::currentDate());
    if (ui->tableWidget_2) ui->tableWidget_2->clearSelection();
}

void FournisseurWindow::fillForm(int row)
{
    if (!ui->tableWidget_2 || row < 0 || row >= ui->tableWidget_2->rowCount()) return;
    
    isEditing = true;
    
    QTableWidgetItem *idItem = ui->tableWidget_2->item(row, 0);
    if (idItem) {
        currentFournisseurId = idItem->text().toInt();
        if (ui->lineEdit) ui->lineEdit->setText(idItem->text());
    }
    
    QTableWidgetItem *item = ui->tableWidget_2->item(row, 1);
    if (item && ui->lineEdit_3) ui->lineEdit_3->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 2);
    if (item && ui->lineEdit_4) ui->lineEdit_4->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 3);
    if (item && ui->lineEdit_5) ui->lineEdit_5->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 4);
    if (item && ui->lineEdit_6) ui->lineEdit_6->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 5);
    if (item && ui->lineEdit_11) ui->lineEdit_11->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 6);
    if (item && ui->lineEdit_12) ui->lineEdit_12->setText(item->text());
    
    item = ui->tableWidget_2->item(row, 7);
    if (item && ui->dateEdit) {
        // Try to parse the date from various formats
        QString dateStr = item->text();
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (!date.isValid()) {
            date = QDate::fromString(dateStr, "yyyy-MM-dd");
        }
        if (!date.isValid()) {
            date = QDate::fromString(dateStr, "MM/dd/yyyy");
        }
        if (date.isValid()) {
            ui->dateEdit->setDate(date);
        } else {
            ui->dateEdit->setDate(QDate::currentDate());
        }
    }
}

void FournisseurWindow::on_pushButton_ajouter_clicked()
{
    QString nomEntreprise = ui->lineEdit_3 ? ui->lineEdit_3->text().trimmed() : "";
    QString nomContact = ui->lineEdit_4 ? ui->lineEdit_4->text().trimmed() : "";
    QString email = ui->lineEdit_5 ? ui->lineEdit_5->text().trimmed() : "";
    QString telephone = ui->lineEdit_6 ? ui->lineEdit_6->text().trimmed() : "";
    QString typeProduit = ui->lineEdit_11 ? ui->lineEdit_11->text().trimmed() : "";
    QString conditionPaiement = ui->lineEdit_12 ? ui->lineEdit_12->text().trimmed() : "";
    QString historique = ui->dateEdit ? ui->dateEdit->date().toString("dd/MM/yyyy") : "";
    
    if (nomEntreprise.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom de l'entreprise est obligatoire!");
        if (ui->lineEdit_3) ui->lineEdit_3->setFocus();
        return;
    }
    
    // Validation email - must contain "@"
    if (!email.isEmpty() && !email.contains('@')) {
        QMessageBox::warning(this, "Validation", "L'adresse e-mail doit contenir le caractère '@'.");
        if (ui->lineEdit_5) {
            ui->lineEdit_5->setFocus();
            ui->lineEdit_5->selectAll();
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
    
    Fournisseur f;
    f.set_nom_entreprise(nomEntreprise);
    f.set_nom_contact(nomContact);
    f.set_email(email);
    f.set_telephone(telephone);
    f.set_type_produit_fournis(typeProduit);
    f.set_condition_paiement(conditionPaiement.toInt());
    QDate histDate = QDate::fromString(historique, "dd/MM/yyyy");
    if (!histDate.isValid()) {
        histDate = QDate::currentDate();
    }
    f.set_historique(histDate);
    
    if (isEditing && currentFournisseurId > 0) {
        f.set_id_fournisseur(currentFournisseurId);
        if (f.modifier(currentFournisseurId)) {
            QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès!");
            clearForm();
            loadFournisseurs();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du fournisseur.");
        }
    } else {
        if (f.ajouter()) {
            QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès!");
            clearForm();
            loadFournisseurs();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du fournisseur.");
        }
    }
}

void FournisseurWindow::on_pushButton_modifier_clicked()
{
    int currentRow = ui->tableWidget_2 ? ui->tableWidget_2->currentRow() : -1;
    if (currentRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un fournisseur à modifier!");
        return;
    }
    
    fillForm(currentRow);
}

void FournisseurWindow::on_pushButton_delete_clicked()
{
    int currentRow = ui->tableWidget_2 ? ui->tableWidget_2->currentRow() : -1;
    if (currentRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un fournisseur à supprimer!");
        return;
    }
    
    QTableWidgetItem *idItem = ui->tableWidget_2->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Attention", "Impossible de récupérer l'ID du fournisseur!");
        return;
    }
    
    int fournisseurId = idItem->text().toInt();
    QString nomEntreprise = ui->tableWidget_2->item(currentRow, 1)->text();
    
    int ret = QMessageBox::question(this, "Confirmation",
                                    QString("Êtes-vous sûr de vouloir supprimer le fournisseur %1 (ID: %2) ?")
                                        .arg(nomEntreprise).arg(fournisseurId),
                                    QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        Fournisseur f;
        if (f.supprimer(fournisseurId)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès!");
            loadFournisseurs();
            clearForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du fournisseur.");
        }
    }
}

void FournisseurWindow::on_pushButton_modifier_3_clicked()
{
    loadFournisseurs();
}

void FournisseurWindow::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    fillForm(row);
}



