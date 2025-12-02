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
#include "promomanager.h"
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
#include <QTimer>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPen>
#include <QMap>
#include <QBrush>
#include <QRect>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QDate>
#include <QAbstractItemView>
#include <QRegularExpression>

namespace {
QString buildBaseSalesQuery()
{
    return QStringLiteral(
        "SELECT v.id_vente, "
        "       c.nom || ' ' || c.prenom AS client, "
        "       e.nom || ' ' || e.prenom AS employe, "
        "       v.date_vente, "
        "       v.prix_ttc, "
        "       v.prix_ht, "
        "       v.remise, "
        "       v.tva, "
        "       v.statut_vente, "
        "       v.statut_paiement, "
        "       v.mode_paiement, "
        "       v.date_livraison "
        "FROM vente v "
        "LEFT JOIN clients c ON v.id_client = c.id_client "
        "LEFT JOIN employe e ON v.id_employe = e.id_employe ");
}
}

// Initialize static instance pointer
SalesWindow* SalesWindow::instance = nullptr;

SalesWindow* SalesWindow::getInstance(const QString &role, QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new SalesWindow(role, parent);
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

SalesWindow::SalesWindow(const QString &role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesWindow),
    cartModel(nullptr),
    salesModel(nullptr),
    currentClientId(0),
    currentEmployeId(0),
    savingAsDraft(false),
    loyaltyDiscountPercent(0.0),
    promoCodeDiscountPercent(0.0),
    currentPromoCode(""),
    promoManagerOpen(false),
    exportDialogOpen(false)
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
    connect(ui->applyPromoButton, &QPushButton::clicked, this, &SalesWindow::on_applyPromoButton_clicked);
    
    // Make logo clickable
    if (ui->topRightLogoLabel) {
        ui->topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        ui->topRightLogoLabel->installEventFilter(this);
        ui->topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Tableau de bord navigation
    // Stock button
    if (role == "admin" || role == "stock") {
        connect(ui->pushButton, &QPushButton::clicked, this, &SalesWindow::on_pushButton_clicked);   // Stock
    } else {
        ui->pushButton->setEnabled(false);
    }
    
    // Ventes button (self)
    if (role == "admin" || role == "vente") {
        connect(ui->pushButton_2, &QPushButton::clicked, this, &SalesWindow::on_salesButton_clicked);  // Ventes (self)
    } else {
        ui->pushButton_2->setEnabled(false);
    }
    
    // Employes button
    if (role == "admin" || role == "employe") {
        connect(ui->pushButton_3, &QPushButton::clicked, this, &SalesWindow::on_pushButton_3_clicked); // Employes
    } else {
        ui->pushButton_3->setEnabled(false);
    }
    
    // Clients button
    if (role == "admin" || role == "client") {
        connect(ui->pushButton_4, &QPushButton::clicked, this, &SalesWindow::on_pushButton_4_clicked); // Clients
    } else {
        ui->pushButton_4->setEnabled(false);
    }
    
    // Fournisseur button
    if (role == "admin" || role == "fournisseur") {
        connect(ui->pushButton_5, &QPushButton::clicked, this, &SalesWindow::on_pushButton_5_clicked); // Fournisseur
    } else {
        ui->pushButton_5->setEnabled(false);
    }
    
    // Codes Promo button (only for admin)
    if (ui->pushButton_6) {
        if (role == "admin") {
            connect(ui->pushButton_6, &QPushButton::clicked, this, &SalesWindow::on_pushButton_6_clicked);
        } else {
            ui->pushButton_6->setEnabled(false);
        }
    }
    
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

void SalesWindow::setSalesModelHeaders()
{
    if (!salesModel) {
        return;
    }
    
    salesModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    salesModel->setHeaderData(1, Qt::Horizontal, tr("Client"));
    salesModel->setHeaderData(2, Qt::Horizontal, tr("Employé"));
    salesModel->setHeaderData(3, Qt::Horizontal, tr("Date"));
    salesModel->setHeaderData(4, Qt::Horizontal, tr("Prix TTC"));
    salesModel->setHeaderData(5, Qt::Horizontal, tr("Prix HT"));
    salesModel->setHeaderData(6, Qt::Horizontal, tr("Remise"));
    salesModel->setHeaderData(7, Qt::Horizontal, tr("TVA"));
    salesModel->setHeaderData(8, Qt::Horizontal, tr("Statut Vente"));
    salesModel->setHeaderData(9, Qt::Horizontal, tr("Statut Paiement"));
    salesModel->setHeaderData(10, Qt::Horizontal, tr("Mode Paiement"));
    salesModel->setHeaderData(11, Qt::Horizontal, tr("Date Livraison"));
}

void SalesWindow::updateSalesTableFromQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        qDebug() << "Sales query failed:" << query.lastError().text();
        return;
    }
    
    if (salesModel) {
        delete salesModel;
    }
    salesModel = new QSqlQueryModel(this);
    salesModel->setQuery(query);
    setSalesModelHeaders();
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->resizeColumnsToContents();
}





void SalesWindow::clearSaleForm()
{
    ui->customerIdLineEdit->clear();
    ui->customerNameLineEdit->clear();
    ui->productComboBox->setCurrentIndex(0);
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->quantitySpinBox->setValue(1);
    ui->paymentMethodComboBox->setCurrentIndex(0);
    ui->loyaltyLevelValueLabel->setText("-");
    
    // Refresh product combo box to update stock availability
    populateProductComboBox();
    
    // Reset current IDs
    currentClientId = 0;
    currentEmployeId = 0;
    
    // Clear cart items list
    cartItems.clear();
    
    // Clear cart model
    cartModel->removeRows(0, cartModel->rowCount());
    
    // Clear discounts
    clearDiscounts();
    
    updateTotals();
}

/* TODO: Uncomment after adding UI elements in Qt Designer
void SalesWindow::on_discountSpinBox_valueChanged(int value)
{
    Q_UNUSED(value);
    updateTotals();
}
*/

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
    // Get selected product from combo box (reference is QString)
    QString reference = ui->productComboBox->currentData().toString();
    
    if (reference.isEmpty()) {
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
    // Try uppercase first (Oracle default)
    query.prepare("SELECT REFERENCE, DESIGNATION, PRIX, QUANTITE FROM PRODUIT WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        query.clear();
        query.prepare("SELECT reference, designation, prix, quantite FROM produit WHERE reference = :reference");
        query.bindValue(":reference", reference);
        if (!query.exec() || !query.next()) {
            QMessageBox::warning(this, "Erreur de recherche", "Produit non trouvé!");
            return;
        }
    } else if (!query.next()) {
        QMessageBox::warning(this, "Erreur de recherche", "Produit non trouvé!");
        return;
    }
    
    QString refFromDb = query.value(0).toString();
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
        if (cartModel->data(cartModel->index(row, 0)).toString() == reference) {
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
    row << new QStandardItem(reference);  // Store as QString
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
    QString reference = cartModel->data(cartModel->index(row, 0)).toString();  // Get as QString
    
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
    QString currentProductId = ui->productComboBox->currentData().toString();
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
    // Try uppercase first (Oracle default)
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, TOTAL_ACHATS, NIVEAU_FIDELITE FROM CLIENTS WHERE ID_CLIENT = :id");
    query.bindValue(":id", searchText.toInt());
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        query.clear();
        query.prepare("SELECT id_client, nom, prenom, total_achats, niveau_fidelite FROM clients WHERE id_client = :id");
        query.bindValue(":id", searchText.toInt());
    }
    
    if (query.exec() && query.next()) {
        currentClientId = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        double totalAchats = query.value(3).toDouble();
        QString niveauFidelite = query.value(4).toString();
        
        ui->customerNameLineEdit->setText(nom + " " + prenom);
        
        // Display loyalty level
        if (!niveauFidelite.isEmpty()) {
            ui->loyaltyLevelValueLabel->setText(niveauFidelite);
        } else {
            ui->loyaltyLevelValueLabel->setText("-");
        }

        qDebug() << "Client trouvé - ID:" << currentClientId << "Total achats:" << totalAchats << "Niveau:" << niveauFidelite;

        // Calculate loyalty discount based on client's total purchases
        calculateLoyaltyDiscount(currentClientId);

        // Update totals to show loyalty discount
        updateTotals();
    } else {
        QMessageBox::warning(this, "Client non trouvé", "Aucun client trouvé avec cet ID.\nErreur: " + query.lastError().text());
        ui->customerNameLineEdit->clear();
        ui->loyaltyLevelValueLabel->setText("-");
        currentClientId = 0;

        // Clear loyalty discount
        loyaltyDiscountPercent = 0.0;
        updateTotals();
    }
}

