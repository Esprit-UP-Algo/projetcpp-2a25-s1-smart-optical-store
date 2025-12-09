#include "fournisseurwindow.h"
#include "ui_fournisseurwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QStringConverter>
#include <QDesktopServices>
#include <QUrl>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include "mainwindow.h"
#include "saleswindow.h"
#include "gclient1.h"
#include "gestionemploye00.h"
#include "WindowManager.h"

// ==== Twilio / HTTP ====
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QEventLoop>
#include <QDebug>
#include <QDate>
#include <QFileDialog>
#include <QStandardPaths>

// =======================
// Singleton
// =======================

FournisseurWindow* FournisseurWindow::instance = nullptr;

FournisseurWindow* FournisseurWindow::getInstance(const QString &role, QWidget *parent)
{
    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new FournisseurWindow(parent);
        instance->userRole = role;  // Store the user's role
        instance->configureRoleBasedAccess();  // Configure access based on role
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

// =======================
// Constructeur / destructeur
// =======================

FournisseurWindow::FournisseurWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FournisseurWindow)
    , Ftmp()
    , selectedId(-1)
    , userRole("")  // Initialize user role
{
    ui->setupUi(this);

    afficherFournisseurs();
    ui->pushButton_delete->setEnabled(false);

    WindowManager::setupWindow(this, "Gestion des Fournisseurs", 1200, 800);

    // Navigation tableau de bord
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                MainWindow::getInstance();
                this->close();
            });
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                SalesWindow::getInstance();
                this->close();
            });
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                gestionemploye00::getInstance();
                this->close();
            });
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                Gclient1::getInstance();
                this->close();
            });
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                this->raise();
                this->activateWindow();
            });
        }
    }
    
    // Load statistics charts automatically
    loadStatisticsCharts();
}

FournisseurWindow::~FournisseurWindow()
{
    delete ui;
}

// =======================
// Affichage tableau
// =======================

void FournisseurWindow::afficherFournisseurs()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT \"ID-fournisseur\", "
            "       \"nom de l'entreprise\", "
            "       \"nom du contact\", "
            "       \"email\", "
            "       \"telephone\", "
            "       \"type de produit fournis\", "
            "       \"condition de paiement\", "
            "       \"historique de commande passée\" "
            "FROM \"fournisseur\""
            ))
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur SELECT fournisseur:" << err;
        QMessageBox::critical(this, "Erreur SQL",
                              "Impossible de charger les fournisseurs :\n" + err);
        return;
    }

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->setRowCount(0);

    QStringList headers;
    headers << "ID"
            << "Entreprise"
            << "Contact"
            << "Email"
            << "Téléphone"
            << "Type Produit"
            << "Condition"
            << "Historique";
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next())
    {
        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
        row++;
    }

    ui->tableWidget_2->resizeColumnsToContents();
    qDebug() << "Affichage de" << row << "fournisseur(s)";
}

// =======================
// Historique fichier texte
// =======================

void FournisseurWindow::ecrireHistorique(const QString &action, int id, const QString &nomEntreprise)
{
    // Nouveau chemin demandé
    QString folderPath = "C:/Users/Dell/Desktop/siwar123";
    QDir dir(folderPath);

    // Crée le dossier si n'existe pas
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Fichier historique dans ce dossier
    QString filePath = dir.filePath("historique_fournisseur.txt");

    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier d'historique:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out << timestamp
        << " | " << action
        << " | ID=" << id
        << " | entreprise=" << nomEntreprise
        << "\n";
}



// =======================
// Sélection de ligne
// =======================

void FournisseurWindow::on_tableWidget_2_itemClicked()
{
    int row = ui->tableWidget_2->currentRow();

    if (row >= 0)
    {
        selectedId = ui->tableWidget_2->item(row, 0)->text().toInt();

        ui->lineEdit->setText(ui->tableWidget_2->item(row, 0)->text());
        ui->lineEdit_3->setText(ui->tableWidget_2->item(row, 1)->text());
        ui->lineEdit_4->setText(ui->tableWidget_2->item(row, 2)->text());
        ui->lineEdit_5->setText(ui->tableWidget_2->item(row, 3)->text());
        ui->lineEdit_6->setText(ui->tableWidget_2->item(row, 4)->text());
        ui->lineEdit_13->setText(ui->tableWidget_2->item(row, 5)->text());
        ui->lineEdit_12->setText(ui->tableWidget_2->item(row, 6)->text());
        ui->lineEdit_11->setText(ui->tableWidget_2->item(row, 7)->text());

        ui->pushButton_delete->setEnabled(true);
    }
}

