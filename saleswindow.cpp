#include "saleswindow.h"
#include "ui_saleswindow.h"
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QStandardItem>
#include <QSqlError>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include "WindowManager.h"

// Initialize static instance pointer
SalesWindow* SalesWindow::instance = nullptr;

SalesWindow* SalesWindow::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new SalesWindow(parent);
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

SalesWindow::SalesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesWindow),
    cartModel(nullptr),
    salesModel(nullptr),
    currentClientId(0),
    currentEmployeId(0)
{
    ui->setupUi(this);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Ventes");
    
    // Setup models and tables
    setupModels();
    
    // Set current date for date filters
    ui->startDateEdit->setDate(QDate::currentDate().addDays(-30));
    ui->endDateEdit->setDate(QDate::currentDate());
    
    // Populate payment method combo box
    ui->paymentMethodComboBox->addItem("Espèces");
    ui->paymentMethodComboBox->addItem("Carte de crédit");
    ui->paymentMethodComboBox->addItem("Carte de débit");
    ui->paymentMethodComboBox->addItem("Assurance");
    ui->paymentMethodComboBox->addItem("Chèque");
    
    // Connect signals and slots
    connect(ui->addProductButton, &QPushButton::clicked, this, &SalesWindow::on_addProductButton_clicked);
    connect(ui->removeProductButton, &QPushButton::clicked, this, &SalesWindow::on_removeProductButton_clicked);
    connect(ui->customerSearchButton, &QPushButton::clicked, this, &SalesWindow::on_customerSearchButton_clicked);
    connect(ui->productSearchButton, &QPushButton::clicked, this, &SalesWindow::on_productSearchButton_clicked);
    connect(ui->saveSaleButton, &QPushButton::clicked, this, &SalesWindow::on_saveSaleButton_clicked);
    connect(ui->newSaleButton, &QPushButton::clicked, this, &SalesWindow::on_newSaleButton_clicked);
    
    // Tableau de bord navigation
    connect(ui->pushButton,   &QPushButton::clicked, this, &SalesWindow::on_pushButton_clicked);   // Stock
    connect(ui->pushButton_2, &QPushButton::clicked, this, &SalesWindow::on_salesButton_clicked);  // Ventes (self)
    connect(ui->pushButton_3, &QPushButton::clicked, this, &SalesWindow::on_pushButton_3_clicked); // Employes
    connect(ui->pushButton_4, &QPushButton::clicked, this, &SalesWindow::on_pushButton_4_clicked); // Clients
    connect(ui->pushButton_5, &QPushButton::clicked, this, &SalesWindow::on_pushButton_5_clicked); // Fournisseur
    connect(ui->sortButton, &QPushButton::clicked, this, &SalesWindow::on_sortButton_clicked);
    
    // Initialize
    clearSaleForm();
    refreshSalesTable();
}

SalesWindow::~SalesWindow()
{
    delete ui;
    delete cartModel;
    if (salesModel) {
        delete salesModel;
    }
}

