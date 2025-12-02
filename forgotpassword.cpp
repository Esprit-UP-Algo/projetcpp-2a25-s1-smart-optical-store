#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
    
    // Set validators for input fields
    QRegularExpression usernameRegex("^[a-zA-Z0-9_]{3,20}$");
    ui->lineEdit_username->setValidator(new QRegularExpressionValidator(usernameRegex, this));
    
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(emailRegex, this));
    
    // Set password validator (at least 6 characters)
    QRegularExpression passwordRegex("^.{6,}$");
    ui->lineEdit_new_password->setValidator(new QRegularExpressionValidator(passwordRegex, this));
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_pushButton_reset_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString newPassword = ui->lineEdit_new_password->text();
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    
    // Validate input
    if (username.isEmpty() || email.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }
    
    // Validate email format
    if (!email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Erreur", "Format d'email invalide !");
        return;
    }
    
    // Check if user exists with matching username and email
    Employe employee;
    employee.setUsername(username);
    
    if (!employee.existsByUsername()) {
        QMessageBox::warning(this, "Erreur", "Nom d'utilisateur non trouvé !");
        return;
    }
    
    // In a real application, you would verify the email address as well
    // For this example, we'll just check that the passwords match
    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas !");
        return;
    }
    
    // Validate password strength
    if (newPassword.length() < 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 6 caractères !");
        return;
    }
    
    // Update the employee's password in the database
    Employe employeeToUpdate;
    if (employeeToUpdate.rechercherParUsername(username)) {
        employeeToUpdate.setPassword(newPassword);
        if (employeeToUpdate.modifier()) {
            QMessageBox::information(this, "Succès", 
                "Votre mot de passe a été réinitialisé avec succès !\n\n"
                "Vous pouvez maintenant vous connecter avec votre nouveau mot de passe.");
            this->accept();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la réinitialisation du mot de passe !");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de trouver l'utilisateur !");
    }
}

void ForgotPassword::on_pushButton_cancel_clicked()
{
    this->reject();
}