#include "server.h"
#include "qiostream.h"

using namespace serverSpace;

void Server::start()
{
    mptrServer = new QTcpServer(this);

    connect(mptrServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if(!mptrServer->listen(QHostAddress::Any, 9999)){
        QIO::qout << "Server is not started. " << mptrServer->errorString() << endl;

        QIO::qout.flush();
    } else {
        QIO::qout << "Server is started" << endl;
        QIO::qout.flush();
    }
}

void Server::slotNewConnection()
{
    QTcpSocket* clientSocket = mptrServer->nextPendingConnection();
    qint64 socketID = clientSocket->socketDescriptor();

    QIO::qout << "New connection. Socket ID " << socketID << endl;
    QIO::qout.flush();

    mClientSockets[socketID] = clientSocket;

    connect(mClientSockets[socketID], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    connect(mClientSockets[socketID], SIGNAL(disconnected()), this, SLOT(slotClientDisconnect()));
}

void Server::slotReadClient()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());

    QIO::qout << "Client sended - " << clientSocket->readAll() << endl;
    QIO::qout.flush();
}

void Server::slotClientDisconnect()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());

    clientSocket->close();
    mClientSockets.remove(clientSocket->socketDescriptor());
}

void Server::shutdown()
{
    for(auto& i: mClientSockets)
    {
        i->write("Server shutdowned.\n");
        i->close();
    }

    mptrServer->close();
}

Server::~Server()
{
    shutdown();

    delete mptrServer;
}
