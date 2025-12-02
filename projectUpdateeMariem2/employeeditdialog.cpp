#include "employeeditdialog.h"

#include "employe.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

EmployeEditDialog::EmployeEditDialog(const Employe &employe, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Modifier un employé"));
    setModal(true);
    resize(400, 0);

    // Validators
    auto emailValidator = new QRegularExpressionValidator(
        QRegularExpression(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)"), this);

    m_nomEdit = new QLineEdit(employe.getNom(), this);
    m_prenomEdit = new QLineEdit(employe.getPrenom(), this);
    m_emailEdit = new QLineEdit(employe.getEmail(), this);
    m_emailEdit->setValidator(emailValidator);
    m_telephoneEdit = new QLineEdit(employe.getTelephone(), this);
    m_dateEdit = new QDateEdit(employe.getDate().isValid() ? employe.getDate() : QDate::currentDate(), this);
    m_dateEdit->setCalendarPopup(true);
    m_adresseEdit = new QLineEdit(employe.getAdresse(), this);
    m_posteEdit = new QLineEdit(employe.getPoste(), this);

    m_salaireSpin = new QDoubleSpinBox(this);
    m_salaireSpin->setRange(0.0, 1000000.0);
    m_salaireSpin->setDecimals(2);
    m_salaireSpin->setValue(employe.getSalaire());

    m_enfantsSpin = new QSpinBox(this);
    m_enfantsSpin->setRange(0, 20);
    m_enfantsSpin->setValue(employe.getNombreEnfants());

    m_disponibiliteCombo = new QComboBox(this);
    m_disponibiliteCombo->addItem(tr("Disponible (O)"), "O");
    m_disponibiliteCombo->addItem(tr("Non disponible (N)"), "N");
    const QString disp = employe.getDisponibilite().toUpper();
    int index = disp == "O" ? 0 : 1;
    m_disponibiliteCombo->setCurrentIndex(index);

    auto *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("Nom"), m_nomEdit);
    formLayout->addRow(tr("Prénom"), m_prenomEdit);
    formLayout->addRow(tr("Email"), m_emailEdit);
    formLayout->addRow(tr("Téléphone"), m_telephoneEdit);
    formLayout->addRow(tr("Date de naissance"), m_dateEdit);
    formLayout->addRow(tr("Adresse"), m_adresseEdit);
    formLayout->addRow(tr("Poste"), m_posteEdit);
    formLayout->addRow(tr("Salaire"), m_salaireSpin);
    formLayout->addRow(tr("Nombre d'enfants"), m_enfantsSpin);
    formLayout->addRow(tr("Disponibilité"), m_disponibiliteCombo);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    formLayout->addRow(buttonBox);
}

QString EmployeEditDialog::nom() const
{
    return m_nomEdit->text().trimmed();
}

QString EmployeEditDialog::prenom() const
{
    return m_prenomEdit->text().trimmed();
}

QString EmployeEditDialog::email() const
{
    return m_emailEdit->text().trimmed();
}

QString EmployeEditDialog::telephone() const
{
    return m_telephoneEdit->text().trimmed();
}

QDate EmployeEditDialog::dateNaissance() const
{
    return m_dateEdit->date();
}

QString EmployeEditDialog::adresse() const
{
    return m_adresseEdit->text().trimmed();
}

QString EmployeEditDialog::poste() const
{
    return m_posteEdit->text().trimmed();
}

double EmployeEditDialog::salaire() const
{
    return m_salaireSpin->value();
}

int EmployeEditDialog::nombreEnfants() const
{
    return m_enfantsSpin->value();
}

QString EmployeEditDialog::disponibilite() const
{
    return m_disponibiliteCombo->currentData().toString();
}
