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
    void shutdown();

private slots:
    void slotReadClient();
    void slotNewConnection();
    void slotClientDisconnect();

public:
    void start();
    ~Server();
};

}

#endif
