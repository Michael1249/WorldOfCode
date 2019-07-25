#include "server.h"
#include "qiostream.h"

using namespace serverSpace;

Server::Server(int pPort) : mNextBlockSize(0)
{
    mptrServer = new QTcpServer(this);
     if (!mptrServer->listen(QHostAddress::Any, pPort)) {
         qio::qout << "Unable to start the server:" + mptrServer->errorString() << endl;
         mptrServer->close();
         return;
     }

     connect(mptrServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void Server::slotNewConnection()
{
    QTcpSocket* ptrClientSocket = mptrServer->nextPendingConnection();
    connect(ptrClientSocket, SIGNAL(disconnected()),  ptrClientSocket, SLOT(deleteLater()));
    connect(ptrClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(ptrClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);

    for (;;) {
        if (!mNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> mNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < mNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage =
            time.toString() + " " + "Client has sended - " + str;
        qio::qout << strMessage << endl;

        mNextBlockSize = 0;

        sendToClient(pClientSocket, "Server Response: Received \"" + str + "\"");
    }
}

void Server::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
