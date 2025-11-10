#ifndef FOURNISSEURWINDOW_H
#define FOURNISSEURWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FournisseurWindow;
}
QT_END_NAMESPACE

class FournisseurWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FournisseurWindow(QWidget *parent = nullptr);
    ~FournisseurWindow();
    
    // Singleton pattern
    static FournisseurWindow* getInstance(QWidget *parent = nullptr);
    static FournisseurWindow* instance;

private:
    Ui::FournisseurWindow *ui;
};
#endif // FOURNISSEURWINDOW_H



