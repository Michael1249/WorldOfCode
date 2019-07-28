#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QObject>
#include <QFile>
#include <config.h>

namespace clientSpace
{

class Client : QTcpSocket
{
Q_OBJECT

public:
    Client(const QString pHost);
    ~Client() {
        mp_clientSocket->close();
        mp_clientSocket->deleteLater();
    }

    void sendToServer(const QString str, const ConfigSpace::sendType type = ConfigSpace::COMMAND);
    void sendToServer(QFile*);
private:
    QTcpSocket *mp_clientSocket;
    qint16 mi16_nextBlockSize;

private slots:
    void slotReadServer();
    void slotConnected();
    void slotError(QAbstractSocket::SocketError);
};

}

#endif // CLIENT_H
