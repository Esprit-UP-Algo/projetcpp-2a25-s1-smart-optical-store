#include "smtpclient.h"
#include <QDebug>

SmtpClient::SmtpClient(const QString &host,
                       quint16 port,
                       const QString &user,
                       const QString &password,
                       QObject *parent)
    : QObject(parent),
    m_host(host),
    m_port(port),
    m_user(user),
    m_password(password)
{
}

bool SmtpClient::sendMail(const QString &from,
                          const QString &to,
                          const QString &subject,
                          const QString &body,
                          QString *errorOut,
                          bool isHtml)
{
    QSslSocket socket;
    socket.connectToHostEncrypted(m_host, m_port);
    if (!socket.waitForEncrypted(10000)) {
        if (errorOut) *errorOut = "SSL Connection failed: " + socket.errorString();
        qDebug() << "SSL Connection error:" << socket.errorString();
        return false;
    }

    qDebug() << "Connected to SMTP server";

    auto sendLine = [&](const QString &line, bool checkResponse = true) -> bool {
        socket.write((line + "\r\n").toUtf8());
        socket.flush();
        if (!socket.waitForReadyRead(10000)) {
            if (errorOut) *errorOut = "Timeout waiting for server response";
            return false;
        }
        QByteArray response = socket.readAll();
        qDebug() << "S:" << line;
        qDebug() << "R:" << response;

        // Check for error responses (5xx codes)
        if (checkResponse && response.startsWith("5")) {
            if (errorOut) *errorOut = "SMTP Error: " + QString::fromUtf8(response);
            return false;
        }
        return true;
    };

    if (!sendLine("EHLO localhost")) return false;
    if (!sendLine("AUTH LOGIN")) return false;
    if (!sendLine(m_user.toUtf8().toBase64())) {
        if (errorOut && errorOut->contains("535")) {
            *errorOut = "Authentication failed. Check your email and app password.";
        }
        return false;
    }
    if (!sendLine(m_password.toUtf8().toBase64())) {
        if (errorOut && errorOut->contains("535")) {
            *errorOut = "Authentication failed. Check your app password.";
        }
        return false;
    }

    // Extract email from "Name <email>" format if present for MAIL FROM
    QString fromEmail = from;
    if (from.contains("<") && from.contains(">")) {
        int start = from.indexOf("<") + 1;
        int end = from.indexOf(">");
        fromEmail = from.mid(start, end - start);
    }

    if (!sendLine("MAIL FROM:<" + fromEmail + ">")) return false;
    if (!sendLine("RCPT TO:<" + to + ">")) return false;
    if (!sendLine("DATA")) return false;

    QString contentType = isHtml ? "text/html" : "text/plain";

    QString data =
        "From: " + from + "\r\n"
                          "To: <" + to + ">\r\n"
               "Subject: " + subject + "\r\n"
                    "MIME-Version: 1.0\r\n"
                    "Content-Type: " + contentType + "; charset=\"utf-8\"\r\n"
                        "\r\n" +
        body + "\r\n.\r\n";

    socket.write(data.toUtf8());
    socket.flush();
    socket.waitForReadyRead(10000);
    QByteArray finalResponse = socket.readAll();
    qDebug() << "Final response:" << finalResponse;

    sendLine("QUIT", false);
    socket.disconnectFromHost();

    qDebug() << "Email sent successfully";
    return true;
}



