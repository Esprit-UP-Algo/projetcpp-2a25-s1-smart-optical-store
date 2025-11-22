#include "fournisseur.h"

// Constructeur par défaut
Fournisseur::Fournisseur()
{
    id_fournisseur = 0;
    nom_entreprise = "";
    nom_contact = "";
    email = "";
    telephone = "";
    type_produit_fournis = "";
    condition_paiement = 0;
    historique = QDate::currentDate();
}

// Constructeur avec paramètres
Fournisseur::Fournisseur(int id, QString nom_ent, QString nom_cont, QString em,
                         QString tel, QString type_prod, int cond_paie, QDate hist)
{
    id_fournisseur = id;
    nom_entreprise = nom_ent;
    nom_contact = nom_cont;
    email = em;
    telephone = tel;
    type_produit_fournis = type_prod;
    condition_paiement = cond_paie;
    historique = hist;
}

// GETTERS
int Fournisseur::get_id_fournisseur()
{
    return id_fournisseur;
}

QString Fournisseur::get_nom_entreprise()
{
    return nom_entreprise;
}

QString Fournisseur::get_nom_contact()
{
    return nom_contact;
}

QString Fournisseur::get_email()
{
    return email;
}

QString Fournisseur::get_telephone()
{
    return telephone;
}

QString Fournisseur::get_type_produit_fournis()
{
    return type_produit_fournis;
}

int Fournisseur::get_condition_paiement()
{
    return condition_paiement;
}

QDate Fournisseur::get_historique()
{
    return historique;
}

// SETTERS
void Fournisseur::set_id_fournisseur(int id)
{
    id_fournisseur = id;
}

void Fournisseur::set_nom_entreprise(QString nom)
{
    nom_entreprise = nom;
}

void Fournisseur::set_nom_contact(QString nom)
{
    nom_contact = nom;
}

void Fournisseur::set_email(QString em)
{

    email = em;
}

void Fournisseur::set_telephone(QString tel)
{
    telephone = tel;
}

void Fournisseur::set_type_produit_fournis(QString type)
{
    type_produit_fournis = type;
}

void Fournisseur::set_condition_paiement(int cond)
{
    condition_paiement = cond;
}

void Fournisseur::set_historique(QDate hist)
{
    historique = hist;
}

// MÉTHODE AJOUTER avec validations
bool Fournisseur::ajouter()
{
    // Validation téléphone (8 chiffres)
    if (telephone.length() != 8 || !telephone.toInt())
    {
        qDebug() << "Erreur: Le téléphone doit contenir exactement 8 chiffres !";
        return false;
    }

    // Validation condition_paiement (0 ou 1)
    if (condition_paiement != 0 && condition_paiement != 1)
    {
        qDebug() << "Erreur: La condition de paiement doit être 0 ou 1 !";
        return false;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOM_ENTREPRISE, NOM_CONTACT, "
                  "EMAIL, TELEPHONE, TYPE_PRODUIT_FOURNIS, CONDITION_PAIEMENT, HISTORIQUE) "
                  "VALUES (:id, :nom_ent, :nom_cont, :email, :tel, :type_prod, :cond_paie, :hist)");

    query.bindValue(":id", id_fournisseur);
    query.bindValue(":nom_ent", nom_entreprise);
    query.bindValue(":nom_cont", nom_contact);
    query.bindValue(":email", email);
    query.bindValue(":tel", telephone.toInt());
    query.bindValue(":type_prod", type_produit_fournis);
    query.bindValue(":cond_paie", condition_paiement);
    query.bindValue(":hist", historique);

    if (query.exec())
    {
        qDebug() << "Fournisseur ajouté avec succès !";
        return true;
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }

}

// MÉTHODE SUPPRIMER
bool Fournisseur::supprimer(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur: connexion base de données invalide ou fermée";
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);

    // D'abord supprimer les relations dans la table fournir
    QString sql = "DELETE FROM FOURNIR WHERE ID_FOURNISSEUR = :id";
    query.prepare(sql);
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        // Try with lowercase
        query.clear();
        sql = "DELETE FROM fournir WHERE id_fournisseur = :id";
        query.prepare(sql);
        query.bindValue(":id", id);
        query.exec(); // Don't fail if this doesn't work
    }
    
    // Ensuite supprimer le fournisseur
    sql = "DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id";
    query.prepare(sql);
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        // Try with lowercase
        query.clear();
        sql = "DELETE FROM fournisseur WHERE id_fournisseur = :id";
        query.prepare(sql);
        query.bindValue(":id", id);
        
        if (!query.exec()) {
            qDebug() << "Erreur lors de la suppression du fournisseur:" << query.lastError().text();
            return false;
        }
    }
    
    qDebug() << "Fournisseur supprimé avec succès !";
    return true;
}

// MÉTHODE AFFICHER
QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISSEUR");

    
    QString sql = "SELECT ID_FOURNISSEUR, NOM_ENTREPRISE, NOM_CONTACT, EMAIL, TELEPHONE, "
                  "TYPE_PRODUIT_FOURNIS, CONDITION_PAIEMENT, HISTORIQUE_COMMANDE_PASSEE "
                  "FROM FOURNISSEUR";
    model->setQuery(sql);
    
    // If query fails, try with lowercase
    if (model->lastError().isValid()) {
        sql = "SELECT id_fournisseur, nom_entreprise, nom_contact, email, telephone, "
              "type_produit_fournis, condition_paiement, historique_commande_passee "
              "FROM fournisseur";
        model->setQuery(sql);
    }
    
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

// MÉTHODE MODIFIER
bool Fournisseur::modifier(int id)
{
    // Validation téléphone (8 chiffres)
    if (telephone.length() != 8 || !telephone.toInt())
    {
        qDebug() << "Erreur: Le téléphone doit contenir exactement 8 chiffres !";
        return false;
    }

    // Validation condition_paiement (0 ou 1)
    if (condition_paiement != 0 && condition_paiement != 1)
    {
        qDebug() << "Erreur: La condition de paiement doit être 0 ou 1 !";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEUR SET NOM_ENTREPRISE = :nom_ent, NOM_CONTACT = :nom_cont, "
                  "EMAIL = :email, TELEPHONE = :tel, TYPE_PRODUIT_FOURNIS = :type_prod, "
                  "CONDITION_PAIEMENT = :cond_paie, HISTORIQUE = :hist "
                  "WHERE ID_FOURNISSEUR = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom_ent", nom_entreprise);
    query.bindValue(":nom_cont", nom_contact);
    query.bindValue(":email", email);
    query.bindValue(":tel", telephone.toInt());
    query.bindValue(":type_prod", type_produit_fournis);
    query.bindValue(":cond_paie", condition_paiement);
    query.bindValue(":hist", historique);

    if (query.exec())
    {
        qDebug() << "Fournisseur modifié avec succès !";
        return true;
    }
    else
    {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}
