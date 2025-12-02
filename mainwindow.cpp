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
#include <QBrush>
#include <QColor>

// Initialize static instance pointer
MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance(const QString &role, QWidget *parent)
{

    if (!instance || !QApplication::topLevelWidgets().contains(instance)) {
        instance = new MainWindow(role, parent);
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
MainWindow::MainWindow(const QString &role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Etmp()
    , currentProductRef("")
    , generatedRef("")
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
    QStringList headers = {"Référence", "Couleur", "Genre", "Prix", "Quantité", "Marque", "Catégorie", "Designation", "Date d'expiration"};
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
    
    // Make reference field read-only for auto-generation (will be editable when modifying)
    ui->lineEdit_3->setReadOnly(false);  // Will be set to read-only in clearForm
    clearForm();

    // Wire tableau de bord buttons by their visible text to avoid object-name differences
    const auto buttons = this->findChildren<QPushButton*>();
    for (QPushButton *btn : buttons) {
        const QString label = btn->text().trimmed();
        if (label.compare("Stock", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "stock") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    this->raise();
                    this->activateWindow();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Ventes", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "vente") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    SalesWindow::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Employ", Qt::CaseInsensitive)) {
            if (role == "admin" || role == "employe") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    gestionemploye00::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.startsWith("Client", Qt::CaseInsensitive)) {
            if (role == "admin" || role == "client") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    Gclient1::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        } else if (label.compare("Fournisseur", Qt::CaseInsensitive) == 0) {
            if (role == "admin" || role == "fournisseur") {
                connect(btn, &QPushButton::clicked, this, [this]() {
                    FournisseurWindow::getInstance();
                    this->close();
                });
            } else {
                btn->setEnabled(false);
            }
        }
    }
    Produit p;
    p.afficher(ui);
    p.afficherRestock(ui,10);


    ui->lineEdit_5->setPlaceholderText("Tapez la référence ou designation");
    ui->lineEdit_6->setPlaceholderText("Tapez la référence");

    // Connect Stock button (pushButton_6) to show stock page
    connect(ui->pushButton_6, &QPushButton::clicked, this, [=](){
        ui->travaille->setCurrentIndex(0);
        loadProducts();
        clearForm();  // Auto-generate reference when switching to stock page
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->travaille->setCurrentIndex(0);
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
    clearForm();  // Auto-generate reference when switching to stock page
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->travaille->setCurrentIndex(1);
}




void MainWindow::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}

// Removed duplicate on_pushButton_2_clicked() - using newer implementation below

void MainWindow::on_pushButton_31_clicked()
{
    // Clear form and auto-generate new reference
    clearForm();
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
    // Table column order: Référence, Couleur, Genre, Prix, Quantité, Marque, Catégorie, Designation, Date d'expiration
    QTableWidgetItem* refItem = ui->tableWidget->item(row, 0);
    if (refItem) {
        QString reference = refItem->text().trimmed();
        ui->lineEdit_3->setText(reference); // Référence
        currentProductRef = reference;  // Set current product reference for modify mode
        // Make reference editable when modifying existing product
        ui->lineEdit_3->setReadOnly(false);
        ui->lineEdit_3->setStyleSheet("background-color: rgb(170, 255, 255); color: rgb(0, 0, 0);");
    }
    
    QTableWidgetItem* colorItem = ui->tableWidget->item(row, 1);
    if (colorItem) {
        ui->lineEdit_8->setText(colorItem->text()); // Couleur
    }

    QTableWidgetItem* genreItem = ui->tableWidget->item(row, 2);
    if (genreItem) {
        QString genre = genreItem->text(); // Genre
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
    }

    QTableWidgetItem* priceItem = ui->tableWidget->item(row, 3);
    if (priceItem) {
        ui->lineEdit_36->setText(priceItem->text()); // Prix
    }
    
    QTableWidgetItem* qtyItem = ui->tableWidget->item(row, 4);
    if (qtyItem) {
        ui->lineEdit_9->setText(qtyItem->text()); // Quantité
    }
    
    QTableWidgetItem* brandItem = ui->tableWidget->item(row, 5);
    if (brandItem) {
        ui->lineEdit_7->setText(brandItem->text()); // Marque
    }
    
    QTableWidgetItem* catItem = ui->tableWidget->item(row, 6);
    if (catItem) {
        ui->comboBox_2->setCurrentText(catItem->text()); // Catégorie
    }
    
    QTableWidgetItem* desigItem = ui->tableWidget->item(row, 7);
    if (desigItem) {
        ui->lineEdit_2->setText(desigItem->text()); // Designation
    }
    
    QTableWidgetItem* dateItem = ui->tableWidget->item(row, 8);
    if (dateItem) {
        QDate dateExp = QDate::fromString(dateItem->text(), "yyyy-MM-dd");
        if (dateExp.isValid()) {
            ui->dateEdit->setDate(dateExp); // Date d'expiration
        }
    }
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
    ui->lineEdit_3->clear();  // Référence - user can type it manually
    ui->lineEdit_3->setReadOnly(false);  // Make editable - user can type
    ui->lineEdit_3->setStyleSheet("background-color: rgb(170, 255, 255); color: rgb(0, 0, 0);");  // Normal background
    ui->lineEdit_3->setPlaceholderText("");  // No placeholder - empty like other fields
    currentProductRef = "";  // Clear current ref to indicate new product mode
    generatedRef = "";  // Clear generated reference
    ui->lineEdit_7->clear();  // Marque
    ui->lineEdit_9->clear();  // Quantité
    ui->lineEdit_8->clear();  // Couleur
    ui->lineEdit_36->clear();  // Prix
    ui->dateEdit->setDate(QDate::currentDate());
    ui->radioButton->setChecked(true);  // Male
}

void MainWindow::fillForm(const QString &reference)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        return;
    }
    
    QSqlQuery query(db);
    // Try uppercase first (Oracle default)
    query.prepare("SELECT REFERENCE, DESIGNATION, QUANTITE, PRIX, CATEGORIE, COULEUR, GENRE, MARQUE, DATEEXPIRATION FROM PRODUIT WHERE REFERENCE = :ref");
    query.bindValue(":ref", reference);
    
    if (!query.exec() || !query.next()) {
        // Try lowercase if uppercase fails
        query.clear();
        query.prepare("SELECT reference, designation, quantite, prix, categorie, couleur, genre, marque, date_expiration FROM produit WHERE reference = :ref");
        query.bindValue(":ref", reference);
        if (!query.exec() || !query.next()) {
            qDebug() << "Product not found with reference:" << reference;
            return;
        }
    }
    
    currentProductRef = reference;  // Set current ref to indicate edit mode
    ui->lineEdit_3->setText(query.value(0).toString());  // Référence
    ui->lineEdit_3->setReadOnly(false);  // Make editable when modifying existing product
    ui->lineEdit_3->setStyleSheet("background-color: rgb(170, 255, 255); color: rgb(0, 0, 0);");  // Normal background
    ui->lineEdit_2->setText(query.value(1).toString());  // Designation (Nom)
    ui->lineEdit_9->setText(query.value(2).toString());  // Quantité
    // Set price in lineEdit_36
    double prix = query.value(3).toDouble();
    ui->lineEdit_36->setText(QString::number(prix, 'f', 2));  // Prix
    ui->comboBox_2->setCurrentText(query.value(4).toString());  // Catégorie (use comboBox_2)
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

void MainWindow::on_pushButton_2_clicked()  // Valider - Add/Modify
{
    // Validate required fields
    if (ui->lineEdit_2->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom du produit (designation) est requis!");
        return;
    }
    
    QString refText = ui->lineEdit_3->text().trimmed();
    
    // User types the reference manually - validate it's not empty
    if (refText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une référence pour le produit!");
        return;
    }
    
    qDebug() << "🔍 Processing product with reference (user-entered):" << refText;
    
    // Reference can be any string (alphanumeric like "C12", "REF47", etc.)
    // No numeric validation needed - accept any string
    qDebug() << "🔍 Processing product with reference (string):" << refText;
    
    // Validate price
    bool prixOk = false;
    double prix = ui->lineEdit_36->text().toDouble(&prixOk);
    if (!prixOk || prix < 0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre valide et positif!");
        return;
    }
    
    Produit p;
    p.setRef(refText);  // Set reference first
    p.setDesignation(ui->lineEdit_2->text().trimmed());
    p.setQuantite(ui->lineEdit_9->text().toInt());
    p.setPrix(prix);  // Use lineEdit_36 for price
    p.setCategorie(ui->comboBox_2->currentText());
    p.setCouleur(ui->lineEdit_8->text().trimmed());
    p.setgenre(ui);  // setgenre takes UI pointer
    p.setMarque(ui->lineEdit_7->text().trimmed());
    p.setDateExpiration(ui->dateEdit->date());
    
    bool success = false;
    
    // Check if product exists
    Produit checkProd;
    if (checkProd.existe(refText)) {
        // Product exists, modify it
        success = p.modifier();
        if (success) {
            loadProducts();
            clearForm();
            QMessageBox::information(this, "Succès", "Produit modifié avec succès!");
            scrollToProduct(refText);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du produit!");
        }
    } else {
        // Product doesn't exist, add new
        success = p.ajouter();
        if (success) {
            // Refresh table immediately before showing message
            loadProducts();
            
            // Highlight the newly added product in the table (yellow zone)
            highlightProductInTable(refText);
            
            // Clear form FIRST to generate next REF reference
            clearForm();  // This will generate REF8, REF9, etc. for next product
            
            QMessageBox::information(this, "Succès", QString("Produit ajouté avec succès!\nRéférence: %1").arg(refText));
            
            // Scroll to the newly added product (use the old refText before clearForm)
            scrollToProduct(refText);
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du produit!");
        }
    }
}

void MainWindow::on_pushButton_5_clicked()  // Delete
{
    QString reference = "";
    
    // First, try to get reference from lineEdit_6 (bottom interface input)
    QString refFromInput = ui->lineEdit_6->text().trimmed();
    if (!refFromInput.isEmpty()) {
        reference = refFromInput;
    } else {
        // If no input, try to get from selected row in table
        int currentRow = ui->tableWidget->currentRow();
        if (currentRow >= 0) {
            // Column 0 is Référence according to the table structure
            QTableWidgetItem* refItem = ui->tableWidget->item(currentRow, 0);
            if (refItem) {
                reference = refItem->text().trimmed();
            }
        }
    }
    
    if (reference.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un produit dans le tableau ou entrer une référence dans le champ de suppression!");
        return;
    }
    
    // Verify product exists
    Produit checkProd;
    if (!checkProd.existe(reference)) {
        QMessageBox::warning(this, "Erreur", QString("Le produit avec la référence '%1' n'existe pas!").arg(reference));
        return;
    }
    
    int ret = QMessageBox::question(this, "Confirmation", 
                                     QString("Êtes-vous sûr de vouloir supprimer le produit (Réf: %1)?").arg(reference),
                                     QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        Produit p;
        if (p.supprimer(reference)) {
            QMessageBox::information(this, "Succès", "Produit supprimé avec succès!");
            loadProducts();
            clearForm();
            ui->lineEdit_6->clear();  // Clear the delete input field
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
    // Column 0 is Référence according to the table structure
    QTableWidgetItem* refItem = ui->tableWidget->item(row, 0);
    if (refItem) {
        QString reference = refItem->text().trimmed();
        if (!reference.isEmpty()) {
            fillForm(reference);
        }
    }
}

void MainWindow::scrollToProduct(const QString &reference)
{
    // Find the product in the table and scroll to it
    // Column 0 is Référence
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* refItem = ui->tableWidget->item(row, 0);  // Référence column
        if (refItem && refItem->text().trimmed() == reference) {
            ui->tableWidget->scrollToItem(refItem, QAbstractItemView::EnsureVisible);
            ui->tableWidget->selectRow(row);
            ui->tableWidget->setCurrentCell(row, 0);
            break;
        }
    }
}

void MainWindow::highlightProductInTable(const QString &reference)
{
    // Find the product in the table and highlight it in yellow
    // Column 0 is Référence
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* refItem = ui->tableWidget->item(row, 0);  // Référence column
        if (refItem && refItem->text().trimmed() == reference) {
            // Highlight the entire row in yellow
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item) {
                    item->setBackground(QBrush(QColor(255, 255, 0)));  // Yellow background
                } else {
                    // Create item if it doesn't exist
                    QTableWidgetItem* newItem = new QTableWidgetItem();
                    newItem->setBackground(QBrush(QColor(255, 255, 0)));  // Yellow background
                    ui->tableWidget->setItem(row, col, newItem);
                }
            }
            // Scroll to the highlighted product
            ui->tableWidget->scrollToItem(refItem, QAbstractItemView::EnsureVisible);
            ui->tableWidget->selectRow(row);
            break;
        }
    }
}

