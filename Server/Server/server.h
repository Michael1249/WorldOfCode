#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <QTime>

namespace serverSpace
{


class Server : QTcpServer
{
Q_OBJECT
private:
    QTcpServer* mptrServer;
    quint16 mNextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);
public:
    Server(int pPort);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};


}

#endif // SERVER_H
