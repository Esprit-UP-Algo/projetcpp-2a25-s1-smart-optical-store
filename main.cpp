#include <QApplication>
#include "gclient1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gclient1 w;  // Crée une instance de la classe Gclient1
    w.show();  // Affiche la fenêtre principale
    return a.exec();  // Lance la boucle d'événements de l'application
}
