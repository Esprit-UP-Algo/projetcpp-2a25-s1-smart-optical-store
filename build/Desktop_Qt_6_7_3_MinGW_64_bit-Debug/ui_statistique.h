/********************************************************************************
** Form generated from reading UI file 'statistique.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIQUE_H
#define UI_STATISTIQUE_H

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

class Ui_Statistique
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshButton;
    QHBoxLayout *topRowLayout;
    QGroupBox *totalGroupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *totalEmployeesLabel;
    QLabel *totalSubtitleLabel;
    QGroupBox *avgSalaryGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *avgSalaryLabel;
    QLabel *avgSalarySubtitleLabel;
    QHBoxLayout *middleRowLayout;
    QGroupBox *availableGroupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *availableLabel;
    QLabel *availableSubtitleLabel;
    QGroupBox *unavailableGroupBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *unavailableLabel;
    QLabel *unavailableSubtitleLabel;
    QHBoxLayout *bottomRowLayout;
    QGroupBox *availabilityGroupBox;
    QVBoxLayout *verticalLayout_6;
    QWidget *availabilityChartWidget;
    QTextEdit *availabilityText;
    QGroupBox *positionsGroupBox;
    QVBoxLayout *verticalLayout_7;
    QWidget *positionsChartWidget;
    QTextEdit *topPositionsText;
    QPushButton *exportButton;

    void setupUi(QDialog *Statistique)
    {
        if (Statistique->objectName().isEmpty())
            Statistique->setObjectName("Statistique");
        Statistique->resize(1000, 700);
        Statistique->setStyleSheet(QString::fromUtf8("background-color: #b8e2f2;"));
        verticalLayout = new QVBoxLayout(Statistique);
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(Statistique);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        titleLabel->setFont(font);

        headerLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        refreshButton = new QPushButton(Statistique);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;\n"
"padding: 8px 16px;\n"
"border-radius: 5px;"));

        headerLayout->addWidget(refreshButton);


        verticalLayout->addLayout(headerLayout);

        topRowLayout = new QHBoxLayout();
        topRowLayout->setObjectName("topRowLayout");
        totalGroupBox = new QGroupBox(Statistique);
        totalGroupBox->setObjectName("totalGroupBox");
        totalGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(totalGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        totalEmployeesLabel = new QLabel(totalGroupBox);
        totalEmployeesLabel->setObjectName("totalEmployeesLabel");
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        totalEmployeesLabel->setFont(font1);
        totalEmployeesLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(totalEmployeesLabel);

        totalSubtitleLabel = new QLabel(totalGroupBox);
        totalSubtitleLabel->setObjectName("totalSubtitleLabel");
        totalSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(totalSubtitleLabel);


        topRowLayout->addWidget(totalGroupBox);

        avgSalaryGroupBox = new QGroupBox(Statistique);
        avgSalaryGroupBox->setObjectName("avgSalaryGroupBox");
        avgSalaryGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(avgSalaryGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        avgSalaryLabel = new QLabel(avgSalaryGroupBox);
        avgSalaryLabel->setObjectName("avgSalaryLabel");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        avgSalaryLabel->setFont(font2);
        avgSalaryLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(avgSalaryLabel);

        avgSalarySubtitleLabel = new QLabel(avgSalaryGroupBox);
        avgSalarySubtitleLabel->setObjectName("avgSalarySubtitleLabel");
        avgSalarySubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(avgSalarySubtitleLabel);


        topRowLayout->addWidget(avgSalaryGroupBox);


        verticalLayout->addLayout(topRowLayout);

        middleRowLayout = new QHBoxLayout();
        middleRowLayout->setObjectName("middleRowLayout");
        availableGroupBox = new QGroupBox(Statistique);
        availableGroupBox->setObjectName("availableGroupBox");
        availableGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(availableGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        availableLabel = new QLabel(availableGroupBox);
        availableLabel->setObjectName("availableLabel");
        availableLabel->setFont(font1);
        availableLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(availableLabel);

        availableSubtitleLabel = new QLabel(availableGroupBox);
        availableSubtitleLabel->setObjectName("availableSubtitleLabel");
        availableSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(availableSubtitleLabel);


        middleRowLayout->addWidget(availableGroupBox);

        unavailableGroupBox = new QGroupBox(Statistique);
        unavailableGroupBox->setObjectName("unavailableGroupBox");
        unavailableGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(unavailableGroupBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        unavailableLabel = new QLabel(unavailableGroupBox);
        unavailableLabel->setObjectName("unavailableLabel");
        unavailableLabel->setFont(font1);
        unavailableLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(unavailableLabel);

        unavailableSubtitleLabel = new QLabel(unavailableGroupBox);
        unavailableSubtitleLabel->setObjectName("unavailableSubtitleLabel");
        unavailableSubtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(unavailableSubtitleLabel);


        middleRowLayout->addWidget(unavailableGroupBox);


        verticalLayout->addLayout(middleRowLayout);

        bottomRowLayout = new QHBoxLayout();
        bottomRowLayout->setObjectName("bottomRowLayout");
        availabilityGroupBox = new QGroupBox(Statistique);
        availabilityGroupBox->setObjectName("availabilityGroupBox");
        availabilityGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(availabilityGroupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        availabilityChartWidget = new QWidget(availabilityGroupBox);
        availabilityChartWidget->setObjectName("availabilityChartWidget");
        availabilityChartWidget->setMinimumSize(QSize(200, 150));
        availabilityChartWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_6->addWidget(availabilityChartWidget);

        availabilityText = new QTextEdit(availabilityGroupBox);
        availabilityText->setObjectName("availabilityText");
        availabilityText->setReadOnly(true);
        availabilityText->setMaximumSize(QSize(16777215, 50));
        availabilityText->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_6->addWidget(availabilityText);


        bottomRowLayout->addWidget(availabilityGroupBox);

        positionsGroupBox = new QGroupBox(Statistique);
        positionsGroupBox->setObjectName("positionsGroupBox");
        positionsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #87CEEB;\n"
"    border: 2px solid rgb(41, 102, 148);\n"
"    border-radius: 10px;\n"
"    padding: 15px;\n"
"}\n"
"QLabel {\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(positionsGroupBox);
        verticalLayout_7->setObjectName("verticalLayout_7");
        positionsChartWidget = new QWidget(positionsGroupBox);
        positionsChartWidget->setObjectName("positionsChartWidget");
        positionsChartWidget->setMinimumSize(QSize(200, 150));
        positionsChartWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_7->addWidget(positionsChartWidget);

        topPositionsText = new QTextEdit(positionsGroupBox);
        topPositionsText->setObjectName("topPositionsText");
        topPositionsText->setReadOnly(true);
        topPositionsText->setMaximumSize(QSize(16777215, 50));
        topPositionsText->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid rgb(41, 102, 148);\n"
"border-radius: 5px;"));

        verticalLayout_7->addWidget(topPositionsText);


        bottomRowLayout->addWidget(positionsGroupBox);


        verticalLayout->addLayout(bottomRowLayout);

        exportButton = new QPushButton(Statistique);
        exportButton->setObjectName("exportButton");
        exportButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;\n"
"padding: 10px 20px;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));

        verticalLayout->addWidget(exportButton);


        retranslateUi(Statistique);

        QMetaObject::connectSlotsByName(Statistique);
    } // setupUi

    void retranslateUi(QDialog *Statistique)
    {
        Statistique->setWindowTitle(QCoreApplication::translate("Statistique", "Statistiques des employ\303\251s", nullptr));
        titleLabel->setText(QCoreApplication::translate("Statistique", "Statistiques des employ\303\251s", nullptr));
        refreshButton->setText(QCoreApplication::translate("Statistique", "Rafra\303\256chir", nullptr));
        totalGroupBox->setTitle(QCoreApplication::translate("Statistique", "TOTAL EMPLOY\303\211S", nullptr));
        totalEmployeesLabel->setText(QCoreApplication::translate("Statistique", "0", nullptr));
        totalSubtitleLabel->setText(QCoreApplication::translate("Statistique", "Nombre d'employ\303\251s enregistr\303\251s", nullptr));
        avgSalaryGroupBox->setTitle(QCoreApplication::translate("Statistique", "SALAIRE MOYEN", nullptr));
        avgSalaryLabel->setText(QCoreApplication::translate("Statistique", "0.00 DT", nullptr));
        avgSalarySubtitleLabel->setText(QCoreApplication::translate("Statistique", "Moyenne actuelle des salaires", nullptr));
        availableGroupBox->setTitle(QCoreApplication::translate("Statistique", "DISPONIBLES", nullptr));
        availableLabel->setText(QCoreApplication::translate("Statistique", "0", nullptr));
        availableSubtitleLabel->setText(QCoreApplication::translate("Statistique", "Employ\303\251s marqu\303\251s comme disponibles", nullptr));
        unavailableGroupBox->setTitle(QCoreApplication::translate("Statistique", "INDISPONIBLES", nullptr));
        unavailableLabel->setText(QCoreApplication::translate("Statistique", "0", nullptr));
        unavailableSubtitleLabel->setText(QCoreApplication::translate("Statistique", "Employ\303\251s non disponibles", nullptr));
        availabilityGroupBox->setTitle(QCoreApplication::translate("Statistique", "R\303\251partition de la disponibilit\303\251", nullptr));
        positionsGroupBox->setTitle(QCoreApplication::translate("Statistique", "Top 5 des postes", nullptr));
        exportButton->setText(QCoreApplication::translate("Statistique", "Exporter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Statistique: public Ui_Statistique {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIQUE_H
