#include "basestationserver.h"
#include "basestationthread.h"

#include "mainwindow.h"

basestationServer::basestationServer(QObject *parent)
    : QTcpServer(parent)
{

    connect(&socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(&socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
}

void basestationServer::incomingConnection(qintptr socketDescriptor)//Start server thread
{
//    qDebug("incomingConnection!\n");

//    basestationThread *thread = new basestationThread(socketDescriptor, this);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    thread->start();
    socket.setSocketDescriptor(socketDescriptor);
    qDebug("connected \n");

}

void basestationServer::disconnected(){
    qDebug("Disconnecting thread \n");
    //QTcpSocket tcpSocket;
    socket.disconnectFromHost();
    socket.waitForDisconnected();
}
void basestationServer::readyRead(){
    //QTcpSocket tcpSocket;
    char client_message[2000] ={0};
    qDebug("read %d\n",socket.read(client_message, 2000));
    qDebug("Message %s\n",client_message);
    lastmessage = QString(client_message);
    emit newMessage(lastmessage);
}

void basestationServer::sendCommand(){
        char packet_nr_send[3];
        char command[200];
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

        qDebug("Writing");
        socket.write("2::102::0::0::1;2;3;4;2.5;\n");
        socket.flush();
        socket.waitForBytesWritten(3000);
}