// =======================
// Ajout
// =======================

void FournisseurWindow::on_pushButton_ajouter_clicked()
{
    QString idStr    = ui->lineEdit->text().trimmed();
    QString nom_ent  = ui->lineEdit_3->text().trimmed();
    QString nom_cont = ui->lineEdit_4->text().trimmed();
    QString email    = ui->lineEdit_5->text().trimmed();
    QString tel      = ui->lineEdit_6->text().trimmed();
    QString type_prod = ui->lineEdit_13->text().trimmed();
    QString condStr  = ui->lineEdit_12->text().trimmed();
    QString histStr  = ui->lineEdit_11->text().trimmed();

    // Regex
    QRegularExpression reId("^[0-9]+$");
    QRegularExpression reNom("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    QRegularExpression reEmail("^[A-Za-z]+[0-9]+@(gmail|outlook|yahoo)\\.(tn|com)$");
    QRegularExpression reTel("^\\d{8}$");
    QRegularExpression reType("^[A-Za-zÀ-ÖØ-öø-ÿ0-9\\s]+$");
    QRegularExpression reCond("^[01]$");
    QRegularExpression reHist("^[A-Za-zÀ-ÖØ-öø-ÿ0-9\\s.,/-]+$");  // *** CHANGEMENT HISTORIQUE ***

    // ID: obligatoire, chiffres uniquement
    if (idStr.isEmpty() || !reId.match(idStr).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "L'ID fournisseur doit contenir uniquement des chiffres.");
        return;
    }

    // Nom entreprise: obligatoire, lettres + espaces
    if (nom_ent.isEmpty() || !reNom.match(nom_ent).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le nom de l'entreprise doit contenir uniquement des lettres et des espaces.");
        return;
    }

    // Nom contact: obligatoire, lettres + espaces
    if (nom_cont.isEmpty() || !reNom.match(nom_cont).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le nom du contact doit contenir uniquement des lettres et des espaces.");
        return;
    }

    // Email: siwar123@gmail.com / outlook / yahoo .tn / .com
    if (!reEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Email invalide.\n"
                             "Format attendu : nomlettres + chiffres + @ + (gmail|outlook|yahoo) + (.tn|.com)\n"
                             "Exemples : siwar123@gmail.com, siwar123@outlook.tn");
        return;
    }

    // Téléphone: 8 chiffres
    if (!reTel.match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    // Type de produit: texte non vide
    if (type_prod.isEmpty() || !reType.match(type_prod).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le type de produit fourni doit être du texte (lettres/chiffres/espaces) et ne pas être vide.");
        return;
    }

    // Condition de paiement: 0 ou 1
    if (!reCond.match(condStr).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "La condition de paiement doit être 0 ou 1.");
        return;
    }

    // *** CHANGEMENT HISTORIQUE ***
    // Historique: maintenant VARCHAR texte, pas date
    if (histStr.isEmpty() || !reHist.match(histStr).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "L'historique doit être un texte valide (lettres, chiffres, espaces, . , / -) et ne pas être vide.");
        return;
    }
    // *** FIN CHANGEMENT HISTORIQUE ***

    int id        = idStr.toInt();
    int cond_paie = condStr.toInt();

    Fournisseur F(id, nom_ent, nom_cont, email, tel, type_prod, cond_paie, histStr);

    if (F.ajouter()) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté.");
        afficherFournisseurs();
        loadStatisticsCharts(); // Refresh statistics with new data
        ecrireHistorique("AJOUT", id, nom_ent);
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout échoué.");
    }
}


// =======================
// Modification
// =======================

