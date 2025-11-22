/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_TEST_H
#define UI_MAINWINDOW_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QStackedWidget *travaille_2;
    QWidget *page_10;
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
    QPushButton *pushButton_31;
    QLabel *label_45;
    QLineEdit *lineEdit_36;
    QLabel *label_46;
    QComboBox *comboBox_4;
    QPushButton *pushButton_32;
    QLineEdit *lineEdit_5;
    QPushButton *pushButtonR;
    QPushButton *pushButton_9;
    QLabel *image_2;
    QWidget *page_11;
    QLabel *image2_2;
    QTableWidget *tableWidget_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QWidget *page_2;
    QStackedWidget *stackedWidget_2;
    QWidget *page_12;
    QPushButton *pushButton_ajouter_2;
    QPushButton *pushButton_modifier_3;
    QPushButton *pushButton_delete_2;
    QTableWidget *tableWidget_7;
    QGroupBox *groupBox_6;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_47;
    QLabel *label_48;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_37;
    QLineEdit *lineEdit_38;
    QLineEdit *lineEdit_39;
    QLineEdit *lineEdit_40;
    QLineEdit *lineEdit_41;
    QLineEdit *lineEdit_42;
    QLineEdit *lineEdit_43;
    QLabel *label_49;
    QLabel *label_50;
    QLabel *label_51;
    QLabel *label_52;
    QLabel *label_53;
    QPushButton *pushButton_modifier_4;
    QWidget *page_13;
    QPushButton *pushButton_33;
    QLabel *logoLabel;
    QWidget *page_14;
    QPushButton *pushButton_6;
    QLineEdit *lineEdit_44;
    QTableWidget *tableWidget_8;
    QPushButton *pushButton_10;
    QGroupBox *groupBox_7;
    QLabel *label_54;
    QLineEdit *lineEdit_45;
    QLabel *label_55;
    QLineEdit *lineEdit_46;
    QLabel *label_56;
    QLineEdit *lineEdit_47;
    QLabel *label_57;
    QDateEdit *dateEdit_4;
    QLineEdit *lineEdit_48;
    QLabel *label_58;
    QLabel *label_59;
    QLineEdit *lineEdit_49;
    QLabel *label_60;
    QLineEdit *lineEdit_50;
    QLabel *label_61;
    QLineEdit *lineEdit_51;
    QLabel *label_62;
    QLineEdit *lineEdit_52;
    QLabel *label_63;
    QLineEdit *lineEdit_53;
    QLabel *label_64;
    QLineEdit *lineEdit_54;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_34;
    QPushButton *pushButton_35;
    QPushButton *pushButton_36;
    QGroupBox *groupBox_2;
    QPushButton *btnProd_2;
    QPushButton *on_btnvente_clicked_2;
    QPushButton *btnemployer_2;
    QPushButton *pushButton_11;
    QPushButton *btnFour_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1339, 643);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #B8E2F2\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(260, 30, 1121, 591));
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"	border-color: rgb(184, 226, 242);\n"
"    border: 2px solid black;\n"
"    border-radius: 8px; /* Optional: rounded corners */\n"
"}\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName("page");
        travaille_2 = new QStackedWidget(page);
        travaille_2->setObjectName("travaille_2");
        travaille_2->setGeometry(QRect(0, 20, 1071, 581));
        travaille_2->setStyleSheet(QString::fromUtf8("/* Static design for label_9 */\n"
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
        page_10 = new QWidget();
        page_10->setObjectName("page_10");
        lineEdit_6 = new QLineEdit(page_10);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(840, 480, 211, 41));
        lineEdit_6->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);"));
        tableWidget = new QTableWidget(page_10);
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
        comboBox = new QComboBox(page_10);
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
        pushButton_5 = new QPushButton(page_10);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(770, 480, 51, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton_5->setIcon(icon);
        label_9 = new QLabel(page_10);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(550, 480, 271, 41));
        label_9->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;"));
        groupBox = new QGroupBox(page_10);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 261, 561));
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
        pushButton_2->setGeometry(QRect(50, 480, 101, 31));
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
        pushButton_31 = new QPushButton(groupBox);
        pushButton_31->setObjectName("pushButton_31");
        pushButton_31->setGeometry(QRect(200, 490, 51, 41));
        pushButton_31->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);\n"
