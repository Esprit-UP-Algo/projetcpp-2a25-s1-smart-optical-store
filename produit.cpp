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
    this->categorie = ui->comboBox_2->currentText();
    this->couleur = ui->lineEdit_8->text();
    this->setgenre(ui);
    this->marque = ui->lineEdit_7->text();
    this->dateExpiration = ui->dateEdit->date();
}
bool Produit::ajouter()
{

    QSqlQuery query;
    // Table name is PRODUIT (singular) and column is REFERENCE (not REF)
    // REFERENCE is a VARCHAR/STRING column - accepts alphanumeric values like "C12", "REF47", etc.
    query.prepare("INSERT INTO PRODUIT (REFERENCE, DESIGNATION, CATEGORIE, MARQUE, PRIX, QUANTITE, COULEUR, GENRE, DATEEXPIRATION) "
                  "VALUES (:ref, :designation, :categorie, :marque, :prix, :quantite, :couleur, :genre, :dateExpiration)");

    query.bindValue(":ref", ref);  // String reference (e.g., "C12", "REF47")
    query.bindValue(":designation", designation);
    query.bindValue(":categorie", categorie);
    query.bindValue(":marque", marque);
    query.bindValue(":genre", genre);
    query.bindValue(":couleur", couleur);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":dateExpiration", dateExpiration);

    qDebug() << "➕ Adding product with reference (string):" << ref;
    if (!query.exec())
    {
        qDebug() << "❌ Erreur lors de l'ajout du produit :" << query.lastError().text();
        qDebug() << "   Reference used:" << ref;
        return false;
    }
    qDebug() << "✅ Product added successfully with reference:" << ref;
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
        // Database columns: REFERENCE, DESIGNATION, QUANTITE, PRIX, CATEGORIE, COULEUR, GENRE, MARQUE, DATEEXPIRATION
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString())); // Référence
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString())); // Couleur
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString())); // Genre
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(query.value("PRIX").toDouble(), 'f', 2))); // Prix
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString())); // Quantité
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString())); // Marque
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString())); // Catégorie
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString())); // Designation
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toDate().toString("yyyy-MM-dd"))); // Date d'expiration

        row++;
    }
    
    qDebug() << "✅ Loaded" << row << "products from database";
}
bool Produit::supprimer(QString ref)
{
    QSqlQuery query;
    // REFERENCE is a VARCHAR/STRING column - accepts alphanumeric values like "C12", "REF47", etc.
    query.prepare("DELETE FROM PRODUIT WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);  // String reference (e.g., "C12", "REF47")

    qDebug() << "🗑️ Deleting product with reference (string):" << ref;
    if (!query.exec())
    {
        qDebug() << "❌ Erreur suppression produit:" << query.lastError().text() << "pour référence:" << ref;
        return false;
    }
    qDebug() << "✅ Product deleted successfully with reference:" << ref;
    return true;
}
bool Produit::existe(QString ref)
{
    QSqlQuery query;
    // REFERENCE is a VARCHAR/STRING column - accepts alphanumeric values like "C12", "REF47", etc.
    query.prepare("SELECT REFERENCE FROM PRODUIT WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);  // String reference (e.g., "C12", "REF47")
    if (!query.exec()) {
        qDebug() << "❌ Error checking if product exists:" << query.lastError().text();
        return false;
    }
    bool exists = query.next();
    qDebug() << "🔍 Product with reference" << ref << (exists ? "exists" : "does not exist");
    return exists;
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
        // Column order: {"Référence", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Catégorie", "Designation", "Date d'expiration"}
        table->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString())); // Référence
        table->setItem(row, 1, new QTableWidgetItem(query.value("COULEUR").toString())); // Couleur
        table->setItem(row, 2, new QTableWidgetItem(query.value("GENRE").toString())); // Genre
        table->setItem(row, 3, new QTableWidgetItem(QString::number(query.value("PRIX").toDouble(), 'f', 2))); // Prix
        table->setItem(row, 4, new QTableWidgetItem(query.value("QUANTITE").toString())); // Quantité
        table->setItem(row, 5, new QTableWidgetItem(query.value("MARQUE").toString())); // Marque
        table->setItem(row, 6, new QTableWidgetItem(query.value("CATEGORIE").toString())); // Catégorie
        table->setItem(row, 7, new QTableWidgetItem(query.value("DESIGNATION").toString())); // Designation
        table->setItem(row, 8, new QTableWidgetItem(query.value("DATEEXPIRATION").toDate().toString("yyyy-MM-dd"))); // Date d'expiration
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

    // REFERENCE is a VARCHAR/STRING column - accepts alphanumeric values like "C12", "REF47", etc.
    query.prepare("UPDATE PRODUIT SET COULEUR=:couleur, GENRE=:genre, PRIX=:prix, QUANTITE=:quantite, MARQUE=:marque, CATEGORIE=:categorie, DESIGNATION=:designation, DATEEXPIRATION=:dateExpiration "
                  "WHERE REFERENCE=:ref");

    query.bindValue(":ref", ref);  // String reference (e.g., "C12", "REF47")
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":marque", marque);
    query.bindValue(":categorie", categorie);
    query.bindValue(":designation", designation);
    query.bindValue(":dateExpiration", dateExpiration);

    qDebug() << "✏️ Modifying product with reference (string):" << ref;
    bool test = query.exec();

    if (test)
        qDebug() << "✅ Modification réussie pour le produit avec référence:" << ref;
    else
        qDebug() << "❌ Erreur de modification:" << query.lastError().text() << "pour référence:" << ref;

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
        // Use REFERENCE (not REF) to match the database column name
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("DESIGNATION").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("QUANTITE").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("MARQUE").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("CATEGORIE").toString()));
        row++;
    }
}






Produit::~Produit() {}
