#include "gclient1.h"
#include "ui_gclient1.h"
#include <QHeaderView>
#include <QDebug>
#include <QTimer>
#include "mainwindow.h"
#include "saleswindow.h"
#include "gestionemploye00.h"
#include "fournisseurwindow.h"
#include <QApplication>
#include "WindowManager.h"

// Initialize static instance pointer
Gclient1* Gclient1::instance = nullptr;

Gclient1* Gclient1::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new Gclient1(parent);
        instance->setAttribute(Qt::WA_DeleteOnClose);
        QObject::connect(instance, &QObject::destroyed, []() {
            instance = nullptr;
        });
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients)
{
    ui->setupUi(this);

#ifdef QT_WIDGETS_LIB
    this->setCentralWidget(ui->centralwidget);
#endif

    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion Clients");
    
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
        
        // Ensure fullscreen button stays on top
        QWidget* btnToggleFullscreen = this->findChild<QWidget*>("btnToggleFullscreen");
        if (btnToggleFullscreen)
            btnToggleFullscreen->raise();
    });

    qDebug() << "✅ Interface GestionClients initialisée avec succès";
}


void Gclient1::on_b1_clicked()
{
    MainWindow::getInstance();
    this->close();
}

void Gclient1::on_b2_clicked()
{
    SalesWindow::getInstance();
    this->close();
}

void Gclient1::on_b3_clicked()
{
    gestionemploye00::getInstance();
    this->close();
}

void Gclient1::on_b4_clicked()
{
    // Already in clients window; keep focus
    this->raise();
    this->activateWindow();
}

void Gclient1::on_b5_clicked()
{
    // Fournisseur
    FournisseurWindow::getInstance();
    this->close();
}

Gclient1::~Gclient1()
{
    delete ui;
}


