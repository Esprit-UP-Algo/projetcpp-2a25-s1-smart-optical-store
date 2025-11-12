#ifndef VENTE_H
#define VENTE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QList>
#include <QPair>

class Vente
{
public:
    Vente();
    Vente(int id, int idClient, int idEmploye, const QDate &dateVente, 
          double prixTtc, double prixHt, double remise, double tva, 
          const QString &statutVente, const QString &statutPaiement, 
          const QString &modePaiement, const QDate &dateLivraison);
    
    // Getters
    int getId() const { return id_vente; }
    int getIdClient() const { return id_client; }
    int getIdEmploye() const { return id_employe; }
    QDate getDateVente() const { return date_vente; }
    double getPrixTtc() const { return prix_ttc; }
    double getPrixHt() const { return prix_ht; }
    double getRemise() const { return remise; }
    double getTva() const { return tva; }
    QString getStatutVente() const { return statut_vente; }
    QString getStatutPaiement() const { return statut_paiement; }
    QString getModePaiement() const { return mode_paiement; }
    QDate getDateLivraison() const { return date_livraison; }
    
    // Setters
    void setId(int id) { id_vente = id; }
    void setIdClient(int id) { id_client = id; }
    void setIdEmploye(int id) { id_employe = id; }
    void setDateVente(const QDate &date) { date_vente = date; }
    void setPrixTtc(double prix) { prix_ttc = prix; }
    void setPrixHt(double prix) { prix_ht = prix; }
    void setRemise(double value) { remise = value; }
    void setTva(double value) { tva = value; }
    void setStatutVente(const QString &statut) { statut_vente = statut; }
    void setStatutPaiement(const QString &statut) { statut_paiement = statut; }
    void setModePaiement(const QString &mode) { mode_paiement = mode; }
    void setDateLivraison(const QDate &date) { date_livraison = date; }
    
    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &critere);
    QSqlQueryModel* filtrerParDate(const QDate &debut, const QDate &fin);
    
    // Méthodes spécifiques pour les ventes
    bool ajouterProduitVente(int idVente, int refProduit, int quantite, double prixUnitaire);
    QSqlQueryModel* afficherProduitsVente(int idVente);
    double calculerTotal(int idVente);
    bool mettreAJourStatutVente(int idVente, const QString &nouveauStatut);
    bool mettreAJourStatutPaiement(int idVente, const QString &nouveauStatut);
    
private:
    int id_vente;
    int id_client;
    int id_employe;
    QDate date_vente;
    double prix_ttc;
    double prix_ht;
    double remise;
    double tva;
    QString statut_vente;
    QString statut_paiement;
    QString mode_paiement;
    QDate date_livraison;
};

#endif // VENTE_H
