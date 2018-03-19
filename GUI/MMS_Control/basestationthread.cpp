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


void basestationThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }
    char client_message[2000]={0};

    for(int i=0; i<(strlen(client_message)); i++){
                if(client_message[i]<32){
                    //printf("False ID: %d\n",(int)client_message[i]);
                    client_message[i] =0;
                }
            }
            if(client_message[0] == '0'){//Data message
                printf("Received AGV Data: %s\n", client_message);
                //Send the message back to client
                int dataOffset = 8;
                char msg[2000-8]={0};
                for(int i=dataOffset; i<(strlen(client_message)); i++){
                    if(client_message[i]==':' && client_message[i-1]==':' && client_message[i-2]=='1' && i>1){
                        msg[i-dataOffset -1] = 0;
                        msg[i-dataOffset -2] = 0;
                        break;
                    }
                    msg[i-dataOffset]=client_message[i];
                }
                //printf("msg: %s \n", msg);
                char reply_message[20]={'3',':',':'};
                reply_message[3]=client_message[3];
                reply_message[4]=client_message[4];
                reply_message[5]=client_message[5];
                int packetnum = getNum(reply_message);
                //printf("Packet: %d\n",packetnum);
                if(lastRecievedDataPacketNum != packetnum){
                        if(writeToFile(FILENAME,msg) == 1){
                        printf("Data saved in: %s\n", FILENAME);
                        for(int i=0; i<sizeof(SAVED); i++){
                                reply_message[i+6]=SAVED[i];
                        }
                        lastRecievedDataPacketNum = packetnum;
                    }
                    else{
                        printf("ERROR: data NOT saved!\n");
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
                    printf("Sending Reply: %s \n", reply_message);
                    tcpSocket.write(reply_message , strlen(reply_message));
            }
            else if(client_message[0] == '1'){//Reply message
                printf("Received AGV Reply: %s\n", client_message);
                lastRecievedReplyPacketNum = getNum(client_message);
                //printf("GOT REPLY: %d \n",lastRecievedReplyPacketNum);

            }
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
