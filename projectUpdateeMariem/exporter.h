#ifndef EXPORTER_H
#define EXPORTER_H

#include <QDialog>

namespace Ui {
class Exporter;
}

class Exporter : public QDialog
{
    Q_OBJECT

public:
    explicit Exporter(QWidget *parent = nullptr);
    ~Exporter();

private:
    Ui::Exporter *ui;
};

#endif // EXPORTER_H