""));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        pushButton_31->setIcon(icon2);
        label_45 = new QLabel(groupBox);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(30, 230, 51, 31));
        label_45->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        lineEdit_36 = new QLineEdit(groupBox);
        lineEdit_36->setObjectName("lineEdit_36");
        lineEdit_36->setGeometry(QRect(120, 240, 121, 31));
        lineEdit_36->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_46 = new QLabel(groupBox);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(20, 140, 71, 41));
        label_46->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        comboBox_4 = new QComboBox(groupBox);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(120, 150, 121, 31));
        comboBox_4->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(170, 255, 255);"));
        pushButton_32 = new QPushButton(groupBox);
        pushButton_32->setObjectName("pushButton_32");
        pushButton_32->setGeometry(QRect(50, 510, 101, 31));
        pushButton_32->setFont(font2);
        pushButton_32->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        pushButton_32->setIcon(icon3);
        lineEdit_5 = new QLineEdit(page_10);
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
        pushButtonR = new QPushButton(page_10);
        pushButtonR->setObjectName("pushButtonR");
        pushButtonR->setGeometry(QRect(610, 20, 61, 41));
        pushButtonR->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"  border: 3px solid #1E3A8A;\n"
""));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        pushButtonR->setIcon(icon4);
        pushButton_9 = new QPushButton(page_10);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(940, 70, 61, 21));
        pushButton_9->setFont(font2);
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        image_2 = new QLabel(page_10);
        image_2->setObjectName("image_2");
        image_2->setGeometry(QRect(950, 10, 41, 41));
        image_2->setPixmap(QPixmap(QString::fromUtf8("../../../Desktop/gsxg/images/1223.jpg")));
        travaille_2->addWidget(page_10);
        image_2->raise();
        lineEdit_6->raise();
        tableWidget->raise();
        comboBox->raise();
        label_9->raise();
        pushButton_5->raise();
        groupBox->raise();
        lineEdit_5->raise();
        pushButton_9->raise();
        pushButtonR->raise();
        page_11 = new QWidget();
        page_11->setObjectName("page_11");
        image2_2 = new QLabel(page_11);
        image2_2->setObjectName("image2_2");
        image2_2->setGeometry(QRect(930, 20, 51, 61));
        image2_2->setPixmap(QPixmap(QString::fromUtf8("../../../Desktop/gsxg/images/1223.jpg")));
        tableWidget_6 = new QTableWidget(page_11);
        if (tableWidget_6->columnCount() < 5)
            tableWidget_6->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        tableWidget_6->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_6->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        tableWidget_6->setObjectName("tableWidget_6");
        tableWidget_6->setGeometry(QRect(170, 80, 621, 321));
        tableWidget_6->setMinimumSize(QSize(621, 0));
        tableWidget_6->setMaximumSize(QSize(621, 16777215));
        tableWidget_6->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
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
        travaille_2->addWidget(page_11);
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(240, 0, 111, 21));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        pushButton_4->setFont(font3);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(90, 0, 151, 21));
        pushButton_3->setFont(font3);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_2 = new QStackedWidget(page_2);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(30, 40, 1071, 541));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("border-color: rgb(184, 226, 242);"));
        page_12 = new QWidget();
        page_12->setObjectName("page_12");
        pushButton_ajouter_2 = new QPushButton(page_12);
        pushButton_ajouter_2->setObjectName("pushButton_ajouter_2");
        pushButton_ajouter_2->setGeometry(QRect(300, 490, 171, 29));
        pushButton_ajouter_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_modifier_3 = new QPushButton(page_12);
        pushButton_modifier_3->setObjectName("pushButton_modifier_3");
        pushButton_modifier_3->setGeometry(QRect(500, 490, 151, 29));
        pushButton_modifier_3->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        pushButton_delete_2 = new QPushButton(page_12);
        pushButton_delete_2->setObjectName("pushButton_delete_2");
        pushButton_delete_2->setGeometry(QRect(710, 490, 161, 29));
        pushButton_delete_2->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        tableWidget_7 = new QTableWidget(page_12);
        if (tableWidget_7->columnCount() < 8)
            tableWidget_7->setColumnCount(8);
        QFont font4;
        font4.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(5, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(6, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font4);
        tableWidget_7->setHorizontalHeaderItem(7, __qtablewidgetitem21);
        tableWidget_7->setObjectName("tableWidget_7");
        tableWidget_7->setGeometry(QRect(270, 60, 791, 291));
        tableWidget_7->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        groupBox_6 = new QGroupBox(page_12);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(10, 0, 241, 551));
        groupBox_6->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 111, 20));
        label_3->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_10 = new QLabel(groupBox_6);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 90, 101, 20));
        label_10->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 101, 20));
        label_4->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_47 = new QLabel(groupBox_6);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(10, 210, 101, 20));
        label_47->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_48 = new QLabel(groupBox_6);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(10, 270, 161, 31));
        label_48->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        lineEdit_4 = new QLineEdit(groupBox_6);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(10, 50, 113, 28));
        lineEdit_37 = new QLineEdit(groupBox_6);
        lineEdit_37->setObjectName("lineEdit_37");
        lineEdit_37->setGeometry(QRect(10, 120, 113, 28));
        lineEdit_38 = new QLineEdit(groupBox_6);
        lineEdit_38->setObjectName("lineEdit_38");
        lineEdit_38->setGeometry(QRect(10, 180, 113, 28));
        lineEdit_39 = new QLineEdit(groupBox_6);
        lineEdit_39->setObjectName("lineEdit_39");
        lineEdit_39->setGeometry(QRect(10, 240, 113, 28));
        lineEdit_40 = new QLineEdit(groupBox_6);
        lineEdit_40->setObjectName("lineEdit_40");
        lineEdit_40->setGeometry(QRect(10, 300, 113, 28));
        lineEdit_41 = new QLineEdit(groupBox_6);
        lineEdit_41->setObjectName("lineEdit_41");
        lineEdit_41->setGeometry(QRect(10, 500, 113, 28));
        lineEdit_42 = new QLineEdit(groupBox_6);
        lineEdit_42->setObjectName("lineEdit_42");
        lineEdit_42->setGeometry(QRect(10, 440, 113, 28));
        lineEdit_43 = new QLineEdit(groupBox_6);
        lineEdit_43->setObjectName("lineEdit_43");
        lineEdit_43->setGeometry(QRect(10, 370, 113, 28));
        label_49 = new QLabel(groupBox_6);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(10, 330, 161, 31));
        label_49->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_50 = new QLabel(groupBox_6);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(20, 470, 161, 31));
        label_50->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_51 = new QLabel(groupBox_6);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(10, 400, 161, 31));
        label_51->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_52 = new QLabel(groupBox_6);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(140, 440, 21, 31));
        label_52->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        label_53 = new QLabel(groupBox_6);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(190, 440, 21, 31));
        label_53->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148); \n"
