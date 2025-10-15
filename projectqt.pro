QT += widgets
CONFIG += c++17
TEMPLATE = app

# Target
TARGET = gestionemploye0

# Sources
SOURCES += \
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
    fournisseurwindow.cpp

# Headers
HEADERS += \
    login.h \
    tab.h \
    gestionemploye00.h \
    statistique.h \
    exporter.h \
    mainwindow.h \
    saleswindow.h \
    gclient1.h \
    dashboardwindow.h \
    fournisseurwindow.h

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