QString MainWindow::generateNextReference(const QString &prefix)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        // If database not available, return default
        qDebug() << "⚠️ Database not available, returning default reference";
        return prefix + "1";
    }
    
    QSqlQuery query(db);
    int maxNumber = 0;
    
    // For "REF" prefix, ONLY search for "REF" pattern (not numeric-only references)
    QString pattern;
    if (prefix.toUpper() == "REF") {
        // Only match references that start with "REF" followed by digits
        pattern = "REF%";  // Will match "REF1", "REF2", "REF47", etc.
    } else {
        pattern = prefix + "%";
    }
    
    // Try uppercase table name first (Oracle default)
    // Simple query - we'll filter in C++ to only get REF references
    QString sqlQuery = QString("SELECT REFERENCE FROM PRODUIT WHERE UPPER(REFERENCE) LIKE :pattern ORDER BY REFERENCE DESC");
    query.prepare(sqlQuery);
    query.bindValue(":pattern", pattern.toUpper());
    
    if (!query.exec()) {
        // Try lowercase table name
        query.clear();
        sqlQuery = QString("SELECT reference FROM produit WHERE UPPER(reference) LIKE :pattern ORDER BY reference DESC");
        query.prepare(sqlQuery);
        query.bindValue(":pattern", pattern.toUpper());
        if (!query.exec()) {
            qDebug() << "❌ Error generating reference:" << query.lastError().text();
            return prefix + "1";
        }
    }
    
    // Find the highest number for the given prefix
    // Handle both "REF" and "REFF" prefixes (normalize "REFF" to "REF")
    if (prefix.toUpper() == "REF") {
        // Check for both "REF" and "REFF" patterns, but ONLY if they start with REF
        while (query.next()) {
            QString ref = query.value(0).toString().trimmed();
            QString upperRef = ref.toUpper();
            // ONLY process if it starts with "REF" (not pure numbers)
            if (upperRef.startsWith("REF") && upperRef.length() > 3) {
                // Normalize "REFF" to "REF" for number extraction
                QString numberPart;
                if (upperRef.startsWith("REFF")) {
                    numberPart = ref.mid(4);  // Skip "REFF"
                } else if (upperRef.startsWith("REF")) {
                    numberPart = ref.mid(3);  // Skip "REF"
                }
                // Only process if there's a number part
                if (!numberPart.isEmpty()) {
                    bool ok;
                    int num = numberPart.toInt(&ok);
                    if (ok && num > maxNumber) {
                        maxNumber = num;
                        qDebug() << "Found REF reference:" << ref << "-> number:" << num;
                    }
                }
            }
        }
    } else {
        // For other prefixes like "C"
        while (query.next()) {
            QString ref = query.value(0).toString();
            // Extract number part after prefix (e.g., "C33" -> 33)
            if (ref.toUpper().startsWith(prefix.toUpper())) {
                QString numberPart = ref.mid(prefix.length());
                bool ok;
                int num = numberPart.toInt(&ok);
                if (ok && num > maxNumber) {
                    maxNumber = num;
                }
            }
        }
    }
    
    // Generate next reference - always use "REF" (not "REFF") if prefix is "REF"
    QString finalPrefix = (prefix.toUpper() == "REF") ? "REF" : prefix;
    int nextNumber = maxNumber + 1;
    QString newRef = finalPrefix + QString::number(nextNumber);
    
    qDebug() << "🔧 Generated next reference:" << newRef << "(max found:" << maxNumber << ", prefix:" << prefix << ")";
    return newRef;
}

