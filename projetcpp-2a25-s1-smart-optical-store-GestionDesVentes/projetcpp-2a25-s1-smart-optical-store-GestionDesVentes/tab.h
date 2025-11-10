#ifndef TAB_H
#define TAB_H

#include <QDialog>

namespace Ui {
class tab;
}

class tab : public QDialog
{
    Q_OBJECT

public:
    explicit tab(QWidget *parent = nullptr);
    ~tab();

private slots:
    void on_emp_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

private:
    Ui::tab *ui;
};

#endif // TAB_H
