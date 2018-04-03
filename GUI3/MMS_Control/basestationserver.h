#ifndef BASESTATIONSERVER_H
#define BASESTATIONSERVER_H


#include "basestationthread.h"
#include <QStringList>
#include <QTcpSocket>
#include <QTcpServer>


class basestationServer : public QTcpServer
{
    Q_OBJECT

public:
    basestationServer(QObject *parent = 0);
    void makeCommand(QString command);

    void sendCommand();
    void setDirectory(QString directory);

signals:
    void newMessage(QString message);
    void messageSend(int packet_nr);
    void connected();
    void disconnecting();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    basestationThread* thread;
    QTcpSocket socket;
    int writeToFile(const char text[]);
    int getNum(char array[]);

    QString _directory;
    int lastRecievedDataPacketNum = -1,lastRecievedReplyPacketNum = -1,packet_nr =0,rotator = 0;
    char packet_nr_send[3];

public slots:
     void disconnected();

private slots:
     void readData();
};
#endif // BASESTATIONSERVER_H
