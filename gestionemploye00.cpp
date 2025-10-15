#include "gestionemploye00.h"
#include "./ui_gestionemploye00.h"
#include "statistique.h"
#include "exporter.h"
#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include <QApplication>

// Initialize static instance pointer
gestionemploye00* gestionemploye00::instance = nullptr;

gestionemploye00* gestionemploye00::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new gestionemploye00(parent);
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
gestionemploye00::gestionemploye00(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gestionemploye00)
{
    ui->setupUi(this);
}

gestionemploye00::~gestionemploye00()
{
    delete ui;
}

void gestionemploye00::on_pushButton_6_clicked()
{
    Statistique *h = new Statistique();
    h->show();
}



void gestionemploye00::on_pushButton_10_clicked()
{
    Exporter *h = new Exporter();
    h->show();
}


void gestionemploye00::on_pushButton_14_clicked()
{
    // Stock
    MainWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_8_clicked()
{
    // Ventes
    SalesWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_9_clicked()
{
    // Client
    Gclient1::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_7_clicked()
{
    // Produit -> go to stock page (MainWindow)
    MainWindow::getInstance();
    this->close();
}

void gestionemploye00::on_pushButton_11_clicked()
{
    // Fournisseur
    FournisseurWindow::getInstance();
    this->close();
}

