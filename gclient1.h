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

private:
    Ui::GestionClients *ui;
};

#endif // GCLIENT1_H
