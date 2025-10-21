#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){
        ui->travaille->setCurrentIndex(0);
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){
        ui->travaille->setCurrentIndex(1);

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnProd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_on_btnvente_clicked_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btnemployer_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_btnFour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




