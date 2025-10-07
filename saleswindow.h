#ifndef SALESWINDOW_H
#define SALESWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class SalesWindow;
}

class SalesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SalesWindow(QWidget *parent = nullptr);
    ~SalesWindow();

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
    void on_dashboardButton_clicked();
    void on_salesButton_clicked();
    void on_logoutButton_clicked();
    void on_sortButton_clicked();

private:
    Ui::SalesWindow *ui;
    QStandardItemModel *cartModel;
    QStandardItemModel *salesModel;
    
    void setupModels();
    void refreshSalesTable();
    void updateTotals();
    void clearSaleForm();
    bool validateSale();
    void sortSalesTable();
};

#endif // SALESWINDOW_H
