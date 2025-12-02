#ifndef SALESWINDOW_H
#define SALESWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QEvent>
#include "client.h"
#include "produit.h"
#include "vente.h"
#include "employe.h"

namespace Ui {
class SalesWindow;
}

class SalesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SalesWindow(const QString &role = "admin", QWidget *parent = nullptr);
    ~SalesWindow();
    
    // Singleton pattern
    static SalesWindow* getInstance(const QString &role = "admin", QWidget *parent = nullptr);
    static SalesWindow* instance;

private slots:
    void on_addProductButton_clicked();
    void on_removeProductButton_clicked();
    void on_customerSearchButton_clicked();
    void on_saveSaleButton_clicked();
    void on_registerSaleButton_clicked();
    void on_searchSalesLineEdit_textChanged(const QString &arg1);
    void on_dateFilterCheckBox_toggled(bool checked);
    void on_startDateEdit_dateChanged(const QDate &date);
    void on_endDateEdit_dateChanged(const QDate &date);
    void on_salesButton_clicked();
    void on_logoutButton_clicked();
    void on_sortButton_clicked();
    void on_modifySaleButton_clicked();
    void on_deleteSaleButton_clicked();
    void on_statisticsButton_clicked();
    void on_productComboBox_currentIndexChanged(int index);
    void on_exportPdfButton_clicked();
    void on_logoClicked();  // Logo click -> Dashboard
    void on_applyPromoButton_clicked();  // Apply promo code
    void on_pushButton_6_clicked();  // Codes Promo button

    // Tableau de bord navigation
    void on_pushButton_clicked();      // Stock -> MainWindow
    void on_pushButton_3_clicked();    // Employes -> gestionemploye00
    void on_pushButton_4_clicked();    // Clients -> Gclient1
    void on_pushButton_5_clicked();    // Fournisseur -> FournisseurWindow

private:
    Ui::SalesWindow *ui;
    QStandardItemModel *cartModel;
    QSqlQueryModel *salesModel;
    
    // Model objects
    Client clientObj;
    Produit produitObj;
    Vente venteObj;
    Employe employeObj;
    
    // Current sale data
    int currentClientId;
    int currentEmployeId;
    QList<QPair<QString, int>> cartItems; // Pairs of product reference (QString) and quantity
    bool savingAsDraft;
    
    // Loyalty and promo code
    double loyaltyDiscountPercent;  // Loyalty discount based on client's total purchases
    double promoCodeDiscountPercent;  // Promo code discount
    QString currentPromoCode;  // Current applied promo code
    bool promoManagerOpen;  // Flag to prevent multiple opens
    bool exportDialogOpen;  // Flag to prevent export dialog from reopening
    
    void setupModels();
    void refreshSalesTable();
    void updateTotals();
    void clearSaleForm();
    bool validateSale();
    void sortSalesTable();
    void filterSalesByDate();
    void searchSales(const QString &searchText);
    void populateProductComboBox();
    void exportSalesToPdf();
    void loadSaleIntoNewSaleForm(int saleId);  // Load sale data into new sale form
    bool eventFilter(QObject *obj, QEvent *event) override;
    void showEvent(QShowEvent *event) override;  // Refresh products when window is shown
    void updateSalesTableFromQuery(QSqlQuery &query);
    void setSalesModelHeaders();
    bool persistSaleItems(int saleId, bool updateStock);
    bool insertDetailRecord(int saleId, const QString &reference, int quantity, double unitPrice);
    bool insertContenirRecord(int saleId, const QString &reference, int quantity, double unitPrice);
    bool updateProductStock(const QString &reference, int quantity);
    bool updateStockFromContenir(int saleId);  // Update stock based on contenir table
    int fetchLatestSaleId() const;
    double getUnitPriceForReference(const QString &reference) const;
    
    // Loyalty and promo code functions
    void calculateLoyaltyDiscount(int clientId);  // Calculate loyalty discount based on total purchases
    bool applyPromoCode(const QString &code);  // Apply promo code and return true if valid
    void clearDiscounts();  // Clear all discounts
};

#endif // SALESWINDOW_H