void SalesWindow::setupModels()
{
    // Setup cart model
    cartModel = new QStandardItemModel(0, 5, this);
    cartModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    cartModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    cartModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    cartModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    cartModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Total"));
    
    ui->cartTableView->setModel(cartModel);
    ui->cartTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cartTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cartTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartTableView->horizontalHeader()->setStretchLastSection(true);
    ui->cartTableView->verticalHeader()->setVisible(false);
    
    // Setup sales model using the Vente class
    salesModel = venteObj.afficher();
    
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->salesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->salesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->salesTableView->horizontalHeader()->setStretchLastSection(true);
    ui->salesTableView->verticalHeader()->setVisible(false);
    
    // Populate sort combo box
    ui->sortComboBox->addItem("ID (Croissant)");
    ui->sortComboBox->addItem("ID (Décroissant)");
    ui->sortComboBox->addItem("Date (Croissant)");
    ui->sortComboBox->addItem("Date (Décroissant)");
    ui->sortComboBox->addItem("Montant (Croissant)");
    ui->sortComboBox->addItem("Montant (Décroissant)");
    ui->sortComboBox->addItem("Client (A-Z)");
    ui->sortComboBox->addItem("Client (Z-A)");
    
    // Populate payment method combo box
    ui->paymentMethodComboBox->clear();
    ui->paymentMethodComboBox->addItem("Espèces");
    ui->paymentMethodComboBox->addItem("Carte de crédit");
    ui->paymentMethodComboBox->addItem("Carte de débit");
    ui->paymentMethodComboBox->addItem("Chèque");
    ui->paymentMethodComboBox->addItem("Virement bancaire");
    ui->paymentMethodComboBox->addItem("Assurance");
    
    // Add modify and delete buttons to the sales history tab
    QWidget *salesTabContent = ui->tabWidget->widget(1); // Get the sales history tab
    QVBoxLayout *salesTabLayout = qobject_cast<QVBoxLayout*>(salesTabContent->layout());
    
    if (salesTabLayout) {
        // Create buttons layout
        QHBoxLayout *buttonsLayout = new QHBoxLayout();
        
        // Create modify button
        QPushButton *modifyButton = new QPushButton("Modifier la vente sélectionnée", salesTabContent);
        modifyButton->setObjectName("modifySaleButton");
        modifyButton->setStyleSheet("background-color: #55aaff; color: black;");
        buttonsLayout->addWidget(modifyButton);
        
        // Create delete button
        QPushButton *deleteButton = new QPushButton("Supprimer la vente sélectionnée", salesTabContent);
        deleteButton->setObjectName("deleteSaleButton");
        deleteButton->setStyleSheet("background-color: #ff5555; color: white;");
        buttonsLayout->addWidget(deleteButton);
        
        // Add the buttons layout after the table view
        salesTabLayout->insertLayout(salesTabLayout->count() - 1, buttonsLayout);
        
        // Connect the buttons to their slots
        connect(modifyButton, &QPushButton::clicked, this, &SalesWindow::on_modifySaleButton_clicked);
        connect(deleteButton, &QPushButton::clicked, this, &SalesWindow::on_deleteSaleButton_clicked);
    }
    
    /* 
    // TODO: Uncomment after adding UI elements in Qt Designer
    
    // Populate sale status combo box
    ui->saleStatusComboBox->clear();
    ui->saleStatusComboBox->addItem("En cours");
    ui->saleStatusComboBox->addItem("Complétée");
    ui->saleStatusComboBox->addItem("Annulée");
    ui->saleStatusComboBox->addItem("En attente");
    
    // Populate payment status combo box
    ui->paymentStatusComboBox->clear();
    ui->paymentStatusComboBox->addItem("Payé");
    ui->paymentStatusComboBox->addItem("Non payé");
    ui->paymentStatusComboBox->addItem("Partiellement payé");
    ui->paymentStatusComboBox->addItem("Remboursé");
    
    // Set default delivery date to current date + 1 day
    ui->deliveryDateEdit->setDate(QDate::currentDate().addDays(1));
    
    // Setup product selection combo box
    QSqlQueryModel* productModel = produitObj.afficher();
    ui->productComboBox->clear();
    
    for (int i = 0; i < productModel->rowCount(); ++i) {
        int reference = productModel->data(productModel->index(i, 0)).toInt();
        QString designation = productModel->data(productModel->index(i, 1)).toString();
        ui->productComboBox->addItem(QString("%1 - %2").arg(reference).arg(designation), reference);
    }
    
    delete productModel;
    
    // Setup employee selection combo box
    QSqlQueryModel* employeeModel = employeObj.afficher();
    ui->employeeComboBox->clear();
    ui->employeeComboBox->addItem("Aucun", 0);
    
    for (int i = 0; i < employeeModel->rowCount(); ++i) {
        int id = employeeModel->data(employeeModel->index(i, 0)).toInt();
        QString nom = employeeModel->data(employeeModel->index(i, 1)).toString();
        QString prenom = employeeModel->data(employeeModel->index(i, 2)).toString();
        ui->employeeComboBox->addItem(QString("%1 - %2 %3").arg(id).arg(nom).arg(prenom), id);
    }
    
    delete employeeModel;
    */
}

void SalesWindow::refreshSalesTable()
{
    // Delete old model if exists
    if (salesModel) {
        delete salesModel;
    }
    
    // Get fresh data from database
    salesModel = venteObj.afficher();
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->resizeColumnsToContents();
}