QString MainWindow::detectBestPrefix()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        return "REF";  // Default to "REF" instead of "C"
    }
    
    QSqlQuery query(db);
    int refCount = 0;
    int cCount = 0;
    
    // Count references starting with "REF" (case insensitive) - includes "REFF" variations
    QString sqlQuery = "SELECT COUNT(*) FROM PRODUIT WHERE (UPPER(REFERENCE) LIKE 'REF%' OR UPPER(REFERENCE) LIKE 'REFF%')";
    query.prepare(sqlQuery);
    
    if (!query.exec()) {
        // Try lowercase table name
        query.clear();
        sqlQuery = "SELECT COUNT(*) FROM produit WHERE (UPPER(reference) LIKE 'REF%' OR UPPER(reference) LIKE 'REFF%')";
        query.prepare(sqlQuery);
        if (!query.exec()) {
            return "REF";  // Default to "REF" if query fails
        }
    }
    
    if (query.next()) {
        refCount = query.value(0).toInt();
    }
    
    // Count references starting with "C" (case insensitive, but not "REF" or "REFF")
    query.clear();
    sqlQuery = "SELECT COUNT(*) FROM PRODUIT WHERE UPPER(REFERENCE) LIKE 'C%' AND UPPER(REFERENCE) NOT LIKE 'REF%' AND UPPER(REFERENCE) NOT LIKE 'REFF%'";
    query.prepare(sqlQuery);
    
    if (!query.exec()) {
        // Try lowercase table name
        query.clear();
        sqlQuery = "SELECT COUNT(*) FROM produit WHERE UPPER(reference) LIKE 'C%' AND UPPER(reference) NOT LIKE 'REF%' AND UPPER(reference) NOT LIKE 'REFF%'";
        query.prepare(sqlQuery);
        if (!query.exec()) {
            return "REF";  // Default to "REF" if query fails
        }
    }
    
    if (query.next()) {
        cCount = query.value(0).toInt();
    }
    
    // Always use "REF" (not "REFF") - normalize any "REFF" to "REF"
    // Use "REF" if there are more REF/REFF references, otherwise use "C"
    QString prefix = (refCount > cCount) ? "REF" : "C";
    qDebug() << "🔍 Detected prefix:" << prefix << "(REF/REFF count:" << refCount << ", C count:" << cCount << ")";
    return prefix;
}
