// Made by:
// Casper Pennings & Bram Langerak
// For the minor project SCOUT 2018
// Version 1.07 17-04-2018

#include "mainwindow.h"
#include "basestationserver.h"

#include <stdlib.h>

#include <QtCore>
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MMS Controls");
    w.show();

    return a.exec();
}