void FournisseurWindow::on_pushButton_modifier_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Sélectionnez un fournisseur.");
        return;
    }

    QString nom_ent  = ui->lineEdit_3->text().trimmed();
    QString nom_cont = ui->lineEdit_4->text().trimmed();
    QString email    = ui->lineEdit_5->text().trimmed();
    QString tel      = ui->lineEdit_6->text().trimmed();
    QString type_prod = ui->lineEdit_13->text().trimmed();
    QString condStr  = ui->lineEdit_12->text().trimmed();
    QString histStr  = ui->lineEdit_11->text().trimmed();

    // Regex
    QRegularExpression reNom("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    QRegularExpression reEmail("^[A-Za-z]+[0-9]+@(gmail|outlook|yahoo)\\.(tn|com)$");
    QRegularExpression reTel("^\\d{8}$");
    QRegularExpression reType("^[A-Za-zÀ-ÖØ-öø-ÿ0-9\\s]+$");
    QRegularExpression reCond("^[01]$");
    QRegularExpression reHist("^[A-Za-zÀ-ÖØ-öø-ÿ0-9\\s.,/-]+$");  // *** CHANGEMENT HISTORIQUE ***

    // Nom entreprise
    if (nom_ent.isEmpty() || !reNom.match(nom_ent).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le nom de l'entreprise doit contenir uniquement des lettres et des espaces.");
        return;
    }

    // Nom contact
    if (nom_cont.isEmpty() || !reNom.match(nom_cont).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le nom du contact doit contenir uniquement des lettres et des espaces.");
        return;
    }

    // Email
    if (!reEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Email invalide.\n"
                             "Format attendu : nomlettres + chiffres + @ + (gmail|outlook|yahoo) + (.tn|.com)\n"
                             "Exemples : siwar123@gmail.com, siwar123@outlook.tn");
        return;
    }

    // Téléphone: 8 chiffres
    if (!reTel.match(tel).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    // Type de produit: texte non vide
    if (type_prod.isEmpty() || !reType.match(type_prod).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "Le type de produit fourni doit être du texte (lettres/chiffres/espaces) et ne pas être vide.");
        return;
    }

    // Condition de paiement: 0 ou 1
    if (!reCond.match(condStr).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "La condition de paiement doit être 0 ou 1.");
        return;
    }

    // *** CHANGEMENT HISTORIQUE ***
    // Historique: maintenant VARCHAR texte, pas date
    if (histStr.isEmpty() || !reHist.match(histStr).hasMatch()) {
        QMessageBox::warning(this, "Attention",
                             "L'historique doit être un texte valide (lettres, chiffres, espaces, . , / -) et ne pas être vide.");
        return;
    }
    // *** FIN CHANGEMENT HISTORIQUE ***

    int cond_paie = condStr.toInt();

    Fournisseur F(selectedId, nom_ent, nom_cont, email, tel, type_prod, cond_paie, histStr);

    if (F.modifier(selectedId)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié.");
        afficherFournisseurs();
        loadStatisticsCharts(); // Refresh statistics with updated data
        ecrireHistorique("MODIFICATION", selectedId, nom_ent);
    } else {
        QMessageBox::critical(this, "Erreur", "Modification échouée.");
    }
}

// =======================
// Suppression
// =======================

