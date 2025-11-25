#ifndef PRODUIT_H
#define PRODUIT_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Produit {
private:
    QString reference;
    QString designation;
    int quantite;
    double prix;
    QString categorie;
    QString couleur;
    QString genre;
    QString marque;
    QDate dateExpiration;
    void checkLowQuantity();
    QString getEmployeeEmail();

public:
    Produit(Ui::MainWindow *ui);
    Produit(){};
    ~Produit();

    // Setters
    void setReference(const QString &r) { reference = r; }
    void setDesignation(const QString &d) { designation = d; }
    void setQuantite(int q) { quantite = q; }
    void setPrix(double p) { prix = p; }
    void setCategorie(const QString &c) { categorie = c; }
    void setCouleur(const QString &cl) { couleur = cl; }
    void setgenre(Ui::MainWindow *ui);
    void setMarque(const QString &m) { marque = m; }
    void setDateExpiration(const QDate &de) { dateExpiration = de; }

    // Getters
    QString getReference() const { return reference; }
    QString getDesignation() const { return designation; }
    int getQuantite() const { return quantite; }
    double getPrix() const { return prix; }
    QString getCategorie() const { return categorie; }
    QString getCouleur() const { return couleur; }
    QString getgenre() const { return genre; }
    QString getMarque() const { return marque; }
    QDate getDateExpiration() const { return dateExpiration; }

    //fonctions
    bool ajouter();
    bool modifier();
    void afficher(Ui::MainWindow *ui);
    bool supprimer(QString reference);
    bool existe(QString reference);
    bool rech(QString recherche, Ui::MainWindow *ui);

};

#endif // PRODUIT_H
