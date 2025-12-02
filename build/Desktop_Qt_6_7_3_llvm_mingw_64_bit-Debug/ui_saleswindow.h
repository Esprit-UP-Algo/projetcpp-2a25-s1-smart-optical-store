/********************************************************************************
** Form generated from reading UI file 'saleswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALESWINDOW_H
#define UI_SALESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalesWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headerLayout;
    QSpacerItem *headerSpacer;
    QLabel *topRightLogoLabel;
    QTabWidget *tabWidget;
    QWidget *newSaleTab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *customerGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *customerIdLabel;
    QLineEdit *customerIdLineEdit;
    QPushButton *customerSearchButton;
    QLabel *customerNameLabel;
    QLineEdit *customerNameLineEdit;
    QLabel *loyaltyLevelLabel;
    QLabel *loyaltyLevelValueLabel;
    QGroupBox *productGroupBox;
    QGridLayout *gridLayout;
    QLabel *productIdLabel;
    QComboBox *productComboBox;
    QLabel *quantityLabel;
    QSpinBox *quantitySpinBox;
    QLabel *productNameLabel;
    QLineEdit *productNameLineEdit;
    QLabel *priceLabel;
    QLineEdit *priceLineEdit;
    QPushButton *addProductButton;
    QGroupBox *cartGroupBox;
    QVBoxLayout *verticalLayout_4;
    QTableView *cartTableView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *removeProductButton;
    QGridLayout *totalsLayout;
    QLabel *label;
    QLabel *subtotalLabel;
    QLabel *label_2;
    QLabel *taxLabel;
    QLabel *promoCodeLabel;
    QHBoxLayout *promoCodeLayout;
    QLineEdit *promoCodeLineEdit;
    QPushButton *applyPromoButton;
    QLabel *discountLabel;
    QLabel *discountValueLabel;
    QLabel *label_3;
    QLabel *totalLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *paymentMethodLabel;
    QComboBox *paymentMethodComboBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *newSaleButton;
    QPushButton *saveSaleButton;
    QWidget *salesHistoryTab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *searchLabel;
    QLineEdit *searchSalesLineEdit;
    QCheckBox *dateFilterCheckBox;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;
    QLabel *endDateLabel;
    QDateEdit *endDateEdit;
    QLabel *sortLabel;
    QComboBox *sortComboBox;
    QPushButton *sortButton;
    QTableView *salesTableView;
    QHBoxLayout *exportButtonLayout;
    QSpacerItem *horizontalSpacer_export;
    QPushButton *exportPdfButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SalesWindow)
    {
        if (SalesWindow->objectName().isEmpty())
            SalesWindow->setObjectName("SalesWindow");
        SalesWindow->resize(1235, 800);
        SalesWindow->setStyleSheet(QString::fromUtf8("background-color:#b8e2f2; color: black;"));
        centralwidget = new QWidget(SalesWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setMinimumSize(QSize(220, 0));
        sidebarWidget->setMaximumSize(QSize(220, 16777215));
        verticalLayout = new QVBoxLayout(sidebarWidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(sidebarWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
" border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;     \n"
"background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;       /* title centered */\n"
"    padding: 2px 10px;\n"
"}"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(0, 420, 201, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("#pushButton_4 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_4:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_4:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 120, 201, 51));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(0, 320, 201, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("#pushButton_3 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_3:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_3:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 220, 201, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(0, 520, 201, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("#pushButton_5 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_5:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_5:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(0, 620, 201, 51));
        pushButton_6->setStyleSheet(QString::fromUtf8("#pushButton_6 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_6:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_6:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}"));

        verticalLayout->addWidget(groupBox);


        horizontalLayout->addWidget(sidebarWidget);

        contentWidget = new QWidget(centralwidget);
        contentWidget->setObjectName("contentWidget");
        verticalLayout_2 = new QVBoxLayout(contentWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        topRightLogoLabel = new QLabel(contentWidget);
        topRightLogoLabel->setObjectName("topRightLogoLabel");
        topRightLogoLabel->setMinimumSize(QSize(60, 60));
        topRightLogoLabel->setMaximumSize(QSize(60, 60));
        topRightLogoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        topRightLogoLabel->setScaledContents(true);
        topRightLogoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        headerLayout->addWidget(topRightLogoLabel);


        verticalLayout_2->addLayout(headerLayout);

        tabWidget = new QTabWidget(contentWidget);
        tabWidget->setObjectName("tabWidget");
        newSaleTab = new QWidget();
        newSaleTab->setObjectName("newSaleTab");
        verticalLayout_3 = new QVBoxLayout(newSaleTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        customerGroupBox = new QGroupBox(newSaleTab);
        customerGroupBox->setObjectName("customerGroupBox");
        customerGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;\n"
""));
        horizontalLayout_2 = new QHBoxLayout(customerGroupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        customerIdLabel = new QLabel(customerGroupBox);
        customerIdLabel->setObjectName("customerIdLabel");
        customerIdLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_2->addWidget(customerIdLabel);

        customerIdLineEdit = new QLineEdit(customerGroupBox);
        customerIdLineEdit->setObjectName("customerIdLineEdit");
        customerIdLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));

        horizontalLayout_2->addWidget(customerIdLineEdit);

        customerSearchButton = new QPushButton(customerGroupBox);
        customerSearchButton->setObjectName("customerSearchButton");
        customerSearchButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_2->addWidget(customerSearchButton);

        customerNameLabel = new QLabel(customerGroupBox);
        customerNameLabel->setObjectName("customerNameLabel");
        customerNameLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_2->addWidget(customerNameLabel);

        customerNameLineEdit = new QLineEdit(customerGroupBox);
        customerNameLineEdit->setObjectName("customerNameLineEdit");
        customerNameLineEdit->setEnabled(true);
        customerNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        customerNameLineEdit->setReadOnly(false);

        horizontalLayout_2->addWidget(customerNameLineEdit);

        loyaltyLevelLabel = new QLabel(customerGroupBox);
        loyaltyLevelLabel->setObjectName("loyaltyLevelLabel");
        loyaltyLevelLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_2->addWidget(loyaltyLevelLabel);

        loyaltyLevelValueLabel = new QLabel(customerGroupBox);
        loyaltyLevelValueLabel->setObjectName("loyaltyLevelValueLabel");
        loyaltyLevelValueLabel->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;\n"
"color: black;\n"
"font-weight: bold;"));

        horizontalLayout_2->addWidget(loyaltyLevelValueLabel);


        verticalLayout_3->addWidget(customerGroupBox);

        productGroupBox = new QGroupBox(newSaleTab);
        productGroupBox->setObjectName("productGroupBox");
        productGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));
        gridLayout = new QGridLayout(productGroupBox);
        gridLayout->setObjectName("gridLayout");
        productIdLabel = new QLabel(productGroupBox);
        productIdLabel->setObjectName("productIdLabel");
        productIdLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        productIdLabel->setFrameShape(QFrame::Shape::Box);

        gridLayout->addWidget(productIdLabel, 0, 0, 1, 1);

        productComboBox = new QComboBox(productGroupBox);
        productComboBox->setObjectName("productComboBox");
        productComboBox->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        productComboBox->setEditable(false);

        gridLayout->addWidget(productComboBox, 0, 1, 1, 2);

        quantityLabel = new QLabel(productGroupBox);
        quantityLabel->setObjectName("quantityLabel");
        quantityLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(quantityLabel, 0, 3, 1, 1);

        quantitySpinBox = new QSpinBox(productGroupBox);
        quantitySpinBox->setObjectName("quantitySpinBox");
        quantitySpinBox->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        quantitySpinBox->setMinimum(1);
        quantitySpinBox->setMaximum(999);

        gridLayout->addWidget(quantitySpinBox, 0, 4, 1, 1);

        productNameLabel = new QLabel(productGroupBox);
        productNameLabel->setObjectName("productNameLabel");
        productNameLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(productNameLabel, 1, 0, 1, 1);

        productNameLineEdit = new QLineEdit(productGroupBox);
        productNameLineEdit->setObjectName("productNameLineEdit");
        productNameLineEdit->setEnabled(true);
        productNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        productNameLineEdit->setReadOnly(true);

        gridLayout->addWidget(productNameLineEdit, 1, 1, 1, 2);

        priceLabel = new QLabel(productGroupBox);
        priceLabel->setObjectName("priceLabel");
        priceLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(priceLabel, 1, 3, 1, 1);

        priceLineEdit = new QLineEdit(productGroupBox);
        priceLineEdit->setObjectName("priceLineEdit");
        priceLineEdit->setEnabled(true);
        priceLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        priceLineEdit->setReadOnly(true);

        gridLayout->addWidget(priceLineEdit, 1, 4, 1, 1);

        addProductButton = new QPushButton(productGroupBox);
        addProductButton->setObjectName("addProductButton");
        addProductButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        gridLayout->addWidget(addProductButton, 1, 5, 1, 1);


        verticalLayout_3->addWidget(productGroupBox);

        cartGroupBox = new QGroupBox(newSaleTab);
        cartGroupBox->setObjectName("cartGroupBox");
        cartGroupBox->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: rgb(41, 102, 148);"));
        verticalLayout_4 = new QVBoxLayout(cartGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        cartTableView = new QTableView(cartGroupBox);
        cartTableView->setObjectName("cartTableView");
        cartTableView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;"));
        cartTableView->setFrameShape(QFrame::Shape::Panel);
        cartTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        cartTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_4->addWidget(cartTableView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        removeProductButton = new QPushButton(cartGroupBox);
        removeProductButton->setObjectName("removeProductButton");
        removeProductButton->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;\n"
"color: black;\n"
""));

        horizontalLayout_3->addWidget(removeProductButton);

        totalsLayout = new QGridLayout();
        totalsLayout->setObjectName("totalsLayout");
        label = new QLabel(cartGroupBox);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(label, 0, 0, 1, 1);

        subtotalLabel = new QLabel(cartGroupBox);
        subtotalLabel->setObjectName("subtotalLabel");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        subtotalLabel->setFont(font);
        subtotalLabel->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;"));
        subtotalLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(subtotalLabel, 0, 1, 1, 1);

        label_2 = new QLabel(cartGroupBox);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        label_2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(label_2, 1, 0, 1, 1);

        taxLabel = new QLabel(cartGroupBox);
        taxLabel->setObjectName("taxLabel");
        taxLabel->setFont(font);
        taxLabel->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;"));
        taxLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(taxLabel, 1, 1, 1, 1);

        promoCodeLabel = new QLabel(cartGroupBox);
        promoCodeLabel->setObjectName("promoCodeLabel");
        promoCodeLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        promoCodeLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(promoCodeLabel, 2, 0, 1, 1);

        promoCodeLayout = new QHBoxLayout();
        promoCodeLayout->setSpacing(5);
        promoCodeLayout->setContentsMargins(0, 0, 0, 0);
        promoCodeLayout->setObjectName("promoCodeLayout");
        promoCodeLineEdit = new QLineEdit(cartGroupBox);
        promoCodeLineEdit->setObjectName("promoCodeLineEdit");
        promoCodeLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;\n"
