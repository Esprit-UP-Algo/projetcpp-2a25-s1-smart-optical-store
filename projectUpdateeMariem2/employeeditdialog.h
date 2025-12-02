#ifndef EMPLOYEEDITDIALOG_H
#define EMPLOYEEDITDIALOG_H

#include <QDialog>
#include <QDate>

class QLineEdit;
class QDateEdit;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class Employe;

class EmployeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeEditDialog(const Employe &employe, QWidget *parent = nullptr);

    QString nom() const;
    QString prenom() const;
    QString email() const;
    QString telephone() const;
    QDate dateNaissance() const;
    QString adresse() const;
    QString poste() const;
    double salaire() const;
    int nombreEnfants() const;
    QString disponibilite() const;

private:
    QLineEdit *m_nomEdit;
    QLineEdit *m_prenomEdit;
    QLineEdit *m_emailEdit;
    QLineEdit *m_telephoneEdit;
    QDateEdit *m_dateEdit;
    QLineEdit *m_adresseEdit;
    QLineEdit *m_posteEdit;
    QDoubleSpinBox *m_salaireSpin;
    QSpinBox *m_enfantsSpin;
    QComboBox *m_disponibiliteCombo;
};

#endif // EMPLOYEEDITDIALOG_H
