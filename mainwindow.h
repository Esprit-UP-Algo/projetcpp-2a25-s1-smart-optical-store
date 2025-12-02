#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <produit.h>

#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &role = "admin", QWidget *parent = nullptr);
    ~MainWindow();
    
    // Singleton pattern
    static MainWindow* getInstance(const QString &role = "admin", QWidget *parent = nullptr);
    static MainWindow* instance;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);
    void on_logoClicked();  // Logo click -> Dashboard
    
    // Stock CRUD operations
    void on_pushButton_2_clicked();  // Valider (Add/Modify)
    void on_pushButton_5_clicked();  // Delete
    void on_pushButton_9_clicked();  // Filter
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_pushButtonR_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_tableWidget_cellClicked(int row);
    void loadProducts();  // Load products into table
    void showToast(QString message);
    void on_pushButton_exportExcel_clicked();  // Export to Excel



private:
    Ui::MainWindow *ui;
    Produit Etmp;

    bool eventFilter(QObject *obj, QEvent *event) override;
    QString currentProductRef;  // For editing mode (string reference)
    QString generatedRef;  // Store the auto-generated reference when showing "Auto-généré"
    void clearForm();
    void fillForm(const QString &reference);
    void scrollToProduct(const QString &reference);  // Scroll to product in table
    void highlightProductInTable(const QString &reference);  // Highlight product in yellow
    QString generateNextReference(const QString &prefix = "C");  // Generate alphanumeric reference like C33, REF47
    QString detectBestPrefix();  // Detect best prefix (C or REF) based on existing references
};
#endif // MAINWINDOW_H
