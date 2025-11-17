/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QStackedWidget *travaille;
    QWidget *page_3;
    QLineEdit *lineEdit_6;
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QLabel *label_9;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QDateEdit *dateEdit;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_14;
    QLabel *label_34;
    QLineEdit *lineEdit_29;
    QLabel *label_35;
    QComboBox *comboBox_2;
    QPushButton *pushButton_16;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton;
    QPushButton *pushButton_9;
    QLabel *image;
    QWidget *page_4;
    QLabel *image2;
    QTableWidget *tableWidget_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QWidget *page_8;
    QLabel *labelLogoTopRight;
    QWidget *layoutWidget;
    QVBoxLayout *contentAreaLayout;
    QLabel *mainTitle;
    QTabWidget *tabWidgetMain;
    QWidget *tabListeClients;
    QVBoxLayout *layoutListeClients;
    QHBoxLayout *layoutSearch;
    QLineEdit *lineEditSearch;
    QLabel *labelFilter;
    QComboBox *comboBoxTri;
    QTableWidget *tableWidgetClients;
    QHBoxLayout *layoutButtons;
    QPushButton *btnExport;
    QPushButton *btnDelete;
    QWidget *tabAddClient;
    QGridLayout *layoutForm;
    QLabel *labelID;
    QLineEdit *lineEditID;
    QLabel *labelNom;
    QLineEdit *lineEditNom;
    QLabel *labelPrenom;
    QLineEdit *lineEditPrenom;
    QLabel *labelDateNaissance;
    QDateEdit *dateEditNaissance;
    QLabel *labelSexe;
    QComboBox *comboBoxSexe;
    QLabel *labelAdresse;
    QLineEdit *lineEditAdresse;
    QLabel *labelTelephone;
    QLineEdit *lineEditTelephone;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QHBoxLayout *layoutButtonsForm;
    QPushButton *btnSave;
    QPushButton *btnCancel;
    QWidget *tabStats;
    QVBoxLayout *layoutStats;
    QLabel *labelStatsTitle;
    QLabel *labelStatsContent;
    QWidget *page_2;
    QStackedWidget *stackedWidget_2;
    QWidget *page_6;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_delete;
    QTableWidget *tableWidget_2;
    QGroupBox *groupBox_5;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_27;
    QLineEdit *lineEdit_28;
    QLineEdit *lineEdit_30;
    QLineEdit *lineEdit_31;
    QLineEdit *lineEdit_32;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_36;
    QPushButton *pushButton_modifier_2;
    QWidget *page_7;
    QPushButton *pushButton_22;
    QLabel *logoLabel;
    QWidget *page_5;
    QPushButton *pushButton_6;
    QLineEdit *lineEdit_14;
    QTableWidget *tableWidget_4;
    QPushButton *pushButton_10;
    QGroupBox *groupBox_4;
    QLabel *label_19;
    QLineEdit *lineEdit_15;
    QLabel *label_20;
    QLineEdit *lineEdit_16;
    QLabel *label_21;
    QLineEdit *lineEdit_17;
    QLabel *label_22;
    QDateEdit *dateEdit_2;
    QLineEdit *lineEdit_18;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *lineEdit_19;
    QLabel *label_25;
    QLineEdit *lineEdit_20;
    QLabel *label_26;
    QLineEdit *lineEdit_21;
    QLabel *label_27;
    QLineEdit *lineEdit_22;
    QLabel *label_28;
    QLineEdit *lineEdit_23;
    QLabel *label_29;
    QLineEdit *lineEdit_24;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_15;
    QPushButton *pushButton_21;
    QPushButton *pushButton_20;
    QGroupBox *groupBox_2;
    QPushButton *btnProd;
    QPushButton *on_btnvente_clicked;
    QPushButton *btnemployer;
    QPushButton *pushButton_11;
    QPushButton *btnFour;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1442, 724);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 226, 242);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(300, 30, 1121, 601));
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"	border-color: rgb(184, 226, 242);\n"
"    border: 2px solid black;\n"
"    border-radius: 8px; /* Optional: rounded corners */\n"
"}\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName("page");
        travaille = new QStackedWidget(page);
        travaille->setObjectName("travaille");
        travaille->setGeometry(QRect(-10, 20, 1091, 601));
        travaille->setStyleSheet(QString::fromUtf8("/* Static design for label_9 */\n"
"QLabel#label_9 {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    padding: 10px 20px;\n"
"    border: 1px solid #93C5FD; /* light blue border */\n"
"    border-radius: 12px;\n"
"    color: #aa0000;  /* text color */\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #BFDBFE,   /* very light blue top */\n"
"        stop:1 #93C5FD    /* soft sky blue bottom */\n"
"    );\n"
"}\n"
"\n"
"/* Hover effect (static, QLabel hover works) */\n"
"QLabel#label_9:hover {\n"
"    background-color: qlineargradient(\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 #E0F2FE,   /* almost white-blue */\n"
"        stop:1 #BFDBFE\n"
"    );\n"
"}\n"
"\n"
"/* Pressed effect (optional for QLabel, not clickable by default) */\n"
"QLabel#label_9:pressed {\n"
"    background-color: #93C5FD; /* flat light blue */\n"
"}\n"
"QStackedWidget#travaille {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px; /* Optional: rounded corners *"
                        "/\n"
"}\n"
""));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        lineEdit_6 = new QLineEdit(page_3);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(830, 510, 191, 41));
        lineEdit_6->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);"));
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QFont font;
        font.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(280, 130, 791, 341));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    border: 3px solid #1E3A8A;   /* outer border */\n"