void SalesWindow::calculateLoyaltyDiscount(int clientId)
{
    loyaltyDiscountPercent = 0.0;
    
    if (clientId <= 0) {
        qDebug() << "calculateLoyaltyDiscount: Invalid client ID";
        return;
    }
    
    // Get client's total purchases and current loyalty level
    QSqlQuery query;
    // Try uppercase first (Oracle default)
    query.prepare("SELECT TOTAL_ACHATS, NIVEAU_FIDELITE FROM CLIENTS WHERE ID_CLIENT = :id");
    query.bindValue(":id", clientId);
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        qDebug() << "Error with uppercase, trying lowercase:" << query.lastError().text();
        query.clear();
        query.prepare("SELECT total_achats, niveau_fidelite FROM clients WHERE id_client = :id");
        query.bindValue(":id", clientId);
    }
    
    if (query.exec() && query.next()) {
        double totalAchats = query.value(0).toDouble();
        QString currentLevel = query.value(1).toString();
        
        qDebug() << "Client #" << clientId << "- Total achats:" << totalAchats << "Niveau actuel:" << currentLevel;
        
        // Get loyalty level discount based on total purchases
        QSqlQuery levelQuery;
        // Try uppercase first
        levelQuery.prepare("SELECT NIVEAU, SEUIL_MINIMUM, POURCENTAGE_REMISE FROM NIVEAU_FIDELITE "
                          "WHERE SEUIL_MINIMUM <= :total_achats "
                          "ORDER BY SEUIL_MINIMUM DESC");
        levelQuery.bindValue(":total_achats", totalAchats);
        
        if (!levelQuery.exec()) {
            // Try lowercase if uppercase fails
            qDebug() << "Error with uppercase niveau_fidelite, trying lowercase:" << levelQuery.lastError().text();
            levelQuery.clear();
            levelQuery.prepare("SELECT niveau, seuil_minimum, pourcentage_remise FROM niveau_fidelite "
                              "WHERE seuil_minimum <= :total_achats "
                              "ORDER BY seuil_minimum DESC");
            levelQuery.bindValue(":total_achats", totalAchats);
        }
        
        if (levelQuery.exec() && levelQuery.next()) {
            QString niveau = levelQuery.value(0).toString();
            double seuil = levelQuery.value(1).toDouble();
            loyaltyDiscountPercent = levelQuery.value(2).toDouble();
            
            qDebug() << "Niveau de fidélité calculé:" << niveau << "Seuil:" << seuil << "Remise:" << loyaltyDiscountPercent << "%";
            
            // Update client's loyalty level if it has changed
            if (niveau != currentLevel) {
                QSqlQuery updateQuery;
                // Try uppercase first
                updateQuery.prepare("UPDATE CLIENTS SET NIVEAU_FIDELITE = :niveau WHERE ID_CLIENT = :id");
                updateQuery.bindValue(":niveau", niveau);
                updateQuery.bindValue(":id", clientId);
                
                bool updateSuccess = updateQuery.exec();
                if (!updateSuccess) {
                    // Try lowercase if uppercase fails
                    updateQuery.clear();
                    updateQuery.prepare("UPDATE clients SET niveau_fidelite = :niveau WHERE id_client = :id");
                    updateQuery.bindValue(":niveau", niveau);
                    updateQuery.bindValue(":id", clientId);
                    updateSuccess = updateQuery.exec();
                }
                
                if (updateSuccess) {
                    qDebug() << "Niveau de fidélité mis à jour pour le client #" << clientId << "à" << niveau;
                    ui->loyaltyLevelValueLabel->setText(niveau);
                } else {
                    qDebug() << "Erreur lors de la mise à jour du niveau de fidélité:" << updateQuery.lastError().text();
                }
            } else {
                // Update UI even if level hasn't changed
                ui->loyaltyLevelValueLabel->setText(niveau);
            }
        } else {
            qDebug() << "Aucun niveau de fidélité trouvé pour le client #" << clientId << "avec total_achats =" << totalAchats;
            qDebug() << "Erreur:" << levelQuery.lastError().text();
            loyaltyDiscountPercent = 0.0;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des informations du client #" << clientId << ":" << query.lastError().text();
        loyaltyDiscountPercent = 0.0;
    }
    
    qDebug() << "Remise de fidélité calculée:" << loyaltyDiscountPercent << "%";
}

bool SalesWindow::applyPromoCode(const QString &code)
{
    if (code.isEmpty()) {
        return false;
    }
    
    // Check if promo code exists and is valid
    QSqlQuery query;
    // Try uppercase first (Oracle default)
    query.prepare("SELECT CODE, DESCRIPTION, POURCENTAGE_REMISE, DATE_DEBUT, DATE_FIN, ACTIF "
                  "FROM CODE_PROMO "
                  "WHERE CODE = :code AND ACTIF = 1");
    query.bindValue(":code", code);
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        query.clear();
        query.prepare("SELECT code, description, pourcentage_remise, date_debut, date_fin, actif "
                      "FROM code_promo "
                      "WHERE code = :code AND actif = 1");
        query.bindValue(":code", code);
    }
    
    if (query.exec() && query.next()) {
        QString promoCode = query.value(0).toString();
        QString description = query.value(1).toString();
        promoCodeDiscountPercent = query.value(2).toDouble();
        QDate dateDebut = query.value(3).toDate();
        QDate dateFin = query.value(4).toDate();
        int actif = query.value(5).toInt();
        
        QDate currentDate = QDate::currentDate();
        
        // Check if promo code is active and within date range
        if (actif == 1 && currentDate >= dateDebut && currentDate <= dateFin) {
            currentPromoCode = promoCode;
            qDebug() << "Code promo appliqué:" << promoCode << "Remise:" << promoCodeDiscountPercent << "%";
            return true;
        } else {
            qDebug() << "Code promo invalide ou expiré:" << promoCode;
            promoCodeDiscountPercent = 0.0;
            currentPromoCode = "";
            return false;
        }
    } else {
        qDebug() << "Code promo non trouvé ou inactif:" << code;
        promoCodeDiscountPercent = 0.0;
        currentPromoCode = "";
        return false;
    }
}

void SalesWindow::clearDiscounts()
{
    loyaltyDiscountPercent = 0.0;
    promoCodeDiscountPercent = 0.0;
    currentPromoCode = "";
    ui->promoCodeLineEdit->clear();
    ui->discountValueLabel->clear();
}

void SalesWindow::on_pushButton_6_clicked()
{
    // Prevent multiple opens
    if (promoManagerOpen) {
        qDebug() << "PromoManager already open, ignoring request";
        return;
    }
    
    promoManagerOpen = true;
    qDebug() << "Opening PromoManager from SalesWindow";
    
    PromoManager *promoManager = new PromoManager(this);
    promoManager->setAttribute(Qt::WA_DeleteOnClose, true);
    promoManager->setModal(true);
    
    // Connect to finished signal to reset flag after delay
    QObject::connect(promoManager, &QDialog::finished, this, [this](int result) {
        Q_UNUSED(result);
        QTimer::singleShot(300, this, [this]() {
            promoManagerOpen = false;
            qDebug() << "PromoManager flag reset after dialog finished";
        });
    });
    
    promoManager->exec();
    // Dialog will be auto-deleted due to WA_DeleteOnClose
}

