#ifndef GESTIONEMPLOYE___H
#define GESTIONEMPLOYE___H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class gestionemploye00;
}
QT_END_NAMESPACE

class gestionemploye00 : public QWidget
{
    Q_OBJECT

public:
    gestionemploye00(QWidget *parent = nullptr);
    ~gestionemploye00();
    
    // Singleton pattern
    static gestionemploye00* getInstance(QWidget *parent = nullptr);
    static gestionemploye00* instance;

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    // Tableau de bord navigation
    void on_pushButton_14_clicked(); // Stock
    void on_pushButton_8_clicked();  // Ventes
    void on_pushButton_9_clicked();  // Client
    void on_pushButton_7_clicked();  // Produit
    void on_pushButton_11_clicked(); // Fournisseur

private:
    Ui::gestionemploye00 *ui;
};
#endif // GESTIONEMPLOYE___H