"    gridline-color: #1E3A8A;     /* inner cell lines */\n"
"    color: black;                /* text color inside cells */\n"
"    background-color: white;     /* cell background */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    border: 1px solid #1E3A8A;\n"
"    color: black;                /* header text color */\n"
"    background-color: #E0F2FE;   /* light blue header background */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
""));
        comboBox = new QComboBox(page_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(770, 60, 151, 41));
        QFont font1;
        font1.setBold(true);
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);"));
        pushButton_5 = new QPushButton(page_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(760, 510, 51, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton_5->setIcon(icon);
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(540, 510, 271, 41));
        label_9->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;"));
        groupBox = new QGroupBox(page_3);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 261, 561));
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
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(120, 50, 121, 31));
        lineEdit_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"\n"
"background-color: rgb(170, 255, 255);"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(120, 100, 121, 31));
        lineEdit_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(130, 400, 121, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 490, 101, 31));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        pushButton_2->setIcon(icon1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 280, 81, 31));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 180, 71, 41));
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 90, 81, 41));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 330, 71, 41));
        label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 440, 61, 41));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 40, 81, 41));
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 390, 121, 41));
        label_16->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(120, 190, 121, 31));
        lineEdit_7->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(120, 340, 121, 31));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(120, 290, 121, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(80, 450, 81, 21));
        radioButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(41, 102, 148);"));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(170, 450, 81, 20));
        radioButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: rgb(0, 0, 0);"));
        pushButton_14 = new QPushButton(groupBox);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(180, 500, 51, 41));
        pushButton_14->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);\n"
""));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        pushButton_14->setIcon(icon2);
        label_34 = new QLabel(groupBox);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(30, 230, 51, 31));
        label_34->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        lineEdit_29 = new QLineEdit(groupBox);
        lineEdit_29->setObjectName("lineEdit_29");
        lineEdit_29->setGeometry(QRect(120, 240, 121, 31));
        lineEdit_29->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_35 = new QLabel(groupBox);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(20, 140, 71, 41));
        label_35->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(120, 150, 121, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(170, 255, 255);"));
        pushButton_16 = new QPushButton(groupBox);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(50, 530, 101, 31));
        pushButton_16->setFont(font2);
        pushButton_16->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        pushButton_16->setIcon(icon3);
        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(310, 20, 361, 41));
        lineEdit_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"      border: 3px solid #1E3A8A;\n"
