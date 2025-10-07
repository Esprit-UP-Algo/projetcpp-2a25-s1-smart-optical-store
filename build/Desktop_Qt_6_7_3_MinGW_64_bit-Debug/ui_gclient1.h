/********************************************************************************
** Form generated from reading UI file 'gclient1.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCLIENT1_H
#define UI_GCLIENT1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionClients
{
public:
    QWidget *centralwidget;
    QLabel *labelLogoTopRight;
    QHBoxLayout *mainLayoutRoot;
    QFrame *sidebarFrame;
    QVBoxLayout *sidebarLayout;
    QLabel *sidebarHeader;
    QPushButton *btnClients;
    QPushButton *btnProduit;
    QPushButton *btnVentes;
    QPushButton *btnEmployes;
    QPushButton *btnDashboard;
    QVBoxLayout *contentAreaLayout;
    QLabel *mainTitle;
    QTabWidget *tabWidgetMain;
    QWidget *tabListeClients;
    QVBoxLayout *layoutListeClients;
    QHBoxLayout *layoutSearch;
    QLineEdit *lineEditSearch;
    QLabel *labelFilter;
    QComboBox *comboBoxTri;
    QTableWidget *tableWidgetClients;
    QHBoxLayout *layoutButtons;
    QPushButton *btnExport;
    QPushButton *btnDelete;
    QWidget *tabAddClient;
    QGridLayout *layoutForm;
    QLabel *labelID;
    QLineEdit *lineEditID;
    QLabel *labelNom;
    QLineEdit *lineEditNom;
    QLabel *labelPrenom;
    QLineEdit *lineEditPrenom;
    QLabel *labelDateNaissance;
    QDateEdit *dateEditNaissance;
    QLabel *labelSexe;
    QComboBox *comboBoxSexe;
    QLabel *labelAdresse;
    QLineEdit *lineEditAdresse;
    QLabel *labelTelephone;
    QLineEdit *lineEditTelephone;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QHBoxLayout *layoutButtonsForm;
    QPushButton *btnSave;
    QPushButton *btnCancel;
    QWidget *tabStats;
    QVBoxLayout *layoutStats;
    QLabel *labelStatsTitle;
    QLabel *labelStatsContent;

    void setupUi(QMainWindow *GestionClients)
    {
        if (GestionClients->objectName().isEmpty())
            GestionClients->setObjectName("GestionClients");
        GestionClients->resize(1200, 800);
        centralwidget = new QWidget(GestionClients);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background-color: #b9e3f7; font-family: \"Segoe UI\", Tahoma, Geneva, Verdana, sans-serif; font-size: 13px; color: #0f172a; }\n"
"#sidebarFrame { background-color: #24587a; border-radius: 8px; padding-top: 12px; padding-bottom: 12px; min-height: 100%; }\n"
"QLabel#sidebarHeader { background-color: #1b4966; color: white; font-weight: 700; padding: 10px 16px; border-radius: 12px; margin: 6px; min-width: 180px; max-height: 42px; }\n"
"QPushButton#btnClients, QPushButton#btnProduit, QPushButton#btnVentes, QPushButton#btnEmployes, QPushButton#btnDashboard { background-color: #24587a; color: white; border: 2px solid #1b4a67; font-weight: bold; text-align: left; padding: 12px 20px; border-radius: 6px; min-width: 180px; margin: 6px; min-height: 56px; }\n"
"QPushButton#btnClients { background-color: #357fa3; border: 2px solid #2d6f91; }\n"
"QPushButton#btnProduit:hover, QPushButton#btnVentes:hover, QPushButton#btnEmployes:hover, QPushButton#btnClients:hover, QPushButton#btnDashboard:hover { background-co"
                        "lor: #357fa3; }\n"
"QLabel#mainTitle { font-size: 20px; font-weight: 800; color: #0f172a; background-color: #bfeafc; padding: 10px 16px; border-radius: 10px; border: 1px solid #89c3e2; }\n"
"QPushButton { background-color: #48a4d6; color: white; border-radius: 6px; padding: 8px 14px; font-weight: 600; border: none; }\n"
"QPushButton:hover { background-color: #5ab5e3; }\n"
"QPushButton#btnDelete { background-color: #d64545; }\n"
"QPushButton#btnDelete:hover { background-color: #b53030; }\n"
"QPushButton#btnExport { background-color: #48b36b; }\n"
"QPushButton#btnExport:hover { background-color: #3da25f; }\n"
"QLineEdit, QComboBox, QDateEdit { background-color: white; border: 1px solid #89c3e2; border-radius: 6px; padding: 8px; color: #0f172a; min-height: 30px; }\n"
"QLabel { font-weight: 600; color: #0f172a; }\n"
"QTableWidget { background-color: white; gridline-color: #90caf9; selection-background-color: #48a4d6; selection-color: white; alternate-background-color: #e9f5fc; border: 1px solid #89c3e2; border-rad"
                        "ius: 8px; }\n"
"QHeaderView::section { background-color: #24587a; color: white; font-weight: bold; height: 28px; border: none; }\n"
"QTabWidget::pane { border: 1px solid #89c3e2; border-radius: 6px; }\n"
"QTabBar::tab { background: #e2e8f0; border-radius: 6px; padding: 10px 20px; margin: 4px; color: #0f172a; min-width: 140px; }\n"
"QTabBar::tab:selected { background: #24587a; color: white; }\n"
"QComboBox::drop-down, QDateEdit::drop-down { border: none; }\n"
"#labelLogoTopRight { background: transparent; border: none; }\n"
"    "));
        labelLogoTopRight = new QLabel(centralwidget);
        labelLogoTopRight->setObjectName("labelLogoTopRight");
        labelLogoTopRight->setGeometry(QRect(1120, 10, 70, 70));
        labelLogoTopRight->setPixmap(QPixmap(QString::fromUtf8("smart_logo.png.jpg")));
        labelLogoTopRight->setScaledContents(true);
        mainLayoutRoot = new QHBoxLayout(centralwidget);
        mainLayoutRoot->setObjectName("mainLayoutRoot");
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarLayout = new QVBoxLayout(sidebarFrame);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarHeader = new QLabel(sidebarFrame);
        sidebarHeader->setObjectName("sidebarHeader");
        sidebarHeader->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(sidebarHeader);

        btnClients = new QPushButton(sidebarFrame);
        btnClients->setObjectName("btnClients");

        sidebarLayout->addWidget(btnClients);

        btnProduit = new QPushButton(sidebarFrame);
        btnProduit->setObjectName("btnProduit");

        sidebarLayout->addWidget(btnProduit);

        btnVentes = new QPushButton(sidebarFrame);
        btnVentes->setObjectName("btnVentes");

        sidebarLayout->addWidget(btnVentes);

        btnEmployes = new QPushButton(sidebarFrame);
        btnEmployes->setObjectName("btnEmployes");

        sidebarLayout->addWidget(btnEmployes);

        btnDashboard = new QPushButton(sidebarFrame);
        btnDashboard->setObjectName("btnDashboard");

        sidebarLayout->addWidget(btnDashboard);


        mainLayoutRoot->addWidget(sidebarFrame);

        contentAreaLayout = new QVBoxLayout();
        contentAreaLayout->setObjectName("contentAreaLayout");
        mainTitle = new QLabel(centralwidget);
        mainTitle->setObjectName("mainTitle");

        contentAreaLayout->addWidget(mainTitle);

        tabWidgetMain = new QTabWidget(centralwidget);
        tabWidgetMain->setObjectName("tabWidgetMain");
        tabListeClients = new QWidget();
        tabListeClients->setObjectName("tabListeClients");
        layoutListeClients = new QVBoxLayout(tabListeClients);
        layoutListeClients->setObjectName("layoutListeClients");
        layoutSearch = new QHBoxLayout();
        layoutSearch->setObjectName("layoutSearch");
        lineEditSearch = new QLineEdit(tabListeClients);
        lineEditSearch->setObjectName("lineEditSearch");

        layoutSearch->addWidget(lineEditSearch);

        labelFilter = new QLabel(tabListeClients);
        labelFilter->setObjectName("labelFilter");

        layoutSearch->addWidget(labelFilter);

        comboBoxTri = new QComboBox(tabListeClients);
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->setObjectName("comboBoxTri");

        layoutSearch->addWidget(comboBoxTri);


        layoutListeClients->addLayout(layoutSearch);

        tableWidgetClients = new QTableWidget(tabListeClients);
        if (tableWidgetClients->columnCount() < 9)
            tableWidgetClients->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidgetClients->setObjectName("tableWidgetClients");
        tableWidgetClients->setColumnCount(9);

        layoutListeClients->addWidget(tableWidgetClients);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName("layoutButtons");
        btnExport = new QPushButton(tabListeClients);
        btnExport->setObjectName("btnExport");

        layoutButtons->addWidget(btnExport);

        btnDelete = new QPushButton(tabListeClients);
        btnDelete->setObjectName("btnDelete");

        layoutButtons->addWidget(btnDelete);


        layoutListeClients->addLayout(layoutButtons);

        tabWidgetMain->addTab(tabListeClients, QString());
        tabAddClient = new QWidget();
        tabAddClient->setObjectName("tabAddClient");
        layoutForm = new QGridLayout(tabAddClient);
        layoutForm->setObjectName("layoutForm");
        labelID = new QLabel(tabAddClient);
        labelID->setObjectName("labelID");

        layoutForm->addWidget(labelID, 0, 0, 1, 1);

        lineEditID = new QLineEdit(tabAddClient);
        lineEditID->setObjectName("lineEditID");

        layoutForm->addWidget(lineEditID, 0, 1, 1, 1);

        labelNom = new QLabel(tabAddClient);
        labelNom->setObjectName("labelNom");

        layoutForm->addWidget(labelNom, 1, 0, 1, 1);

        lineEditNom = new QLineEdit(tabAddClient);
        lineEditNom->setObjectName("lineEditNom");

        layoutForm->addWidget(lineEditNom, 1, 1, 1, 1);

        labelPrenom = new QLabel(tabAddClient);
        labelPrenom->setObjectName("labelPrenom");

        layoutForm->addWidget(labelPrenom, 2, 0, 1, 1);

        lineEditPrenom = new QLineEdit(tabAddClient);
        lineEditPrenom->setObjectName("lineEditPrenom");

        layoutForm->addWidget(lineEditPrenom, 2, 1, 1, 1);

        labelDateNaissance = new QLabel(tabAddClient);
        labelDateNaissance->setObjectName("labelDateNaissance");

        layoutForm->addWidget(labelDateNaissance, 3, 0, 1, 1);

        dateEditNaissance = new QDateEdit(tabAddClient);
        dateEditNaissance->setObjectName("dateEditNaissance");
        dateEditNaissance->setCalendarPopup(true);

        layoutForm->addWidget(dateEditNaissance, 3, 1, 1, 1);

        labelSexe = new QLabel(tabAddClient);
        labelSexe->setObjectName("labelSexe");

        layoutForm->addWidget(labelSexe, 4, 0, 1, 1);

        comboBoxSexe = new QComboBox(tabAddClient);
        comboBoxSexe->addItem(QString());
        comboBoxSexe->addItem(QString());
        comboBoxSexe->setObjectName("comboBoxSexe");

        layoutForm->addWidget(comboBoxSexe, 4, 1, 1, 1);

        labelAdresse = new QLabel(tabAddClient);
        labelAdresse->setObjectName("labelAdresse");

        layoutForm->addWidget(labelAdresse, 5, 0, 1, 1);

        lineEditAdresse = new QLineEdit(tabAddClient);
        lineEditAdresse->setObjectName("lineEditAdresse");

        layoutForm->addWidget(lineEditAdresse, 5, 1, 1, 1);

        labelTelephone = new QLabel(tabAddClient);
        labelTelephone->setObjectName("labelTelephone");

        layoutForm->addWidget(labelTelephone, 6, 0, 1, 1);

        lineEditTelephone = new QLineEdit(tabAddClient);
        lineEditTelephone->setObjectName("lineEditTelephone");

        layoutForm->addWidget(lineEditTelephone, 6, 1, 1, 1);

        labelEmail = new QLabel(tabAddClient);
        labelEmail->setObjectName("labelEmail");

        layoutForm->addWidget(labelEmail, 7, 0, 1, 1);

        lineEditEmail = new QLineEdit(tabAddClient);
        lineEditEmail->setObjectName("lineEditEmail");

        layoutForm->addWidget(lineEditEmail, 7, 1, 1, 1);

        layoutButtonsForm = new QHBoxLayout();
        layoutButtonsForm->setObjectName("layoutButtonsForm");
        btnSave = new QPushButton(tabAddClient);
        btnSave->setObjectName("btnSave");

        layoutButtonsForm->addWidget(btnSave);

        btnCancel = new QPushButton(tabAddClient);
        btnCancel->setObjectName("btnCancel");

        layoutButtonsForm->addWidget(btnCancel);


        layoutForm->addLayout(layoutButtonsForm, 8, 0, 1, 2);

        tabWidgetMain->addTab(tabAddClient, QString());
        tabStats = new QWidget();
        tabStats->setObjectName("tabStats");
        layoutStats = new QVBoxLayout(tabStats);
        layoutStats->setObjectName("layoutStats");
        labelStatsTitle = new QLabel(tabStats);
        labelStatsTitle->setObjectName("labelStatsTitle");

        layoutStats->addWidget(labelStatsTitle);

        labelStatsContent = new QLabel(tabStats);
        labelStatsContent->setObjectName("labelStatsContent");

        layoutStats->addWidget(labelStatsContent);

        tabWidgetMain->addTab(tabStats, QString());

        contentAreaLayout->addWidget(tabWidgetMain);


        mainLayoutRoot->addLayout(contentAreaLayout);

        GestionClients->setCentralWidget(centralwidget);

        retranslateUi(GestionClients);

        tabWidgetMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GestionClients);
    } // setupUi

    void retranslateUi(QMainWindow *GestionClients)
    {
        GestionClients->setWindowTitle(QCoreApplication::translate("GestionClients", "Gestion de Clients", nullptr));
        sidebarHeader->setText(QCoreApplication::translate("GestionClients", "\360\237\223\212 Tableau de board", nullptr));
        btnClients->setText(QCoreApplication::translate("GestionClients", "\360\237\247\215 Clients", nullptr));
        btnProduit->setText(QCoreApplication::translate("GestionClients", "\360\237\223\246 Produits", nullptr));
        btnVentes->setText(QCoreApplication::translate("GestionClients", "\360\237\222\270 Ventes", nullptr));
        btnEmployes->setText(QCoreApplication::translate("GestionClients", "\360\237\221\224 Employ\303\251s", nullptr));
        btnDashboard->setText(QCoreApplication::translate("GestionClients", "\360\237\223\212 Dashboard", nullptr));
        mainTitle->setText(QCoreApplication::translate("GestionClients", "Gestion de Clients", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("GestionClients", "\360\237\224\215 Recherche par Nom, ID ou T\303\251l\303\251phone...", nullptr));
        labelFilter->setText(QCoreApplication::translate("GestionClients", "Filtrer :", nullptr));
        comboBoxTri->setItemText(0, QCoreApplication::translate("GestionClients", "Nom A-Z", nullptr));
        comboBoxTri->setItemText(1, QCoreApplication::translate("GestionClients", "Nom Z-A", nullptr));
        comboBoxTri->setItemText(2, QCoreApplication::translate("GestionClients", "Date Inscription \342\206\221", nullptr));
        comboBoxTri->setItemText(3, QCoreApplication::translate("GestionClients", "Date Inscription \342\206\223", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidgetClients->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GestionClients", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetClients->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GestionClients", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetClients->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GestionClients", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetClients->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GestionClients", "Date Naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetClients->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GestionClients", "Sexe", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetClients->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GestionClients", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetClients->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GestionClients", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetClients->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GestionClients", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetClients->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("GestionClients", "Date Inscription", nullptr));
        btnExport->setText(QCoreApplication::translate("GestionClients", "\360\237\223\244 Exporter PDF", nullptr));
        btnDelete->setText(QCoreApplication::translate("GestionClients", "\360\237\227\221\357\270\217 Supprimer Client", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabListeClients), QCoreApplication::translate("GestionClients", "Liste Clients", nullptr));
        labelID->setText(QCoreApplication::translate("GestionClients", "ID :", nullptr));
        labelNom->setText(QCoreApplication::translate("GestionClients", "Nom :", nullptr));
        labelPrenom->setText(QCoreApplication::translate("GestionClients", "Pr\303\251nom :", nullptr));
        labelDateNaissance->setText(QCoreApplication::translate("GestionClients", "Date Naissance :", nullptr));
        labelSexe->setText(QCoreApplication::translate("GestionClients", "Sexe :", nullptr));
        comboBoxSexe->setItemText(0, QCoreApplication::translate("GestionClients", "Homme", nullptr));
        comboBoxSexe->setItemText(1, QCoreApplication::translate("GestionClients", "Femme", nullptr));

        labelAdresse->setText(QCoreApplication::translate("GestionClients", "Adresse :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("GestionClients", "T\303\251l\303\251phone :", nullptr));
        labelEmail->setText(QCoreApplication::translate("GestionClients", "Email", nullptr));
        btnSave->setText(QCoreApplication::translate("GestionClients", "\360\237\222\276 Enregistrer", nullptr));
        btnCancel->setText(QCoreApplication::translate("GestionClients", "\342\235\214 Annuler", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabAddClient), QCoreApplication::translate("GestionClients", "Ajouter / Modifier", nullptr));
        labelStatsTitle->setText(QCoreApplication::translate("GestionClients", "\360\237\223\212 Statistiques Clients", nullptr));
        labelStatsContent->setText(QCoreApplication::translate("GestionClients", "Graphiques et donn\303\251es statistiques ici...", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabStats), QCoreApplication::translate("GestionClients", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionClients: public Ui_GestionClients {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCLIENT1_H
