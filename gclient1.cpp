#include "gclient1.h"
#include "ui_gclient1.h"
#include <QHeaderView>
#include <QDebug>
#include <QTimer> // ✅ ضروري لتفادي خطأ incomplete type

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients)
{
    ui->setupUi(this);

#ifdef QT_WIDGETS_LIB
    this->setCentralWidget(ui->centralwidget);
#endif

    this->resize(1200, 800);
    this->showMaximized();

    // إعداد جدول العملاء
    if (ui->tableWidgetClients) {
        ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidgetClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    // 🔹 إعداد اللوغو ليكون فوق كل العناصر (حتى العنوان)
    if (ui->labelLogoTopRight) {
        ui->labelLogoTopRight->raise();
        ui->labelLogoTopRight->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->labelLogoTopRight->setStyleSheet(
            "background: transparent;"
            "border: none;"
            "z-index: 9999;"
            );
    }

    // 🔹 تأكيد أن اللوغو يبقى فوق بعد رسم كل الواجهة
    QTimer::singleShot(0, this, [this]() {
        if (ui->labelLogoTopRight)
            ui->labelLogoTopRight->raise();
    });

    qDebug() << "✅ Interface GestionClients initialisée avec succès";
}

Gclient1::~Gclient1()
{
    delete ui;
}