""));
        pushButton_modifier_4 = new QPushButton(page_12);
        pushButton_modifier_4->setObjectName("pushButton_modifier_4");
        pushButton_modifier_4->setGeometry(QRect(290, 380, 121, 21));
        pushButton_modifier_4->setStyleSheet(QString::fromUtf8(" background-color: rgb(41, 102, 148);"));
        stackedWidget_2->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName("page_13");
        stackedWidget_2->addWidget(page_13);
        pushButton_33 = new QPushButton(page_2);
        pushButton_33->setObjectName("pushButton_33");
        pushButton_33->setGeometry(QRect(10, 0, 201, 21));
        pushButton_33->setFont(font3);
        pushButton_33->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
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
        page_14 = new QWidget();
        page_14->setObjectName("page_14");
        pushButton_6 = new QPushButton(page_14);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(700, 720, 131, 31));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        lineEdit_44 = new QLineEdit(page_14);
        lineEdit_44->setObjectName("lineEdit_44");
        lineEdit_44->setGeometry(QRect(310, 30, 321, 41));
        lineEdit_44->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        tableWidget_8 = new QTableWidget(page_14);
        if (tableWidget_8->columnCount() < 11)
            tableWidget_8->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(7, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(8, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(9, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_8->setHorizontalHeaderItem(10, __qtablewidgetitem32);
        if (tableWidget_8->rowCount() < 9)
            tableWidget_8->setRowCount(9);
        tableWidget_8->setObjectName("tableWidget_8");
        tableWidget_8->setGeometry(QRect(300, 80, 651, 311));
        tableWidget_8->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
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
        pushButton_10 = new QPushButton(page_14);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(530, 720, 141, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        groupBox_7 = new QGroupBox(page_14);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(0, 0, 271, 651));
        groupBox_7->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        label_54 = new QLabel(groupBox_7);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(20, 50, 31, 28));
        label_54->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_45 = new QLineEdit(groupBox_7);
        lineEdit_45->setObjectName("lineEdit_45");
        lineEdit_45->setGeometry(QRect(100, 50, 151, 21));
        label_55 = new QLabel(groupBox_7);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(10, 100, 51, 28));
        label_55->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_46 = new QLineEdit(groupBox_7);
        lineEdit_46->setObjectName("lineEdit_46");
        lineEdit_46->setGeometry(QRect(100, 110, 151, 21));
        label_56 = new QLabel(groupBox_7);
        label_56->setObjectName("label_56");
        label_56->setGeometry(QRect(10, 170, 55, 28));
        label_56->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_47 = new QLineEdit(groupBox_7);
        lineEdit_47->setObjectName("lineEdit_47");
        lineEdit_47->setGeometry(QRect(100, 170, 151, 21));
        lineEdit_47->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_57 = new QLabel(groupBox_7);
        label_57->setObjectName("label_57");
        label_57->setGeometry(QRect(10, 230, 72, 28));
        label_57->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        dateEdit_4 = new QDateEdit(groupBox_7);
        dateEdit_4->setObjectName("dateEdit_4");
        dateEdit_4->setGeometry(QRect(100, 300, 151, 21));
        dateEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        lineEdit_48 = new QLineEdit(groupBox_7);
        lineEdit_48->setObjectName("lineEdit_48");
        lineEdit_48->setGeometry(QRect(100, 240, 151, 21));
        lineEdit_48->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_58 = new QLabel(groupBox_7);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(10, 290, 41, 28));
        label_58->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_59 = new QLabel(groupBox_7);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(10, 350, 55, 28));
        label_59->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_49 = new QLineEdit(groupBox_7);
        lineEdit_49->setObjectName("lineEdit_49");
        lineEdit_49->setGeometry(QRect(100, 360, 151, 21));
        lineEdit_49->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_60 = new QLabel(groupBox_7);
        label_60->setObjectName("label_60");
        label_60->setGeometry(QRect(10, 410, 48, 28));
        label_60->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_50 = new QLineEdit(groupBox_7);
        lineEdit_50->setObjectName("lineEdit_50");
        lineEdit_50->setGeometry(QRect(100, 410, 151, 21));
        lineEdit_50->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"\n"
