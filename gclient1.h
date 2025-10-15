#ifndef GCLIENT1_H
#define GCLIENT1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class GestionClients;
}
QT_END_NAMESPACE

class Gclient1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gclient1(QWidget *parent = nullptr);
    ~Gclient1();
    
    // Singleton pattern
    static Gclient1* getInstance(QWidget *parent = nullptr);
    static Gclient1* instance;

private:
    Ui::GestionClients *ui;

private slots:
    void on_b1_clicked(); // Stock
    void on_b2_clicked(); // Ventes
    void on_b3_clicked(); // Employes
    void on_b4_clicked(); // Clients (self)
    void on_b5_clicked(); // Fournisseur
};

#endif // GCLIENT1_H
