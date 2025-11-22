#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QMessageBox>
#include "saleswindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "produit.h"
#include "fournisseurwindow.h"
#include "dashboardwindow.h"
#include <QApplication>
#include "WindowManager.h"
#include <QMouseEvent>
#include "produit.h"
#include "Connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDate>
#include <QAbstractItemView>

#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <QPixmap>

// Initialize static instance pointer
MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance(QWidget *parent)
{

    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new MainWindow(parent);
        instance->setAttribute(Qt::WA_DeleteOnClose);
        // Populate produit table immediately
        Produit p(instance->ui);      // Use the MainWindow's UI
        p.afficher(instance->ui);     // Fill table
        QObject::connect(instance, &QObject::destroyed, []() {
            instance = nullptr;
        });
    }
    instance->show();
    instance->raise();
    instance->activateWindow();
    return instance;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Etmp()
    , currentProductRef(0)
{
    ui->setupUi(this);




    
    // Use WindowManager to setup common window features
    WindowManager::setupWindow(this, "Gestion de Stock", 1200, 800);
    
    //ui->lineEdit_5->setPlaceholderText("  Recherche par référence ou Nom ...");

    // Initialize database connection
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données!");
    }
    
    ui->lineEdit_5->setPlaceholderText("  Recherche par référence ou Nom ...");
    qDebug() << "Chemin courant =" << QDir::currentPath();
    
    // Setup logo - ensure it's visible and clickable
    // Find topRightLogoLabel (the logo visible in the interface) and logoLabel
    QLabel* topRightLogoLabel = this->findChild<QLabel*>("topRightLogoLabel", Qt::FindChildrenRecursively);
    QLabel* logoLabel = this->findChild<QLabel*>("logoLabel", Qt::FindChildrenRecursively);
    if (!logoLabel) {
        logoLabel = ui->logoLabel;
    }
    
    // Setup topRightLogoLabel (main logo visible in stock management page)
    if (topRightLogoLabel) {
        // Load logo image from resources
        QPixmap logoPixmap(":/images/logof.jpg");
        if (logoPixmap.isNull()) {
            logoPixmap = QPixmap("images/logof.jpg");
        }
        if (!logoPixmap.isNull()) {
            topRightLogoLabel->setPixmap(logoPixmap);
            topRightLogoLabel->setScaledContents(true);
            qDebug() << "✅ topRightLogoLabel loaded successfully, size:" << logoPixmap.size();
        }
        
        // Make logo clickable
        topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        topRightLogoLabel->installEventFilter(this);
        topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        topRightLogoLabel->setToolTip("Cliquez pour aller au Tableau de bord");
        topRightLogoLabel->show();
        topRightLogoLabel->raise();
        qDebug() << "✅ topRightLogoLabel setup complete - clickable and ready";
    } else {
        qDebug() << "⚠️ topRightLogoLabel widget not found in UI";
    }
    
    // Also setup logoLabel if it exists
    if (logoLabel) {
        QPixmap logoPixmap(":/images/logof.jpg");
        if (logoPixmap.isNull()) {
            logoPixmap = QPixmap("images/logof.jpg");
        }
        if (!logoPixmap.isNull()) {
            logoLabel->setPixmap(logoPixmap);
            logoLabel->setScaledContents(true);
        }
        logoLabel->setCursor(Qt::PointingHandCursor);
        logoLabel->installEventFilter(this);
        logoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        logoLabel->setToolTip("Cliquez pour aller au Tableau de bord");
        logoLabel->show();
        logoLabel->raise();
    }
    
    // Setup table widget
    ui->tableWidget->setColumnCount(9);
    QStringList headers = {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Connect table double-click
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::on_tableWidget_cellDoubleClicked);
    
    // Load products on startup - delay to ensure UI is fully initialized
    QTimer::singleShot(500, this, [this]() {
        loadProducts();
    });
    clearForm();

    // Wire tableau de bord buttons by their visible text to avoid object-name differences
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            connect(btn, &QPushButton::clicked, this, [this]() {
                this->raise();
                this->activateWindow();
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
                FournisseurWindow::getInstance();
                this->close();
            });
        }
    }
    Produit p;
    p.afficher(ui);
    p.afficherRestock(ui,10);


    ui->lineEdit_5->setPlaceholderText("Tapez la référence ou designation");
    ui->lineEdit_6->setPlaceholderText("Tapez la référence");

    connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){
        ui->travaille_2->setCurrentIndex(0);
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){
        ui->travaille_2->setCurrentIndex(1);


    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    // Ensure logos are visible and clickable when switching to stock page
    QLabel* topRightLogoLabel = this->findChild<QLabel*>("topRightLogoLabel", Qt::FindChildrenRecursively);
    QLabel* logoLabel = this->findChild<QLabel*>("logoLabel", Qt::FindChildrenRecursively);
    if (!logoLabel) {
        logoLabel = ui->logoLabel;
    }
    
    // Setup topRightLogoLabel (the visible logo)
    if (topRightLogoLabel) {
        topRightLogoLabel->show();
        topRightLogoLabel->raise();
        QPixmap logoPixmap(":/images/logof.jpg");
        if (logoPixmap.isNull()) {
            logoPixmap = QPixmap("images/logof.jpg");
        }
        if (!logoPixmap.isNull()) {
            topRightLogoLabel->setPixmap(logoPixmap);
        }
        topRightLogoLabel->installEventFilter(this);
        topRightLogoLabel->setCursor(Qt::PointingHandCursor);
        topRightLogoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    
    // Setup logoLabel
    if (logoLabel) {
        logoLabel->show();
        logoLabel->raise();
        QPixmap logoPixmap(":/images/logof.jpg");
        if (logoPixmap.isNull()) {
            logoPixmap = QPixmap("images/logof.jpg");
        }
        if (!logoPixmap.isNull()) {
            logoLabel->setPixmap(logoPixmap);
        }
        logoLabel->installEventFilter(this);
        logoLabel->setCursor(Qt::PointingHandCursor);
    }
    // Reload products when switching to stock page
    loadProducts();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}

// Removed duplicate on_pushButton_2_clicked() - using newer implementation below

void MainWindow::on_pushButton_31_clicked()
{
    // Clear all input fields
    ui->lineEdit_3->clear();   // Ref
    ui->lineEdit_2->clear();   // Designation
    ui->lineEdit_9->clear();   // Quantité
    ui->lineEdit_36->clear();  // Prix
    ui->comboBox_4->setCurrentIndex(0);  // Catégorie
    ui->lineEdit_8->clear();   // Couleur
    ui->lineEdit_7->clear();   // Marque
    ui->dateEdit->setDate(QDate::currentDate()); // Date d’expiration
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(true);


}

void MainWindow::showToast(QString message)
{
    QLabel *toast = new QLabel(message, this);
    toast->setStyleSheet(
        "background-color: #ff4444; "
        "color: white; "
        "padding: 10px 18px; "
        "border-radius: 8px; "
        "font-weight: bold;"
        );
    toast->setAlignment(Qt::AlignCenter);
    toast->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    toast->adjustSize();
    toast->move(width()/2 - toast->width()/2, 20);
    toast->show();

    QPropertyAnimation *anim = new QPropertyAnimation(toast, "opacity");
    anim->setDuration(2500);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(anim, &QPropertyAnimation::finished, toast, &QLabel::deleteLater);
}



// Removed duplicate on_pushButton_5_clicked() - using newer implementation below


void MainWindow::on_pushButtonR_clicked()
{
    QString rech = ui->lineEdit_5->text();
    Produit c;


    if (!c.rech(rech, ui)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun produit trouvé !"));
    }


}


// Removed duplicate on_pushButton_9_clicked() - using newer implementation below
void MainWindow::on_pushButton_32_clicked()
{
    Produit c(ui);
    if (c.existe(c.getRef()))
    {
        c.modifier();
        QMessageBox::information(this, " Modifié", "produit modifié avec succès");
    }
    else
    {

        QMessageBox::critical(this,tr("Erreur"),tr("produit pas trouvé") );
    }
    c.afficher(ui);
}
void MainWindow::on_tableWidget_cellClicked(int row)
{
    // Updated column order: {"Id", "Nom", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Référence", "Fournisseur"}
    ui->lineEdit_3->setText(ui->tableWidget->item(row, 0)->text()); // REF (Id)
    ui->lineEdit_2->setText(ui->tableWidget->item(row, 1)->text()); // DESIGNATION (Nom)
    ui->lineEdit_8->setText(ui->tableWidget->item(row, 2)->text()); // Couleur

    QString genre = ui->tableWidget->item(row, 3)->text(); // Genre
    if (genre == "Homme") {
        ui->radioButton->setChecked(true);
        ui->radioButton_2->setChecked(false);
    }
    else if (genre == "Femme") {
        ui->radioButton_2->setChecked(true);
        ui->radioButton->setChecked(false);
    }
    else {
        ui->radioButton->setAutoExclusive(false);
        ui->radioButton_2->setAutoExclusive(false);
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
        ui->radioButton->setAutoExclusive(true);
        ui->radioButton_2->setAutoExclusive(true);
    }

    ui->lineEdit_36->setText(ui->tableWidget->item(row, 4)->text()); // Prix
    ui->lineEdit_9->setText(ui->tableWidget->item(row, 5)->text()); // Quantité
    ui->lineEdit_7->setText(ui->tableWidget->item(row, 6)->text()); // Marque
    // row, 7 is REF again (duplicate), skip
    // row, 8 is Fournisseur, skip
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Find both logo labels recursively to handle nested widgets
    QLabel* topRightLogoLabel = this->findChild<QLabel*>("topRightLogoLabel", Qt::FindChildrenRecursively);
    QLabel* logoLabel = this->findChild<QLabel*>("logoLabel", Qt::FindChildrenRecursively);
    if (!logoLabel) {
        logoLabel = ui->logoLabel;
    }
    
    // Check if clicked object is topRightLogoLabel (the visible logo)
    if (topRightLogoLabel && obj == topRightLogoLabel) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                qDebug() << "🖱️ topRightLogoLabel clicked - navigating to Dashboard";
                on_logoClicked();
                return true;
            }
        }
    }
    
    // Check if clicked object is logoLabel
    if (logoLabel && obj == logoLabel) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                qDebug() << "🖱️ logoLabel clicked - navigating to Dashboard";
                on_logoClicked();
                return true;
            }
        }
    }
    
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_logoClicked()
{
    qDebug() << "🔄 Logo clicked - Navigating to Dashboard...";
    // Navigate to Dashboard like other interfaces
    // Get or create dashboard instance
    DashboardWindow* dashboard = DashboardWindow::getInstance();
    if (dashboard) {
        // Show and activate dashboard
        dashboard->show();
        dashboard->raise();
        dashboard->activateWindow();
        qDebug() << "✅ Dashboard opened successfully";
    } else {
        qDebug() << "❌ Failed to open Dashboard";
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le Tableau de bord.");
        return;
    }
    // Close current window after a short delay to ensure dashboard is shown
    QTimer::singleShot(200, this, [this]() {
        this->close();
    });
}