void SalesWindow::on_applyPromoButton_clicked()
{
    QString code = ui->promoCodeLineEdit->text().trimmed();
    
    if (code.isEmpty()) {
        QMessageBox::warning(this, "Code Promo", "Veuillez entrer un code promo!");
        return;
    }
    
    if (applyPromoCode(code)) {
        QMessageBox::information(this, "Code Promo", "Code promo appliqué avec succès!");
        updateTotals();
    } else {
        QMessageBox::warning(this, "Code Promo", "Code promo invalide, expiré ou inactif!");
    }
}

void SalesWindow::updateTotals()
{
    double subtotal = 0.0;
    
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        QString totalStr = cartModel->data(cartModel->index(row, 4)).toString();
        totalStr.remove(" DT");
        subtotal += totalStr.toDouble();
    }
    
    // Calculate discounts
    double loyaltyDiscountAmount = subtotal * (loyaltyDiscountPercent / 100.0);
    double promoDiscountAmount = subtotal * (promoCodeDiscountPercent / 100.0);
    double totalDiscount = loyaltyDiscountAmount + promoDiscountAmount;
    
    double discountedSubtotal = subtotal - totalDiscount;
    
    // Calculate tax (assuming 19% TVA)
    double taxRate = 0.19;
    double tax = discountedSubtotal * taxRate;
    double total = discountedSubtotal + tax;
    
    // Update labels
    ui->subtotalLabel->setText(QString("%1 DT").arg(subtotal, 0, 'f', 2));
    
    // Show discount details
    if (totalDiscount > 0) {
        QString discountText;
        if (loyaltyDiscountAmount > 0 && promoDiscountAmount > 0) {
            discountText = QString("%1 DT (Fidélité: %2%, Promo: %3%)")
                          .arg(totalDiscount, 0, 'f', 2)
                          .arg(loyaltyDiscountPercent, 0, 'f', 2)
                          .arg(promoCodeDiscountPercent, 0, 'f', 2);
        } else if (loyaltyDiscountAmount > 0) {
            discountText = QString("%1 DT (Fidélité: %2%)")
                          .arg(totalDiscount, 0, 'f', 2)
                          .arg(loyaltyDiscountPercent, 0, 'f', 2);
        } else {
            discountText = QString("%1 DT (Promo: %2%)")
                          .arg(totalDiscount, 0, 'f', 2)
                          .arg(promoCodeDiscountPercent, 0, 'f', 2);
        }
        ui->discountValueLabel->setText(discountText);
    } else {
        ui->discountValueLabel->setText("0.00 DT");
    }
    
    ui->taxLabel->setText(QString("%1 DT").arg(tax, 0, 'f', 2));
    ui->totalLabel->setText(QString("%1 DT").arg(total, 0, 'f', 2));
}

void SalesWindow::populateProductComboBox()
{
    ui->productComboBox->clear();
    ui->productComboBox->addItem("Sélectionner un produit", QVariant());
    
    // Calculate quantities already in cart
    QMap<QString, int> cartQuantities;
    for (const auto &item : cartItems) {
        cartQuantities[item.first] += item.second;
    }
    
    QSqlQuery query;
    // Try uppercase first (Oracle default)
    query.prepare("SELECT REFERENCE, DESIGNATION, PRIX, QUANTITE FROM PRODUIT WHERE QUANTITE > 0 ORDER BY DESIGNATION");
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        qDebug() << "Error with uppercase table name:" << query.lastError().text();
        query.clear();
        query.prepare("SELECT reference, designation, prix, quantite FROM produit WHERE quantite > 0 ORDER BY designation");
        if (!query.exec()) {
            qDebug() << "Error with lowercase table name:" << query.lastError().text();
            QMessageBox::warning(this, "Erreur", "Impossible de charger les produits: " + query.lastError().text());
            return;
        }
    }
    
    int count = 0;
    while (query.next()) {
        QString reference = query.value(0).toString();
        QString designation = query.value(1).toString();
        double prix = query.value(2).toDouble();
        int quantiteDb = query.value(3).toInt(); // Stock from database
        
        // Subtract quantities already in cart
        int quantiteInCart = cartQuantities.value(reference, 0);
        int quantiteAvailable = quantiteDb - quantiteInCart;
        
        // Only show products with available stock > 0
        if (quantiteAvailable > 0) {
            QString displayText = QString("%1 - %2 (%3 DT, Stock: %4)")
                                 .arg(reference)
                                 .arg(designation)
                                 .arg(prix, 0, 'f', 2)
                                 .arg(quantiteAvailable);
            ui->productComboBox->addItem(displayText, reference);
            count++;
        }
    }
    
    if (count == 0) {
        qDebug() << "No products found with available stock > 0";
    } else {
        qDebug() << "Loaded" << count << "products into combo box (considering cart items)";
    }
}

void SalesWindow::on_productComboBox_currentIndexChanged(int index)
{
    if (index <= 0) {
        ui->productNameLineEdit->clear();
        ui->priceLineEdit->clear();
        return;
    }
    
    QVariant refVariant = ui->productComboBox->itemData(index);
    if (!refVariant.isValid()) {
        return;
    }
    
    QString reference = refVariant.toString();
    QSqlQuery query;
    // Try uppercase first (Oracle default)
    query.prepare("SELECT DESIGNATION, PRIX, QUANTITE FROM PRODUIT WHERE REFERENCE = :ref");
    query.bindValue(":ref", reference);
    
    if (!query.exec()) {
        // Try lowercase if uppercase fails
        query.clear();
        query.prepare("SELECT designation, prix, quantite FROM produit WHERE reference = :ref");
        query.bindValue(":ref", reference);
        if (!query.exec()) {
            qDebug() << "Error loading product details:" << query.lastError().text();
            return;
        }
    }
    
    if (query.next()) {
        QString designation = query.value(0).toString();
        double prix = query.value(1).toDouble();
        int quantiteDb = query.value(2).toInt(); // Stock from database
        
        ui->productNameLineEdit->setText(designation);
        ui->priceLineEdit->setText(QString::number(prix, 'f', 2));
        
        // Calculate available stock (database stock minus items already in cart)
        int quantiteInCart = 0;
        for (const auto &item : cartItems) {
            if (item.first == reference) {
                quantiteInCart += item.second;
            }
        }
        int quantiteAvailable = quantiteDb - quantiteInCart;
        
        // Update quantity max based on available stock
        ui->quantitySpinBox->setMaximum(quantiteAvailable > 0 ? quantiteAvailable : 0);
        if (ui->quantitySpinBox->value() > quantiteAvailable) {
            ui->quantitySpinBox->setValue(quantiteAvailable > 0 ? quantiteAvailable : 0);
        }
    }
}

