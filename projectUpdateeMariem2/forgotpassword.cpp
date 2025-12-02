#include "ForgotPassword.h"
#include "ui_ForgotPassword.h"

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
    const QString salt = "SmartOpticalStoreSalt";
    const QString saltedPassword = password + salt;
    return QString(QCryptographicHash::hash(saltedPassword.toUtf8(),
                                            QCryptographicHash::Sha256).toHex());
}

// Generate a 6-digit OTP
static QString generateOtp()
{
    int code = QRandomGenerator::global()->bounded(100000, 1000000);
    return QString::number(code);
}

// ✅ CONSTRUCTOR
ForgotPassword::ForgotPassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);

    // Username validator
    QRegularExpression usernameRegex("^[a-zA-Z0-9_]{3,20}$");
    ui->lineEdit_username->setValidator(
        new QRegularExpressionValidator(usernameRegex, this));

    // Email validator
    QRegularExpression emailRegex(
        "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    ui->lineEdit_email->setValidator(
        new QRegularExpressionValidator(emailRegex, this));

    // Password validator (at least 6 characters)
    QRegularExpression passwordRegex("^.{6,}$");
    ui->lineEdit_new_password->setValidator(
        new QRegularExpressionValidator(passwordRegex, this));
}

// ✅ DESTRUCTOR
ForgotPassword::~ForgotPassword()
{
    delete ui;
}

// ✅ CREATE RESET CODE
bool ForgotPassword::createResetCode(const QString &email,
                                     QString &otpOut,
                                     QString &errorOut)
{
    QSqlQuery check;
    check.prepare("SELECT ID_EMPLOYE FROM EMPLOYE WHERE EMAIL = :email");
    check.bindValue(":email", email);

    if (!check.exec() || !check.next()) {
        errorOut = "Email introuvable";
        return false;
    }

    const int idEmploye = check.value(0).toInt();
    const QString otp = generateOtp();
    const QDateTime expiry = QDateTime::currentDateTime().addSecs(600);

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

// ✅ VERIFY + CHANGE PASSWORD
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

    const int idEmploye = q.value(0).toInt();
    const QString storedCode = q.value(1).toString();
    const QDateTime expires = q.value(2).toDateTime();

    if (storedCode != otp) {
        errorOut = "Code incorrect";
        return false;
    }

    if (QDateTime::currentDateTime() > expires) {
        errorOut = "Code expiré";
        return false;
    }

    QSqlQuery upd;
    upd.prepare("UPDATE EMPLOYE SET PASSWORD = :pwd, "
                "RESET_CODE = NULL, RESET_EXPIRES = NULL "
                "WHERE ID_EMPLOYE = :id");
    upd.bindValue(":pwd", hashPassword(newPassword));
    upd.bindValue(":id", idEmploye);

    if (!upd.exec()) {
        errorOut = upd.lastError().text();
        return false;
    }

    return true;
}

// ✅ SEND CODE BUTTON
void ForgotPassword::on_pushButton_send_code_clicked()
{
    const QString email = ui->lineEdit_email->text().trimmed();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir votre email.");
        return;
    }

    QString otp;
    QString error;

    if (!createResetCode(email, otp, error)) {
        QMessageBox::critical(this, "Erreur", error);
        return;
    }

    // SMTP
    const QString smtpUser = "ghaythweslaty10@gmail.com";
    const QString smtpPass = "dcixvxvphgsofajg";

    SmtpClient smtp("smtp.gmail.com", 465, smtpUser, smtpPass, this);

    QString htmlBody =
        "<h2>SightIQ - Réinitialisation du mot de passe</h2>"
        "<p>Votre code est :</p>"
        "<h1 style='letter-spacing:5px;'>" + otp + "</h1>"
                "<p>Ce code est valable pendant 10 minutes.</p>";

    QString mailError;
    QString senderName = "SightIQ <" + smtpUser + ">";

    bool ok = smtp.sendMail(senderName,
                            email,
                            "Code de réinitialisation",
                            htmlBody,
                            &mailError,
                            true);

    if (!ok) {
        QMessageBox::critical(this, "Erreur", mailError);
        return;
    }

    QMessageBox::information(this, "Succès", "Code envoyé avec succès !");
}

// ✅ RESET BUTTON
void ForgotPassword::on_pushButton_reset_clicked()
{
    const QString username = ui->lineEdit_username->text().trimmed();
    const QString email = ui->lineEdit_email->text().trimmed();
    const QString code = ui->lineEdit_code->text().trimmed();
    const QString newPassword = ui->lineEdit_new_password->text();
    const QString confirmPassword = ui->lineEdit_confirm_password->text();

    if (username.isEmpty() || email.isEmpty() ||
        code.isEmpty() || newPassword.isEmpty() ||
        confirmPassword.isEmpty()) {

        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }

    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas !");
        return;
    }

    if (newPassword.length() < 6) {
        QMessageBox::warning(this, "Erreur",
                             "Mot de passe trop court (min 6 caractères)");
        return;
    }

    QString error;
    if (!verifyOtpAndChangePassword(email, code, newPassword, error)) {
        QMessageBox::critical(this, "Erreur", error);
        return;
    }

    QMessageBox::information(this,
                             "Succès",
                             "Mot de passe changé avec succès !");
    accept();
}

// ✅ CANCEL BUTTON
void ForgotPassword::on_pushButton_cancel_clicked()
{
    reject();
}
