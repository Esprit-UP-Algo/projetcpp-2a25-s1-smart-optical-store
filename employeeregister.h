#ifndef EMPLOYEEREGISTER_H
#define EMPLOYEEREGISTER_H

#include <QDialog>
#include "employe.h"
#include <QComboBox>

namespace Ui {
class EmployeeRegister;
}

class EmployeeRegister : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeRegister(QWidget *parent = nullptr);
    ~EmployeeRegister();

private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::EmployeeRegister *ui;
};

#endif // EMPLOYEEREGISTER_H