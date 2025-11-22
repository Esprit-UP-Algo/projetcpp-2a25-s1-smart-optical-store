/********************************************************************************
** Form generated from reading UI file 'tab.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_H
#define UI_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_tab
{
public:
    QLabel *logoLabel;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *emp;

    void setupUi(QDialog *tab)
    {
        if (tab->objectName().isEmpty())
            tab->setObjectName("tab");
        tab->resize(1169, 827);
        tab->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        logoLabel = new QLabel(tab);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1050, 20, 100, 100));
        logoLabel->setMinimumSize(QSize(60, 60));
        logoLabel->setMaximumSize(QSize(100, 100));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(390, 80, 381, 701));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        pushButton_10 = new QPushButton(groupBox_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(70, 230, 251, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("#pushButton_10 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_10:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_10:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(70, 340, 251, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("#pushButton_11 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_11:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_11:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_12 = new QPushButton(groupBox_2);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(70, 450, 251, 51));
        pushButton_12->setStyleSheet(QString::fromUtf8("#pushButton_12 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_12:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_12:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_13 = new QPushButton(groupBox_2);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(70, 570, 251, 51));
        pushButton_13->setStyleSheet(QString::fromUtf8("#pushButton_13 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_13:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_13:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        emp = new QPushButton(groupBox_2);
        emp->setObjectName("emp");
        emp->setGeometry(QRect(70, 110, 251, 51));
        emp->setStyleSheet(QString::fromUtf8("#emp{\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#emp:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#emp:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));

        retranslateUi(tab);

        QMetaObject::connectSlotsByName(tab);
    } // setupUi

    void retranslateUi(QDialog *tab)
    {
        tab->setWindowTitle(QCoreApplication::translate("tab", "Dialog", nullptr));
        logoLabel->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("tab", "tableau de bord", nullptr));
        pushButton_10->setText(QCoreApplication::translate("tab", "Stock", nullptr));
        pushButton_11->setText(QCoreApplication::translate("tab", "Ventes", nullptr));
        pushButton_12->setText(QCoreApplication::translate("tab", "Client", nullptr));
        pushButton_13->setText(QCoreApplication::translate("tab", "Fournisseur", nullptr));
        emp->setText(QCoreApplication::translate("tab", "Employes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab: public Ui_tab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_H
