//#include <QtNetwork>
//#include <QtWidgets>

//#include <stdlib.h>

//#include <qlocalserver.h>
//#include <qlocalsocket.h>

//#define FILENAME "BaseStationMeasurementData.csv"
//#define SAVED "saved"
//#define NOTSAVED "not saved"

//#include <mainwindow.h>
//#include <basestationserver.h>
//#include <basestationthread.h>


//basestationServer::basestationServer(QObject *parent)
//    : QTcpServer(parent)
//{
//    MainWindow mw;
//    mw.inputData("session10");
//}

//void basestationServer::incomingConnection(qintptr socketDescriptor)
//{
//    basestationThread *thread = new basestationThread(socketDescriptor, this);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    thread->start();
//}


//void basestationServer::getData()
//{
//    MainWindow mw;
//    mw.inputData("vef");
//}



#include "basestationserver.h"
#include "basestationthread.h"

basestationServer::basestationServer(QObject *parent)
    : QTcpServer(parent)
{

}

void basestationServer::incomingConnection(qintptr socketDescriptor)
{
    basestationThread *thread = new basestationThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

int basestationServer::writeToFile(char filename[], char text[]){
   //printf("text: %s \n", text);
   FILE *fp;
   fp = fopen(filename, "a");
   if(!fp){
     fclose(fp);
     return 0;
   }else{
     fprintf(fp, "%s\n",text);
     //fprintf(fp, "\n");
     fclose(fp);
     return 1;
   }
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
 //       commandPending = 1;
  //      counter = 0;
}
