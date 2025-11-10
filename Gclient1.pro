QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gclient1
TEMPLATE = app

SOURCES += \
    connexion.cpp \
    main.cpp \
    gclient1.cpp

HEADERS += \
    connexion.h \
    gclient1.h

FORMS += \
    gclient1.ui
