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
