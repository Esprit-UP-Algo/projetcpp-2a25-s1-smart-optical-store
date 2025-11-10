#include "vente.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QDateTime>

Vente::Vente()
{
    id_vente = 0;
    id_client = 0;
    id_employe = 0;
    date_vente = QDate::currentDate();
    prix_ttc = 0.0;
    prix_ht = 0.0;
    remise = 0.0;
    tva = 0.0;
    statut_vente = "En attente";
    statut_paiement = "Non payé";
    mode_paiement = "";
    date_livraison = QDate::currentDate().addDays(7);
}

Vente::Vente(int id, int idClient, int idEmploye, const QDate &dateVente, 
             double prixTtc, double prixHt, double remise, double tva, 
             const QString &statutVente, const QString &statutPaiement, 
             const QString &modePaiement, const QDate &dateLivraison)
{
    this->id_vente = id;
    this->id_client = idClient;
    this->id_employe = idEmploye;
    this->date_vente = dateVente;
    this->prix_ttc = prixTtc;
    this->prix_ht = prixHt;
    this->remise = remise;
    this->tva = tva;
    this->statut_vente = statutVente;
    this->statut_paiement = statutPaiement;
    this->mode_paiement = modePaiement;
    this->date_livraison = dateLivraison;
}

bool Vente::ajouter()
{
    // First, verify that the client exists
    QSqlQuery clientCheck;
    clientCheck.prepare("SELECT id_client FROM clients WHERE id_client = :id_client");
    clientCheck.bindValue(":id_client", id_client);
    
    if (!clientCheck.exec() || !clientCheck.next()) {
        qDebug() << "Erreur: Client avec ID" << id_client << "n'existe pas";
        return false;
    }
    
    // If employee ID is provided, verify that the employee exists
    if (id_employe > 0) {
        QSqlQuery employeeCheck;
        employeeCheck.prepare("SELECT id_employe FROM employe WHERE id_employe = :id_employe");
        employeeCheck.bindValue(":id_employe", id_employe);
        
        if (!employeeCheck.exec() || !employeeCheck.next()) {
            qDebug() << "Erreur: Employé avec ID" << id_employe << "n'existe pas";
            return false;
        }
    }
    
    QSqlQuery query;
    
    // If employee ID is 0, set it to NULL in the database
    if (id_employe == 0) {
        query.prepare("INSERT INTO vente (id_client, id_employe, date_vente, prix_ttc, prix_ht, "
                      "remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison) "
                      "VALUES (:id_client, NULL, :date_vente, :prix_ttc, :prix_ht, "
                      ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, :date_livraison)");
    } else {
        query.prepare("INSERT INTO vente (id_client, id_employe, date_vente, prix_ttc, prix_ht, "
                      "remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison) "
                      "VALUES (:id_client, :id_employe, :date_vente, :prix_ttc, :prix_ht, "
                      ":remise, :tva, :statut_vente, :statut_paiement, :mode_paiement, :date_livraison)");
        query.bindValue(":id_employe", id_employe);
    }
    
    query.bindValue(":id_client", id_client);
    query.bindValue(":date_vente", date_vente);
    query.bindValue(":prix_ttc", prix_ttc);
    query.bindValue(":prix_ht", prix_ht);
    query.bindValue(":remise", remise);
    query.bindValue(":tva", tva);
    query.bindValue(":statut_vente", statut_vente);
    query.bindValue(":statut_paiement", statut_paiement);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":date_livraison", date_livraison);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de la vente: " << query.lastError().text();
        return false;
    }
    
    // Récupérer l'ID de la vente qui vient d'être créée
    QVariant lastId = query.lastInsertId();
    if (lastId.isValid()) {
        id_vente = lastId.toInt();
    }
    
    return true;
}

bool Vente::modifier()
{
    QSqlQuery query;
    
    query.prepare("UPDATE vente SET id_client = :id_client, id_employe = :id_employe, "
                  "date_vente = :date_vente, prix_ttc = :prix_ttc, prix_ht = :prix_ht, "
                  "remise = :remise, tva = :tva, statut_vente = :statut_vente, "
                  "statut_paiement = :statut_paiement, mode_paiement = :mode_paiement, "
                  "date_livraison = :date_livraison "
                  "WHERE id_vente = :id_vente");
    
    query.bindValue(":id_vente", id_vente);
    query.bindValue(":id_client", id_client);
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":date_vente", date_vente);
    query.bindValue(":prix_ttc", prix_ttc);
    query.bindValue(":prix_ht", prix_ht);
    query.bindValue(":remise", remise);
    query.bindValue(":tva", tva);
    query.bindValue(":statut_vente", statut_vente);
    query.bindValue(":statut_paiement", statut_paiement);
    query.bindValue(":mode_paiement", mode_paiement);
    query.bindValue(":date_livraison", date_livraison);
    
    return query.exec();
}

