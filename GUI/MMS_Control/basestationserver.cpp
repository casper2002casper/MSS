#include "basestationserver.h"
#include "basestationthread.h"

#include "mainwindow.h"

basestationServer::basestationServer(QObject *parent)
    : QTcpServer(parent)
{

}

void basestationServer::incomingConnection(qintptr socketDescriptor)//Start server thread
{
    qDebug("incomingConnection!\n");

    basestationThread *thread = new basestationThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