""));
        label_61 = new QLabel(groupBox_7);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(10, 470, 122, 28));
        label_61->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_51 = new QLineEdit(groupBox_7);
        lineEdit_51->setObjectName("lineEdit_51");
        lineEdit_51->setGeometry(QRect(110, 480, 151, 21));
        lineEdit_51->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_62 = new QLabel(groupBox_7);
        label_62->setObjectName("label_62");
        label_62->setGeometry(QRect(10, 530, 38, 28));
        label_62->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_52 = new QLineEdit(groupBox_7);
        lineEdit_52->setObjectName("lineEdit_52");
        lineEdit_52->setGeometry(QRect(110, 530, 151, 20));
        lineEdit_52->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_63 = new QLabel(groupBox_7);
        label_63->setObjectName("label_63");
        label_63->setGeometry(QRect(10, 580, 48, 28));
        label_63->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_53 = new QLineEdit(groupBox_7);
        lineEdit_53->setObjectName("lineEdit_53");
        lineEdit_53->setGeometry(QRect(110, 580, 151, 21));
        lineEdit_53->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        label_64 = new QLabel(groupBox_7);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(10, 640, 88, 28));
        label_64->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_54 = new QLineEdit(groupBox_7);
        lineEdit_54->setObjectName("lineEdit_54");
        lineEdit_54->setGeometry(QRect(110, 640, 151, 21));
        lineEdit_54->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        pushButton_12 = new QPushButton(groupBox_7);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(170, 690, 51, 31));
        pushButton_12->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);"));
        pushButton_12->setIcon(icon2);
        pushButton_13 = new QPushButton(groupBox_7);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(40, 690, 61, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        pushButton_34 = new QPushButton(page_14);
        pushButton_34->setObjectName("pushButton_34");
        pushButton_34->setGeometry(QRect(1030, 720, 141, 31));
        pushButton_34->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton_35 = new QPushButton(page_14);
        pushButton_35->setObjectName("pushButton_35");
        pushButton_35->setGeometry(QRect(860, 720, 141, 31));
        pushButton_35->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);"));
        pushButton_36 = new QPushButton(page_14);
        pushButton_36->setObjectName("pushButton_36");
        pushButton_36->setGeometry(QRect(570, 30, 61, 41));
        pushButton_36->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"  border: 3px solid #1E3A8A;\n"
