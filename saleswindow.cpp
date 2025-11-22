#include "saleswindow.h"
#include "ui_saleswindow.h"
#include <QShowEvent>
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include "WindowManager.h"
#include "salesstatistique.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QStandardItem>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QFileInfo>
#include <QMetaType>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

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
    currentEmployeId(0),
    savingAsDraft(false)
{
    ui->setupUi(this);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Ventes");
    
    // Setup models and tables
    setupModels();
    
    // Set current date for date filters
    ui->startDateEdit->setDate(QDate::currentDate().addDays(-30));
    ui->endDateEdit->setDate(QDate::currentDate());
    
    // Payment method combo box is populated in setupModels()
    
    // Update button labels
    ui->newSaleButton->setText("Enregistrer");
    
    // Connect signals and slots
    connect(ui->addProductButton, &QPushButton::clicked, this, &SalesWindow::on_addProductButton_clicked);
    connect(ui->removeProductButton, &QPushButton::clicked, this, &SalesWindow::on_removeProductButton_clicked);
    connect(ui->customerSearchButton, &QPushButton::clicked, this, &SalesWindow::on_customerSearchButton_clicked);
    connect(ui->productComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SalesWindow::on_productComboBox_currentIndexChanged);
    connect(ui->saveSaleButton, &QPushButton::clicked, this, &SalesWindow::on_saveSaleButton_clicked);
    connect(ui->newSaleButton, &QPushButton::clicked, this, &SalesWindow::on_registerSaleButton_clicked);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &SalesWindow::on_exportPdfButton_clicked);
    
    // Make logo clickable
    if (ui->topRightLogoLabel) {
        ui->topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        ui->topRightLogoLabel->installEventFilter(this);
        ui->topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
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

void SalesWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    // Refresh product combo box when window is shown to get latest products
    populateProductComboBox();
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
    ui->paymentMethodComboBox->addItem("Chèque");
    
    // Add modify, delete, and statistics buttons to the sales history tab
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
        
        // Create statistics button
        QPushButton *statisticsButton = new QPushButton("Statistiques", salesTabContent);
        statisticsButton->setObjectName("statisticsButton");
        statisticsButton->setStyleSheet("background-color: rgb(41, 102, 148); color: white; font-weight: bold;");
        buttonsLayout->addWidget(statisticsButton);
        
        // Add the buttons layout after the table view
        salesTabLayout->insertLayout(salesTabLayout->count() - 1, buttonsLayout);
        
        // Connect the buttons to their slots
        connect(modifyButton, &QPushButton::clicked, this, &SalesWindow::on_modifySaleButton_clicked);
        connect(deleteButton, &QPushButton::clicked, this, &SalesWindow::on_deleteSaleButton_clicked);
        connect(statisticsButton, &QPushButton::clicked, this, &SalesWindow::on_statisticsButton_clicked);
    }
    
    // Populate product selection combo box
    populateProductComboBox();
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
    ui->productComboBox->setCurrentIndex(0);
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->quantitySpinBox->setValue(1);
    ui->paymentMethodComboBox->setCurrentIndex(0);
    
    // Refresh product combo box to update stock availability
    populateProductComboBox();
    
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
    // Get selected product from combo box
    int productId = ui->productComboBox->currentData().toInt();
    
    if (productId <= 0) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un produit!");
        return;
    }
    
    QString productName = ui->productNameLineEdit->text();
    QString priceStr = ui->priceLineEdit->text();
    
    if (productName.isEmpty() || priceStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un produit valide!");
        return;
    }
    
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
            
            // Refresh product combo box to update stock availability
            populateProductComboBox();
            
            // Reset product selection
            ui->productComboBox->setCurrentIndex(0);
            
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
    
    // Reset product selection
    ui->productComboBox->setCurrentIndex(0);
    
    // Refresh product combo box to update stock availability
    populateProductComboBox();
    
    // Note: Quantity spinbox maximum will be updated when product is selected again
    // The maximum is set in on_productComboBox_currentIndexChanged() which considers cart items
    
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
    
    // Refresh product combo box to update stock availability
    populateProductComboBox();
    
    // Update quantity spinbox if the removed product is currently selected
    int currentProductId = ui->productComboBox->currentData().toInt();
    if (currentProductId == reference) {
        // Trigger the product selection change to update the quantity maximum
        on_productComboBox_currentIndexChanged(ui->productComboBox->currentIndex());
    }
    
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

void SalesWindow::populateProductComboBox()
{
    ui->productComboBox->clear();
    ui->productComboBox->addItem("Sélectionner un produit", 0);
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "⚠️ Database not connected in populateProductComboBox()";
        return;
    }
    
    // Get all products from database using direct query for better control
    QSqlQuery query(db);
    QString sql = "SELECT reference, designation, quantite, prix FROM produit ORDER BY reference";
    
    if (!query.exec(sql)) {
        qDebug() << "❌ Error with lowercase query:" << query.lastError().text();
        // Try uppercase table name
        query.clear();
        sql = "SELECT REFERENCE, DESIGNATION, QUANTITE, PRIX FROM PRODUIT ORDER BY REFERENCE";
        if (!query.exec(sql)) {
            qDebug() << "❌ Error with uppercase query:" << query.lastError().text();
            return;
        }
    }
    
    int productCount = 0;
    while (query.next()) {
        int reference = query.value(0).toInt();
        QString designation = query.value(1).toString();
        int quantite = query.value(2).toInt();
        double prix = query.value(3).toDouble();
        
        // Only show products that are available (quantite > 0)
        // Products with rupture de stock (quantite <= 0) are excluded
        if (quantite > 0) {
            QString displayText = QString("%1 - %2 (Stock: %3, Prix: %4)").arg(reference).arg(designation).arg(quantite).arg(prix, 0, 'f', 2);
            ui->productComboBox->addItem(displayText, reference);
            productCount++;
        }
    }
    
    qDebug() << "✅ Loaded" << productCount << "products into combo box";
}

