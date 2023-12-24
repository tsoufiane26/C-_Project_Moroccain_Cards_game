#include "mainwindow.h"
#include "manche.h"

#include <QApplication>
#include <QTimer> // Ajout de l'en-tête pour utiliser QTimer


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
