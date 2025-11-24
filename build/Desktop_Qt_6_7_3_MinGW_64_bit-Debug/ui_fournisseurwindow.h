/********************************************************************************
** Form generated from reading UI file 'fournisseurwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOURNISSEURWINDOW_H
#define UI_FOURNISSEURWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FournisseurWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_6;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_delete;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QDateEdit *dateEdit;
    QWidget *page_2;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *logoLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FournisseurWindow)
    {
        if (FournisseurWindow->objectName().isEmpty())
            FournisseurWindow->setObjectName("FournisseurWindow");
        FournisseurWindow->resize(1299, 600);
        FournisseurWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        centralwidget = new QWidget(FournisseurWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(290, -10, 951, 591));
        page = new QWidget();
        page->setObjectName("page");
        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(260, 400, 231, 29));
        pushButton_6->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        tableWidget_2 = new QTableWidget(page);
        if (tableWidget_2->columnCount() < 8)
            tableWidget_2->setColumnCount(8);
        QFont font;
        font.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(250, 90, 701, 221));
        tableWidget_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);\n"
" QHeaderView::section { color: black; background-color: rgb(41, 102, 148); }\n"
" QTableWidget::item { color: white; }"));
        pushButton_ajouter = new QPushButton(page);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(270, 500, 171, 29));
        pushButton_ajouter->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_modifier = new QPushButton(page);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(500, 500, 151, 29));
        pushButton_modifier->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_delete = new QPushButton(page);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(720, 500, 161, 29));
        pushButton_delete->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, 20, 241, 541));
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
"}\n"
""));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 111, 20));
        label->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 90, 101, 20));
        label_6->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 150, 101, 20));
        label_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 210, 101, 20));
        label_3->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 270, 161, 31));
        label_4->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 60, 113, 28));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(10, 120, 113, 28));
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(10, 180, 113, 28));
        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(10, 240, 113, 28));
        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(10, 300, 113, 28));
        lineEdit_11 = new QLineEdit(groupBox_2);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(10, 370, 113, 28));
        lineEdit_12 = new QLineEdit(groupBox_2);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(10, 440, 113, 28));
        lineEdit_13 = new QLineEdit(groupBox_2);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(10, 370, 113, 28));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 340, 161, 31));
        label_11->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 470, 161, 31));
        label_12->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 410, 161, 31));
        label_13->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        dateEdit = new QDateEdit(groupBox_2);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(10, 500, 113, 28));
        dateEdit->setCalendarPopup(true);
        dateEdit->setDate(QDate(2024, 1, 1));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 20, 251, 521));
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
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 80, 261, 41));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 150, 261, 41));
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
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(0, 300, 261, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("#pushButton_3 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_3:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_3:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(0, 230, 261, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("#pushButton_4 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_4:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_4:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(0, 370, 261, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("#pushButton_5 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_5:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_5:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1230, 10, 60, 60));
        logoLabel->setMinimumSize(QSize(50, 50));
        logoLabel->setMaximumSize(QSize(60, 60));
        logoLabel->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        FournisseurWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FournisseurWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1299, 25));
        FournisseurWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FournisseurWindow);
        statusbar->setObjectName("statusbar");
        FournisseurWindow->setStatusBar(statusbar);

        retranslateUi(FournisseurWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FournisseurWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FournisseurWindow)
    {
        FournisseurWindow->setWindowTitle(QCoreApplication::translate("FournisseurWindow", "Gestion des Fournisseurs", nullptr));
        pushButton_6->setText(QCoreApplication::translate("FournisseurWindow", "Export format Excel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FournisseurWindow", "id_fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("FournisseurWindow", "Entreprise", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("FournisseurWindow", "Contact", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("FournisseurWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("FournisseurWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("FournisseurWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("FournisseurWindow", "Paiement", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("FournisseurWindow", "Date", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("FournisseurWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("FournisseurWindow", "modifier", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("FournisseurWindow", "delete", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FournisseurWindow", "ajouter /modifier", nullptr));
        label->setText(QCoreApplication::translate("FournisseurWindow", "id_fournisseur", nullptr));
        label_6->setText(QCoreApplication::translate("FournisseurWindow", "Entreprise", nullptr));
        label_2->setText(QCoreApplication::translate("FournisseurWindow", "Contact", nullptr));
        label_3->setText(QCoreApplication::translate("FournisseurWindow", "Email", nullptr));
        label_4->setText(QCoreApplication::translate("FournisseurWindow", "Telephone", nullptr));
        lineEdit->setText(QString());
        lineEdit_3->setText(QString());
        lineEdit_4->setText(QString());
        lineEdit_5->setText(QString());
        lineEdit_6->setText(QString());
        lineEdit_11->setText(QString());
        lineEdit_12->setText(QString());
        lineEdit_13->setText(QString());
        label_11->setText(QCoreApplication::translate("FournisseurWindow", "Type", nullptr));
        label_12->setText(QCoreApplication::translate("FournisseurWindow", "Date", nullptr));
        label_13->setText(QCoreApplication::translate("FournisseurWindow", "Paiement", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FournisseurWindow", "Tableau de bord", nullptr));
        pushButton->setText(QCoreApplication::translate("FournisseurWindow", "Stock", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FournisseurWindow", "Ventes", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FournisseurWindow", "Clients", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FournisseurWindow", "Employes", nullptr));
        pushButton_5->setText(QCoreApplication::translate("FournisseurWindow", "Fournisseur", nullptr));
        logoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FournisseurWindow: public Ui_FournisseurWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOURNISSEURWINDOW_H