void SalesWindow::on_productComboBox_currentIndexChanged(int index)
{
    if (index <= 0) {
        // First item is "Sélectionner un produit" or no selection
        ui->productNameLineEdit->clear();
        ui->priceLineEdit->clear();
        ui->quantitySpinBox->setMaximum(999);
        ui->quantitySpinBox->setValue(1);
        return;
    }
    
    int reference = ui->productComboBox->currentData().toInt();
    if (reference <= 0) return;
    
    // Get product details from database
    QSqlQuery query;
    query.prepare("SELECT reference, designation, prix, quantite FROM produit WHERE reference = :reference");
    query.bindValue(":reference", reference);
    
    if (query.exec() && query.next()) {
        QString designation = query.value(1).toString();
        double prix = query.value(2).toDouble();
        int stockDisponible = query.value(3).toInt();
        
        ui->productNameLineEdit->setText(designation);
        ui->priceLineEdit->setText(QString::number(prix, 'f', 2));
        
        // Calculate how much of this product is already in the cart
        int alreadyInCart = 0;
        for (int i = 0; i < cartItems.size(); ++i) {
            if (cartItems[i].first == reference) {
                alreadyInCart = cartItems[i].second;
                break;
            }
        }
        
        // Available stock = total stock - what's already in cart
        int availableStock = stockDisponible - alreadyInCart;
        
        // Set maximum quantity based on available stock (considering what's already in cart)
        if (availableStock > 0) {
            ui->quantitySpinBox->setMaximum(availableStock);
            ui->quantitySpinBox->setValue(1);
        } else {
            ui->quantitySpinBox->setMaximum(0);
            ui->quantitySpinBox->setValue(0);
            QMessageBox::information(this, "Information", 
                QString("Ce produit est déjà dans le panier avec la quantité maximale disponible.\nStock total: %1\nDéjà dans le panier: %2")
                .arg(stockDisponible).arg(alreadyInCart));
        }
    } else {
        ui->productNameLineEdit->clear();
        ui->priceLineEdit->clear();
        ui->quantitySpinBox->setMaximum(999);
        ui->quantitySpinBox->setValue(1);
    }
}


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
    
    // Start a transaction for the entire sale operation (VENTE + products)
    QSqlDatabase db = QSqlDatabase::database();
    bool inTransaction = false;
    if (db.driver()->hasFeature(QSqlDriver::Transactions)) {
        if (db.transaction()) {
            inTransaction = true;
            qDebug() << "Transaction démarrée pour la création complète de la vente (VENTE + produits)";
        } else {
            qDebug() << "⚠️ Impossible de démarrer une transaction, continuation sans transaction";
        }
    }
    
    // Use default values for now
    double discount = 0;
    QString saleStatus = savingAsDraft ? "En attente" : "Complétée";
    QString paymentStatus = savingAsDraft ? "Non payé" : "Payé";
    QDate deliveryDate = QDate::currentDate().addDays(1);
    
    // Check if there's a valid employee in the database
    QSqlQuery empQuery;
    QString empSql = "SELECT id_employe FROM employe";
    if (!empQuery.exec(empSql)) {
        qDebug() << "Erreur avec employe en minuscules:" << empQuery.lastError().text();
        empQuery.clear();
        empSql = "SELECT ID_EMPLOYE FROM EMPLOYE";
        if (!empQuery.exec(empSql)) {
            qDebug() << "Erreur avec EMPLOYE en majuscules:" << empQuery.lastError().text();
        }
    }
    int employeeId = 0; // Default to NULL (0)
    
    // Use the first employee found if any exist
    if (empQuery.next()) {
        employeeId = empQuery.value(0).toInt();
        qDebug() << "Employé trouvé, ID:" << employeeId;
    } else {
        qDebug() << "Aucun employé trouvé dans la base de données, la vente sera enregistrée sans employé";
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
        QString clientCheckSql = "SELECT COUNT(*) FROM clients";
        if (!clientQuery.exec(clientCheckSql)) {
            clientQuery.clear();
            clientCheckSql = "SELECT COUNT(*) FROM CLIENTS";
            clientQuery.exec(clientCheckSql);
        }
        int clientCount = 0;
        if (clientQuery.next()) {
            clientCount = clientQuery.value(0).toInt();
        }
        
        // Check if the specific client exists
        bool clientExists = false;
        if (currentClientId > 0) {
            QSqlQuery specificClientQuery;
            QString specificClientSql = "SELECT id_client FROM clients WHERE id_client = :id_client";
            specificClientQuery.prepare(specificClientSql);
            specificClientQuery.bindValue(":id_client", currentClientId);
            if (!specificClientQuery.exec()) {
                specificClientQuery.clear();
                specificClientSql = "SELECT ID_CLIENT FROM CLIENTS WHERE ID_CLIENT = :id_client";
                specificClientQuery.prepare(specificClientSql);
                specificClientQuery.bindValue(":id_client", currentClientId);
                specificClientQuery.exec();
            }
            clientExists = specificClientQuery.next();
        }
        
        // Provide specific error messages
        if (currentClientId <= 0) {
            QMessageBox::critical(this, "Erreur", "Veuillez sélectionner un client valide avant de créer une vente.");
        } else if (!clientExists) {
            QMessageBox::critical(this, "Erreur", 
                QString("Le client avec l'ID %1 n'existe pas dans la base de données.\nVeuillez vérifier l'ID du client.").arg(currentClientId));
        } else if (clientCount == 0) {
            QMessageBox::critical(this, "Erreur", "Aucun client n'existe dans la base de données. Veuillez d'abord ajouter un client.");
        } else if (employeeId > 0) {
            // Check if employee exists
            QSqlQuery empCheckQuery;
            QString empCheckSql = "SELECT id_employe FROM employe WHERE id_employe = :id_employe";
            empCheckQuery.prepare(empCheckSql);
            empCheckQuery.bindValue(":id_employe", employeeId);
            if (!empCheckQuery.exec()) {
                empCheckQuery.clear();
                empCheckSql = "SELECT ID_EMPLOYE FROM EMPLOYE WHERE ID_EMPLOYE = :id_employe";
                empCheckQuery.prepare(empCheckSql);
                empCheckQuery.bindValue(":id_employe", employeeId);
                empCheckQuery.exec();
            }
            if (!empCheckQuery.next()) {
                QMessageBox::critical(this, "Erreur", 
                    QString("L'employé avec l'ID %1 n'existe pas dans la base de données.\nLa vente sera enregistrée sans employé.").arg(employeeId));
                // Retry without employee
                newVente.setIdEmploye(0);
                if (!newVente.ajouter()) {
                    QString errorMsg = newVente.getLastError();
                    if (errorMsg.isEmpty()) {
                        errorMsg = "Erreur lors de l'enregistrement de la vente.\nVérifiez les logs pour plus de détails.";
                    }
                    QMessageBox::critical(this, "Erreur", errorMsg);
                    qDebug() << "❌ Échec de la création de la vente (sans employé) - Erreur:" << errorMsg;
                    return;
                }
            } else {
                QString errorMsg = newVente.getLastError();
                if (errorMsg.isEmpty()) {
                    errorMsg = "Erreur lors de l'enregistrement de la vente.\nVérifiez les logs pour plus de détails.";
                }
                QMessageBox::critical(this, "Erreur", errorMsg);
                qDebug() << "❌ Échec de la création de la vente - Erreur:" << errorMsg;
                return;
            }
        } else {
            // Try to add the sale and capture the error
            if (!newVente.ajouter()) {
                QString errorMsg = newVente.getLastError();
                if (errorMsg.isEmpty()) {
                    errorMsg = "Erreur lors de l'enregistrement de la vente.\nVérifiez les logs pour plus de détails.";
                }
                if (inTransaction) {
                    db.rollback();
                    qDebug() << "Transaction annulée - Échec de la création de la vente";
                }
                QMessageBox::critical(this, "Erreur", errorMsg);
                qDebug() << "❌ Échec de la création de la vente - Erreur:" << errorMsg;
                return;
            }
        }
    }
    
    int idVente = newVente.getId();
    
    if (idVente <= 0) {
        if (inTransaction) {
            db.rollback();
            qDebug() << "Transaction annulée - ID de vente invalide";
        }
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer l'ID de la vente créée. La vente n'a peut-être pas été enregistrée correctement.");
        qDebug() << "❌ ID de vente invalide après création:" << idVente;
        return;
    }
    
    qDebug() << "✅ Vente créée avec succès, ID:" << idVente;
    
    // Add products to sale - CRITICAL: This ensures all products are saved to contenir table
    // IMPORTANT: Re-validate stock availability before saving (stock may have changed since adding to cart)
    bool allProductsAdded = true;
    int productsAddedCount = 0;
    int productsFailedCount = 0;
    QStringList failedProducts;
    QStringList stockIssues;
    
    for (int i = 0; i < cartItems.size(); ++i) {
        int reference = cartItems[i].first;
        int quantity = cartItems[i].second;
        
        // Get product details: price, designation, and CURRENT stock availability
        QSqlQuery query;
        QString priceSql = "SELECT prix, designation, quantite FROM produit WHERE reference = :reference";
        query.prepare(priceSql);
        query.bindValue(":reference", reference);
        
        if (!query.exec()) {
            qDebug() << "Erreur avec produit en minuscules:" << query.lastError().text();
            query.clear();
            priceSql = "SELECT PRIX, DESIGNATION, QUANTITE FROM PRODUIT WHERE REFERENCE = :reference";
            query.prepare(priceSql);
            query.bindValue(":reference", reference);
            if (!query.exec()) {
                qDebug() << "Erreur avec PRODUIT en majuscules:" << query.lastError().text();
                allProductsAdded = false;
                productsFailedCount++;
                failedProducts << QString("Réf: %1 (Erreur de base de données)").arg(reference);
                continue;
            }
        }
        
        if (!query.next()) {
            qDebug() << "Produit avec référence" << reference << "non trouvé dans la base de données";
            allProductsAdded = false;
            productsFailedCount++;
            failedProducts << QString("Réf: %1 (Produit supprimé)").arg(reference);
            continue;
        }
        
        double prix = query.value(0).toDouble();
        QString designation = query.value(1).toString();
        int stockDisponible = query.value(2).toInt();
        
        qDebug() << "Vérification du produit - Réf:" << reference << "Désignation:" << designation 
                 << "Prix:" << prix << "Quantité demandée:" << quantity << "Stock disponible:" << stockDisponible;
        
        // CRITICAL: Re-validate stock availability before saving
        if (stockDisponible <= 0) {
            qDebug() << "❌ Produit" << reference << "est en rupture de stock (stock:" << stockDisponible << ")";
            allProductsAdded = false;
            productsFailedCount++;
            stockIssues << QString("%1 (Réf: %2) - Rupture de stock (Stock: %3)").arg(designation.isEmpty() ? "Produit inconnu" : designation).arg(reference).arg(stockDisponible);
            continue;
        }
        
        if (quantity > stockDisponible) {
            qDebug() << "❌ Stock insuffisant pour le produit" << reference << "- Demandé:" << quantity << "Disponible:" << stockDisponible;
            allProductsAdded = false;
            productsFailedCount++;
            stockIssues << QString("%1 (Réf: %2) - Stock insuffisant (Demandé: %3, Disponible: %4)").arg(designation.isEmpty() ? "Produit inconnu" : designation).arg(reference).arg(quantity).arg(stockDisponible);
            continue;
        }
        
        qDebug() << "✅ Stock validé - Ajout du produit - Réf:" << reference << "Désignation:" << designation << "Prix:" << prix << "Quantité:" << quantity;
        
        // Add product to sale in contenir table
        if (!newVente.ajouterProduitVente(idVente, reference, quantity, prix)) {
            qDebug() << "❌ Échec de l'ajout du produit" << reference << "à la vente" << idVente;
            allProductsAdded = false;
            productsFailedCount++;
            failedProducts << QString("%1 (Réf: %2) - Erreur lors de l'ajout").arg(designation.isEmpty() ? "Produit inconnu" : designation).arg(reference);
        } else {
            qDebug() << "✅ Produit" << reference << "ajouté avec succès à la vente" << idVente << "dans la table contenir";
            productsAddedCount++;
        }
    }
    
    // Commit or rollback transaction (this includes both VENTE and products)
    if (inTransaction) {
        if (allProductsAdded) {
            if (db.commit()) {
                qDebug() << "✅ Transaction validée - Vente et tous les produits ont été ajoutés";
            } else {
                qDebug() << "❌ Erreur lors du commit de la transaction:" << db.lastError().text();
                db.rollback();
                QMessageBox::critical(this, "Erreur", 
                    QString("Erreur lors de la validation de la transaction.\n%1\n\nLa vente et les produits n'ont pas été enregistrés.").arg(db.lastError().text()));
                return;
            }
        } else {
            qDebug() << "❌ Annulation de la transaction - Certains produits n'ont pas pu être ajoutés";
            db.rollback();
            qDebug() << "Transaction annulée - La vente et les produits n'ont pas été enregistrés";
            // Don't return here - we want to show the warning message below
        }
    }
    
    // Provide detailed feedback
    if (!allProductsAdded) {
        QString warningMsg = QString("Attention: %1 produit(s) n'ont pas pu être ajoutés à la vente #%2.\n\n").arg(productsFailedCount).arg(idVente);
        if (productsAddedCount > 0) {
            warningMsg += QString("%1 produit(s) ont été ajoutés avec succès.\n\n").arg(productsAddedCount);
        }
        
        // Separate stock issues from other errors for better clarity
        if (!stockIssues.isEmpty()) {
            warningMsg += "Problèmes de stock:\n" + stockIssues.join("\n") + "\n\n";
        }
        if (!failedProducts.isEmpty()) {
            warningMsg += "Autres erreurs:\n" + failedProducts.join("\n");
        }
        
        QMessageBox::warning(this, "Avertissement", warningMsg);
    } else {
        qDebug() << "✅ Tous les produits ont été ajoutés avec succès à la vente #" << idVente << "dans la table contenir";
    }
    
    if (productsAddedCount > 0) {
        QMessageBox::information(this, "Succès", 
            QString("Vente #%1 enregistrée avec succès!\n\n%2 produit(s) ajouté(s) à la vente.").arg(idVente).arg(productsAddedCount));
    } else {
        QString errorMsg = QString("La vente #%1 a été créée mais aucun produit n'a pu être ajouté.\n\n").arg(idVente);
        if (!stockIssues.isEmpty()) {
            errorMsg += "Raisons principales:\n" + stockIssues.join("\n") + "\n\n";
        }
        errorMsg += "Veuillez vérifier les produits dans le panier et leur disponibilité en stock.";
        QMessageBox::warning(this, "Avertissement", errorMsg);
    }
    
    // Clear form and refresh table
    clearSaleForm();
    
    // Refresh product combo box to update stock after sale
    populateProductComboBox();
    
    refreshSalesTable();
    
    // Refresh statistics window if it's open
    SalesStatistique::refreshIfOpen();
}