void FournisseurWindow::on_pushButton_delete_clicked()
{
    if (selectedId == -1) {
        QMessageBox::warning(this, "Attention", "Sélectionnez un fournisseur à supprimer !");
        return;
    }

    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirmation",
                              "Êtes-vous sûr de vouloir supprimer ce fournisseur ?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        Fournisseur f;
        QString nom_ent_avant = ui->lineEdit_3->text();

        if (f.supprimer(selectedId)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé avec succès !");
            afficherFournisseurs();
            loadStatisticsCharts(); // Refresh statistics after deletion
            ecrireHistorique("SUPPRESSION", selectedId, nom_ent_avant);

            selectedId = -1;
            ui->pushButton_delete->setEnabled(false);

            ui->lineEdit->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_13->clear();
            ui->lineEdit_12->clear();
            ui->lineEdit_11->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}

// =======================
// Export PDF (pushButton_6)
// =======================

void FournisseurWindow::on_pushButton_6_clicked()
{
    int rows = ui->tableWidget_2->rowCount();
    int cols = ui->tableWidget_2->columnCount();

    if (rows == 0 || cols == 0) {
        QMessageBox::warning(this, "Export PDF",
                             "Il n'y a aucune donnée à exporter.");
        return;
    }

    // 🟦 1) Sélection du dossier où enregistrer le PDF
    QString folderPath = QFileDialog::getExistingDirectory(
        this,
        "Choisir un dossier pour enregistrer le PDF",
        QDir::homePath()
        );

    if (folderPath.isEmpty()) {
        QMessageBox::information(this, "Export PDF",
                                 "Export annulé par l'utilisateur.");
        return;
    }

    // 🟦 2) Construction du nom du fichier
    QString fileName = QString("fournisseurs_%1.pdf")
                           .arg(QDateTime::currentDateTime()
                                    .toString("yyyyMMdd_HHmmss"));

    QString filePath = folderPath + "/" + fileName;

    // 🟦 3) Création du PDF
    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(96);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Export PDF",
                              "Impossible de créer le fichier PDF.");
        return;
    }

    QRect pageRect = pdf.pageLayout().paintRectPixels(pdf.resolution());

    const int marginLeft    = 50;
    const int marginTop     = 80;
    const int lineHeight    = 30;
    const int columnSpacing = 10;

    int x = marginLeft;
    int y = marginTop;

    // Titre
    QFont titleFont("Arial", 16, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(x, y, "Liste des fournisseurs");
    y += 2 * lineHeight;

    // En-têtes
    QFont headerFont("Arial", 10, QFont::Bold);
    painter.setFont(headerFont);

    int availableWidth = pageRect.width() - 2 * marginLeft;
    int colWidth = availableWidth / cols;

    for (int c = 0; c < cols; ++c) {
        QString header = ui->tableWidget_2->horizontalHeaderItem(c)->text();
        painter.drawText(marginLeft + c * colWidth,
                         y,
                         colWidth - columnSpacing,
                         lineHeight,
                         Qt::AlignLeft | Qt::AlignVCenter,
                         header);
    }
    y += lineHeight;

    // Corps du tableau
    QFont bodyFont("Arial", 9);
    painter.setFont(bodyFont);

    for (int r = 0; r < rows; ++r) {

        // Nouvelle page si besoin
        if (y + lineHeight > pageRect.bottom() - marginTop) {
            pdf.newPage();
            y = marginTop;

            painter.setFont(headerFont);
            for (int c = 0; c < cols; ++c) {
                QString header = ui->tableWidget_2->horizontalHeaderItem(c)->text();
                painter.drawText(marginLeft + c * colWidth,
                                 y,
                                 colWidth - columnSpacing,
                                 lineHeight,
                                 Qt::AlignLeft | Qt::AlignVCenter,
                                 header);
            }
            y += lineHeight;
            painter.setFont(bodyFont);
        }

        // Lignes du tableau
        for (int c = 0; c < cols; ++c) {
            QTableWidgetItem *item = ui->tableWidget_2->item(r, c);
            QString text = item ? item->text() : "";
            painter.drawText(marginLeft + c * colWidth,
                             y,
                             colWidth - columnSpacing,
                             lineHeight,
                             Qt::AlignLeft | Qt::AlignVCenter,
                             text);
        }
        y += lineHeight;
    }

    painter.end();

    QMessageBox::information(this, "Export PDF",
                             "PDF créé avec succès :\n" + filePath);
}


// =======================
// Stat liste (pushButton_8)
// =======================

void FournisseurWindow::on_pushButton_8_clicked()
{
    if (!ui->listWidget)
        return;

    ui->listWidget->clear();

    QSqlQuery query;
    if (!query.exec(
            "SELECT \"nom de l'entreprise\", COUNT(*) "
            "FROM \"fournisseur\" "
            "GROUP BY \"nom de l'entreprise\" "
            "ORDER BY \"nom de l'entreprise\""
            ))
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur stats fournisseur:" << err;
        QMessageBox::critical(this, "Erreur SQL",
                              "Impossible de calculer les statistiques :\n" + err);
        return;
    }

    int nbEntreprisesDistinctes = 0;
    int nbFournisseursTotal = 0;

    while (query.next())
    {
        QString nomEnt = query.value(0).toString();
        int nb = query.value(1).toInt();

        nbEntreprisesDistinctes++;
        nbFournisseursTotal += nb;

        ui->listWidget->addItem(
            QString("%1 : %2 fournisseur(s)").arg(nomEnt).arg(nb)
            );
    }

    ui->listWidget->addItem("------------------------");
    ui->listWidget->addItem(
        QString("Nombre d'entreprises distinctes : %1")
            .arg(nbEntreprisesDistinctes)
        );
    ui->listWidget->addItem(
        QString("Nombre total de fournisseurs : %1")
            .arg(nbFournisseursTotal)
        );
}

// =======================
// Stat graphique (pushButton_7)
// =======================

