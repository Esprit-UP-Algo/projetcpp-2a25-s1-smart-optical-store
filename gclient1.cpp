#include "gclient1.h"
#include "ui_gclient1.h"
#include <QHeaderView>
#include <QPixmap>
#include <QDebug>
#include <QFile>

Gclient1::Gclient1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClients)
{
    ui->setupUi(this);

    // Redimensionner la fenêtre
    this->resize(1200, 800);
    this->showMaximized();

    // Configuration de la table
    if (ui->tableWidgetClients) {
        ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidgetClients->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    // Charger le logo depuis le système de fichiers
    QString logoPath = "./smart_logo.png";  // Chemin relatif vers l'image
    QPixmap logo(logoPath);

    if (!logo.isNull()) {
        ui->labelLogoTopRight->setPixmap(logo);  // Applique le logo sur le QLabel
        ui->labelLogoTopRight->setScaledContents(true);  // Ajuste la taille du logo
        ui->labelLogoTopRight->setMaximumSize(50, 50);  // Taille maximale
    } else {
        qDebug() << "⚠️ Logo non trouvé à " << logoPath;  // Afficher un message d'erreur
    }

    qDebug() << "✅ Interface GestionClients initialisée avec succès";
}

Gclient1::~Gclient1()
{
    delete ui;
}
