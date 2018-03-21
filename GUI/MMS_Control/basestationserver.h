#ifndef BASESTATIONSERVER_H
#define BASESTATIONSERVER_H

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


};
#endif // BASESTATIONSERVER_H