"color: black;"));

        promoCodeLayout->addWidget(promoCodeLineEdit);

        applyPromoButton = new QPushButton(cartGroupBox);
        applyPromoButton->setObjectName("applyPromoButton");
        applyPromoButton->setMinimumSize(QSize(80, 0));
        applyPromoButton->setMaximumSize(QSize(80, 16777215));
        applyPromoButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        promoCodeLayout->addWidget(applyPromoButton);


        totalsLayout->addLayout(promoCodeLayout, 2, 1, 1, 1);

        discountLabel = new QLabel(cartGroupBox);
        discountLabel->setObjectName("discountLabel");
        discountLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        discountLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(discountLabel, 3, 0, 1, 1);

        discountValueLabel = new QLabel(cartGroupBox);
        discountValueLabel->setObjectName("discountValueLabel");
        discountValueLabel->setFont(font);
        discountValueLabel->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;\n"
"color: green;"));
        discountValueLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(discountValueLabel, 3, 1, 1, 1);

        label_3 = new QLabel(cartGroupBox);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(label_3, 4, 0, 1, 1);

        totalLabel = new QLabel(cartGroupBox);
        totalLabel->setObjectName("totalLabel");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        totalLabel->setFont(font1);
        totalLabel->setStyleSheet(QString::fromUtf8("background-color: #87CEEB;"));
        totalLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        totalsLayout->addWidget(totalLabel, 4, 1, 1, 1);


        horizontalLayout_3->addLayout(totalsLayout);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(cartGroupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        paymentMethodLabel = new QLabel(newSaleTab);
        paymentMethodLabel->setObjectName("paymentMethodLabel");
        paymentMethodLabel->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: white;"));

        horizontalLayout_4->addWidget(paymentMethodLabel);

        paymentMethodComboBox = new QComboBox(newSaleTab);
        paymentMethodComboBox->setObjectName("paymentMethodComboBox");
        paymentMethodComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));

        horizontalLayout_4->addWidget(paymentMethodComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        newSaleButton = new QPushButton(newSaleTab);
        newSaleButton->setObjectName("newSaleButton");
        newSaleButton->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: rgb(41, 102, 148);"));

        horizontalLayout_4->addWidget(newSaleButton);

        saveSaleButton = new QPushButton(newSaleTab);
        saveSaleButton->setObjectName("saveSaleButton");
        saveSaleButton->setMinimumSize(QSize(150, 40));
        saveSaleButton->setFont(font);
        saveSaleButton->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: white;"));

        horizontalLayout_4->addWidget(saveSaleButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(newSaleTab, QString());
        salesHistoryTab = new QWidget();
        salesHistoryTab->setObjectName("salesHistoryTab");
        verticalLayout_5 = new QVBoxLayout(salesHistoryTab);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        searchLabel = new QLabel(salesHistoryTab);
        searchLabel->setObjectName("searchLabel");
        searchLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_5->addWidget(searchLabel);

        searchSalesLineEdit = new QLineEdit(salesHistoryTab);
        searchSalesLineEdit->setObjectName("searchSalesLineEdit");
        searchSalesLineEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));

        horizontalLayout_5->addWidget(searchSalesLineEdit);

        dateFilterCheckBox = new QCheckBox(salesHistoryTab);
        dateFilterCheckBox->setObjectName("dateFilterCheckBox");
        dateFilterCheckBox->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_5->addWidget(dateFilterCheckBox);

        startDateLabel = new QLabel(salesHistoryTab);
        startDateLabel->setObjectName("startDateLabel");
        startDateLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_5->addWidget(startDateLabel);

        startDateEdit = new QDateEdit(salesHistoryTab);
        startDateEdit->setObjectName("startDateEdit");
        startDateEdit->setEnabled(false);
        startDateEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        startDateEdit->setCalendarPopup(true);

        horizontalLayout_5->addWidget(startDateEdit);

        endDateLabel = new QLabel(salesHistoryTab);
        endDateLabel->setObjectName("endDateLabel");
        endDateLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_5->addWidget(endDateLabel);

        endDateEdit = new QDateEdit(salesHistoryTab);
        endDateEdit->setObjectName("endDateEdit");
        endDateEdit->setEnabled(false);
        endDateEdit->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        endDateEdit->setCalendarPopup(true);

        horizontalLayout_5->addWidget(endDateEdit);

        sortLabel = new QLabel(salesHistoryTab);
        sortLabel->setObjectName("sortLabel");
        sortLabel->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color:black;"));

        horizontalLayout_5->addWidget(sortLabel);

        sortComboBox = new QComboBox(salesHistoryTab);
        sortComboBox->setObjectName("sortComboBox");
        sortComboBox->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));

        horizontalLayout_5->addWidget(sortComboBox);

        sortButton = new QPushButton(salesHistoryTab);
        sortButton->setObjectName("sortButton");
        sortButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff; color: black;"));

        horizontalLayout_5->addWidget(sortButton);


        verticalLayout_5->addLayout(horizontalLayout_5);

        salesTableView = new QTableView(salesHistoryTab);
        salesTableView->setObjectName("salesTableView");
        salesTableView->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;\n"