void SalesWindow::updateTotals()
{
    double subtotal = 0.0;
    
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        QString totalStr = cartModel->data(cartModel->index(row, 4)).toString();
        totalStr.remove(" DT");
        subtotal += totalStr.toDouble();
    }
    
    /* TODO: Uncomment after adding UI elements in Qt Designer
    // Apply discount
    double discountPercent = ui->discountSpinBox->value();
    double discountAmount = subtotal * (discountPercent / 100.0);
    double discountedSubtotal = subtotal - discountAmount;
    
    // Calculate tax (assuming 19% TVA)
    double taxRate = 0.19;
    double tax = discountedSubtotal * taxRate;
    double total = discountedSubtotal + tax;
    
    // Update labels
    ui->subtotalLabel->setText(QString("%1 DT").arg(subtotal, 0, 'f', 2));
    ui->discountLabel->setText(QString("%1 DT").arg(discountAmount, 0, 'f', 2));
    ui->discountedSubtotalLabel->setText(QString("%1 DT").arg(discountedSubtotal, 0, 'f', 2));
    ui->taxLabel->setText(QString("%1 DT").arg(tax, 0, 'f', 2));
    ui->totalLabel->setText(QString("%1 DT").arg(total, 0, 'f', 2));
    */
    
    // Simple calculation without discount for now
    double taxRate = 0.19;
    double tax = subtotal * taxRate;
    double total = subtotal + tax;
    
    ui->subtotalLabel->setText(QString("%1 DT").arg(subtotal, 0, 'f', 2));
    ui->taxLabel->setText(QString("%1 DT").arg(tax, 0, 'f', 2));
    ui->totalLabel->setText(QString("%1 DT").arg(total, 0, 'f', 2));
}

/* TODO: Uncomment after adding UI elements in Qt Designer
void SalesWindow::on_discountSpinBox_valueChanged(int value)
{
    Q_UNUSED(value);
    updateTotals();
}
*/

void SalesWindow::clearSaleForm()
{
    ui->customerIdLineEdit->clear();
    ui->customerNameLineEdit->clear();
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->quantitySpinBox->setValue(1);
    ui->paymentMethodComboBox->setCurrentIndex(0);
    
    /* TODO: Uncomment after adding UI elements in Qt Designer
    ui->saleStatusComboBox->setCurrentIndex(0);
    ui->paymentStatusComboBox->setCurrentIndex(0);
    ui->employeeComboBox->setCurrentIndex(0);
    ui->productComboBox->setCurrentIndex(0);
    ui->discountSpinBox->setValue(0);
    ui->deliveryDateEdit->setDate(QDate::currentDate().addDays(1));
    */
    
    // Reset current IDs
    currentClientId = 0;
    currentEmployeId = 0;
    
    // Clear cart items list
    cartItems.clear();
    
    // Clear cart model
    cartModel->removeRows(0, cartModel->rowCount());
    
    updateTotals();
}

bool SalesWindow::validateSale()
{
    if (cartModel->rowCount() == 0) {
        QMessageBox::warning(this, "Erreur de validation", "Le panier est vide. Veuillez ajouter des produits à la vente.");
        return false;
    }
    
    if (currentClientId <= 0) {
        QMessageBox::warning(this, "Erreur de validation", "Veuillez sélectionner un client.");
        return false;
    }
    
    // Check if the client exists in the database
    QSqlQuery clientCheck;
    clientCheck.prepare("SELECT id_client FROM clients WHERE id_client = :id_client");
    clientCheck.bindValue(":id_client", currentClientId);
    
    if (!clientCheck.exec() || !clientCheck.next()) {
        QMessageBox::warning(this, "Erreur de validation", "Le client sélectionné n'existe pas dans la base de données.");
        return false;
    }
    
    return true;
}