void FournisseurWindow::on_pushButton_7_clicked()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT \"condition de paiement\", COUNT(*) "
            "FROM \"fournisseur\" "
            "GROUP BY \"condition de paiement\" "
            "ORDER BY \"condition de paiement\""
            ))
    {
        QString err = query.lastError().text();
        qDebug() << "Erreur stats graphiques fournisseur:" << err;
        QMessageBox::critical(this, "Erreur SQL",
                              "Impossible de calculer les statistiques :\n" + err);
        return;
    }

    int count0 = 0;
    int count1 = 0;

    while (query.next())
    {
        int type  = query.value(0).toInt();
        int nb    = query.value(1).toInt();

        if (type == 0)
            count0 = nb;
        else if (type == 1)
            count1 = nb;
    }

    if (count0 == 0 && count1 == 0) {
        QMessageBox::information(this, "Statistiques",
                                 "Aucun fournisseur en base, camembert vide.");
        return;
    }

    QPieSeries *series = new QPieSeries();
    if (count0 > 0)
        series->append("Paiement type 0", count0);
    if (count1 > 0)
        series->append("Paiement type 1", count1);

    if (series->slices().size() > 0) {
        series->slices()[0]->setBrush(QColor("#003366")); // bleu foncé
        series->slices()[0]->setLabelColor(Qt::white);
    }
    if (series->slices().size() > 1) {
        series->slices()[1]->setBrush(QColor("#006699")); // bleu moyen
        series->slices()[1]->setLabelColor(Qt::white);
    }

    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par type de paiement");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500, 400);
    chartView->setWindowTitle("Statistique graphique - Type de paiement");
    chartView->show();
}

// =======================
// Historique dernier mois (pushButton_9)
// =======================

void FournisseurWindow::on_pushButton_9_clicked()
{
    QString folderPath = "C:/Users/firas/Desktop/siwar";
    QDir dir(folderPath);
    if (!dir.exists()) {
        QMessageBox::warning(this, "Historique",
                             "Le dossier d'historique n'existe pas :\n" + folderPath);
        return;
    }

    QString inputPath  = dir.filePath("historique_fournisseur.txt");
    QString outputPath = dir.filePath("historique_fournisseur_dernier_mois.txt");

    QFile inFile(inputPath);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Historique",
                             "Impossible d'ouvrir le fichier d'historique :\n" + inputPath);
        return;
    }

    QTextStream in(&inFile);
    in.setEncoding(QStringConverter::Utf8);

    QDateTime now = QDateTime::currentDateTime();
    QDateTime oneMonthAgo = now.addMonths(-1);

    QStringList filteredLines;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        // Format actuel :
        // "yyyy-MM-dd HH:mm:ss | ACTION | ID=xx | entreprise=YYY"
        int sepIndex = line.indexOf(" | ");
        if (sepIndex <= 0)
            continue;

        QString tsStr = line.left(sepIndex);
        QDateTime ts = QDateTime::fromString(tsStr, "yyyy-MM-dd HH:mm:ss");
        if (!ts.isValid())
            continue;

        if (ts >= oneMonthAgo && ts <= now) {
            filteredLines << line;
        }
    }

    inFile.close();

    QFile outFile(outputPath);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Historique",
                              "Impossible de créer le fichier :\n" + outputPath);
        return;
    }

    QTextStream out(&outFile);
    out.setEncoding(QStringConverter::Utf8);

    for (const QString &l : filteredLines) {
        out << l << "\n";
    }

    outFile.close();

    if (filteredLines.isEmpty()) {
        QMessageBox::information(this, "Historique",
                                 "Aucune action enregistrée sur le dernier mois.\n"
                                 "Le fichier a quand même été créé :\n" + outputPath);
    } else {
        QMessageBox::information(this, "Historique",
                                 QString("Historique du dernier mois généré (%1 ligne(s)) :\n%2")
                                     .arg(filteredLines.size())
                                     .arg(outputPath));
    }

    // Ouvrir le fichier dans le bloc-notes (optionnel)
    QDesktopServices::openUrl(QUrl::fromLocalFile(outputPath));
}

// =======================
// Envoi SMS Twilio
// =======================

