#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMap>

namespace serverSpace
{

class Server: public QTcpServer
{
    Q_OBJECT
private:
    QMap<qint64, QTcpSocket*> mClientSockets;
    QTcpServer* mptrServer;
    quint16 mi16_nextBlockSize = 0;

private slots:
    void slotReadClient();
    void slotNewConnection();
    void slotClientDisconnect();

public:
    void sendToClient(const qint64 pll_clientSocketID, const QString pMessage);
    void sendToAllClients(const QString pMessage);
    void start();
    void shutdown();
    ~Server() {delete mptrServer;}
};

}

#endif
