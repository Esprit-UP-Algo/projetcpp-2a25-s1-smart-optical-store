#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    int connect_arduino();
    void close_arduino();
    qint64 write_to_arduino(const QByteArray &data);

private:
    QSerialPort *serial;
};

#endif
