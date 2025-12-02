#include "saleswindow.h"
#include "ui_saleswindow.h"
#include <QShowEvent>
#include "mainwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include "WindowManager.h"
#include "salesstatistique.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QStandardItem>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QFileInfo>
#include <QMetaType>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>

// Initialize static instance pointer
SalesWindow* SalesWindow::instance = nullptr;

SalesWindow* SalesWindow::getInstance(QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new SalesWindow(parent);
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

SalesWindow::SalesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesWindow),
    cartModel(nullptr),
    salesModel(nullptr),
    currentClientId(0),
    currentEmployeId(0),
    savingAsDraft(false)
{
    ui->setupUi(this);
    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion des Ventes");
    
    // Setup models and tables
    setupModels();
    
    // Set current date for date filters
    ui->startDateEdit->setDate(QDate::currentDate().addDays(-30));
    ui->endDateEdit->setDate(QDate::currentDate());
    
    // Payment method combo box is populated in setupModels()
    
    // Update button labels
    ui->newSaleButton->setText("Enregistrer");
    
    // Connect signals and slots
    connect(ui->addProductButton, &QPushButton::clicked, this, &SalesWindow::on_addProductButton_clicked);
    connect(ui->removeProductButton, &QPushButton::clicked, this, &SalesWindow::on_removeProductButton_clicked);
    connect(ui->customerSearchButton, &QPushButton::clicked, this, &SalesWindow::on_customerSearchButton_clicked);
    connect(ui->productComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SalesWindow::on_productComboBox_currentIndexChanged);
    connect(ui->saveSaleButton, &QPushButton::clicked, this, &SalesWindow::on_saveSaleButton_clicked);
    connect(ui->newSaleButton, &QPushButton::clicked, this, &SalesWindow::on_registerSaleButton_clicked);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &SalesWindow::on_exportPdfButton_clicked);
    
    // Make logo clickable
    if (ui->topRightLogoLabel) {
        ui->topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        ui->topRightLogoLabel->installEventFilter(this);
        ui->topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Tableau de bord navigation
    connect(ui->pushButton,   &QPushButton::clicked, this, [this]() {
        MainWindow::getInstance();
        this->close();
    });   // Stock
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        this->raise();
        this->activateWindow();
    });  // Ventes (self)
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        gestionemploye00::getInstance();
        this->close();
    }); // Employes
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() {
        Gclient1::getInstance();
        this->close();
    }); // Clients
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() {
        FournisseurWindow::getInstance();
        this->close();
    }); // Fournisseur
    connect(ui->sortButton, &QPushButton::clicked, this, &SalesWindow::on_sortButton_clicked);
    
    // Initialize
    clearSaleForm();
    refreshSalesTable();
}

SalesWindow::~SalesWindow()
