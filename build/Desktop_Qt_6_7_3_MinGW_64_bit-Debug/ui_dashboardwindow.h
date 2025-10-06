/********************************************************************************
** Form generated from reading UI file 'dashboardwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARDWINDOW_H
#define UI_DASHBOARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *topSpacer;
    QLabel *storeNameLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *dashboardButton;
    QPushButton *salesButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *logoutButton;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headerLayout;
    QLabel *welcomeLabel;
    QSpacerItem *headerSpacer;
    QLabel *topRightLogoLabel;
    QLabel *dateTimeLabel;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *statsLayout;
    QFrame *customersFrame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *customersCountLabel;
    QFrame *productsFrame;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLabel *productsCountLabel;
    QFrame *salesFrame;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLabel *salesCountLabel;
    QHBoxLayout *statsLayout2;
    QFrame *todaySalesFrame;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QLabel *todaySalesLabel;
    QFrame *todayRevenueFrame;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QLabel *todayRevenueLabel;
    QFrame *lowStockFrame;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_6;
    QLabel *lowStockLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *recentSalesLabel;
    QTableWidget *recentSalesTable;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DashboardWindow)
    {
        if (DashboardWindow->objectName().isEmpty())
            DashboardWindow->setObjectName("DashboardWindow");
        DashboardWindow->resize(1024, 768);
        DashboardWindow->setStyleSheet(QString::fromUtf8("background-color: #55aaff; color: black;"));
        centralwidget = new QWidget(DashboardWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setMinimumSize(QSize(220, 0));
        sidebarWidget->setMaximumSize(QSize(220, 16777215));
        verticalLayout = new QVBoxLayout(sidebarWidget);
        verticalLayout->setObjectName("verticalLayout");
        topSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(topSpacer);

        storeNameLabel = new QLabel(sidebarWidget);
        storeNameLabel->setObjectName("storeNameLabel");
        storeNameLabel->setMinimumSize(QSize(0, 80));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        storeNameLabel->setFont(font);
        storeNameLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: white;\n"
"border: 2px solid #87CEEB;\n"
"border-radius: 10px;\n"
"padding: 10px;\n"
"\n"
""));
        storeNameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(storeNameLabel);

        verticalSpacer = new QSpacerItem(60, 125, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        dashboardButton = new QPushButton(sidebarWidget);
        dashboardButton->setObjectName("dashboardButton");
        dashboardButton->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setPointSize(10);
        dashboardButton->setFont(font1);
        dashboardButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        dashboardButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: white;\n"
"\n"
""));
        dashboardButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(dashboardButton);

        salesButton = new QPushButton(sidebarWidget);
        salesButton->setObjectName("salesButton");
        salesButton->setMinimumSize(QSize(0, 50));
        salesButton->setFont(font1);
        salesButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        salesButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: white;\n"
"\n"
""));
        salesButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(salesButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        logoutButton = new QPushButton(sidebarWidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setMinimumSize(QSize(0, 50));
        logoutButton->setFont(font1);
        logoutButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        logoutButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
"color: white;\n"
"\n"
""));
        logoutButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(logoutButton);


        horizontalLayout->addWidget(sidebarWidget);

        contentWidget = new QWidget(centralwidget);
        contentWidget->setObjectName("contentWidget");
        contentWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        verticalLayout_2 = new QVBoxLayout(contentWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        welcomeLabel = new QLabel(contentWidget);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        welcomeLabel->setFont(font2);
        welcomeLabel->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
"\n"
""));

        headerLayout->addWidget(welcomeLabel);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        topRightLogoLabel = new QLabel(contentWidget);
        topRightLogoLabel->setObjectName("topRightLogoLabel");
        topRightLogoLabel->setMinimumSize(QSize(60, 60));
        topRightLogoLabel->setMaximumSize(QSize(60, 60));
        topRightLogoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logo.jpg")));
        topRightLogoLabel->setScaledContents(true);
        topRightLogoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        headerLayout->addWidget(topRightLogoLabel);


        verticalLayout_2->addLayout(headerLayout);

        dateTimeLabel = new QLabel(contentWidget);
        dateTimeLabel->setObjectName("dateTimeLabel");
        dateTimeLabel->setFont(font1);
        dateTimeLabel->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
"\n"
""));

        verticalLayout_2->addWidget(dateTimeLabel);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        statsLayout = new QHBoxLayout();
        statsLayout->setObjectName("statsLayout");
        customersFrame = new QFrame(contentWidget);
        customersFrame->setObjectName("customersFrame");
        customersFrame->setMinimumSize(QSize(180, 120));
        customersFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        customersFrame->setFrameShape(QFrame::Shape::StyledPanel);
        customersFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(customersFrame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(customersFrame);
        label->setObjectName("label");
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        customersCountLabel = new QLabel(customersFrame);
        customersCountLabel->setObjectName("customersCountLabel");
        QFont font3;
        font3.setPointSize(24);
        font3.setBold(true);
        customersCountLabel->setFont(font3);
        customersCountLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(customersCountLabel);


        statsLayout->addWidget(customersFrame);

        productsFrame = new QFrame(contentWidget);
        productsFrame->setObjectName("productsFrame");
        productsFrame->setMinimumSize(QSize(180, 120));
        productsFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        productsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        productsFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(productsFrame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(productsFrame);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        productsCountLabel = new QLabel(productsFrame);
        productsCountLabel->setObjectName("productsCountLabel");
        productsCountLabel->setFont(font3);
        productsCountLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(productsCountLabel);


        statsLayout->addWidget(productsFrame);

        salesFrame = new QFrame(contentWidget);
        salesFrame->setObjectName("salesFrame");
        salesFrame->setMinimumSize(QSize(180, 120));
        salesFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        salesFrame->setFrameShape(QFrame::Shape::StyledPanel);
        salesFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(salesFrame);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_3 = new QLabel(salesFrame);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_3);

        salesCountLabel = new QLabel(salesFrame);
        salesCountLabel->setObjectName("salesCountLabel");
        salesCountLabel->setFont(font3);
        salesCountLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(salesCountLabel);


        statsLayout->addWidget(salesFrame);


        verticalLayout_2->addLayout(statsLayout);

        statsLayout2 = new QHBoxLayout();
        statsLayout2->setObjectName("statsLayout2");
        todaySalesFrame = new QFrame(contentWidget);
        todaySalesFrame->setObjectName("todaySalesFrame");
        todaySalesFrame->setMinimumSize(QSize(180, 120));
        todaySalesFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        todaySalesFrame->setFrameShape(QFrame::Shape::StyledPanel);
        todaySalesFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(todaySalesFrame);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(todaySalesFrame);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(label_4);

        todaySalesLabel = new QLabel(todaySalesFrame);
        todaySalesLabel->setObjectName("todaySalesLabel");
        todaySalesLabel->setFont(font3);
        todaySalesLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(todaySalesLabel);


        statsLayout2->addWidget(todaySalesFrame);

        todayRevenueFrame = new QFrame(contentWidget);
        todayRevenueFrame->setObjectName("todayRevenueFrame");
        todayRevenueFrame->setMinimumSize(QSize(180, 120));
        todayRevenueFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        todayRevenueFrame->setFrameShape(QFrame::Shape::StyledPanel);
        todayRevenueFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(todayRevenueFrame);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_5 = new QLabel(todayRevenueFrame);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(label_5);

        todayRevenueLabel = new QLabel(todayRevenueFrame);
        todayRevenueLabel->setObjectName("todayRevenueLabel");
        todayRevenueLabel->setFont(font3);
        todayRevenueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(todayRevenueLabel);


        statsLayout2->addWidget(todayRevenueFrame);

        lowStockFrame = new QFrame(contentWidget);
        lowStockFrame->setObjectName("lowStockFrame");
        lowStockFrame->setMinimumSize(QSize(180, 120));
        lowStockFrame->setStyleSheet(QString::fromUtf8("background-color: #87CEEB; color: black;"));
        lowStockFrame->setFrameShape(QFrame::Shape::StyledPanel);
        lowStockFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(lowStockFrame);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_6 = new QLabel(lowStockFrame);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(label_6);

        lowStockLabel = new QLabel(lowStockFrame);
        lowStockLabel->setObjectName("lowStockLabel");
        lowStockLabel->setFont(font3);
        lowStockLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(lowStockLabel);


        statsLayout2->addWidget(lowStockFrame);


        verticalLayout_2->addLayout(statsLayout2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        recentSalesLabel = new QLabel(contentWidget);
        recentSalesLabel->setObjectName("recentSalesLabel");
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        recentSalesLabel->setFont(font4);
        recentSalesLabel->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
"\n"
""));

        verticalLayout_2->addWidget(recentSalesLabel);

        recentSalesTable = new QTableWidget(contentWidget);
        if (recentSalesTable->columnCount() < 5)
            recentSalesTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        recentSalesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        recentSalesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        recentSalesTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        recentSalesTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        recentSalesTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        recentSalesTable->setObjectName("recentSalesTable");
        recentSalesTable->setMinimumSize(QSize(0, 200));
        recentSalesTable->setStyleSheet(QString::fromUtf8("background-color: white; color: black;"));

        verticalLayout_2->addWidget(recentSalesTable);


        horizontalLayout->addWidget(contentWidget);

        DashboardWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DashboardWindow);
        statusbar->setObjectName("statusbar");
        DashboardWindow->setStatusBar(statusbar);

        retranslateUi(DashboardWindow);

        QMetaObject::connectSlotsByName(DashboardWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DashboardWindow)
    {
        DashboardWindow->setWindowTitle(QCoreApplication::translate("DashboardWindow", "Dashboard - Smart Optical Store", nullptr));
        storeNameLabel->setText(QCoreApplication::translate("DashboardWindow", "Smart Optical Store", nullptr));
        dashboardButton->setText(QCoreApplication::translate("DashboardWindow", "Dashboard", nullptr));
        salesButton->setText(QCoreApplication::translate("DashboardWindow", "Sales", nullptr));
        logoutButton->setText(QCoreApplication::translate("DashboardWindow", "Logout", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("DashboardWindow", "Sales Dashboard - Smart Optical Store", nullptr));
        topRightLogoLabel->setText(QString());
        dateTimeLabel->setText(QCoreApplication::translate("DashboardWindow", "Today's Date", nullptr));
        label->setText(QCoreApplication::translate("DashboardWindow", "Today's Sales", nullptr));
        customersCountLabel->setText(QCoreApplication::translate("DashboardWindow", "0", nullptr));
        label_2->setText(QCoreApplication::translate("DashboardWindow", "This Week Sales", nullptr));
        productsCountLabel->setText(QCoreApplication::translate("DashboardWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("DashboardWindow", "This Month Sales", nullptr));
        salesCountLabel->setText(QCoreApplication::translate("DashboardWindow", "0", nullptr));
        label_4->setText(QCoreApplication::translate("DashboardWindow", "Today's Revenue", nullptr));
        todaySalesLabel->setText(QCoreApplication::translate("DashboardWindow", "$0.00", nullptr));
        label_5->setText(QCoreApplication::translate("DashboardWindow", "This Week Revenue", nullptr));
        todayRevenueLabel->setText(QCoreApplication::translate("DashboardWindow", "$0.00", nullptr));
        label_6->setText(QCoreApplication::translate("DashboardWindow", "This Month Revenue", nullptr));
        lowStockLabel->setText(QCoreApplication::translate("DashboardWindow", "$0.00", nullptr));
        recentSalesLabel->setText(QCoreApplication::translate("DashboardWindow", "\360\237\223\212 Recent Sales Activity", nullptr));
        QTableWidgetItem *___qtablewidgetitem = recentSalesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DashboardWindow", "Sale ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = recentSalesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DashboardWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = recentSalesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DashboardWindow", "Customer", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = recentSalesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DashboardWindow", "Amount", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = recentSalesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DashboardWindow", "Payment Method", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardWindow: public Ui_DashboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDWINDOW_H