"      /* default border */\n"
"    border-radius: 12px;            /* rounded shape */\n"
"    padding: 6px 10px;\n"
"    background-color: #ffffff;\n"
"    color: black;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* when focused */\n"
"QLineEdit:focus {\n"
"    border: 2px solid #2f2ee9;      /* highlight color */\n"
"    background-color: #f0f4ff;      /* light blue background on focus */\n"
"    font-weight: bold;              /* text bolder on focus */\n"
"}\n"
"color: rgb(0, 0, 0);"));
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(610, 20, 61, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"  border: 3px solid #1E3A8A;\n"
""));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        pushButton->setIcon(icon4);
        pushButton_9 = new QPushButton(page_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(940, 70, 61, 21));
        pushButton_9->setFont(font2);
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        image = new QLabel(page_3);
        image->setObjectName("image");
        image->setGeometry(QRect(950, 10, 41, 41));
        image->setPixmap(QPixmap(QString::fromUtf8("../../../Desktop/gsxg/images/1223.jpg")));
        travaille->addWidget(page_3);
        lineEdit_6->raise();
        tableWidget->raise();
        comboBox->raise();
        label_9->raise();
        pushButton_5->raise();
        groupBox->raise();
        lineEdit_5->raise();
        pushButton_9->raise();
        image->raise();
        pushButton->raise();
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        image2 = new QLabel(page_4);
        image2->setObjectName("image2");
        image2->setGeometry(QRect(930, 20, 51, 61));
        image2->setPixmap(QPixmap(QString::fromUtf8("../../../Desktop/gsxg/images/1223.jpg")));
        tableWidget_5 = new QTableWidget(page_4);
        if (tableWidget_5->columnCount() < 5)
            tableWidget_5->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        tableWidget_5->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_5->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        tableWidget_5->setObjectName("tableWidget_5");
        tableWidget_5->setGeometry(QRect(170, 80, 621, 321));
        tableWidget_5->setMinimumSize(QSize(621, 0));
        tableWidget_5->setMaximumSize(QSize(621, 16777215));
        tableWidget_5->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    border: 3px solid #1E3A8A;   /* outer border */\n"
