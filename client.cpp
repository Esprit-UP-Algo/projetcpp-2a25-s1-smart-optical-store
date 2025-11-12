#include "client.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

Client::Client()
{
    id_client = 0;
    nom = "";
    prenom = "";
    email = "";
    d_naissance = QDate::currentDate();
    sexe = "";
    adresse = "";
    telephone = "";
}

Client::Client(int id, const QString &nom, const QString &prenom, const QString &email, 
               const QDate &dateNaissance, const QString &sexe, const QString &adresse, 
               const QString &telephone)
{
    this->id_client = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->d_naissance = dateNaissance;
    this->sexe = sexe;
    this->adresse = adresse;
    this->telephone = telephone;
}

bool Client::ajouter()
{
    QSqlQuery query;
    
    // Using parameterized query to prevent SQL injection
    query.prepare("INSERT INTO clients (nom, prenom, email, d_naissance, sexe, adresse, telephone) "
                  "VALUES (:nom, :prenom, :email, :d_naissance, :sexe, :adresse, :telephone)");
    
    // Binding values
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":d_naissance", d_naissance);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    
    // Execute the query and return result
    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    
    query.prepare("UPDATE clients SET nom = :nom, prenom = :prenom, email = :email, "
                  "d_naissance = :d_naissance, sexe = :sexe, adresse = :adresse, "
                  "telephone = :telephone WHERE id_client = :id");
    
    query.bindValue(":id", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":d_naissance", d_naissance);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    
    return query.exec();
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    
    query.prepare("DELETE FROM clients WHERE id_client = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM clients");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
    
    return model;
}

QSqlQueryModel* Client::rechercher(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    model->setQuery("SELECT * FROM clients WHERE "
                    "id_client LIKE '%" + critere + "%' OR "
                    "nom LIKE '%" + critere + "%' OR "
                    "prenom LIKE '%" + critere + "%' OR "
                    "email LIKE '%" + critere + "%' OR "
                    "telephone LIKE '%" + critere + "%'");
    
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
    
    return model;
}
