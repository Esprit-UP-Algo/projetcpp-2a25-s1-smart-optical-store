#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QMessageBox>
#include "saleswindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "produit.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include <QApplication>
#include "WindowManager.h"
#include <QMouseEvent>
#include "produit.h"
#include "Connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDate>
#include <QAbstractItemView>

#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFileDialog>

// Initialize static instance pointer
MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance(QWidget *parent)
{

    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new MainWindow(parent);
        instance->setAttribute(Qt::WA_DeleteOnClose);
        // Populate produit table immediately
        Produit p(instance->ui);      // Use the MainWindow's UI
        p.afficher(instance->ui);     // Fill table
        QObject::connect(instance, &QObject::destroyed, []() {
            instance = nullptr;
        });
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),Etmp()

    , ui(new Ui::MainWindow)
    , currentProductRef(0)
{
    ui->setupUi(this);




    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion de Stock", 1200, 800);
    
    //ui->lineEdit_5->setPlaceholderText("  Recherche par référence ou Nom ...");

    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
    }
    
    ui->lineEdit_5->setPlaceholderText("  Recherche par référence ou Nom ...");
    qDebug() << "Chemin courant =" << QDir::currentPath();
    ui->logoLabel->setPixmap(QPixmap(":/images/logof.jpg"));
    ui->logoLabel->setScaledContents(true);
    
    // Make logo clickable
    if (ui->logoLabel) {
        ui->logoLabel->setCursor(Qt::PointingHandCursor);
        ui->logoLabel->installEventFilter(this);
        ui->logoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Setup table widget
    ui->tableWidget->setColumnCount(9);
    QStringList headers = {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Connect table double-click
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::on_tableWidget_cellDoubleClicked);
    
    // Load products on startup
    loadProducts();
    clearForm();

    // Wire tableau de bord buttons by their visible text to avoid object-name differences
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                this->raise();
                this->activateWindow();
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
                FournisseurWindow::getInstance();
                this->close();
            });
        }
    }
    Produit p;
    p.afficher(ui);
    p.afficherRestock(ui,10);


    ui->lineEdit_5->setPlaceholderText("Tapez la référence ou designation");
    ui->lineEdit_6->setPlaceholderText("Tapez la référence");

    connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){
        ui->travaille_2->setCurrentIndex(0);
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){
        ui->travaille_2->setCurrentIndex(1);


    });


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




void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString ref        = ui->lineEdit_3->text();
    QString designation = ui->lineEdit_2->text();
    QString marque     = ui->lineEdit_7->text();
    QString couleur    = ui->lineEdit_8->text();
    QString prix       = ui->lineEdit_36->text();
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
    MainWindow::on_pushButton_31_clicked();
}

void MainWindow::on_pushButton_31_clicked()
{
    // Clear all input fields
    ui->lineEdit_3->clear();   // Ref
    ui->lineEdit_2->clear();   // Designation
    ui->lineEdit_9->clear();   // Quantité
    ui->lineEdit_36->clear();  // Prix
    ui->comboBox_4->setCurrentIndex(0);  // Catégorie
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


void MainWindow::on_pushButtonR_clicked()
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
void MainWindow::on_pushButton_32_clicked()
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
void MainWindow::on_tableWidget_cellClicked(int row)
{
    ui->lineEdit_3->setText(ui->tableWidget->item(row, 0)->text());
    ui->lineEdit_8->setText(ui->tableWidget->item(row, 1)->text());

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

    ui->lineEdit_36->setText(ui->tableWidget->item(row, 3)->text());
    ui->lineEdit_9->setText(ui->tableWidget->item(row, 4)->text());
    ui->lineEdit_7->setText(ui->tableWidget->item(row, 5)->text());
    ui->comboBox_4->setCurrentText(ui->tableWidget->item(row, 6)->text());
    ui->lineEdit_2->setText(ui->tableWidget->item(row, 7)->text());
    ui->dateEdit->setDate(QDate::fromString(ui->tableWidget->item(row, 8)->text(), "yyyy-MM-dd"));
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->logoLabel && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            on_logoClicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_logoClicked()
{
    DashboardWindow::getInstance();
    this->close();
}

void MainWindow::loadProducts()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Database not connected in loadProducts()";
        return;
    }
    
    // Disable updates temporarily for better performance
    ui->tableWidget->setUpdatesEnabled(false);
    
    Produit p;
    QSqlQueryModel* model = p.afficher();
    
    if (!model) {
        qDebug() << "Failed to create model";
        ui->tableWidget->setUpdatesEnabled(true);
        return;
    }
    
    // Clear existing rows
    ui->tableWidget->setRowCount(0);
    
    // Populate table
    for (int i = 0; i < model->rowCount(); ++i) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // Couleur
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(model->data(model->index(i, 6)).toString())); // Genre
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(model->data(model->index(i, 3)).toDouble(), 'f', 2)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem("")); // Fournisseur - not in produit table
    }
    
    // Re-enable updates and refresh display
    ui->tableWidget->setUpdatesEnabled(true);
    ui->tableWidget->viewport()->update();
    
    delete model;
    qDebug() << "Products loaded:" << ui->tableWidget->rowCount();
}

void MainWindow::clearForm()
{
    ui->lineEdit_11->clear();  // Nom
    ui->lineEdit_3->clear();  // Référence
    ui->lineEdit_4->clear();  // Fournisseur
    ui->lineEdit_7->clear();  // Marque
    ui->lineEdit_9->clear();  // Quantité
    ui->lineEdit_8->clear();  // Couleur
    ui->lineEdit_10->clear();  // Prix
    ui->dateEdit->setDate(QDate::currentDate());
    ui->radioButton->setChecked(true);  // Male
    currentProductRef = 0;
}