"    gridline-color: #1E3A8A;     /* inner cell lines */\n"
"    color: black;                /* text color inside cells */\n"
"    background-color: white;     /* cell background */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    border: 1px solid #1E3A8A;\n"
"    color: black;                /* header text color */\n"
"    background-color: #E0F2FE;   /* light blue header background */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
""));
        travaille->addWidget(page_4);
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(230, 0, 111, 21));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        pushButton_4->setFont(font3);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(80, 0, 151, 21));
        pushButton_3->setFont(font3);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        stackedWidget->addWidget(page);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        labelLogoTopRight = new QLabel(page_8);
        labelLogoTopRight->setObjectName("labelLogoTopRight");
        labelLogoTopRight->setGeometry(QRect(1170, 30, 70, 70));
        labelLogoTopRight->setPixmap(QPixmap(QString::fromUtf8("../../Gclient1/Gclient1/smart_logo.png.jpg")));
        labelLogoTopRight->setScaledContents(true);
        layoutWidget = new QWidget(page_8);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 1101, 571));
        contentAreaLayout = new QVBoxLayout(layoutWidget);
        contentAreaLayout->setSpacing(6);
        contentAreaLayout->setContentsMargins(11, 11, 11, 11);
        contentAreaLayout->setObjectName("contentAreaLayout");
        contentAreaLayout->setContentsMargins(0, 0, 0, 0);
        mainTitle = new QLabel(layoutWidget);
        mainTitle->setObjectName("mainTitle");

        contentAreaLayout->addWidget(mainTitle);

        tabWidgetMain = new QTabWidget(layoutWidget);
        tabWidgetMain->setObjectName("tabWidgetMain");
        tabWidgetMain->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tabListeClients = new QWidget();
        tabListeClients->setObjectName("tabListeClients");
        layoutListeClients = new QVBoxLayout(tabListeClients);
        layoutListeClients->setSpacing(6);
        layoutListeClients->setContentsMargins(11, 11, 11, 11);
        layoutListeClients->setObjectName("layoutListeClients");
        layoutSearch = new QHBoxLayout();
        layoutSearch->setSpacing(6);
        layoutSearch->setObjectName("layoutSearch");
        lineEditSearch = new QLineEdit(tabListeClients);
        lineEditSearch->setObjectName("lineEditSearch");

        layoutSearch->addWidget(lineEditSearch);

        labelFilter = new QLabel(tabListeClients);
        labelFilter->setObjectName("labelFilter");

        layoutSearch->addWidget(labelFilter);

        comboBoxTri = new QComboBox(tabListeClients);
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->setObjectName("comboBoxTri");

        layoutSearch->addWidget(comboBoxTri);


        layoutListeClients->addLayout(layoutSearch);

        tableWidgetClients = new QTableWidget(tabListeClients);
        if (tableWidgetClients->columnCount() < 8)
            tableWidgetClients->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(5, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(6, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidgetClients->setHorizontalHeaderItem(7, __qtablewidgetitem21);
        tableWidgetClients->setObjectName("tableWidgetClients");
        tableWidgetClients->setColumnCount(8);

        layoutListeClients->addWidget(tableWidgetClients);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setSpacing(6);
        layoutButtons->setObjectName("layoutButtons");
        btnExport = new QPushButton(tabListeClients);
        btnExport->setObjectName("btnExport");
        btnExport->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));

        layoutButtons->addWidget(btnExport);

        btnDelete = new QPushButton(tabListeClients);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        layoutButtons->addWidget(btnDelete);


        layoutListeClients->addLayout(layoutButtons);

        tabWidgetMain->addTab(tabListeClients, QString());
        tabAddClient = new QWidget();
        tabAddClient->setObjectName("tabAddClient");
        layoutForm = new QGridLayout(tabAddClient);
        layoutForm->setSpacing(6);
        layoutForm->setContentsMargins(11, 11, 11, 11);
        layoutForm->setObjectName("layoutForm");
        labelID = new QLabel(tabAddClient);
        labelID->setObjectName("labelID");

        layoutForm->addWidget(labelID, 0, 0, 1, 1);

        lineEditID = new QLineEdit(tabAddClient);
        lineEditID->setObjectName("lineEditID");

        layoutForm->addWidget(lineEditID, 0, 1, 1, 1);

        labelNom = new QLabel(tabAddClient);
        labelNom->setObjectName("labelNom");

        layoutForm->addWidget(labelNom, 1, 0, 1, 1);

        lineEditNom = new QLineEdit(tabAddClient);
        lineEditNom->setObjectName("lineEditNom");

        layoutForm->addWidget(lineEditNom, 1, 1, 1, 1);

        labelPrenom = new QLabel(tabAddClient);
        labelPrenom->setObjectName("labelPrenom");

        layoutForm->addWidget(labelPrenom, 2, 0, 1, 1);

        lineEditPrenom = new QLineEdit(tabAddClient);
        lineEditPrenom->setObjectName("lineEditPrenom");

        layoutForm->addWidget(lineEditPrenom, 2, 1, 1, 1);

        labelDateNaissance = new QLabel(tabAddClient);
        labelDateNaissance->setObjectName("labelDateNaissance");

        layoutForm->addWidget(labelDateNaissance, 3, 0, 1, 1);

        dateEditNaissance = new QDateEdit(tabAddClient);
        dateEditNaissance->setObjectName("dateEditNaissance");
        dateEditNaissance->setCalendarPopup(true);

        layoutForm->addWidget(dateEditNaissance, 3, 1, 1, 1);

        labelSexe = new QLabel(tabAddClient);
        labelSexe->setObjectName("labelSexe");

        layoutForm->addWidget(labelSexe, 4, 0, 1, 1);

        comboBoxSexe = new QComboBox(tabAddClient);
        comboBoxSexe->addItem(QString());
        comboBoxSexe->addItem(QString());
        comboBoxSexe->setObjectName("comboBoxSexe");

        layoutForm->addWidget(comboBoxSexe, 4, 1, 1, 1);

        labelAdresse = new QLabel(tabAddClient);
        labelAdresse->setObjectName("labelAdresse");

        layoutForm->addWidget(labelAdresse, 5, 0, 1, 1);

        lineEditAdresse = new QLineEdit(tabAddClient);
        lineEditAdresse->setObjectName("lineEditAdresse");

        layoutForm->addWidget(lineEditAdresse, 5, 1, 1, 1);

        labelTelephone = new QLabel(tabAddClient);
        labelTelephone->setObjectName("labelTelephone");

        layoutForm->addWidget(labelTelephone, 6, 0, 1, 1);

        lineEditTelephone = new QLineEdit(tabAddClient);
        lineEditTelephone->setObjectName("lineEditTelephone");

        layoutForm->addWidget(lineEditTelephone, 6, 1, 1, 1);

        labelEmail = new QLabel(tabAddClient);
        labelEmail->setObjectName("labelEmail");

        layoutForm->addWidget(labelEmail, 7, 0, 1, 1);

        lineEditEmail = new QLineEdit(tabAddClient);
        lineEditEmail->setObjectName("lineEditEmail");

        layoutForm->addWidget(lineEditEmail, 7, 1, 1, 1);

        layoutButtonsForm = new QHBoxLayout();
        layoutButtonsForm->setSpacing(6);
        layoutButtonsForm->setObjectName("layoutButtonsForm");
        btnSave = new QPushButton(tabAddClient);
        btnSave->setObjectName("btnSave");

        layoutButtonsForm->addWidget(btnSave);

        btnCancel = new QPushButton(tabAddClient);
        btnCancel->setObjectName("btnCancel");

        layoutButtonsForm->addWidget(btnCancel);


        layoutForm->addLayout(layoutButtonsForm, 8, 0, 1, 2);

        tabWidgetMain->addTab(tabAddClient, QString());
        tabStats = new QWidget();
        tabStats->setObjectName("tabStats");
        layoutStats = new QVBoxLayout(tabStats);
        layoutStats->setSpacing(6);
        layoutStats->setContentsMargins(11, 11, 11, 11);
        layoutStats->setObjectName("layoutStats");
        labelStatsTitle = new QLabel(tabStats);
        labelStatsTitle->setObjectName("labelStatsTitle");

        layoutStats->addWidget(labelStatsTitle);

        labelStatsContent = new QLabel(tabStats);
        labelStatsContent->setObjectName("labelStatsContent");

        layoutStats->addWidget(labelStatsContent);

        tabWidgetMain->addTab(tabStats, QString());

        contentAreaLayout->addWidget(tabWidgetMain);

        stackedWidget->addWidget(page_8);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_2 = new QStackedWidget(page_2);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(30, 40, 1071, 541));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("border-color: rgb(184, 226, 242);"));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        pushButton_ajouter = new QPushButton(page_6);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(300, 490, 171, 29));
        pushButton_ajouter->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_modifier = new QPushButton(page_6);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(500, 490, 151, 29));
        pushButton_modifier->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_delete = new QPushButton(page_6);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(710, 490, 161, 29));
        pushButton_delete->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        tableWidget_2 = new QTableWidget(page_6);
        if (tableWidget_2->columnCount() < 8)
            tableWidget_2->setColumnCount(8);
        QFont font4;
        font4.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFont(font4);
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem29);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(270, 60, 791, 291));
        tableWidget_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);\n"