void SalesWindow::on_addProductButton_clicked()
{
    QString productIdStr = ui->productIdLineEdit->text();
    QString productName = ui->productNameLineEdit->text();
    QString priceStr = ui->priceLineEdit->text();
    
    if (productIdStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une référence de produit!");
        return;
    }
    
    if (productName.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez d'abord rechercher un produit par son ID!");
        return;
    }
    
    int productId = productIdStr.toInt();
    
    // Get product details from database
    QSqlQuery query;
    query.prepare("SELECT reference, designation, prix, quantite FROM produit WHERE reference = :reference");
    query.bindValue(":reference", productId);
    
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur de recherche", "Produit non trouvé!");
        return;
    }
    
    int reference = query.value(0).toInt();
    QString designation = query.value(1).toString();
    double prix = query.value(2).toDouble();
    int stockDisponible = query.value(3).toInt();
    
    int quantity = ui->quantitySpinBox->value();
    
    if (quantity <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "La quantité doit être supérieure à 0!");
        return;
    }
    
    if (quantity > stockDisponible) {
        QMessageBox::warning(this, "Stock insuffisant", 
                            QString("Stock disponible: %1\nQuantité demandée: %2").arg(stockDisponible).arg(quantity));
        return;
    }
    
    double total = prix * quantity;
    
    // Check if product is already in cart
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        if (cartModel->data(cartModel->index(row, 0)).toInt() == reference) {
            int currentQty = cartModel->data(cartModel->index(row, 3)).toInt();
            int newQty = currentQty + quantity;
            
            if (newQty > stockDisponible) {
                QMessageBox::warning(this, "Stock insuffisant", 
                                    QString("Stock disponible: %1\nQuantité totale demandée: %2").arg(stockDisponible).arg(newQty));
                return;
            }
            
            double newTotal = prix * newQty;
            
            cartModel->setData(cartModel->index(row, 3), newQty);
            cartModel->setData(cartModel->index(row, 4), QString("%1 DT").arg(newTotal, 0, 'f', 2));
            
            // Update cart items list
            for (int i = 0; i < cartItems.size(); ++i) {
                if (cartItems[i].first == reference) {
                    cartItems[i].second = newQty;
                    break;
                }
            }
            
            updateTotals();
            
            // Clear product input fields
            ui->productIdLineEdit->clear();
            ui->productNameLineEdit->clear();
            ui->priceLineEdit->clear();
            
            return;
        }
    }
    
    // Add new product to cart
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::number(reference));
    row << new QStandardItem(designation);
    row << new QStandardItem(QString("%1 DT").arg(prix, 0, 'f', 2));
    row << new QStandardItem(QString::number(quantity));
    row << new QStandardItem(QString("%1 DT").arg(total, 0, 'f', 2));
    
    cartModel->appendRow(row);
    ui->cartTableView->resizeColumnsToContents();
    
    // Add to cart items list
    cartItems.append(qMakePair(reference, quantity));
    
    // Clear product input fields
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    
    updateTotals();
}

void SalesWindow::on_removeProductButton_clicked()
{
    if (!ui->cartTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un produit à supprimer!");
        return;
    }
    
    int row = ui->cartTableView->selectionModel()->selectedRows().first().row();
    int reference = cartModel->data(cartModel->index(row, 0)).toInt();
    
    // Remove from cart items list
    for (int i = 0; i < cartItems.size(); ++i) {
        if (cartItems[i].first == reference) {
            cartItems.removeAt(i);
            break;
        }
    }
    
    cartModel->removeRow(row);
    
    updateTotals();
}

void SalesWindow::on_customerSearchButton_clicked()
{
    QString searchText = ui->customerIdLineEdit->text();
    
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Erreur de recherche", "Veuillez entrer un ID client!");
        return;
    }
    
    // Search client in database
    QSqlQuery query;
    query.prepare("SELECT id_client, nom, prenom FROM clients WHERE id_client = :id");
    query.bindValue(":id", searchText.toInt());
    
    if (query.exec() && query.next()) {
        currentClientId = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        
        ui->customerNameLineEdit->setText(nom + " " + prenom);
    } else {
        QMessageBox::warning(this, "Client non trouvé", "Aucun client trouvé avec cet ID.");
        ui->customerNameLineEdit->clear();
        currentClientId = 0;
    }
}

