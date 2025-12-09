#include "produit.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "smtp.h"



void Produit::setgenre(Ui::MainWindow *ui) {
    if (ui->radioButton->isChecked()) {
        genre = "Homme";
    }
    else if (ui->radioButton_2->isChecked()) {
        genre = "Femme";
    }
    else {
        genre = "         ∅";
    }
}
Produit::Produit(Ui::MainWindow *ui)
{
    this->reference = ui->lineEdit_3->text();
    this->designation = ui->lineEdit_des->text();
    this->quantite = ui->lineEdit_9->text().toInt();
    this->prix = ui->lineEdit_29->text().toDouble();
    this->categorie = ui->comboBox_2->currentText();
    this->couleur = ui->lineEdit_8->text();
    this->setgenre(ui);
    this->marque = ui->lineEdit_7->text();
    this->dateExpiration = ui->dateEdit->date();
    this->id_four = ui->comboBox_idFour->currentData().toInt();

}

QString Produit::getEmployeeEmail()
{
    QSqlQuery query;

    query.prepare(
        "SELECT EMAIL FROM EMPLOYE "
        "WHERE UPPER(POSTE) IN ('RESPONSABLE STOCK')"
        );

    if (query.exec() && query.next()) {
        QString email = query.value("EMAIL").toString();
        qDebug() << "Employee email found:" << email;
        return email;
    } else {
        qDebug() << "No employee found with required role. Error:"
                 << query.lastError().text();
        return "";
    }
}



void Produit::checkLowQuantity()
{
    if (quantite < 10) {
        QString email = getEmployeeEmail(); // get employee email once

        if (!email.isEmpty()) {
            Smtp mail;
            mail.setUser("hamza.benabdallah999@gmail.com"); // your email
            mail.setPassword("jalwjudvgrewrvyp");      // your app password

            mail.sendMail(
                "meriemlaabidi21@gmail.com", // from
                email,                       // to
                "Alerte Stock Faible",       // subject
                QString("Bonjour,\n\n"
                        "Le produit '%1' (Référence: %2) a un stock faible: %3 unités.\n"
                        "Veuillez envisager un réapprovisionnement.\n\n"
                        "Cordialement,\nVotre système de gestion")
                    .arg(designation)
                    .arg(reference)
                    .arg(quantite)             // message body
                );

            qDebug() << "Email d'alerte envoyé à:" << email;
        } else {
            qDebug() << "Aucun employé trouvé pour envoyer l'alerte";
        }
    }
}




bool Produit::ajouter()
{
    checkLowQuantity();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO PRODUIT "
        "(REFERENCE, DESIGNATION, CATEGORIE, MARQUE, PRIX, QUANTITE, "
        "COULEUR, GENRE, DATEEXPIRATION, ID_FOUR) "
        "VALUES (:reference, :designation, :categorie, :marque, :prix, "
        ":quantite, :couleur, :genre, :dateExpiration, :id_four)"
        );

    query.bindValue(":reference", reference);
    query.bindValue(":designation", designation);
    query.bindValue(":categorie", categorie);
    query.bindValue(":marque", marque);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":dateExpiration", dateExpiration);
    query.bindValue(":id_four", id_four);

    if (!query.exec())
    {
        qDebug() << "Erreur lors de l'ajout du produit :" << query.lastError().text();
        return false;
    }
    return true;
}
void Produit::afficher(Ui::MainWindow *ui)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT");

    if (query.exec())
    {
        ui->tableWidget->setRowCount(0); // clear table first
        int row = 0;

        while (query.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("PRIX").toString()));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString()));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString()));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString()));
            ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString()));
            //ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toString()));
            ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toDate().toString("dd/MM/yyyy")));
            ui->tableWidget->setItem(row, 9, new QTableWidgetItem(query.value("ID_FOUR").toString()));

            row++;
        }
    }
}
bool Produit::supprimer(QString reference)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUIT WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression produit:" << query.lastError().text();
        return false;
    }
    
    // Check if any row was actually deleted
    int rowsAffected = query.numRowsAffected();
    qDebug() << "Rows deleted:" << rowsAffected << "for reference:" << reference;
    
    if (rowsAffected <= 0) {
        qDebug() << "No product found with reference:" << reference;
        return false;
    }
    
    return true;
}
bool Produit::existe(QString reference)
{
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM PRODUIT WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);
    query.exec();
    return query.next();
}
bool Produit::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT WHERE REFERENCE = :ref OR DESIGNATION LIKE :des");
    query.bindValue(":ref", recherche);
    query.bindValue(":des", "%" + recherche + "%");

    if (!query.exec()) {
        qDebug() << "Erreur recherche:" << query.lastError().text();
        return false;
    }

    QTableWidget *table = ui->tableWidget;
    table->setRowCount(0);
    int row = 0;

    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("PRIX").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString()));
        table->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString()));
        table->setItem(row, 8, new QTableWidgetItem(query.value("DATE_EXPIRATION").toDate().toString("yyyy-MM-dd")));
        row++;
    }

    if (row == 0)
        qDebug() << "Aucun résultat trouvé pour:" << recherche;
    else
        qDebug() << row << "résultat(s) trouvé(s).";

    return row > 0;
}


bool Produit:: modifier()
{
    checkLowQuantity();

    QSqlQuery query;

    query.prepare(
        "UPDATE PRODUIT SET "
        "COULEUR=:couleur, GENRE=:genre, PRIX=:prix, QUANTITE=:quantite, "
        "MARQUE=:marque, CATEGORIE=:categorie, DESIGNATION=:designation, "
        "DATEEXPIRATION=:dateExpiration, ID_FOUR=:id_four "
        "WHERE REFERENCE=:reference"
        );

    query.bindValue(":reference", reference);
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":marque", marque);
    query.bindValue(":categorie", categorie);
    query.bindValue(":designation", designation);
    query.bindValue(":dateExpiration", dateExpiration);
    query.bindValue(":id_four", id_four);

    bool test = query.exec();

    if (test)
        qDebug() << " Modification réussie pour le produit:" ;
    else
        qDebug() << " Erreur de modification:" << query.lastError().text();

    return test;
}






Produit::~Produit() {}
