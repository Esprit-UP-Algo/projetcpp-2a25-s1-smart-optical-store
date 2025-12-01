/********************************************************************************
** Form generated from reading UI file 'salesstatistique.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALESSTATISTIQUE_H
#define UI_SALESSTATISTIQUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalesStatistique
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshButton;
    QHBoxLayout *topRowLayout;
    QGroupBox *totalSalesGroupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *totalSalesLabel;
    QLabel *totalSalesSubtitleLabel;
    QGroupBox *totalRevenueGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *totalRevenueLabel;
    QLabel *totalRevenueSubtitleLabel;
    QGroupBox *avgSaleGroupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *avgSaleLabel;
    QLabel *avgSaleSubtitleLabel;
    QHBoxLayout *middleRowLayout;
    QGroupBox *salesTodayGroupBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *salesTodayLabel;
    QLabel *salesTodaySubtitleLabel;
    QGroupBox *revenueTodayGroupBox;
    QVBoxLayout *verticalLayout_6;
    QLabel *revenueTodayLabel;
    QLabel *revenueTodaySubtitleLabel;
    QGroupBox *completedGroupBox;
    QVBoxLayout *verticalLayout_7;
    QLabel *completedLabel;
    QLabel *completedSubtitleLabel;
    QHBoxLayout *bottomRowLayout;
    QGroupBox *paymentMethodsGroupBox;
    QVBoxLayout *verticalLayout_8;
    QWidget *paymentChartWidget;
    QTextEdit *paymentMethodsText;
    QGroupBox *topClientsGroupBox;
    QVBoxLayout *verticalLayout_9;
    QWidget *clientsChartWidget;
    QTextEdit *topClientsText;
    QGroupBox *statusGroupBox;
    QVBoxLayout *verticalLayout_10;
    QWidget *statusChartWidget;
    QTextEdit *statusText;
    QPushButton *exportButton;

    void setupUi(QDialog *SalesStatistique)
    {
        if (SalesStatistique->objectName().isEmpty())
            SalesStatistique->setObjectName("SalesStatistique");
        SalesStatistique->resize(1200, 800);
        SalesStatistique->setStyleSheet(QString::fromUtf8("background-color: #b8e2f2;"));
        verticalLayout = new QVBoxLayout(SalesStatistique);
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(SalesStatistique);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        titleLabel->setFont(font);

        headerLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        refreshButton = new QPushButton(SalesStatistique);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;\n"
"padding: 8px 16px;\n"
"border-radius: 5px;"));

        headerLayout->addWidget(refreshButton);


        verticalLayout->addLayout(headerLayout);

        topRowLayout = new QHBoxLayout();
        topRowLayout->setObjectName("topRowLayout");
        totalSalesGroupBox = new QGroupBox(SalesStatistique);
        totalSalesGroupBox->setObjectName("totalSalesGroupBox");
        totalSalesGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(totalSalesGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        totalSalesLabel = new QLabel(totalSalesGroupBox);
        totalSalesLabel->setObjectName("totalSalesLabel");
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        totalSalesLabel->setFont(font1);
        totalSalesLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(totalSalesLabel);

        totalSalesSubtitleLabel = new QLabel(totalSalesGroupBox);
        totalSalesSubtitleLabel->setObjectName("totalSalesSubtitleLabel");
        totalSalesSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(totalSalesSubtitleLabel);


        topRowLayout->addWidget(totalSalesGroupBox);

        totalRevenueGroupBox = new QGroupBox(SalesStatistique);
        totalRevenueGroupBox->setObjectName("totalRevenueGroupBox");
        totalRevenueGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(totalRevenueGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        totalRevenueLabel = new QLabel(totalRevenueGroupBox);
        totalRevenueLabel->setObjectName("totalRevenueLabel");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        totalRevenueLabel->setFont(font2);
        totalRevenueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(totalRevenueLabel);

        totalRevenueSubtitleLabel = new QLabel(totalRevenueGroupBox);
        totalRevenueSubtitleLabel->setObjectName("totalRevenueSubtitleLabel");
        totalRevenueSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(totalRevenueSubtitleLabel);


        topRowLayout->addWidget(totalRevenueGroupBox);

        avgSaleGroupBox = new QGroupBox(SalesStatistique);
        avgSaleGroupBox->setObjectName("avgSaleGroupBox");
        avgSaleGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(avgSaleGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        avgSaleLabel = new QLabel(avgSaleGroupBox);
        avgSaleLabel->setObjectName("avgSaleLabel");
        avgSaleLabel->setFont(font2);
        avgSaleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(avgSaleLabel);

        avgSaleSubtitleLabel = new QLabel(avgSaleGroupBox);
        avgSaleSubtitleLabel->setObjectName("avgSaleSubtitleLabel");
        avgSaleSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(avgSaleSubtitleLabel);


        topRowLayout->addWidget(avgSaleGroupBox);


        verticalLayout->addLayout(topRowLayout);

        middleRowLayout = new QHBoxLayout();
        middleRowLayout->setObjectName("middleRowLayout");
        salesTodayGroupBox = new QGroupBox(SalesStatistique);
        salesTodayGroupBox->setObjectName("salesTodayGroupBox");
        salesTodayGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(salesTodayGroupBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        salesTodayLabel = new QLabel(salesTodayGroupBox);
        salesTodayLabel->setObjectName("salesTodayLabel");
        salesTodayLabel->setFont(font1);
        salesTodayLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(salesTodayLabel);

        salesTodaySubtitleLabel = new QLabel(salesTodayGroupBox);
        salesTodaySubtitleLabel->setObjectName("salesTodaySubtitleLabel");
        salesTodaySubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(salesTodaySubtitleLabel);


        middleRowLayout->addWidget(salesTodayGroupBox);

        revenueTodayGroupBox = new QGroupBox(SalesStatistique);
        revenueTodayGroupBox->setObjectName("revenueTodayGroupBox");
        revenueTodayGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(revenueTodayGroupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        revenueTodayLabel = new QLabel(revenueTodayGroupBox);
        revenueTodayLabel->setObjectName("revenueTodayLabel");
        revenueTodayLabel->setFont(font2);
        revenueTodayLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(revenueTodayLabel);

        revenueTodaySubtitleLabel = new QLabel(revenueTodayGroupBox);
        revenueTodaySubtitleLabel->setObjectName("revenueTodaySubtitleLabel");
        revenueTodaySubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(revenueTodaySubtitleLabel);


        middleRowLayout->addWidget(revenueTodayGroupBox);

        completedGroupBox = new QGroupBox(SalesStatistique);
        completedGroupBox->setObjectName("completedGroupBox");
        completedGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(completedGroupBox);
        verticalLayout_7->setObjectName("verticalLayout_7");
        completedLabel = new QLabel(completedGroupBox);
        completedLabel->setObjectName("completedLabel");
        completedLabel->setFont(font1);
        completedLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(completedLabel);

        completedSubtitleLabel = new QLabel(completedGroupBox);
        completedSubtitleLabel->setObjectName("completedSubtitleLabel");
        completedSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(completedSubtitleLabel);


        middleRowLayout->addWidget(completedGroupBox);


        verticalLayout->addLayout(middleRowLayout);

        bottomRowLayout = new QHBoxLayout();
        bottomRowLayout->setObjectName("bottomRowLayout");
        paymentMethodsGroupBox = new QGroupBox(SalesStatistique);
        paymentMethodsGroupBox->setObjectName("paymentMethodsGroupBox");
        paymentMethodsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(paymentMethodsGroupBox);
        verticalLayout_8->setObjectName("verticalLayout_8");
        paymentChartWidget = new QWidget(paymentMethodsGroupBox);
        paymentChartWidget->setObjectName("paymentChartWidget");
        paymentChartWidget->setMinimumSize(QSize(200, 150));
        paymentChartWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_8->addWidget(paymentChartWidget);

        paymentMethodsText = new QTextEdit(paymentMethodsGroupBox);
        paymentMethodsText->setObjectName("paymentMethodsText");
        paymentMethodsText->setReadOnly(true);
        paymentMethodsText->setMaximumSize(QSize(16777215, 50));
        paymentMethodsText->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_8->addWidget(paymentMethodsText);


        bottomRowLayout->addWidget(paymentMethodsGroupBox);

        topClientsGroupBox = new QGroupBox(SalesStatistique);
        topClientsGroupBox->setObjectName("topClientsGroupBox");
        topClientsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_9 = new QVBoxLayout(topClientsGroupBox);
        verticalLayout_9->setObjectName("verticalLayout_9");
        clientsChartWidget = new QWidget(topClientsGroupBox);
        clientsChartWidget->setObjectName("clientsChartWidget");
        clientsChartWidget->setMinimumSize(QSize(200, 150));
        clientsChartWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_9->addWidget(clientsChartWidget);

        topClientsText = new QTextEdit(topClientsGroupBox);
        topClientsText->setObjectName("topClientsText");
        topClientsText->setReadOnly(true);
        topClientsText->setMaximumSize(QSize(16777215, 50));
        topClientsText->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_9->addWidget(topClientsText);


        bottomRowLayout->addWidget(topClientsGroupBox);

        statusGroupBox = new QGroupBox(SalesStatistique);
        statusGroupBox->setObjectName("statusGroupBox");
        statusGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_10 = new QVBoxLayout(statusGroupBox);
        verticalLayout_10->setObjectName("verticalLayout_10");
        statusChartWidget = new QWidget(statusGroupBox);
        statusChartWidget->setObjectName("statusChartWidget");
        statusChartWidget->setMinimumSize(QSize(200, 150));
        statusChartWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_10->addWidget(statusChartWidget);

        statusText = new QTextEdit(statusGroupBox);
        statusText->setObjectName("statusText");
        statusText->setReadOnly(true);
        statusText->setMaximumSize(QSize(16777215, 50));
        statusText->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_10->addWidget(statusText);


        bottomRowLayout->addWidget(statusGroupBox);


        verticalLayout->addLayout(bottomRowLayout);

        exportButton = new QPushButton(SalesStatistique);
        exportButton->setObjectName("exportButton");
        exportButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;\n"
"padding: 10px 20px;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));

        verticalLayout->addWidget(exportButton);


        retranslateUi(SalesStatistique);

        QMetaObject::connectSlotsByName(SalesStatistique);
    } // setupUi

    void retranslateUi(QDialog *SalesStatistique)
    {
        SalesStatistique->setWindowTitle(QCoreApplication::translate("SalesStatistique", "Statistiques des ventes", nullptr));
        titleLabel->setText(QCoreApplication::translate("SalesStatistique", "Statistiques des ventes", nullptr));
        refreshButton->setText(QCoreApplication::translate("SalesStatistique", "Rafra\303\256chir", nullptr));
        totalSalesGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "TOTAL VENTES", nullptr));
        totalSalesLabel->setText(QCoreApplication::translate("SalesStatistique", "0", nullptr));
        totalSalesSubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Nombre total de ventes", nullptr));
        totalRevenueGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "REVENU TOTAL", nullptr));
        totalRevenueLabel->setText(QCoreApplication::translate("SalesStatistique", "0.00 DT", nullptr));
        totalRevenueSubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Chiffre d'affaires total", nullptr));
        avgSaleGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "VENTE MOYENNE", nullptr));
        avgSaleLabel->setText(QCoreApplication::translate("SalesStatistique", "0.00 DT", nullptr));
        avgSaleSubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Montant moyen par vente", nullptr));
        salesTodayGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "VENTES AUJOURD'HUI", nullptr));
        salesTodayLabel->setText(QCoreApplication::translate("SalesStatistique", "0", nullptr));
        salesTodaySubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Nombre de ventes aujourd'hui", nullptr));
        revenueTodayGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "REVENU AUJOURD'HUI", nullptr));
        revenueTodayLabel->setText(QCoreApplication::translate("SalesStatistique", "0.00 DT", nullptr));
        revenueTodaySubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Chiffre d'affaires du jour", nullptr));
        completedGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "VENTES COMPL\303\211T\303\211ES", nullptr));
        completedLabel->setText(QCoreApplication::translate("SalesStatistique", "0", nullptr));
        completedSubtitleLabel->setText(QCoreApplication::translate("SalesStatistique", "Ventes finalis\303\251es", nullptr));
        paymentMethodsGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "Ventes de la semaine", nullptr));
        topClientsGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "Top 5 clients", nullptr));
        statusGroupBox->setTitle(QCoreApplication::translate("SalesStatistique", "Statut des ventes", nullptr));
        exportButton->setText(QCoreApplication::translate("SalesStatistique", "Exporter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SalesStatistique: public Ui_SalesStatistique {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALESSTATISTIQUE_H
