#include "tab.h"
#include "ui_tab.h"
#include "gestionemploye00.h"
#include "mainwindow.h"      // GestionStock.ui
#include "saleswindow.h"      // saleswindow.ui
#include "gclient1.h"         // gclient1.ui
tab::tab(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tab)
{
    ui->setupUi(this);
}

tab::~tab()
{
    delete ui;
}

void tab::on_emp_clicked()
{
    gestionemploye00 *h = gestionemploye00::getInstance("admin", this);
    h->setAttribute(Qt::WA_DeleteOnClose);
    h->show();
    this->close();
}


void tab::on_pushButton_10_clicked()
{
    // Produits -> open GestionStock (MainWindow)
    MainWindow *win = new MainWindow();
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->show();
    this->close();
}

void tab::on_pushButton_11_clicked()
{
    // Ventes -> open SalesWindow
    SalesWindow *win = new SalesWindow();
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->show();
    this->close();
}

void tab::on_pushButton_12_clicked()
{
    // Clients -> open Gclient1
    Gclient1 *win = new Gclient1();
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->show();
    this->close();
}