void MainWindow::on_pushButton_exportExcel_clicked()
{
    // Check if table has data
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucun produit à exporter.");
        return;
    }
    
    // Get file path for saving Excel/CSV
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Exporter les produits en Excel", 
        QString("produits_%1.csv").arg(QDate::currentDate().toString("yyyy-MM-dd")),
        "Excel Files (*.csv);;All Files (*)");
    
    if (fileName.isEmpty()) {
        return;
    }
    
    // Ensure .csv extension
    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }
    
    // Open file for writing
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier.\nVérifiez les permissions.");
        return;
    }
    
    QTextStream out(&file);
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    out.setEncoding(QStringConverter::Utf8);
    #else
    out.setCodec("UTF-8");
    #endif
    
    // Write BOM for Excel UTF-8 compatibility
    out << "\xEF\xBB\xBF";
    
    // Write headers
    QStringList headers;
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *headerItem = ui->tableWidget->horizontalHeaderItem(col);
        if (headerItem) {
            headers << headerItem->text();
        } else {
            headers << QString("Column %1").arg(col + 1);
        }
    }
    out << headers.join(",") << "\n";
    
    // Write data rows
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            QString cellValue = item ? item->text() : "";
            // Escape commas and quotes in CSV
            if (cellValue.contains(",") || cellValue.contains("\"") || cellValue.contains("\n")) {
                cellValue.replace("\"", "\"\""); // Escape quotes
                cellValue = "\"" + cellValue + "\""; // Wrap in quotes
            }
            rowData << cellValue;
        }
        out << rowData.join(",") << "\n";
    }
    
    file.close();
    
    QMessageBox::information(this, "Succès", 
                            QString("Les produits ont été exportés avec succès dans:\n%1\n\nLe fichier peut être ouvert dans Microsoft Excel.").arg(fileName));
    
    // Optionally open the file
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void MainWindow::loadProducts()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "❌ Database not connected in loadProducts()";
        qDebug() << "   Is Valid:" << db.isValid();
        qDebug() << "   Is Open:" << db.isOpen();
        qDebug() << "   Database Name:" << db.databaseName();
        
        // Try to reconnect
        Connection c;
        if (c.createconnect()) {
            qDebug() << "✅ Reconnected to database";
            db = QSqlDatabase::database();
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de se connecter à la base de données!\nVérifiez votre connexion.");
            return;
        }
    }
    
    qDebug() << "🔄 Loading products from database...";
    
    // Use afficher which directly fills the table
    Produit p;
    p.afficher(ui);
    
    int rowCount = ui->tableWidget->rowCount();
    qDebug() << "✅ Products loaded:" << rowCount;
    
    if (rowCount == 0) {
        qDebug() << "⚠️ No products found in database. Table might be empty.";
    }
}

