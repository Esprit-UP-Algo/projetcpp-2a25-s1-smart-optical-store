/********************************************************************************
** Form generated from reading UI file 'exporter.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTER_H
#define UI_EXPORTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Exporter
{
public:
    QLabel *label;

    void setupUi(QDialog *Exporter)
    {
        if (Exporter->objectName().isEmpty())
            Exporter->setObjectName("Exporter");
        Exporter->resize(905, 579);
        label = new QLabel(Exporter);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 90, 63, 20));

        retranslateUi(Exporter);

        QMetaObject::connectSlotsByName(Exporter);
    } // setupUi

    void retranslateUi(QDialog *Exporter)
    {
        Exporter->setWindowTitle(QCoreApplication::translate("Exporter", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Exporter", "Exporter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exporter: public Ui_Exporter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTER_H