void SalesWindow::on_saveSaleButton_clicked()
{
    savingAsDraft = true;
    if (validateSale()) {
        // Save as draft (brouillon)
        QString paymentMethod = ui->paymentMethodComboBox->currentText();
        
        // Calculate prices
        QString subtotalStr = ui->subtotalLabel->text();
        subtotalStr.remove(" DT");
        double subtotal = subtotalStr.toDouble();
        
        QString discountStr = ui->discountValueLabel->text();
        discountStr.remove(" DT");
        // Remove discount details in parentheses if present
        int parenPos = discountStr.indexOf(" (");
        if (parenPos >= 0) {
            discountStr = discountStr.left(parenPos);
        }
        double discount = discountStr.toDouble();
        
        double prixHt = subtotal - discount;
        double tva = prixHt * 0.19;
        double prixTtc = prixHt + tva;
        
        venteObj.setIdClient(currentClientId);
        venteObj.setDateVente(QDate::currentDate());
        venteObj.setPrixHt(prixHt);
        venteObj.setTva(tva);
        venteObj.setPrixTtc(prixTtc);
        venteObj.setRemise(discount);
        venteObj.setModePaiement(paymentMethod);
        venteObj.setStatutVente("brouillon");
        
        if (venteObj.ajouter()) {
            int saleId = fetchLatestSaleId();
            if (saleId <= 0) {
                QMessageBox::warning(this, "Avertissement", "Vente enregistrée mais impossible de déterminer l'ID généré.");
            } else {
                if (!persistSaleItems(saleId, false)) {
                    qDebug() << "Certaines lignes de la vente n'ont pas pu être enregistrées.";
                }
            }
            
            // Commit the draft sale to database
            QSqlDatabase db = QSqlDatabase::database();
            QSqlQuery commitQuery;
            if (!commitQuery.exec("COMMIT")) {
                if (!db.commit()) {
                    qDebug() << "Warning: Could not commit draft sale:" << db.lastError().text();
                }
            }
            
            QMessageBox::information(this, "Succès", "Vente enregistrée comme brouillon!");
            clearSaleForm();
            refreshSalesTable();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'enregistrement de la vente!");
        }
    }
}

void SalesWindow::on_registerSaleButton_clicked()
{
    savingAsDraft = false;
    if (validateSale()) {
        QString paymentMethod = ui->paymentMethodComboBox->currentText();
        
        // Calculate prices
        QString subtotalStr = ui->subtotalLabel->text();
        subtotalStr.remove(" DT");
        double subtotal = subtotalStr.toDouble();
        
        QString discountStr = ui->discountValueLabel->text();
        discountStr.remove(" DT");
        // Remove discount details in parentheses if present
        int parenPos = discountStr.indexOf(" (");
        if (parenPos >= 0) {
            discountStr = discountStr.left(parenPos);
        }
        double discount = discountStr.toDouble();
        
        double prixHt = subtotal - discount;
        double tva = prixHt * 0.19;
        double prixTtc = prixHt + tva;
        
        venteObj.setIdClient(currentClientId);
        venteObj.setDateVente(QDate::currentDate());
        venteObj.setPrixHt(prixHt);
        venteObj.setTva(tva);
        venteObj.setPrixTtc(prixTtc);
        venteObj.setRemise(discount);
        venteObj.setModePaiement(paymentMethod);
        venteObj.setStatutVente("validée");
        
        if (venteObj.ajouter()) {
            int saleId = fetchLatestSaleId();
            if (saleId <= 0) {
                QMessageBox::warning(this, "Avertissement", "Vente enregistrée mais impossible de déterminer l'ID généré.");
            } else {
                if (!persistSaleItems(saleId, true)) {
                    qDebug() << "Certaines lignes de la vente n'ont pas pu être enregistrées.";
                }
            }
            
            // Update client's total purchases (TOTAL_ACHATS) after successful sale
            if (currentClientId > 0) {
                QSqlQuery updateClientQuery;
                // Try uppercase first
                updateClientQuery.prepare("UPDATE CLIENTS SET TOTAL_ACHATS = TOTAL_ACHATS + :montant WHERE ID_CLIENT = :id");
                updateClientQuery.bindValue(":montant", prixTtc);
                updateClientQuery.bindValue(":id", currentClientId);
                
                if (!updateClientQuery.exec()) {
                    // Try lowercase if uppercase fails
                    updateClientQuery.clear();
                    updateClientQuery.prepare("UPDATE clients SET total_achats = total_achats + :montant WHERE id_client = :id");
                    updateClientQuery.bindValue(":montant", prixTtc);
                    updateClientQuery.bindValue(":id", currentClientId);
                    updateClientQuery.exec();
                }
                
                // Recalculate loyalty level after updating total purchases
                calculateLoyaltyDiscount(currentClientId);
            }
            
            // CRITICAL: Update stock from CONTENIR table to ensure consistency
            // This ensures stock is reduced based on what's actually in contenir
            if (saleId > 0) {
                if (!updateStockFromContenir(saleId)) {
                    qDebug() << "⚠️ Warning: Stock update from contenir failed, but sale was saved";
                } else {
                    qDebug() << "✅ Stock updated successfully from contenir table";
                }
            }
            
            // CRITICAL: Commit all database changes to persist them
            // Oracle requires explicit COMMIT for ODBC connections
            QSqlDatabase db = QSqlDatabase::database();
            QSqlQuery commitQuery;
            if (!commitQuery.exec("COMMIT")) {
                // Try alternative commit method
                if (!db.commit()) {
                    qDebug() << "Warning: Could not commit transaction:" << db.lastError().text();
                    QMessageBox::warning(this, "Avertissement", 
                        "Les modifications ont été effectuées mais la sauvegarde pourrait être incomplète.\n"
                        "Veuillez vérifier manuellement dans la base de données.");
                } else {
                    qDebug() << "Transaction committed successfully using db.commit()";
                }
            } else {
                qDebug() << "Transaction committed successfully using SQL COMMIT";
            }
            
            // Refresh product combo box to show updated stock quantities
            populateProductComboBox();
            
            QMessageBox::information(this, "Succès", "Vente enregistrée avec succès!");
            clearSaleForm();
            refreshSalesTable();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'enregistrement de la vente!");
        }
    }
}

void SalesWindow::on_searchSalesLineEdit_textChanged(const QString &arg1)
{
    searchSales(arg1);
}

void SalesWindow::on_dateFilterCheckBox_toggled(bool checked)
{
    if (checked) {
        filterSalesByDate();
    } else {
        refreshSalesTable();
    }
}

void SalesWindow::on_startDateEdit_dateChanged(const QDate &)
{
    if (ui->dateFilterCheckBox->isChecked()) {
        filterSalesByDate();
    }
}

void SalesWindow::on_endDateEdit_dateChanged(const QDate &)
{
    if (ui->dateFilterCheckBox->isChecked()) {
        filterSalesByDate();
    }
}

void SalesWindow::on_salesButton_clicked()
{
    // Switch to sales history tab
    ui->tabWidget->setCurrentIndex(1);
}

void SalesWindow::on_logoutButton_clicked()
{
    this->close();
}

void SalesWindow::on_sortButton_clicked()
{
    sortSalesTable();
}

