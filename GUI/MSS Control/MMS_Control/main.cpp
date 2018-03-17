#include "mainwindow.h"
#include "basestationserver.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MMS Controls");
    w.show();

    //while(basestationServer.writeToFile() != 0)
    //}



    return a.exec();
}
