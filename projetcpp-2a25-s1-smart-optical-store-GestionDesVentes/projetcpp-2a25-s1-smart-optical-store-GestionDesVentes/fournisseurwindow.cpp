#include "fournisseurwindow.h"
#include "fournisseur.h"
#include "ui_fournisseurwindow.h"
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "gestionemploye00.h"
#include "WindowManager.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFileDialog>



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
    , ui(new Ui::FournisseurWindow),selectedId(-1)

{
    ui->setupUi(this);

    afficherFournisseurs();

        // Désactiver le bouton Supprimer tant qu’aucune ligne n’est sélectionnée
        ui->pushButton_delete->setEnabled(false);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Fournisseurs", 1200, 800);
    
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

void FournisseurWindow::on_pushButton_ajouter_clicked()
{
    QString idStr = ui->lineEdit->text();
    QString nom_ent = ui->lineEdit_3->text();
    QString nom_cont = ui->lineEdit_4->text();
    QString email = ui->lineEdit_5->text();
    QString tel = ui->lineEdit_6->text();
    QString type_prod = ui->lineEdit_13->text();
    QString condStr = ui->lineEdit_12->text();
    QString histStr = ui->lineEdit_11->text();

    // === VALIDATIONS ===
    if (idStr.isEmpty() || !QRegularExpression("^[0-9]+$").match(idStr).hasMatch()) {
        QMessageBox::warning(this, "Attention", "L'ID doit contenir uniquement des chiffres !");
        return;
    }
    if (!QRegularExpression("^\\d{8}$").match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Le téléphone doit avoir 8 chiffres !");
        return;
    }
    if (!QRegularExpression("^[01]$").match(condStr).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Condition paiement doit être 0 ou 1 !");
        return;
    }

    QDate hist = QDate::fromString(histStr, "dd/MM/yyyy");
    if (!hist.isValid()) {
        QMessageBox::warning(this, "Attention", "Format date : jj/MM/aaaa !");
        return;
    }

    int id = idStr.toInt();
    int cond_paie = condStr.toInt();

    Fournisseur F(id, nom_ent, nom_cont, email, tel, type_prod, cond_paie, hist);

    if (F.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté !");
        afficherFournisseurs();
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout échoué !");
    }
}

void FournisseurWindow::on_pushButton_modifier_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Sélectionnez un fournisseur !");
        return;
    }

    QString nom_ent = ui->lineEdit_3->text();
    QString nom_cont = ui->lineEdit_4->text();
    QString email = ui->lineEdit_5->text();
    QString tel = ui->lineEdit_6->text();
    QString type_prod = ui->lineEdit_13->text();
    QString condStr = ui->lineEdit_12->text();
    QString histStr = ui->lineEdit_11->text();

    if (!QRegularExpression("^\\d{8}$").match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Téléphone invalide !");
        return;
    }

    int cond_paie = condStr.toInt();
    QDate hist = QDate::fromString(histStr, "dd/MM/yyyy");

    Fournisseur F(selectedId, nom_ent, nom_cont, email, tel, type_prod, cond_paie, hist);

    if (F.modifier(selectedId)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié !");
        afficherFournisseurs();
    } else {
        QMessageBox::critical(this, "Erreur", "Modification échouée !");
    }
}

void FournisseurWindow::on_pushButton_delete_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un fournisseur à supprimer !");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce fournisseur ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Fournisseur f;
        if (f.supprimer(selectedId)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès !");
            afficherFournisseurs();
            selectedId = -1;
            ui->pushButton_delete->setEnabled(false);

            ui->lineEdit->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_13->clear();
            ui->lineEdit_12->clear();
            ui->lineEdit_11->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}