void SalesWindow::on_modifySaleButton_clicked()
{
    if (!ui->salesTableView->selectionModel() ||
        !ui->salesTableView->selectionModel()->hasSelection() ||
        !salesModel) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une vente à modifier!");
        return;
    }
    
    const int row = ui->salesTableView->selectionModel()->selectedRows().first().row();
    const int saleId = salesModel->data(salesModel->index(row, 0)).toInt();
    
    QSqlQuery saleQuery;
    saleQuery.prepare("SELECT id_vente, id_client, id_employe, date_vente, prix_ttc, prix_ht, "
                      "remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison "
                      "FROM vente WHERE id_vente = :id_vente");
    saleQuery.bindValue(":id_vente", saleId);
    
    if (!saleQuery.exec() || !saleQuery.next()) {
        QMessageBox::critical(this, "Erreur",
                              QString("Impossible de récupérer la vente #%1.\n%2")
                                  .arg(saleId)
                                  .arg(saleQuery.lastError().text()));
        return;
    }
    
    const int clientId = saleQuery.value(1).toInt();
    const int employeId = saleQuery.value(2).toInt();
    const QDate dateVente = saleQuery.value(3).toDate();
    const double prixTtc = saleQuery.value(4).toDouble();
    const double prixHt = saleQuery.value(5).toDouble();
    const double remise = saleQuery.value(6).toDouble();
    const double tva = saleQuery.value(7).toDouble();
    const QString statutVente = saleQuery.value(8).toString();
    const QString statutPaiement = saleQuery.value(9).toString();
    const QString modePaiement = saleQuery.value(10).toString();
    const QDate dateLivraison = saleQuery.value(11).toDate();
    
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier la vente #" + QString::number(saleId));
    dialog.setMinimumWidth(420);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    
    // Client combo
    QComboBox *clientCombo = new QComboBox(&dialog);
    int clientIndex = -1;
    QSqlQuery clientsQuery;
    clientsQuery.prepare("SELECT id_client, nom, prenom FROM clients ORDER BY nom, prenom");
    if (clientsQuery.exec()) {
        while (clientsQuery.next()) {
            const int id = clientsQuery.value(0).toInt();
            const QString display = QString("%1 - %2 %3")
                                        .arg(id)
                                        .arg(clientsQuery.value(1).toString())
                                        .arg(clientsQuery.value(2).toString());
            clientCombo->addItem(display, id);
            if (id == clientId) {
                clientIndex = clientCombo->count() - 1;
            }
        }
    }
    if (clientCombo->count() == 0) {
        clientCombo->addItem("Aucun client disponible", clientId);
    }
    if (clientIndex >= 0) {
        clientCombo->setCurrentIndex(clientIndex);
    }
    formLayout->addRow("Client:", clientCombo);
    
    // Employee combo
    QComboBox *employeeCombo = new QComboBox(&dialog);
    employeeCombo->addItem("Aucun employé", 0);
    int employeeIndex = (employeId == 0) ? 0 : -1;
    QSqlQuery employeeQuery;
    employeeQuery.prepare("SELECT id_employe, nom, prenom FROM employe ORDER BY nom, prenom");
    if (employeeQuery.exec()) {
        while (employeeQuery.next()) {
            const int id = employeeQuery.value(0).toInt();
            const QString display = QString("%1 - %2 %3")
                                        .arg(id)
                                        .arg(employeeQuery.value(1).toString())
                                        .arg(employeeQuery.value(2).toString());
            employeeCombo->addItem(display, id);
            if (id == employeId) {
                employeeIndex = employeeCombo->count() - 1;
            }
        }
    }
    if (employeeIndex >= 0) {
        employeeCombo->setCurrentIndex(employeeIndex);
    }
    formLayout->addRow("Employé:", employeeCombo);
    
    // Dates
    QDateEdit *saleDateEdit = new QDateEdit(&dialog);
    saleDateEdit->setCalendarPopup(true);
    saleDateEdit->setDate(dateVente.isValid() ? dateVente : QDate::currentDate());
    formLayout->addRow("Date de vente:", saleDateEdit);
    
    QDateEdit *deliveryDateEdit = new QDateEdit(&dialog);
    deliveryDateEdit->setCalendarPopup(true);
    deliveryDateEdit->setDate(dateLivraison.isValid() ? dateLivraison : QDate::currentDate().addDays(1));
    formLayout->addRow("Date de livraison:", deliveryDateEdit);
    
    auto setupSpin = [](QDoubleSpinBox *spin, double value) {
        spin->setDecimals(2);
        spin->setMaximum(999999999.0);
        spin->setMinimum(0.0);
        spin->setValue(value);
    };
    
    QDoubleSpinBox *prixHtSpin = new QDoubleSpinBox(&dialog);
    setupSpin(prixHtSpin, prixHt);
    formLayout->addRow("Prix HT:", prixHtSpin);
    
    QDoubleSpinBox *tvaSpin = new QDoubleSpinBox(&dialog);
    setupSpin(tvaSpin, tva);
    formLayout->addRow("TVA:", tvaSpin);
    
    QDoubleSpinBox *remiseSpin = new QDoubleSpinBox(&dialog);
    setupSpin(remiseSpin, remise);
    formLayout->addRow("Remise:", remiseSpin);
    
    QDoubleSpinBox *prixTtcSpin = new QDoubleSpinBox(&dialog);
    setupSpin(prixTtcSpin, prixTtc);
    formLayout->addRow("Prix TTC:", prixTtcSpin);
    
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems({"En cours", "Complétée", "Annulée", "En attente"});
    const int statusIndex = statusCombo->findText(statutVente);
    if (statusIndex >= 0) {
        statusCombo->setCurrentIndex(statusIndex);
    }
    formLayout->addRow("Statut de vente:", statusCombo);
    
    QComboBox *paymentStatusCombo = new QComboBox(&dialog);
    paymentStatusCombo->addItems({"Payé", "Non payé", "Partiellement payé", "Remboursé"});
    const int paymentStatusIndex = paymentStatusCombo->findText(statutPaiement);
    if (paymentStatusIndex >= 0) {
        paymentStatusCombo->setCurrentIndex(paymentStatusIndex);
    }
    formLayout->addRow("Statut de paiement:", paymentStatusCombo);
    
    QComboBox *paymentMethodCombo = new QComboBox(&dialog);
    paymentMethodCombo->addItems({"Espèces", "Carte de crédit", "Chèque"});
    const int paymentMethodIndex = paymentMethodCombo->findText(modePaiement);
    if (paymentMethodIndex >= 0) {
        paymentMethodCombo->setCurrentIndex(paymentMethodIndex);
    }
    formLayout->addRow("Mode de paiement:", paymentMethodCombo);
    
    layout->addLayout(formLayout);
    
    QPushButton *reloadButton = new QPushButton("Recharger dans Panier", &dialog);
    reloadButton->setStyleSheet("background-color: #55aaff; color: black; padding: 8px; font-weight: bold;");
    layout->addWidget(reloadButton);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    bool reloadRequested = false;
    connect(reloadButton, &QPushButton::clicked, [&dialog, &reloadRequested]() {
        reloadRequested = true;
        dialog.done(QDialog::Accepted + 1);
    });
    
    const int result = dialog.exec();
    if (reloadRequested) {
    loadSaleIntoNewSaleForm(saleId);
        return;
    }
    
    if (result == QDialog::Accepted) {
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
        
        if (vente.modifier()) {
            QMessageBox::information(this, "Succès",
                                     QString("La vente #%1 a été modifiée avec succès.").arg(saleId));
            refreshSalesTable();
            SalesStatistique::refreshIfOpen();
        } else {
            QMessageBox::critical(this, "Erreur",
                                  QString("Impossible de modifier la vente #%1.\nVérifiez les logs pour plus de détails.")
                                      .arg(saleId));
        }
    }
}

void SalesWindow::on_deleteSaleButton_clicked()
{
    QModelIndexList selected = ui->salesTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une vente à supprimer!");
        return;
    }
    
    int row = selected.first().row();
    int saleId = salesModel->data(salesModel->index(row, 0)).toInt();
    
    int ret = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer cette vente?",
                                    QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (venteObj.supprimer(saleId)) {
            QMessageBox::information(this, "Succès", "Vente supprimée avec succès!");
            refreshSalesTable();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression!");
        }
    }
}

void SalesWindow::on_statisticsButton_clicked()
{
    SalesStatistique *statsWindow = new SalesStatistique(this);
    statsWindow->exec();
    delete statsWindow;
}

void SalesWindow::on_exportPdfButton_clicked()
{
    // Prevent multiple dialog opens
    if (exportDialogOpen) {
        return;
    }
    
    exportDialogOpen = true;
    exportSalesToPdf();
    
    // Reset flag after a delay
    QTimer::singleShot(500, [this]() {
        exportDialogOpen = false;
    });
}

void SalesWindow::on_logoClicked()
{
    DashboardWindow *dashboard = DashboardWindow::getInstance();
    dashboard->show();
    this->close();
}

void SalesWindow::on_pushButton_clicked()
{
    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->show();
    this->close();
}

void SalesWindow::on_pushButton_3_clicked()
{
    gestionemploye00 *empWindow = gestionemploye00::getInstance();
    empWindow->show();
    this->close();
}

void SalesWindow::on_pushButton_4_clicked()
{
    Gclient1 *clientWindow = Gclient1::getInstance();
    clientWindow->show();
    this->close();
}