void SalesWindow::on_registerSaleButton_clicked()
{
    savingAsDraft = true;
    on_saveSaleButton_clicked();
    savingAsDraft = false;
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
    
    // Get the sale details - use explicit column names to avoid Oracle case sensitivity issues
    QSqlQuery query;
    query.prepare("SELECT id_vente, id_client, id_employe, date_vente, prix_ttc, prix_ht, "
                  "remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison "
                  "FROM vente WHERE id_vente = :id_vente");
    query.bindValue(":id_vente", saleId);
    
    if (!query.exec()) {
        QString errorMsg = query.lastError().text();
        qDebug() << "Error retrieving sale #" << saleId << ":" << errorMsg;
        QMessageBox::critical(this, "Erreur", 
            QString("Impossible de récupérer les détails de la vente #%1:\n%2").arg(saleId).arg(errorMsg));
        return;
    }
    
    if (!query.next()) {
        QMessageBox::critical(this, "Erreur", 
            QString("La vente #%1 n'existe pas dans la base de données.").arg(saleId));
        return;
    }
    
    // Get the current values using column indices (more reliable with Oracle)
    // Column order: id_vente(0), id_client(1), id_employe(2), date_vente(3), prix_ttc(4), 
    // prix_ht(5), remise(6), tva(7), statut_vente(8), statut_paiement(9), 
    // mode_paiement(10), date_livraison(11)
    int idClient = query.value(1).toInt();
    int idEmploye = query.value(2).toInt();
    QDate dateVente = query.value(3).toDate();
    double prixTtc = query.value(4).toDouble();
    double prixHt = query.value(5).toDouble();
    double remise = query.value(6).toDouble();
    double tva = query.value(7).toDouble();
    QString statutVente = query.value(8).toString();
    QString statutPaiement = query.value(9).toString();
    QString modePaiement = query.value(10).toString();
    QDate dateLivraison = query.value(11).toDate();
    
    qDebug() << "Sale #" << saleId << "loaded - Client:" << idClient << "Employee:" << idEmploye 
             << "Date:" << dateVente << "PrixTTC:" << prixTtc;
    
    // Create a dialog for editing the sale
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier la vente #" + QString::number(saleId));
    dialog.setMinimumWidth(420);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    
    // Client selection
    QComboBox *clientCombo = new QComboBox(&dialog);
    int clientIndex = -1;
    QSqlQuery clientsQuery;
    clientsQuery.prepare("SELECT id_client, nom, prenom FROM clients ORDER BY nom, prenom");
    if (clientsQuery.exec()) {
        while (clientsQuery.next()) {
            int clientId = clientsQuery.value(0).toInt();
            QString clientName = QString("%1 - %2 %3")
                .arg(clientId)
                .arg(clientsQuery.value(1).toString())
                .arg(clientsQuery.value(2).toString());
            clientCombo->addItem(clientName, clientId);
            if (clientId == idClient) {
                clientIndex = clientCombo->count() - 1;
            }
        }
    }
    if (clientCombo->count() == 0) {
        clientCombo->addItem("Aucun client disponible", idClient);
    }
    if (clientIndex >= 0) {
        clientCombo->setCurrentIndex(clientIndex);
    }
    formLayout->addRow("Client:", clientCombo);
    
    // Employee selection
    QComboBox *employeeCombo = new QComboBox(&dialog);
    employeeCombo->addItem("Aucun employé", 0);
    int employeeIndex = (idEmploye == 0) ? 0 : -1;
    QSqlQuery employeeQuery;
    employeeQuery.prepare("SELECT id_employe, nom, prenom FROM employe ORDER BY nom, prenom");
    if (employeeQuery.exec()) {
        while (employeeQuery.next()) {
            int employeeId = employeeQuery.value(0).toInt();
            QString employeeName = QString("%1 - %2 %3")
                .arg(employeeId)
                .arg(employeeQuery.value(1).toString())
                .arg(employeeQuery.value(2).toString());
            employeeCombo->addItem(employeeName, employeeId);
            if (employeeId == idEmploye) {
                employeeIndex = employeeCombo->count() - 1;
            }
        }
    }
    if (employeeIndex >= 0) {
        employeeCombo->setCurrentIndex(employeeIndex);
    }
    formLayout->addRow("Employé:", employeeCombo);
    
    // Sale and delivery dates
    QDateEdit *saleDateEdit = new QDateEdit(&dialog);
    saleDateEdit->setCalendarPopup(true);
    saleDateEdit->setDate(dateVente.isValid() ? dateVente : QDate::currentDate());
    formLayout->addRow("Date de vente:", saleDateEdit);
    
    QDateEdit *deliveryDateEdit = new QDateEdit(&dialog);
    deliveryDateEdit->setCalendarPopup(true);
    deliveryDateEdit->setDate(dateLivraison.isValid() ? dateLivraison : QDate::currentDate().addDays(1));
    formLayout->addRow("Date de livraison:", deliveryDateEdit);
    
    // Financial fields
    auto setupSpinBox = [](QDoubleSpinBox *spin, double value) {
        spin->setDecimals(2);
        spin->setMaximum(999999999.0);
        spin->setMinimum(0.0);
        spin->setValue(value);
    };
    
    QDoubleSpinBox *prixHtSpin = new QDoubleSpinBox(&dialog);
    setupSpinBox(prixHtSpin, prixHt);
    formLayout->addRow("Prix HT:", prixHtSpin);
    
    QDoubleSpinBox *tvaSpin = new QDoubleSpinBox(&dialog);
    setupSpinBox(tvaSpin, tva);
    formLayout->addRow("TVA:", tvaSpin);
    
    QDoubleSpinBox *remiseSpin = new QDoubleSpinBox(&dialog);
    setupSpinBox(remiseSpin, remise);
    formLayout->addRow("Remise:", remiseSpin);
    
    QDoubleSpinBox *prixTtcSpin = new QDoubleSpinBox(&dialog);
    setupSpinBox(prixTtcSpin, prixTtc);
    formLayout->addRow("Prix TTC:", prixTtcSpin);
    
    // Sale status
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems(QStringList() << "En cours" << "Complétée" << "Annulée" << "En attente");
    int statusIndex = statusCombo->findText(statutVente);
    if (statusIndex >= 0) statusCombo->setCurrentIndex(statusIndex);
    formLayout->addRow("Statut de vente:", statusCombo);
    
    // Payment status
    QComboBox *paymentStatusCombo = new QComboBox(&dialog);
    paymentStatusCombo->addItems(QStringList() << "Payé" << "Non payé" << "Partiellement payé" << "Remboursé");
    int paymentStatusIndex = paymentStatusCombo->findText(statutPaiement);
    if (paymentStatusIndex >= 0) paymentStatusCombo->setCurrentIndex(paymentStatusIndex);
    formLayout->addRow("Statut de paiement:", paymentStatusCombo);
    
    // Payment method
    QComboBox *paymentMethodCombo = new QComboBox(&dialog);
    paymentMethodCombo->addItems(QStringList()
                                 << "Espèces"
                                 << "Carte de crédit"
                                 << "Chèque");
    int paymentMethodIndex = paymentMethodCombo->findText(modePaiement);
    if (paymentMethodIndex >= 0) {
        paymentMethodCombo->setCurrentIndex(paymentMethodIndex);
    }
    formLayout->addRow("Mode de paiement:", paymentMethodCombo);
    
    layout->addLayout(formLayout);
    
    // Add button to reload sale into new sale form
    QPushButton *reloadButton = new QPushButton("Recharger dans Panier", &dialog);
    reloadButton->setStyleSheet("background-color: #55aaff; color: black; padding: 8px; font-weight: bold;");
    layout->addWidget(reloadButton);
    
    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    // Connect reload button - use a custom return code to distinguish from OK
    bool reloadRequested = false;
    connect(reloadButton, &QPushButton::clicked, [&dialog, &reloadRequested]() {
        reloadRequested = true;
        dialog.done(QDialog::Accepted + 1);  // Use custom return code
    });
    
    // Show the dialog
    int result = dialog.exec();
    
    // If reload was requested, load sale into new sale form and return
    if (reloadRequested) {
        loadSaleIntoNewSaleForm(saleId);
        return;
    }
    
    if (result == QDialog::Accepted) {
        // Update the sale with new values
        Vente vente;
        vente.setId(saleId);
        vente.setIdClient(clientCombo->currentData().toInt());
        vente.setIdEmploye(employeeCombo->currentData().toInt());
        vente.setDateVente(saleDateEdit->date());
        vente.setPrixTtc(prixTtcSpin->value());
        vente.setPrixHt(prixHtSpin->value());
        vente.setRemise(remiseSpin->value());
        vente.setTva(tvaSpin->value());
        vente.setStatutVente(statusCombo->currentText());
        vente.setStatutPaiement(paymentStatusCombo->currentText());
        vente.setModePaiement(paymentMethodCombo->currentText());
        vente.setDateLivraison(deliveryDateEdit->date());
        
        qDebug() << "Updating sale #" << saleId << "with values:";
        qDebug() << "  Client:" << vente.getIdClient() << "Employee:" << vente.getIdEmploye();
        qDebug() << "  Date:" << vente.getDateVente() << "PrixTTC:" << vente.getPrixTtc();
        qDebug() << "  Statut:" << vente.getStatutVente() << "Paiement:" << vente.getStatutPaiement();
        
        if (vente.modifier()) {
            QMessageBox::information(this, "Succès", 
                QString("La vente #%1 a été modifiée avec succès.").arg(saleId));
            refreshSalesTable();
            // Refresh statistics window if it's open
            SalesStatistique::refreshIfOpen();
        } else {
            QMessageBox::critical(this, "Erreur", 
                QString("Impossible de modifier la vente #%1.\nVérifiez les logs pour plus de détails.").arg(saleId));
        }
    }
}

