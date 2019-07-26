#ifndef CLIENT_H
#define CLIENT_H


#include <QtNetwork/QTcpSocket>
#include <QObject>

namespace clientSpace
{

class Client : QTcpSocket
{
Q_OBJECT

public:
    Client(const QString pHost);
    ~Client() { delete mp_clientSocket; }

    void sendToServer(const QString);
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
