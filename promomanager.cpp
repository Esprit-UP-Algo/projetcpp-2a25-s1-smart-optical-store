#include "promomanager.h"
#include "ui_promomanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QRandomGenerator>
#include <QDebug>
#include <QCloseEvent>

PromoManager::PromoManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PromoManager),
    promoModel(nullptr)
{
    ui->setupUi(this);
    
    // Set dialog as modal to prevent interaction with parent window
    setModal(true);
    
    // Set dialog to be deleted when closed
    setAttribute(Qt::WA_DeleteOnClose, false);  // We'll manage deletion manually
    
    // Set today's date as default for start date
    ui->startDateEdit->setDate(QDate::currentDate());
    
    // Set end date to 30 days from now
    ui->endDateEdit->setDate(QDate::currentDate().addDays(30));
    
    // Setup table
    setupTable();
    
    // Refresh data
    refreshPromoTable();
    
    // Connect signals
    connect(ui->addButton, &QPushButton::clicked, this, &PromoManager::on_addButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &PromoManager::on_editButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &PromoManager::on_deleteButton_clicked);
    connect(ui->generateCodeButton, &QPushButton::clicked, this, &PromoManager::on_generateCodeButton_clicked);
    
    // Ensure Close button properly closes the dialog
    if (ui->buttonBox) {
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }
}

PromoManager::~PromoManager()
{
    delete ui;
    if (promoModel) {
        delete promoModel;
    }
}

void PromoManager::closeEvent(QCloseEvent *event)
{
    // Properly reject the dialog to close it
    reject();
    event->accept();
}

void PromoManager::setupTable()
{
    promoModel = new QSqlQueryModel(this);
    ui->promoTableView->setModel(promoModel);
    ui->promoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->promoTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->promoTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->promoTableView->horizontalHeader()->setStretchLastSection(true);
    ui->promoTableView->verticalHeader()->setVisible(false);
}

void PromoManager::refreshPromoTable()
{
    if (promoModel) {
        promoModel->setQuery("SELECT CODE, DESCRIPTION, POURCENTAGE_REMISE, DATE_DEBUT, DATE_FIN, ACTIF FROM CODE_PROMO ORDER BY DATE_DEBUT DESC");
        
        promoModel->setHeaderData(0, Qt::Horizontal, tr("Code"));
        promoModel->setHeaderData(1, Qt::Horizontal, tr("Description"));
        promoModel->setHeaderData(2, Qt::Horizontal, tr("Remise (%)"));
        promoModel->setHeaderData(3, Qt::Horizontal, tr("Date Début"));
        promoModel->setHeaderData(4, Qt::Horizontal, tr("Date Fin"));
        promoModel->setHeaderData(5, Qt::Horizontal, tr("Actif"));
        
        ui->promoTableView->resizeColumnsToContents();
    }
}

void PromoManager::on_generateCodeButton_clicked()
{
    // Generate a random promo code with letters and numbers
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString code;
    
    for (int i = 0; i < 8; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        code.append(chars.at(index));
    }
    
    ui->codeLineEdit->setText(code);
}