bool FournisseurWindow::envoyerSmsFournisseur(const QString &numero, const QString &message)
{
    // ⚠️ À adapter avec TES vraies valeurs Twilio
const QString accountSid = QStringLiteral("ACfd295f0088ec144432ef5e42669e29ab");
const QString authToken  = QStringLiteral("4fd60608962ad5e664c5ccf17280d714");    // <-- TON NOUVEAU Auth Token
    const QString fromNumber = QStringLiteral("+16292589149");                        // <-- TON numéro Twilio                        // Numéro acheté Twilio (ou sandbox)

    if (numero.isEmpty()) {
        qDebug() << "Numéro vide";
        QMessageBox::warning(this, "SMS livraison validée", "53031417");
        return false;
    }

    QNetworkAccessManager manager;

    // URL Twilio Messages API
    QUrl url(QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json")
                 .arg(accountSid));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    // Auth Basic: base64("SID:AUTH_TOKEN")
    QByteArray authData = QString("%1:%2").arg(accountSid, authToken).toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + authData);

    // Corps de la requête
    QUrlQuery postData;
    postData.addQueryItem("To", numero);
    postData.addQueryItem("From", fromNumber);
    postData.addQueryItem("Body", message);

    QByteArray payload = postData.query(QUrl::FullyEncoded).toUtf8();

    QNetworkReply *reply = manager.post(request, payload);

    // Attente synchrone de la réponse
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray body = reply->readAll();

    if (reply->error() != QNetworkReply::NoError) {
        QString debugMsg = QString("Erreur réseau Twilio (%1): %2\n\nRéponse brute:\n%3")
                               .arg(httpStatus)
                               .arg(reply->errorString())
                               .arg(QString::fromUtf8(body));

        qDebug() << debugMsg;
        QMessageBox::critical(this, "Erreur Twilio", debugMsg);

        reply->deleteLater();
        return false;
    }

    // Même si error == NoError, Twilio peut répondre HTTP 4xx/5xx avec du JSON d’erreur
    if (httpStatus < 200 || httpStatus >= 300) {
        QString debugMsg = QString("SMS refusé par Twilio (HTTP %1).\n\nRéponse:\n%2")
                               .arg(httpStatus)
                               .arg(QString::fromUtf8(body));

        qDebug() << debugMsg;
        QMessageBox::critical(this, "Erreur Twilio", debugMsg);

        reply->deleteLater();
        return false;
    }

    qDebug() << "SMS Twilio OK. Réponse:" << body;
    reply->deleteLater();
    return true;
}


// =======================
// Bouton SMS fournisseur (pushButton_38)
// =======================

