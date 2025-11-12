#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <produit.h>

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
    
    // Singleton pattern
    static MainWindow* getInstance(QWidget *parent = nullptr);
    static MainWindow* instance;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked(); //mariem
    void on_pushButton_31_clicked();
    void showToast(QString message);
    void on_pushButton_5_clicked();
    void on_pushButtonR_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_32_clicked();
    void on_tableWidget_cellClicked(int row);



private:
    Ui::MainWindow *ui;
    Produit Etmp;
};
#endif // MAINWINDOW_H
