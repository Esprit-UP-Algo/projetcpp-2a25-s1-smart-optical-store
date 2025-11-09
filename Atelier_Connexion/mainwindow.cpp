#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),Etmp()

{
    ui->setupUi(this);

    Produit p;
    p.afficher(ui);

    ui->lineEdit_5->setPlaceholderText("Tapez la référence ou designation");
    ui->lineEdit_6->setPlaceholderText("Tapez la référence");

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
    QString ref        = ui->lineEdit_3->text();
    QString designation = ui->lineEdit_2->text();
    QString marque     = ui->lineEdit_7->text();
    QString couleur    = ui->lineEdit_8->text();
    QString prix       = ui->lineEdit_29->text();
    QString quantite   = ui->lineEdit_9->text();

    // REGEX
    QRegularExpression rxRef("^[A-Za-z]{2}[0-9]{5}$");
    QRegularExpression rxDesignation("^[A-Za-z]{5}[0-9]{2}$");
    QRegularExpression rxMarque("^[A-Za-z]+$");
    QRegularExpression rxCouleur("^[A-Za-z]+$");
    QRegularExpression rxPrix("^[0-9]+(\\.[0-9]+)?$");
    QRegularExpression rxQuantite("^[0-9]+$");

    // Vérifications
    if (!rxRef.match(ref).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La référence doit contenir 2 lettres + 5 chiffres (ex: AB12345).");
        return;
    }

    if (!rxDesignation.match(designation).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La désignation doit contenir 5 lettres + 2 chiffres (ex: ABCDE12).");
        return;
    }

    if (!rxMarque.match(marque).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La marque doit contenir seulement des lettres.");
        return;
    }

    if (!rxCouleur.match(couleur).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La couleur doit contenir seulement des lettres.");
        return;
    }

    if (!rxPrix.match(prix).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre (ex: 45 ou 45.6).");
        return;
    }

    if (!rxQuantite.match(quantite).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être un nombre.");
        return;
    }

    // Si tout est valide -> ajouter
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
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun produit trouvé !"));
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
void MainWindow::on_pushButton_16_clicked()
{
    Produit c(ui);
    if (c.existe(c.getRef()))
    {
        c.modifier();
        QMessageBox::information(this, " Modifié", "produit modifié avec succès");
    }
    else
    {

        QMessageBox::critical(this,tr("Erreur"),tr("produit pas trouvé") );
    }
    c.afficher(ui);
}
void  MainWindow::on_tableWidget_cellClicked(int row)
{
    ui->lineEdit_2->setText(ui->tableWidget->item(row, 7)->text());
    ui->lineEdit_3->setText(ui->tableWidget->item(row, 0)->text());
    ui->comboBox_2->setCurrentText(ui->tableWidget->item(row, 6)->text());
    ui->lineEdit_7->setText(ui->tableWidget->item(row, 5)->text());
    ui->lineEdit_29->setText(ui->tableWidget->item(row, 3)->text());
    ui->lineEdit_9->setText(ui->tableWidget->item(row, 4)->text());
    ui->lineEdit_8->setText(ui->tableWidget->item(row, 1)->text());

    ui->dateEdit->setDate(QDate::fromString(ui->tableWidget->item(row, 8)->text(), "yyyy-MM-dd"));
    QString genre = ui->tableWidget->item(row, 2)->text();

    if (genre == "Homme") {
        ui->radioButton->setChecked(true);
        ui->radioButton_2->setChecked(false);
    }
    else if (genre == "Femme") {
        ui->radioButton_2->setChecked(true);
        ui->radioButton->setChecked(false);
    }
    else {

        ui->radioButton->setAutoExclusive(false);
        ui->radioButton_2->setAutoExclusive(false);

        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);

        ui->radioButton->setAutoExclusive(true);
        ui->radioButton_2->setAutoExclusive(true);
    }
}


