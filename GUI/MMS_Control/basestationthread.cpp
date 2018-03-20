#include "basestationthread.h"
#include "mainwindow.h"

#include <QtNetwork>

#define FILENAME "BaseStationMeasurementData.csv"
#define SAVED "saved"
#define NOTSAVED "not saved"

basestationThread::basestationThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), lastRecievedDataPacketNum(-1), lastRecievedReplyPacketNum(-1)
{
}

int basestationThread::getNum(char array[]){
    int value = 0;
    int multiplier[3] = {100,10,1};
    for(int i = 0; i < 3;i++){
        value += (array[i + 3] - '0') * multiplier[i];
    }
    return (value);
}

int basestationThread::writeToFile(const char filename[], char text[]){
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

void basestationThread::getData(){
    static int read_size = 1;
    QTcpSocket tcpSocket;
    while(true){

        char client_message[2000]={0};
        tcpSocket.read(client_message, 2000);
        for(size_t i=0; i<(strlen(client_message)); i++){
            if(client_message[i]<32){
                qDebug("False ID: %d\n",(int)client_message[i]);
                client_message[i] =0;
            }
        }
        if(client_message[0] == '0'){//Data message
            qDebug("Received AGV Data: %s\n", client_message);
            //Send the message back to client
            int dataOffset = 8;
            char msg[2000-8]={0};
            for(size_t i=dataOffset; i<(strlen(client_message)); i++){
                if(client_message[i]==':' && client_message[i-1]==':' && client_message[i-2]=='1' && i>1){
                    msg[i-dataOffset -1] = 0;
                    msg[i-dataOffset -2] = 0;
                    break;
                }
                msg[i-dataOffset]=client_message[i];
            }
            qDebug("msg: %s \n", msg);
            char reply_message[20]={'3',':',':'};
            reply_message[3]=client_message[3];
            reply_message[4]=client_message[4];
            reply_message[5]=client_message[5];
            int packetnum = getNum(reply_message);
            qDebug("Packet: %d\n",packetnum);
            if(lastRecievedDataPacketNum != packetnum){
                    if(writeToFile(FILENAME,msg) == 1){
                    qDebug("Data saved in: %s\n", FILENAME);
                    for(int i=0; i<sizeof(SAVED); i++){
                            reply_message[i+6]=SAVED[i];
                    }
                    lastRecievedDataPacketNum = packetnum;
                }
                else{
                    qDebug("ERROR: data NOT saved!\n");
                    for(int i=0; i<sizeof(NOTSAVED); i++){
                            reply_message[i+6]=NOTSAVED[i];
                    }
                    }
            }
            else {
                for(int i=0; i<sizeof(SAVED); i++){
                        reply_message[i+6]=SAVED[i];
                }
            }
                qDebug("Sending Reply: %s \n", reply_message);
               // tcpSocket.write(reply_message , strlen(reply_message));
            usleep(50000);
        }
        else if(client_message[0] == '1'){//Reply message
            qDebug("Received AGV Reply: %s\n", client_message);
            lastRecievedReplyPacketNum = getNum(client_message);
            qDebug("GOT REPLY: %d \n",lastRecievedReplyPacketNum);

        }
        else {
            qDebug("niks");
            usleep(5000);
        }
    }
}

void basestationThread::disconnect(){
    QTcpSocket tcpSocket;

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}


void basestationThread::run()
{
    qDebug("Thread created \n");
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;}


    tcpSocket.open(QIODevice::WriteOnly);
    QDataStream out(&tcpSocket);   // we will serialize the data into the file
    out << (int) 5;

//    int numRead = 0, numReadTotal = 0;
//    char buffer[50];

//        forever {
//            numRead  = tcpSocket.read(buffer, 50);

//            // do whatever with array

//            numReadTotal += numRead;
//            qDebug("GOT REPLY: %d \n",numReadTotal);
//            if (numRead == 0 && !tcpSocket.waitForReadyRead())
//                break;
//        }
//    tcpSocket.open(QIODevice::ReadOnly);
//    QDataStream in(&tcpSocket);    // read the data serialized from the file
//    QString str;
//    qint32 a;
//    in >> str >> a;
//    qDebug("GOT RE: %s \n", qUtf8Printable(str));
//    qDebug("GOT REPLY: %d \n",a);
   // getData();
//    while(true){
//        qDebug(tcpSocket.readAll());
//        //getData();
//        usleep(5000);
//    }
}
