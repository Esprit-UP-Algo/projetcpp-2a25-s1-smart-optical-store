#include "gclient1.h"
#include "ui_gclient1.h"

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gclient1)
{
    ui->setupUi(this);
}

Gclient1::~Gclient1()
{
    delete ui;
}
