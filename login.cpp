#include "login.h"
#include "ui_login.h"
#include "dashboardwindow.h"
#include "gestionemploye00.h"
#include "employe.h"
#include "employeeregister.h"
#include "forgotpassword.h"
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QRegularExpression>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    // Set the window title
    setWindowTitle("Login - Smart Optical Store");
    
    // Connect to the database
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("DRIVER={Oracle in OraDB23Home1};" "SERVER=localhost:1521/xepdb1;" "DATABASE=GHAITH;" "UID=GHAITH;" "PWD=ghaith2004;");
    } else {
        db = QSqlDatabase::database();
    }
    
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Database connection error:" << db.lastError().text();
            QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à la base de données: " + db.lastError().text());
        }
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_2_clicked()
{
    QString username = ui->id1->text();
    QString password = ui->mot1->text();

    // Authenticate against the employee database
    Employe authenticatedEmployee = Employe::authenticate(username, password);
    
    if (authenticatedEmployee.getId() > 0) {
        // Authentication successful
        QString role = authenticatedEmployee.getRole();
        if (role == "admin") {
            // Admin user - show full dashboard
            DashboardWindow::getInstance(role);
        } else if (role == "stock") {
            // Stock manager - show stock management
            MainWindow::getInstance(role);
        } else if (role == "vente") {
            // Sales person - show sales management
            SalesWindow::getInstance(role);
        } else if (role == "client") {
            // Client manager - show client management
            Gclient1::getInstance(role);
        } else if (role == "fournisseur") {
            // Supplier manager - show supplier management
            FournisseurWindow::getInstance(role);
        } else if (role == "employe") {
            // Regular employee - show employee management
            gestionemploye00::getInstance(role);
        } else {
            // Default to employee management for any other role
            gestionemploye00::getInstance(role);
        }
        this->close();
    } else {
        QMessageBox::warning(this, "Erreur d'authentification", "Nom d'utilisateur ou mot de passe incorrect");
    }
}

void login::on_pushButton_register_clicked()
{
    EmployeeRegister registerDialog(this);
    registerDialog.setModal(true);
    registerDialog.exec();
}

void login::on_pushButton_forgot_password_clicked()
{
    ForgotPassword forgotPasswordDialog(this);
    forgotPasswordDialog.setModal(true);
    forgotPasswordDialog.exec();
}