void SalesWindow::on_pushButton_5_clicked()
{
    FournisseurWindow *fournisseurWindow = FournisseurWindow::getInstance();
    fournisseurWindow->show();
    this->close();
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

void SalesWindow::searchSales(const QString &searchText)
{
    if (searchText.trimmed().isEmpty()) {
        refreshSalesTable();
        return;
    }
    
    QSqlQuery query;
    QString statement = buildBaseSalesQuery() +
                        "WHERE v.id_vente LIKE :search "
                        "OR LOWER(c.nom) LIKE LOWER(:search) "
                        "OR LOWER(c.prenom) LIKE LOWER(:search) "
                        "OR LOWER(e.nom) LIKE LOWER(:search) "
                        "OR LOWER(e.prenom) LIKE LOWER(:search) "
                        "OR LOWER(v.mode_paiement) LIKE LOWER(:search) "
                        "ORDER BY v.date_vente DESC";
    query.prepare(statement);
    const QString pattern = "%" + searchText + "%";
    query.bindValue(":search", pattern);
    
    updateSalesTableFromQuery(query);
}

void SalesWindow::filterSalesByDate()
{
    QDate startDate = ui->startDateEdit->date();
    QDate endDate = ui->endDateEdit->date();
    
    QSqlQuery query;
    query.prepare(buildBaseSalesQuery() +
                  "WHERE v.date_vente BETWEEN :start AND :end "
                  "ORDER BY v.date_vente DESC");
    query.bindValue(":start", startDate);
    query.bindValue(":end", endDate);
    
    updateSalesTableFromQuery(query);
}

void SalesWindow::sortSalesTable()
{
    QString sortOption = ui->sortComboBox->currentText();
    
    QString orderBy;
    if (sortOption.contains("ID (Croissant)")) {
        orderBy = "v.id_vente ASC";
    } else if (sortOption.contains("ID (Décroissant)")) {
        orderBy = "v.id_vente DESC";
    } else if (sortOption.contains("Date (Croissant)")) {
        orderBy = "v.date_vente ASC";
    } else if (sortOption.contains("Date (Décroissant)")) {
        orderBy = "v.date_vente DESC";
    } else if (sortOption.contains("Montant (Croissant)")) {
        orderBy = "v.prix_ttc ASC";
    } else if (sortOption.contains("Montant (Décroissant)")) {
        orderBy = "v.prix_ttc DESC";
    } else if (sortOption.contains("Client (A-Z)")) {
        orderBy = "client ASC";
    } else if (sortOption.contains("Client (Z-A)")) {
        orderBy = "client DESC";
    } else {
        orderBy = "v.date_vente DESC";
    }
    
    QSqlQuery query;
    QString statement = buildBaseSalesQuery();
    
    if (ui->dateFilterCheckBox->isChecked()) {
        statement += "WHERE v.date_vente BETWEEN :start AND :end ";
    }
    
    statement += "ORDER BY " + orderBy;
    query.prepare(statement);
    
    if (ui->dateFilterCheckBox->isChecked()) {
        query.bindValue(":start", ui->startDateEdit->date());
        query.bindValue(":end", ui->endDateEdit->date());
    }
    
    updateSalesTableFromQuery(query);
}

void SalesWindow::exportSalesToPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }
    
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize::A4);
    writer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);
    
    QPainter painter(&writer);
    painter.setPen(Qt::black);
    
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont normalFont("Arial", 9);
    
    int yPos = 50;
    
    // Title
    painter.setFont(titleFont);
    painter.drawText(0, yPos, "Rapport des Ventes");
    yPos += 40;
    
    // Date range if filtered
    if (ui->dateFilterCheckBox->isChecked()) {
        painter.setFont(normalFont);
        painter.drawText(0, yPos, QString("Période: %1 - %2")
                        .arg(ui->startDateEdit->date().toString("dd/MM/yyyy"))
                        .arg(ui->endDateEdit->date().toString("dd/MM/yyyy")));
        yPos += 30;
    }
    
    // Headers
    painter.setFont(headerFont);
    int xPos = 0;
    painter.drawText(xPos, yPos, "ID");
    xPos += 50;
    painter.drawText(xPos, yPos, "Date");
    xPos += 100;
    painter.drawText(xPos, yPos, "Client");
    xPos += 150;
    painter.drawText(xPos, yPos, "Montant");
    xPos += 100;
    painter.drawText(xPos, yPos, "Paiement");
    yPos += 20;
    
    // Data
    painter.setFont(normalFont);
    for (int row = 0; row < salesModel->rowCount(); ++row) {
        if (yPos > writer.height() - 50) {
            writer.newPage();
            yPos = 50;
        }
        
        xPos = 0;
        painter.drawText(xPos, yPos, salesModel->data(salesModel->index(row, 0)).toString());
        xPos += 50;
        painter.drawText(xPos, yPos, salesModel->data(salesModel->index(row, 1)).toString());
        xPos += 100;
        painter.drawText(xPos, yPos, salesModel->data(salesModel->index(row, 4)).toString());
        xPos += 150;
        painter.drawText(xPos, yPos, salesModel->data(salesModel->index(row, 2)).toString() + " DT");
        xPos += 100;
        painter.drawText(xPos, yPos, salesModel->data(salesModel->index(row, 3)).toString());
        yPos += 20;
    }
    
    painter.end();
    QMessageBox::information(this, "Succès", "Rapport exporté avec succès!");
    
    // Reset flag immediately after export completes
    exportDialogOpen = false;
}

