#include "login.h"
#include "ui_login.h"
#include "tab.h"
#include "dashboardwindow.h"
#include "gestionemploye00.h"
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
    }else{
        QMessageBox ::warning(this," mot de pass in valide","eurreur");
    }
}

