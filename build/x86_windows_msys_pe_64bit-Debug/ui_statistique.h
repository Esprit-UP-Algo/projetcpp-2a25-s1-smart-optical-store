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
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Statistique
{
public:
    QLabel *label;

    void setupUi(QDialog *Statistique)
    {
        if (Statistique->objectName().isEmpty())
            Statistique->setObjectName("Statistique");
        Statistique->resize(1096, 736);
        label = new QLabel(Statistique);
        label->setObjectName("label");
        label->setGeometry(QRect(470, 130, 111, 61));

        retranslateUi(Statistique);

        QMetaObject::connectSlotsByName(Statistique);
    } // setupUi

    void retranslateUi(QDialog *Statistique)
    {
        Statistique->setWindowTitle(QCoreApplication::translate("Statistique", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Statistique", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Statistique: public Ui_Statistique {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIQUE_H
