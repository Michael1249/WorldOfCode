#include <QDataStream>
#include "server.h"
#include "qiostream.h"
#include <config.h>

using namespace serverSpace;
using namespace QIO;

void Server::start()
{
    mptrServer = new QTcpServer(this);

    connect(mptrServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if(!mptrServer->listen(QHostAddress::Any, ConfigSpace::PORT))
        qout << "Server is not started. " << mptrServer->errorString() << endl;
    else
        qout << "Server is started" << endl;

    qout.flush();
}

void Server::slotNewConnection()
{
    QTcpSocket* clientSocket = mptrServer->nextPendingConnection();
    qint64 socketID = clientSocket->socketDescriptor();

    qout << "New connection. Socket ID " << socketID << endl;
    qout.flush();

    mClientSockets[socketID] = clientSocket;

    connect(mClientSockets[socketID], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    connect(mClientSockets[socketID], SIGNAL(disconnected()), this, SLOT(slotClientDisconnect()));

    if(socketID == 8) sendToAllClients("Hello");
}

void Server::slotReadClient()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());

    QDataStream in(clientSocket);

    for(;;)
    {
        if(!mi16_nextBlockSize)
        {
            if(clientSocket->bytesAvailable() < sizeof (quint16)) break;

            in >> mi16_nextBlockSize;
        }

        if(clientSocket->bytesAvailable() < mi16_nextBlockSize) break;

        QString str;
        quint8 type;

        in >> type >> str;

        mi16_nextBlockSize = 0;

        qout << "Client send: " << str << " type: " << (type == 0 ? "FILE" : "COMMAND") << endl;
        qout.flush();
    }

    clientSocket->flush();
}

void Server::slotClientDisconnect()
{
    using namespace QIO;
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());

    qout << mClientSockets.size() << endl;
    qout.flush();

    mClientSockets.remove(clientSocket->socketDescriptor());
    clientSocket->deleteLater();

    qout << mClientSockets.size() << endl;
    qout.flush();
}



void Server::sendToClient(const qint64 pll_clientSocketID, const QString pMessage)
{
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket->setSocketDescriptor(pll_clientSocketID);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out << quint16(0) << pMessage;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    clientSocket->write(arrBlock);
}

void Server::sendToAllClients(const QString pMessage)
{
    for(auto& sockeyID: mClientSockets.keys())
        sendToClient(sockeyID, pMessage);
}

void Server::shutdown()
{
    for(auto& i: mClientSockets)
    {
        i->write("Server shutdown.\n");
        i->close();
    }

    mptrServer->close();
    mptrServer->deleteLater();
}
