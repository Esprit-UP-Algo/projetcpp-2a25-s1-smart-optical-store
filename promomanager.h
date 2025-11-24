#ifndef PROMOMANAGER_H
#define PROMOMANAGER_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QCloseEvent>

namespace Ui {
class PromoManager;
}

class PromoManager : public QDialog
{
    Q_OBJECT

public:
    explicit PromoManager(QWidget *parent = nullptr);
    ~PromoManager();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_generateCodeButton_clicked();
    void refreshPromoTable();

private:
    Ui::PromoManager *ui;
    QSqlQueryModel *promoModel;
    void setupTable();
};

#endif // PROMOMANAGER_H