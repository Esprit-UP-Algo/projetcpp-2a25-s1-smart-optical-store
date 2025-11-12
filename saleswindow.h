#ifndef SALESWINDOW_H
#define SALESWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
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
    explicit SalesWindow(QWidget *parent = nullptr);
    ~SalesWindow();
    
    // Singleton pattern
    static SalesWindow* getInstance(QWidget *parent = nullptr);
    static SalesWindow* instance;

private slots:
    void on_addProductButton_clicked();
    void on_removeProductButton_clicked();
    void on_customerSearchButton_clicked();
    void on_productSearchButton_clicked();
    void on_saveSaleButton_clicked();
    void on_newSaleButton_clicked();
    void on_searchSalesLineEdit_textChanged(const QString &arg1);
    void on_dateFilterCheckBox_toggled(bool checked);
    void on_startDateEdit_dateChanged(const QDate &date);
    void on_endDateEdit_dateChanged(const QDate &date);
    void on_salesButton_clicked();
    void on_logoutButton_clicked();
    void on_sortButton_clicked();
    void on_modifySaleButton_clicked();
    void on_deleteSaleButton_clicked();
    
    // New slots for enhanced sales interface - Uncomment after adding UI elements in Qt Designer
    /*
    void on_productComboBox_currentIndexChanged(int index);
    void on_employeeComboBox_currentIndexChanged(int index);
    void on_discountSpinBox_valueChanged(int value);
    */

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
    QList<QPair<int, int>> cartItems; // Pairs of product reference and quantity
    
    void setupModels();
    void refreshSalesTable();
    void updateTotals();
    void clearSaleForm();
    bool validateSale();
    void sortSalesTable();
    void filterSalesByDate();
    void searchSales(const QString &searchText);
};

#endif // SALESWINDOW_H
