#include "fournisseurwindow.h"
#include "ui_fournisseurwindow.h"
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "gestionemploye00.h"

// Initialize static instance pointer
FournisseurWindow* FournisseurWindow::instance = nullptr;

FournisseurWindow* FournisseurWindow::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new FournisseurWindow(parent);
        instance->setAttribute(Qt::WA_DeleteOnClose);
        QObject::connect(instance, &QObject::destroyed, []() {
            instance = nullptr;
        });
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}

FournisseurWindow::FournisseurWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FournisseurWindow)
{
    ui->setupUi(this);
    
    // Wire tableau de bord buttons by their visible text to avoid object-name differences
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                MainWindow::getInstance();
                this->close();
            });
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                SalesWindow::getInstance();
                this->close();
            });
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                gestionemploye00::getInstance();
                this->close();
            });
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                Gclient1::getInstance();
                this->close();
            });
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                this->raise();
                this->activateWindow();
            });
        }
    }
}

FournisseurWindow::~FournisseurWindow()
{
    delete ui;
}



