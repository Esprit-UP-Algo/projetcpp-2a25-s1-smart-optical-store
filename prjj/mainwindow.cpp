#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_5->setPlaceholderText("  Recherche par référence ou Nom ...");
    qDebug() << "Chemin courant =" << QDir::currentPath();
    ui->image->setPixmap(QPixmap("C:/Users/mimi/Desktop/gsxg/images/1223.jpg"));
    ui->image->setScaledContents(true);
    ui->image2->setPixmap(QPixmap("C:/Users/mimi/Desktop/gsxg/images/1223.jpg"));
    ui->image2->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