"color: rgb(0, 0, 0);"));
        groupBox_5 = new QGroupBox(page_6);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 0, 241, 551));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
"}\n"
""));
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 111, 20));
        label_3->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 90, 101, 20));
        label_10->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 101, 20));
        label_4->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 210, 101, 20));
        label_17->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 270, 161, 31));
        label_18->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        lineEdit = new QLineEdit(groupBox_5);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 50, 113, 28));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_4 = new QLineEdit(groupBox_5);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(10, 120, 113, 28));
        lineEdit_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_10 = new QLineEdit(groupBox_5);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(10, 180, 113, 28));
        lineEdit_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_27 = new QLineEdit(groupBox_5);
        lineEdit_27->setObjectName("lineEdit_27");
        lineEdit_27->setGeometry(QRect(10, 240, 113, 28));
        lineEdit_27->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_28 = new QLineEdit(groupBox_5);
        lineEdit_28->setObjectName("lineEdit_28");
        lineEdit_28->setGeometry(QRect(10, 300, 113, 28));
        lineEdit_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_30 = new QLineEdit(groupBox_5);
        lineEdit_30->setObjectName("lineEdit_30");
        lineEdit_30->setGeometry(QRect(10, 500, 113, 28));
        lineEdit_30->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_31 = new QLineEdit(groupBox_5);
        lineEdit_31->setObjectName("lineEdit_31");
        lineEdit_31->setGeometry(QRect(10, 440, 113, 28));
        lineEdit_31->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_32 = new QLineEdit(groupBox_5);
        lineEdit_32->setObjectName("lineEdit_32");
        lineEdit_32->setGeometry(QRect(10, 370, 113, 28));
        lineEdit_32->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 330, 161, 31));
        label_30->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(20, 470, 161, 31));
        label_31->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_32 = new QLabel(groupBox_5);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 400, 161, 31));
        label_32->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_33 = new QLabel(groupBox_5);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(140, 440, 21, 31));
        label_33->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_36 = new QLabel(groupBox_5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(190, 440, 21, 31));
        label_36->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        pushButton_modifier_2 = new QPushButton(page_6);
        pushButton_modifier_2->setObjectName("pushButton_modifier_2");
        pushButton_modifier_2->setGeometry(QRect(290, 380, 121, 21));
        pushButton_modifier_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        stackedWidget_2->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        stackedWidget_2->addWidget(page_7);
        pushButton_22 = new QPushButton(page_2);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(10, 0, 201, 21));
        pushButton_22->setFont(font3);
        pushButton_22->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        logoLabel = new QLabel(page_2);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(1050, 10, 60, 60));
        logoLabel->setMinimumSize(QSize(50, 50));
        logoLabel->setMaximumSize(QSize(60, 60));
        logoLabel->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logof.jpg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidget->addWidget(page_2);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        pushButton_6 = new QPushButton(page_5);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(700, 720, 131, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        lineEdit_14 = new QLineEdit(page_5);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(310, 30, 321, 41));
        lineEdit_14->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"      border: 3px solid #1E3A8A;\n"