void SalesWindow::loadSaleIntoNewSaleForm(int saleId)
{
    QSqlQuery query;
    const QStringList saleQueries = {
        QStringLiteral("SELECT id_client, id_employe, date_vente, prix_ttc, prix_ht, remise, tva, statut_vente, statut_paiement, mode_paiement, date_livraison "
                       "FROM vente WHERE id_vente = :id"),
        QStringLiteral("SELECT ID_CLIENT, ID_EMPLOYE, DATE_VENTE, PRIX_TTC, PRIX_HT, REMISE, TVA, STATUT_VENTE, STATUT_PAIEMENT, MODE_PAIEMENT, DATE_LIVRAISON "
                       "FROM VENTE WHERE ID_VENTE = :id"),
        QStringLiteral("SELECT id_client, id_employe, date_vente, montant_total, prix_ht, remise, tva, statut_vente, statut_paiement, methode_paiement, date_livraison "
                       "FROM vente WHERE id_vente = :id"),
        QStringLiteral("SELECT ID_CLIENT, ID_EMPLOYE, DATE_VENTE, MONTANT_TOTAL, PRIX_HT, REMISE, TVA, STATUT_VENTE, STATUT_PAIEMENT, METHODE_PAIEMENT, DATE_LIVRAISON "
                       "FROM VENTE WHERE ID_VENTE = :id")
    };
    
    bool saleLoaded = false;
    for (const QString &sql : saleQueries) {
        query.clear();
        query.prepare(sql);
        query.bindValue(":id", saleId);
    if (query.exec() && query.next()) {
            saleLoaded = true;
            break;
        }
    }
    
    if (!saleLoaded) {
        QMessageBox::warning(this, "Avertissement",
                             QString("Impossible de charger la vente #%1 dans le formulaire.").arg(saleId));
        return;
    }
    
        int clientId = query.value(0).toInt();
        currentClientId = clientId;
    currentEmployeId = query.value(1).toInt();
        
    ui->customerIdLineEdit->setText(QString::number(clientId));
        
    // Load client info (handle plural table names + case)
        QSqlQuery clientQuery;
    const QStringList clientQueries = {
        QStringLiteral("SELECT nom, prenom FROM clients WHERE id_client = :id"),
        QStringLiteral("SELECT NOM, PRENOM FROM CLIENTS WHERE ID_CLIENT = :id"),
        QStringLiteral("SELECT nom, prenom FROM client WHERE id_client = :id"),
        QStringLiteral("SELECT NOM, PRENOM FROM CLIENT WHERE ID_CLIENT = :id")
    };
    for (const QString &clientSql : clientQueries) {
        clientQuery.clear();
        clientQuery.prepare(clientSql);
        clientQuery.bindValue(":id", clientId);
        if (clientQuery.exec() && clientQuery.next()) {
            ui->customerNameLineEdit->setText(clientQuery.value(0).toString() + " " + clientQuery.value(1).toString());
            break;
        }
    }
    
    cartItems.clear();
    cartModel->removeRows(0, cartModel->rowCount());
    
    bool itemsLoaded = false;
    QSqlQueryModel *productsModel = venteObj.afficherProduitsVente(saleId);
    if (productsModel) {
        for (int rowIdx = 0; rowIdx < productsModel->rowCount(); ++rowIdx) {
            QString ref = productsModel->data(productsModel->index(rowIdx, 0)).toString();
            QString designation = productsModel->data(productsModel->index(rowIdx, 1)).toString();
            double price = productsModel->data(productsModel->index(rowIdx, 2)).toDouble();
            int qty = productsModel->data(productsModel->index(rowIdx, 3)).toInt();
            double lineTotal = productsModel->data(productsModel->index(rowIdx, 4)).toDouble();
            if (lineTotal == 0.0) {
                lineTotal = price * qty;
            }
            
            cartItems.append(qMakePair(ref, qty));
            
            QList<QStandardItem*> row;
            row << new QStandardItem(ref);
            row << new QStandardItem(designation);
            row << new QStandardItem(QString("%1 DT").arg(price, 0, 'f', 2));
            row << new QStandardItem(QString::number(qty));
            row << new QStandardItem(QString("%1 DT").arg(lineTotal, 0, 'f', 2));
            cartModel->appendRow(row);
        }
        itemsLoaded = productsModel->rowCount() > 0;
        delete productsModel;
    }
    
    if (!itemsLoaded) {
        // Load sale items with multiple fallbacks (detail_vente or contenir)
        const QList<QString> itemQueries = {
            QStringLiteral("SELECT p.REFERENCE, p.DESIGNATION, dv.QUANTITE, p.PRIX "
                           "FROM DETAIL_VENTE dv "
                           "JOIN PRODUIT p ON dv.REFERENCE_PRODUIT = p.REFERENCE "
                           "WHERE dv.ID_VENTE = :id"),
            QStringLiteral("SELECT p.REFERENCE, p.DESIGNATION, dv.QUANTITE, p.PRIX "
                           "FROM DETAIL_VENTE dv "
                           "JOIN PRODUIT p ON dv.ID_PRODUIT = p.ID_PRODUIT "
                           "WHERE dv.ID_VENTE = :id"),
            QStringLiteral("SELECT p.reference, p.designation, dv.quantite, p.prix "
                           "FROM detail_vente dv "
                           "JOIN produit p ON dv.reference_produit = p.reference "
                           "WHERE dv.id_vente = :id"),
            QStringLiteral("SELECT p.reference, p.designation, dv.quantite, p.prix "
                           "FROM detail_vente dv "
                           "JOIN produit p ON dv.id_produit = p.id_produit "
                           "WHERE dv.id_vente = :id"),
            QStringLiteral("SELECT p.REFERENCE, p.DESIGNATION, c.QUANTITE, p.PRIX "
                           "FROM CONTENIR c "
                           "JOIN PRODUIT p ON c.REFERENCE = p.REFERENCE "
                           "WHERE c.ID_VENTE = :id"),
            QStringLiteral("SELECT p.reference, p.designation, c.quantite, p.prix "
                           "FROM contenir c "
                           "JOIN produit p ON c.reference = p.reference "
                           "WHERE c.id_vente = :id"),
            QStringLiteral("SELECT dv.REFERENCE_PRODUIT, 'Produit existant', dv.QUANTITE, COALESCE(dv.PRIX_UNITAIRE, 0) "
                           "FROM DETAIL_VENTE dv "
                           "WHERE dv.ID_VENTE = :id"),
            QStringLiteral("SELECT dv.reference_produit, 'Produit existant', dv.quantite, COALESCE(dv.prix_unitaire, 0) "
                           "FROM detail_vente dv "
                           "WHERE dv.id_vente = :id"),
            QStringLiteral("SELECT c.reference, 'Produit panier', c.quantite, COALESCE(c.prix_unitaire, 0) "
                           "FROM CONTENIR c "
                           "WHERE c.ID_VENTE = :id"),
            QStringLiteral("SELECT c.reference, 'Produit panier', c.quantite, COALESCE(c.prix_unitaire, 0) "
                           "FROM contenir c "
                           "WHERE c.id_vente = :id")
        };
        
        QSqlQuery itemsQuery;
        for (const QString &sql : itemQueries) {
            itemsQuery.clear();
            itemsQuery.prepare(sql);
            itemsQuery.bindValue(":id", saleId);
            if (itemsQuery.exec()) {
                while (itemsQuery.next()) {
                    QString ref = itemsQuery.value(0).toString();
                    QString designation = itemsQuery.value(1).toString();
                    if (designation.trimmed().isEmpty()) {
                        designation = QString("Produit %1").arg(ref);
                    }
                    int qty = itemsQuery.value(2).toInt();
                    double price = itemsQuery.value(3).toDouble();
                    double lineTotal = qty * price;
                    
                    cartItems.append(qMakePair(ref, qty));
                    
                    QList<QStandardItem*> row;
                    row << new QStandardItem(ref);
                    row << new QStandardItem(designation);
                    row << new QStandardItem(QString("%1 DT").arg(price, 0, 'f', 2));
                    row << new QStandardItem(QString::number(qty));
                    row << new QStandardItem(QString("%1 DT").arg(lineTotal, 0, 'f', 2));
                    cartModel->appendRow(row);
                }
                if (cartModel->rowCount() > 0) {
                    itemsLoaded = true;
                    break;
                }
            } else {
                qDebug() << "Fallback sale-item query failed:" << itemsQuery.lastError().text();
            }
        }
    }
    
    if (!itemsLoaded) {
        QMessageBox::warning(this, "Avertissement",
                             "Impossible de charger les produits de la vente sélectionnée.");
    } else {
        ui->cartTableView->resizeColumnsToContents();
    }
    
    // Set payment method (handle potential column naming differences)
    QString paymentMethod = query.value(9).toString();
    if (paymentMethod.isEmpty()) {
        paymentMethod = query.value(10).toString();
    }
    if (paymentMethod.isEmpty()) {
        paymentMethod = query.value(8).toString();
    }
        int index = ui->paymentMethodComboBox->findText(paymentMethod);
        if (index >= 0) {
            ui->paymentMethodComboBox->setCurrentIndex(index);
        }
        
    populateProductComboBox();
        updateTotals();
        ui->tabWidget->setCurrentIndex(0);
}

bool SalesWindow::persistSaleItems(int saleId, bool updateStock)
{
    bool overallSuccess = true;
    
    for (const auto &item : cartItems) {
        const QString &ref = item.first;
        int qty = item.second;
        double unitPrice = getUnitPriceForReference(ref);

        // Toujours enregistrer le détail de la vente (table DETAIL_VENTE ou équivalent)
        if (!insertDetailRecord(saleId, ref, qty, unitPrice)) {
            overallSuccess = false;
        }

        // Utiliser la logique métier de la classe Vente pour :
        //  - insérer dans la table CONTENIR
        //  - mettre à jour le stock PRODUIT en fonction de CONTENIR
        //
        // Cette méthode gère déjà :
        //  - la vérification de l'existence de la vente
        //  - la vérification de l'existence du produit
        //  - l'UPDATE du stock dans PRODUIT basé sur la quantité dans CONTENIR
        if (updateStock) {
            if (!venteObj.ajouterProduitVente(saleId, ref, qty, unitPrice)) {
                qDebug() << "Failed to add product to sale via Vente::ajouterProduitVente for ref"
                         << ref << "- error:" << venteObj.getProductAddError();
                overallSuccess = false;
            }
        } else {
            // Si on ne souhaite pas toucher au stock (brouillon),
            // on enregistre uniquement la ligne de vente dans CONTENIR sans mise à jour du stock.
            if (!insertContenirRecord(saleId, ref, qty, unitPrice)) {
                overallSuccess = false;
            }
        }
    }
    
    return overallSuccess;
}