void SalesWindow::on_productSearchButton_clicked()
{
    QString searchText = ui->productIdLineEdit->text();
    
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Erreur de recherche", "Veuillez entrer une référence de produit!");
        return;
    }
    
    // Search product in database by ID and get name and price
    QSqlQuery query;
    query.prepare("SELECT reference, designation, prix FROM produit WHERE reference = :reference");
    query.bindValue(":reference", searchText.toInt());
    
    if (query.exec() && query.next()) {
        // Display product name and price
        QString designation = query.value(1).toString();
        double prix = query.value(2).toDouble();
        
        ui->productNameLineEdit->setText(designation);
        ui->priceLineEdit->setText(QString::number(prix, 'f', 2));
        
        // No need for a success message - just update the fields
    } else {
        QMessageBox::warning(this, "Produit non trouvé", "Aucun produit trouvé avec cette référence.");
        ui->productNameLineEdit->clear();
        ui->priceLineEdit->clear();
    }
}

/* TODO: Uncomment after adding UI elements in Qt Designer
void SalesWindow::on_productComboBox_currentIndexChanged(int index)
{
    if (index < 0) return;
    
    int productId = ui->productComboBox->currentData().toInt();
    if (productId <= 0) return;
    
    // Get product details from database
    QSqlQuery query;
    query.prepare("SELECT reference, designation, prix, quantite FROM produit WHERE reference = :reference");
    query.bindValue(":reference", productId);
    
    if (query.exec() && query.next()) {
        ui->productIdLineEdit->setText(query.value(0).toString());
        ui->productNameLineEdit->setText(query.value(1).toString());
        ui->priceLineEdit->setText(QString::number(query.value(2).toDouble(), 'f', 2));
        
        // Set maximum quantity based on stock
        int stockQuantity = query.value(3).toInt();
        ui->quantitySpinBox->setMaximum(stockQuantity);
        
        // Update stock information
        ui->stockInfoLabel->setText(QString("Stock disponible: %1").arg(stockQuantity));
    }
}

void SalesWindow::on_employeeComboBox_currentIndexChanged(int index)
{
    if (index < 0) return;
    
    currentEmployeId = ui->employeeComboBox->currentData().toInt();
}
*/

void SalesWindow::on_saveSaleButton_clicked()
{
    if (!validateSale()) {
        return;
    }
    
    // Prepare sale data
    QDate currentDate = QDate::currentDate();
    
    // Get totals
    QString subtotalStr = ui->subtotalLabel->text();
    subtotalStr.remove(" DT");
    double subtotal = subtotalStr.toDouble();
    
    QString taxStr = ui->taxLabel->text();
    taxStr.remove(" DT");
    double tax = taxStr.toDouble();
    
    QString totalStr = ui->totalLabel->text();
    totalStr.remove(" DT");
    double total = totalStr.toDouble();
    
    // Get payment method
    QString paymentMethod = ui->paymentMethodComboBox->currentText();
    
    /* TODO: Uncomment after adding UI elements in Qt Designer
    // Get discount
    double discount = ui->discountSpinBox->value();
    
    // Get payment method and statuses
    QString saleStatus = ui->saleStatusComboBox->currentText();
    QString paymentStatus = ui->paymentStatusComboBox->currentText();
    
    // Get employee ID
    int employeeId = ui->employeeComboBox->currentData().toInt();
    
    // Get delivery date
    QDate deliveryDate = ui->deliveryDateEdit->date();
    */
    
    // Use default values for now
    double discount = 0;
    QString saleStatus = "Complétée";
    QString paymentStatus = "Payé";
    QDate deliveryDate = QDate::currentDate().addDays(1);
    
    // Check if there's a valid employee in the database
    QSqlQuery empQuery;
    empQuery.exec("SELECT id_employe FROM employe");
    int employeeId = 0; // Default to NULL (0)
    
    // Use the first employee found if any exist
    if (empQuery.next()) {
        employeeId = empQuery.value(0).toInt();
    }
    
    // Create sale in database
    Vente newVente;
    newVente.setIdClient(currentClientId);
    newVente.setIdEmploye(employeeId);
    newVente.setDateVente(currentDate);
    newVente.setPrixTtc(total);
    newVente.setPrixHt(subtotal);
    newVente.setRemise(discount);
    newVente.setTva(tax);
    newVente.setStatutVente(saleStatus);
    newVente.setStatutPaiement(paymentStatus);
    newVente.setModePaiement(paymentMethod);
    newVente.setDateLivraison(deliveryDate);
    
    if (!newVente.ajouter()) {
        // Check if there are any clients in the database
        QSqlQuery clientQuery;
        clientQuery.exec("SELECT COUNT(*) FROM clients");
        int clientCount = 0;
        if (clientQuery.next()) {
            clientCount = clientQuery.value(0).toInt();
        }
        
        if (clientCount == 0) {
            QMessageBox::critical(this, "Erreur", "Aucun client n'existe dans la base de données. Veuillez d'abord ajouter un client.");
        } else if (currentClientId <= 0) {
            QMessageBox::critical(this, "Erreur", "Veuillez sélectionner un client valide avant de créer une vente.");
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement de la vente. Vérifiez que les employés et clients existent dans la base de données.");
        }
        return;
    }
    
    int idVente = newVente.getId();
    
    // Add products to sale
    bool allProductsAdded = true;
    
    for (int i = 0; i < cartItems.size(); ++i) {
        int reference = cartItems[i].first;
        int quantity = cartItems[i].second;
        
        // Get product price
        QSqlQuery query;
        query.prepare("SELECT prix FROM produit WHERE reference = :reference");
        query.bindValue(":reference", reference);
        
        if (!query.exec() || !query.next()) {
            allProductsAdded = false;
            continue;
        }
        
        double prix = query.value(0).toDouble();
        
        // Add product to sale
        if (!newVente.ajouterProduitVente(idVente, reference, quantity, prix)) {
            allProductsAdded = false;
        }
    }
    
    if (!allProductsAdded) {
        QMessageBox::warning(this, "Avertissement", "Certains produits n'ont pas pu être ajoutés à la vente!");
    }
    
    QMessageBox::information(this, "Succès", "Vente enregistrée avec succès!");
    
    // Clear form and refresh table
    clearSaleForm();
    refreshSalesTable();
}

