#ifndef BASESTATIONTHREAD_H
#define BASESTATIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

#include <mainwindow.h>

class basestationThread : public QThread
{
    Q_OBJECT

public:
    basestationThread() = default;
    basestationThread(int socketDescriptor, QObject *parent);
    void run() override;

public slots:
    void sendCommand(QString comm);

signals:
    void error(QTcpSocket::SocketError socketError);
    void newMessage(QString message);

private:
    QTcpSocket tcpSocket;
    int socketDescriptor;
    int lastRecievedDataPacketNum;
    int lastRecievedReplyPacketNum;

    QString text;
    int getNum(char array[]);
    int writeToFile(const char filename[], char text[]);



private slots:
     void readyRead();
     void disconnected();
};

#endif // BASESTATIONTHREAD_H