void MainWindow::clearForm()
{
    ui->lineEdit_2->clear();  // Designation (Nom)
    ui->lineEdit_3->clear();  // Référence
    ui->lineEdit_7->clear();  // Marque
    ui->lineEdit_9->clear();  // Quantité
    ui->lineEdit_8->clear();  // Couleur
    ui->lineEdit_36->clear();  // Prix
    ui->dateEdit->setDate(QDate::currentDate());
    ui->radioButton->setChecked(true);  // Male
    currentProductRef = 0;
}

void MainWindow::fillForm(int reference)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT reference, designation, quantite, prix, categorie, couleur, genre, marque, date_expiration FROM produit WHERE reference = :ref");
    query.bindValue(":ref", reference);
    
    if (query.exec() && query.next()) {
        currentProductRef = reference;
        ui->lineEdit_3->setText(query.value(0).toString());  // Référence
        ui->lineEdit_2->setText(query.value(1).toString());  // Designation (Nom)
        ui->lineEdit_9->setText(query.value(2).toString());  // Quantité
        // Set price in lineEdit_36
        double prix = query.value(3).toDouble();
        ui->lineEdit_36->setText(QString::number(prix, 'f', 2));  // Prix
        ui->comboBox->setCurrentText(query.value(4).toString());  // Catégorie
        ui->lineEdit_8->setText(query.value(5).toString());  // Couleur
        QString genre = query.value(6).toString();
        if (genre.compare("Femme", Qt::CaseInsensitive) == 0 || genre.compare("Female", Qt::CaseInsensitive) == 0) {
            ui->radioButton_2->setChecked(true);
        } else {
            ui->radioButton->setChecked(true);
        }
        ui->lineEdit_7->setText(query.value(7).toString());  // Marque
        ui->dateEdit->setDate(query.value(8).toDate());
    }
}