void SalesWindow::on_newSaleButton_clicked()
{
    clearSaleForm();
}

void SalesWindow::on_searchSalesLineEdit_textChanged(const QString &arg1)
{
    searchSales(arg1);
}

void SalesWindow::searchSales(const QString &searchText)
{
    if (searchText.isEmpty()) {
        refreshSalesTable();
        return;
    }
    
    // Delete old model if exists
    if (salesModel) {
        delete salesModel;
    }
    
    // Search sales in database
    salesModel = venteObj.rechercher(searchText);
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->resizeColumnsToContents();
}

void SalesWindow::on_dateFilterCheckBox_toggled(bool checked)
{
    ui->startDateEdit->setEnabled(checked);
    ui->endDateEdit->setEnabled(checked);
    
    if (checked) {
        filterSalesByDate();
    } else {
        refreshSalesTable();
    }
}

void SalesWindow::filterSalesByDate()
{
    QDate startDate = ui->startDateEdit->date();
    QDate endDate = ui->endDateEdit->date();
    
    // Delete old model if exists
    if (salesModel) {
        delete salesModel;
    }
    
    // Filter sales by date
    salesModel = venteObj.filtrerParDate(startDate, endDate);
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->resizeColumnsToContents();
}

void SalesWindow::on_startDateEdit_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    
    if (ui->dateFilterCheckBox->isChecked()) {
        filterSalesByDate();
    }
}

void SalesWindow::on_endDateEdit_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    
    if (ui->dateFilterCheckBox->isChecked()) {
        filterSalesByDate();
    }
}

void SalesWindow::on_salesButton_clicked()
{
    // Already in sales window, refresh
    refreshSalesTable();
}

void SalesWindow::on_pushButton_clicked()
{
    // Stock -> MainWindow
    MainWindow::getInstance();
    this->close();
}

void SalesWindow::on_pushButton_3_clicked()
{
    // Employes -> gestionemploye00
    gestionemploye00::getInstance();
    this->close();
}

void SalesWindow::on_pushButton_4_clicked()
{
    // Clients -> Gclient1
    Gclient1::getInstance();
    this->close();
}

void SalesWindow::on_pushButton_5_clicked()
{
    // Fournisseur -> FournisseurWindow
    FournisseurWindow::getInstance();
    this->close();
}

