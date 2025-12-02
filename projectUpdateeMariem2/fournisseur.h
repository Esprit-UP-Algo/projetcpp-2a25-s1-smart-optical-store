#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int id,
                QString nom_ent,
                QString nom_cont,
                QString em,
                QString tel,
                QString type_prod,
                int cond_paie,
                QString hist);

    // Getters
    int get_id_fournisseur();
    QString get_nom_entreprise();
    QString get_nom_contact();
    QString get_email();
    QString get_telephone();
    QString get_type_produit_fournis();
    int get_condition_paiement();
    QString get_historique();

    // Setters
    void set_id_fournisseur(int);
    void set_nom_entreprise(QString);
    void set_nom_contact(QString);
    void set_email(QString);
    void set_telephone(QString);
    void set_type_produit_fournis(QString);
    void set_condition_paiement(int);
    void set_historique(QString);

    // CRUD
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* afficher();

private:
    int id_fournisseur;
    QString nom_entreprise;
    QString nom_contact;
    QString email;
    QString telephone;           // 8 chiffres
    QString type_produit_fournis;
    int condition_paiement;      // 0 ou 1
    QString historique;          // texte libre
};

#endif // FOURNISSEUR_H
