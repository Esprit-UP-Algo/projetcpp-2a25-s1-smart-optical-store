/********************************************************************************
** Form generated from reading UI file 'promomanager.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMOMANAGER_H
#define UI_PROMOMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PromoManager
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QGroupBox *formGroupBox;
    QGridLayout *gridLayout;
    QLabel *codeLabel;
    QLineEdit *codeLineEdit;
    QPushButton *generateCodeButton;
    QLabel *descriptionLabel;
    QLineEdit *descriptionLineEdit;
    QLabel *discountLabel;
    QDoubleSpinBox *discountSpinBox;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;
    QLabel *endDateLabel;
    QDateEdit *endDateEdit;
    QLabel *activeLabel;
    QCheckBox *activeCheckBox;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QGroupBox *listGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTableView *promoTableView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PromoManager)
    {
        if (PromoManager->objectName().isEmpty())
            PromoManager->setObjectName("PromoManager");
        PromoManager->resize(800, 600);
        PromoManager->setStyleSheet(QString::fromUtf8("background-color: #b8e2f2; color: black;"));
        verticalLayout = new QVBoxLayout(PromoManager);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(PromoManager);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("color: rgb(41, 102, 148);"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        formGroupBox = new QGroupBox(PromoManager);
        formGroupBox->setObjectName("formGroupBox");
        formGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    margin-top: 20px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 2px 10px;\n"
"}"));
        gridLayout = new QGridLayout(formGroupBox);
        gridLayout->setObjectName("gridLayout");
        codeLabel = new QLabel(formGroupBox);
        codeLabel->setObjectName("codeLabel");
        codeLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(codeLabel, 0, 0, 1, 1);

        codeLineEdit = new QLineEdit(formGroupBox);
        codeLineEdit->setObjectName("codeLineEdit");
        codeLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));

        gridLayout->addWidget(codeLineEdit, 0, 1, 1, 1);

        generateCodeButton = new QPushButton(formGroupBox);
        generateCodeButton->setObjectName("generateCodeButton");
        generateCodeButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(generateCodeButton, 0, 2, 1, 1);

        descriptionLabel = new QLabel(formGroupBox);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(descriptionLabel, 1, 0, 1, 1);

        descriptionLineEdit = new QLineEdit(formGroupBox);
        descriptionLineEdit->setObjectName("descriptionLineEdit");
        descriptionLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));

        gridLayout->addWidget(descriptionLineEdit, 1, 1, 1, 2);

        discountLabel = new QLabel(formGroupBox);
        discountLabel->setObjectName("discountLabel");
        discountLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(discountLabel, 2, 0, 1, 1);

        discountSpinBox = new QDoubleSpinBox(formGroupBox);
        discountSpinBox->setObjectName("discountSpinBox");
        discountSpinBox->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        discountSpinBox->setDecimals(2);
        discountSpinBox->setMaximum(100.000000000000000);
        discountSpinBox->setSingleStep(1.000000000000000);

        gridLayout->addWidget(discountSpinBox, 2, 1, 1, 2);

        startDateLabel = new QLabel(formGroupBox);
        startDateLabel->setObjectName("startDateLabel");
        startDateLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(startDateLabel, 3, 0, 1, 1);

        startDateEdit = new QDateEdit(formGroupBox);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        startDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(startDateEdit, 3, 1, 1, 2);

        endDateLabel = new QLabel(formGroupBox);
        endDateLabel->setObjectName("endDateLabel");
        endDateLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(endDateLabel, 4, 0, 1, 1);

        endDateEdit = new QDateEdit(formGroupBox);
        endDateEdit->setObjectName("endDateEdit");
        endDateEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        endDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(endDateEdit, 4, 1, 1, 2);

        activeLabel = new QLabel(formGroupBox);
        activeLabel->setObjectName("activeLabel");
        activeLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(activeLabel, 5, 0, 1, 1);

        activeCheckBox = new QCheckBox(formGroupBox);
        activeCheckBox->setObjectName("activeCheckBox");
        activeCheckBox->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        activeCheckBox->setChecked(true);

        gridLayout->addWidget(activeCheckBox, 5, 1, 1, 2);


        verticalLayout->addWidget(formGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(PromoManager);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));

        buttonLayout->addWidget(addButton);

        editButton = new QPushButton(PromoManager);
        editButton->setObjectName("editButton");
        editButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));

        buttonLayout->addWidget(editButton);

        deleteButton = new QPushButton(PromoManager);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));

        buttonLayout->addWidget(deleteButton);


        verticalLayout->addLayout(buttonLayout);

        listGroupBox = new QGroupBox(PromoManager);
        listGroupBox->setObjectName("listGroupBox");
        listGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    margin-top: 20px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 2px 10px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(listGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        promoTableView = new QTableView(listGroupBox);
        promoTableView->setObjectName("promoTableView");
        promoTableView->setStyleSheet(QString::fromUtf8("background-color: white; color: black;"));
        promoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        promoTableView->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_2->addWidget(promoTableView);


        verticalLayout->addWidget(listGroupBox);

        buttonBox = new QDialogButtonBox(PromoManager);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PromoManager);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, PromoManager, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PromoManager, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PromoManager);
    } // setupUi

    void retranslateUi(QDialog *PromoManager)
    {
        PromoManager->setWindowTitle(QCoreApplication::translate("PromoManager", "Gestion des Codes Promo", nullptr));
        titleLabel->setText(QCoreApplication::translate("PromoManager", "Gestion des Codes Promotionnels", nullptr));
        formGroupBox->setTitle(QCoreApplication::translate("PromoManager", "Ajouter/Modifier Code Promo", nullptr));
        codeLabel->setText(QCoreApplication::translate("PromoManager", "Code Promo :", nullptr));
        codeLineEdit->setPlaceholderText(QCoreApplication::translate("PromoManager", "Entrer le code promo", nullptr));
        generateCodeButton->setText(QCoreApplication::translate("PromoManager", "G\303\251n\303\251rer", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("PromoManager", "Description :", nullptr));
        descriptionLineEdit->setPlaceholderText(QCoreApplication::translate("PromoManager", "Entrer une description (optionnel)", nullptr));
        discountLabel->setText(QCoreApplication::translate("PromoManager", "Remise (%) :", nullptr));
        startDateLabel->setText(QCoreApplication::translate("PromoManager", "Date D\303\251but :", nullptr));
        endDateLabel->setText(QCoreApplication::translate("PromoManager", "Date Fin :", nullptr));
        activeLabel->setText(QCoreApplication::translate("PromoManager", "Actif :", nullptr));
        activeCheckBox->setText(QCoreApplication::translate("PromoManager", "Code promo actif", nullptr));
        addButton->setText(QCoreApplication::translate("PromoManager", "Ajouter", nullptr));
        editButton->setText(QCoreApplication::translate("PromoManager", "Modifier", nullptr));
        deleteButton->setText(QCoreApplication::translate("PromoManager", "Supprimer", nullptr));
        listGroupBox->setTitle(QCoreApplication::translate("PromoManager", "Codes Promo Existants", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PromoManager: public Ui_PromoManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMOMANAGER_H
