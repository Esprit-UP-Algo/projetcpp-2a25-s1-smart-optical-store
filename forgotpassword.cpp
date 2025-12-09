#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QRandomGenerator>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

// Helper function to hash passwords (same as in employe.cpp)
static QString hashPassword(const QString &password)
{
    QString salt = "SmartOpticalStoreSalt";
    QString saltedPassword = password + salt;
    return QString(QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
}

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

static QString generateOtp()
{
    int code = QRandomGenerator::global()->bounded(100000, 1000000);
    return QString::number(code);
}

bool ForgotPassword::createResetCode(const QString &email, QString &otpOut, QString &errorOut)
{
    QSqlQuery check;
    check.prepare("SELECT ID_EMPLOYE FROM EMPLOYE WHERE EMAIL = :email");
    check.bindValue(":email", email);
    if (!check.exec() || !check.next()) {
        errorOut = "Email introuvable";
        return false;
    }

    int idEmploye = check.value(0).toInt();
    QString otp = generateOtp();
    QDateTime expiry = QDateTime::currentDateTime().addSecs(10 * 60);

    QSqlQuery q;
    q.prepare("UPDATE EMPLOYE SET RESET_CODE = :code, RESET_EXPIRES = :expires "
              "WHERE ID_EMPLOYE = :id");
    q.bindValue(":code", otp);
    q.bindValue(":expires", expiry);
    q.bindValue(":id", idEmploye);

    if (!q.exec()) {
        errorOut = q.lastError().text();
        return false;
    }

    otpOut = otp;
    return true;
}

bool ForgotPassword::verifyOtpAndChangePassword(const QString &email,
                                                const QString &otp,
                                                const QString &newPassword,
                                                QString &errorOut)
{
    QSqlQuery q;
    q.prepare("SELECT ID_EMPLOYE, RESET_CODE, RESET_EXPIRES "
              "FROM EMPLOYE WHERE EMAIL = :email");
    q.bindValue(":email", email);

    if (!q.exec() || !q.next()) {
        errorOut = "Email introuvable";
        return false;
    }

    int idEmploye = q.value(0).toInt();
    QString storedCode = q.value(1).toString();
    QDateTime expires = q.value(2).toDateTime();

    if (storedCode != otp) {
        errorOut = "Code incorrect";
        return false;
    }
    if (QDateTime::currentDateTime() > expires) {
        errorOut = "Code expiré";
        return false;
    }

    QSqlQuery upd;
    upd.prepare("UPDATE EMPLOYE SET PASSWORD = :pwd, RESET_CODE = NULL, RESET_EXPIRES = NULL "
                "WHERE ID_EMPLOYE = :id");
    upd.bindValue(":pwd", hashPassword(newPassword));
    upd.bindValue(":id", idEmploye);

    if (!upd.exec()) {
        errorOut = upd.lastError().text();
        return false;
    }

    return true;
}

void ForgotPassword::on_pushButton_send_code_clicked()
{
    QString email = ui->lineEdit_email->text().trimmed();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir votre email.");
        return;
    }

    QString otp;
    QString error;
    if (!createResetCode(email, otp, error)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le code : " + error);
        return;
    }

    // Gmail SMTP credentials
    const QString smtpUser = QStringLiteral("ghaythweslaty10@gmail.com");
    const QString smtpPass = QStringLiteral("dcixvxvphgsofajg");
    SmtpClient smtp("smtp.gmail.com", 465, smtpUser, smtpPass, this);

    // HTML Email Content
    QString htmlBody = 
        "<html>"
        "<body style='font-family: Arial, sans-serif; background-color: #f4f4f4; padding: 20px;'>"
        "  <div style='max-width: 600px; margin: 0 auto; background-color: #ffffff; border-radius: 10px; overflow: hidden; box-shadow: 0 4px 6px rgba(0,0,0,0.1);'>"
        "    <div style='background-color: #0c66ed; padding: 20px; text-align: center; color: white;'>"
        "      <h1 style='margin: 0; font-size: 24px;'>SightIQ</h1>"
        "      <p style='margin: 5px 0 0; font-size: 14px;'>Smart Optical Store</p>"
        "    </div>"
        "    <div style='padding: 30px; color: #333333;'>"
        "      <h2 style='margin-top: 0; color: #333333;'>Réinitialisation du mot de passe</h2>"
        "      <p>Bonjour,</p>"
        "      <p>Nous avons reçu une demande de réinitialisation de votre mot de passe pour votre compte SightIQ.</p>"
        "      <p>Utilisez le code ci-dessous pour compléter la procédure :</p>"
        "      <div style='background-color: #f0f7ff; border: 1px solid #cce4ff; border-radius: 5px; padding: 15px; text-align: center; margin: 20px 0;'>"
        "        <span style='font-size: 32px; font-weight: bold; letter-spacing: 5px; color: #0c66ed;'>" + otp + "</span>"
        "      </div>"
        "      <p>Ce code est valide pour les 10 prochaines minutes.</p>"
        "      <p>Si vous n'avez pas demandé cette réinitialisation, vous pouvez ignorer cet email en toute sécurité.</p>"
        "      <br>"
        "      <p style='font-size: 12px; color: #888888;'>Cordialement,<br>L'équipe SightIQ</p>"
        "    </div>"
        "    <div style='background-color: #eeeeee; padding: 15px; text-align: center; font-size: 12px; color: #666666;'>"
        "      &copy; 2025 SightIQ. Tous droits réservés."
        "    </div>"
        "  </div>"
        "</body>"
        "</html>";

    QString mailError;
    // Use "SightIQ <email>" as sender name
    QString senderName = "SightIQ <" + smtpUser + ">";
    
    bool ok = smtp.sendMail(senderName,
                            email,
                            "Réinitialisation de votre mot de passe SightIQ",
                            htmlBody,
                            &mailError,
                            true); // true for HTML content
    if (!ok) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'envoi du mail : " + mailError);
        return;
    }

    QMessageBox::information(this, "Code envoyé",
                             "Un code de réinitialisation a été envoyé à votre adresse email.");
}

void ForgotPassword::on_pushButton_reset_clicked()
{
    QString username = ui->lineEdit_username->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString code = ui->lineEdit_code->text().trimmed();
    QString newPassword = ui->lineEdit_new_password->text();
    QString confirmPassword = ui->lineEdit_confirm_password->text();
    
    // Validate input
    if (username.isEmpty() || email.isEmpty() || code.isEmpty() ||
        newPassword.isEmpty() || confirmPassword.isEmpty()) {
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
    
    // In a real application, you would also verify that the email corresponds to this user
    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas !");
        return;
    }
    
    // Validate password strength
    if (newPassword.length() < 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 6 caractères !");
        return;
    }
    
    // Verify OTP and change password
    QString error;
    if (!verifyOtpAndChangePassword(email, code, newPassword, error)) {
        QMessageBox::critical(this, "Erreur", error);
        return;
    }

    QMessageBox::information(this, "Succès",
                             "Votre mot de passe a été réinitialisé avec succès !\n\n"
                             "Vous pouvez maintenant vous connecter avec votre nouveau mot de passe.");
    this->accept();
}

void ForgotPassword::on_pushButton_cancel_clicked()
{
    this->reject();
}