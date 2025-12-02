#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <QObject>
#include <QSslSocket>

class SmtpClient : public QObject
{
    Q_OBJECT
public:
    explicit SmtpClient(const QString &host,
                        quint16 port,
                        const QString &user,
                        const QString &password,
                        QObject *parent = nullptr);

    bool sendMail(const QString &from,
                  const QString &to,
                  const QString &subject,
                  const QString &body,
                  QString *errorOut = nullptr,
                  bool isHtml = false);

private:
    QString m_host;
    quint16 m_port;
    QString m_user;
    QString m_password;
};

#endif // SMTPCLIENT_H