void SalesWindow::on_logoutButton_clicked()
{
    // Logout/Exit disabled: prevent application from closing
    QMessageBox::information(this, "Déconnexion", "La déconnexion est désactivée dans cette version.");
}

void SalesWindow::on_sortButton_clicked()
{
    sortSalesTable();
}

void SalesWindow::sortSalesTable()
{
    QString sortOption = ui->sortComboBox->currentText();
    
    // SQL query for sorting
    QString queryStr;
    
    if (sortOption == "ID (Croissant)") {
        queryStr = "SELECT * FROM vente ORDER BY id_vente ASC";
    } else if (sortOption == "ID (Décroissant)") {
        queryStr = "SELECT * FROM vente ORDER BY id_vente DESC";
    } else if (sortOption == "Date (Croissant)") {
        queryStr = "SELECT * FROM vente ORDER BY date_vente ASC";
    } else if (sortOption == "Date (Décroissant)") {
        queryStr = "SELECT * FROM vente ORDER BY date_vente DESC";
    } else if (sortOption == "Montant (Croissant)") {
        queryStr = "SELECT * FROM vente ORDER BY prix_ttc ASC";
    } else if (sortOption == "Montant (Décroissant)") {
        queryStr = "SELECT * FROM vente ORDER BY prix_ttc DESC";
    } else if (sortOption == "Client (A-Z)") {
        queryStr = "SELECT v.* FROM vente v "
                  "JOIN clients c ON v.id_client = c.id_client "
                  "ORDER BY c.nom ASC, c.prenom ASC";
    } else if (sortOption == "Client (Z-A)") {
        queryStr = "SELECT v.* FROM vente v "
                  "JOIN clients c ON v.id_client = c.id_client "
                  "ORDER BY c.nom DESC, c.prenom DESC";
    } else {
        // Default sort
        queryStr = "SELECT * FROM vente ORDER BY date_vente DESC";
    }
    
    // Delete old model if exists
    if (salesModel) {
        delete salesModel;
    }
    
    // Create new model with sorted data
    salesModel = new QSqlQueryModel();
    salesModel->setQuery(queryStr);
    
    // Set headers
    salesModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    salesModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Client"));
    salesModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Employé"));
    salesModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    salesModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix TTC"));
    salesModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix HT"));
    salesModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Remise"));
    salesModel->setHeaderData(7, Qt::Horizontal, QObject::tr("TVA"));
    salesModel->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    salesModel->setHeaderData(9, Qt::Horizontal, QObject::tr("Paiement"));
    salesModel->setHeaderData(10, Qt::Horizontal, QObject::tr("Mode"));
    salesModel->setHeaderData(11, Qt::Horizontal, QObject::tr("Livraison"));
    
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->resizeColumnsToContents();
}

