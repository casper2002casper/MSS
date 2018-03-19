#ifndef BASESTATIONSERVER_H
#define BASESTATIONSERVER_H

//#include <QDataStream>
//#include <QDialog>
//#include <QTcpSocket>
//#include <QObject>
//#include <QTcpServer>

//QT_BEGIN_NAMESPACE
//class QLocalServer;
//QT_END_NAMESPACE

//class basestationServer : public QTcpServer
//{
//    Q_OBJECT

//public:
//    basestationServer(QObject *parent = 0);
//    int writeToFile(char filename[], char text[]);
//    void Connect();
//    void sendCommand(int command[]);
//    void serverConect(const QString host, int port);
//    void getData();
//    void displayError(QAbstractSocket::SocketError socketError);

//protected:
//    void incomingConnection(qintptr socketDescriptor) override;

//private:

//    int getNum(char array[]);
//    void sessionOpened();



//};

#include <QStringList>
#include <QTcpServer>

class basestationServer : public QTcpServer
{
    Q_OBJECT

public:
    basestationServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    int writeToFile(char filename[], char text[]);
    void sendCommand(int command[]);

};
#endif // BASESTATIONSERVER_H
