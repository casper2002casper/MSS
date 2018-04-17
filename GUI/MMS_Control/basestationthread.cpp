// Made by:
// Casper Pennings & Bram Langerak
// For the minor project SCOUT 2018
// Version 1.07 17-04-2018

#include "basestationthread.h"
#include "mainwindow.h"

#include <QtNetwork>

#define FILENAME "BaseStationMeasurementData.csv"
#define SAVED "saved"
#define NOTSAVED "not saved"

basestationThread::basestationThread(QTcpSocket *socket, QObject *parent)
    : QThread(parent)
{
    //tcpSocket.setSocketDescriptor(socketDescriptor);
    //qDebug("constructor");
    _socket = socket;
    //qDebug("Thread created \n");
}


void basestationThread::run()
{
    while(true){
        //QMutexLocker locker(&m_mutex);
        if(_socket->state() == QAbstractSocket::ConnectedState && command.toLatin1() != "-")
         {
            qDebug("Writing");
            _socket->write(command.toLatin1());
            _socket->flush();
            _socket->waitForBytesWritten(3000);
        }
        msleep(200);
    }
}
