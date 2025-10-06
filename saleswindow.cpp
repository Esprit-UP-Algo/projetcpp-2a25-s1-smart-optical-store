#include "saleswindow.h"
#include "ui_saleswindow.h"
#include "dashboardwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QStandardItem>

SalesWindow::SalesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesWindow),
    cartModel(nullptr),
    salesModel(nullptr)
{
    ui->setupUi(this);
    
    // Set window properties
    setWindowTitle("Sales Management - Smart Optical Store");
    setMinimumSize(1200, 800);
    
    // Setup models and tables
    setupModels();
    
    // Set current date for date filters
    ui->startDateEdit->setDate(QDate::currentDate().addDays(-30));
    ui->endDateEdit->setDate(QDate::currentDate());
    
    // Populate payment method combo box
    ui->paymentMethodComboBox->addItem("Cash");
    ui->paymentMethodComboBox->addItem("Credit Card");
    ui->paymentMethodComboBox->addItem("Debit Card");
    ui->paymentMethodComboBox->addItem("Insurance");
    
    // Connect signals and slots
    connect(ui->addProductButton, &QPushButton::clicked, this, &SalesWindow::on_addProductButton_clicked);
    connect(ui->removeProductButton, &QPushButton::clicked, this, &SalesWindow::on_removeProductButton_clicked);
    connect(ui->customerSearchButton, &QPushButton::clicked, this, &SalesWindow::on_customerSearchButton_clicked);
    connect(ui->productSearchButton, &QPushButton::clicked, this, &SalesWindow::on_productSearchButton_clicked);
    connect(ui->saveSaleButton, &QPushButton::clicked, this, &SalesWindow::on_saveSaleButton_clicked);
    connect(ui->newSaleButton, &QPushButton::clicked, this, &SalesWindow::on_newSaleButton_clicked);
    // Only allow Ventes navigation to be functional; dashboard/logout disabled
    connect(ui->pushButton_2, &QPushButton::clicked, this, &SalesWindow::on_salesButton_clicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &SalesWindow::on_sortButton_clicked);
    
    // Initialize
    clearSaleForm();
}

SalesWindow::~SalesWindow()
{
    delete ui;
    delete salesModel;
    delete cartModel;
}

void SalesWindow::setupModels()
{
    // Setup sales history model (simple list without database)
    salesModel = new QStandardItemModel(0, 5, this);
    salesModel->setHeaderData(0, Qt::Horizontal, "ID");
    salesModel->setHeaderData(1, Qt::Horizontal, "Customer ID");
    salesModel->setHeaderData(2, Qt::Horizontal, "Date");
    salesModel->setHeaderData(3, Qt::Horizontal, "Total Amount");
    salesModel->setHeaderData(4, Qt::Horizontal, "Payment Method");
    
    // Apply the model to the table view
    ui->salesTableView->setModel(salesModel);
    ui->salesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->salesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->salesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->salesTableView->horizontalHeader()->setStretchLastSection(true);
    ui->salesTableView->verticalHeader()->setVisible(false);
    
    // Setup cart model
    cartModel = new QStandardItemModel(0, 5, this);
    cartModel->setHeaderData(0, Qt::Horizontal, "Product ID");
    cartModel->setHeaderData(1, Qt::Horizontal, "Name");
    cartModel->setHeaderData(2, Qt::Horizontal, "Price");
    cartModel->setHeaderData(3, Qt::Horizontal, "Quantity");
    cartModel->setHeaderData(4, Qt::Horizontal, "Total");
    
    ui->cartTableView->setModel(cartModel);
    ui->cartTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cartTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cartTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartTableView->horizontalHeader()->setStretchLastSection(true);
    ui->cartTableView->verticalHeader()->setVisible(false);
    
    // Populate sort combo box
    ui->sortComboBox->addItem("ID (Croissant)");
    ui->sortComboBox->addItem("ID (Décroissant)");
    ui->sortComboBox->addItem("Date (Croissant)");
    ui->sortComboBox->addItem("Date (Décroissant)");
    ui->sortComboBox->addItem("Montant (Croissant)");
    ui->sortComboBox->addItem("Montant (Décroissant)");
    ui->sortComboBox->addItem("Client (A-Z)");
    ui->sortComboBox->addItem("Client (Z-A)");
    
    // Refresh the sales table
    refreshSalesTable();
}

