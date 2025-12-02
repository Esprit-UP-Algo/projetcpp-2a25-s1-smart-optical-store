#include "fournisseur.h"
#include <QMessageBox>

// Constructeurs

Fournisseur::Fournisseur()
{
    id_fournisseur       = 0;
    nom_entreprise       = "";
    nom_contact          = "";
    email                = "";
    telephone            = "";
    type_produit_fournis = "";
    condition_paiement   = 0;
    historique           = "";
}

Fournisseur::Fournisseur(int id,
                         QString nom_ent,
                         QString nom_cont,
                         QString em,
                         QString tel,
                         QString type_prod,
                         int cond_paie,
                         QString hist)
{
    id_fournisseur       = id;
    nom_entreprise       = nom_ent;
    nom_contact          = nom_cont;
    email                = em;
    telephone            = tel;
    type_produit_fournis = type_prod;
    condition_paiement   = cond_paie;
    historique           = hist;
}

// Getters

int Fournisseur::get_id_fournisseur()           { return id_fournisseur; }
QString Fournisseur::get_nom_entreprise()       { return nom_entreprise; }
QString Fournisseur::get_nom_contact()          { return nom_contact; }
QString Fournisseur::get_email()                { return email; }
QString Fournisseur::get_telephone()            { return telephone; }
QString Fournisseur::get_type_produit_fournis() { return type_produit_fournis; }
int Fournisseur::get_condition_paiement()       { return condition_paiement; }
QString Fournisseur::get_historique()           { return historique; }

// Setters

void Fournisseur::set_id_fournisseur(int id)          { id_fournisseur = id; }
void Fournisseur::set_nom_entreprise(QString nom)     { nom_entreprise = nom; }
void Fournisseur::set_nom_contact(QString nom)        { nom_contact = nom; }
void Fournisseur::set_email(QString em)               { email = em; }
void Fournisseur::set_telephone(QString tel)          { telephone = tel; }
void Fournisseur::set_type_produit_fournis(QString t) { type_produit_fournis = t; }
void Fournisseur::set_condition_paiement(int cond)    { condition_paiement = cond; }
void Fournisseur::set_historique(QString hist)        { historique = hist; }

// Ajout

bool Fournisseur::ajouter()
{
    // téléphone = 8 chiffres
    if (telephone.length() != 8 || !telephone.toInt())
    {
        QMessageBox::warning(nullptr, "Erreur",
                             "Le téléphone doit contenir exactement 8 chiffres !");
        qDebug() << "Erreur: Le téléphone doit contenir exactement 8 chiffres !";
        return false;
    }

    // condition_paiement = 0 ou 1
    if (condition_paiement != 0 && condition_paiement != 1)
    {
        QMessageBox::warning(nullptr, "Erreur",
                             "La condition de paiement doit être 0 ou 1 !");
        qDebug() << "Erreur: La condition de paiement doit être 0 ou 1 !";
        return false;
    }

    QSqlQuery query;

    // Noms EXACTS de la table Oracle "fournisseur"
    query.prepare(
        "INSERT INTO \"fournisseur\" "
        "(\"ID-fournisseur\", \"nom de l'entreprise\", \"nom du contact\", "
        "\"email\", \"telephone\", \"type de produit fournis\", "
        "\"condition de paiement\", \"historique de commande passée\") "
        "VALUES (:id, :nom_ent, :nom_cont, :email, :tel, :type_prod, :cond_paie, :hist)"
        );

    query.bindValue(":id",        id_fournisseur);
    query.bindValue(":nom_ent",   nom_entreprise);
    query.bindValue(":nom_cont",  nom_contact);
    query.bindValue(":email",     email);
    query.bindValue(":tel",       telephone.toInt());
    query.bindValue(":type_prod", type_produit_fournis);
    query.bindValue(":cond_paie", condition_paiement);
    query.bindValue(":hist",      historique);

    if (query.exec())
    {
        qDebug() << "Fournisseur ajouté avec succès !";
        return true;
    }
    else
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur lors de l'ajout:" << err;

        if (err.contains("ORA-00001")) {
            QMessageBox::critical(nullptr,
                                  "Erreur",
                                  "Cet ID fournisseur existe déjà.\n"
                                  "Sélectionne-le dans le tableau et clique sur 'modifier'.");
        } else {
            QMessageBox::critical(nullptr,
                                  "Erreur SQL lors de l'ajout",
                                  err);
        }
        return false;
    }
}

// Suppression

bool Fournisseur::supprimer(int id)
{
    QSqlQuery query;

    query.prepare(
        "DELETE FROM \"fournisseur\" "
        "WHERE \"ID-fournisseur\" = :id"
        );
    query.bindValue(":id", id);

    if (query.exec())
    {
        qDebug() << "Fournisseur supprimé avec succès !";
        return true;
    }
    else
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur lors de la suppression:" << err;
        QMessageBox::critical(nullptr, "Erreur SQL lors de la suppression", err);
        return false;
    }
}

// Affichage

QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM \"fournisseur\"");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Entreprise"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type Produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Condition"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Historique"));

    return model;
}

// Modification

bool Fournisseur::modifier(int id)
{
    // téléphone = 8 chiffres
    if (telephone.length() != 8 || !telephone.toInt())
    {
        QMessageBox::warning(nullptr, "Erreur",
                             "Le téléphone doit contenir exactement 8 chiffres !");
        qDebug() << "Erreur: Le téléphone doit contenir exactement 8 chiffres !";
        return false;
    }

    // condition_paiement = 0 ou 1
    if (condition_paiement != 0 && condition_paiement != 1)
    {
        QMessageBox::warning(nullptr, "Erreur",
                             "La condition de paiement doit être 0 ou 1 !");
        qDebug() << "Erreur: La condition de paiement doit être 0 ou 1 !";
        return false;
    }

    QSqlQuery query;

    query.prepare(
        "UPDATE \"fournisseur\" SET "
        "\"nom de l'entreprise\" = :nom_ent, "
        "\"nom du contact\" = :nom_cont, "
        "\"email\" = :email, "
        "\"telephone\" = :tel, "
        "\"type de produit fournis\" = :type_prod, "
        "\"condition de paiement\" = :cond_paie, "
        "\"historique de commande passée\" = :hist "
        "WHERE \"ID-fournisseur\" = :id"
        );

    query.bindValue(":id",        id);
    query.bindValue(":nom_ent",   nom_entreprise);
    query.bindValue(":nom_cont",  nom_contact);
    query.bindValue(":email",     email);
    query.bindValue(":tel",       telephone.toInt());
    query.bindValue(":type_prod", type_produit_fournis);
    query.bindValue(":cond_paie", condition_paiement);
    query.bindValue(":hist",      historique);

    if (query.exec())
    {
        qDebug() << "Fournisseur modifié avec succès !";
        return true;
    }
    else
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur lors de la modification:" << err;
        QMessageBox::critical(nullptr, "Erreur SQL lors de la modification", err);
        return false;
    }
}