"      /* default border */\n"
"    border-radius: 12px;            /* rounded shape */\n"
"    padding: 6px 10px;\n"
"    background-color: #ffffff;\n"
"    color: black;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* when focused */\n"
"QLineEdit:focus {\n"
"    border: 2px solid #2f2ee9;      /* highlight color */\n"
"    background-color: #f0f4ff;      /* light blue background on focus */\n"
"    font-weight: bold;              /* text bolder on focus */\n"
"}\n"
"\n"
""));
        tableWidget_4 = new QTableWidget(page_5);
        if (tableWidget_4->columnCount() < 11)
            tableWidget_4->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(7, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(8, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(9, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(10, __qtablewidgetitem40);
        if (tableWidget_4->rowCount() < 9)
            tableWidget_4->setRowCount(9);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(300, 80, 651, 311));
        tableWidget_4->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    border: 3px solid #1E3A8A;   /* outer border */\n"
"    gridline-color: #1E3A8A;     /* inner cell lines */\n"
"    color: black;                /* text color inside cells */\n"
"    background-color: white;     /* cell background */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    border: 1px solid #1E3A8A;\n"
"    color: black;                /* header text color */\n"
"    background-color: #E0F2FE;   /* light blue header background */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
""));
        pushButton_10 = new QPushButton(page_5);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(530, 720, 141, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        groupBox_4 = new QGroupBox(page_5);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(0, 0, 271, 651));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
"}\n"
""));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(20, 50, 31, 28));
        label_19->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_15 = new QLineEdit(groupBox_4);
        lineEdit_15->setObjectName("lineEdit_15");
        lineEdit_15->setGeometry(QRect(100, 50, 151, 21));
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 100, 51, 28));
        label_20->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_16 = new QLineEdit(groupBox_4);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(100, 110, 151, 21));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 170, 55, 28));
        label_21->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_17 = new QLineEdit(groupBox_4);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(100, 170, 151, 21));
        lineEdit_17->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 230, 72, 28));
        label_22->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        dateEdit_2 = new QDateEdit(groupBox_4);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(100, 300, 151, 21));
        dateEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        lineEdit_18 = new QLineEdit(groupBox_4);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(100, 240, 151, 21));
        lineEdit_18->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 290, 41, 28));
        label_23->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 350, 55, 28));
        label_24->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_19 = new QLineEdit(groupBox_4);
        lineEdit_19->setObjectName("lineEdit_19");
        lineEdit_19->setGeometry(QRect(100, 360, 151, 21));
        lineEdit_19->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 410, 48, 28));
        label_25->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_20 = new QLineEdit(groupBox_4);
        lineEdit_20->setObjectName("lineEdit_20");
        lineEdit_20->setGeometry(QRect(100, 410, 151, 21));
        lineEdit_20->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"\n"
