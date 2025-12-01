/********************************************************************************
** Form generated from reading UI file 'employeeregister.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEREGISTER_H
#define UI_EMPLOYEEREGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EmployeeRegister
{
public:
    QLabel *logoLabel;
    QGroupBox *groupBox;
    QLabel *label_nom;
    QLineEdit *lineEdit_nom;
    QLabel *label_prenom;
    QLineEdit *lineEdit_prenom;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QLabel *label_telephone;
    QLineEdit *lineEdit_telephone;
    QLabel *label_date_naissance;
    QDateEdit *dateEdit_naissance;
    QLabel *label_adresse;
    QLineEdit *lineEdit_adresse;
    QLabel *label_role;
    QComboBox *comboBox_role;
    QLabel *label_salaire;
    QLineEdit *lineEdit_salaire;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_register;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *EmployeeRegister)
    {
        if (EmployeeRegister->objectName().isEmpty())
            EmployeeRegister->setObjectName("EmployeeRegister");
        EmployeeRegister->resize(1249, 821);
        EmployeeRegister->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        logoLabel = new QLabel(EmployeeRegister);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1120, 20, 100, 100));
        logoLabel->setMinimumSize(QSize(60, 60));
        logoLabel->setMaximumSize(QSize(100, 100));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(EmployeeRegister);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(200, 100, 850, 650));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
" border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;     \n"
"background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;       /* title centered */\n"
"    padding: 2px 10px;\n"
"}"));
        label_nom = new QLabel(groupBox);
        label_nom->setObjectName("label_nom");
        label_nom->setGeometry(QRect(60, 60, 81, 20));
        label_nom->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(60, 90, 291, 41));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_prenom = new QLabel(groupBox);
        label_prenom->setObjectName("label_prenom");
        label_prenom->setGeometry(QRect(480, 60, 81, 20));
        label_prenom->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(480, 90, 291, 41));
        lineEdit_prenom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_email = new QLabel(groupBox);
        label_email->setObjectName("label_email");
        label_email->setGeometry(QRect(60, 150, 81, 20));
        label_email->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_email = new QLineEdit(groupBox);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(60, 180, 291, 41));
        lineEdit_email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_telephone = new QLabel(groupBox);
        label_telephone->setObjectName("label_telephone");
        label_telephone->setGeometry(QRect(480, 150, 81, 20));
        label_telephone->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_telephone = new QLineEdit(groupBox);
        lineEdit_telephone->setObjectName("lineEdit_telephone");
        lineEdit_telephone->setGeometry(QRect(480, 180, 291, 41));
        lineEdit_telephone->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_date_naissance = new QLabel(groupBox);
        label_date_naissance->setObjectName("label_date_naissance");
        label_date_naissance->setGeometry(QRect(60, 240, 121, 20));
        label_date_naissance->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        dateEdit_naissance = new QDateEdit(groupBox);
        dateEdit_naissance->setObjectName("dateEdit_naissance");
        dateEdit_naissance->setGeometry(QRect(60, 270, 291, 41));
        dateEdit_naissance->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        dateEdit_naissance->setCalendarPopup(true);
        label_adresse = new QLabel(groupBox);
        label_adresse->setObjectName("label_adresse");
        label_adresse->setGeometry(QRect(480, 240, 81, 20));
        label_adresse->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_adresse = new QLineEdit(groupBox);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(480, 270, 291, 41));
        lineEdit_adresse->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_role = new QLabel(groupBox);
        label_role->setObjectName("label_role");
        label_role->setGeometry(QRect(60, 330, 81, 20));
        label_role->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        comboBox_role = new QComboBox(groupBox);
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->addItem(QString());
        comboBox_role->setObjectName("comboBox_role");
        comboBox_role->setGeometry(QRect(60, 360, 291, 41));
        comboBox_role->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_salaire = new QLabel(groupBox);
        label_salaire->setObjectName("label_salaire");
        label_salaire->setGeometry(QRect(480, 330, 81, 20));
        label_salaire->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_salaire = new QLineEdit(groupBox);
        lineEdit_salaire->setObjectName("lineEdit_salaire");
        lineEdit_salaire->setGeometry(QRect(480, 360, 291, 41));
        lineEdit_salaire->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_username = new QLabel(groupBox);
        label_username->setObjectName("label_username");
        label_username->setGeometry(QRect(60, 420, 121, 20));
        label_username->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_username = new QLineEdit(groupBox);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(60, 450, 291, 41));
        lineEdit_username->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_password = new QLabel(groupBox);
        label_password->setObjectName("label_password");
        label_password->setGeometry(QRect(480, 420, 121, 20));
        label_password->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(480, 450, 291, 41));
        lineEdit_password->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        pushButton_register = new QPushButton(groupBox);
        pushButton_register->setObjectName("pushButton_register");
        pushButton_register->setGeometry(QRect(60, 520, 291, 61));
        pushButton_register->setStyleSheet(QString::fromUtf8("#pushButton_register {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_register:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_register:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_cancel = new QPushButton(groupBox);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(480, 520, 291, 61));
        pushButton_cancel->setStyleSheet(QString::fromUtf8("#pushButton_cancel {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #808080;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_cancel:hover {\n"
"    background-color: #606060; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_cancel:pressed {\n"
"    background-color: #404040; /* pressed effect */\n"
"}"));

        retranslateUi(EmployeeRegister);

        QMetaObject::connectSlotsByName(EmployeeRegister);
    } // setupUi

    void retranslateUi(QDialog *EmployeeRegister)
    {
        EmployeeRegister->setWindowTitle(QCoreApplication::translate("EmployeeRegister", "Employee Registration", nullptr));
        logoLabel->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("EmployeeRegister", "Employee Registration", nullptr));
        label_nom->setText(QCoreApplication::translate("EmployeeRegister", "Nom :", nullptr));
        label_prenom->setText(QCoreApplication::translate("EmployeeRegister", "Pr\303\251nom :", nullptr));
        label_email->setText(QCoreApplication::translate("EmployeeRegister", "Email :", nullptr));
        label_telephone->setText(QCoreApplication::translate("EmployeeRegister", "T\303\251l\303\251phone :", nullptr));
        label_date_naissance->setText(QCoreApplication::translate("EmployeeRegister", "Date de naissance :", nullptr));
        dateEdit_naissance->setDisplayFormat(QCoreApplication::translate("EmployeeRegister", "dd/MM/yyyy", nullptr));
        label_adresse->setText(QCoreApplication::translate("EmployeeRegister", "Adresse :", nullptr));
        label_role->setText(QCoreApplication::translate("EmployeeRegister", "R\303\264le :", nullptr));
        comboBox_role->setItemText(0, QCoreApplication::translate("EmployeeRegister", "admin", nullptr));
        comboBox_role->setItemText(1, QCoreApplication::translate("EmployeeRegister", "stock", nullptr));
        comboBox_role->setItemText(2, QCoreApplication::translate("EmployeeRegister", "vente", nullptr));
        comboBox_role->setItemText(3, QCoreApplication::translate("EmployeeRegister", "client", nullptr));
        comboBox_role->setItemText(4, QCoreApplication::translate("EmployeeRegister", "fournisseur", nullptr));
        comboBox_role->setItemText(5, QCoreApplication::translate("EmployeeRegister", "employe", nullptr));

        label_salaire->setText(QCoreApplication::translate("EmployeeRegister", "Salaire :", nullptr));
        label_username->setText(QCoreApplication::translate("EmployeeRegister", "Nom d'utilisateur :", nullptr));
        label_password->setText(QCoreApplication::translate("EmployeeRegister", "Mot de passe :", nullptr));
        pushButton_register->setText(QCoreApplication::translate("EmployeeRegister", "S'inscrire", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("EmployeeRegister", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployeeRegister: public Ui_EmployeeRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEREGISTER_H
