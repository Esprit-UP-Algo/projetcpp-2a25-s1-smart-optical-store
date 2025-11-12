#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    // Singleton pattern
    static MainWindow* getInstance(QWidget *parent = nullptr);
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
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void loadProducts();  // Load products into table

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *obj, QEvent *event) override;
    int currentProductRef;  // For editing mode
    void clearForm();
    void fillForm(int reference);
    void scrollToProduct(int reference);  // Scroll to product in table
};
#endif // MAINWINDOW_H