""));
        label_26 = new QLabel(groupBox_4);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 470, 122, 28));
        label_26->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_21 = new QLineEdit(groupBox_4);
        lineEdit_21->setObjectName("lineEdit_21");
        lineEdit_21->setGeometry(QRect(110, 480, 151, 21));
        lineEdit_21->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_27 = new QLabel(groupBox_4);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 530, 38, 28));
        label_27->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_22 = new QLineEdit(groupBox_4);
        lineEdit_22->setObjectName("lineEdit_22");
        lineEdit_22->setGeometry(QRect(110, 530, 151, 20));
        lineEdit_22->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_28 = new QLabel(groupBox_4);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 580, 48, 28));
        label_28->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_23 = new QLineEdit(groupBox_4);
        lineEdit_23->setObjectName("lineEdit_23");
        lineEdit_23->setGeometry(QRect(110, 580, 151, 21));
        lineEdit_23->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_29 = new QLabel(groupBox_4);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 640, 88, 28));
        label_29->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_24 = new QLineEdit(groupBox_4);
        lineEdit_24->setObjectName("lineEdit_24");
        lineEdit_24->setGeometry(QRect(110, 640, 151, 21));
        lineEdit_24->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        pushButton_12 = new QPushButton(groupBox_4);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(170, 690, 51, 31));
        pushButton_12->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);"));
        pushButton_12->setIcon(icon2);
        pushButton_13 = new QPushButton(groupBox_4);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(40, 690, 61, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        pushButton_15 = new QPushButton(page_5);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(1030, 720, 141, 31));
        pushButton_15->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton_21 = new QPushButton(page_5);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(860, 720, 141, 31));
        pushButton_21->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        pushButton_20 = new QPushButton(page_5);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(570, 30, 61, 41));
        pushButton_20->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"  border: 3px solid #1E3A8A;\n"
