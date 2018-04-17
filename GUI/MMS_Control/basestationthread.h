// Made by:
// Casper Pennings & Bram Langerak
// For the minor project SCOUT 2018
// Version 1.07 17-04-2018

#ifndef BASESTATIONTHREAD_H
#define BASESTATIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtWidgets>

class basestationThread : public QThread
{
    Q_OBJECT

public:
    basestationThread() = default;
    basestationThread(QTcpSocket *socket, QObject *parent = 0);
    QString command = "-";
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:

    QTcpSocket *_socket;
    QMutex m_mutex;
};

#endif // BASESTATIONTHREAD_H
