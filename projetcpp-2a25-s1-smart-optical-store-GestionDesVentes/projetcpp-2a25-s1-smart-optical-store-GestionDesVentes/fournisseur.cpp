#include "fournisseur.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QDateTime>

Fournisseur::Fournisseur()
{
    id_fournisseur = 0;
    nom_entreprise = "";
    nom_contact = "";
    email = "";
    telephone = "";
    type_produit_fournis = "";
    condition_paiement = "";
    historique_commande_passee = "";
}

Fournisseur::Fournisseur(int id, const QString &nomEntreprise, const QString &nomContact, 
                         const QString &email, const QString &telephone, const QString &typeProduit, 
                         const QString &conditionPaiement, const QString &historiqueCommande)
{
    this->id_fournisseur = id;
    this->nom_entreprise = nomEntreprise;
    this->nom_contact = nomContact;
    this->email = email;
    this->telephone = telephone;
    this->type_produit_fournis = typeProduit;
    this->condition_paiement = conditionPaiement;
    this->historique_commande_passee = historiqueCommande;
}

bool Fournisseur::ajouter()
{
    QSqlQuery query;
    
    query.prepare("INSERT INTO fournisseur (nom_entreprise, nom_contact, email, telephone, "
                  "type_produit_fournis, condition_paiement, historique_commande_passee) "
                  "VALUES (:nom_entreprise, :nom_contact, :email, :telephone, "
                  ":type_produit_fournis, :condition_paiement, :historique_commande_passee)");
    
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":nom_contact", nom_contact);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":type_produit_fournis", type_produit_fournis);
    query.bindValue(":condition_paiement", condition_paiement);
    query.bindValue(":historique_commande_passee", historique_commande_passee);
    
    return query.exec();
}

bool Fournisseur::modifier()
{
    QSqlQuery query;
    
    query.prepare("UPDATE fournisseur SET nom_entreprise = :nom_entreprise, nom_contact = :nom_contact, "
                  "email = :email, telephone = :telephone, type_produit_fournis = :type_produit_fournis, "
                  "condition_paiement = :condition_paiement, historique_commande_passee = :historique_commande_passee "
                  "WHERE id_fournisseur = :id_fournisseur");
    
    query.bindValue(":id_fournisseur", id_fournisseur);
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":nom_contact", nom_contact);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":type_produit_fournis", type_produit_fournis);
    query.bindValue(":condition_paiement", condition_paiement);
    query.bindValue(":historique_commande_passee", historique_commande_passee);
    
    return query.exec();
}

bool Fournisseur::supprimer(int id)
{
    QSqlQuery query;
    
    // D'abord supprimer les relations dans la table fournir
    query.prepare("DELETE FROM fournir WHERE id_fournisseur = :id");
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des relations fournisseur-produit: " << query.lastError().text();
        return false;
    }
    
    // Ensuite supprimer le fournisseur
    query.prepare("DELETE FROM fournisseur WHERE id_fournisseur = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM fournisseur");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Entreprise"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Condition de paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Historique"));
    
    return model;
}

QSqlQueryModel* Fournisseur::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM fournisseur WHERE "
                    "id_fournisseur LIKE '%" + critere + "%' OR "
                    "nom_entreprise LIKE '%" + critere + "%' OR "
                    "nom_contact LIKE '%" + critere + "%' OR "
                    "email LIKE '%" + critere + "%' OR "
                    "telephone LIKE '%" + critere + "%' OR "
                    "type_produit_fournis LIKE '%" + critere + "%'");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Entreprise"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Condition de paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Historique"));
    
    return model;
}

bool Fournisseur::associerProduit(int idFournisseur, int refProduit)
{
    QSqlQuery query;
    QDate currentDate = QDate::currentDate();
    
    query.prepare("INSERT INTO fournir (id_fournisseur, reference, date_fourniture) "
                  "VALUES (:id_fournisseur, :reference, :date_fourniture)");
    
    query.bindValue(":id_fournisseur", idFournisseur);
    query.bindValue(":reference", refProduit);
    query.bindValue(":date_fourniture", currentDate);
    
    return query.exec();
}

QSqlQueryModel* Fournisseur::afficherProduitsFournis(int idFournisseur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT p.reference, p.designation, p.prix, p.categorie, p.marque, f.date_fourniture "
                    "FROM fournir f "
                    "JOIN produit p ON f.reference = p.reference "
                    "WHERE f.id_fournisseur = " + QString::number(idFournisseur) + " "
                    "ORDER BY f.date_fourniture DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date fourniture"));
    
    return model;
}
