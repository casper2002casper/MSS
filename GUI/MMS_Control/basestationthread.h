#ifndef BASESTATIONTHREAD_H
#define BASESTATIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

class basestationThread : public QThread
{
    Q_OBJECT

public:
    basestationThread(int socketDescriptor, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    int lastRecievedDataPacketNum;
    int lastRecievedReplyPacketNum;

    QString text;
    int getNum(char array[]);
    int writeToFile(const char filename[], char text[]);
    void getData();

private slots:
     void readyRead();
     void disconnect();
};

#endif // BASESTATIONTHREAD_H