void FournisseurWindow::on_pushButton_38_clicked()
{
    // Récupérer le numéro et le message depuis l'UI
    QString numeroSaisi = ui->lineEdit_7->text().trimmed();
    QString message     = ui->textEdit->toPlainText().trimmed();

    // Vérifier le message
    if (message.isEmpty()) {
        QMessageBox::warning(this,
                             "SMS fournisseur",
                             "Le message est vide. Écris quelque chose dans la zone de texte.");
        return;
    }

    // Vérifier le numéro
    if (numeroSaisi.isEmpty()) {
        QMessageBox::warning(this,
                             "SMS fournisseur",
                             "Le numéro de téléphone est vide. Écris-le dans le champ prévu.");
        return;
    }

    // Deux formats acceptés:
    //  - international direct: +21653031417
    //  - local 8 chiffres: 53031417  -> on préfixe avec +216
    QRegularExpression reIntl("^\\+\\d{8,15}$");  // + puis 8 à 15 chiffres
    QRegularExpression reLocal("^\\d{8}$");       // 8 chiffres (Tunisie)

    QString numeroFinal;

    if (reIntl.match(numeroSaisi).hasMatch()) {
        // Déjà au bon format (+216...)
        numeroFinal = numeroSaisi;
    } else if (reLocal.match(numeroSaisi).hasMatch()) {
        // Format local tunisien, on ajoute le préfixe
        numeroFinal = "+216" + numeroSaisi;
    } else {
        QMessageBox::warning(this,
                             "SMS fournisseur",
                             "Numéro invalide.\n"
                             "Utilise soit 8 chiffres (ex: 53031417), soit un format international (ex: +21653031417).");
        return;
    }

    // Appel Twilio
    bool ok = envoyerSmsFournisseur(numeroFinal, message);

    if (ok) {
        QMessageBox::information(this,
                                 "SMS fournisseur",
                                 "SMS envoyé avec succès.");
    } else {
        QMessageBox::critical(this,
                              "SMS fournisseur",
                              "Échec de l'envoi du SMS.\n"
                              "Regarde le message d'erreur Twilio pour plus de détails.");
    }
}
void FournisseurWindow::on_pushButton_modifier_3_clicked()
{
    // Récupérer l'ID tapé dans le QLineEdit l5
    QString idStr = ui->l5->text().trimmed();

    // Si vide, on réaffiche toute la liste
    if (idStr.isEmpty()) {
        afficherFournisseurs();
        return;
    }

    // Contrôle: chiffres uniquement
    QRegularExpression reId("^[0-9]+$");
    if (!reId.match(idStr).hasMatch()) {
        QMessageBox::warning(this,
                             "Recherche fournisseur",
                             "L'ID doit contenir uniquement des chiffres.");
        return;
    }

    int id = idStr.toInt();

    QSqlQuery query;
    query.prepare(
        "SELECT \"ID-fournisseur\", "
        "       \"nom de l'entreprise\", "
        "       \"nom du contact\", "
        "       \"email\", "
        "       \"telephone\", "
        "       \"type de produit fournis\", "
        "       \"condition de paiement\", "
        "       \"historique de commande passée\" "
        "FROM \"fournisseur\" "
        "WHERE \"ID-fournisseur\" = :id"
        );
    query.bindValue(":id", id);

    if (!query.exec()) {
        QString err = query.lastError().text();
        qDebug() << "Erreur SELECT fournisseur (recherche par ID):" << err;
        QMessageBox::critical(this,
                              "Erreur SQL",
                              "Impossible d'effectuer la recherche :\n" + err);
        return;
    }

    // On prépare le tableau pour n'afficher que le résultat filtré
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(8);
    ui->tableWidget_2->setRowCount(0);

    QStringList headers;
    headers << "ID"
            << "Entreprise"
            << "Contact"
            << "Email"
            << "Téléphone"
            << "Type Produit"
            << "Condition"
            << "Historique";
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->tableWidget_2->insertRow(row);
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
        row++;
    }

    ui->tableWidget_2->resizeColumnsToContents();

    if (row == 0) {
        QMessageBox::information(this,
                                 "Recherche fournisseur",
                                 QString("Aucun fournisseur trouvé avec l'ID %1.").arg(id));
    }

    // On réinitialise la sélection / suppression
    selectedId = -1;
    ui->pushButton_delete->setEnabled(false);
}

// =======================
// Load Statistics Charts on Startup
// =======================

void FournisseurWindow::loadStatisticsCharts()
{
    // This function will populate any statistics widgets found in the UI
    // It automatically calls the existing statistics functions
    
    qDebug() << "Loading statistics charts...";
    
    // Call the statistics list function (pushButton_8 functionality)
    // This will populate any listWidget if it exists
    on_pushButton_8_clicked();
    
    qDebug() << "Statistics charts loaded successfully";
}

// =======================
// Role-Based Access Control
// =======================

void FournisseurWindow::configureRoleBasedAccess()
{
    qDebug() << "Configuring access control for role:" << userRole;
    
    // If user has fournisseur role, disable navigation to other modules
    if (userRole.toLower() == "fournisseur")
    {
        // Disable navigation buttons to other modules (keep them visible but unclickable)
        if (ui->pushButton) ui->pushButton->setEnabled(false);          // Stock - disabled
        if (ui->pushButton_2) ui->pushButton_2->setEnabled(false);      // Ventes - disabled
        if (ui->pushButton_3) ui->pushButton_3->setEnabled(false);      // Clients - disabled
        if (ui->pushButton_4) ui->pushButton_4->setEnabled(false);      // Employés - disabled
        // pushButton_5 is Fournisseur - keep it enabled
        
        qDebug() << "Navigation restricted for fournisseur role - buttons disabled";
        
        // Optional: Show information message
        QMessageBox::information(this, "Mode Fournisseur",
            "Vous êtes connecté en mode Fournisseur.\n"
            "Accès limité au module de gestion des fournisseurs.");
    }
    else if (userRole.toLower() == "admin" || userRole.isEmpty())
    {
        // Full access for admin - all buttons visible (default state)
        qDebug() << "Full access granted for admin role";
    }
    else
    {
        // For other roles, default to full access
        qDebug() << "Unknown role:" << userRole << "- defaulting to full access";
    }
}