void SalesWindow::on_statisticsButton_clicked()
{
    // Use singleton pattern to reuse existing window or create new one
    SalesStatistique::getInstance(this);
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
            // Refresh statistics window if it's open
            SalesStatistique::refreshIfOpen();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer la vente.");
        }
    }
}

void SalesWindow::on_exportPdfButton_clicked()
{
    exportSalesToPdf();
}

void SalesWindow::exportSalesToPdf()
{
    // Check if there are any sales to export
    if (!salesModel || salesModel->rowCount() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucune vente à exporter.");
        return;
    }
    
    // Get file path for saving PDF
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Exporter les ventes en PDF", 
        QString("factures_%1.pdf").arg(QDate::currentDate().toString("yyyy-MM-dd")),
        "PDF Files (*.pdf)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    // Ensure .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }
    
    // Check if file exists and can be written
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists() && !fileInfo.isWritable()) {
        QMessageBox::critical(this, "Erreur", "Le fichier existe déjà et ne peut pas être modifié.\nVeuillez choisir un autre nom ou fermer le fichier s'il est ouvert.");
        return;
    }
    
    // Create PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    // Create painter
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Check if PDF writer is valid
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.\nVérifiez que le fichier n'est pas ouvert dans une autre application.");
        return;
    }
    
    // Company information (you can customize these)
    QString companyName = "Smart Optical Store";
    QString companyAddress = "123 Rue Principale, Tunis, Tunisie";
    QString companyPhone = "+216 12 345 678";
    QString companyEmail = "contact@smartopticalstore.com";
    
    // Page dimensions (in pixels)
    int pageWidth = pdfWriter.width();
    int margin = 60;
    int yPos = margin;
    
    // Setup fonts
    QFont titleFont("Arial", 24, QFont::Bold);
    QFont headerFont("Arial", 11, QFont::Bold);
    QFont normalFont("Arial", 9);
    QFont smallFont("Arial", 8);
    QFont tableHeaderFont("Arial", 9, QFont::Bold);
    QFont tableFont("Arial", 9);
    
    // Process each sale
    for (int row = 0; row < salesModel->rowCount(); ++row) {
        if (row > 0) {
            pdfWriter.newPage();
            yPos = margin;
        }
        
        // Get sale data with error checking
        QModelIndex idx;
        int saleId = 0;
        QString clientName = "";
        QDate saleDateObj;
        double prixTTCval = 0.0;
        double prixHTval = 0.0;
        double tvaVal = 0.0;
        double remiseVal = 0.0;
        QString statutPaiement = "";
        QString modePaiement = "";
        QDate dateLivraisonObj;
        
        // Safely get data from model
        if (row >= 0 && row < salesModel->rowCount()) {
            idx = salesModel->index(row, 0);
            if (idx.isValid()) saleId = salesModel->data(idx).toInt();
            
            idx = salesModel->index(row, 1);
            if (idx.isValid()) clientName = salesModel->data(idx).toString();
            
            idx = salesModel->index(row, 3);
            if (idx.isValid()) {
                QVariant dateVar = salesModel->data(idx);
                if (dateVar.typeId() == QMetaType::QDate) {
                    saleDateObj = dateVar.toDate();
                } else {
                    QString dateStr = dateVar.toString();
                    saleDateObj = QDate::fromString(dateStr, "yyyy-MM-dd");
                    if (!saleDateObj.isValid()) {
                        saleDateObj = QDate::fromString(dateStr, Qt::ISODate);
                    }
                }
            }
            
            idx = salesModel->index(row, 4);
            if (idx.isValid()) {
                QVariant priceVar = salesModel->data(idx);
                QString priceStr = priceVar.toString();
                priceStr.remove(" DT");
                prixTTCval = priceVar.toDouble();
                if (prixTTCval == 0.0) prixTTCval = priceStr.toDouble();
            }
            
            idx = salesModel->index(row, 5);
            if (idx.isValid()) {
                QVariant priceVar = salesModel->data(idx);
                QString priceStr = priceVar.toString();
                priceStr.remove(" DT");
                prixHTval = priceVar.toDouble();
                if (prixHTval == 0.0) prixHTval = priceStr.toDouble();
            }
            
            idx = salesModel->index(row, 6);
            if (idx.isValid()) {
                QVariant priceVar = salesModel->data(idx);
                QString priceStr = priceVar.toString();
                priceStr.remove(" DT");
                remiseVal = priceVar.toDouble();
                if (remiseVal == 0.0) remiseVal = priceStr.toDouble();
            }
            
            idx = salesModel->index(row, 7);
            if (idx.isValid()) {
                QVariant priceVar = salesModel->data(idx);
                QString priceStr = priceVar.toString();
                priceStr.remove(" DT");
                tvaVal = priceVar.toDouble();
                if (tvaVal == 0.0) tvaVal = priceStr.toDouble();
            }
            
            idx = salesModel->index(row, 9);
            if (idx.isValid()) statutPaiement = salesModel->data(idx).toString();
            
            idx = salesModel->index(row, 10);
            if (idx.isValid()) modePaiement = salesModel->data(idx).toString();
            
            idx = salesModel->index(row, 11);
            if (idx.isValid()) {
                QVariant dateVar = salesModel->data(idx);
                if (dateVar.typeId() == QMetaType::QDate) {
                    dateLivraisonObj = dateVar.toDate();
                } else {
                    QString dateStr = dateVar.toString();
                    if (!dateStr.isEmpty() && dateStr != "Invalid") {
                        dateLivraisonObj = QDate::fromString(dateStr, "yyyy-MM-dd");
                        if (!dateLivraisonObj.isValid()) {
                            dateLivraisonObj = QDate::fromString(dateStr, Qt::ISODate);
                        }
                    }
                }
            }
        }
        
        // Skip if invalid sale ID
        if (saleId <= 0) {
            qDebug() << "Skipping invalid sale at row" << row;
            continue;
        }
        
        // Get client details
        QSqlQuery clientQuery;
        clientQuery.prepare("SELECT c.nom, c.prenom, c.email, c.adresse, c.telephone "
                           "FROM clients c "
                           "JOIN vente v ON c.id_client = v.id_client "
                           "WHERE v.id_vente = :id_vente");
        clientQuery.bindValue(":id_vente", saleId);
        QString clientFullName = clientName.isEmpty() ? "Client inconnu" : clientName;
        QString clientEmail = "";
        QString clientAddress = "";
        QString clientPhone = "";
        if (clientQuery.exec() && clientQuery.next()) {
            QString nom = clientQuery.value(0).toString();
            QString prenom = clientQuery.value(1).toString();
            if (!nom.isEmpty() || !prenom.isEmpty()) {
                clientFullName = "M. " + nom + " " + prenom; // Format: M. NOM PRENOM
            }
            clientEmail = clientQuery.value(2).toString();
            clientAddress = clientQuery.value(3).toString();
            clientPhone = clientQuery.value(4).toString();
        }
        
        // ===== HEADER SECTION =====
        // Top bar
        painter.setPen(QPen(QColor(50, 50, 50), 2));
        painter.setBrush(QColor(240, 240, 240));
        painter.drawRect(0, 0, pageWidth, 80);
        
        // Company name and logo area (left)
        painter.setPen(Qt::black);
        painter.setFont(headerFont);
        painter.drawText(margin, 20, pageWidth / 2 - margin, 30, Qt::AlignLeft | Qt::AlignVCenter, companyName);
        painter.setFont(smallFont);
        painter.drawText(margin, 45, pageWidth / 2 - margin, 30, Qt::AlignLeft | Qt::AlignVCenter, companyAddress);
        
        // Invoice title and details (right)
        painter.setFont(titleFont);
        painter.drawText(pageWidth / 2, 15, pageWidth / 2 - margin, 35, Qt::AlignRight | Qt::AlignTop, "FACTURE");
        
        painter.setFont(normalFont);
        // Format sale date
        QString formattedSaleDate = saleDateObj.isValid() ? saleDateObj.toString("dd/MM/yyyy") : QDate::currentDate().toString("dd/MM/yyyy");
        painter.drawText(pageWidth / 2, 45, pageWidth / 2 - margin, 15, Qt::AlignRight | Qt::AlignTop, 
                        "DATE: " + formattedSaleDate);
        // Format delivery date (échéance)
        if (dateLivraisonObj.isValid()) {
            painter.drawText(pageWidth / 2, 60, pageWidth / 2 - margin, 15, Qt::AlignRight | Qt::AlignTop, 
                            "ÉCHÉANCE: " + dateLivraisonObj.toString("dd/MM/yyyy"));
        }
        painter.drawText(pageWidth / 2, 75, pageWidth / 2 - margin, 15, Qt::AlignRight | Qt::AlignTop, 
                        "FACTURE N°: " + QString::number(saleId));
        
        yPos = 100;
        
        // ===== SENDER AND RECIPIENT SECTION =====
        // Sender (Company) - Left side
        painter.setFont(headerFont);
        painter.drawText(margin, yPos, pageWidth / 2 - margin - 20, 20, Qt::AlignLeft, "ÉMETTEUR:");
        painter.setFont(normalFont);
        painter.drawText(margin, yPos + 20, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, companyPhone);
        painter.drawText(margin, yPos + 35, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, companyEmail);
        painter.drawText(margin, yPos + 50, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, companyAddress);
        
        // Recipient (Client) - Right side
        painter.setFont(headerFont);
        painter.drawText(pageWidth / 2 + 20, yPos, pageWidth / 2 - margin - 20, 20, Qt::AlignLeft, "DESTINATAIRE:");
        painter.setFont(normalFont);
        painter.drawText(pageWidth / 2 + 20, yPos + 20, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, clientFullName);
        if (!clientEmail.isEmpty()) {
            painter.drawText(pageWidth / 2 + 20, yPos + 35, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, clientEmail);
        }
        if (!clientAddress.isEmpty()) {
            painter.drawText(pageWidth / 2 + 20, yPos + 50, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, clientAddress);
        }
        if (!clientPhone.isEmpty()) {
            painter.drawText(pageWidth / 2 + 20, yPos + 65, pageWidth / 2 - margin - 20, 15, Qt::AlignLeft, clientPhone);
        }
        
        yPos += 100;
        
        // ===== PRODUCTS TABLE =====
        // Table header background
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(230, 230, 230));
        painter.drawRect(margin, yPos, pageWidth - 2 * margin, 30);
        
        // Table headers
        painter.setPen(Qt::black);
        painter.setFont(tableHeaderFont);
        int colWidth1 = (pageWidth - 2 * margin) * 0.40; // Description
        int colWidth2 = (pageWidth - 2 * margin) * 0.20; // Prix Unitaire
        int colWidth3 = (pageWidth - 2 * margin) * 0.15; // Quantité
        int colWidth4 = (pageWidth - 2 * margin) * 0.25; // Total
        
        painter.drawText(margin + 10, yPos, colWidth1 - 10, 30, Qt::AlignLeft | Qt::AlignVCenter, "Description:");
        painter.drawText(margin + colWidth1 + 10, yPos, colWidth2 - 10, 30, Qt::AlignRight | Qt::AlignVCenter, "Prix Unitaire:");
        painter.drawText(margin + colWidth1 + colWidth2 + 10, yPos, colWidth3 - 10, 30, Qt::AlignCenter | Qt::AlignVCenter, "Quantité:");
        painter.drawText(margin + colWidth1 + colWidth2 + colWidth3 + 10, yPos, colWidth4 - 10, 30, Qt::AlignRight | Qt::AlignVCenter, "Total:");
        
        yPos += 30;
        
        // Get products for this sale
        QSqlQueryModel* productsModel = venteObj.afficherProduitsVente(saleId);
        
        // Draw table rows
        painter.setFont(tableFont);
        if (productsModel && productsModel->rowCount() > 0) {
            for (int pRow = 0; pRow < productsModel->rowCount(); ++pRow) {
                QModelIndex pIdx;
                QString designation = "";
                double prixUnitaire = 0.0;
                int quantite = 0;
                double total = 0.0;
                
                pIdx = productsModel->index(pRow, 1);
                if (pIdx.isValid()) designation = productsModel->data(pIdx).toString();
                
                pIdx = productsModel->index(pRow, 2);
                if (pIdx.isValid()) prixUnitaire = productsModel->data(pIdx).toDouble();
                
                pIdx = productsModel->index(pRow, 3);
                if (pIdx.isValid()) quantite = productsModel->data(pIdx).toInt();
                
                pIdx = productsModel->index(pRow, 4);
                if (pIdx.isValid()) {
                    total = productsModel->data(pIdx).toDouble();
                    // If total is 0, calculate it
                    if (total == 0.0 && prixUnitaire > 0 && quantite > 0) {
                        total = prixUnitaire * quantite;
                    }
                }
                
                if (designation.isEmpty()) designation = "Produit inconnu";
                
                // Draw row border
                painter.setPen(QPen(QColor(200, 200, 200), 1));
                painter.drawLine(margin, yPos, pageWidth - margin, yPos);
                
                // Draw product data
                painter.setPen(Qt::black);
                painter.drawText(margin + 10, yPos, colWidth1 - 10, 25, Qt::AlignLeft | Qt::AlignVCenter, designation);
                painter.drawText(margin + colWidth1 + 10, yPos, colWidth2 - 10, 25, Qt::AlignRight | Qt::AlignVCenter, 
                                QString::number(prixUnitaire, 'f', 2) + " DT");
                painter.drawText(margin + colWidth1 + colWidth2 + 10, yPos, colWidth3 - 10, 25, Qt::AlignCenter | Qt::AlignVCenter, 
                                QString::number(quantite));
                painter.drawText(margin + colWidth1 + colWidth2 + colWidth3 + 10, yPos, colWidth4 - 10, 25, Qt::AlignRight | Qt::AlignVCenter, 
                                QString::number(total, 'f', 2) + " DT");
                
                yPos += 25;
            }
        } else {
            // No products found - draw a message
            painter.setPen(QPen(QColor(200, 200, 200), 1));
            painter.drawLine(margin, yPos, pageWidth - margin, yPos);
            painter.setPen(Qt::black);
            painter.drawText(margin + 10, yPos, pageWidth - 2 * margin - 10, 25, Qt::AlignLeft | Qt::AlignVCenter, 
                            "Aucun produit trouvé pour cette vente");
            yPos += 25;
        }
        
        if (productsModel) {
            delete productsModel;
            productsModel = nullptr;
        }
        
        // Draw bottom border of table
        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.drawLine(margin, yPos, pageWidth - margin, yPos);
        
        yPos += 20;
        
        // ===== SUMMARY SECTION =====
        // Summary on the right
        int summaryX = pageWidth - margin - colWidth4;
        int summaryWidth = colWidth4;
        
        painter.setFont(tableHeaderFont);
        painter.setPen(Qt::black);
        
        // TOTAL HT
        painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignLeft, "TOTAL HT:");
        painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignRight, QString::number(prixHTval, 'f', 2) + " DT");
        yPos += 20;
        
        // TVA
        painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignLeft, "TVA 19%:");
        painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignRight, QString::number(tvaVal, 'f', 2) + " DT");
        yPos += 20;
        
        // REMISE
        if (remiseVal > 0) {
            painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignLeft, "REMISE:");
            painter.drawText(summaryX, yPos, summaryWidth - 10, 20, Qt::AlignRight, "-" + QString::number(remiseVal, 'f', 2) + " DT");
            yPos += 20;
        }
        
        // TOTAL TTC (bold and larger)
        painter.setFont(headerFont);
        painter.drawText(summaryX, yPos, summaryWidth - 10, 25, Qt::AlignLeft, "TOTAL TTC:");
        painter.drawText(summaryX, yPos, summaryWidth - 10, 25, Qt::AlignRight, QString::number(prixTTCval, 'f', 2) + " DT");
        yPos += 30;
        
        // ===== PAYMENT INFORMATION =====
        painter.setFont(headerFont);
        painter.drawText(margin, yPos, pageWidth / 2 - margin, 20, Qt::AlignLeft, "RÈGLEMENT:");
        painter.setFont(normalFont);
        if (!modePaiement.isEmpty()) {
            painter.drawText(margin, yPos + 20, pageWidth / 2 - margin, 15, Qt::AlignLeft, "Par " + modePaiement + ":");
        }
        if (!statutPaiement.isEmpty()) {
            painter.drawText(margin, yPos + 35, pageWidth / 2 - margin, 15, Qt::AlignLeft, "Statut: " + statutPaiement);
        }
        
        yPos += 60;
        
        // ===== FOOTER =====
        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.drawLine(margin, yPos, pageWidth - margin, yPos);
        yPos += 10;
        
        painter.setFont(smallFont);
        painter.setPen(QColor(100, 100, 100));
        QString footerText = "En cas de retard de paiement, et conformément au code de commerce, "
                            "une indemnité calculée à trois fois le taux d'intérêt légal ainsi qu'un "
                            "frais de recouvrement de 40 dinars sont exigibles. "
                            "Conditions générales de vente consultables sur le site: www.smartopticalstore.com";
        QRect footerRect(margin, yPos, pageWidth - 2 * margin, 40);
        painter.drawText(footerRect, Qt::TextWordWrap, footerText);
    }
    
    painter.end();
    
    QMessageBox::information(this, "Succès", 
        QString("Les factures ont été exportées avec succès vers:\n%1").arg(fileName));
}

