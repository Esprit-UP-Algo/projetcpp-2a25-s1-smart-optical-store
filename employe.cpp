#include "employe.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

Employe::Employe()
{
    id_employe = 0;
    nom = "";
    prenom = "";
    email = "";
    telephone = "";
    d_naissance = QDate::currentDate();
    adresse = "";
    n_enfant = 0;
    poste = "";
    salaire = 0.0;
    dispo = "Disponible";
}

Employe::Employe(int id, const QString &nom, const QString &prenom, const QString &email, 
                 const QString &telephone, const QDate &dateNaissance, const QString &adresse, 
                 int nEnfant, const QString &poste, double salaire, const QString &dispo)
{
    this->id_employe = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->d_naissance = dateNaissance;
    this->adresse = adresse;
    this->n_enfant = nEnfant;
    this->poste = poste;
    this->salaire = salaire;
    this->dispo = dispo;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    
    query.prepare("INSERT INTO employe (nom, prenom, email, telephone, d_naissance, adresse, "
                  "n_enfant, poste, salaire, dispo) "
                  "VALUES (:nom, :prenom, :email, :telephone, :d_naissance, :adresse, "
                  ":n_enfant, :poste, :salaire, :dispo)");
    
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":d_naissance", d_naissance);
    query.bindValue(":adresse", adresse);
    query.bindValue(":n_enfant", n_enfant);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":dispo", dispo);
    
    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;
    
    query.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, email = :email, "
                  "telephone = :telephone, d_naissance = :d_naissance, adresse = :adresse, "
                  "n_enfant = :n_enfant, poste = :poste, salaire = :salaire, dispo = :dispo "
                  "WHERE id_employe = :id_employe");
    
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":d_naissance", d_naissance);
    query.bindValue(":adresse", adresse);
    query.bindValue(":n_enfant", n_enfant);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":dispo", dispo);
    
    return query.exec();
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;
    
    // Mettre à NULL l'id_employe dans les ventes associées
    query.prepare("UPDATE vente SET id_employe = NULL WHERE id_employe = :id");
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour des ventes: " << query.lastError().text();
        return false;
    }
    
    // Supprimer l'employé
    query.prepare("DELETE FROM employe WHERE id_employe = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM employe");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Enfants"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));
    
    return model;
}

QSqlQueryModel* Employe::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM employe WHERE "
                    "id_employe LIKE '%" + critere + "%' OR "
                    "nom LIKE '%" + critere + "%' OR "
                    "prenom LIKE '%" + critere + "%' OR "
                    "email LIKE '%" + critere + "%' OR "
                    "telephone LIKE '%" + critere + "%' OR "
                    "poste LIKE '%" + critere + "%' OR "
                    "dispo LIKE '%" + critere + "%'");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Enfants"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Disponibilité"));
    
    return model;
}

QSqlQueryModel* Employe::afficherVentesParEmploye(int idEmploye)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "v.date_vente, v.prix_ttc, v.statut_vente, v.statut_paiement "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "WHERE v.id_employe = " + QString::number(idEmploye) + " "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Vente"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    
    return model;
}

double Employe::calculerCommission(int idEmploye, const QDate &debut, const QDate &fin, double tauxCommission)
{
    QSqlQuery query;
    double totalVentes = 0.0;
    
    query.prepare("SELECT SUM(prix_ttc) FROM vente "
                  "WHERE id_employe = :id_employe "
                  "AND date_vente BETWEEN :debut AND :fin "
                  "AND statut_paiement = 'Payé'");
    
    query.bindValue(":id_employe", idEmploye);
    query.bindValue(":debut", debut);
    query.bindValue(":fin", fin);
    
    if (query.exec() && query.next()) {
        totalVentes = query.value(0).toDouble();
    }
    
    return totalVentes * tauxCommission;
}
