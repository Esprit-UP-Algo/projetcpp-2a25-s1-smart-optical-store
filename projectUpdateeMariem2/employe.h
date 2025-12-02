#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

class Employe
{
public:
    Employe();
    Employe(int id, const QString &nom, const QString &prenom, const QString &email,
            const QString &telephone, const QDate &dateNaissance, const QString &adresse,
            int nEnfant, const QString &poste, double salaire, const QString &dispo,
            const QString &username = "", const QString &password = "", const QString &role = "employee");

    // Getters
    int getId() const { return id_employe; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QDate getDateNaissance() const { return d_naissance; }
    QString getAdresse() const { return adresse; }
    int getNEnfant() const { return n_enfant; }
    QString getPoste() const { return poste; }
    double getSalaire() const { return salaire; }
    QString getDispo() const { return dispo; }
    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
    QString getRole() const { return role; }

    // Alias getters for CRUD compatibility
    QDate getDate() const { return d_naissance; }
    int getNombreEnfants() const { return n_enfant; }
    QString getDisponibilite() const { return dispo; }

    // Setters
    void setId(int id) { id_employe = id; }
    void setNom(const QString &value) { nom = value; }
    void setPrenom(const QString &value) { prenom = value; }
    void setEmail(const QString &value) { email = value; }
    void setTelephone(const QString &value) { telephone = value; }
    void setDateNaissance(const QDate &value) { d_naissance = value; }
    void setAdresse(const QString &value) { adresse = value; }
    void setNEnfant(int value) { n_enfant = value; }
    void setPoste(const QString &value) { poste = value; }
    void setSalaire(double value) { salaire = value; }
    void setDispo(const QString &value) { dispo = value; }
    void setUsername(const QString &value) { username = value; }
    void setPassword(const QString &value);
    void setRole(const QString &value) { role = value; }

    // Alias setters for CRUD compatibility
    void setDate(const QDate &value) { d_naissance = value; }
    void setNombreEnfants(int value) { n_enfant = value; }
    void setDisponibilite(const QString &value) { dispo = value; }

    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &critere);

    // Additional CRUD methods for employee management
    bool rechercherParId(int id);
    bool rechercherParUsername(const QString &username);
    QSqlQueryModel* rechercherParNom(const QString &nom);
    QSqlQueryModel* trierParNom();
    QSqlQueryModel* trierParSalaire();

    // Authentication methods
    static Employe authenticate(const QString &username, const QString &password);
    bool isAdmin() const { return role.toLower() == "admin"; }
    bool existsByUsername();

    // Méthodes spécifiques pour les employés
    QSqlQueryModel* afficherVentesParEmploye(int idEmploye);
    double calculerCommission(int idEmploye, const QDate &debut, const QDate &fin, double tauxCommission = 0.02);

private:
    int id_employe;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QDate d_naissance;
    QString adresse;
    int n_enfant;
    QString poste;
    double salaire;
    QString dispo;
    QString username;
    QString password;
    QString role;
};

#endif // EMPLOYE_H
