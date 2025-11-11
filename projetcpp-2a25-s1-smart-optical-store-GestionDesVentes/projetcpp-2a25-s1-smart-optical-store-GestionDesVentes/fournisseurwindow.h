#ifndef FOURNISSEURWINDOW_H
#define FOURNISSEURWINDOW_H
#include <QMainWindow>
#include "fournisseur.h"

#include <QMainWindow>

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
    void on_tableWidget_2_itemClicked();        // Sélection d’une ligne
    void on_pushButton_delete_clicked();
private:
    Ui::FournisseurWindow *ui;
    Fournisseur Ftmp;
    int selectedId;
    void afficherFournisseurs();

};
#endif // FOURNISSEURWINDOW_H