""));
        pushButton_20->setIcon(icon4);
        stackedWidget->addWidget(page_5);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 20, 261, 611));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        btnProd = new QPushButton(groupBox_2);
        btnProd->setObjectName("btnProd");
        btnProd->setGeometry(QRect(0, 90, 261, 51));
        btnProd->setStyleSheet(QString::fromUtf8("#btnProd {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnProd:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnProd:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
"\n"
""));
        on_btnvente_clicked = new QPushButton(groupBox_2);
        on_btnvente_clicked->setObjectName("on_btnvente_clicked");
        on_btnvente_clicked->setGeometry(QRect(0, 180, 261, 51));
        on_btnvente_clicked->setStyleSheet(QString::fromUtf8("#on_btnvente_clicked {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#on_btnvente_clicked:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#on_btnvente_clicked:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        btnemployer = new QPushButton(groupBox_2);
        btnemployer->setObjectName("btnemployer");
        btnemployer->setGeometry(QRect(0, 270, 261, 51));
        btnemployer->setStyleSheet(QString::fromUtf8("#btnemployer {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnemployer:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnemployer:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(0, 360, 261, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("#pushButton_11 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_11:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_11:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        btnFour = new QPushButton(groupBox_2);
        btnFour->setObjectName("btnFour");
        btnFour->setGeometry(QRect(0, 450, 261, 51));
        btnFour->setStyleSheet(QString::fromUtf8("#btnFour {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnFour:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnFour:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1442, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        travaille->setCurrentIndex(0);
        tabWidgetMain->setCurrentIndex(0);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        lineEdit_6->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "reference", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Genre", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "cat\303\251gorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "designation", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Date d'expiration", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "categories", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "prix", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "genre", nullptr));

#if QT_CONFIG(whatsthis)
        comboBox->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_5->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "- Suppression de produit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "+ Ajouter / modifier un produit", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_3->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", " Marque :", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Rr\303\251f\303\251rence", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Genre :", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "designation", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Date d'expiration:", nullptr));
        lineEdit_7->setText(QString());
        lineEdit_8->setText(QString());
        lineEdit_9->setText(QString());
        radioButton->setText(QCoreApplication::translate("MainWindow", "Homme", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Femme", nullptr));
        pushButton_14->setText(QString());
        label_34->setText(QCoreApplication::translate("MainWindow", "prix :", nullptr));
        lineEdit_29->setText(QString());
        label_35->setText(QCoreApplication::translate("MainWindow", " cat\303\251gorie :", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Lunettes", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Lentilles", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Accessoires", nullptr));

#if QT_CONFIG(whatsthis)
        comboBox_2->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        lineEdit_5->setText(QString());
        pushButton->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        image->setText(QString());
        image2->setText(QString());
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_5->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "reference", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_5->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "designation", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_5->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_5->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_5->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "cat\303\251gorie", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion de Stock", nullptr));
        mainTitle->setText(QCoreApplication::translate("MainWindow", "Gestion de Clients", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche par Nom, ID ou T\303\251l\303\251phone...", nullptr));
        labelFilter->setText(QCoreApplication::translate("MainWindow", "Filtrer :", nullptr));
        comboBoxTri->setItemText(0, QCoreApplication::translate("MainWindow", "Nom A-Z", nullptr));
        comboBoxTri->setItemText(1, QCoreApplication::translate("MainWindow", "Nom Z-A", nullptr));
        comboBoxTri->setItemText(2, QCoreApplication::translate("MainWindow", "ID \342\206\221", nullptr));
        comboBoxTri->setItemText(3, QCoreApplication::translate("MainWindow", "ID \342\206\223", nullptr));

        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetClients->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetClients->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetClients->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetClients->horizontalHeaderItem(3);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Date Naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetClients->horizontalHeaderItem(4);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetClients->horizontalHeaderItem(5);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidgetClients->horizontalHeaderItem(6);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidgetClients->horizontalHeaderItem(7);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        btnExport->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 Exporter PDF", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Client", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabListeClients), QCoreApplication::translate("MainWindow", "Liste Clients", nullptr));
        labelID->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        labelNom->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        labelPrenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom :", nullptr));
        labelDateNaissance->setText(QCoreApplication::translate("MainWindow", "Date Naissance :", nullptr));
        labelSexe->setText(QCoreApplication::translate("MainWindow", "Sexe :", nullptr));
        comboBoxSexe->setItemText(0, QCoreApplication::translate("MainWindow", "Homme", nullptr));
        comboBoxSexe->setItemText(1, QCoreApplication::translate("MainWindow", "Femme", nullptr));

        labelAdresse->setText(QCoreApplication::translate("MainWindow", "Adresse :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone :", nullptr));
        labelEmail->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 Enregistrer", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Annuler", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabAddClient), QCoreApplication::translate("MainWindow", "Ajouter / Modifier", nullptr));
        labelStatsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques Clients", nullptr));
        labelStatsContent->setText(QCoreApplication::translate("MainWindow", "Graphiques et donn\303\251es statistiques ici...", nullptr));
        tabWidgetMain->setTabText(tabWidgetMain->indexOf(tabStats), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "id_fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "nom_entreprise", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "nom_contact", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "type_produit_fournis", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "condition_paeiment", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "historique", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "ajouter /modifier", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "id_fournisseur", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "nom_entreprise", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "nom_contact", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "telephone", nullptr));
        lineEdit->setText(QString());
        lineEdit_4->setText(QString());
        lineEdit_10->setText(QString());
        lineEdit_27->setText(QString());
        lineEdit_28->setText(QString());
        lineEdit_30->setText(QString());
        lineEdit_31->setText(QString());
        lineEdit_32->setText(QString());
        label_30->setText(QCoreApplication::translate("MainWindow", "type_produit_fournis", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "historique", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "condition_paeiment", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "c:1", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "L:0", nullptr));
        pushButton_modifier_2->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "Gestion de fournisseur", nullptr));
        logoLabel->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "trie", nullptr));
        lineEdit_14->setText(QCoreApplication::translate("MainWindow", "rechercher ar nom ou prenom ou email", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_4->horizontalHeaderItem(7);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_4->horizontalHeaderItem(8);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_4->horizontalHeaderItem(9);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_4->horizontalHeaderItem(10);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("MainWindow", "Disponibilite", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Ajouter un employe", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Nom  :", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Prenom:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Adresse:", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Nombre d\342\200\231enfants:", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Poste:", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Salaire:", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "Disponibilite:", nullptr));
        pushButton_12->setText(QString());
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Vlider", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_20->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Tableau de bord", nullptr));
        btnProd->setText(QCoreApplication::translate("MainWindow", "Produit", nullptr));
        on_btnvente_clicked->setText(QCoreApplication::translate("MainWindow", "Ventes", nullptr));
        btnemployer->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        btnFour->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
