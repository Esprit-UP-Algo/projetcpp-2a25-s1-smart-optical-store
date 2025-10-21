#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnProd_clicked();

    void on_on_btnvente_clicked_clicked();

    void on_btnemployer_clicked();

    void on_pushButton_11_clicked();

    void on_btnFour_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
