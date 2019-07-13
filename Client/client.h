#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <QTime>

namespace clientSpace
{

class Client : public QTcpSocket
{
Q_OBJECT
private:
    QTcpSocket* mptrSocket;
    quint16 mNextBlockSize;
public:
    Client(const QString pHost, quint16 pPort);
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();
};

}

#endif // CLIENT_H
