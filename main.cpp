#include "gclient1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gclient1 w;
    w.show();  // The constructor already maximizes it
    return a.exec();
}
