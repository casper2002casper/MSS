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
    void sendCommand();
    QString lastmessage;


signals:
    void newMessage(QString message);


protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QTcpSocket socket;
    int writeToFile(char filename[], char text[]);


private slots:
     void readyRead();
     void disconnected();
};
#endif // BASESTATIONSERVER_H
