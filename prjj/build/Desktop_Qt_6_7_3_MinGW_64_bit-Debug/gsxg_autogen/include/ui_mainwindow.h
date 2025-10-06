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
#include <QtWidgets/QDoubleSpinBox>
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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QWidget *widget;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLineEdit *lineEdit_6;
    QTableWidget *tableWidget;
    QPushButton *pushButton_7;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QLabel *label_9;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QDateEdit *dateEdit;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_10;
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
    QLineEdit *lineEdit_5;
    QPushButton *pushButton;
    QPushButton *pushButton_9;
    QLabel *image;
    QWidget *page_2;
    QWidget *widget_3;
    QLabel *label;
    QPushButton *pushButton_12;
    QWidget *widget_4;
    QLabel *image2;
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
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 0, 1301, 611));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(layoutWidget);
        widget_2->setObjectName("widget_2");
        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 0, 1281, 611));
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(370, 0, 141, 31));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        pushButton_4->setFont(font);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(210, 0, 161, 31));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, 20, 261, 571));
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
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(0, 110, 261, 51));
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
"}\n"
"\n"
""));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(0, 200, 261, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("#pushButton_8 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_8:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_8:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        pushButton_10 = new QPushButton(groupBox_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(0, 280, 261, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("#pushButton_10 {\n"
"    font-family: Arial, Helvetica, sans-serif;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background-color: #171717;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"#pushButton_10:hover {\n"
"    background-color: #0c66ed; /* hover effect */\n"
"}\n"
"\n"
"#pushButton_10:pressed {\n"
"    background-color: #094bb0; /* pressed effect */\n"
"}\n"
""));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(0, 370, 261, 51));
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
        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(280, 40, 1001, 551));
        stackedWidget->setStyleSheet(QString::fromUtf8("/* Static design for label_9 */\n"
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
"QStackedWidget {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px; /* Optional: rounded corners */\n"
"}\n"
""));
        page = new QWidget();
        page->setObjectName("page");
        lineEdit_6 = new QLineEdit(page);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(770, 490, 191, 41));
        lineEdit_6->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
""));
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QFont font1;
        font1.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
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
        tableWidget->setGeometry(QRect(280, 130, 681, 301));
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
        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(300, 450, 181, 31));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        pushButton_7->setFont(font2);
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(480, 70, 101, 31));
        QFont font3;
        font3.setPointSize(8);
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(740, 70, 51, 31));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        doubleSpinBox = new QDoubleSpinBox(page);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(790, 70, 131, 31));
        doubleSpinBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border: 3px solid #1E3A8A;"));
        comboBox = new QComboBox(page);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(600, 70, 131, 31));
        comboBox->setStyleSheet(QString::fromUtf8("  border: 3px solid #1E3A8A;\n"
"color: rgb(0, 0, 0);"));
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(710, 490, 51, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;\n"
"background-color: rgb(170, 0, 0);"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton_5->setIcon(icon);
        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(490, 490, 271, 41));
        label_9->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A;"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 261, 541));
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
        lineEdit_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"background-color: rgb(170, 255, 255);"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(120, 100, 121, 31));
        lineEdit_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);"));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(120, 160, 121, 31));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
""));
        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(130, 400, 121, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(90, 510, 71, 21));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 280, 81, 31));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 150, 81, 41));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 210, 71, 41));
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
        label_14->setGeometry(QRect(10, 450, 71, 41));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(20, 40, 41, 41));
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 390, 121, 41));
        label_16->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
""));
        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(120, 220, 121, 31));
        lineEdit_7->setStyleSheet(QString::fromUtf8("background-color: rgb(11, 210, 255);\n"
"background-color: rgb(170, 255, 255);"));
        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(120, 330, 121, 31));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(120, 280, 121, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(80, 460, 61, 21));
        radioButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(41, 102, 148);"));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(160, 460, 81, 20));
        radioButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_5 = new QLineEdit(page);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(280, 20, 361, 41));
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
""));
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(580, 20, 61, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"  border: 3px solid #1E3A8A;\n"
""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        pushButton->setIcon(icon1);
        pushButton_9 = new QPushButton(page);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(930, 100, 51, 21));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 127);\n"
""));
        image = new QLabel(page);
        image->setObjectName("image");
        image->setGeometry(QRect(940, 10, 41, 41));
        image->setPixmap(QPixmap(QString::fromUtf8("images/1223.jpg")));
        stackedWidget->addWidget(page);
        lineEdit_6->raise();
        tableWidget->raise();
        pushButton_7->raise();
        label_3->raise();
        label_4->raise();
        doubleSpinBox->raise();
        comboBox->raise();
        label_9->raise();
        pushButton_5->raise();
        groupBox->raise();
        lineEdit_5->raise();
        pushButton_9->raise();
        image->raise();
        pushButton->raise();
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        widget_3 = new QWidget(page_2);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(690, 330, 281, 191));
        widget_3->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A; \n"
""));
        label = new QLabel(widget_3);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 20, 201, 31));
        QFont font4;
        font4.setBold(true);
        label->setFont(font4);
        label->setStyleSheet(QString::fromUtf8("border-color: rgb(184, 226, 242);\n"
"color: rgb(170, 0, 0);\n"
""));
        pushButton_12 = new QPushButton(widget_3);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(10, 20, 51, 31));
        pushButton_12->setStyleSheet(QString::fromUtf8("background-color: rgb(176, 0, 0);\n"
"border-color: rgb(184, 226, 242);"));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DialogWarning));
        pushButton_12->setIcon(icon2);
        widget_4 = new QWidget(page_2);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(110, 30, 541, 311));
        widget_4->setStyleSheet(QString::fromUtf8("border: 3px solid #1E3A8A; \n"
""));
        image2 = new QLabel(page_2);
        image2->setObjectName("image2");
        image2->setGeometry(QRect(930, 20, 51, 61));
        image2->setPixmap(QPixmap(QString::fromUtf8("images/1223.jpg")));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(widget_2);

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


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion de Stock", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Tableau de bord", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Produit", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Ventes", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "  Taper l'Id ou r\303\251f\303\251rence...", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Genre", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Export format Excel", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Cat\303\251gories :</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Prix :</span></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "   Lunettes", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "   Lentilles", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "   Accessoires", nullptr));

#if QT_CONFIG(whatsthis)
        comboBox->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_5->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "- Suppression de produit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "+ Ajouter / modifier un produit", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_3->setText(QString());
        lineEdit_4->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 :", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", " Marque :", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Rr\303\251f\303\251rence", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Genre :", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Date d'expiration:", nullptr));
        lineEdit_7->setText(QString());
        lineEdit_8->setText(QString());
        lineEdit_9->setText(QString());
        radioButton->setText(QCoreApplication::translate("MainWindow", "Male", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Femelle", nullptr));
        lineEdit_5->setText(QString());
        pushButton->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        image->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Alerte de rupture de stock", nullptr));
        pushButton_12->setText(QString());
        image2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