bool SalesWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->topRightLogoLabel && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            on_logoClicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void SalesWindow::on_logoClicked()
{
    DashboardWindow::getInstance();
    this->close();
}

void SalesWindow::loadSaleIntoNewSaleForm(int saleId)
{
    // Switch to the "Nouvelle Vente" tab (index 0)
    ui->tabWidget->setCurrentIndex(0);
    
    // Clear the current form
    clearSaleForm();
    
    // Get sale details from database
    QSqlQuery saleQuery;
    saleQuery.prepare("SELECT * FROM vente WHERE id_vente = :id_vente");
    saleQuery.bindValue(":id_vente", saleId);
    
    if (!saleQuery.exec() || !saleQuery.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les détails de la vente.");
        return;
    }
    
    // Get sale data
    int idClient = saleQuery.value("id_client").toInt();
    QString modePaiement = saleQuery.value("mode_paiement").toString();
    
    // Set customer information
    if (idClient > 0) {
        QSqlQuery clientQuery;
        clientQuery.prepare("SELECT id_client, nom, prenom FROM clients WHERE id_client = :id_client");
        clientQuery.bindValue(":id_client", idClient);
        
        if (clientQuery.exec() && clientQuery.next()) {
            currentClientId = idClient;
            QString nom = clientQuery.value(1).toString();
            QString prenom = clientQuery.value(2).toString();
            
            ui->customerIdLineEdit->setText(QString::number(idClient));
            ui->customerNameLineEdit->setText(nom + " " + prenom);
        }
    }
    
    // Set payment method
    if (!modePaiement.isEmpty()) {
        int paymentIndex = ui->paymentMethodComboBox->findText(modePaiement);
        if (paymentIndex >= 0) {
            ui->paymentMethodComboBox->setCurrentIndex(paymentIndex);
        }
    }
    
    // Load products from the sale into the cart using direct query
    qDebug() << "Loading sale #" << saleId << "into cart...";
    
    // Use direct query instead of QSqlQueryModel for better reliability
    QSqlQuery query;
    query.prepare("SELECT c.reference, p.designation, c.prix_unitaire, c.quantite, "
                  "(c.prix_unitaire * c.quantite) AS total "
                  "FROM contenir c "
                  "LEFT JOIN produit p ON c.reference = p.reference "
                  "WHERE c.id_vente = :id_vente");
    query.bindValue(":id_vente", saleId);
    
    if (!query.exec()) {
        QString errorMsg = query.lastError().text();
        qDebug() << "Query error for sale #" << saleId << ":" << errorMsg;
        QMessageBox::critical(this, "Erreur", 
            QString("Erreur lors de la récupération des produits pour la vente #%1:\n%2").arg(saleId).arg(errorMsg));
        return;
    }
    
    // Clear cart first
    cartModel->removeRows(0, cartModel->rowCount());
    cartItems.clear();
    
    int productsAdded = 0;
    int rowCount = 0;
    
    // Process each product from the query
    while (query.next()) {
        rowCount++;
        
        int reference = query.value(0).toInt();
        QString designation = query.value(1).toString();
        double prix = query.value(2).toDouble();
        int quantite = query.value(3).toInt();
        double total = query.value(4).toDouble();
        
        // Handle deleted products
        if (designation.isEmpty() || designation.isNull()) {
            designation = QString("Produit supprimé (Ref: %1)").arg(reference);
        }
        
        qDebug() << "Sale #" << saleId << "- Row" << rowCount << "- Ref:" << reference 
                 << "Designation:" << designation << "Prix:" << prix << "Qty:" << quantite << "Total:" << total;
        
        // Validate data
        if (reference <= 0) {
            qDebug() << "Sale #" << saleId << "- Skipping row" << rowCount << "- invalid reference:" << reference;
            continue;
        }
        
        if (quantite <= 0) {
            qDebug() << "Sale #" << saleId << "- Skipping row" << rowCount << "- invalid quantity:" << quantite;
            continue;
        }
        
        // Calculate total if not provided or zero
        if (total == 0.0 && prix > 0 && quantite > 0) {
            total = prix * quantite;
        }
        
        // Add product to cart model
        QList<QStandardItem*> cartRow;
        cartRow << new QStandardItem(QString::number(reference));
        cartRow << new QStandardItem(designation);
        cartRow << new QStandardItem(QString("%1 DT").arg(prix, 0, 'f', 2));
        cartRow << new QStandardItem(QString::number(quantite));
        cartRow << new QStandardItem(QString("%1 DT").arg(total, 0, 'f', 2));
        
        cartModel->appendRow(cartRow);
        
        // Add to cart items list
        cartItems.append(qMakePair(reference, quantite));
        productsAdded++;
    }
    
    qDebug() << "Sale #" << saleId << "- Query returned" << rowCount << "rows, added" << productsAdded << "products to cart";
    
    ui->cartTableView->resizeColumnsToContents();
    updateTotals();
    
    if (productsAdded > 0) {
        QMessageBox::information(this, "Succès", 
            QString("La vente #%1 a été chargée dans le panier.\n%2 produit(s) ajouté(s).\nVous pouvez maintenant modifier les produits.").arg(saleId).arg(productsAdded));
    } else {
        // Check if there are any products in contenir table for this sale
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM contenir WHERE id_vente = :id_vente");
        checkQuery.bindValue(":id_vente", saleId);
        
        int count = 0;
        if (checkQuery.exec() && checkQuery.next()) {
            count = checkQuery.value(0).toInt();
            qDebug() << "Sale #" << saleId << "- Found" << count << "products in contenir table";
        }
        
        if (count > 0) {
            QMessageBox::warning(this, "Avertissement", 
                QString("La vente #%1 contient %2 produit(s) dans la base de données mais aucun produit valide n'a pu être chargé.\n\n"
                       "Vérifiez que les produits existent et ont des quantités valides.").arg(saleId).arg(count));
        } else {
            QMessageBox::warning(this, "Avertissement", 
                QString("Aucun produit trouvé pour la vente #%1 dans la table contenir.").arg(saleId));
        }
    }
}