void MainWindow::on_pushButton_2_clicked()  // Valider - Add/Modify
{
    // Validate required fields
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom du produit est requis!");
        return;
    }
    
    // Validate price
    bool prixOk = false;
    double prix = ui->lineEdit_36->text().toDouble(&prixOk);
    if (!prixOk || prix < 0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre valide et positif!");
        return;
    }
    
    Produit p;
    p.setDesignation(ui->lineEdit_2->text());
    p.setQuantite(ui->lineEdit_9->text().toInt());
    p.setPrix(prix);  // Use lineEdit_36 for price
    p.setCategorie(ui->comboBox_4->currentText());
    p.setCouleur(ui->lineEdit_8->text());
    p.setgenre(ui);  // setgenre takes UI pointer
    p.setMarque(ui->lineEdit_7->text());
    p.setDateExpiration(ui->dateEdit->date());
    
    bool success = false;
    int newReference = 0;
    
    if (currentProductRef > 0) {
        // Modify existing
        p.setRef(ui->lineEdit_3->text());
        success = p.modifier();
        if (success) {
            // Refresh table immediately
            loadProducts();
            clearForm();
            QMessageBox::information(this, "Succès", "Produit modifié avec succès!");
            
            // Scroll to the modified product
            scrollToProduct(currentProductRef);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du produit!");
        }
    } else {
        // Add new
        success = p.ajouter();
        if (success) {
            // Get the newly inserted product reference
            QSqlDatabase db = QSqlDatabase::database();
            QSqlQuery query(db);
            query.exec("SELECT MAX(reference) FROM produit");
            if (query.next()) {
                newReference = query.value(0).toInt();
            }
            
            // Refresh table immediately before showing message
            loadProducts();
            clearForm();
            QMessageBox::information(this, "Succès", "Produit ajouté avec succès!");
            
            // Scroll to the newly added product
            if (newReference > 0) {
                scrollToProduct(newReference);
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du produit!");
        }
    }
}

