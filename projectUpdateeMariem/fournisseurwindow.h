#ifndef FOURNISSEURWINDOW_H
#define FOURNISSEURWINDOW_H

#include <QMainWindow>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class FournisseurWindow;
}
QT_END_NAMESPACE

class FournisseurWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FournisseurWindow(QWidget *parent = nullptr);
    ~FournisseurWindow();
    
    // Singleton pattern
    static FournisseurWindow* getInstance(QWidget *parent = nullptr);
    static FournisseurWindow* instance;

private slots:
    void on_logoClicked();  // Logo click -> Dashboard
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_modifier_3_clicked();  // Display/Refresh button
    void on_tableWidget_2_cellDoubleClicked(int row, int column);

private:
    Ui::FournisseurWindow *ui;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void loadFournisseurs();  // Load all fournisseurs into table
    void clearForm();          // Clear the form
    void fillForm(int row);    // Fill form from table row
    int currentFournisseurId;  // Current fournisseur ID being edited
    bool isEditing;            // Whether we're editing or adding
};
#endif // FOURNISSEURWINDOW_H



