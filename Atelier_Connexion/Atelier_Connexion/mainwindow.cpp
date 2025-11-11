#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),Etmp(),selectedId(-1)

{
    ui->setupUi(this);

    afficherFournisseurs();

    // Désactiver le bouton Supprimer tant qu’aucune ligne n’est sélectionnée
    ui->pushButton_delete->setEnabled(false);


    Produit p;
    p.afficher(ui);
    p.afficherRestock(ui,10);


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
    ui->stackedWidget->setCurrentIndex(4);
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
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::showToast(QString message)
{
    QLabel *toast = new QLabel(message, this);
    toast->setStyleSheet(
        "background-color: #ff4444; "
        "color: white; "
        "padding: 10px 18px; "
        "border-radius: 8px; "
        "font-weight: bold;"
        );
    toast->setAlignment(Qt::AlignCenter);
    toast->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    toast->adjustSize();
    toast->move(width()/2 - toast->width()/2, 20);
    toast->show();

    QPropertyAnimation *anim = new QPropertyAnimation(toast, "opacity");
    anim->setDuration(2500);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, &QPropertyAnimation::finished, toast, &QLabel::deleteLater);
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


void MainWindow::afficherFournisseurs()
{
    QSqlQuery query("SELECT * FROM FOURNISSEUR");

    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->setRowCount(0);

    QStringList headers;
    headers << "ID" << "Entreprise" << "Contact" << "Email"
            << "Téléphone" << "Type Produit" << "Condition" << "Historique";
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next())
    {
        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(query.value(7).toDate().toString("dd/MM/yyyy")));
        row++;
    }

    ui->tableWidget_2->resizeColumnsToContents();
    qDebug() << "Affichage de" << row << "fournisseur(s)";
}

void MainWindow::on_tableWidget_2_itemClicked()
{
    int row = ui->tableWidget_2->currentRow();

    if (row >= 0)
    {
        selectedId = ui->tableWidget_2->item(row, 0)->text().toInt();

        ui->lineEdit->setText(ui->tableWidget_2->item(row, 0)->text());
        ui->lineEdit_4->setText(ui->tableWidget_2->item(row, 1)->text());
        ui->lineEdit_10->setText(ui->tableWidget_2->item(row, 2)->text());
        ui->lineEdit_27->setText(ui->tableWidget_2->item(row, 3)->text());
        ui->lineEdit_28->setText(ui->tableWidget_2->item(row, 4)->text());
        ui->lineEdit_32->setText(ui->tableWidget_2->item(row, 5)->text());
        ui->lineEdit_31->setText(ui->tableWidget_2->item(row, 6)->text());
        ui->lineEdit_30->setText(ui->tableWidget_2->item(row, 7)->text());

        ui->pushButton_delete->setEnabled(true); // activer le bouton Supprimer
    }
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString idStr = ui->lineEdit->text();
    QString nom_ent = ui->lineEdit_4->text();
    QString nom_cont = ui->lineEdit_10->text();
    QString email = ui->lineEdit_27->text();
    QString tel = ui->lineEdit_28->text();
    QString type_prod = ui->lineEdit_32->text();
    QString condStr = ui->lineEdit_31->text();
    QString histStr = ui->lineEdit_30->text();

    // === VALIDATIONS ===
    if (idStr.isEmpty() || !QRegularExpression("^[0-9]+$").match(idStr).hasMatch()) {
        QMessageBox::warning(this, "Attention", "L'ID doit contenir uniquement des chiffres !");
        return;
    }
    if (!QRegularExpression("^\\d{8}$").match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Le téléphone doit avoir 8 chiffres !");
        return;
    }
    if (!QRegularExpression("^[01]$").match(condStr).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Condition paiement doit être 0 ou 1 !");
        return;
    }

    QDate hist = QDate::fromString(histStr, "dd/MM/yyyy");
    if (!hist.isValid()) {
        QMessageBox::warning(this, "Attention", "Format date : jj/MM/aaaa !");
        return;
    }

    int id = idStr.toInt();
    int cond_paie = condStr.toInt();

    Fournisseur F(id, nom_ent, nom_cont, email, tel, type_prod, cond_paie, hist);

    if (F.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté !");
        afficherFournisseurs();
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout échoué !");
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Sélectionnez un fournisseur !");
        return;
    }

    QString nom_ent = ui->lineEdit_4->text();
    QString nom_cont = ui->lineEdit_10->text();
    QString email = ui->lineEdit_27->text();
    QString tel = ui->lineEdit_28->text();
    QString type_prod = ui->lineEdit_32->text();
    QString condStr = ui->lineEdit_31->text();
    QString histStr = ui->lineEdit_30->text();

    if (!QRegularExpression("^\\d{8}$").match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention", "Téléphone invalide !");
        return;
    }

    int cond_paie = condStr.toInt();
    QDate hist = QDate::fromString(histStr, "dd/MM/yyyy");

    Fournisseur F(selectedId, nom_ent, nom_cont, email, tel, type_prod, cond_paie, hist);

    if (F.modifier(selectedId)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié !");
        afficherFournisseurs();
    } else {
        QMessageBox::critical(this, "Erreur", "Modification échouée !");
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un fournisseur à supprimer !");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce fournisseur ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Fournisseur f;
        if (f.supprimer(selectedId)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès !");
            afficherFournisseurs();
            selectedId = -1;
            ui->pushButton_delete->setEnabled(false);

            ui->lineEdit->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_10->clear();
            ui->lineEdit_27->clear();
            ui->lineEdit_28->clear();
            ui->lineEdit_32->clear();
            ui->lineEdit_31->clear();
            ui->lineEdit_30->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}
