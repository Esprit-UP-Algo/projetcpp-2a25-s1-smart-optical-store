#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int id, const QString &nomEntreprise, const QString &nomContact, 
                const QString &email, const QString &telephone, const QString &typeProduit, 
                const QString &conditionPaiement, const QString &historiqueCommande);
    
    // Getters
    int getId() const { return id_fournisseur; }
    QString getNomEntreprise() const { return nom_entreprise; }
    QString getNomContact() const { return nom_contact; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getTypeProduit() const { return type_produit_fournis; }
    QString getConditionPaiement() const { return condition_paiement; }
    QString getHistoriqueCommande() const { return historique_commande_passee; }
    
    // Setters
    void setId(int id) { id_fournisseur = id; }
    void setNomEntreprise(const QString &nom) { nom_entreprise = nom; }
    void setNomContact(const QString &nom) { nom_contact = nom; }
    void setEmail(const QString &value) { email = value; }
    void setTelephone(const QString &value) { telephone = value; }
    void setTypeProduit(const QString &type) { type_produit_fournis = type; }
    void setConditionPaiement(const QString &condition) { condition_paiement = condition; }
    void setHistoriqueCommande(const QString &historique) { historique_commande_passee = historique; }
    
    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &critere);
    
    // Méthodes spécifiques pour les fournisseurs
    bool associerProduit(int idFournisseur, int refProduit);
    QSqlQueryModel* afficherProduitsFournis(int idFournisseur);
    
private:
    int id_fournisseur;
    QString nom_entreprise;
    QString nom_contact;
    QString email;
    QString telephone;
    QString type_produit_fournis;
    QString condition_paiement;
    QString historique_commande_passee;
};

#endif // FOURNISSEUR_H
