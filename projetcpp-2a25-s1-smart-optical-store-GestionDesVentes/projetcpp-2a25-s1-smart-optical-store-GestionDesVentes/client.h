#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

class Client
{
public:
    Client();
    Client(int id, const QString &nom, const QString &prenom, const QString &email, 
           const QDate &dateNaissance, const QString &sexe, const QString &adresse, 
           const QString &telephone);
    
    // Getters
    int getId() const { return id_client; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QDate getDateNaissance() const { return d_naissance; }
    QString getSexe() const { return sexe; }
    QString getAdresse() const { return adresse; }
    QString getTelephone() const { return telephone; }
    
    // Setters
    void setId(int id) { id_client = id; }
    void setNom(const QString &value) { nom = value; }
    void setPrenom(const QString &value) { prenom = value; }
    void setEmail(const QString &value) { email = value; }
    void setDateNaissance(const QDate &value) { d_naissance = value; }
    void setSexe(const QString &value) { sexe = value; }
    void setAdresse(const QString &value) { adresse = value; }
    void setTelephone(const QString &value) { telephone = value; }
    
    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &critere);
    
private:
    int id_client;
    QString nom;
    QString prenom;
    QString email;
    QDate d_naissance;
    QString sexe;
    QString adresse;
    QString telephone;
};

#endif // CLIENT_H