bool SalesWindow::insertDetailRecord(int saleId, const QString &reference, int quantity, double unitPrice)
{
    const QList<QString> queries = {
        QStringLiteral("INSERT INTO DETAIL_VENTE (ID_VENTE, REFERENCE_PRODUIT, QUANTITE, PRIX_UNITAIRE) "
                       "VALUES (:vente, :ref, :qty, :price)"),
        QStringLiteral("INSERT INTO detail_vente (id_vente, reference_produit, quantite, prix_unitaire) "
                       "VALUES (:vente, :ref, :qty, :price)"),
        QStringLiteral("INSERT INTO DETAIL_VENTE (ID_VENTE, ID_PRODUIT, QUANTITE, PRIX_UNITAIRE) "
                       "VALUES (:vente, (SELECT ID_PRODUIT FROM PRODUIT WHERE REFERENCE = :ref), :qty, :price)"),
        QStringLiteral("INSERT INTO detail_vente (id_vente, id_produit, quantite, prix_unitaire) "
                       "VALUES (:vente, (SELECT id_produit FROM produit WHERE reference = :ref), :qty, :price)")
    };
    
    for (const QString &sql : queries) {
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":vente", saleId);
        query.bindValue(":ref", reference);
        query.bindValue(":qty", quantity);
        query.bindValue(":price", unitPrice);
        
        if (query.exec()) {
            return true;
        }
    }
    
    qDebug() << "Failed to insert detail_vente for" << reference << ":" << queries.last();
    return false;
}

bool SalesWindow::insertContenirRecord(int saleId, const QString &reference, int quantity, double unitPrice)
{
    const QList<QString> queries = {
        QStringLiteral("INSERT INTO CONTENIR (ID_VENTE, REFERENCE, QUANTITE, PRIX_UNITAIRE) "
                       "VALUES (:vente, :ref, :qty, :price)"),
        QStringLiteral("INSERT INTO contenir (id_vente, reference, quantite, prix_unitaire) "
                       "VALUES (:vente, :ref, :qty, :price)")
    };
    
    for (const QString &sql : queries) {
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":vente", saleId);
        query.bindValue(":ref", reference);
        query.bindValue(":qty", quantity);
        query.bindValue(":price", unitPrice);
        
        if (query.exec()) {
            return true;
        }
    }
    
    qDebug() << "Failed to insert into contenir for" << reference << ":" << queries.last();
    return false;
}

bool SalesWindow::updateProductStock(const QString &reference, int quantity)
{
    const QList<QString> queries = {
        QStringLiteral("UPDATE PRODUIT SET QUANTITE = QUANTITE - :qty WHERE REFERENCE = :ref"),
        QStringLiteral("UPDATE produit SET quantite = quantite - :qty WHERE reference = :ref")
    };
    
    for (const QString &sql : queries) {
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":qty", quantity);
        query.bindValue(":ref", reference);
        if (query.exec()) {
            if (query.numRowsAffected() > 0) {
                qDebug() << "✅ Stock updated for" << reference << "- reduced by" << quantity;
                return true;
            } else {
                qDebug() << "⚠️ No rows affected for" << reference << "- product may not exist";
            }
        }
    }
    
    qDebug() << "❌ Failed to update stock for" << reference;
    return false;
}

bool SalesWindow::updateStockFromContenir(int saleId)
{
    // This method updates stock based on all quantities in CONTENIR for this sale
    // This ensures stock is always consistent with what's in contenir
    qDebug() << "Updating stock from contenir table for sale ID:" << saleId;
    
    QSqlQuery query;
    QString selectSql = "SELECT REFERENCE, QUANTITE FROM CONTENIR WHERE ID_VENTE = :saleId";
    query.prepare(selectSql);
    query.bindValue(":saleId", saleId);
    
    if (!query.exec()) {
        // Try lowercase
        query.clear();
        selectSql = "SELECT reference, quantite FROM contenir WHERE id_vente = :saleId";
        query.prepare(selectSql);
        query.bindValue(":saleId", saleId);
        if (!query.exec()) {
            qDebug() << "❌ Failed to read from contenir:" << query.lastError().text();
            return false;
        }
    }
    
    bool allSuccess = true;
    int updateCount = 0;
    
    while (query.next()) {
        QString reference = query.value(0).toString();
        int quantite = query.value(1).toInt();
        
        if (quantite <= 0) {
            qDebug() << "⚠️ Skipping invalid quantity" << quantite << "for reference" << reference;
            continue;
        }
        
        // Update stock for this product
        QSqlQuery updateQuery;
        QString updateSql = "UPDATE PRODUIT SET QUANTITE = QUANTITE - :qty WHERE REFERENCE = :ref";
        updateQuery.prepare(updateSql);
        updateQuery.bindValue(":qty", quantite);
        updateQuery.bindValue(":ref", reference);
        
        bool updated = false;
        if (updateQuery.exec()) {
            if (updateQuery.numRowsAffected() > 0) {
                updated = true;
                updateCount++;
                qDebug() << "✅ Stock updated: REFERENCE" << reference << "- reduced by" << quantite;
            }
        }
        
        if (!updated) {
            // Try lowercase
            updateQuery.clear();
            updateSql = "UPDATE produit SET quantite = quantite - :qty WHERE reference = :ref";
            updateQuery.prepare(updateSql);
            updateQuery.bindValue(":qty", quantite);
            updateQuery.bindValue(":ref", reference);
            
            if (updateQuery.exec() && updateQuery.numRowsAffected() > 0) {
                updated = true;
                updateCount++;
                qDebug() << "✅ Stock updated (lowercase): REFERENCE" << reference << "- reduced by" << quantite;
            }
        }
        
        if (!updated) {
            qDebug() << "❌ Failed to update stock for REFERENCE" << reference << "quantity" << quantite;
            allSuccess = false;
        }
    }
    
    if (updateCount > 0) {
        qDebug() << "✅ Updated stock for" << updateCount << "product(s) from contenir";
    } else {
        qDebug() << "⚠️ No products found in contenir for sale ID" << saleId;
    }
    
    return allSuccess;
}

int SalesWindow::fetchLatestSaleId() const
{
    int id = venteObj.getId();
    if (id > 0) {
        return id;
    }
    
    const QList<QString> queries = {
        QStringLiteral("SELECT ID_VENTE FROM VENTE ORDER BY ID_VENTE DESC FETCH FIRST 1 ROWS ONLY"),
        QStringLiteral("SELECT MAX(ID_VENTE) FROM VENTE"),
        QStringLiteral("SELECT MAX(id_vente) FROM vente")
    };
    
    for (const QString &sql : queries) {
        QSqlQuery query;
        if (query.exec(sql) && query.next()) {
            int value = query.value(0).toInt();
            if (value > 0) {
                return value;
            }
        }
    }
    return 0;
}

double SalesWindow::getUnitPriceForReference(const QString &reference) const
{
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        QStandardItem *refItem = cartModel->item(row, 0);
        if (!refItem) {
            continue;
        }
        if (refItem->text() == reference) {
            QStandardItem *priceItem = cartModel->item(row, 2);
            if (!priceItem) {
                break;
            }
            QString cleaned = priceItem->text();
            cleaned.remove("DT", Qt::CaseInsensitive);
            cleaned.remove(QRegularExpression("[^0-9\\.,]"));
            cleaned.replace(',', '.');
            bool ok = false;
            double value = cleaned.toDouble(&ok);
            if (ok) {
                return value;
            }
        }
    }
    return 0.0;
}