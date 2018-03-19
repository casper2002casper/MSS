#include "basestationthread.h"
#include "mainwindow.h"

#include <QtNetwork>

basestationThread::basestationThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void basestationThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

 //Lees socket

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