""));
        pushButton_36->setIcon(icon4);
        stackedWidget->addWidget(page_14);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(-10, 10, 271, 611));
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
        btnProd_2 = new QPushButton(groupBox_2);
        btnProd_2->setObjectName("btnProd_2");
        btnProd_2->setGeometry(QRect(0, 90, 271, 51));
        btnProd_2->setStyleSheet(QString::fromUtf8("#btnProd_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnProd_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnProd_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
"\n"
""));
        on_btnvente_clicked_2 = new QPushButton(groupBox_2);
        on_btnvente_clicked_2->setObjectName("on_btnvente_clicked_2");
        on_btnvente_clicked_2->setGeometry(QRect(0, 180, 271, 51));
        on_btnvente_clicked_2->setStyleSheet(QString::fromUtf8("#on_btnvente_clicked_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#on_btnvente_clicked_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#on_btnvente_clicked_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        btnemployer_2 = new QPushButton(groupBox_2);
        btnemployer_2->setObjectName("btnemployer_2");
        btnemployer_2->setGeometry(QRect(0, 270, 271, 51));
        btnemployer_2->setStyleSheet(QString::fromUtf8("#btnemployer_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnemployer_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnemployer_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(0, 360, 271, 51));
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
        btnFour_2 = new QPushButton(groupBox_2);
        btnFour_2->setObjectName("btnFour_2");
        btnFour_2->setGeometry(QRect(0, 450, 271, 51));
        btnFour_2->setStyleSheet(QString::fromUtf8("#btnFour_2 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#btnFour_2:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#btnFour_2:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1339, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        travaille_2->setCurrentIndex(0);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
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
        pushButton_31->setText(QString());
        label_45->setText(QCoreApplication::translate("MainWindow", "prix :", nullptr));
        lineEdit_36->setText(QString());
        label_46->setText(QCoreApplication::translate("MainWindow", " cat\303\251gorie :", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "   Lunettes", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "   Lentilles", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "   Accessoires", nullptr));

#if QT_CONFIG(whatsthis)
        comboBox_4->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_32->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        lineEdit_5->setText(QString());
        pushButtonR->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        image_2->setText(QString());
        image2_2->setText(QString());
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_6->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "reference", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_6->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "designation", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_6->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_6->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_6->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "cat\303\251gorie", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion de Stock", nullptr));
        pushButton_ajouter_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modifier_3->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_delete_2->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_7->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "id_fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_7->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "nom_entreprise", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_7->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "nom_contact", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_7->horizontalHeaderItem(3);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_7->horizontalHeaderItem(4);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_7->horizontalHeaderItem(5);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "type_produit_fournis", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_7->horizontalHeaderItem(6);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "condition_paeiment", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_7->horizontalHeaderItem(7);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "historique", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "ajouter /modifier", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "id_fournisseur", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "nom_entreprise", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "nom_contact", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "telephone", nullptr));
        lineEdit_4->setText(QString());
        lineEdit_37->setText(QString());
        lineEdit_38->setText(QString());
        lineEdit_39->setText(QString());
        lineEdit_40->setText(QString());
        lineEdit_41->setText(QString());
        lineEdit_42->setText(QString());
        lineEdit_43->setText(QString());
        label_49->setText(QCoreApplication::translate("MainWindow", "type_produit_fournis", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "historique", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "condition_paeiment", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "c:1", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "L:0", nullptr));
        pushButton_modifier_4->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        pushButton_33->setText(QCoreApplication::translate("MainWindow", "Gestion de fournisseur", nullptr));
        logoLabel->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "trie", nullptr));
        lineEdit_44->setText(QCoreApplication::translate("MainWindow", "rechercher ar nom ou prenom ou email", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_8->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_8->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_8->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_8->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_8->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_8->horizontalHeaderItem(5);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_8->horizontalHeaderItem(6);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_8->horizontalHeaderItem(7);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_8->horizontalHeaderItem(8);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_8->horizontalHeaderItem(9);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_8->horizontalHeaderItem(10);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Disponibilite", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Ajouter un employe", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_55->setText(QCoreApplication::translate("MainWindow", "Nom  :", nullptr));
        label_56->setText(QCoreApplication::translate("MainWindow", "Prenom:", nullptr));
        label_57->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        label_58->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_59->setText(QCoreApplication::translate("MainWindow", "Adresse:", nullptr));
        label_60->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_61->setText(QCoreApplication::translate("MainWindow", "Nombre d\342\200\231enfants:", nullptr));
        label_62->setText(QCoreApplication::translate("MainWindow", "Poste:", nullptr));
        label_63->setText(QCoreApplication::translate("MainWindow", "Salaire:", nullptr));
        label_64->setText(QCoreApplication::translate("MainWindow", "Disponibilite:", nullptr));
        pushButton_12->setText(QString());
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Vlider", nullptr));
        pushButton_34->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        pushButton_35->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_36->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Tableau de bord", nullptr));
        btnProd_2->setText(QCoreApplication::translate("MainWindow", "Produit", nullptr));
        on_btnvente_clicked_2->setText(QCoreApplication::translate("MainWindow", "Ventes", nullptr));
        btnemployer_2->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        btnFour_2->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_TEST_H