void PromoManager::on_addButton_clicked()
{
    QString code = ui->codeLineEdit->text().trimmed();
    QString description = ui->descriptionLineEdit->text().trimmed();
    double discount = ui->discountSpinBox->value();
    QDate startDate = ui->startDateEdit->date();
    QDate endDate = ui->endDateEdit->date();
    int active = ui->activeCheckBox->isChecked() ? 1 : 0;
    
    if (code.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez entrer un code promo!"));
        return;
    }
    
    if (discount <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le pourcentage de remise doit être supérieur à 0!"));
        return;
    }
    
    if (startDate > endDate) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date de fin doit être après la date de début!"));
        return;
    }
    
    // Check if code already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT CODE FROM CODE_PROMO WHERE CODE = :code");
    checkQuery.bindValue(":code", code);
    
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Ce code promo existe déjà!"));
        return;
    }
    
    // Insert new promo code
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO CODE_PROMO (CODE, DESCRIPTION, POURCENTAGE_REMISE, DATE_DEBUT, DATE_FIN, ACTIF) "
                        "VALUES (:code, :description, :discount, :startDate, :endDate, :active)");
    insertQuery.bindValue(":code", code);
    insertQuery.bindValue(":description", description);
    insertQuery.bindValue(":discount", discount);
    insertQuery.bindValue(":startDate", startDate);
    insertQuery.bindValue(":endDate", endDate);
    insertQuery.bindValue(":active", active);
    
    if (insertQuery.exec()) {
        QMessageBox::information(this, tr("Succès"), tr("Code promo ajouté avec succès!"));
        refreshPromoTable();
        
        // Clear form
        ui->codeLineEdit->clear();
        ui->descriptionLineEdit->clear();
        ui->discountSpinBox->setValue(0);
        ui->startDateEdit->setDate(QDate::currentDate());
        ui->endDateEdit->setDate(QDate::currentDate().addDays(30));
        ui->activeCheckBox->setChecked(true);
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ajout du code promo: %1").arg(insertQuery.lastError().text()));
    }
}

void PromoManager::on_editButton_clicked()
{
    if (!ui->promoTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez sélectionner un code promo à modifier!"));
        return;
    }
    
    int row = ui->promoTableView->selectionModel()->selectedRows().first().row();
    QString currentCode = promoModel->data(promoModel->index(row, 0)).toString();
    
    QString code = ui->codeLineEdit->text().trimmed();
    QString description = ui->descriptionLineEdit->text().trimmed();
    double discount = ui->discountSpinBox->value();
    QDate startDate = ui->startDateEdit->date();
    QDate endDate = ui->endDateEdit->date();
    int active = ui->activeCheckBox->isChecked() ? 1 : 0;
    
    if (code.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez entrer un code promo!"));
        return;
    }
    
    if (discount <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le pourcentage de remise doit être supérieur à 0!"));
        return;
    }
    
    if (startDate > endDate) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date de fin doit être après la date de début!"));
        return;
    }
    
    // Check if code already exists (but allow editing the same code)
    if (code != currentCode) {
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT CODE FROM CODE_PROMO WHERE CODE = :code");
        checkQuery.bindValue(":code", code);
        
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, tr("Erreur"), tr("Ce code promo existe déjà!"));
            return;
        }
    }
    
    // Update promo code
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE CODE_PROMO SET CODE = :code, DESCRIPTION = :description, POURCENTAGE_REMISE = :discount, "
                        "DATE_DEBUT = :startDate, DATE_FIN = :endDate, ACTIF = :active WHERE CODE = :currentCode");
    updateQuery.bindValue(":code", code);
    updateQuery.bindValue(":description", description);
    updateQuery.bindValue(":discount", discount);
    updateQuery.bindValue(":startDate", startDate);
    updateQuery.bindValue(":endDate", endDate);
    updateQuery.bindValue(":active", active);
    updateQuery.bindValue(":currentCode", currentCode);
    
    if (updateQuery.exec()) {
        QMessageBox::information(this, tr("Succès"), tr("Code promo modifié avec succès!"));
        refreshPromoTable();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la modification du code promo: %1").arg(updateQuery.lastError().text()));
    }
}

void PromoManager::on_deleteButton_clicked()
{
    if (!ui->promoTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez sélectionner un code promo à supprimer!"));
        return;
    }
    
    int row = ui->promoTableView->selectionModel()->selectedRows().first().row();
    QString code = promoModel->data(promoModel->index(row, 0)).toString();
    
    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirmation"), tr("Êtes-vous sûr de vouloir supprimer le code promo '%1'?").arg(code),
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM CODE_PROMO WHERE CODE = :code");
        deleteQuery.bindValue(":code", code);
        
        if (deleteQuery.exec()) {
            QMessageBox::information(this, tr("Succès"), tr("Code promo supprimé avec succès!"));
            refreshPromoTable();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la suppression du code promo: %1").arg(deleteQuery.lastError().text()));
        }
    }
}