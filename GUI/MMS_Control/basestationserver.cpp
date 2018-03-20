#include "basestationserver.h"
#include "basestationthread.h"

#include "mainwindow.h"

basestationServer::basestationServer(QObject *parent)
    : QTcpServer(parent)
{

}

void basestationServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug("incomingConnection!\n");

    basestationThread *thread = new basestationThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void basestationServer::sendCommand(int command[]){
        char packet_nr_send[3];
        for(int i =0; i<sizeof(command);i++){
            command[i]=0;
        }
        command[0] = '2';
        command[1] = ':';
        command[2] = ':';
        command[3] = packet_nr_send[0];
        command[4] = packet_nr_send[1];
        command[5] = packet_nr_send[2];
        command[6] = ':';
        command[7] = ':';
        command[8] = '0';
        command[9] = ':';
        command[10] = ':';
        command[11] = '5';
        command[12] = ':';
        command[13] = ':';
        command[14] = '1';
        command[15] = ';';
        command[16] = '2';
        command[17] = ';';
}
