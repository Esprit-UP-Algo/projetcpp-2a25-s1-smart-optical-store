#include <QApplication>
#include "gclient1.h"
#include "connexion.h"
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gclient1 w;  // Crée une instance de la classe Gclient1
    Connexion c;
    bool test = c.connect();
    if(test)
    {
        // Charger les clients après la connexion réussie
        w.loadClients();
        w.show();  // Affiche la fenêtre principale après la connexion
        QMessageBox::information(nullptr, QObject::tr("Base de Données ouverte"),
                                 QObject::tr("FELICITATIONS vous etes connectés à la base de données.\n"
                                             "Cliquer OK pour continuer."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("echec"),
                              QObject::tr("echec de connexion à la base de données.\n"
                                          "Cliquer OK pour quitter."), QMessageBox::Cancel);
    }
    return a.exec();  // Lance la boucle d'événements de l'application
}
