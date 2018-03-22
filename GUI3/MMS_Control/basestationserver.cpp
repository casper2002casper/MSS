#include "basestationserver.h"
#include "mainwindow.h"

#define FILENAME "BaseStationMeasurementData.csv"
#define SAVED "saved"
#define NOTSAVED "not saved"

basestationServer::basestationServer(QObject *parent)
    : QTcpServer(parent)
{
    connect(&socket, SIGNAL(readyRead()),this, SLOT(readData()));
    connect(&socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
}

void basestationServer::incomingConnection(qintptr socketDescriptor)
{
    socket.setSocketDescriptor(socketDescriptor);
    qDebug("connected \n");
}

void basestationServer::disconnected(){
    qDebug("Disconnecting\n");
    socket.disconnectFromHost();
}
void basestationServer::readData(){

    char client_message[2000] ={0};
    qDebug("read %d\n",socket.read(client_message, 2000));
    qDebug("Message %s\n",client_message);
    lastmessage = QString(client_message);
    emit newMessage(lastmessage);

    for(size_t i=0; i<(strlen(client_message)); i++){
                if(client_message[i]<32){
                    qDebug("False ID: %d\n",(int)client_message[i]);
                    client_message[i] =0;
                }
            }

    if(client_message[0] == '0'){
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
                qDebug("offset msg: %s \n", msg);
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
                    qDebug("test");
                }
                else {
                    for(int i=0; i<sizeof(SAVED); i++){
                            reply_message[i+6]=SAVED[i];
                    }
                }
                    qDebug("Sending Reply: %s \n", reply_message);
                    socket.write(reply_message);
                    socket.flush();
                    socket.waitForBytesWritten(3000);
            }
            else if(client_message[0] == '1'){//Reply message
                qDebug("Received AGV Reply: %s\n", client_message);
                lastRecievedReplyPacketNum = getNum(client_message);
                qDebug("GOT REPLY: %d \n",lastRecievedReplyPacketNum);

            }
    sendPacket();
}

int basestationServer::writeToFile(const char filename[], const char text[]){
   //printf("text: %s \n", text);
   FILE *fp;
   fp = fopen(filename, "a");
   if(!fp){
     fclose(fp);
     return 0;
   }else{
     //qDebug(fp, "%s\n",text);
     //fprintf(fp, "\n");
     fclose(fp);
     return 1;
   }
}

int basestationServer::getNum(char array[]){
    int value = 0;
    int multiplier[3] = {100,10,1};
    for(int i = 0; i < 3;i++){
        value += (array[i + 3] - '0') * multiplier[i];
    }
    return (value);
}

void basestationServer::sendPacket(){
    if(packet_nr == lastRecievedReplyPacketNum){
        packet_nr++;
    }
    else{
        socket.write(command);
        socket.flush();
        socket.waitForBytesWritten(3000);
        qDebug("Sending Data: %s \n",command);
        for(int i =0; i<sizeof(command);i++){
            command[i]=0;
        }
    }
}

void basestationServer::makeCommand(int comm){
        sprintf(packet_nr_send,"%03d::",packet_nr);

        char layoutcommand[] = "2::000::0::0::1;2;3;4;2.5;";
        for(int i =0; i<sizeof(layoutcommand);i++){
            command[i]=layoutcommand[i];
        }
        command[3] = packet_nr_send[0];
        command[4] = packet_nr_send[1];
        command[5] = packet_nr_send[2];
        // uitzoeken welke plek command is
        command[6] = comm;
        command[11] = rotator + '0';
        if(rotator<5)rotator++;
        else rotator = 0;
        if(rotator == 2)rotator++;
}
