QT += widgets sql charts serialport
CONFIG += c++17
TEMPLATE = app
QT += network
QT += core gui widgets
QT += charts
QT += core gui sql charts printsupport
# Target
TARGET = gestionemploye0

# Sources
SOURCES += \
    Connection.cpp \
    WindowManager.cpp \
    arduino.cpp \
    main.cpp \
    login.cpp \
    smtp.cpp \
    tab.cpp \
    gestionemploye00.cpp \
    statistique.cpp \
    salesstatistique.cpp \
    exporter.cpp \
    mainwindow.cpp \
    saleswindow.cpp \
    gclient1.cpp \
    dashboardwindow.cpp \
    fournisseurwindow.cpp \
    # Model classes
    client.cpp \
    produit.cpp \
    vente.cpp \
    employe.cpp \
    fournisseur.cpp \
    employeeditdialog.cpp

# Headers
HEADERS += \
    Connection.h \
    WindowManager.h \
    arduino.h \
    login.h \
    smtp.h \
    tab.h \
    gestionemploye00.h \
    statistique.h \
    salesstatistique.h \
    exporter.h \
    mainwindow.h \
    saleswindow.h \
    gclient1.h \
    dashboardwindow.h \
    fournisseurwindow.h \
    # Model classes
    client.h \
    produit.h \
    vente.h \
    employe.h \
    fournisseur.h \
    employeeditdialog.h

# Forms (UI)
FORMS += \
    login.ui \
    tab.ui \
    gestionemploye00.ui \
    statistique.ui \
    salesstatistique.ui \
    exporter.ui \
    mainwindow.ui \
    saleswindow.ui \
    gclient1.ui \
    dashboardwindow.ui \
    fournisseurwindow.ui

# Resources
RESOURCES += resources.qrc

# Include path (if any extra include dirs are needed)
INCLUDEPATH += .

# Windows: copy images if needed (qrc already embeds images)
