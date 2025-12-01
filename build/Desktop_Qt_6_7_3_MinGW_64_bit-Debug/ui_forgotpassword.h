/********************************************************************************
** Form generated from reading UI file 'forgotpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASSWORD_H
#define UI_FORGOTPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ForgotPassword
{
public:
    QGroupBox *groupBox;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QPushButton *pushButton_send_code;
    QLabel *label_code;
    QLineEdit *lineEdit_code;
    QLabel *label_new_password;
    QLineEdit *lineEdit_new_password;
    QLabel *label_confirm_password;
    QLineEdit *lineEdit_confirm_password;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *ForgotPassword)
    {
        if (ForgotPassword->objectName().isEmpty())
            ForgotPassword->setObjectName("ForgotPassword");
        ForgotPassword->resize(600, 650);
        ForgotPassword->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        groupBox = new QGroupBox(ForgotPassword);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(50, 30, 500, 590));
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
        label_username = new QLabel(groupBox);
        label_username->setObjectName("label_username");
        label_username->setGeometry(QRect(100, 60, 300, 20));
        label_username->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_username = new QLineEdit(groupBox);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(100, 90, 300, 41));
        lineEdit_username->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_email = new QLabel(groupBox);
        label_email->setObjectName("label_email");
        label_email->setGeometry(QRect(100, 150, 300, 20));
        label_email->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_email = new QLineEdit(groupBox);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(100, 180, 300, 41));
        lineEdit_email->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_send_code = new QPushButton(groupBox);
        pushButton_send_code->setObjectName("pushButton_send_code");
        pushButton_send_code->setGeometry(QRect(100, 230, 300, 30));
        pushButton_send_code->setStyleSheet(QString::fromUtf8("font-weight: bold; background-color: #0c66ed; color: white; border-radius: 6px;"));
        label_code = new QLabel(groupBox);
        label_code->setObjectName("label_code");
        label_code->setGeometry(QRect(100, 270, 300, 20));
        label_code->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_code = new QLineEdit(groupBox);
        lineEdit_code->setObjectName("lineEdit_code");
        lineEdit_code->setGeometry(QRect(100, 300, 300, 41));
        lineEdit_code->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_new_password = new QLabel(groupBox);
        label_new_password->setObjectName("label_new_password");
        label_new_password->setGeometry(QRect(100, 350, 300, 20));
        label_new_password->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_new_password = new QLineEdit(groupBox);
        lineEdit_new_password->setObjectName("lineEdit_new_password");
        lineEdit_new_password->setGeometry(QRect(100, 380, 300, 41));
        lineEdit_new_password->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_new_password->setEchoMode(QLineEdit::Password);
        label_confirm_password = new QLabel(groupBox);
        label_confirm_password->setObjectName("label_confirm_password");
        label_confirm_password->setGeometry(QRect(100, 440, 300, 20));
        label_confirm_password->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_confirm_password = new QLineEdit(groupBox);
        lineEdit_confirm_password->setObjectName("lineEdit_confirm_password");
        lineEdit_confirm_password->setGeometry(QRect(100, 470, 300, 41));
        lineEdit_confirm_password->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_confirm_password->setEchoMode(QLineEdit::Password);
        pushButton_reset = new QPushButton(groupBox);
        pushButton_reset->setObjectName("pushButton_reset");
        pushButton_reset->setGeometry(QRect(100, 520, 140, 50));
        pushButton_reset->setStyleSheet(QString::fromUtf8("#pushButton_reset {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_reset:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_reset:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_cancel = new QPushButton(groupBox);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(260, 520, 140, 50));
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

        retranslateUi(ForgotPassword);

        QMetaObject::connectSlotsByName(ForgotPassword);
    } // setupUi

    void retranslateUi(QDialog *ForgotPassword)
    {
        ForgotPassword->setWindowTitle(QCoreApplication::translate("ForgotPassword", "Mot de passe oubli\303\251", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ForgotPassword", "R\303\251cup\303\251ration du mot de passe", nullptr));
        label_username->setText(QCoreApplication::translate("ForgotPassword", "Nom d'utilisateur :", nullptr));
        label_email->setText(QCoreApplication::translate("ForgotPassword", "Email :", nullptr));
        pushButton_send_code->setText(QCoreApplication::translate("ForgotPassword", "Envoyer le code par email", nullptr));
        label_code->setText(QCoreApplication::translate("ForgotPassword", "Code re\303\247u par email :", nullptr));
        label_new_password->setText(QCoreApplication::translate("ForgotPassword", "Nouveau mot de passe :", nullptr));
        label_confirm_password->setText(QCoreApplication::translate("ForgotPassword", "Confirmer le mot de passe :", nullptr));
        pushButton_reset->setText(QCoreApplication::translate("ForgotPassword", "R\303\251initialiser", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("ForgotPassword", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForgotPassword: public Ui_ForgotPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASSWORD_H
