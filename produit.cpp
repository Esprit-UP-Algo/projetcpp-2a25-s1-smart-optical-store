#include "produit.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


//m
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
    this->prix = ui->lineEdit_36->text().toDouble();
    this->categorie = ui->comboBox_4->currentText();
    this->couleur = ui->lineEdit_8->text();
    this->setgenre(ui);
    this->marque = ui->lineEdit_7->text();
    this->dateExpiration = ui->dateEdit->date();
}
bool Produit::ajouter()
{

    QSqlQuery query;
    // Table name is PRODUIT (singular) and column is REFERENCE (not REF)
    query.prepare("INSERT INTO PRODUIT (REFERENCE, DESIGNATION, CATEGORIE, MARQUE, PRIX, QUANTITE, COULEUR, GENRE, DATE_EXPIRATION) "
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
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not connected in afficher()";
        return;
    }

    QSqlQuery query(db);
    // Table name is PRODUIT (singular) and column is REFERENCE (not REF)
    query.prepare("SELECT * FROM PRODUIT ORDER BY REFERENCE");

    if (!query.exec()) {
        qDebug() << "❌ Error in afficher():" << query.lastError().text();
        qDebug() << "   Database:" << db.databaseName();
        qDebug() << "   Is Open:" << db.isOpen();
        qDebug() << "   Is Valid:" << db.isValid();
        // Try alternative table name (case sensitivity)
        query.prepare("SELECT * FROM produit ORDER BY REFERENCE");
        if (!query.exec()) {
            qDebug() << "❌ Error with lowercase table name:" << query.lastError().text();
            return;
        }
    }

    ui->tableWidget->setRowCount(0); // clear table first
    int row = 0;

    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        // Column order: {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"}
        // Database columns: REFERENCE, DESIGNATION, QUANTITE, PRIX, CATEGORIE, COULEUR, GENRE, MARQUE, DATE_EXPIRATION
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString())); // Id (REFERENCE)
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("DESIGNATION").toString())); // Nom
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("COULEUR").toString())); // Couleur
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("GENRE").toString())); // Genre
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(query.value("PRIX").toDouble(), 'f', 2))); // Prix
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("QUANTITE").toString())); // Quantité
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("MARQUE").toString())); // Marque
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("REFERENCE").toString())); // Référence
        // Fournisseur - set to "N/A" for now (can be joined later if needed)
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem("N/A")); // Fournisseur

        row++;
    }
    
    qDebug() << "✅ Loaded" << row << "products from database";
}
bool Produit::supprimer(QString ref)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUIT WHERE REFERENCE = :ref");
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
    query.prepare("SELECT REFERENCE FROM PRODUIT WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);
    query.exec();
    return query.next();
}
bool Produit::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT WHERE REFERENCE LIKE :rech OR DESIGNATION LIKE :rech");
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
        // Column order: {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"}
        table->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString())); // Id
        table->setItem(row, 1, new QTableWidgetItem(query.value("DESIGNATION").toString())); // Nom
        table->setItem(row, 2, new QTableWidgetItem(query.value("COULEUR").toString())); // Couleur
        table->setItem(row, 3, new QTableWidgetItem(query.value("GENRE").toString())); // Genre
        table->setItem(row, 4, new QTableWidgetItem(QString::number(query.value("PRIX").toDouble(), 'f', 2))); // Prix
        table->setItem(row, 5, new QTableWidgetItem(query.value("QUANTITE").toString())); // Quantité
        table->setItem(row, 6, new QTableWidgetItem(query.value("MARQUE").toString())); // Marque
        table->setItem(row, 7, new QTableWidgetItem(query.value("REFERENCE").toString())); // Référence
        table->setItem(row, 8, new QTableWidgetItem("N/A")); // Fournisseur
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

    query.prepare("UPDATE PRODUIT SET COULEUR=:couleur, GENRE=:genre, PRIX=:prix, QUANTITE=:quantite, MARQUE=:marque, CATEGORIE=:categorie, DESIGNATION=:designation, DATE_EXPIRATION=:dateExpiration "
                  "WHERE REFERENCE=:ref");

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
void Produit::afficherRestock(Ui::MainWindow *ui, int seuil)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT WHERE QUANTITE < :seuil ORDER BY QUANTITE ASC");
    query.bindValue(":seuil", seuil);

    if (!query.exec()) {
        qDebug() << "Erreur restock :" << query.lastError().text();
        return;
    }

    ui->tableWidget->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REF").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("DESIGNATION").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("QUANTITE").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MARQUE").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("CATEGORIE").toString()));
        row++;
    }
}






Produit::~Produit() {}
