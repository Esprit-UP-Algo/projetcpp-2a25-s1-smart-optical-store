#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_register_clicked();
    void on_pushButton_forgot_password_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
