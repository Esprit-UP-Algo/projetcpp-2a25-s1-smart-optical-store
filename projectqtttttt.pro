QT += widgets sql serialport charts printsupport network
CONFIG += c++17
TEMPLATE = app

# Target
TARGET = gestionemploye0

# Sources
SOURCES += \
    Connection.cpp \
    WindowManager.cpp \
    arduino.cpp \
    main.cpp \
    login.cpp \
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
    employeeditdialog.cpp \
    employeeregister.cpp \
    forgotpassword.cpp \
    promomanager.cpp \
    smtpclient.cpp \
    smtp.cpp

# Headers
HEADERS += \
    Connection.h \
    WindowManager.h \
    arduino.h \
    login.h \
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
    employeeditdialog.h \
    employeeregister.h \
    forgotpassword.h \
    promomanager.h \
    smtpclient.h \
    smtp.h

# Forms (UI)
FORMS += \
    login.ui \
    gestionemploye00.ui \
    statistique.ui \
    salesstatistique.ui \
    exporter.ui \
    mainwindow.ui \
    saleswindow.ui \
    gclient1.ui \
    dashboardwindow.ui \
    fournisseurwindow.ui \
    employeeregister.ui \
    forgotpassword.ui \
    promomanager.ui

# Resources
RESOURCES += resources.qrc

# Include path (if any extra include dirs are needed)
INCLUDEPATH += .

# Windows: copy images if needed (qrc already embeds images)