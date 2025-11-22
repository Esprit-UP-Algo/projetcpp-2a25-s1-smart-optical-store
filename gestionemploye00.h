#ifndef GESTIONEMPLOYE___H
#define GESTIONEMPLOYE___H

#include <QWidget>

class QSqlQueryModel;

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
    void on_logoClicked();  // Logo click -> Dashboard

    // CRUD Operations
    void on_pushButton_13_clicked(); // Ajouter/Valider
    void on_pushButton_12_clicked(); // Effacer
    void on_pushButton_3_clicked();  // Afficher
    void on_pushButton_15_clicked(); // Afficher (duplicate)
    void on_pushButton_4_clicked();  // Rechercher
    void on_pushButton_5_clicked();  // Trier
    void on_pushButton_16_clicked(); // Modifier
    void on_pushButton_17_clicked(); // Supprimer
    void on_lineEdit_12_textChanged(const QString &text);

    // Table selection
    void on_tableWidget_itemSelectionChanged();

    // Table action buttons
    void handleModifyFromTable();
    void handleDeleteFromTable();
    
    // PDF Export
    void exportEmployeesToPdf();

private:
    Ui::gestionemploye00 *ui;
    void afficherTableau();
    void remplirFormulaire(int id);
    int selectedEmployeId() const;
    void createActionButtonsForRow(int row);
    void modifyEmployeeById(int id);
    void deleteEmployeeById(int id);
    void populateTable(QSqlQueryModel *model);
    void searchEmployees(const QString &text);
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // GESTIONEMPLOYE___H
