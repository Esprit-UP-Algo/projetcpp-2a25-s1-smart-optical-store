#include "exporter.h"
#include "ui_exporter.h"

Exporter::Exporter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Exporter)
{
    ui->setupUi(this);
}

Exporter::~Exporter()
{
    delete ui;
}
