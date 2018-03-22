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
