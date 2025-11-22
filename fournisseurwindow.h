#ifndef FOURNISSEURWINDOW_H
#define FOURNISSEURWINDOW_H
#include <QMainWindow>
#include <QEvent>
#include "fournisseur.h"

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
    void on_pushButton_ajouter_clicked();       // Bouton Ajouter
    void on_pushButton_modifier_clicked();      // Bouton Modifier
    void on_tableWidget_2_itemClicked();        // Sélection d'une ligne
    void on_pushButton_delete_clicked();
    void on_pushButton_modifier_3_clicked();    // Display/Refresh button
    void on_tableWidget_2_cellDoubleClicked(int row, int column);
    void on_logoClicked();                      // Logo click -> Dashboard

private:
    Ui::FournisseurWindow *ui;
    Fournisseur Ftmp;
    int selectedId;
    int currentFournisseurId;  // Current fournisseur ID being edited
    bool isEditing;            // Whether we're editing or adding
    bool eventFilter(QObject *obj, QEvent *event) override;
    void afficherFournisseurs();
    void loadFournisseurs();   // Load all fournisseurs into table
    void clearForm();          // Clear the form
    void fillForm(int row);    // Fill form from table row
};
#endif // FOURNISSEURWINDOW_H



