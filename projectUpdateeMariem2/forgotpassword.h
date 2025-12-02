#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>
#include "employe.h"
#include "smtpclient.h"

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

private slots:
    void on_pushButton_send_code_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::ForgotPassword *ui;

    bool createResetCode(const QString &email, QString &otpOut, QString &errorOut);
    bool verifyOtpAndChangePassword(const QString &email,
                                    const QString &otp,
                                    const QString &newPassword,
                                    QString &errorOut);
};

#endif // FORGOTPASSWORD_H
