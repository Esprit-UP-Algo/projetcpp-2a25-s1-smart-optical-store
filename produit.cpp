#include "produit.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

Produit::Produit()
{
    reference = 0;
    designation = "";
    quantite = 0;
    prix = 0.0;
    categorie = "";
    couleur = "";
    genre = "";
    marque = "";
    date_expiration = QDate::currentDate();
}

Produit::Produit(int reference, const QString &designation, int quantite, 
                 double prix, const QString &categorie, const QString &couleur, 
                 const QString &genre, const QString &marque, const QDate &dateExpiration)
{
    this->reference = reference;
    this->designation = designation;
    this->quantite = quantite;
    this->prix = prix;
    this->categorie = categorie;
    this->couleur = couleur;
    this->genre = genre;
    this->marque = marque;
    this->date_expiration = dateExpiration;
}

bool Produit::ajouter()
{
    QSqlQuery query;
    
    query.prepare("INSERT INTO produit (designation, quantite, prix, categorie, couleur, genre, marque, date_expiration) "
                  "VALUES (:designation, :quantite, :prix, :categorie, :couleur, :genre, :marque, :date_expiration)");
    
    query.bindValue(":designation", designation);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":categorie", categorie);
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":marque", marque);
    query.bindValue(":date_expiration", date_expiration);
    
    return query.exec();
}

bool Produit::modifier()
{
    QSqlQuery query;
    
    query.prepare("UPDATE produit SET designation = :designation, quantite = :quantite, "
                  "prix = :prix, categorie = :categorie, couleur = :couleur, "
                  "genre = :genre, marque = :marque, date_expiration = :date_expiration "
                  "WHERE reference = :reference");
    
    query.bindValue(":reference", reference);
    query.bindValue(":designation", designation);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":categorie", categorie);
    query.bindValue(":couleur", couleur);
    query.bindValue(":genre", genre);
    query.bindValue(":marque", marque);
    query.bindValue(":date_expiration", date_expiration);
    
    return query.exec();
}

bool Produit::supprimer(int reference)
{
    QSqlQuery query;
    
    query.prepare("DELETE FROM produit WHERE reference = :reference");
    query.bindValue(":reference", reference);
    
    return query.exec();
}

QSqlQueryModel* Produit::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM produit");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date d'expiration"));
    
    return model;
}

QSqlQueryModel* Produit::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM produit WHERE "
                    "reference LIKE '%" + critere + "%' OR "
                    "designation LIKE '%" + critere + "%' OR "
                    "categorie LIKE '%" + critere + "%' OR "
                    "marque LIKE '%" + critere + "%'");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date d'expiration"));
    
    return model;
}

bool Produit::updateStock(int ref, int newQuantite)
{
    QSqlQuery query;
    
    query.prepare("UPDATE produit SET quantite = :quantite WHERE reference = :reference");
    query.bindValue(":reference", ref);
    query.bindValue(":quantite", newQuantite);
    
    return query.exec();
}
