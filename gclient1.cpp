#include "gclient1.h"
#include "ui_gclient1.h"
#include <QHeaderView>

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients)
{
    ui->setupUi(this);

    // If ui generated centralwidget member exists, set it as central widget
    // (uic for QMainWindow usually creates ui->centralwidget).
    // If not present, setupUi already parented widgets correctly.
    // Protect against missing member by checking via pointer cast would be complex;
    // typically ui->centralwidget is present with a QMainWindow-based .ui.
    // The centralwidget is declared in the generated ui_gclient1.h,
    // so we can safely call setCentralWidget if it exists:
#ifdef QT_WIDGETS_LIB
    // setCentralWidget is safe if ui->centralwidget exists
    // (it will exist because .ui root is QMainWindow)
    this->setCentralWidget(ui->centralwidget);
#endif

    // Make window a reasonable starting size and maximize for convenience
    this->resize(1200, 800);
    this->showMaximized();

    // Ensure table resizes nicely
    if (ui->tableWidgetClients) {
        ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidgetClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

Gclient1::~Gclient1()
{
    delete ui;
}
