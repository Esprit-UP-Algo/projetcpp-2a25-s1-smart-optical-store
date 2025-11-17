#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <produit.h>
#include <fournisseur.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showToast(QString message);


private slots:
    void on_on_btnvente_clicked_clicked();

    void on_btnemployer_clicked();

    void on_btnProd_clicked();

    void on_btnFour_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_14_clicked();

    void on_lineEdit_6_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();
    void on_pushButton_16_clicked();
    void on_tableWidget_cellClicked(int row);

    void on_tableWidget_2_itemClicked();//siwar
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_delete_clicked();







private:
    Ui::MainWindow *ui;
    Produit Etmp;
    Fournisseur Ftmp;
    int selectedId;

    void afficherFournisseurs();

};

#endif // MAINWINDOW_H
