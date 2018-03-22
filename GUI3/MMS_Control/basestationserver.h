#ifndef BASESTATIONSERVER_H
#define BASESTATIONSERVER_H

#include <QStringList>
#include <QTcpSocket>
#include <QTcpServer>

class basestationServer : public QTcpServer
{
    Q_OBJECT

public:
    basestationServer(QObject *parent = 0);
    void makeCommand(int comm);

    QString lastmessage;
    void sendPacket();

signals:
    void newMessage(QString message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QTcpSocket socket;
    int writeToFile(const char filename[], const char text[]);
    int getNum(char array[]);


    int lastRecievedDataPacketNum = -1,lastRecievedReplyPacketNum = -1,packet_nr =0,rotator = 0;
    char packet_nr_send[3];
    char command[200] = {"2::000::0::5::1;2;3;4;2.5;\n"};

private slots:
     void readData();
     void disconnected();
};
#endif // BASESTATIONSERVER_H