bool Vente::supprimer(int id)
{
    QSqlQuery query;
    
    // D'abord supprimer les entrées dans la table contenir
    query.prepare("DELETE FROM contenir WHERE id_vente = :id");
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des produits de la vente: " << query.lastError().text();
        return false;
    }
    
    // Ensuite supprimer la vente
    query.prepare("DELETE FROM vente WHERE id_vente = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

QSqlQueryModel* Vente::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

QSqlQueryModel* Vente::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "WHERE v.id_vente LIKE '%" + critere + "%' OR "
                    "c.nom LIKE '%" + critere + "%' OR "
                    "c.prenom LIKE '%" + critere + "%' OR "
                    "e.nom LIKE '%" + critere + "%' OR "
                    "e.prenom LIKE '%" + critere + "%' OR "
                    "v.statut_vente LIKE '%" + critere + "%' OR "
                    "v.statut_paiement LIKE '%" + critere + "%' OR "
                    "v.mode_paiement LIKE '%" + critere + "%' "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

QSqlQueryModel* Vente::filtrerParDate(const QDate &debut, const QDate &fin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT v.id_vente, c.nom || ' ' || c.prenom AS client, "
                    "e.nom || ' ' || e.prenom AS employe, v.date_vente, "
                    "v.prix_ttc, v.prix_ht, v.remise, v.tva, "
                    "v.statut_vente, v.statut_paiement, v.mode_paiement, v.date_livraison "
                    "FROM vente v "
                    "LEFT JOIN clients c ON v.id_client = c.id_client "
                    "LEFT JOIN employe e ON v.id_employe = e.id_employe "
                    "WHERE v.date_vente BETWEEN '" + debut.toString("yyyy-MM-dd") + "' AND '" + fin.toString("yyyy-MM-dd") + "' "
                    "ORDER BY v.date_vente DESC");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    return model;
}

bool Vente::ajouterProduitVente(int idVente, int refProduit, int quantite, double prixUnitaire)
{
    QSqlQuery query;
    
    query.prepare("INSERT INTO contenir (id_vente, reference, quantite, prix_unitaire) "
                  "VALUES (:id_vente, :reference, :quantite, :prix_unitaire)");
    
    query.bindValue(":id_vente", idVente);
    query.bindValue(":reference", refProduit);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix_unitaire", prixUnitaire);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du produit à la vente: " << query.lastError().text();
        return false;
    }
    
    // Mettre à jour le stock du produit
    query.prepare("UPDATE produit SET quantite = quantite - :quantite WHERE reference = :reference");
    query.bindValue(":reference", refProduit);
    query.bindValue(":quantite", quantite);
    
    return query.exec();
}

QSqlQueryModel* Vente::afficherProduitsVente(int idVente)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT c.reference, p.designation, c.prix_unitaire, c.quantite, "
                    "(c.prix_unitaire * c.quantite) AS total "
                    "FROM contenir c "
                    "JOIN produit p ON c.reference = p.reference "
                    "WHERE c.id_vente = " + QString::number(idVente));
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix unitaire"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Total"));
    
    return model;
}

double Vente::calculerTotal(int idVente)
{
    QSqlQuery query;
    double total = 0.0;
    
    query.prepare("SELECT SUM(prix_unitaire * quantite) FROM contenir WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    
    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    }
    
    return total;
}

bool Vente::mettreAJourStatutVente(int idVente, const QString &nouveauStatut)
{
    QSqlQuery query;
    
    query.prepare("UPDATE vente SET statut_vente = :statut WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    query.bindValue(":statut", nouveauStatut);
    
    return query.exec();
}

bool Vente::mettreAJourStatutPaiement(int idVente, const QString &nouveauStatut)
{
    QSqlQuery query;
    
    query.prepare("UPDATE vente SET statut_paiement = :statut WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", idVente);
    query.bindValue(":statut", nouveauStatut);
    
    return query.exec();
}
