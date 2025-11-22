#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT
public:
    Arduino(QObject *parent = nullptr);
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray d);
    QByteArray read_from_arduino();
    QSerialPort *getserial();
    QString getarduino_port_name();
    QByteArray getdata();
    bool is_available();
    QString get_connection_status();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 0x2341;
    static const quint16 arduino_uno_producy_id = 0x0043;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
    QString serialbuffer;
};

#endif // ARDUINO_H