void SalesWindow::on_modifySaleButton_clicked()
{
    // Check if a sale is selected
    if (!ui->salesTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une vente à modifier.");
        return;
    }
    
    // Get the selected sale ID
    int row = ui->salesTableView->selectionModel()->selectedRows().first().row();
    int saleId = salesModel->data(salesModel->index(row, 0)).toInt();
    
    // Get the sale details
    QSqlQuery query;
    query.prepare("SELECT * FROM vente WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", saleId);
    
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les détails de la vente.");
        return;
    }
    
    // Get the current values
    int idClient = query.value("id_client").toInt();
    int idEmploye = query.value("id_employe").toInt();
    QString statutVente = query.value("statut_vente").toString();
    QString statutPaiement = query.value("statut_paiement").toString();
    QString modePaiement = query.value("mode_paiement").toString();
    QDate dateLivraison = query.value("date_livraison").toDate();
    
    // Create a dialog for editing the sale
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier la vente #" + QString::number(saleId));
    dialog.setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    // Status combo box
    QHBoxLayout *statusLayout = new QHBoxLayout();
    QLabel *statusLabel = new QLabel("Statut de vente:", &dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems(QStringList() << "En cours" << "Complétée" << "Annulée" << "En attente");
    statusCombo->setCurrentText(statutVente);
    statusLayout->addWidget(statusLabel);
    statusLayout->addWidget(statusCombo);
    layout->addLayout(statusLayout);
    
    // Payment status combo box
    QHBoxLayout *paymentStatusLayout = new QHBoxLayout();
    QLabel *paymentStatusLabel = new QLabel("Statut de paiement:", &dialog);
    QComboBox *paymentStatusCombo = new QComboBox(&dialog);
    paymentStatusCombo->addItems(QStringList() << "Payé" << "Non payé" << "Partiellement payé" << "Remboursé");
    paymentStatusCombo->setCurrentText(statutPaiement);
    paymentStatusLayout->addWidget(paymentStatusLabel);
    paymentStatusLayout->addWidget(paymentStatusCombo);
    layout->addLayout(paymentStatusLayout);
    
    // Payment method combo box
    QHBoxLayout *paymentMethodLayout = new QHBoxLayout();
    QLabel *paymentMethodLabel = new QLabel("Mode de paiement:", &dialog);
    QComboBox *paymentMethodCombo = new QComboBox(&dialog);
    paymentMethodCombo->addItems(QStringList() << "Espèces" << "Carte de crédit" << "Carte de débit" << "Chèque" << "Virement bancaire" << "Assurance");
    paymentMethodCombo->setCurrentText(modePaiement);
    paymentMethodLayout->addWidget(paymentMethodLabel);
    paymentMethodLayout->addWidget(paymentMethodCombo);
    layout->addLayout(paymentMethodLayout);
    
    // Delivery date
    QHBoxLayout *deliveryDateLayout = new QHBoxLayout();
    QLabel *deliveryDateLabel = new QLabel("Date de livraison:", &dialog);
    QDateEdit *deliveryDateEdit = new QDateEdit(&dialog);
    deliveryDateEdit->setDate(dateLivraison);
    deliveryDateEdit->setCalendarPopup(true);
    deliveryDateLayout->addWidget(deliveryDateLabel);
    deliveryDateLayout->addWidget(deliveryDateEdit);
    layout->addLayout(deliveryDateLayout);
    
    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        // Get the full sale details to preserve other fields
        QSqlQuery fullSaleQuery;
        fullSaleQuery.prepare("SELECT * FROM vente WHERE id_vente = :id_vente");
        fullSaleQuery.bindValue(":id_vente", saleId);
        
        if (!fullSaleQuery.exec() || !fullSaleQuery.next()) {
            QMessageBox::critical(this, "Erreur", "Impossible de récupérer les détails complets de la vente.");
            return;
        }
        
        // Update the sale with new values
        Vente vente;
        vente.setId(saleId);
        vente.setIdClient(idClient);
        vente.setIdEmploye(idEmploye);
        vente.setDateVente(fullSaleQuery.value("date_vente").toDate());
        vente.setPrixTtc(fullSaleQuery.value("prix_ttc").toDouble());
        vente.setPrixHt(fullSaleQuery.value("prix_ht").toDouble());
        vente.setRemise(fullSaleQuery.value("remise").toDouble());
        vente.setTva(fullSaleQuery.value("tva").toDouble());
        vente.setStatutVente(statusCombo->currentText());
        vente.setStatutPaiement(paymentStatusCombo->currentText());
        vente.setModePaiement(paymentMethodCombo->currentText());
        vente.setDateLivraison(deliveryDateEdit->date());
        
        if (vente.modifier()) {
            QMessageBox::information(this, "Succès", "La vente a été modifiée avec succès.");
            refreshSalesTable();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de modifier la vente.");
        }
    }
}

void SalesWindow::on_deleteSaleButton_clicked()
{
    // Check if a sale is selected
    if (!ui->salesTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une vente à supprimer.");
        return;
    }
    
    // Get the selected sale ID
    int row = ui->salesTableView->selectionModel()->selectedRows().first().row();
    int saleId = salesModel->data(salesModel->index(row, 0)).toInt();
    
    // Ask for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", 
                                 "Êtes-vous sûr de vouloir supprimer la vente #" + QString::number(saleId) + " ?",
                                 QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Delete the sale
        Vente vente;
        if (vente.supprimer(saleId)) {
            QMessageBox::information(this, "Succès", "La vente a été supprimée avec succès.");
            refreshSalesTable();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer la vente.");
        }
    }
}