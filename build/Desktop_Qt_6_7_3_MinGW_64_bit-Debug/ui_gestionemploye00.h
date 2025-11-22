/********************************************************************************
** Form generated from reading UI file 'gestionemploye00.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONEMPLOYE00_H
#define UI_GESTIONEMPLOYE00_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gestionemploye00
{
public:
    QLabel *logoLabel;
    QLineEdit *lineEdit_12;
    QPushButton *pushButton_4;
    QTableWidget *tableWidget;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_10;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_5;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_6;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QLineEdit *lineEdit_8;
    QLabel *label_9;
    QLineEdit *lineEdit_9;
    QLabel *label_10;
    QLineEdit *lineEdit_10;
    QLabel *label_12;
    QComboBox *comboBox_disponibilite;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QPushButton *pushButton_14;

    void setupUi(QWidget *gestionemploye00)
    {
        if (gestionemploye00->objectName().isEmpty())
            gestionemploye00->setObjectName("gestionemploye00");
        gestionemploye00->resize(1165, 825);
        gestionemploye00->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        logoLabel = new QLabel(gestionemploye00);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1050, 20, 80, 80));
        logoLabel->setMinimumSize(QSize(60, 60));
        logoLabel->setMaximumSize(QSize(80, 80));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_12 = new QLineEdit(gestionemploye00);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(590, 160, 281, 28));
        lineEdit_12->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_4 = new QPushButton(gestionemploye00);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(870, 160, 131, 31));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        tableWidget = new QTableWidget(gestionemploye00);
        if (tableWidget->columnCount() < 11)
            tableWidget->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(500, 200, 651, 491));
        tableWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_3 = new QPushButton(gestionemploye00);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(510, 730, 141, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        pushButton_5 = new QPushButton(gestionemploye00);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(680, 730, 131, 31));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        pushButton_6 = new QPushButton(gestionemploye00);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(840, 730, 141, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        pushButton_10 = new QPushButton(gestionemploye00);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(1010, 730, 141, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        groupBox = new QGroupBox(gestionemploye00);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(210, 50, 281, 771));
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
"}\n"
""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 50, 72, 28));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 80, 231, 28));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 110, 51, 28));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(20, 140, 231, 28));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 170, 55, 28));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(20, 200, 231, 28));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 230, 72, 28));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(20, 320, 231, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(20, 260, 231, 28));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 290, 41, 28));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 350, 55, 28));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(20, 380, 231, 28));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 410, 48, 28));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(20, 440, 231, 28));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 470, 122, 28));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(20, 500, 231, 28));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 530, 38, 28));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(20, 560, 231, 28));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 590, 48, 28));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_10 = new QLineEdit(groupBox);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(20, 620, 231, 28));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 650, 88, 28));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        comboBox_disponibilite = new QComboBox(groupBox);
        comboBox_disponibilite->addItem(QString());
        comboBox_disponibilite->addItem(QString());
        comboBox_disponibilite->setObjectName("comboBox_disponibilite");
        comboBox_disponibilite->setGeometry(QRect(20, 680, 231, 28));
        pushButton_12 = new QPushButton(groupBox);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(140, 720, 91, 31));
        pushButton_12->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        pushButton_13 = new QPushButton(groupBox);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(20, 720, 81, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color:white;"));
        groupBox_2 = new QGroupBox(gestionemploye00);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 30, 191, 781));
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
        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(0, 350, 189, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("#pushButton_7 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_7:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_7:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(0, 250, 189, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("#pushButton_8 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_8:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton86:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(0, 450, 189, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("#pushButton_9 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_9:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_9:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(0, 550, 189, 51));
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
        pushButton_14 = new QPushButton(groupBox_2);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(0, 140, 189, 51));
        pushButton_14->setStyleSheet(QString::fromUtf8("#pushButton_14 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_14:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton14:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));

        retranslateUi(gestionemploye00);

        QMetaObject::connectSlotsByName(gestionemploye00);
    } // setupUi

    void retranslateUi(QWidget *gestionemploye00)
    {
        gestionemploye00->setWindowTitle(QCoreApplication::translate("gestionemploye00", "gestionemploye00", nullptr));
        logoLabel->setText(QString());
        lineEdit_12->setText(QString());
        lineEdit_12->setPlaceholderText(QCoreApplication::translate("gestionemploye00", "rechercher ar nom ou prenom ou email", nullptr));
        pushButton_4->setText(QCoreApplication::translate("gestionemploye00", "Rechercher", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("gestionemploye00", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("gestionemploye00", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("gestionemploye00", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("gestionemploye00", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("gestionemploye00", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("gestionemploye00", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("gestionemploye00", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("gestionemploye00", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("gestionemploye00", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("gestionemploye00", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("gestionemploye00", "Disponibilite", nullptr));
        pushButton_3->setText(QCoreApplication::translate("gestionemploye00", "Afficher", nullptr));
        pushButton_5->setText(QCoreApplication::translate("gestionemploye00", "trier", nullptr));
        pushButton_6->setText(QCoreApplication::translate("gestionemploye00", "Statistique", nullptr));
        pushButton_10->setText(QCoreApplication::translate("gestionemploye00", "Exporter", nullptr));
        groupBox->setTitle(QCoreApplication::translate("gestionemploye00", "Ajouter un employe", nullptr));
        label_3->setText(QCoreApplication::translate("gestionemploye00", "ID:", nullptr));
        label_4->setText(QCoreApplication::translate("gestionemploye00", "Nom  :", nullptr));
        label_2->setText(QCoreApplication::translate("gestionemploye00", "Prenom:", nullptr));
        label->setText(QCoreApplication::translate("gestionemploye00", "T\303\251l\303\251phone:", nullptr));
        label_6->setText(QCoreApplication::translate("gestionemploye00", "Date:", nullptr));
        label_7->setText(QCoreApplication::translate("gestionemploye00", "Adresse:", nullptr));
        label_5->setText(QCoreApplication::translate("gestionemploye00", "Email", nullptr));
        label_8->setText(QCoreApplication::translate("gestionemploye00", "Nombre d\342\200\231enfants:", nullptr));
        label_9->setText(QCoreApplication::translate("gestionemploye00", "Poste:", nullptr));
        label_10->setText(QCoreApplication::translate("gestionemploye00", "Salaire:", nullptr));
        label_12->setText(QCoreApplication::translate("gestionemploye00", "Disponibilite:", nullptr));
        comboBox_disponibilite->setItemText(0, QCoreApplication::translate("gestionemploye00", "O", nullptr));
        comboBox_disponibilite->setItemText(1, QCoreApplication::translate("gestionemploye00", "N", nullptr));

        pushButton_12->setText(QCoreApplication::translate("gestionemploye00", "effacer", nullptr));
        pushButton_13->setText(QCoreApplication::translate("gestionemploye00", "Valider", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("gestionemploye00", "tableau de bord", nullptr));
        pushButton_7->setText(QCoreApplication::translate("gestionemploye00", "Employe", nullptr));
        pushButton_8->setText(QCoreApplication::translate("gestionemploye00", "Ventes", nullptr));
        pushButton_9->setText(QCoreApplication::translate("gestionemploye00", "Client", nullptr));
        pushButton_11->setText(QCoreApplication::translate("gestionemploye00", "Fournisseur", nullptr));
        pushButton_14->setText(QCoreApplication::translate("gestionemploye00", "Stock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gestionemploye00: public Ui_gestionemploye00 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONEMPLOYE00_H
