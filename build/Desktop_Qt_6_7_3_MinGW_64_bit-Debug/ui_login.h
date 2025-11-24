/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *logoLabel;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLineEdit *id1;
    QLineEdit *mot1;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_register;
    QPushButton *pushButton_forgot_password;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(1249, 821);
        login->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        logoLabel = new QLabel(login);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1120, 20, 100, 100));
        logoLabel->setMinimumSize(QSize(60, 60));
        logoLabel->setMaximumSize(QSize(100, 100));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(login);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(410, 240, 441, 371));
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
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 70, 81, 20));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        id1 = new QLineEdit(groupBox);
        id1->setObjectName("id1");
        id1->setGeometry(QRect(60, 110, 291, 41));
        id1->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        mot1 = new QLineEdit(groupBox);
        mot1->setObjectName("mot1");
        mot1->setGeometry(QRect(60, 210, 291, 41));
        mot1->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        mot1->setEchoMode(QLineEdit::EchoMode::Password);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 170, 121, 20));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(60, 280, 291, 61));
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_register = new QPushButton(login);
        pushButton_register->setObjectName("pushButton_register");
        pushButton_register->setGeometry(QRect(550, 630, 150, 30));
        pushButton_register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: blue;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    text-decoration: underline;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    color: darkblue;\n"
"}"));
        pushButton_forgot_password = new QPushButton(login);
        pushButton_forgot_password->setObjectName("pushButton_forgot_password");
        pushButton_forgot_password->setGeometry(QRect(550, 670, 150, 30));
        pushButton_forgot_password->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: blue;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    text-decoration: underline;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    color: darkblue;\n"
"}"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        logoLabel->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("login", "login", nullptr));
        label_2->setText(QCoreApplication::translate("login", "Identifiant :", nullptr));
        label_3->setText(QCoreApplication::translate("login", "mot de passe :", nullptr));
        pushButton_2->setText(QCoreApplication::translate("login", "Se connecter", nullptr));
        pushButton_register->setText(QCoreApplication::translate("login", "S'inscrire", nullptr));
        pushButton_forgot_password->setText(QCoreApplication::translate("login", "Mot de passe oubli\303\251 ?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