"color:black;"));
        salesTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        salesTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_5->addWidget(salesTableView);

        exportButtonLayout = new QHBoxLayout();
        exportButtonLayout->setObjectName("exportButtonLayout");
        horizontalSpacer_export = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        exportButtonLayout->addItem(horizontalSpacer_export);

        exportPdfButton = new QPushButton(salesHistoryTab);
        exportPdfButton->setObjectName("exportPdfButton");
        exportPdfButton->setMinimumSize(QSize(200, 40));
        exportPdfButton->setFont(font);
        exportPdfButton->setStyleSheet(QString::fromUtf8("background-color: #55aaff;\n"
"color: black;"));

        exportButtonLayout->addWidget(exportPdfButton);


        verticalLayout_5->addLayout(exportButtonLayout);

        tabWidget->addTab(salesHistoryTab, QString());

        verticalLayout_2->addWidget(tabWidget);


        horizontalLayout->addWidget(contentWidget);

        SalesWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SalesWindow);
        statusbar->setObjectName("statusbar");
        SalesWindow->setStatusBar(statusbar);

        retranslateUi(SalesWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SalesWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SalesWindow)
    {
        SalesWindow->setWindowTitle(QCoreApplication::translate("SalesWindow", "Sales Management - Smart Optical Store", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SalesWindow", "Tableau de board", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SalesWindow", "Clients", nullptr));
        pushButton->setText(QCoreApplication::translate("SalesWindow", "Stock", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SalesWindow", "Employes", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SalesWindow", "Ventes", nullptr));
        pushButton_5->setText(QCoreApplication::translate("SalesWindow", "Fournisseur", nullptr));
        pushButton_6->setText(QCoreApplication::translate("SalesWindow", "Codes Promo", nullptr));
        topRightLogoLabel->setText(QString());
        customerGroupBox->setTitle(QCoreApplication::translate("SalesWindow", "Informations Client", nullptr));
        customerIdLabel->setText(QCoreApplication::translate("SalesWindow", "ID Client :", nullptr));
        customerIdLineEdit->setText(QString());
        customerIdLineEdit->setPlaceholderText(QCoreApplication::translate("SalesWindow", "Entrer l'ID client", nullptr));
        customerSearchButton->setText(QCoreApplication::translate("SalesWindow", "Rechercher", nullptr));
        customerNameLabel->setText(QCoreApplication::translate("SalesWindow", "Nom du Client :", nullptr));
        loyaltyLevelLabel->setText(QCoreApplication::translate("SalesWindow", "Fid\303\251lit\303\251 :", nullptr));
        loyaltyLevelValueLabel->setText(QCoreApplication::translate("SalesWindow", "-", nullptr));
        productGroupBox->setTitle(QCoreApplication::translate("SalesWindow", "Ajouter un Produit", nullptr));
        productIdLabel->setText(QCoreApplication::translate("SalesWindow", " S\303\251lectionner Produit :", nullptr));
        quantityLabel->setText(QCoreApplication::translate("SalesWindow", "Quantit\303\251 :", nullptr));
        productNameLabel->setText(QCoreApplication::translate("SalesWindow", " Nom du Produit :", nullptr));
        priceLabel->setText(QCoreApplication::translate("SalesWindow", "  Prix :", nullptr));
        addProductButton->setText(QCoreApplication::translate("SalesWindow", "Ajouter au Panier", nullptr));
        cartGroupBox->setTitle(QCoreApplication::translate("SalesWindow", "Panier", nullptr));
        removeProductButton->setText(QCoreApplication::translate("SalesWindow", "Supprimer l'Article S\303\251lectionn\303\251", nullptr));
        label->setText(QCoreApplication::translate("SalesWindow", "HT-total :", nullptr));
        subtotalLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("SalesWindow", "Taxe :", nullptr));
        taxLabel->setText(QString());
        promoCodeLabel->setText(QCoreApplication::translate("SalesWindow", "Code Promo :", nullptr));
        applyPromoButton->setText(QCoreApplication::translate("SalesWindow", "Appliquer", nullptr));
        discountLabel->setText(QCoreApplication::translate("SalesWindow", "Remise :", nullptr));
        discountValueLabel->setText(QString());
        label_3->setText(QCoreApplication::translate("SalesWindow", "Total:", nullptr));
        totalLabel->setText(QString());
        paymentMethodLabel->setText(QCoreApplication::translate("SalesWindow", "M\303\251thode de Paiement :", nullptr));
        newSaleButton->setText(QCoreApplication::translate("SalesWindow", "Nouvelle Vente", nullptr));
        saveSaleButton->setText(QCoreApplication::translate("SalesWindow", "Valider la Vente", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newSaleTab), QCoreApplication::translate("SalesWindow", " Vente", nullptr));
        searchLabel->setText(QCoreApplication::translate("SalesWindow", "Rechercher", nullptr));
        searchSalesLineEdit->setPlaceholderText(QCoreApplication::translate("SalesWindow", "Rechercher par ID de vente", nullptr));
        dateFilterCheckBox->setText(QCoreApplication::translate("SalesWindow", "Filtrer par date", nullptr));
        startDateLabel->setText(QCoreApplication::translate("SalesWindow", "Date de :", nullptr));
        endDateLabel->setText(QCoreApplication::translate("SalesWindow", "Date a :", nullptr));
        sortLabel->setText(QCoreApplication::translate("SalesWindow", "Trier par :", nullptr));
        sortButton->setText(QCoreApplication::translate("SalesWindow", "Trier", nullptr));
        exportPdfButton->setText(QCoreApplication::translate("SalesWindow", "Exporter Ventes en PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(salesHistoryTab), QCoreApplication::translate("SalesWindow", "Historique ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SalesWindow: public Ui_SalesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALESWINDOW_H
