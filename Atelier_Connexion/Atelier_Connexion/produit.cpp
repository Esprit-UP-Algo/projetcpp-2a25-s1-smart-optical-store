#include "produit.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>



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
    this->ref = ui->lineEdit_3->text();
    this->designation = ui->lineEdit_2->text();
    this->quantite = ui->lineEdit_9->text().toInt();
    this->prix = ui->lineEdit_29->text().toDouble();
    this->categorie = ui->comboBox_2->currentText();
    this->couleur = ui->lineEdit_8->text();
    this->setgenre(ui);
    this->marque = ui->lineEdit_7->text();
    this->dateExpiration = ui->dateEdit->date();
}
bool Produit::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (REF, DESIGNATION, CATEGORIE, MARQUE, PRIX, QUANTITE, COULEUR, GENRE, DATEEXPIRATION) "
                  "VALUES (:ref, :designation, :categorie, :marque, :prix, :quantite, :couleur, :genre, :dateExpiration)");

    query.bindValue(":ref", ref);
    query.bindValue(":designation", designation);
    query.bindValue(":categorie", categorie);
    query.bindValue(":marque", marque);
    query.bindValue(":genre", genre);
    query.bindValue(":couleur", couleur);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":dateExpiration", dateExpiration);

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
    query.prepare("SELECT * FROM PRODUITS");

    if (query.exec())
    {
        ui->tableWidget->setRowCount(0); // clear table first
        int row = 0;

        while (query.next())
        {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REF").toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("PRIX").toString()));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString()));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString()));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString()));
            ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString()));
            ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toString()));

            row++;
        }
    }
}
bool Produit::supprimer(QString ref)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUITS WHERE REF = :ref");
    query.bindValue(":ref", ref);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression produit:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Produit::existe(QString ref)
{
    QSqlQuery query;
    query.prepare("SELECT REF FROM PRODUITS WHERE REF = :ref");
    query.bindValue(":ref", ref);
    query.exec();
    return query.next();
}
bool Produit::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUITS WHERE REF LIKE :rech OR DESIGNATION LIKE :rech");
    query.bindValue(":rech", "%" + recherche + "%");

    if (!query.exec()) {
        qDebug() << " Erreur recherche:" << query.lastError().text();
        return false;
    }

    QTableWidget *table = ui->tableWidget;
    table->setRowCount(0);
    int row = 0;

    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("REF").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("PRIX").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString()));
        table->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString()));
        table->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toString()));
        row++;
    }

    if (row == 0)
        qDebug() << " Aucun résultat trouvé pour:" << recherche;
    else
        qDebug() << "" << row << "résultat(s) trouvé(s).";

    return row > 0;
}

bool Produit:: modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE PRODUITS SET COULEUR=:couleur, GENRE=:genre, PRIX=:prix, QUANTITE=:quantite, MARQUE=:marque, CATEGORIE=:categorie, DESIGNATION=:designation, DATEEXPIRATION=:dateexpiration "
                  "WHERE REF=:ref");

    query.bindValue(":ref", ref);
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":marque", marque);
    query.bindValue(":categorie", categorie);
    query.bindValue(":designation", designation);
    query.bindValue(":dateExpiration", dateExpiration);


    bool test = query.exec();

    if (test)
        qDebug() << " Modification réussie pour le produit:" ;
    else
        qDebug() << " Erreur de modification:" << query.lastError().text();

    return test;
}





Produit::~Produit() {}
