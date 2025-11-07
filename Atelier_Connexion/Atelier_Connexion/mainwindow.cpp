#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),Etmp()

{
    ui->setupUi(this);
    Produit p;
    p.afficher(ui);

    ui->lineEdit_5->setPlaceholderText("Tapez la référence");
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

void MainWindow::on_on_btnvente_clicked_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btnemployer_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btnProd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);


}


void MainWindow::on_btnFour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_2_clicked()
{

        Produit p(ui);
        p.ajouter();
        p.afficher(ui);
        MainWindow::on_pushButton_14_clicked();


}
void MainWindow::on_pushButton_14_clicked()
{
        // Clear all input fields
        ui->lineEdit_3->clear();   // Ref
        ui->lineEdit_2->clear();   // Designation
        ui->lineEdit_9->clear();   // Quantité
        ui->lineEdit_29->clear();  // Prix
        ui->comboBox_2->setCurrentIndex(0);  // Catégorie
        ui->lineEdit_8->clear();   // Couleur
        ui->lineEdit_7->clear();   // Marque
        ui->dateEdit->setDate(QDate::currentDate()); // Date d’expiration
        ui->radioButton->setAutoExclusive(false);
        ui->radioButton_2->setAutoExclusive(false);
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
        ui->radioButton->setAutoExclusive(true);
        ui->radioButton_2->setAutoExclusive(true);


}




void MainWindow::on_pushButton_5_clicked()
{
    QString ref = ui->lineEdit_6->text();

    Produit c;
    bool test = c.supprimer(ref);

    if (test)
    {
        QMessageBox::information(this, tr("Suppression réussie"),tr("Le produit a été supprimé avec succès."));
        c.afficher(ui);
    }
    else
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échoué. Vérifiez la ref saisi.") );
    }
    ui->lineEdit_6->clear();
}


void MainWindow::on_pushButton_clicked()
{
    QString rech = ui->lineEdit_5->text();
    Produit c;

    if (!c.rech(rech, ui)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun client trouvé !"));
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    QString trier = ui->comboBox->currentText();
    if (trier == "categories")
    {

        ui->tableWidget->sortItems(6, Qt::AscendingOrder);
    }
    else if (trier == "prix")
    {

        ui->tableWidget->sortItems(3, Qt::AscendingOrder);
    }
    else if (trier == "genre")
    {
        ui->tableWidget->sortItems(2, Qt::DescendingOrder );
    }
    else
    {
        QMessageBox::warning(this, "Tri", "Choisissez un critère valide !");
    }
}
void MainWindow::on_pushButton_7_clicked()
{
    Produit c(ui);
    if (c.existe(c.getRef()))
    {
        c.modifier();
        QMessageBox::information(this, " Modifié", "Client modifié avec succès");
    }
    else
    {

        QMessageBox::critical(this,tr("Erreur"),tr("client pas trouvé") );
    }
    c.afficher(ui);
}

