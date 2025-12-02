#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>

namespace Ui {
class Statistique;
}

class Statistique : public QDialog
{
    Q_OBJECT

public:
    explicit Statistique(QWidget *parent = nullptr);
    ~Statistique();
    
    void loadEmployeeStatistics();

private slots:
    void on_refreshButton_clicked();
    void on_exportButton_clicked();

private:
    Ui::Statistique *ui;
};

#endif // STATISTIQUE_H
