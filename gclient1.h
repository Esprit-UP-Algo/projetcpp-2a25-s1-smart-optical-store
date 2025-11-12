#ifndef GCLIENT1_H
#define GCLIENT1_H

#include <QMainWindow>
#include <QEvent>

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
    void loadClients();  // Méthode publique pour charger les clients
    
    // Singleton pattern
    static Gclient1* getInstance(QWidget *parent = nullptr);
    static Gclient1* instance;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
    void on_btnDelete_clicked();
    void on_tableWidgetClients_cellDoubleClicked(int row, int column);
    void on_lineEditSearch_textChanged(const QString &text);
    void on_comboBoxTri_currentIndexChanged(int index);
    void on_tabWidgetMain_currentChanged(int index);
    
    // Navigation buttons
    void on_b1_clicked(); // Stock
    void on_b2_clicked(); // Ventes
    void on_b3_clicked(); // Employes
    void on_b4_clicked(); // Clients (self)
    void on_b5_clicked(); // Fournisseur

private:
    Ui::GestionClients *ui;
    bool isEditing;
    int currentClientId;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void clearForm();
    void fillForm(int row);
    void refreshTable(const QString &searchText = "", int sortIndex = -1);
};

#endif // GCLIENT1_H
