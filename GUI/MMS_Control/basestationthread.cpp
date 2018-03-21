#include "basestationthread.h"
#include "mainwindow.h"

#include <QtNetwork>

#define FILENAME "BaseStationMeasurementData.csv"
#define SAVED "saved"
#define NOTSAVED "not saved"

basestationThread::basestationThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), lastRecievedDataPacketNum(-1), lastRecievedReplyPacketNum(-1)
{
    MainWindow mw;
    tcpSocket.setSocketDescriptor(socketDescriptor);
    qDebug("Thread created \n");
    connect(&tcpSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(&tcpSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(&mw, SIGNAL(command()),this, SLOT(sendCommand()));
}
void basestationThread::disconnected(){
    qDebug("Connection disconnected \n");

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
void basestationThread::readyRead(){

    char client_message[2000]={0};
    qDebug("read %d\n",tcpSocket.read(client_message, 2000));
    qDebug("Message %s\n",client_message);
    emit newMessage(QString(client_message));
}
void basestationThread::run()
{
    qDebug("Connection running");
    while(true){
        if(tcpSocket.state() == QAbstractSocket::ConnectedState)
         {
            qDebug("Writing");
            tcpSocket.write("2::102::0::0::1;2;3;4;2.5;\n");
            tcpSocket.flush();
            tcpSocket.waitForBytesWritten(3000);
            QThread::sleep(1);
        }
    }
}
void basestationThread::sendCommand(){
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
        tcpSocket.write("2::102::0::0::1;2;3;4;2.5;\n");
        tcpSocket.flush();
        tcpSocket.waitForBytesWritten(3000);
}
