#include "login.h"
#include "ui_login.h"
#include "tab.h"
#include "dashboardwindow.h"
#include "gestionemploye00.h"
#include "gclient1.h"
#include "fournisseurwindow.h"
#include "saleswindow.h"
#include "mainwindow.h"
#include <QMessageBox>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_2_clicked()
{
    QString identfient = ui->id1->text();
    QString motdepasse = ui->mot1->text();

    if(identfient=="admin"&&motdepasse=="baha"){
        DashboardWindow::getInstance();
        this->close();
    }
    else if(identfient == "employe" && motdepasse == "employe"){
        gestionemploye00 *gestionemploye00Window = new gestionemploye00();
        gestionemploye00Window->show();
        this->close();
    }
    else if(identfient == "fourni" && motdepasse == "fourni"){
        FournisseurWindow *fourWindow = new FournisseurWindow();
        fourWindow->show();
        this->close();
    }
    else if(identfient == "client" && motdepasse == "client"){
        Gclient1 *gclient1Window = new Gclient1();
        gclient1Window->show();
        this->close();
    }
    else if(identfient == "vent" && motdepasse == "vent"){
        SalesWindow *SalesWindowWindow = new SalesWindow();
        SalesWindowWindow->show();
        this->close();
    }
    else if(identfient == "stock" && motdepasse == "stock"){
        MainWindow *MainWindowWindow = new MainWindow();
        MainWindowWindow->show();
        this->close();
    }
    else{
        QMessageBox::warning(this, "Mot de passe invalide", "Erreur d'authentification");
    }
}

