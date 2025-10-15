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
    
    // Singleton pattern
    static MainWindow* getInstance(QWidget *parent = nullptr);
    static MainWindow* instance;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
