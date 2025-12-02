#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
Arduino::Arduino(QObject *parent) : QObject(parent)
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial = new QSerialPort(this);
    qDebug() << "========================================";
    qDebug() << "Arduino object created";
    qDebug() << "========================================";
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

bool Arduino::is_available()
{
    return arduino_is_available;
}

QString Arduino::get_connection_status()
{
    if (arduino_is_available && serial && serial->isOpen()) {
        return QString("Connected to %1 at 9600 baud").arg(arduino_port_name);
    } else if (arduino_is_available) {
        return QString("Arduino detected on %1 but not connected").arg(arduino_port_name);
    } else {
        return "No Arduino detected";
    }
}

QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    // Recherche du port sur lequel la carte arduino identifiée par arduino_uno_vendor_id
    // est connectée
    serialbuffer = "";

    qDebug() << "========================================";
    qDebug() << "Starting Arduino connection process...";
    qDebug() << "========================================";
    qDebug() << "Scanning for available serial ports...";

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        qDebug() << "Port:" << serial_port_info.portName()
        << "Description:" << serial_port_info.description()
        << "Manufacturer:" << serial_port_info.manufacturer();

        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            qDebug() << "  Vendor ID:" << QString::number(serial_port_info.vendorIdentifier(), 16)
            << "Product ID:" << QString::number(serial_port_info.productIdentifier(), 16);

            // Check for Arduino Uno
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "  >> Arduino Uno detected!";
            }
            // Check for other common Arduino boards (CH340 chip)
            else if (serial_port_info.vendorIdentifier() == 0x1a86) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "  >> Arduino with CH340 chip detected!";
            }
            // Check for FTDI-based Arduinos
            else if (serial_port_info.vendorIdentifier() == 0x0403) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "  >> Arduino with FTDI chip detected!";
            }
            // Generic Arduino detection by description
            else if (serial_port_info.description().contains("Arduino", Qt::CaseInsensitive) ||
                     serial_port_info.manufacturer().contains("Arduino", Qt::CaseInsensitive)) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "  >> Arduino detected by description!";
            }
        }
    }

    if (arduino_port_name.isEmpty()) {
        qDebug() << "========================================";
        qDebug() << "CONNECTION FAILED: No Arduino detected";
        qDebug() << "========================================";
        qDebug() << "Troubleshooting steps:";
        qDebug() << "1. Ensure Arduino is connected to USB port";
        qDebug() << "2. Install USB drivers (CH340/FTDI if needed)";
        qDebug() << "3. Check Device Manager for COM ports";
        qDebug() << "4. Close other programs using the serial port";
        qDebug() << "========================================";
        return -1;
    }

    qDebug() << "========================================";
    qDebug() << "Arduino DETECTED on port:" << arduino_port_name;
    qDebug() << "========================================";

    if (arduino_is_available){
        // Configuration de la communication (débit...)
        qDebug() << "Attempting to open serial port...";
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
            serial->setDataBits(QSerialPort::Data8); // Longueur des données : 8 bits,
            serial->setParity(QSerialPort::NoParity); // 1 bit de parité optionnel
            serial->setStopBits(QSerialPort::OneStop); // Nombre de bits de stop : 1
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "========================================";
            qDebug() << "CONNECTION SUCCESS!";
            qDebug() << "========================================";
            qDebug() << "Port:" << arduino_port_name;
            qDebug() << "Baud Rate: 9600";
            qDebug() << "Data Bits: 8";
            qDebug() << "Parity: None";
            qDebug() << "Stop Bits: 1";
            qDebug() << "Flow Control: None";
            qDebug() << "========================================";
            qDebug() << "Arduino is ready for communication!";
            qDebug() << "========================================";
            return 0;
        } else {
            qDebug() << "========================================";
            qDebug() << "CONNECTION FAILED: Could not open port";
            qDebug() << "Error:" << serial->errorString();
            qDebug() << "========================================";
            qDebug() << "Possible reasons:";
            qDebug() << "1. Port is already in use by another application";
            qDebug() << "2. Permission denied (try running as administrator)";
            qDebug() << "3. Arduino is not responding";
            qDebug() << "========================================";
        }
        return 1;
    }
    return -1;
}


int Arduino::close_arduino()
{
    if(serial && serial->isOpen()){
        qDebug() << "========================================";
        qDebug() << "Closing Arduino connection on port:" << arduino_port_name;
        serial->close();
        qDebug() << "Arduino connection closed successfully";
        qDebug() << "========================================";
        return 0;
    } else {
        qDebug() << "Arduino port was not open";
    }
    return 1;
}


QByteArray Arduino::read_from_arduino()
{
    if(serial && serial->isReadable()){
        serial->waitForReadyRead(10);
        data=serial->readAll();
        if (!data.isEmpty()) {
            qDebug() << "Data received from Arduino:" << data;
        }
        return data;
    } else {
        qDebug() << "Serial port is not readable";
    }
    return QByteArray();
}


QByteArray Arduino::getdata()
{
    return data;
}
int Arduino::write_to_arduino(QByteArray d)
{
    if(serial && serial->isWritable()){
        qint64 bytesWritten = serial->write(d);  // envoyer des données vers Arduino
        qDebug() << "Data sent to Arduino:" << d << "(" << bytesWritten << "bytes)";
        serial->flush();  // Ensure data is sent immediately
        return 0;
    }else{
        qDebug() << "========================================";
        qDebug() << "WRITE FAILED: Serial port not writable";
        qDebug() << "Port status:" << (serial && serial->isOpen() ? "Open" : "Closed");
        qDebug() << "========================================";
        return -1;
    }
}