void SalesWindow::refreshSalesTable()
{
    ui->salesTableView->resizeColumnsToContents();
}

void SalesWindow::updateTotals()
{
    double subtotal = 0.0;
    
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        QString totalStr = cartModel->data(cartModel->index(row, 4)).toString();
        totalStr.remove('$');
        subtotal += totalStr.toDouble();
    }
    
    // Calculate tax (assuming 7% tax rate)
    double taxRate = 0.07;
    double tax = subtotal * taxRate;
    double total = subtotal + tax;
    
    // Update labels
    ui->subtotalLabel->setText(QString("$%1").arg(subtotal, 0, 'f', 2));
    ui->taxLabel->setText(QString("$%1").arg(tax, 0, 'f', 2));
    ui->totalLabel->setText(QString("$%1").arg(total, 0, 'f', 2));
}

void SalesWindow::clearSaleForm()
{
    ui->customerIdLineEdit->clear();
    ui->customerNameLineEdit->clear();
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->quantitySpinBox->setValue(1);
    ui->paymentMethodComboBox->setCurrentIndex(0);
    
    // Ensure all fields are enabled and editable
    ui->customerNameLineEdit->setEnabled(true);
    ui->productNameLineEdit->setEnabled(true);
    ui->priceLineEdit->setEnabled(true);
    
    cartModel->removeRows(0, cartModel->rowCount());
    
    updateTotals();
}

bool SalesWindow::validateSale()
{
    if (cartModel->rowCount() == 0) {
        QMessageBox::warning(this, "Validation Error", "Cart is empty. Please add products to the sale.");
        return false;
    }
    
    return true;
}


void SalesWindow::on_addProductButton_clicked()
{
    QString productId = ui->productIdLineEdit->text();
    QString productName = ui->productNameLineEdit->text();
    QString priceStr = ui->priceLineEdit->text();
    int quantity = ui->quantitySpinBox->value();
    
    if (productId.isEmpty() || productName.isEmpty() || priceStr.isEmpty() || quantity <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter valid product information!");
        return;
    }
    
    double price = priceStr.toDouble();
    double total = price * quantity;
    
    // Check if product is already in cart
    for (int row = 0; row < cartModel->rowCount(); ++row) {
        if (cartModel->data(cartModel->index(row, 0)).toString() == productId) {
            int currentQty = cartModel->data(cartModel->index(row, 3)).toInt();
            int newQty = currentQty + quantity;
            double newTotal = price * newQty;
            
            cartModel->setData(cartModel->index(row, 3), newQty);
            cartModel->setData(cartModel->index(row, 4), QString("$%1").arg(newTotal, 0, 'f', 2));
            
            updateTotals();
            return;
        }
    }
    
    // Add new product to cart
    QList<QStandardItem*> row;
    row << new QStandardItem(productId);
    row << new QStandardItem(productName);
    row << new QStandardItem(QString("$%1").arg(price, 0, 'f', 2));
    row << new QStandardItem(QString::number(quantity));
    row << new QStandardItem(QString("$%1").arg(total, 0, 'f', 2));
    
    cartModel->appendRow(row);
    ui->cartTableView->resizeColumnsToContents();
    
    // Clear product input fields
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->quantitySpinBox->setValue(1);
    
    updateTotals();
}

void SalesWindow::on_removeProductButton_clicked()
{
    if (!ui->cartTableView->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Warning", "Please select a product to remove!");
        return;
    }
    
    int row = ui->cartTableView->selectionModel()->selectedRows().first().row();
    cartModel->removeRow(row);
    
    updateTotals();
}

void SalesWindow::on_customerSearchButton_clicked()
{
    QString searchText = ui->customerIdLineEdit->text();
    
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Search Error", "Please enter a customer ID!");
        return;
    }
    
    // Simulate customer search (without database)
    ui->customerNameLineEdit->setText("Customer " + searchText);
    ui->customerNameLineEdit->setEnabled(true);
}

