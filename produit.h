#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

class Produit
{
public:
    Produit();
    Produit(int reference, const QString &designation, int quantite, 
            double prix, const QString &categorie, const QString &couleur, 
            const QString &genre, const QString &marque, const QDate &dateExpiration);
    
    // Getters
    int getReference() const { return reference; }
    QString getDesignation() const { return designation; }
    int getQuantite() const { return quantite; }
    double getPrix() const { return prix; }
    QString getCategorie() const { return categorie; }
    QString getCouleur() const { return couleur; }
    QString getGenre() const { return genre; }
    QString getMarque() const { return marque; }
    QDate getDateExpiration() const { return date_expiration; }
    
    // Setters
    void setReference(int ref) { reference = ref; }
    void setDesignation(const QString &value) { designation = value; }
    void setQuantite(int value) { quantite = value; }
    void setPrix(double value) { prix = value; }
    void setCategorie(const QString &value) { categorie = value; }
    void setCouleur(const QString &value) { couleur = value; }
    void setGenre(const QString &value) { genre = value; }
    void setMarque(const QString &value) { marque = value; }
    void setDateExpiration(const QDate &value) { date_expiration = value; }
    
    // CRUD Operations
    bool ajouter();
    bool supprimer(int reference);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &critere);
    bool updateStock(int ref, int newQuantite);
    
private:
    int reference;
    QString designation;
    int quantite;
    double prix;
    QString categorie;
    QString couleur;
    QString genre;
    QString marque;
    QDate date_expiration;
};

#endif // PRODUIT_H