void MainWindow::fillForm(int reference)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT reference, designation, quantite, prix, categorie, couleur, genre, marque, date_expiration FROM produit WHERE reference = :ref");
    query.bindValue(":ref", reference);
    
    if (query.exec() && query.next()) {
        currentProductRef = reference;
        ui->lineEdit_3->setText(query.value(0).toString());  // Référence
        ui->lineEdit_11->setText(query.value(1).toString());  // Nom
        ui->lineEdit_9->setText(query.value(2).toString());  // Quantité
        // Set price in lineEdit_10
        double prix = query.value(3).toDouble();
        ui->lineEdit_10->setText(QString::number(prix, 'f', 2));  // Prix
        ui->comboBox->setCurrentText(query.value(4).toString());  // Catégorie
        ui->lineEdit_8->setText(query.value(5).toString());  // Couleur
        QString genre = query.value(6).toString();
        if (genre.compare("Femme", Qt::CaseInsensitive) == 0 || genre.compare("Female", Qt::CaseInsensitive) == 0) {
            ui->radioButton_2->setChecked(true);
        } else {
            ui->radioButton->setChecked(true);
        }
        ui->lineEdit_7->setText(query.value(7).toString());  // Marque
        ui->dateEdit->setDate(query.value(8).toDate());
    }
}

void MainWindow::on_pushButton_2_clicked()  // Valider - Add/Modify
{
    // Validate required fields
    if (ui->lineEdit_11->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom du produit est requis!");
        return;
    }
    
    // Validate price
    bool prixOk = false;
    double prix = ui->lineEdit_10->text().toDouble(&prixOk);
    if (!prixOk || prix < 0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre valide et positif!");
        return;
    }
    
    Produit p;
    p.setDesignation(ui->lineEdit_11->text());
    p.setQuantite(ui->lineEdit_9->text().toInt());
    p.setPrix(prix);  // Use lineEdit_10 for price
    p.setCategorie(ui->comboBox->currentText());
    p.setCouleur(ui->lineEdit_8->text());
    p.setGenre(ui->radioButton->isChecked() ? "Homme" : "Femme");
    p.setMarque(ui->lineEdit_7->text());
    p.setDateExpiration(ui->dateEdit->date());
    
    bool success = false;
    int newReference = 0;
    
    if (currentProductRef > 0) {
        // Modify existing
        p.setReference(currentProductRef);
        success = p.modifier();
        if (success) {
            // Refresh table immediately
            loadProducts();
            clearForm();
            QMessageBox::information(this, "Succès", "Produit modifié avec succès!");
            
            // Scroll to the modified product
            scrollToProduct(currentProductRef);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du produit!");
        }
    } else {
        // Add new
        success = p.ajouter();
        if (success) {
            // Get the newly inserted product reference
            QSqlDatabase db = QSqlDatabase::database();
            QSqlQuery query(db);
            query.exec("SELECT MAX(reference) FROM produit");
            if (query.next()) {
                newReference = query.value(0).toInt();
            }
            
            // Refresh table immediately before showing message
            loadProducts();
            clearForm();
            QMessageBox::information(this, "Succès", "Produit ajouté avec succès!");
            
            // Scroll to the newly added product
            if (newReference > 0) {
                scrollToProduct(newReference);
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du produit!");
        }
    }
}

void MainWindow::on_pushButton_5_clicked()  // Delete
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un produit à supprimer!");
        return;
    }
    
    QTableWidgetItem* refItem = ui->tableWidget->item(currentRow, 7);  // Référence column
    if (!refItem) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer la référence du produit!");
        return;
    }
    
    int reference = refItem->text().toInt();
    if (reference <= 0) {
        QMessageBox::warning(this, "Erreur", "Référence invalide!");
        return;
    }
    
    int ret = QMessageBox::question(this, "Confirmation", 
                                     QString("Êtes-vous sûr de vouloir supprimer le produit (Réf: %1)?").arg(reference),
                                     QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        Produit p;
        if (p.supprimer(reference)) {
            QMessageBox::information(this, "Succès", "Produit supprimé avec succès!");
            loadProducts();
            clearForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du produit!");
        }
    }
}

void MainWindow::on_pushButton_9_clicked()  // Filter
{
    QString searchText = ui->lineEdit_5->text().trimmed();
    if (searchText.isEmpty()) {
        loadProducts();
        return;
    }
    
    Produit p;
    QSqlQueryModel* model = p.rechercher(searchText);
    
    if (!model) {
        return;
    }
    
    ui->tableWidget->setRowCount(0);
    
    for (int i = 0; i < model->rowCount(); ++i) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(model->data(model->index(i, 3)).toDouble(), 'f', 2)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(""));
    }
    
    delete model;
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    QTableWidgetItem* refItem = ui->tableWidget->item(row, 7);  // Référence column
    if (refItem) {
        int reference = refItem->text().toInt();
        if (reference > 0) {
            fillForm(reference);
        }
    }
}

void MainWindow::scrollToProduct(int reference)
{
    // Find the product in the table and scroll to it
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* refItem = ui->tableWidget->item(row, 7);  // Référence column
        if (refItem && refItem->text().toInt() == reference) {
            ui->tableWidget->scrollToItem(refItem, QAbstractItemView::EnsureVisible);
            ui->tableWidget->selectRow(row);
            ui->tableWidget->setCurrentCell(row, 0);
            break;
        }
    }
}