void SalesWindow::on_productSearchButton_clicked()
{
    QString searchText = ui->productIdLineEdit->text();
    
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Search Error", "Please enter a product ID!");
        return;
    }
    
    // Simulate product search (without database)
    ui->productNameLineEdit->setText("Product " + searchText);
    ui->priceLineEdit->setText("10.00");
    ui->productNameLineEdit->setEnabled(true);
    ui->priceLineEdit->setEnabled(true);
}

void SalesWindow::on_saveSaleButton_clicked()
{
    if (!validateSale()) {
        return;
    }
    
    // Get customer ID (optional)
    QString customerId = ui->customerIdLineEdit->text();
    if (customerId.isEmpty()) {
        customerId = "0";
    }
    
    // Get current date and time
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    
    // Get total amount
    QString totalStr = ui->totalLabel->text();
    totalStr.remove('$');
    double totalAmount = totalStr.toDouble();
    
    // Get payment method
    QString paymentMethod = ui->paymentMethodComboBox->currentText();
    
    // Add sale to the sales table (simulate database save)
    QList<QStandardItem*> saleRow;
    saleRow << new QStandardItem(QString::number(salesModel->rowCount() + 1));
    saleRow << new QStandardItem(customerId);
    saleRow << new QStandardItem(currentDateTime);
    saleRow << new QStandardItem(QString("$%1").arg(totalAmount, 0, 'f', 2));
    saleRow << new QStandardItem(paymentMethod);
    
    salesModel->appendRow(saleRow);
    
    QMessageBox::information(this, "Success", "Sale saved successfully!");
    
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
    // Search functionality removed (no database)
    Q_UNUSED(arg1);
}

void SalesWindow::on_dateFilterCheckBox_toggled(bool checked)
{
    ui->startDateEdit->setEnabled(checked);
    ui->endDateEdit->setEnabled(checked);
    // Filter functionality removed (no database)
    Q_UNUSED(checked);
}

void SalesWindow::on_startDateEdit_dateChanged(const QDate &date)
{
    // Date filter functionality removed (no database)
    Q_UNUSED(date);
}

void SalesWindow::on_endDateEdit_dateChanged(const QDate &date)
{
    // Date filter functionality removed (no database)
    Q_UNUSED(date);
}

void SalesWindow::on_dashboardButton_clicked()
{
    // Find existing dashboard window or create new one
    DashboardWindow *dashboardWindow = nullptr;
    QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    
    for (QWidget *widget : topLevelWidgets) {
        if (DashboardWindow *dashboard = qobject_cast<DashboardWindow*>(widget)) {
            dashboardWindow = dashboard;
            break;
        }
    }
    
    if (!dashboardWindow) {
        dashboardWindow = new DashboardWindow();
    }
    
    dashboardWindow->show();
    dashboardWindow->raise();
    dashboardWindow->activateWindow();
    this->hide();
}

void SalesWindow::on_salesButton_clicked()
{
    // Already in sales window, do nothing or refresh
    refreshSalesTable();
}

void SalesWindow::on_logoutButton_clicked()
{
    // Logout/Exit disabled: prevent application from closing
    QMessageBox::information(this, "Logout", "Logout is disabled in this build.");
}

void SalesWindow::on_sortButton_clicked()
{
    sortSalesTable();
}

void SalesWindow::sortSalesTable()
{
    QString sortOption = ui->sortComboBox->currentText();
    int column = -1;
    Qt::SortOrder order = Qt::AscendingOrder;
    
    if (sortOption.contains("ID")) {
        column = 0; // ID column
        order = sortOption.contains("Croissant") ? Qt::AscendingOrder : Qt::DescendingOrder;
    }
    else if (sortOption.contains("Date")) {
        column = 2; // Date column
        order = sortOption.contains("Croissant") ? Qt::AscendingOrder : Qt::DescendingOrder;
    }
    else if (sortOption.contains("Montant")) {
        column = 3; // Amount column
        order = sortOption.contains("Croissant") ? Qt::AscendingOrder : Qt::DescendingOrder;
    }
    else if (sortOption.contains("Client")) {
        column = 1; // Customer column
        order = sortOption.contains("A-Z") ? Qt::AscendingOrder : Qt::DescendingOrder;
    }
    
    if (column >= 0) {
        salesModel->sort(column, order);
        ui->salesTableView->resizeColumnsToContents();
    }
}
