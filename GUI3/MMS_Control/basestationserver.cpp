
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

void basestationServer::incomingConnection(qintptr socketDescriptor) //Gets called when there is a new connection
{
    qDebug("Connected to AGV");
    socket.setSocketDescriptor(socketDescriptor);
    thread = new basestationThread(&socket, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    emit connected();
}

void basestationServer::disconnected(){ //Gets called when the socket disconnects
    qDebug("Disconnecting\n");
    socket.disconnectFromHost();
    socket.waitForDisconnected();
    emit disconnecting();
}

void basestationServer::readData(){//Gets called when data is recieved

    char client_message[2000] ={0};
    socket.read(client_message, 2000);

    for(size_t i=0; i<(strlen(client_message)); i++){//Filter foute tekens
        if(client_message[i]<32 || client_message[i]>59){
            //qDebug("False ID: %d\n",(int)client_message[i]);
            client_message[i] =0;
        }
    }

    emit newMessage(QString(client_message));

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
        //qDebug("offset msg: %s \n", msg);
        char reply_message[20]={'3',':',':'};
        reply_message[3]=client_message[3];
        reply_message[4]=client_message[4];
        reply_message[5]=client_message[5];
        int packetnum = getNum(reply_message);
        //qDebug("Packet: %d\n",packetnum);
        if(lastRecievedDataPacketNum != packetnum){
                if(writeToFile(msg) == 1){
                //qDebug("Data saved in: %s\n", FILENAME);
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
        //thread->reply = reply_message;
        socket.write(reply_message);
        socket.flush();
        socket.waitForBytesWritten(3000);
    }
    else if(client_message[0] == '1'){//Reply message
        qDebug("Received AGV Reply: %s\n", client_message);
        lastRecievedReplyPacketNum = getNum(client_message);
        //qDebug("GOT REPLY: %d \n",lastRecievedReplyPacketNum);
        if(packet_nr == lastRecievedReplyPacketNum){
                packet_nr++;
                thread->command = "-";
        }
    }
}

int basestationServer::writeToFile(const char text[]){//Opens file as apendable and writes the new data to it
    QFile file(_directory);
    qDebug("Saving in "+ _directory.toLatin1());
    if (!file.open(QIODevice::Append)) {
            qDebug() << file.errorString();
            return 0;
    }
    else
    {
        file.write(text);
        file.write("\n");
        file.close();
        return 1;
    }
}

int basestationServer::getNum(char array[]){//Converts char array to integer number(can most likely be done easier with a build in function)
    int value = 0;
    int multiplier[3] = {100,10,1};
    for(int i = 0; i < 3;i++){
        value += (array[i + 3] - '0') * multiplier[i];
    }
    return (value);
}


void basestationServer::makeCommand(QString command){//Sets a new command in the thread which keeps repeating it until it gets a reply
    sprintf(packet_nr_send,"%03d::",packet_nr);
    //qDebug("sending 1 " + command.toLatin1());
    command[3] = packet_nr_send[0];
    command[4] = packet_nr_send[1];
    command[5] = packet_nr_send[2];

    qDebug("sending " + command.toLatin1());
    thread->command = command;
}

void basestationServer::setDirectory(QString directory){//To set the directory from the mainwindow
    _directory = directory;
}
