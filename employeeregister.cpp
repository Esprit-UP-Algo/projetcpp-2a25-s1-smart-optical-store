#include "employeeregister.h"
#include "ui_employeeregister.h"
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

EmployeeRegister::EmployeeRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeRegister)
{
    ui->setupUi(this);
    
    // Set today's date as default
    ui->dateEdit_naissance->setDate(QDate::currentDate().addYears(-25));
    
    // Set validators for specific fields
    QRegularExpression phoneRegex("^\\+?[0-9]{8,15}$");
    ui->lineEdit_telephone->setValidator(new QRegularExpressionValidator(phoneRegex, this));
    
    QRegularExpression salaryRegex("^[0-9]+(\\.[0-9]{1,2})?$");
    ui->lineEdit_salaire->setValidator(new QRegularExpressionValidator(salaryRegex, this));
    
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(emailRegex, this));
}

EmployeeRegister::~EmployeeRegister()
{
    delete ui;
}

void EmployeeRegister::on_pushButton_register_clicked()
{
    // Get all the input values
    QString nom = ui->lineEdit_nom->text().trimmed();
    QString prenom = ui->lineEdit_prenom->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString telephone = ui->lineEdit_telephone->text().trimmed();
    QDate dateNaissance = ui->dateEdit_naissance->date();
    QString adresse = ui->lineEdit_adresse->text().trimmed();
    QString role = ui->comboBox_role->currentText().trimmed();
    QString salaireStr = ui->lineEdit_salaire->text().trimmed();
    QString username = ui->lineEdit_username->text().trimmed();
    QString password = ui->lineEdit_password->text();
    
    // Validate all fields
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || telephone.isEmpty() || 
        adresse.isEmpty() || salaireStr.isEmpty() || 
        username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires !");
        return;
    }
    
    // Validate email format
    if (!email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Erreur", "Format d'email invalide !");
        return;
    }
    
    // Validate salary
    bool salaryOk;
    double salaire = salaireStr.toDouble(&salaryOk);
    if (!salaryOk || salaire <= 0) {
        QMessageBox::warning(this, "Erreur", "Le salaire doit être un nombre positif !");
        return;
    }
    
    // Validate password strength
    if (password.length() < 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 6 caractères !");
        return;
    }
    
    // Check if username already exists
    Employe existingEmployee;
    existingEmployee.setId(0); // Reset ID
    existingEmployee.setUsername(username);
    if (existingEmployee.existsByUsername()) {
        QMessageBox::warning(this, "Erreur", "Ce nom d'utilisateur existe déjà !");
        return;
    }
    
    // Create new employee object
    Employe newEmployee;
    newEmployee.setNom(nom);
    newEmployee.setPrenom(prenom);
    newEmployee.setEmail(email);
    newEmployee.setTelephone(telephone);
    newEmployee.setDateNaissance(dateNaissance);
    newEmployee.setAdresse(adresse);
    newEmployee.setSalaire(salaire);
    newEmployee.setUsername(username);
    newEmployee.setPassword(password); // This will be hashed in the setter
    newEmployee.setRole(role); // Use selected role
    
    // Try to add the employee to the database
    if (newEmployee.ajouter()) {
        QMessageBox::information(this, "Succès", "Employé enregistré avec succès !");
        this->accept(); // Close the dialog
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'enregistrement de l'employé !");
    }
}

void EmployeeRegister::on_pushButton_cancel_clicked()
{
    this->reject(); // Close the dialog without saving
}