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
    void loadClients();  // Méthode publique pour charger les clients

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
    void on_btnDelete_clicked();
    void on_tableWidgetClients_cellDoubleClicked(int row, int column);
    void on_lineEditSearch_textChanged(const QString &text);
    void on_comboBoxTri_currentIndexChanged(int index);
    void on_tabWidgetMain_currentChanged(int index);
    void clearForm();
    void fillForm(int row);

private:
    Ui::GestionClients *ui;
    bool isEditing;
    int currentClientId;
    void refreshTable(const QString &searchText = "", int sortIndex = -1);
};

#endif // GCLIENT1_H