void MainWindow::on_pushButton_5_clicked()  // Delete
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un produit à supprimer!");
        return;
    }
    
    QTableWidgetItem* refItem = ui->tableWidget->item(currentRow, 7);  // Référence column
    if (!refItem) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer la référence du produit!");
        return;
    }
    
    int reference = refItem->text().toInt();
    if (reference <= 0) {
        QMessageBox::warning(this, "Erreur", "Référence invalide!");
        return;
    }
    
    int ret = QMessageBox::question(this, "Confirmation", 
                                     QString("Êtes-vous sûr de vouloir supprimer le produit (Réf: %1)?").arg(reference),
                                     QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        Produit p;
        if (p.supprimer(QString::number(reference))) {
            QMessageBox::information(this, "Succès", "Produit supprimé avec succès!");
            loadProducts();
            clearForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression du produit!");
        }
    }
}

void MainWindow::on_pushButton_9_clicked()  // Filter
{
    QString searchText = ui->lineEdit_5->text().trimmed();
    if (searchText.isEmpty()) {
        loadProducts();
        return;
    }
    
    Produit p;
    // Use rech method which takes UI pointer
    if (!p.rech(searchText, ui)) {
        QMessageBox::information(this, "Recherche", "Aucun produit trouvé.");
    }
    // rech already displays results in the table
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    QTableWidgetItem* refItem = ui->tableWidget->item(row, 7);  // Référence column
    if (refItem) {
        int reference = refItem->text().toInt();
        if (reference > 0) {
            fillForm(reference);
        }
    }
}

void MainWindow::scrollToProduct(int reference)
{
    // Find the product in the table and scroll to it
    // Column 0 is Id (REF), Column 7 is also Référence (REF)
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* refItem = ui->tableWidget->item(row, 0);  // Id column (REF)
        if (refItem && refItem->text().toInt() == reference) {
            ui->tableWidget->scrollToItem(refItem, QAbstractItemView::EnsureVisible);
            ui->tableWidget->selectRow(row);
            ui->tableWidget->setCurrentCell(row, 0);
            break;
        }
    }
}
