QT += widgets sql
CONFIG += c++17
TEMPLATE = app

# Target
TARGET = gestionemploye0

# Sources
SOURCES += \
    Connection.cpp \
    WindowManager.cpp \
    main.cpp \
    login.cpp \
    tab.cpp \
    gestionemploye00.cpp \
    statistique.cpp \
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
    login.h \
    tab.h \
    gestionemploye00.h \
    statistique.h \
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
